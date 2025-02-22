/*++

Copyright (c) 1999, 2000 Microsoft Corporation

Module Name:

   periodic.c

Abstract:

   miniport transfer code for interrupt endpoints

Environment:

    kernel mode only

Notes:

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
  PURPOSE.

  Copyright (c) 1999, 2000 Microsoft Corporation.  All Rights Reserved.


Revision History:

    1-1-00 : created, jdunn

--*/

#include "common.h"

/*

For USB 2 period indicates a microframe polling interval so
our tree structure is based on microframes.


      |- 1 ms frame -->|<---------  microframe ------------->|
      mic <32>  <16>  <08>   <04>      <02>              <01>

          (table entry)

[FRAME.MICROFRAME] frame_list_Index (offset)
[0.0] 0   ( 0) -\
                ( 0)-\
[2.0] 16  ( 1) -/     \
                      ( 0)-\
[1.0] 8   ( 2) -\     /     \
                ( 1)-/       \
[3.0] 24  ( 3) -/             \
                              (0)-\
[0.4] 4   ( 4) -\             /     \
                ( 2)-\       /       \
[2.4] 20  ( 5) -/     \     /         \
                      ( 1)-/           \
[1.4] 12  ( 6) -\     /                 \
                ( 3)-/                   \
[3.4] 28  ( 7) -/                         \
                                          (0)-\
[0.2] 2   ( 8) -\                         /    \
                ( 4)-\                   /      \
[2.2] 18  ( 9) -/     \                 /        \
                       ( 2)-\          /          \
[1.2] 10  (10) -\     /      \        /            \
                ( 5)-/        \      /              \
[3.2] 26  (11) -/              \    /                \
                               (1)-/                  \
[0.6] 6   (12) -\              /                       \
                ( 6)-\        /                         \
[2.6] 22  (13) -/     \      /                           \
                       ( 3)-/                             \
[1.6] 14  (14) -\     /                                    \
                ( 7)-/                                      \
[3.6] 30  (15) -/                                            \
                                                             (0)
[0.1] 1   (16) -\                                            /
                ( 8)-\                                      /
[2.1] 17  (17) -/     \                                    /
                      ( 4)-\                              /
[1.1] 9   (18) -\     /     \                            /
                ( 9)-/       \                          /
[3.1] 25  (19) -/             \                        /
                              (2)-\                   /
[0.5] 5   (20) -\             /    \                 /
                (10)-\       /      \               /
[2.5] 21  (21) -/     \     /        \             /
                      ( 5)-/          \           /
[1.5] 13  (22) -\     /                \         /
                (11)-/                  \       /
[3.5] 29  (23) -/                        \     /
                                          (1)-/
[0.3] 3   (24) -\                        /
                (12)-\                  /
[2.3] 19  (25) -/     \                /
                      ( 6)-\          /
[1.3] 11  (26) -\     /     \        /
                (13)-/       \      /
[3.3] 27  (27) -/             \    /
                              (3)-/
[0.7] 7   (28) -\             /
                (14)-\       /
[2.7] 23  (29) -/     \     /
                      ( 7)-/
[1.7] 15  (30) -\     /
                (15)-/
[3.7] 31  (31) -/


Allocations:
    period.offset           table entries
      1                    0, 1, 2.........31

      2.0                  0, 1, 2.........15
      2.1                 16,17,18.........31

      4.0                  0, 1, 2..........7
      4.1                  8, 9,10.........15
      4.2                 16,17,18.........23
      4.3                 24,25,26.........31

      8.0                  0, 1, 2, 3
      8.1                  4, 5, 6, 7
      8.2                  8, 9,10,11
      8.3                 12,13,14,15
      8.4                 16,17,18,19
      8.5                 20,21,22,23
      8.6                 24,25,26,27
      8.7                 28,29,30,31

      ...


we mainatin a set of dummy queue heads that correspond to the 1ms nodes
in the chart above.

            the queue head table has 4 entries QH 0..3

            frame   mic frame      qh
              0       0..7         <0>
              1       0..7         <1>

driver maintains a mini tree that has seven QHs that are placed in the
schedule.

period frame(microframes)

      32(4) 16(2)  1(8)

frame

 0   (a 0) -\
           (e 0)-\
 2   (b 1) -/     \
                 (g 0)-
 1   (c 2) -\     /
           (f 1)-/
 3   (d 3) -/



idx    QH  frame
 0       a    0
 1       b    2
 2       c    1
 3       d    3
 4       e    0,2
 5       f    1,3
 6       g    0,2,1,3
*/

/*

We represent each possible node in the tree with a data structure that decodes
the appropriate queue head and S-Mask for the node

*e.g
    for period 8 microframe, sched offset 0 QH = g s-mask = 1

    // The structure contains entries for the 64 possible nodes
    // plus the static ED for bulk and control (2) each entry
    // corresponds to the period in the following table.
    //
    // the array looks like this:
    //  1, 2, 2, 4, 4, 4, 4, 8,
    //  8, 8, 8, 8, 8, 8, 8,16,
    // 16,16,16,16,16,16,16,16,
    // 16,16,16,16,16,16,16,32,
    // 32,32,32,32,32,32,32,32,
    // 32,32,32,32,32,32,32,32,
    // 32,32,32,32,32,32,32,32,
    // 32,32,32,32,32,32,32,

queue heads used for high speed

 0   (3) -\
           (1)-\
 2   (4) -/     \
                 (0)-
 1   (5) -\     /
           (2)-/
 3   (6) -/

*/

/* offsets for each period list */

#define ED_INTERRUPT_1mf    0 //period = 1mf
#define ED_INTERRUPT_2mf    1 //period = 2mf
#define ED_INTERRUPT_4mf    3 //period = 4mf
#define ED_INTERRUPT_8mf    7 //period = 8mf
#define ED_INTERRUPT_16mf   15 //period = 16mf
#define ED_INTERRUPT_32mf   31 //period = 32mf

#define ED_INTERRUPT_1ms    0 //period = 1ms
#define ED_INTERRUPT_2ms    1 //period = 2ms
#define ED_INTERRUPT_4ms    3 //period = 4ms
#define ED_INTERRUPT_8ms    7 //period = 8ms
#define ED_INTERRUPT_16ms   15 //period = 16ms
#define ED_INTERRUPT_32ms   31 //period = 32ms


PERIOD_TABLE periodTable[64] =
   {   // period, qh-idx, s-mask
        1,  0, 0xFF,        // 1111 1111 bits 0..7

        2,  0, 0x55,        // 0101 0101 bits 0,2,4,6
        2,  0, 0xAA,        // 1010 1010 bits 1,3,5,7

        4,  0, 0x11,        // 0001 0001 bits 0,4
        4,  0, 0x44,        // 0100 0100 bits 2,6
        4,  0, 0x22,        // 0010 0010 bits 1,5
        4,  0, 0x88,        // 1000 1000 bits 3,7

        8,  0, 0x01,        // 0000 0001 bits 0
        8,  0, 0x10,        // 0001 0000 bits 4
        8,  0, 0x04,        // 0000 0100 bits 2
        8,  0, 0x40,        // 0100 0000 bits 6
        8,  0, 0x02,        // 0000 0010 bits 1
        8,  0, 0x20,        // 0010 0000 bits 5
        8,  0, 0x08,        // 0000 1000 bits 3
        8,  0, 0x80,        // 1000 0000 bits 7

        16,  1, 0x01,       // 0000 0001 bits 0
        16,  2, 0x01,       // 0000 0001 bits 0
        16,  1, 0x10,       // 0001 0000 bits 4
        16,  2, 0x10,       // 0001 0000 bits 4
        16,  1, 0x04,       // 0000 0100 bits 2
        16,  2, 0x04,       // 0000 0100 bits 2
        16,  1, 0x40,       // 0100 0000 bits 6
        16,  2, 0x40,       // 0100 0000 bits 6
        16,  1, 0x02,       // 0000 0010 bits 1
        16,  2, 0x02,       // 0000 0010 bits 1
        16,  1, 0x20,       // 0010 0000 bits 5
        16,  2, 0x20,       // 0010 0000 bits 5
        16,  1, 0x08,       // 0000 1000 bits 3
        16,  2, 0x08,       // 0000 1000 bits 3
        16,  1, 0x80,       // 1000 0000 bits 7
        16,  2, 0x80,       // 1000 0000 bits 7

        32,  3, 0x01,       // 0000 0000 bits 0
        32,  5, 0x01,       // 0000 0000 bits 0
        32,  4, 0x01,       // 0000 0000 bits 0
        32,  6, 0x01,       // 0000 0000 bits 0
        32,  3, 0x10,       // 0000 0000 bits 4
        32,  5, 0x10,       // 0000 0000 bits 4
        32,  4, 0x10,       // 0000 0000 bits 4
        32,  6, 0x10,       // 0000 0000 bits 4
        32,  3, 0x04,       // 0000 0000 bits 2
        32,  5, 0x04,       // 0000 0000 bits 2
        32,  4, 0x04,       // 0000 0000 bits 2
        32,  6, 0x04,       // 0000 0000 bits 2
        32,  3, 0x40,       // 0000 0000 bits 6
        32,  5, 0x40,       // 0000 0000 bits 6
        32,  4, 0x40,       // 0000 0000 bits 6
        32,  6, 0x40,       // 0000 0000 bits 6
        32,  3, 0x02,       // 0000 0000 bits 1
        32,  5, 0x02,       // 0000 0000 bits 1
        32,  4, 0x02,       // 0000 0000 bits 1
        32,  6, 0x02,       // 0000 0000 bits 1
        32,  3, 0x20,       // 0000 0000 bits 5
        32,  5, 0x20,       // 0000 0000 bits 5
        32,  4, 0x20,       // 0000 0000 bits 5
        32,  6, 0x20,       // 0000 0000 bits 5
        32,  3, 0x08,       // 0000 0000 bits 3
        32,  5, 0x08,       // 0000 0000 bits 3
        32,  4, 0x08,       // 0000 0000 bits 3
        32,  6, 0x08,       // 0000 0000 bits 3
        32,  3, 0x80,       // 0000 0000 bits 7
        32,  5, 0x80,       // 0000 0000 bits 7
        32,  4, 0x80,       // 0000 0000 bits 7
        32,  6, 0x80,       // 0000 0000 bits 7

    };

VOID
EHCI_EnablePeriodicList(
     __inout PDEVICE_DATA DeviceData
    )
{
    KIRQL irql;

    // Must acquire the AcfListSpin spinlock prior to calling
    // EHCI_iEnablePeriodicList() or EHCI_iDisablePeriodicList()
    //
    EHCI_AcquireAsyncDoorbellLock(DeviceData, &irql);

    EHCI_iEnablePeriodicList(DeviceData);

    EHCI_ReleaseAsyncDoorbellLock(DeviceData, irql);
}


VOID
EHCI_DisablePeriodicList(
    __inout PDEVICE_DATA DeviceData
    )
/*++

Routine Description:

    Disables the processing for the Periodic schedule

--*/
{
    KIRQL irql;

    // Must acquire the AcfListSpin spinlock prior to calling
    // EHCI_iEnablePeriodicList() or EHCI_iDisablePeriodicList()
    //
    EHCI_AcquireAsyncDoorbellLock(DeviceData, &irql);

    EHCI_iDisablePeriodicList(DeviceData);

    EHCI_ReleaseAsyncDoorbellLock(DeviceData, irql);
}


_Requires_lock_held_(DeviceData->AcfListSpin)
VOID
EHCI_iEnablePeriodicList(
     __inout PDEVICE_DATA DeviceData
    )
/*++

Routine Description:

Arguments:

Return Value:

--*/
{
    PHC_OPERATIONAL_REGISTER    hcOp;
    USBCMD                      cmd;
    USBSTS                      sts;

    hcOp = DeviceData->OperationalRegisters;

    cmd.ul = READ_REGISTER_ULONG(&hcOp->UsbCommand.ul);
    sts.ul = READ_REGISTER_ULONG(&hcOp->UsbStatus.ul);

    EHCI_UpdateScheduleStates(DeviceData, cmd, sts);
    LOGENTRY(DeviceData, G, '_enP', cmd.ul, sts.ul, 0);

    do {

        if (cmd.ul == 0xffffffff) {
            break;
        }

        // If we are currently waiting for the doorbell request from the
        // host controller and doorbell retry is disabled, prevent changes to
        // the schedule. When the doorbell cycle completes and moves to
        // "AsyncDoorbellState_NotWaiting" state, the last request pending
        // (enable/disable) will be retried
        //

        if (DeviceData->PreventCmdChangesWithDoorbellPending != FALSE &&
            DeviceData->CurrentDoorbellRetryEnableValue == FALSE &&
            EHCI_IsAsyncDoorbellPending(DeviceData) != FALSE) {

            EHCI_SetPeriodicScheduleState(DeviceData, PeriodicScheduleState_EnablePendingDoorbell);
            DeviceData->PeriodicEnableChangeWithDoorbellPending++;
            break;
        }

        if (cmd.PeriodicScheduleEnable == 0)
        {
            if (DeviceData->ImmediatePeriodicEnableChange == 0) {

                // Enhanced Host Controller Interface Specification
                // Revision: 1.0, Section 4.6 Periodic Schedule
                //
                // "Software must not modify the Periodic Schedule Enable bit
                // unless the value of the Periodic Schedule Enable bit
                // equals that of the Periodic Schedule Status bit."
                //
                ULONG   stallcount;

                for (stallcount = 0; stallcount < 15; stallcount++)
                {
                    if (cmd.PeriodicScheduleEnable == sts.PeriodicScheduleStatus)
                    {
                        break;
                    }
                    else
                    {
                        KeStallExecutionProcessor(25);

                        cmd.ul = READ_REGISTER_ULONG(&hcOp->UsbCommand.ul);
                        sts.ul = READ_REGISTER_ULONG(&hcOp->UsbStatus.ul);

                        LOGENTRY(DeviceData, G, '_epS', cmd.ul, sts.ul, 0);
                    }
                }

                if (cmd.PeriodicScheduleEnable != sts.PeriodicScheduleStatus) {
                    // Stats used for debugging purposes.
                    DeviceData->StatPeriodicEnableTimeoutCount++;
                }
            }

            DeviceData->StatPeriodicEnableCount++;

            cmd.PeriodicScheduleEnable = 1;
            cmd.IntOnAsyncAdvanceDoorbell = 0;

            WRITE_REGISTER_ULONG(&hcOp->UsbCommand.ul, cmd.ul);
            EHCI_SetPeriodicScheduleState(DeviceData, PeriodicScheduleState_EnableRequested);

            {
                EVENT_DATA_DESCRIPTOR   EventDataDescriptor[1];

                // The first (and only in this case) data item is the Host
                // Controller data, which is filled in EventDataDescriptor[]
                // by USBPORT.
                //
                RtlZeroMemory(EventDataDescriptor,sizeof(EVENT_DATA_DESCRIPTOR));
                USBPORT_ETW_WRITE(DeviceData,
                                  &USBPORT_ETW_EVENT_HC_PERIODIC_SCHEDULE_ENABLE,
                                  NULL,
                                  1,
                                  EventDataDescriptor);
            }
        }
    } WHILE (0);

    LOGENTRY(DeviceData, G, '_enX', cmd.ul, sts.ul, 0);
}


_Requires_lock_held_(DeviceData->AcfListSpin)
VOID
EHCI_iDisablePeriodicList(
     __inout PDEVICE_DATA DeviceData
    )
/*++

Routine Description:

Arguments:

Return Value:

--*/
{
    PHC_OPERATIONAL_REGISTER    hcOp;
    USBCMD                      cmd;
    USBSTS                      sts;

    hcOp = DeviceData->OperationalRegisters;

    cmd.ul = READ_REGISTER_ULONG(&hcOp->UsbCommand.ul);
    sts.ul = READ_REGISTER_ULONG(&hcOp->UsbStatus.ul);

    EHCI_UpdateScheduleStates(DeviceData, cmd, sts);
    LOGENTRY(DeviceData, G, '_diP', cmd.ul, sts.ul, 0);

    do {

        // If we are currently waiting for the doorbell request from the
        // host controller, prevent changes to the schedule. When the doorbell
        // cycle completes and moves to "AsyncDoorbellState_NotWaiting" state, the
        // last request pending (enable/disable) will be retried
        //

        if (DeviceData->PreventCmdChangesWithDoorbellPending != FALSE &&
            DeviceData->CurrentDoorbellRetryEnableValue == FALSE &&
            EHCI_IsAsyncDoorbellPending(DeviceData) != FALSE) {

            EHCI_SetPeriodicScheduleState(DeviceData, PeriodicScheduleState_DisablePendingDoorbell);
            DeviceData->PeriodicDisableChangeWithDoorbellPending++;
            break;

        }

        if (cmd.PeriodicScheduleEnable == 1) {

            if (DeviceData->ImmediatePeriodicEnableChange == 0) {

                // Enhanced Host Controller Interface Specification
                // Revision: 1.0, Section 4.6 Periodic Schedule
                //
                // "Software must not modify the Periodic Schedule Enable bit
                // unless the value of the Periodic Schedule Enable bit
                // equals that of the Periodic Schedule Status bit."
                //
                ULONG   stallcount;

                for (stallcount = 0; stallcount < 15; stallcount++)
                {
                    if (cmd.PeriodicScheduleEnable == sts.PeriodicScheduleStatus)
                    {
                        break;
                    }
                    else
                    {
                        KeStallExecutionProcessor(25);

                        cmd.ul = READ_REGISTER_ULONG(&hcOp->UsbCommand.ul);
                        sts.ul = READ_REGISTER_ULONG(&hcOp->UsbStatus.ul);

                        LOGENTRY(DeviceData, G, '_dpS', cmd.ul, sts.ul, 0);
                    }
                }

                if (cmd.PeriodicScheduleEnable != sts.PeriodicScheduleStatus) {
                    // Stats used for debugging purposes.
                    DeviceData->StatPeriodicDisableTimeoutCount++;
                }
            }

            DeviceData->StatPeriodicDisableCount++;

            cmd.PeriodicScheduleEnable = 0;
            cmd.IntOnAsyncAdvanceDoorbell = 0;

            WRITE_REGISTER_ULONG(&hcOp->UsbCommand.ul, cmd.ul);
            EHCI_SetPeriodicScheduleState(DeviceData, PeriodicScheduleState_DisableRequested);

            {
                EVENT_DATA_DESCRIPTOR   EventDataDescriptor[1];

                // The first (and only in this case) data item is the Host
                // Controller data, which is filled in EventDataDescriptor[]
                // by USBPORT.
                //
                RtlZeroMemory(EventDataDescriptor,sizeof(EVENT_DATA_DESCRIPTOR));
                USBPORT_ETW_WRITE(DeviceData,
                                  &USBPORT_ETW_EVENT_HC_PERIODIC_SCHEDULE_DISABLE,
                                  NULL,
                                  1,
                                  EventDataDescriptor);
            }
        }
    } WHILE (0);

    LOGENTRY(DeviceData, G, '_diX', cmd.ul, sts.ul, 0);
}


VOID
EHCI_SetPeriodicScheduleState(
     __inout PDEVICE_DATA DeviceData,
     __in PERIODIC_SCHEDULE_STATE NextState
     )
/*

Routine Description:

    Sets the periodic schedule state as specified by the caller.

    Async Doorbell Spinlock is held by the caller

*/
{
    LOGENTRY(DeviceData, G, 'PSTr', DeviceData->PeriodicScheduleState, NextState, 0);

    //
    // If a previous enable/disable schedule operation was blocked due to a pending doorbell,
    // do not overwrite the state so that a retry will be made when doorbell arrives.
    //
    if ((DeviceData->PeriodicScheduleState == PeriodicScheduleState_EnablePendingDoorbell) &&
        (NextState == PeriodicScheduleState_Disabled)) {
            return;
    }

    if ((DeviceData->PeriodicScheduleState == PeriodicScheduleState_DisablePendingDoorbell) &&
        (NextState == PeriodicScheduleState_Enabled)) {
            return;
    }

    DeviceData->PeriodicScheduleState = NextState;
    return;
}


VOID
EHCI_UpdatePeriodicScheduleState(
     __inout PDEVICE_DATA DeviceData,
     __in USBCMD cmd,
     __in USBSTS sts
     )
/*

Routine Description:

    Updates the periodic schedule state based on the current state of the command
    and status registers.

    Async Doorbell Spinlock is held by the caller

*/
{

    LOGENTRY(DeviceData, G, 'PSUp', cmd.ul, sts.ul, 0);

    if (cmd.ul == 0xffffffff) {

        EHCI_SetPeriodicScheduleState(DeviceData, PeriodicScheduleState_Disabled);
        return;
    }

    if (sts.PeriodicScheduleStatus == 0 && cmd.PeriodicScheduleEnable == 0) {

        //
        // Schedule is disabled and no pending request to enable it from the
        // software
        //

        if (DeviceData->StrictTransitionChecksEnabled != FALSE) {
            NT_ASSERTMSG("Invalid state cached in software",
                         DeviceData->PeriodicScheduleState != PeriodicScheduleState_EnableRequested);
        }

        EHCI_SetPeriodicScheduleState(DeviceData, PeriodicScheduleState_Disabled);

    }

    if (sts.PeriodicScheduleStatus == 1 && cmd.PeriodicScheduleEnable == 1) {

        //
        // Schedule is enabled and no pending request to disable it from the
        // software
        //

        if (DeviceData->StrictTransitionChecksEnabled != FALSE) {
            NT_ASSERTMSG("Invalid state cached in software",
                         DeviceData->PeriodicScheduleState != PeriodicScheduleState_DisableRequested);
        }

        EHCI_SetPeriodicScheduleState(DeviceData, PeriodicScheduleState_Enabled);

    }

    if (sts.PeriodicScheduleStatus != cmd.PeriodicScheduleEnable) {

        //
        // Schedule is in transition. Ensure that there was a correct prior request posted
        // to the hardware
        //

        if (cmd.PeriodicScheduleEnable) {

            if (DeviceData->StrictTransitionChecksEnabled != FALSE) {
                NT_ASSERTMSG("Invalid state cached in software",
                             DeviceData->PeriodicScheduleState == PeriodicScheduleState_EnableRequested ||
                             DeviceData->PeriodicScheduleState == PeriodicScheduleState_EnablePendingDoorbell ||
                             DeviceData->PeriodicScheduleState == PeriodicScheduleState_DisablePendingDoorbell);
            }

        } else {

            // NOTE: VIA EHCI Host Controller is known to be violating the following
            // assumption where it can temporarily set the status bit without a prior
            // request in the command enable bit.
            //

            if (DeviceData->StrictTransitionChecksEnabled != FALSE) {
                NT_ASSERTMSG("Invalid state cached in software",
                             DeviceData->PeriodicScheduleState == PeriodicScheduleState_DisableRequested ||
                             DeviceData->PeriodicScheduleState == PeriodicScheduleState_EnablePendingDoorbell ||
                             DeviceData->PeriodicScheduleState == PeriodicScheduleState_DisablePendingDoorbell);
            }

        }

    }

    return;

}


UCHAR ClassicPeriodIdx[8] = {
                           ED_INTERRUPT_1ms, //period = 1ms
                           ED_INTERRUPT_2ms, //period = 2ms
                           ED_INTERRUPT_4ms, //period = 4ms
                           ED_INTERRUPT_8ms, //period = 8ms
                           ED_INTERRUPT_16ms,//period = 16ms
                           ED_INTERRUPT_32ms,//period = 32ms
                           ED_INTERRUPT_32ms,//period = 64ms
                           ED_INTERRUPT_32ms //period = 128ms
                           };

const UCHAR NextFrameQHIndex[] = {
/*   QH index    Normalized frames        QH index            Next frames          */
/* [curr frame]                        [following frame]                           */
/*       0         all frames       */        0,        /*     all frames          */
/*       1  [0 16 8 24 4 20 12 28 2]                       [1 17 9 25 5 21 13 29 3]
             [18 10 26 6 22 14 30]  */        2,        /*   [19 11 27 7 23 15 31] */
/*       2  [1 17 9 25 5 21 13 29 3]                       [0 16 8 24 4 20 12 28 2]
             [19 11 27 7 23 15 31]  */        1,        /*   [18 10 26 6 22 14 30] */
/*       3  [0 16 8 24 4 20 12 28]  */        5,        /*  [1 17 9 25 5 21 13 29] */
/*       4  [2 18 10 26 6 22 14 30] */        6,        /* [3 19 11 27 7 23 15 31] */
/*       5  [1 17 9 25 5 21 13 29]  */        4,        /* [2 18 10 26 6 22 14 30] */
/*       6  [3 19 11 27 7 23 15 31] */        3,        /* [0 16 8 24 4 20 12 28]  */
/*       7       [0 16 8 24]        */       11,        /*       [1 17 9 25]       */
/*       8      [4 20 12 28]        */       12,        /*       [5 21 13 29]      */
/*       9      [2 18 10 26]        */       13,        /*       [3 19 11 27]      */
/*      10      [6 22 14 30]        */       14,        /*       [7 23 15 31]      */
/*      11      [1 17 9 25]         */        9,        /*       [2 18 10 26]      */
/*      12      [5 21 13 29]        */       10,        /*       [6 22 14 30]      */
/*      13      [3 19 11 27]        */        8,        /*       [4 20 12 28]      */
/*      14      [7 23 15 31]        */        7,        /*       [0 16 8 24]       */
/*      15         [0 16]           */       23,        /*          [1 17]         */
/*      16         [8 24]           */       24,        /*          [9 25]         */
/*      17         [4 20]           */       25,        /*          [5 21]         */
/*      18         [12 28]          */       26,        /*          [13 29]        */
/*      19         [2 18]           */       27,        /*          [3 19]         */
/*      20         [10 26]          */       28,        /*          [11 27]        */
/*      21         [6 22]           */       29,        /*          [7 23]         */
/*      22         [14 30]          */       30,        /*          [15 31]        */
/*      23         [1 17]           */       19,        /*          [2 18]         */
/*      24         [9 25]           */       20,        /*          [10 26]        */
/*      25         [5 21]           */       21,        /*          [6 22]         */
/*      26         [13 29]          */       22,        /*          [14 30]        */
/*      27         [3 19]           */       17,        /*          [4 20]         */
/*      28         [11 27]          */       18,        /*          [12 28]        */
/*      29         [7 23]           */       16,        /*          [8 24]         */
/*      30         [15 31]          */       15,        /*          [16 0]         */
/*      31           [0]            */       47,        /*            [1]          */
/*      32           [16]           */       48,        /*            [17]         */
/*      33           [8]            */       49,        /*            [9]          */
/*      34           [24]           */       50,        /*            [25]         */
/*      35           [4]            */       51,        /*            [5]          */
/*      36           [20]           */       52,        /*            [21]         */
/*      37           [12]           */       53,        /*            [13]         */
/*      38           [28]           */       54,        /*            [29]         */
/*      39           [2]            */       55,        /*            [3]          */
/*      40           [18]           */       56,        /*            [19]         */
/*      41           [10]           */       57,        /*            [11]         */
/*      42           [26]           */       58,        /*            [27]         */
/*      43           [6]            */       59,        /*            [7]          */
/*      44           [22]           */       60,        /*            [23]         */
/*      45           [14]           */       61,        /*            [15]         */
/*      46           [30]           */       62,        /*            [31]         */
/*      47           [1]            */       39,        /*            [2]          */
/*      48           [17]           */       40,        /*            [18]         */
/*      49           [9]            */       41,        /*            [10]         */
/*      50           [25]           */       42,        /*            [26]         */
/*      51           [5]            */       43,        /*            [6]          */
/*      52           [21]           */       44,        /*            [22]         */
/*      53           [13]           */       45,        /*            [14]         */
/*      54           [29]           */       46,        /*            [30]         */
/*      55           [3]            */       35,        /*            [4]          */
/*      56           [19]           */       36,        /*            [20]         */
/*      57           [11]           */       37,        /*            [12]         */
/*      58           [27]           */       38,        /*            [28]         */
/*      59           [7]            */       33,        /*            [8]          */
/*      60           [23]           */       34,        /*            [24]         */
/*      61           [15]           */       32,        /*            [16]         */
/*      62           [31]           */       31         /*            [0]          */
};

USB_MINIPORT_STATUS
EHCI_OpenInterruptEndpoint(
     __inout PDEVICE_DATA DeviceData,
     __in PENDPOINT_PARAMETERS EndpointParameters,
     __inout PENDPOINT_DATA EndpointData
    )
/*++

Routine Description:

Arguments:

Return Value:

--*/
{
    PUCHAR buffer;
    HW_32BIT_PHYSICAL_ADDRESS phys, qhPhys;
    PHCD_QUEUEHEAD_DESCRIPTOR qh;
    ULONG i;
    ULONG tdCount, bytes, offset;
    PPERIOD_TABLE periodTableEntry;
    BOOLEAN classic;
    UCHAR periodIdx[8] = {
                           ED_INTERRUPT_1mf, //period = 1mf
                           ED_INTERRUPT_2mf, //period = 2mf
                           ED_INTERRUPT_4mf, //period = 4mf
                           ED_INTERRUPT_8mf, //period = 8mf
                           ED_INTERRUPT_16mf,//period = 16mf
                           ED_INTERRUPT_32mf,//period = 32mf
                           ED_INTERRUPT_32mf,//period = 64mf
                           ED_INTERRUPT_32mf //period = 128mf
                           };

    classic =
        (EndpointData->Parameters.DeviceSpeed != HighSpeed) ? TRUE : FALSE;

    LOGENTRY(DeviceData, G, '_opI', EndpointData, EndpointParameters, classic);

    // select the proper list
    // the period is a power of 2 ie
    // 32,16,8,4,2,1
    // we just need to find which bit is set
    GET_BIT_SET(EndpointParameters->Period, i);
    EHCI_ASSERT(DeviceData, i < 8);
    EHCI_ASSERT(DeviceData, EndpointParameters->Period < 64);

    InitializeListHead(&EndpointData->DoneTdList);

    buffer = EndpointParameters->CommonBufferVa;
    phys = EndpointParameters->CommonBufferPhys;
    offset = EndpointParameters->ScheduleOffset;

    if (classic) {
        i = ClassicPeriodIdx[i];
        periodTableEntry = NULL;
    } else {
        i = periodIdx[i];
        periodTableEntry = &periodTable[i+offset];
    }

    LOGENTRY(DeviceData, G, '_iep', EndpointData,
        periodTableEntry, i);

    // locate the appropriate queue head and period
    // table entry

    if (classic) {
        EndpointData->StaticQH =
            DeviceData->StaticInterruptQH[i+offset];
        EndpointData->PeriodTableEntry = NULL;
    } else {
        EndpointData->StaticQH =
            DeviceData->StaticInterruptQH[periodTableEntry->qhIdx];
        EndpointData->PeriodTableEntry = periodTableEntry;
    }

    // how much did we get
    bytes = EndpointParameters->CommonBufferBytes;

    EndpointData->HwSyncState = Qh_Not_Busy;
    EndpointData->QhChkPhys = phys;
    EndpointData->QhChk = buffer;
    RtlZeroMemory(buffer, 256);
    phys += 256;
    buffer += 256;
    bytes -= 256;

    // make the Ed
    qh = (PHCD_QUEUEHEAD_DESCRIPTOR) buffer;
    qhPhys = phys;

    phys += HCD_QUEUEHEAD_DESCRIPTOR_PAD;
    buffer += HCD_QUEUEHEAD_DESCRIPTOR_PAD;
    bytes -= HCD_QUEUEHEAD_DESCRIPTOR_PAD;

    // td must be equal to PAD value to maintain 4kb alignemnt
    EHCI_ASSERT(DeviceData, sizeof(HCD_TRANSFER_DESCRIPTOR) == HCD_QUEUEHEAD_DESCRIPTOR_PAD);

    tdCount = bytes/sizeof(HCD_TRANSFER_DESCRIPTOR);
    EHCI_ASSERT(DeviceData, tdCount >= TDS_PER_INTERRUPT_ENDPOINT);

    EndpointData->TdList = (PHCD_TD_LIST) buffer;
    EndpointData->TdCount = tdCount;
    for (i=0; i<tdCount; i++) {
        EHCI_InitializeTD(DeviceData,
                          EndpointData,
                          &EndpointData->TdList->Td[i],
                          phys);

        EHCI_AssertHwAlignment(DeviceData, phys, sizeof(HW_QUEUE_ELEMENT_TD));

        phys += sizeof(HCD_TRANSFER_DESCRIPTOR);
    }

    EndpointData->FreeTds = tdCount;

    EndpointData->QueueHead =
        EHCI_InitializeQH(DeviceData,
                          EndpointData,
                          qh,
                          qhPhys);

    if (classic) {
        // use mask parameters passed to us
        qh->HwQH.EpCaps.InterruptScheduleMask =
            EndpointParameters->InterruptScheduleMask;
        qh->HwQH.EpCaps.SplitCompletionMask =
            EndpointParameters->SplitCompletionMask;
    } else {
        qh->HwQH.EpCaps.InterruptScheduleMask =
            periodTableEntry->InterruptScheduleMask;
    }

    EHCI_sMode_InitEndpoint(DeviceData, EndpointData);

    return USBMP_STATUS_SUCCESS;
}

#define SPANS_FRAME_BOUNDARY(m) ((m) & 0x03)


VOID
EHCI_InsertQueueHeadInPeriodicList(
     __inout PDEVICE_DATA DeviceData,
     __inout PENDPOINT_DATA EndpointData
    )
/*++

Routine Description:

   Insert an interrupt endpoint into the h/w schedule

Arguments:


--*/
{
    PHCD_QUEUEHEAD_DESCRIPTOR staticQH, qh, nxtQH, prvQH;
    HW_LINK_POINTER hLink;

    staticQH = EndpointData->StaticQH;
    qh = EndpointData->QueueHead;

    EHCI_ASSERT(DeviceData,
                TEST_FLAG(staticQH->QhFlags, EHCI_QH_FLAG_STATIC));

    EHCI_ASSERT(DeviceData,
                !TEST_FLAG(qh->QhFlags, EHCI_QH_FLAG_IN_SCHEDULE));

    nxtQH = QH_DESCRIPTOR_PTR(staticQH->NextQh);
    prvQH = staticQH;

    // Note: This function must be coherent with the budgeter code
    // the budgeter inserts endpoints such that the newer endpoints
    // are at the end of the sublist, older are at the begining. The
    // lower the ordinal value the older the endpoint.  The ordinal
    // values are used to maintain the same ordering in the event the
    // schedule must be reconstructed

    // hook this queue head to the the static
    // queue head list, two cases

    // case 1:
    // insert QH1, queue head list is not empty:
    //
    // |staticQH|<->QH2<->QH3<->|staticQH|<->QH4
    //
    // |staticQH|<->QH2<->QH3<->QH1<->|staticQH|<->QH4
    //              (o=1)  (o=2)  (o=3)
    //  for case one qeue must insert the queue head in the list
    //  based on the ordinal value we need to compute prev and
    //  next


    // case 2:
    // insert QH1, queue head sublist is empty
    //
    // |staticQH|<->|staticQH|<->QH4
    //
    // |staticQH|<->QH1<->|staticQH|<->QH4

    LOGENTRY(DeviceData, G, '_inQ', EndpointData, qh, staticQH);

    // find the correct spot
    // prvQH, nxtQH are currently the beginnig and end of the
    // sublist
    qh->Ordinal = EndpointData->Parameters.Ordinal;
    qh->Period = EndpointData->Parameters.Period;

    if (TEST_FLAG(prvQH->QhFlags, EHCI_QH_FLAG_STATIC) &&
        (nxtQH == NULL || TEST_FLAG(nxtQH->QhFlags, EHCI_QH_FLAG_STATIC))) {
        // case 2 qh list is empty

        LOGENTRY(DeviceData, G, '_iq1', prvQH, 0, nxtQH);

    } else {
        // case 1 qh list is not empty

        // find the correct position based on ordinal
        while (nxtQH != NULL &&
               !TEST_FLAG(nxtQH->QhFlags, EHCI_QH_FLAG_STATIC) &&
               qh->Ordinal > nxtQH->Ordinal) {

            prvQH = nxtQH;
            nxtQH = QH_DESCRIPTOR_PTR(prvQH->NextQh);

        }

        //if (nxtQH != NULL &&
        //    !TEST_FLAG(nxtQH->QhFlags, EHCI_QH_FLAG_STATIC)) {
        //    // middle insertion
        //    TEST_TRAP(DeviceData);
        //}
    }


    // do the insertion

    QH_DESCRIPTOR_PTR(qh->NextQh) = nxtQH;
    QH_DESCRIPTOR_PTR(qh->PrevQh) = prvQH;
    // next link points back
    if (nxtQH != NULL &&
        !TEST_FLAG(nxtQH->QhFlags, EHCI_QH_FLAG_STATIC)) {
        QH_DESCRIPTOR_PTR(nxtQH->PrevQh) = qh;
    }

    // prev points to new qh
    QH_DESCRIPTOR_PTR(prvQH->NextQh) = qh;

    // now link to HW,order of operation is
    // important here
    hLink.HwAddress = qh->PhysicalAddress;
    SET_QH(hLink.HwAddress);

    qh->HwQH.HLink = prvQH->HwQH.HLink;
    prvQH->HwQH.HLink = hLink;

    SET_FLAG(qh->QhFlags, EHCI_QH_FLAG_IN_SCHEDULE);
    EndpointData->StateChangeTc.QuadPart = 0;
    EndpointData->HwSyncState = Qh_Not_Busy;
}


VOID
EHCI_RemoveQueueHeadFromPeriodicList(
     __inout PDEVICE_DATA DeviceData,
     __inout PENDPOINT_DATA EndpointData
    )
/*++

Routine Description:

   remove an interrupt endpoint into from the h/w schedule

Arguments:


--*/
{
    PHCD_QUEUEHEAD_DESCRIPTOR staticQH, qh, prevQH, nextQH;
    HW_LINK_POINTER hLink;
    PHC_OPERATIONAL_REGISTER hcOp;
    USBCMD cmd;
    USBSTS sts;

    hcOp = DeviceData->OperationalRegisters;

    staticQH = EndpointData->StaticQH;
    qh = EndpointData->QueueHead;

    if (!TEST_FLAG(qh->QhFlags, EHCI_QH_FLAG_IN_SCHEDULE))  {
        // state chnage may still be pending so we don't change the sync state
        LOGENTRY(DeviceData, G, '_rp!', EndpointData, qh, staticQH);

        return;
    }

    LOGENTRY(DeviceData, G, '_rmQ', EndpointData, qh, staticQH);

    // remove the queue head

    // remove QH2, two cases
    // |staticQH|<->QH1<->QH2<->QH3<->|staticQH|<->QH4
    //
    // |staticQH|<->QH1<->QH3<->|staticQH|<->QH4


    prevQH = QH_DESCRIPTOR_PTR(qh->PrevQh);
    nextQH = QH_DESCRIPTOR_PTR(qh->NextQh);

    if (prevQH) {
        LOGENTRY(DeviceData, G, '_rmP', prevQH,
                 QH_DESCRIPTOR_PTR(prevQH->NextQh),
                 QH_DESCRIPTOR_PTR(prevQH->PrevQh));
    }
    if (nextQH) {
        LOGENTRY(DeviceData, G, '_rmN', nextQH,
                 QH_DESCRIPTOR_PTR(nextQH->NextQh),
                 QH_DESCRIPTOR_PTR(nextQH->PrevQh));
    }

    // unlink next ptrs
    QH_DESCRIPTOR_PTR(prevQH->NextQh) = nextQH;
    if (nextQH != NULL &&
        !TEST_FLAG(nextQH->QhFlags, EHCI_QH_FLAG_STATIC)) {
        QH_DESCRIPTOR_PTR(nextQH->PrevQh) = prevQH;
    }

    // hw unlink, nextqh will be null if this is period 1ms
    // qh
    if (nextQH == NULL) {
        hLink.HwAddress = 0;
        SET_T_BIT(hLink.HwAddress);
    } else {
        hLink.HwAddress = nextQH->PhysicalAddress;
        SET_QH(hLink.HwAddress);
    }
    prevQH->HwQH.HLink = hLink;

    CLEAR_FLAG(qh->QhFlags, EHCI_QH_FLAG_IN_SCHEDULE);
    QH_DESCRIPTOR_PTR(qh->NextQh) = NULL;
    QH_DESCRIPTOR_PTR(qh->PrevQh) = NULL;

    cmd.ul = READ_REGISTER_ULONG(&hcOp->UsbCommand.ul);
    sts.ul = READ_REGISTER_ULONG(&hcOp->UsbStatus.ul);

    if ((sts.PeriodicScheduleStatus == 0 && cmd.PeriodicScheduleEnable == 0) ||
        // allow immediate sync if run bit is clear (ie controller stopped)
         cmd.HostControllerRun == 0 ||
         cmd.ul == 0xFFFFFFFF) {

        LOGENTRY(DeviceData, G, '_rmx', qh, 0, 0);
        // mark this qh not busy
        EndpointData->HwSyncState = Qh_Not_Busy;
        EndpointData->StateChangeTc.QuadPart = 0;

    } else {

        EndpointData->HwSyncState = Qh_Busy;
        KeQueryTickCount(&EndpointData->StateChangeTc);
    }
}


USB_MINIPORT_STATUS
EHCI_InterruptTransfer(
     __inout PDEVICE_DATA DeviceData,
     __inout PENDPOINT_DATA EndpointData,
     __inout PTRANSFER_PARAMETERS TransferUrb,
     __inout PTRANSFER_CONTEXT TransferContext,
     __inout PTRANSFER_SG_LIST TransferSGList
    )
/*++

Routine Description:

    Initialize interrupt Transfer

Arguments:

--*/
{
    USB_MINIPORT_STATUS mps;

    EHCI_ASSERT(DeviceData, EndpointData->sMode);

    mps = EHCI_sMode_Transfer(DeviceData,
                              EndpointData,
                              TransferUrb,
                              TransferContext,
                              TransferSGList,
                              FALSE);

    return mps;
}


/*
    CLASSIC

    The classic tree has 63 possible nodes, usport bw manager will select the
    appropriate node based on a 'classic' bus.

    usbport maintains bandwidth management for each classic bus, however
    budgeting the microframes is left to the miniport.

    classic 1ms interrupt schedule, NOTE:this schedule shares some queue heads
    with the high speed schedule.

    * = shared queue head

fr <32>  <16>  <08>   <04>      <02>              <01>


0   ( 0) -\
          ( 0)-\
16  ( 1) -/     \
                ( 0)-\
8   ( 2) -\     /     \
          ( 1)-/       \
24  ( 3) -/             \
                        *(0)-\
4   ( 4) -\             /    \
          ( 2)-\       /      \
20  ( 5) -/     \     /        \
                ( 1)-/          \
12  ( 6) -\     /                \
          ( 3)-/                  \
28  ( 7) -/                        \
                                   *(0)-\
2   ( 8) -\                        /    \
          ( 4)-\                  /      \
18  ( 9) -/     \                /        \
                ( 2)-\          /          \
10  (10) -\     /     \        /            \
          ( 5)-/       \      /              \
26  (11) -/             \    /                \
                        *(1)-/                 \
6   (12) -\             /                       \
          ( 6)-\       /                         \
22  (13) -/     \     /                           \
                ( 3)-/                             \
14  (14) -\     /                                   \
          ( 7)-/                                     \
30  (15) -/                                           \
                                                      *(0)
1   (16) -\                                           /
          ( 8)-\                                     /
17  (17) -/     \                                   /
                ( 4)-\                             /
9   (18) -\     /     \                           /
          ( 9)-/       \                         /
25  (19) -/             \                       /
                        *(2)-\                 /
5   (20) -\             /    \                /
          (10)-\       /      \              /
21  (21) -/     \     /        \            /
                ( 5)-/          \          /
13  (22) -\     /                \        /
          (11)-/                  \      /
29  (23) -/                        \    /
                                   *(1)-/
3   (24) -\                        /
          (12)-\                  /
19  (25) -/     \                /
                ( 6)-\          /
11  (26) -\     /     \        /
          (13)-/       \      /
27  (27) -/             \    /
                        *(3)-/
7   (28) -\             /
          (14)-\       /
23  (29) -/     \     /
                ( 7)-/
15  (30) -\     /
          (15)-/
31  (31) -/


    The node table is arrangened in the standard usb 1.1 fashion so that
    the schedule offset passed to us by the budget engine applies

    // the static array looks like this:
    //  1, 2, 2, 4, 4, 4, 4, 8,
    //  8, 8, 8, 8, 8, 8, 8,16,
    // 16,16,16,16,16,16,16,16,
    // 16,16,16,16,16,16,16,32,
    // 32,32,32,32,32,32,32,32,
    // 32,32,32,32,32,32,32,32,
    // 32,32,32,32,32,32,32,32,
    // 32,32,32,32,32,32,32,


    CLASSIC BUDGET

    The classic budget is maintained by the port driver we
    simply need to program the endpoint at the appropriate
    offset (node) with the given smask cmask

period(ms)    queue head(index)
    1                0
    2                1
    2                2
    4                3
    4                4
    4                5
    4                6
    8                7
    8                8
    8                9
    8               10
    8               11
    8               12
    8               13
    8               14

*/

UCHAR EHCI_Frame2Qhead[32] = {
/*
offset     ms frame
*/
0, //        0
16,//        1
8, //        2
24,//        3
4, //        4
20,//        5
12,//        6
28,//        7
2, //        8
18,//        9
10,//       10
26,//       11
6, //       12
22,//       13
14,//       14
30,//       15
1, //       16
17,//       17
9, //       18
25,//       19
5, //       20
21,//       21
13,//       22
29,//       23
3, //       24
19,//       25
11,//       26
27,//       27
7, //       28
23,//       29
15,//       30
31,//       31
};

PHCD_QUEUEHEAD_DESCRIPTOR
EHCI_GetQueueHeadForFrame(
     __in PDEVICE_DATA DeviceData,
     ULONG Frame
    )
/*++

Routine Description:

Arguments:

Return Value:

    static queue head associated with a particular frame

--*/
{
    PHCD_QUEUEHEAD_DESCRIPTOR qh;
    ULONG f;

    // normalize frame
    f = Frame%32;

    qh = DeviceData->StaticInterruptQH[EHCI_Frame2Qhead[f]+ED_INTERRUPT_32ms];

    return qh;

}


/*

Periodic Schedule Initialization.

The queue head index tables are used to contruct a set of static interrupt queue heads in the host controller schedule
based on the standard tree format.

Queue head index table:

(values) correspond to index in StaticQueueHead List.
<values >indicate microframe period
fr is the absolute frame number (ie cuurent frame MOD 32)

fr <32>  <16>  <08>   <04>      <02>              <01>


0   (31) -\
          (15)-\
16  (32) -/     \
                (7)-\
8   (33) -\     /     \
          (16)-/       \
24  (34) -/             \
                       *(3)-\
4   (35) -\             /    \
          (17)-\       /      \
20  (36) -/     \     /        \
                (8)-/          \
12  (37) -\     /                \
          (18)-/                  \
28  (38) -/                        \
                                  *(1)-\
2   (39) -\                        /    \
          (19)-\                  /      \
18  (40) -/     \                /        \
                (9)-\          /           \
10  (41) -\     /     \        /            \
          (20)-/       \      /              \
26  (42) -/             \    /                \
                       *(4)-/                  \
6   (43) -\             /                       \
          (21)-\       /                         \
22  (44) -/     \     /                           \
                (10)-/                             \
14  (45) -\     /                                   \
          (22)-/                                     \
30  (46) -/                                           \
                                                      *(0)
1   (47) -\                                           /
          (23)-\                                     /
17  (48) -/     \                                   /
                (11)-\                             /
9   (49) -\     /     \                           /
          (24)-/       \                         /
25  (50) -/             \                       /
                       *(5)-\                  /
5   (51) -\             /    \                /
          (25)-\       /      \              /
21  (52) -/     \     /        \            /
                (12)-/          \          /
13  (53) -\     /                \        /
          (26)-/                  \      /
29  (54) -/                        \    /
                                  *(2)-/
3   (55) -\                        /
          (27)-\                  /
19  (56) -/     \                /
                (13)-\          /
11  (57) -\     /     \        /
          (28)-/       \      /
27  (58) -/             \    /
                       *(6)-/
7   (59) -\             /
          (29)-\       /
23  (60) -/     \     /
                (14)-/
15  (61) -\     /
          (30)-/
31  (62) -/

*/

UCHAR EHCI_QHeadLinkTable[63] = {
    /* nextQueueHead    QueueHead */
           0xff,      //      0
           0,         //      1
           0,         //      2
           1,         //      3
           1,         //      4
           2,         //      5
           2,         //      6
           3,         //      7
           3,         //      8
           4,         //      9
           4,         //      10
           5,         //      11
           5,         //      12
           6,         //      13
           6,         //      14
           7,         //      15
           7,         //      16
           8,         //      17
           8,         //      18
           9,         //      19
           9,         //      20
          10,         //      21
          10,         //      22
          11,         //      23
          11,         //      24
          12,         //      25
          12,         //      26
          13,         //      27
          13,         //      28
          14,         //      29
          14,         //      30
          15,         //      31
          15,         //      32
          16,         //      33
          16,         //      34
          17,         //      35
          17,         //      36
          18,         //      37
          18,         //      38
          19,         //      39
          19,         //      40
          20,         //      41
          20,         //      42
          21,         //      43
          21,         //      44
          22,         //      45
          22,         //      46
          23,         //      47
          23,         //      48
          24,         //      49
          24,         //      50
          25,         //      51
          25,         //      52
          26,         //      53
          26,         //      54
          27,         //      55
          27,         //      56
          28,         //      57
          28,         //      58
          29,         //      59
          29,         //      60
          30,         //      61
          30,         //      62
};


UCHAR EHCI_QHeadPeriodTable[64] = {

      1, 2, 2, 4, 4, 4, 4, 8,
      8, 8, 8, 8, 8, 8, 8,16,
     16,16,16,16,16,16,16,16,
     16,16,16,16,16,16,16,32,
     32,32,32,32,32,32,32,32,
     32,32,32,32,32,32,32,32,
     32,32,32,32,32,32,32,32,
     32,32,32,32,32,32,32,0

};


VOID
EHCI_InitializeInterruptSchedule(
     __inout PDEVICE_DATA DeviceData
    )
/*++

Routine Description:

Arguments:

Return Value:

--*/
{
    ULONG i;
    PHCD_QUEUEHEAD_DESCRIPTOR qh = NULL;
    HC_QTD_TOKEN token;

    // First initialize all the 'dummy' queue heads
    //
    for (i=0; i<63; i++) {
        qh = DeviceData->StaticInterruptQH[i];

        SET_T_BIT(qh->HwQH.Overlay.qTD.Next_qTD.HwAddress);

        token = qh->HwQH.Overlay.qTD.Token;
        token.Halted = 1;
        qh->HwQH.Overlay.qTD.Token = token;

        qh->HwQH.EpChars.HeadOfReclimationList = 0;
        qh->Sig = SIG_HCD_IQH;
        EHCI_AssertHwAlignment(DeviceData, qh->PhysicalAddress,
                    sizeof(HW_QUEUEHEAD_DESCRIPTOR));
    }


    {
        // version with no FSTN support

#define INIT_QH(q, nq, f, p) \
        do {\
        QH_DESCRIPTOR_PTR((q)->NextQh) = (nq); \
        QH_DESCRIPTOR_PTR((q)->PrevQh) = NULL; \
        (q)->HwQH.HLink.HwAddress = (nq)->PhysicalAddress; \
        (q)->HwQH.HLink.HwAddress |= EHCI_DTYPE_QH;\
        (q)->HwQH.EpCaps.InterruptScheduleMask =0xff;\
        (q)->QhFlags |= EHCI_QH_FLAG_STATIC;\
        (q)->QhFlags |= f;\
        (q)->Period = p;\
        } WHILE (0)

        // now build the above tree
        for (i=1; i<63; i++) {
            INIT_QH(DeviceData->StaticInterruptQH[i],
                    DeviceData->StaticInterruptQH[EHCI_QHeadLinkTable[i]],
                    i<=6 ? EHCI_QH_FLAG_HIGHSPEED : 0, EHCI_QHeadPeriodTable[i]);
        }
#undef INIT_QH
    }

    // last qh has t bit set

    DeviceData->StaticInterruptQH[0]->HwQH.HLink.HwAddress = 0;
    SET_T_BIT(DeviceData->StaticInterruptQH[0]->HwQH.HLink.HwAddress);
    DeviceData->StaticInterruptQH[0]->HwQH.EpCaps.InterruptScheduleMask =0xff;
    DeviceData->StaticInterruptQH[0]->QhFlags |=
        (EHCI_QH_FLAG_HIGHSPEED | EHCI_QH_FLAG_STATIC);
}


VOID
EHCI_WaitFrames(
     __inout PDEVICE_DATA DeviceData,
     ULONG Frames
    )
{
    PHC_OPERATIONAL_REGISTER hcOp = NULL;
    FRINDEX frameIndex;
    ULONG frameNumber, i, c;
    USBCMD cmd;
    LARGE_INTEGER now, timeout;

    hcOp = DeviceData->OperationalRegisters;

    for (c=0; c< Frames; c++) {
        // bugbug this code does not handle varaible frame list
        // sizes
        frameIndex.ul = READ_REGISTER_ULONG(&hcOp->UsbFrameIndex.ul);

        frameNumber = (ULONG) frameIndex.FrameListCurrentIndex;
        // shift off the microframes
        frameNumber >>= 3;

        i = frameNumber;

        KeQuerySystemTime(&timeout);
        // timeout is 1 sec
        timeout.QuadPart += 10000000;
        do {
            frameIndex.ul = READ_REGISTER_ULONG(&hcOp->UsbFrameIndex.ul);

            frameNumber = (ULONG) frameIndex.FrameListCurrentIndex;
            // shift off the microframes
            frameNumber >>= 3;

            cmd.ul = READ_REGISTER_ULONG(&hcOp->UsbCommand.ul);
            if (cmd.HostControllerRun == 0 ||
                cmd.ul == 0xFFFFFFFF) {
                // if for some reason the HC is moved out of the running state
                // here. This can happen since rebalance is called a passive
                // and this routine is used to rebalance so we break out of the
                // loop here.
                break;
            }

            // if for some other reason the frame counter is not advancing
            // (HC dead) we timeout in one second.

            KeQuerySystemTime(&now);
            if (now.QuadPart > timeout.QuadPart) {
                break;
            }
        } while (frameNumber == i);
    }

}


VOID
EHCI_RebalanceInterruptEndpoint(
    __inout PDEVICE_DATA DeviceData,
    __inout PENDPOINT_PARAMETERS EndpointParameters,
    __inout PENDPOINT_DATA EndpointData
    )
/*++

Routine Description:

    compute how much common buffer we will need
    for this endpoint

Arguments:

Return Value:

--*/
{
    PHCD_QUEUEHEAD_DESCRIPTOR   qh;
    HC_QTD_TOKEN                token;
    ULONG                       qhInSchedule;

    qh = EndpointData->QueueHead;

    // update internal copy of parameters
    EndpointData->Parameters = *EndpointParameters;

    qhInSchedule = TEST_FLAG(qh->QhFlags, EHCI_QH_FLAG_IN_SCHEDULE);

    // period promotion?
    if (qh->Period != EndpointParameters->Period) {
        ULONG i, offset;

        EHCI_KdPrint((DeviceData, 1, "'period change old - %d new %d\n",
            qh->Period, EndpointParameters->Period));

        if (qhInSchedule) {
            EHCI_RemoveQueueHeadFromPeriodicList(DeviceData, EndpointData);
        }

        EHCI_WaitFrames(DeviceData, 2);

        // clear residual data from overlay area
        token = qh->HwQH.Overlay.qTD.Token;
        token.ErrorCounter = 0;
        token.SplitXstate = 0;
        qh->HwQH.Overlay.qTD.Token = token;

        qh->HwQH.Overlay.Ov.OverlayDw8.CprogMask = 0;
        qh->HwQH.Overlay.Ov.OverlayDw9.Sbytes = 0;
        qh->HwQH.Overlay.Ov.OverlayDw9.fTag = 0;


        EHCI_ASSERT(DeviceData,
                    EndpointData->Parameters.DeviceSpeed != HighSpeed);

        // select the proper list
        // the period is a power of 2 ie
        // 32,16,8,4,2,1
        // we just need to find which bit is set
        GET_BIT_SET(EndpointParameters->Period, i);
        EHCI_ASSERT(DeviceData, i < 8);
        EHCI_ASSERT(DeviceData, EndpointParameters->Period < 64);

        offset = EndpointParameters->ScheduleOffset;

        i = ClassicPeriodIdx[i];
        EndpointData->StaticQH =
            DeviceData->StaticInterruptQH[i+offset];

        EndpointData->PeriodTableEntry = NULL;

        qh->Period = EndpointParameters->Period;
        qh->HwQH.EpCaps.InterruptScheduleMask =
                EndpointParameters->InterruptScheduleMask;
        qh->HwQH.EpCaps.SplitCompletionMask =
                EndpointParameters->SplitCompletionMask;

        if (qhInSchedule) {
            EHCI_InsertQueueHeadInPeriodicList(DeviceData, EndpointData);
        }

    } else {

        if (qhInSchedule) {
            EHCI_RemoveQueueHeadFromPeriodicList(DeviceData, EndpointData);
        }

        EHCI_WaitFrames(DeviceData, 2);

        // clear residual data from overlay area
        token = qh->HwQH.Overlay.qTD.Token;
        token.ErrorCounter = 0;
        token.SplitXstate = 0;
        qh->HwQH.Overlay.qTD.Token = token;

        qh->HwQH.Overlay.Ov.OverlayDw8.CprogMask = 0;
        qh->HwQH.Overlay.Ov.OverlayDw9.Sbytes = 0;
        qh->HwQH.Overlay.Ov.OverlayDw9.fTag = 0;

        qh->HwQH.EpCaps.InterruptScheduleMask =
                EndpointParameters->InterruptScheduleMask;
        qh->HwQH.EpCaps.SplitCompletionMask =
                EndpointParameters->SplitCompletionMask;

        if (qhInSchedule) {
            EHCI_InsertQueueHeadInPeriodicList(DeviceData, EndpointData);
        }

    }
}


ULONG
EHCI_CheckHwSync_Periodic(
     __inout PDEVICE_DATA DeviceData,
     __inout PENDPOINT_DATA EndpointData
    )
/*++

Routine Description:

    Called to see if an endpoint is dereferenced by the hardware.

    non-zero(Qh_Not_Busy) return value means endpoint hw transition is complete.

--*/
{

    PHCD_QUEUEHEAD_DESCRIPTOR qh;
    // defaulting to busy (still on HW)
    ULONG hw_done;
    PHC_OPERATIONAL_REGISTER hcOp;
    USBCMD cmd;
    USBSTS sts;
    KIRQL irql;
    BOOLEAN registersUnavailable = FALSE;

    hcOp = DeviceData->OperationalRegisters;
    qh = EndpointData->QueueHead;

    hw_done = EndpointData->HwSyncState;
    LOGENTRY(DeviceData, G, '_kp1', hw_done, EndpointData, qh);

    EHCI_AcquireAsyncDoorbellLock(DeviceData, &irql);
    // periodic endpoints should not be on the flush list
    EHCI_ASSERT(DeviceData, EndpointData->AcfLink.Blink == NULL);
    EHCI_ASSERT(DeviceData, EndpointData->AcfLink.Flink == NULL);
    EHCI_ASSERT(DeviceData, DeviceData->EpAtTheDoor != EndpointData);
    EHCI_ReleaseAsyncDoorbellLock(DeviceData, irql);

    if (hw_done == Qh_Not_Busy) {
        LOGENTRY(DeviceData, G, '_kpx', hw_done, EndpointData, qh);

        return hw_done;
    }

    if (DeviceData->HcSuspendedFlag) {
        registersUnavailable = TRUE;
    } else {
        cmd.ul = READ_REGISTER_ULONG(&hcOp->UsbCommand.ul);
        sts.ul = READ_REGISTER_ULONG(&hcOp->UsbStatus.ul);

        // if the Periodic list if off then report this endpoint as ready.
        if (sts.PeriodicScheduleStatus == 0 &&
            cmd.PeriodicScheduleEnable == 0) {
            registersUnavailable = TRUE;
        }
    }

    if (registersUnavailable) {

        ULONG qhInSchedule;

        qhInSchedule = TEST_FLAG(qh->QhFlags, EHCI_QH_FLAG_IN_SCHEDULE);
        LOGENTRY(DeviceData, G, '_kp2', qhInSchedule, 0, qh);
        switch (EndpointData->CurEpState) {
        case ENDPOINT_REMOVE:
        case ENDPOINT_PAUSE:
           EHCI_ASSERT(DeviceData, !qhInSchedule);
           break;
        case ENDPOINT_ACTIVE:
           EHCI_ASSERT(DeviceData, qhInSchedule);
           break;
        }
        EndpointData->StateChangeTc.QuadPart = 0;
        EndpointData->HwSyncState = hw_done = Qh_Not_Busy;

    } else {
        // indicate state based on elapsed time or I-bit status

        do {
            LARGE_INTEGER   tickNow;
            LARGE_INTEGER   tickDelta;

            if (EndpointData->CurEpState == ENDPOINT_ACTIVE) {
                // transition to active is immediate
                EndpointData->StateChangeTc.QuadPart  = 0;
                EndpointData->HwSyncState = hw_done = Qh_Not_Busy;
                LOGENTRY(DeviceData, G, '_kp3', 0, 0, qh);
                break;
            }

            EHCI_ASSERT(DeviceData, EndpointData->StateChangeTc.QuadPart != 0);

            //
            // Determine how many timer ticks have occurred since the
            // periodic QH state change was initiated.
            //
            KeQueryTickCount(&tickNow);

            tickDelta.QuadPart = tickNow.QuadPart - EndpointData->StateChangeTc.QuadPart;

            LOGENTRY(DeviceData, G, '_KP4', tickDelta.HighPart, tickDelta.LowPart, qh);

            //
            // Don't check the elasped time via timer ticks unless at
            // least 2 timer ticks have occurred.  If only one timer
            // tick has occurred it might have occurred immediately
            // after the call to KeQueryTickCount() in which case only a
            // very small amount of time has actually elasped, not one
            // full timer tick.
            //
            if (tickDelta.QuadPart > 1) {

                LARGE_INTEGER   timerIncrement100ns;
                LARGE_INTEGER   tickDelta100ns;

                // The per-tick timer increment is returned in 100
                // nanosecond units.
                //
                timerIncrement100ns = RtlConvertUlongToLargeInteger(KeQueryTimeIncrement());

                //
                // Convert the elasped time in units of full timer ticks
                // to the elasped time in units of 100 nanoseconds.
                //
                tickDelta100ns.QuadPart = (tickDelta.QuadPart - 1) *
                                          timerIncrement100ns.QuadPart;

                LOGENTRY(DeviceData, G, '_KP5', tickDelta100ns.HighPart, tickDelta100ns.LowPart, qh);

                //
                // If the elasped time is at least 2ms then assume the
                // periodic QH is no longer referenced by the host
                // controller hardware.
                //
                if (tickDelta100ns.QuadPart >= (2 * MILLISECONDS_IN_100NS)) {
                    EndpointData->StateChangeTc.QuadPart = 0;
                    EndpointData->HwSyncState = hw_done = Qh_Not_Busy;
                    break;
                }
            }

        } WHILE (0);
    }

    if (hw_done == Qh_Busy) {

        // Request USBPORT to queue a timer DPC to queue a call to the
        // USBPORT ISR DPC, which will cause USBPORT to process the
        // endpoint state change list again, which will cause
        // EHCI_CheckHwSync() to be called again.
        //
        USBPORT_INVALIDATE_CONTROLLER(DeviceData, UsbMpSimulateInterrupt);
    }

    return hw_done;
}
