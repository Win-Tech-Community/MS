/*++

Copyright (c) 1991  Microsoft Corporation

Module Name:

    pcr.c

Abstract:

    This module provides access to the pcr and a bang command to dump the pcr.

Author:

    Wesley Witt (wesw)  26-Aug-1993  (ported to WinDbg)

Revision History:


--*/

#include "precomp.h"
#pragma hdrstop



/*++

Routine Description:

    Print out the current values in interesting fields of the PCR
    for the specified processor.

Arguments:

    args - provides pointer to argument string, expect to be empty
            or to contain a positive decimal integer specifing which
            processor's pcr to dump

--*/

DECLARE_API( pcr )

{
    KPCR  Pcr;
    ULONG Address;
    PKPCR pp;
    USHORT processor;
    PROCESSORINFO pi;
    ULONG Result;
    KDPC  Dpc;

    //
    // Apply to whichever processor user asks for
    //

    if (strlen(args)) {
        processor = (USHORT)strtoul(args, NULL, 16);
        }
    else {
        processor = (USHORT)dwProcessor;
        }
    pp = &Pcr;
    if (!ReadPcr(processor, pp, &Address, hCurrentThread)) {
        dprintf("Unable to read PCR for Processor %u\n", processor);
        return;
    }

    //
    // Print out the PCR up through PrcbData, let dumpprcb print that.
    //

    dprintf("PCR Processor %ld @%08lx\n", processor, Address);
    dprintf("\tNtTib.ExceptionList: %08lx\n", pp->NtTib.ExceptionList);
    dprintf("\t    NtTib.StackBase: %08lx\n", pp->NtTib.StackBase);
    dprintf("\t   NtTib.StackLimit: %08lx\n", pp->NtTib.StackLimit);
    dprintf("\t NtTib.SubSystemTib: %08lx\n", pp->NtTib.SubSystemTib);
    dprintf("\t      NtTib.Version: %08lx\n", pp->NtTib.Version);
    dprintf("\t  NtTib.UserPointer: %08lx\n", pp->NtTib.ArbitraryUserPointer);
    dprintf("\t      NtTib.SelfTib: %08lx\n", pp->NtTib.Self);
    dprintf("\n");
    dprintf("\t            SelfPcr: %08lx\n", pp->SelfPcr);
    dprintf("\t               Prcb: %08lx\n", pp->Prcb);
    dprintf("\t               Irql: %08lx\n", (ULONG)pp->Irql);
    dprintf("\n");
    dprintf("\t      CurrentThread: %08lx\n", pp->PrcbData.CurrentThread);
    dprintf("\t         NextThread: %08lx\n", pp->PrcbData.NextThread);
    dprintf("\t         IdleThread: %08lx\n", pp->PrcbData.IdleThread);

    GetKdContext( &pi );

    dprintf("\n");

    dprintf( "\t          DpcQueue: ");

    Dpc.DpcListEntry.Flink = pp->PrcbData.DpcListHead.Flink;
    while ((DWORD)(Dpc.DpcListEntry.Flink) != (DWORD)pp->Prcb + FIELD_OFFSET( KPRCB, DpcListHead )) {

        UCHAR Name[0x100];
        ULONG_PTR Displacement;

        Name[0] = 0;
        dprintf(" 0x%x ", (ULONG)(Dpc.DpcListEntry.Flink) - 4 );

        if (!ReadMemory( (ULONG)(Dpc.DpcListEntry.Flink) - 4, &Dpc, sizeof( KDPC ), &Result )) {
            dprintf( "Failed to read DPC at 0x%x\n", (ULONG)(Dpc.DpcListEntry.Flink) - 4 );
            break;
        }

        GetSymbol( Dpc.DeferredRoutine, Name, &Displacement );
        dprintf("0x%x %s\n\t                    ", Dpc.DeferredRoutine, Name );

        if (CheckControlC()) {
            break;
        }
    
    }

    dprintf("\n");

}


BOOL
ReadPcr(
    USHORT  Processor,
    PVOID   Pcr,
    PULONG  AddressOfPcr,
    HANDLE  hThread
    )
{
    DESCRIPTOR_TABLE_ENTRY Entry;
    ULONG Result;
    ULONG Address;


    Entry.Selector=KGDT_R0_PCR;

    Result = LookupSelector( Processor, &Entry );
    if (Result != STATUS_SUCCESS) {
        return FALSE;
    }

    Address =
        ((ULONG)Entry.Descriptor.BaseLow & 0xffff) |
        (((ULONG)Entry.Descriptor.HighWord.Bytes.BaseMid << 16) & 0xff0000) |
        (((ULONG)Entry.Descriptor.HighWord.Bytes.BaseHi << 24) & 0xff000000);

    //
    // Address -> base of the pcr, read the PCR in.
    //

    if (!ReadMemory((DWORD)Address, Pcr, sizeof(KPCR), &Result)) {
        return FALSE;
    }

    *AddressOfPcr = Address;
    return TRUE;
}
