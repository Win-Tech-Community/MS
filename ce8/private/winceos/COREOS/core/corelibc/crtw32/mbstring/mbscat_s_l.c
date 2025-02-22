//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft shared
// source or premium shared source license agreement under which you licensed
// this source code. If you did not accept the terms of the license agreement,
// you are not authorized to use this source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the SOURCE.RTF on your install media or the root of your tools installation.
// THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
/***
*mbscat_s_l.c - Concatenate one string to another (MBCS)
*
*       Copyright (c) Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Concatenate one string to another (MBCS)
*
*Revision History:
*       08-12-04  AC    Module created.
*
*******************************************************************************/

#ifdef  _MBCS

#include <mbstring.h>
#include <internal_securecrt.h>
#include <mtdll.h>
#include <setlocal.h>

#define _FUNC_PROLOGUE
#define _FUNC_NAME _mbscat_s_l
#define _SB_FUNC_NAME strcat_s
#define _DEST _Dst
#define _SRC _Src

#include <mbscat_s.inl>

#endif  /* _MBCS */
