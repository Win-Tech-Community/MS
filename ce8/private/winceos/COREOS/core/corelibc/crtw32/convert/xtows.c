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
*xtows.c - Secure Version of xtow.c
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This module is split from xtow to avoid xtow.obj pulling in startup code
*
*Revision History:
*       10-13-03  SJ   Module created, split from xtow.c
*
*******************************************************************************/

#define _SECURE_ITOA
#define _UNICODE
#include "xtoa.c"
