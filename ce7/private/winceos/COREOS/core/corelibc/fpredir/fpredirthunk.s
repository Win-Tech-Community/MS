;
; Copyright (c) Microsoft Corporation.  All rights reserved.
;
;
; Use of this source code is subject to the terms of the Microsoft shared
; source or premium shared source license agreement under which you licensed
; this source code. If you did not accept the terms of the license agreement,
; you are not authorized to use this source code. For the terms of the license,
; please see the license agreement between you and Microsoft or, if applicable,
; see the SOURCE.RTF on your install media or the root of your tools installation.
; THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
;

        OPT     2       ; disable listing
        INCLUDE kxarm.h
        OPT     1       ; reenable listing
    
        IMPORT      _FixupFPCrtRedirection
    
        TEXTAREA
    
;******************************************************************************
            
    NESTED_ENTRY _FixupFPCrtThunk
    
        stmdb sp!, {r0 - r3, r12, lr}
    
    PROLOG_END
    
        ; call the FPCRT fixup function
        ;
        bl _FixupFPCrtRedirection
        
        ; restore saved registers and
        ; call the real implementation
        ;
        ldmia sp!, {r0 - r3, r12, lr}
        
        ldr pc, [r12]
        
    ENTRY_END
        
        
        END
    

