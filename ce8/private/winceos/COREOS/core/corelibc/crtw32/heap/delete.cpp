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
*delete.cpp - defines C++ scalar delete routine, non-debug version
*
*       Copyright (c) Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Defines C++ delete routine.
*
*Revision History:
*       05-07-90  WAJ   Initial version.
*       08-30-90  WAJ   new now takes unsigned ints.
*       08-08-91  JCR   call _halloc/_hfree, not halloc/hfree
*       08-13-91  KRS   Change new.hxx to new.h.  Fix copyright.
*       08-13-91  JCR   ANSI-compatible _set_new_handler names
*       10-30-91  JCR   Split new, delete, and handler into seperate sources
*       11-13-91  JCR   32-bit version
*       11-13-95  CFW   Not in debug libs.
*       05-22-98  JWM   Support for KFrei's RTC work, and operator delete[].
*       07-28-98  JWM   RTC update.
*       03-15-99  KBF   RTC update (RTCALLBACK requires some windows defs)
*       05-26-99  KBF   Updated RTC hook func params
*       10-21-99  PML   Split delete[] out to fix mult defs (vs7#53440)
*       11-04-04  JL    Make operator new and delete as a part of pure CRT
*       11-09-04  AC    Add the right operator delete in debug
*                       VSW#406964
*
*******************************************************************************/

#ifndef _DEBUG

#include <cruntime.h>
#include <malloc.h>
#include <new.h>
#include <windows.h>
#include <rtcsup.h>

void operator delete( void * p )
{
    RTCCALLBACK(_RTC_Free_hook, (p, 0));

    free( p );
}

#endif /* _DEBUG */
