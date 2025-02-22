
        title  "Stall Execution Support"
;++
;
; Copyright (c) 1989-2001  Microsoft Corporation
;
; Module Name:
;
;    ixstall.asm
;
; Abstract:
;
;    This module implements the code necessary to field and process the
;    interval clock interrupt.
;
; Environment:
;
;    Kernel mode only.
;
;--

.386p
        .xlist
include hal386.inc
include callconv.inc                    ; calling convention macros
include i386\ix8259.inc
include i386\kimacro.inc
include i386\ixcmos.inc
        .list

        EXTRNP  _DbgBreakPoint,0
        EXTRNP  _HalpAcquireCmosSpinLock  ,0
        EXTRNP  _HalpReleaseCmosSpinLock  ,0

;
; Constants used to initialize CMOS/Real Time Clock
;

D_INT032                EQU     8E00h   ; access word for 386 ring 0 interrupt gate

;
; RegisterAInitByte sets 8Hz clock rate, used during init to set up
; KeStallExecutionProcessor, etc.  (See RegASystemClockByte below.)
;

RegisterAInitByte       EQU     00101101B ; RT/CMOS Register 'A' init byte
                                        ; 32.768KHz Base divider rate
                                        ;  8Hz int rate, period = 125.0ms
PeriodInMicroSecond     EQU     125000  ;

STICKY  SEGMENT  DWORD PUBLIC 'DATA'

;
; Initialize the stall scale factor to the number required for the 733Mhz
; processor in the console.  This number can be calculated by running the
; HalpInitializeStallExecution routine from xxhal.c.
;

        public  _HalpStallScaleFactor
_HalpStallScaleFactor   dd      016Fh

STICKY  ends

INIT    SEGMENT PARA PUBLIC 'CODE'
        ASSUME  DS:FLAT, ES:FLAT, SS:NOTHING, FS:NOTHING, GS:NOTHING

        page ,132
        subttl  "Initialize Real Time Clock"
;++
;
; VOID
; HalpInitializeRealTimeClock(
;    VOID
;    )
;
; Routine Description:
;
;    This function initializes the real time clock to a known state.
;
; Arguments:
;
;    None.
;
; Return Value:
;
;    None.
;
;--

cPublicProc _HalpInitializeRealTimeClock, 0

        stdCall   _HalpAcquireCmosSpinLock      ; intr disabled

        mov     ax,(RegisterAInitByte SHL 8) OR 0AH ; Register A
        CMOS_WRITE                      ; Initialize it
;
; Don't clobber the Daylight Savings Time bit in register B, because we
; stash the LastKnownGood "environment variable" there.
;
        mov     ax, 0bh
        CMOS_READ
        and     al, 1
        mov     ah, al
        or      ah, REGISTER_B_DISABLE_PERIODIC_INTERRUPT
        mov     al, 0bh
        CMOS_WRITE                      ; Initialize it
        mov     al,0CH                  ; Register C
        CMOS_READ                       ; Read to initialize
        mov     al,0DH                  ; Register D
        CMOS_READ                       ; Read to initialize

        stdCall   _HalpReleaseCmosSpinLock

        stdRET    _HalpInitializeRealTimeClock

stdENDP _HalpInitializeRealTimeClock

INIT    ends

IFDEF NOT_NEEDED

INIT    SEGMENT PARA PUBLIC 'CODE'
        ASSUME  DS:FLAT, ES:FLAT, SS:NOTHING, FS:NOTHING, GS:NOTHING

        page ,132
        subttl  "Initialize Stall Execution Counter"
;++
;
; VOID
; HalpInitializeStallExecution (
;    VOID
;    )
;
; Routine Description:
;
;    This routine initialize the per Microsecond counter for
;    KeStallExecutionProcessor
;
; Arguments:
;
;    None.
;
; Return Value:
;
;    None.
;
; Note:
;
;    Current implementation assumes that all the processors share
;    the same Real Time Clock.  So, the dispatcher database lock is
;    acquired before entering this routine to guarantee only one
;    processor can access the routine.
;
;--

KiseInterruptCount      equ     [ebp-12] ; local variable

cPublicProc _HalpInitializeStallExecution     ,0

        push    ebp                     ; save ebp
        mov     ebp, esp                ; set up 12 bytes for local use
        sub     esp, 12

        pushfd                          ; save caller's eflag

;
; Initialize Real Time Clock to interrupt us for every 125ms at
; IRQ 8.
;

        cli                             ; make sure interrupts are disabled

;
; Get and save current 8259 masks
;

        xor     eax,eax

;
; Assume there is no third and fourth PICs
;
; Get interrupt Mask on PIC2
;

        in      al,PIC2_PORT1
        shl     eax, 8

;
; Get interrupt Mask on PIC1
;

        in      al,PIC1_PORT1
        push    eax                     ; save the masks
        mov     eax, NOT (( 1 SHL PIC_SLAVE_IRQ) + (1 SHL RTCIRQ))
                                        ; Mask all the irqs except irq 2 and 8
        SET_8259_MASK                   ; Set 8259's int mask register

;
; Since RTC interrupt will come from IRQ 8, we need to
; Save original irq 8 descriptor and set the descriptor to point to
; our own handler.
;

        sidt    fword ptr [ebp-8]       ; get IDT address
        mov     ecx, [ebp-6]            ; (ecx)->IDT

        mov     eax, (RTCIRQ+PRIMARY_VECTOR_BASE)

        shl     eax, 3                  ; 8 bytes per IDT entry
        add     ecx, eax                ; now at the correct IDT RTC entry

        push    dword ptr [ecx]         ; (TOS) = original desc of IRQ 8
        push    dword ptr [ecx + 4]     ; each descriptor has 8 bytes

        ;
        ; Pushing the appropriate entry address now (instead of
        ; the IDT start address later) to make the pop at the end simpler.
        ;
        push    ecx                     ; (TOS) -> &IDT[HalProfileVector]

        mov     eax, offset FLAT:RealTimeClockHandler

        mov     word ptr [ecx], ax              ; Lower half of handler addr
        mov     word ptr [ecx+2], KGDT_R0_CODE  ; set up selector
        mov     word ptr [ecx+4], D_INT032      ; 386 interrupt gate

        shr     eax, 16                 ; (ax)=higher half of handler addr
        mov     word ptr [ecx+6], ax

        mov     dword ptr KiseinterruptCount, 0 ; set no interrupt yet

        stdCall   _HalpAcquireCmosSpinLock      ; intr disabled

        mov     ax,(RegisterAInitByte SHL 8) OR 0AH ; Register A
        CMOS_WRITE                      ; Initialize it
;
; Don't clobber the Daylight Savings Time bit in register B, because we
; stash the LastKnownGood "environment variable" there.
;
        mov     ax, 0bh
        CMOS_READ
        and     al, 1
        mov     ah, al
        or      ah, REGISTER_B_ENABLE_PERIODIC_INTERRUPT
        mov     al, 0bh
        CMOS_WRITE                      ; Initialize it
        mov     al,0CH                  ; Register C
        CMOS_READ                       ; Read to initialize
        mov     al,0DH                  ; Register D
        CMOS_READ                       ; Read to initialize
        mov     dword ptr [KiseInterruptCount], 0

        stdCall   _HalpReleaseCmosSpinLock

;
; Now enable the interrupt and start the counter
; (As a matter of fact, only IRQ8 can come through.)
;
        xor     eax, eax                ; (eax) = 0, initialize loopcount
ALIGN 16
        sti
        jmp     kise10

ALIGN 16
kise10:
        sub     eax, 1                  ; increment the loopcount
        jnz     short kise10

if DBG
;
; Counter overflowed
;

        stdCall   _DbgBreakPoint
endif
        jmp     short kise10

;
; Our RealTimeClock interrupt handler.  The control comes here through
; irq 8.
; Note: we discard first real time clock interrupt and compute the
;       permicrosecond loopcount on receiving of the second real time
;       interrupt.  This is because the first interrupt is generated
;       based on the previous real time tick interval.
;

RealTimeClockHandler:

        inc     dword ptr KiseInterruptCount ; increment interrupt count
        cmp     dword ptr KiseInterruptCount,1 ; Is this the first interrupt?
        jnz     short kise25            ; no, its the second go process it
        pop     eax                     ; get rid of original ret addr
        push    offset FLAT:kise10      ; set new return addr


        stdCall   _HalpAcquireCmosSpinLock      ; intr disabled

        mov     ax,(RegisterAInitByte SHL 8) OR 0AH ; Register A
        CMOS_WRITE                      ; Initialize it
;
; Don't clobber the Daylight Savings Time bit in register B, because we
; stash the LastKnownGood "environment variable" there.
;
        mov     ax, 0bh
        CMOS_READ
        and     al, 1
        mov     ah, al
        or      ah, REGISTER_B_ENABLE_PERIODIC_INTERRUPT
        mov     al, 0bh
        CMOS_WRITE                      ; Initialize it
        mov     al,0CH                  ; Register C
        CMOS_READ                       ; Read to initialize
        mov     al,0DH                  ; Register D
        CMOS_READ                       ; Read to initialize

        stdCall   _HalpReleaseCmosSpinLock
;
; Dismiss the interrupt.
;
        mov     al, OCW2_NON_SPECIFIC_EOI ; send non specific eoi to slave
        out     PIC2_PORT0, al
        mov     al, PIC2_EOI            ; specific eoi to master for pic2 eoi
        out     PIC1_PORT0, al          ; send irq2 specific eoi to master

        xor     eax, eax                ; reset loop counter

        iretd

kise25:

;
; ** temporary - check for incorrect KeStallExecutionProcessorLoopCount
;

if DBG
        cmp     eax, 0
        jnz     short kise30
        stdCall   _DbgBreakPoint

endif
                                         ; never return
;
; ** End temporay code
;

kise30:
        neg     eax
        xor     edx, edx                ; (edx:eax) = divident
        mov     ecx, PeriodInMicroSecond; (ecx) = time spent in the loop
        div     ecx                     ; (eax) = loop count per microsecond
        cmp     edx, 0                  ; Is remainder =0?
        jz      short kise40            ; yes, go kise40
        inc     eax                     ; increment loopcount by 1
kise40:
        mov     _HalpStallScaleFactor, eax

;
; Reset return address to kexit
;

        pop     eax                     ; discard original return address
        push    offset FLAT:kexit       ; return to kexit
        mov     eax, (HIGHEST_LEVEL_FOR_8259 - RTCIRQ)

;
; Shutdown periodic interrupt
;
        stdCall   _HalpAcquireCmosSpinLock
        mov     ax,(RegisterAInitByte SHL 8) OR 0AH ; Register A
        CMOS_WRITE                      ; Initialize it
        mov     ax, 0bh
        CMOS_READ
        and     al, 1
        mov     ah, al
        or      ah, REGISTER_B_DISABLE_PERIODIC_INTERRUPT
        mov     al, 0bh
        CMOS_WRITE                      ; Initialize it
        mov     al,0CH                  ; Register C
        CMOS_READ                       ; dismiss pending interrupt
        stdCall   _HalpReleaseCmosSpinLock

;
; Dismiss the interrupt.
;
        mov     eax, RTCIRQ
        mov     al, OCW2_NON_SPECIFIC_EOI ; send non specific eoi to slave
        out     PIC2_PORT0, al
        mov     al, PIC2_EOI            ; specific eoi to master for pic2 eoi
        out     PIC1_PORT0, al          ; send irq2 specific eoi to master

        and     word ptr [esp+8], NOT 0200H ; Disable interrupt upon return
        iretd

kexit:                                  ; Interrupts are disabled
        pop     ecx                     ; (ecx) -> &IDT[HalProfileVector]
        pop     [ecx+4]                 ; restore higher half of RTC desc
        pop     [ecx]                   ; restore lower half of RTC desc

        pop     eax                     ; (eax) = origianl 8259 int masks
        SET_8259_MASK

        popfd                           ; restore caller's eflags
        mov     esp, ebp
        pop     ebp                     ; restore ebp
        stdRET    _HalpInitializeStallExecution

stdENDP _HalpInitializeStallExecution

INIT   ends

ENDIF

_TEXT   SEGMENT PARA PUBLIC 'CODE'
        ASSUME  DS:FLAT, ES:FLAT, SS:NOTHING, FS:NOTHING, GS:NOTHING

        page ,132
        subttl  "Stall Execution"
;++
;
; VOID
; KeStallExecutionProcessor (
;    IN ULONG MicroSeconds
;    )
;
; Routine Description:
;
;    This function stalls execution for the specified number of microseconds.
;    KeStallExecutionProcessor
;
; Arguments:
;
;    MicroSeconds - Supplies the number of microseconds that execution is to be
;        stalled.
;
; Return Value:
;
;    None.
;
;--

MicroSeconds equ [esp + 4]

cPublicProc _KeStallExecutionProcessor       ,1
cPublicFpo 1, 0

;
; Issue a CPUID to implement a "fence"
;
        push    ebx                             ; cpuid uses eax, ebx, ecx, edx
        xor     eax, eax                        ; Processor zero
    .586p
        cpuid
    .386p
        pop     ebx

        mov     ecx, MicroSeconds               ; (ecx) = Microseconds
        jecxz   short kese10                    ; return if no loop needed

        mov     eax, _HalpStallScaleFactor      ; get per microsecond
                                                ; loop count for the processor
        mul     ecx                             ; (eax) = desired loop count

if   DBG
;
; Make sure we the loopcount is less than 4G and is not equal to zero
;

        cmp     edx, 0
        jz      short @f
        int 3

@@:     cmp     eax,0
        jnz     short @f
        int 3
@@:
endif
ALIGN 16
        jmp     kese05

ALIGN 16
kese05: sub     eax, 1                          ; (eax) = (eax) - 1
        jnz     short kese05
kese10:
        stdRET    _KeStallExecutionProcessor

stdENDP _KeStallExecutionProcessor

_TEXT   ends

        end
