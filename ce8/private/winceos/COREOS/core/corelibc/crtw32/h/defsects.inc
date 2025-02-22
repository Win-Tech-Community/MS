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
;***
;defsects.inc - defines sections.
;
;   Copyright (c) Microsoft Corporation.  All rights reserved.
;
;Purpose:
;   This file defines sections for the C and C++ libs.
;
;   NOTE:  As needed, special "CRT" sections can be added into the existing
;   init/term tables.  These will be for our use only -- users who put
;   stuff in here do so at their own risk.
;
;Revision History:
;   03-19-92  SKS   Loosely based on the 16-bit include file DEFSEGS.INC
;   08-06-92  SKS   Changed these section names from X[ICPT]$[ACLUXZ] to
;		    .CRT$X[ICPT][ACLUXZ] to avoid creating too many sections
;		    Also, sections are no longer defined in groups.  That was
;		    for use with OMF type objects where order of appearance
;		    is important.  With COFF, sorting is done by section name.
;
;******************************************************************************

;*******
;*
;* beginSection - a macro for declaring and beginning a section
;*
;* endSection - a macro for ending a previously declared section
;*
;*******

beginSection	MACRO	SectName
.CRT$&SectName	SEGMENT DWORD PUBLIC 'DATA'
		ENDM

endSection	MACRO	SectName
.CRT$&SectName	ENDS
		ENDM

;  XIA	Begin C Initializer Sections
;  XIC	 Microsoft Reserved
;  XIU	 User
;  XIZ	End C Initializer Sections
;
;  XCA	Begin C++ Constructor Sections
;  XCC	 Compiler (MS)
;  XCL	 Library
;  XCU	 User
;  XCZ	End C++ Constructor Sections
;
;  XPA	Begin C Pre-Terminator Sections
;  XPU	 User
;  XPX	 Microsoft Reserved
;  XPZ	End C Pre-Terminator Sections
;
;  XTA	Begin C Pre-Terminator Sections
;  XTU	 User
;  XTX	 Microsoft Reserved
;  XTZ	End C Pre-Terminator Sections
