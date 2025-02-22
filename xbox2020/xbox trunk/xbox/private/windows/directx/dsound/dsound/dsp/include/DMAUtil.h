;*******************************************************************
;
;    DMAUtil.h		DMA header file for Global/Encode Audio Processor   
;
;******************************************************************        

; ==============================================================
;  DMA Engine stuff
; ==============================================================

kDMANode_MaxSize	equ		7	
kDMANode_Size		equ		6	
kDMANode_Size_FIFO	equ		4
kDMANode_Size_DSPnSM	equ		6
kDMANode_EOL		equ		$004000		; Bit 14 = Eol
kDMANode_EOLBit		equ		kDMANode_EOL
kDMANode_EOLMask	equ		$003fff		; Will Clear Eol bit

DMA_CONTROL_REGISTER 		equ $FFFFD6	; Address of DMA control register
kDMA_ActionRequest_None	    	equ 0	; Useless		 
kDMA_ActionRequest_Start    	equ 1		 
kDMA_ActionRequest_Stop    		equ 2		 
kDMA_ActionRequest_Freeze    	equ 3		 
kDMA_ActionRequest_UnFreeze   	equ 4		 
kDMA_ActionRequest_Abort		equ 5
	 
kDMA_FrozenBit		equ		3	
kDMA_RunningBit		equ		4
kDMA_StoppedBit		equ		5

DMA_CONFIGURATION_REGISTER	equ $FFFFD7	; Address of DMA configuration register
kDMA_AutoStartBit		equ		0			; Bit 0
kDMA_AutoRdyBit			equ		1
kDMA_IocRequireClrBit	equ		2
kDMA_EolRequireClrBit	equ		3
kDMA_ErrRequireClrBit	equ		4

kDMASampleFormat_08bits		equ		0
kDMASampleFormat_16bits		equ		1
kDMASampleFormat_24msbits	equ		2
kDMASampleFormat_32bits		equ		3
kDMASampleFormat_24lsbits	equ		6

; Command Node structure for DSP<->System Memory transfers
kDMAWord0_NextCmd	equ	0
kDMAWord1_ControlBits	equ	1
kDMAWord2_Count		equ	2
kDMAWord3_DSPAddress	equ	3
kDMAWord4_SMOffset	equ	4
kDMAWord5_SMBaseOffset	equ	5
kDMAWord6_SMLength	equ	6

DMA_NEXT_BLOCK_CONTROL_REGISTER		equ $FFFFD4 ; Bit 14 eol, Bits 13:0  Head of List Address
												; Alter only in Idle State or frozen bit asserted
DMA_START_BLOCK_CONTROL_REGISTER	equ $FFFFD5	; Bit 14 e0l, Bits 13:0  Head of List Address

; *********** DMA Read/Write Words **************
; 
; dspBaseAddress = $000000 (0)
; blockSize      = $000000 (0)

; ---- Word 0
; eol         = $1 (1) 
; nextCmd     = $000000 (0)

; ---- Word 1
; interleave  = $0 ( 0) (bit    :0)
; rdDspMem    = $0 ( 0) (bit    :1)(DSP Memory <- System Memory)
; IOC         = $0 ( 0) (bit   3:2)
; smPtrWrBk   = $0 ( 0) (bit     4)
; smBufID     = $F (15) (bit   8:5)
; iso         = $0 ( 0) (bit     9)
; smDataFmt   = $6 ( 6) (bit 12:10)
; >>>>> CONTROLBITS = $19E0
; incr        = $1 ( 1) 

; ---- Word 2
; Count1      = $0000 (0)
; Count0      = $0000 (0)

; ---- Word 3
; Nul         = $0 (0)
; PDspStart   = $000000 (0)

; ---- Word 4
; smOffset      = $000000 (0)

; ---- Word 5 (Used in circular buffers)
; smBaseAddress = $000000 (0)

; ---- Word 6 (Used in circular buffers)
; smSizeMinus1  = $000000 (0)

; >>>>>> Only need Words 0..4
;
;  Generated by dmawords.exe

DMA_BASE_READ0	equ	$004000
DMA_BASE_READ1	equ	$0059E0
DMA_BASE_READ1_ISO	equ	$005BE0
DMA_BASE_READ2	equ	$000000
DMA_BASE_READ3	equ	$000000
DMA_BASE_READ4	equ	$000000
DMA_BASE_READ5	equ	$000000

DMA_BASE_WRITE0	equ	DMA_BASE_READ0
DMA_BASE_WRITE1	equ	$0059E2
DMA_BASE_WRITE1_ISO	equ	$005BE2
DMA_BASE_WRITE2	equ	DMA_BASE_READ2
DMA_BASE_WRITE3	equ	DMA_BASE_READ3
DMA_BASE_WRITE4	equ	DMA_BASE_READ4
DMA_BASE_WRITE5	equ	DMA_BASE_READ5

DMA_MULTIPASS_WRITE1 equ $0049E2
 
DMA_NODE_EOL0	equ	$004000
DMA_NODE_EOL1	equ	$000000
DMA_NODE_EOL2	equ	$000000
DMA_NODE_EOL3	equ	$000000
DMA_NODE_EOL4	equ	$000000
DMA_NODE_EOL5	equ	$000000

;
; Control words for ISO circular buffer dma
;

DMA_CIRCULAR_WRITE1_ISO equ $004bD2
DMA_CIRCULAR_READ1_ISO  equ $004bD0


; *********** DMA FIFO Words **************
; ---- Setup to use Output FIFO0
; DMA Word 1  
; interleave  = $1 (Bits    :0)
; rdDspMem    = $1 (Bits    :1)(DSP Memory -> System Memory)
; IOC         = $0 (Bits   3:2)
; smPtrWrBk   = $0 (Bits     4)
; smBufID     = $0 (Bits   8:5)
; iso         = $0 (Bits     9)
; smDataFmt   = $1 (Bits 12:10)()
; incr        = $1 ( 1) (Bits 23:14)

kDMA_FIFOOut0_Word1 equ $080403  ; 0000 1000 0000 0100 0000 0011

; Count0 = 1 channels/block
; Count1 = 32 transfer length

kDMA_FIFOOut0_Word2 equ $000201  ; 

; ---- Setup to use Output FIFO1
; DMA Word 1  
; interleave  = $1 (Bits    :0)
; rdDspMem    = $1 (Bits    :1)(DSP Memory -> System Memory)
; IOC         = $0 (Bits   3:2)
; smPtrWrBk   = $0 (Bits     4)
; smBufID     = $01 (Bits   8:5)(use FIFO 1)
; iso         = $0 (Bits     9)
; smDataFmt   = $1 (Bits 12:10)()
; incr        = $1 ( 1) (Bits 23:14)

kDMA_FIFOOut1_Word1 equ $080423  ; 0000 1000 0000 0100 0010 0011

; Count0 = 1 channels/block
; Count1 = 32 transfer length

kDMA_FIFOOut1_Word2 equ $000201  ; 


kDMA_FIFO_Channels1			equ	$0
kDMA_FIFO_Channels2			equ	$1
kDMA_FIFO_Channels4			equ	$2
kDMA_FIFO_Channels6			equ	$3

kDMA_FIFO_SampleFormat08	equ	$0
kDMA_FIFO_SampleFormat16	equ	$1
kDMA_FIFO_SampleFormat24	equ	$2
kDMA_FIFO_SampleFormat32	equ	$3

; Output FIFO #0  DMA words:  
; 32 stereo samples in 16-bit format. 


; ---- Setup to use Input FIFO
; DMA Word 1  
; interleave  = $0 ( 0) (Bits    :0)
; rdDspMem    = $0 ( 0) (Bits    :1)(DSP Memory <- System Memory)
; IOC         = $0 ( 0) (Bits   3:2)
; smPtrWrBk   = $0 ( 0) (Bits     4)
; smBufID     = $0 ( 0) (Bits   8:5)
; iso         = $0 ( 0) (Bits     9)
; smDataFmt   = $2 ( 2) (Bits 12:10)()
; >>>>> CONTROLBITS = $0800 = binary 0 1000 0000 0000
; incr        = $1 ( 1) (Bits 23:14)

kDMA_InFIFO_Word1   equ $4800
kDMA_InFIFO0_Word1	equ	(kDMA_InFIFO_Word1|$00) ; 0000 0000
kDMA_InFIFO1_Word1	equ	(kDMA_InFIFO_Word1|$20) ; 0010 0000


;************************************************************
; ClearDMAConfigRegister	Clear  register
;************************************************************
ClearDMAConfigRegister macro
      	movep    #>0,x:DMA_CONFIGURATION_REGISTER	
	endm
; ---- end ClearDMAConfigRegister ----



NewDMABlockSimple macro

    dc  0
    dc  0
    dc  0
    dc  0
    dc  0

    endm

NewDMABlock macro

    dc  0
    dc  0
    dc  0
    dc  0
    dc  0
    dc  0
    dc  0

    endm


