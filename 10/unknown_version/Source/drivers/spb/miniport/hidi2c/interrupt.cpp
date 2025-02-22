//
//    Copyright (C) Microsoft.  All rights reserved.
//
/*++

Module Name:

    interrupt .cpp 
    
    Device handling events for example driver.

Abstract:

   This file contains the definitions for 
   interrupt callbacks.

Author:

    Arvind Aiyar March 2011
    
Environment:

    Kernel-mode Driver Framework

--*/

#include "internal.h"

#include "interrupt.tmh"


BOOLEAN
OnInterruptIsr(
    _In_  WDFINTERRUPT FxInterrupt,
    _In_  ULONG        MessageID
    )
/*++
 
  Routine Description:

    This routine responds to interrupts generated by the H/W.
    It then quiesces the interrupt and schedules a work-item for 
    additional processing.
    This ISR is called at PASSIVE_LEVEL

  Arguments:
  
    Interrupt - a handle to a framework interrupt object
    MessageID - message number identifying the device's
        hardware interrupt message (if using MSI)

  Return Value:

    TRUE if interrupt recognized.

--*/
{
    UNREFERENCED_PARAMETER(MessageID);

    NTSTATUS status = STATUS_SUCCESS;

    FuncEntry(TRACE_FLAG_INTERRUPT);
             
    // Typically the pattern in most ISRs (DIRQL or otherwise) is to:
    // a) Check if the interrupt belongs to this device (shared interrupts)
    // b) Acknowledge and quiesce the interrupt 
    // c) Disable the interrupt so that it doesnt generate a storm (to be later
    //    re-enabled in the DPC or WorkItem

    // Since the interrupt is PASSIVE_LEVEL we simply read the data to quiesce
    // the interrupt and save it in the request buffer which prevents 
    // it from being over-written. Also, since we are not expecting shared interrupts, 
    // we acknowledge the interrupt as ours
    //

    BOOLEAN interruptRecognized     = TRUE;
    PBYTE   inputReportBuffer       = NULL;
    LONG    inputReportActualLength = 0;
    GUID    activityId = {0};
    WDFREQUEST deviceResetNotificationRequest = NULL;

    PDEVICE_CONTEXT pDeviceContext = GetDeviceContext(WdfInterruptGetDevice(FxInterrupt));

    //
    // Only process Interrupts if HIDClass has queued it's first read request
    // or if this is a Host Initiated Reset, or if there's a device reset 
    // notification request.
    //
  
    if ( pDeviceContext->HostInitiatedResetActive == FALSE &&
         pDeviceContext->ProcessInterrupts == FALSE &&
         pDeviceContext->DeviceResetNotificationRequest == NULL)
    {
        TraceEvents(
                TRACE_LEVEL_INFORMATION,
                TRACE_FLAG_INTERRUPT,
                "Interrupt processing deferred until first Read request");
        goto exit;
    }
    
    //
    // Generate an activityId for this IO flow
    //
    activityId = _LogGetActivityId(NULL);

    //
    // Log the start event signalling an interrupt was received
    //
    EventWrite_HIDI2C_IO_INTERRUPT_RECEIVED(&activityId);

    //
    // When an interrupt is received, we will read the data from the Input Register.
    // This will de-assert the interrupt and device should re-interrupt on new data
    //
    {
        USHORT inputRegister = pDeviceContext->HidSettings.InputRegisterAddress;
        ULONG  inputReportMaxLength = pDeviceContext->HidSettings.InputReportMaxLength;

        //
        // It has at least two bytes.
        // This should have been validated by _HidGetHidDescriptor earlier.
        //
        NT_ASSERT(inputReportMaxLength >= sizeof(USHORT));

        inputReportBuffer = pDeviceContext->pHidInputReport;
        NT_ASSERTMSG("Input Report buffer must be allocated and non-NULL", inputReportBuffer != NULL);

        RtlZeroMemory(pDeviceContext->pHidInputReport, inputReportMaxLength);

        //
        // Issue a writeless-read to retrieve the input report
        //

        status = SpbWritelessRead(
            pDeviceContext->SpbIoTarget,
            pDeviceContext->SpbRequest,
            inputReportBuffer,
            inputReportMaxLength,
            &activityId);

        //
        // We no longer support "normal read" for Input Reports
        // everything defaults to Writeless Read.
        // 
        //else
        //{
        //    status = SpbRead(
        //                pDeviceContext->SpbIoTarget,
        //                inputRegister,
        //                inputReportBuffer,
        //                inputReportMaxLength,
        //                0);
        //}

        if (!NT_SUCCESS(status))
        {
            TraceEvents(
                TRACE_LEVEL_ERROR,
                TRACE_FLAG_INTERRUPT,
                "SpbWritelessRead failed "
                "offset:0x%x status:%!STATUS!",
                inputRegister,
                status);
            goto exit;
        }

        // 
        // Validate the input report first before yanking any requests
        // off the ReportQueue
        //

        //
        // Check if this is a zero length report, which indicates a reset.
        //
        if (*((PUSHORT)inputReportBuffer) == 0)
        {
            //
            // Are we expecting a Host Initated Reset?
            //
            if (pDeviceContext->HostInitiatedResetActive == TRUE)
            {
                //
                // This is what we're waiting for. Reset the flag to indicate 
                // that an interrupt was received in response to the RESET command.
                //
                pDeviceContext->HostInitiatedResetActive = FALSE;
            }
            else
            {
                //
                // This is a Device Initiated Reset. Then we need to complete
                // the Device Reset Notification request if it exists and is 
                // still cancelable.
                //
                BOOLEAN completeRequest = FALSE;

                WdfSpinLockAcquire(pDeviceContext->DeviceResetNotificationSpinLock);

                if (NULL != pDeviceContext->DeviceResetNotificationRequest)
                {
                    deviceResetNotificationRequest = pDeviceContext->DeviceResetNotificationRequest;
                    pDeviceContext->DeviceResetNotificationRequest = NULL;

                    status = WdfRequestUnmarkCancelable(deviceResetNotificationRequest);
                    if (NT_SUCCESS(status))
                    {
                        completeRequest = TRUE;
                    }
                    else
                    {
                        NT_ASSERT(STATUS_CANCELLED == status);
                    }
                }

                WdfSpinLockRelease(pDeviceContext->DeviceResetNotificationSpinLock);

                if (completeRequest)
                {
                    status = STATUS_SUCCESS;

                    TraceEvents(
                        TRACE_LEVEL_INFORMATION,
                        TRACE_FLAG_INTERRUPT,
                        "Detected a device-initiated reset. Completing Device Reset Notification request:0x%p with %!STATUS!.",
                        deviceResetNotificationRequest,
                        status);

                    WdfRequestComplete(deviceResetNotificationRequest, status);
                }
            }
            goto exit;
        }

        //
        // It's not a zero length report. If we've initated a RESET command
        // but got a non-zero length report, we treat it as a protocol error.
        //
        if (pDeviceContext->HostInitiatedResetActive == TRUE)
        {
            status = STATUS_DEVICE_PROTOCOL_ERROR;
            TraceEvents(
                TRACE_LEVEL_ERROR,
                TRACE_FLAG_INTERRUPT,
                "Invalid input report returned for Reset command "
                "status:%!STATUS!",
                status);
            goto exit;
        }

        // 
        // Total Length = 2 Bytes (#Bytes for Length field) + x Bytes (#Bytes for Report field)
        //
        inputReportActualLength =  (*((PUSHORT) inputReportBuffer) - HID_REPORT_LENGTH_FIELD_SIZE);

        //
        // Check if this is a valid report 
        // report length > 0 and < max length
        //
        if (inputReportActualLength <= 0 || (ULONG) inputReportActualLength > inputReportMaxLength)
        {
            status = STATUS_DEVICE_PROTOCOL_ERROR;
            TraceEvents(
                    TRACE_LEVEL_INFORMATION,
                    TRACE_FLAG_INTERRUPT,
                    "Invalid input report returned "
                    "Length:%u status:%!STATUS!",
                    inputReportActualLength,
                    status);
            goto exit;
        }
    }
    
    //
    // Retrieve the next read request from the ReportQueue which
    // stores all the incoming IOCTL_READ_REPORT requests
    // 
    
    WDFREQUEST request = NULL;
    status = WdfIoQueueRetrieveNextRequest(
                            pDeviceContext->ReportQueue,
                            &request);

    //
    // If the queue is empty then there are no Read requests to complete.
    // TODO: Should we save the data anyway and complete it when the 
    // next read request is queued ??
    //
    if (!NT_SUCCESS(status) || (request == NULL))
    {
        TraceEvents(
                (status == STATUS_NO_MORE_ENTRIES) ? TRACE_LEVEL_INFORMATION : TRACE_LEVEL_ERROR,
                TRACE_FLAG_INTERRUPT,
                "Error retrieving request:0x%p from ReportQueue "
                "status:%!STATUS!",
                request,
                status);
        goto exit;
    }
    
    //
    // This IOCTL is METHOD_NEITHER so WdfRequestRetrieveOutputMemory
    // will correctly retrieve buffer from Irp->UserBuffer.
    //
    WDFMEMORY memory;
    status = WdfRequestRetrieveOutputMemory(request, &memory);

    if (!NT_SUCCESS(status)) 
    {
        TraceEvents(
                TRACE_LEVEL_ERROR,
                TRACE_FLAG_INTERRUPT,
                "WdfRequestRetrieveOutputMemory failed "
                "status:%!STATUS!",
                status);
        goto requestComplete;
    }

    //
    // Copy the input report into the request buffer
    //
    status = WdfMemoryCopyFromBuffer(
                            memory,
                            0,
                            inputReportBuffer + HID_REPORT_LENGTH_FIELD_SIZE,
                            inputReportActualLength);

    if (!NT_SUCCESS(status)) 
    {
        TraceEvents(
                TRACE_LEVEL_ERROR,
                TRACE_FLAG_INTERRUPT,
                "WdfMemoryCopyFromBuffer failed "
                "status:%!STATUS!",
                status);
        goto requestComplete;
    }

    //
    // Report how many bytes were copied
    //
    WdfRequestSetInformation(request, inputReportActualLength);
    
requestComplete:

    //
    // Set the activity ID on the IRP and log the ETW event
    //
    // Note: This would overwrite the activityId in the PingPong read IRPs from HIDClass
    // but we are not tracing IRPs anyway so this is ok. Eventually, a EtwWriteTransfer
    // would be the right approach.

    IoSetActivityIdIrp(WdfRequestWdmGetIrp(request), &activityId);
    EventWrite_HIDI2C_IO_FORWARD_TO_COMPLETIONQUEUE(&activityId, request);

    //
    // Forward the request to the completion queue
    //
    status = WdfRequestForwardToIoQueue(request, pDeviceContext->CompletionQueue);

    if (!NT_SUCCESS(status)) 
    {
        //
        // CompletionQueue is a manual-dispatch, non-power-managed queue. This should
        // *never* fail.
        //

        NT_ASSERTMSG("WdfRequestForwardToIoQueue to CompletionQueue failed!", FALSE);

        TraceEvents(
                TRACE_LEVEL_ERROR,
                TRACE_FLAG_INTERRUPT,
                "WdfRequestForwardToIoQueue failed "
                "status:%!STATUS!",
                status);
    }
    
    // Queue a DPC to complete the request
    WdfInterruptQueueDpcForIsr(FxInterrupt);

exit:
    if (!NT_SUCCESS(status)) 
    {
        TraceLoggingInterrupt(
            status, 
            pDeviceContext->FxDevice);
    }
    FuncExit(TRACE_FLAG_INTERRUPT);
    return interruptRecognized;
}


VOID
OnInterruptDpc (
    _In_ WDFINTERRUPT   FxInterrupt,
    _In_ WDFOBJECT      FxDevice
    )
/*++

Routine Description:

    This DPC handler is triggered when a passive-level interrupt fires. 
    It will yank requests from the completion queue and complete them.

Arguments:

    FxInterrupt - framework interrupt object
    FxDevice - framework device object

Return Value:

    None

--*/
{
    UNREFERENCED_PARAMETER(FxDevice);
    
    FuncEntry(TRACE_FLAG_INTERRUPT);

    NTSTATUS status;
    
    BOOLEAN progress, rerun;
    PDEVICE_CONTEXT pDeviceContext = GetDeviceContext(WdfInterruptGetDevice(FxInterrupt));

    //
    // Check if an existing DPC is already in progress
    //
    WdfSpinLockAcquire(pDeviceContext->InProgressLock);
    
    if (pDeviceContext->DpcInProgess == TRUE) 
    {
        pDeviceContext->DpcRerun = TRUE;
        progress = TRUE;
    }
    else 
    {
        pDeviceContext->DpcInProgess = TRUE;
        pDeviceContext->DpcRerun = FALSE;
        progress = FALSE;
    }
    
    WdfSpinLockRelease(pDeviceContext->InProgressLock);

    if (progress == TRUE) 
    {
        //
        // There is already a DPC in progress. Nothing to do
        // since the logic above will take care of it
        //
        goto exit;
    }

    do 
    {  
        for (;;) 
        {
            WDFREQUEST request = NULL;
            status = WdfIoQueueRetrieveNextRequest(
                                    pDeviceContext->CompletionQueue,
                                    &request);

            if (!NT_SUCCESS(status) || (request == NULL))
            {
                break;
            }

            //
            // Log the ETW event for request completion
            //

            GUID activityId = _LogGetActivityId(request);
            EventWrite_HIDI2C_IO_COMPLETE(&activityId, request);
            
            WdfRequestComplete(request, status);

            TraceEvents(
                    TRACE_LEVEL_INFORMATION,
                    TRACE_FLAG_INTERRUPT,
                    "Read request completed for Interrupt:0x%p", FxInterrupt);
        }

        WdfSpinLockAcquire(pDeviceContext->InProgressLock);
        
        if (pDeviceContext->DpcRerun == TRUE) 
        {
            rerun = TRUE;
            pDeviceContext->DpcRerun = FALSE;
        }
        else 
        {
            pDeviceContext->DpcInProgess = FALSE;
            rerun = FALSE;
        }
        
        WdfSpinLockRelease(pDeviceContext->InProgressLock);

    } while (rerun);

exit:
    FuncExit(TRACE_FLAG_INTERRUPT);
    return;

}

VOID
OnInterruptWorkItem(
    _In_ WDFINTERRUPT   FxInterrupt,
    _In_ WDFOBJECT      FxDevice
    )
/*++

Routine Description:

    This work item handler is triggered when a  passive-level interrupt fires. 
    It will yank requests from the completion queue and complete them.

Arguments:

    FxInterrupt - framework interrupt object
    FxDevice - framework device object

Return Value:

    None

--*/
{
    UNREFERENCED_PARAMETER(FxDevice);
    
    FuncEntry(TRACE_FLAG_INTERRUPT);

    NTSTATUS status;
    
    BOOLEAN progress, rerun;
    PDEVICE_CONTEXT pDeviceContext = GetDeviceContext(WdfInterruptGetDevice(FxInterrupt));

    //
    // Check if an existing work-item is already in progress
    //
    WdfSpinLockAcquire(pDeviceContext->InProgressLock);
    
    if (pDeviceContext->DpcInProgess == TRUE) 
    {
        pDeviceContext->DpcRerun = TRUE;
        progress = TRUE;
    }
    else 
    {
        pDeviceContext->DpcInProgess = TRUE;
        pDeviceContext->DpcRerun = FALSE;
        progress = FALSE;
    }
    
    WdfSpinLockRelease(pDeviceContext->InProgressLock);

    if (progress == TRUE) 
    {
        //
        // There is already a workitem in progress. Nothing to do
        // since the logic above will take care of it
        //
        goto exit;
    }

    do 
    {  
        for (;;) 
        {
            WDFREQUEST request = NULL;
            status = WdfIoQueueRetrieveNextRequest(
                                    pDeviceContext->CompletionQueue,
                                    &request);

            if (!NT_SUCCESS(status) || (request == NULL))
            {
                break;
            }

            //
            // Log the ETW event for request completion
            //

            GUID activityId = _LogGetActivityId(request);
            EventWrite_HIDI2C_IO_COMPLETE(&activityId, request);
            
            WdfRequestComplete(request, status);

            TraceEvents(
                    TRACE_LEVEL_INFORMATION,
                    TRACE_FLAG_INTERRUPT,
                    "Read request completed for Interrupt:0x%p", FxInterrupt);

        }

        WdfSpinLockAcquire(pDeviceContext->InProgressLock);
        
        if (pDeviceContext->DpcRerun == TRUE) 
        {
            rerun = TRUE;
            pDeviceContext->DpcRerun = FALSE;
        }
        else 
        {
            pDeviceContext->DpcInProgess = FALSE;
            rerun = FALSE;
        }
        
        WdfSpinLockRelease(pDeviceContext->InProgressLock);

    } while (rerun);

exit:
    FuncExit(TRACE_FLAG_INTERRUPT);
    return;
}

GUID 
_LogGetActivityId(
    _In_opt_ WDFREQUEST FxRequest
    )
/*++
 
  Routine Description:

    This routine attempts to extract an activityId from the supplied WDFREQUEST.  In the
    event that a request isn't provided or that an activityId hasn't already been set,
    this routine will create an activityID and set it into the current thread's TSL
    current irql permitting.

  Arguments:
  
    FxRequest - pointer to a passed in WDFREQUEST

  Return Value:
    
    GUID that represents the activityId

--*/
{
    GUID activityId = {0}, nullGuid = {0};

    //
    // Try to get the activityId from the IRP
    //
    if (ARGUMENT_PRESENT(FxRequest) == TRUE)
    {
        IoGetActivityIdIrp(WdfRequestWdmGetIrp(FxRequest), &activityId);
    }
        
    //
    // If we couldn't get an activityId from the IRP, lets see if we can create one
    //
    if (IsEqualGUID(activityId, nullGuid))
    {
        EtwActivityIdControl(EVENT_ACTIVITY_CTRL_CREATE_ID, &activityId);
    }

    return activityId;
}
