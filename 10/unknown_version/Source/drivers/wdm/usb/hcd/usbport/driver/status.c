/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    status.c

Abstract:

    Status Code mapping functions

Environment:

    kernel mode only

Notes:

Revision History:

    06-20-99 : created
    01-12-04 : fix bugs

--*/

#include "common.h"


NTSTATUS
USBPORT_SetUSBDError(
    PURB Urb,
    USBD_STATUS UsbdStatus
    )
/*++

Routine Description:

    Set the USBD error code in the urb and return an NTSTATUS 
    equivalent

Arguments:

    URB urb to set error in (optional)

Return Value:


--*/
{
    if (Urb) {
        Urb->UrbHeader.Status = UsbdStatus;
    }        

    switch (UsbdStatus) {
    case USBD_STATUS_SUCCESS:
        return STATUS_SUCCESS;
        
    case USBD_STATUS_INSUFFICIENT_RESOURCES:
        return STATUS_INSUFFICIENT_RESOURCES;
        
    case USBD_STATUS_INVALID_URB_FUNCTION:    
    case USBD_STATUS_INVALID_PARAMETER:
    case USBD_STATUS_INVALID_PIPE_HANDLE:
    case USBD_STATUS_BAD_START_FRAME:
        return STATUS_INVALID_PARAMETER;
        
    case USBD_STATUS_NOT_SUPPORTED:
        return STATUS_NOT_SUPPORTED;
    case USBD_STATUS_DEVICE_GONE:        
        return STATUS_DEVICE_NOT_CONNECTED;
    case USBD_STATUS_CANCELED:
        return STATUS_CANCELLED;
    }

    return STATUS_UNSUCCESSFUL;
}


USBD_STATUS
USBPORT_MiniportStatus_TO_USBDStatus(
    USB_MINIPORT_STATUS mpStatus
    )
/*++

Routine Description:

    return the USBD status code equivalent for a 
    miniport status code

Arguments:

Return Value:


--*/
{
    USBD_STATUS usbdStatus = USBD_STATUS_STATUS_NOT_MAPPED;

    switch (mpStatus) {
    case USBMP_STATUS_SUCCESS:
        usbdStatus = USBD_STATUS_SUCCESS;
        break;
    case USBMP_STATUS_BUSY:
        //usbdStatus = 
        //should not be mapping this one
        USBPORT_ASSERTMSG("USBMP_STATUS_BUSY cannot be mapped to USBD_STATUS",FALSE);
        break;
    case USBMP_STATUS_NO_RESOURCES:
        usbdStatus = USBD_STATUS_INSUFFICIENT_RESOURCES;
        break;
    case USBMP_STATUS_NO_BANDWIDTH:
        usbdStatus = USBD_STATUS_NO_BANDWIDTH;
        break;
    case USBMP_STATUS_NOT_SUPPORTED:
        usbdStatus = USBD_STATUS_NOT_SUPPORTED;
        break;
    default:
        usbdStatus = USBD_STATUS_INTERNAL_HC_ERROR;
        TEST_TRAP();
        break;
    }

    return usbdStatus;
}


NTSTATUS
USBPORT_MiniportStatus_TO_NtStatus(
    USB_MINIPORT_STATUS mpStatus
    )
/*++

Routine Description:

    return the NT status code equivalent for a 
    miniport status code

Arguments:

Return Value:


--*/
{
    USBD_STATUS usbdStatus;
    NTSTATUS ntStatus;
    
    usbdStatus = 
        USBPORT_MiniportStatus_TO_USBDStatus(mpStatus);

    ntStatus = USBPORT_SetUSBDError(NULL, usbdStatus);

    return ntStatus;
}    


USB_MINIPORT_STATUS
USBPORT_NtStatus_TO_MiniportStatus(
    LONG NtStatus
    )
/*++

Routine Description:

    return the miniport status code equivalent for a 
    NTSTATUS status code

Arguments:

Return Value:


--*/
{
    USB_MINIPORT_STATUS mpStatus;
    
    switch (NtStatus) {
    case STATUS_SUCCESS:
        mpStatus = USBMP_STATUS_SUCCESS;
        break;
        
    default:        
        mpStatus = USBMP_STATUS_NTERRCODE_NOT_MAPPFED;
    }

    return mpStatus;
}    


RHSTATUS
USBPORT_MiniportStatus_TO_RHStatus(
    USB_MINIPORT_STATUS mpStatus
    )
/*++

Routine Description:

    return the RH status code equivalent for a 
    miniport status code

Arguments:

Return Value:


--*/
{
    RHSTATUS rhStatus;

    if (mpStatus == USBMP_STATUS_SUCCESS) {
        rhStatus = RH_SUCCESS;
    } else if (mpStatus == USBMP_STATUS_BUSY) {
        rhStatus = RH_NAK;
    } else {
        rhStatus = RH_STALL;
    }

    return rhStatus;
}    


USBD_STATUS
USBPORT_RHStatus_TO_USBDStatus(
    USB_MINIPORT_STATUS rhStatus
    )
/*++

Routine Description:

    return the RH status code equivalent for a 
    miniport status code

Arguments:

Return Value:


--*/
{
    USBD_STATUS usbdStatus;

    switch (rhStatus) {
    case RH_STALL:
        usbdStatus = USBD_STATUS_STALL_PID;
        break;
    case RH_SUCCESS:
    case RH_PENDING:
        usbdStatus = USBD_STATUS_SUCCESS;
        break;
    case RH_NAK:
    default:
        // why are we mapping a NAK -- this is a bug.
        usbdStatus = USBD_STATUS_STALL_PID;
        TEST_TRAP();
    }

    return usbdStatus;
}        


USBD_STATUS
USBPORT_NtStatus_TO_UsbdStatus(
    LONG NtStatus
    )
/*++

Routine Description:

    map NT status codes to one of the USB status codes

Arguments:

Return Value:


--*/
{
    USBD_STATUS usbdStatus;

    switch (NtStatus) {
        
    case STATUS_SUCCESS:
        usbdStatus = USBD_STATUS_SUCCESS;
        break;

    case STATUS_NO_SUCH_DEVICE:
        usbdStatus = USBD_STATUS_DEVICE_GONE;
        break;

    case STATUS_INSUFFICIENT_RESOURCES: 
        usbdStatus = USBD_STATUS_INSUFFICIENT_RESOURCES;
        break;
        
    case STATUS_NOT_SUPPORTED: 
        usbdStatus = USBD_STATUS_NOT_SUPPORTED;
        break;

    case STATUS_CANCELLED: 
        usbdStatus = USBD_STATUS_CANCELED;
        break;
                
    default:        
        usbdStatus = USBD_STATUS_INVALID_PARAMETER;
    }

    return usbdStatus;
}    

