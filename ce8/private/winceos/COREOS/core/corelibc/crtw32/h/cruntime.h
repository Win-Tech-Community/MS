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
*cruntime.h - definitions specific to the target operating system and hardware
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This header file contains widely used definitions specific to the
*       host operating system and hardware. It is included by every C source
*       and most every other header file.
*
*       [Internal]
*
*Revision History:
*       02-27-90  GJF   File created
*       03-06-90  GJF   Added register macros (REG1,...,etc.)
*       04-11-90  GJF   Set _CALLTYPE1 and _CALLTYPE4 to _stdcall.
*       10-30-90  GJF   Added macros defining variable args interface.
*       10-31-90  GJF   Added definition of _JBLEN (from setjmp.h).
*       11-13-90  GJF   Revised #ifdef-s, now use symbolic constants
*                       representing target OS and target processor, with
*                       #error directives for unsupported targets. Note the
*                       general grouping of only OS-dependent definitions
*                       followed by OS and processor dependent definitions.
*       02-25-91  SRW   Move _JBLEN definition back to setjmp.h [_WIN32_]
*       04-09-91  PNT   Added _MAC_ definitions
*       05-09-91  GJF   Restored _JBLEN definitions. Also fixed the macros
*                       defining the target processor so both Stevewo's stuff
*                       and mine would work.
*       05-13-91  GJF   Changed _CALLTYPE1 and _CALLTYPE4 to _cdecl for
*                       Cruiser (_CRUISER_).
*       08-28-91  JCR   ANSI keywords
*       11-01-91  GDP   _JBLEN back to setjmp.h, stdarg macros back to stdarg.h
*       03-30-92  DJM   POSIX support.
*       08-07-92  GJF   Revised various macros.
*       09-08-92  GJF   Restored definition of _MIPS_ (temporarily).
*       11-09-92  GJF   Revised preprocessing conditionals for MIPS.
*       01-09-93  SRW   Remove usage of MIPS and ALPHA to conform to ANSI
*                       Use _MIPS_ and _ALPHA_ instead.
*       02-01-93  GJF   Removed support for C6-386.
*       04-06-93  SKS   Remove support for OS/2, MAC, POSIX, MIPS, etc.
*       11-11-93  GJF   Merged in NT SDK version. Note that having
*                       definitions for the variable-argument access macros
*                       in this file is probably obsolete - this needs to be
*                       checked.
*       10-02-94  BWT   Add PPC support.
*       10-09-94  BWT   Unknown platform changes from John Morgan.
*       12-15-94  XY    merged with mac header
*       02-14-95  CFW   Clean up Mac merge.
*       03-29-95  CFW   Add error message to internal headers.
*       12-14-95  JWM   Add "#pragma once".
*       02-24-97  GJF   Detab-ed.
*       05-17-99  PML   Remove all Macintosh support.
*       11-03-99  PML   Remove _VA_LIST_T
*       03-18-01  PML   Define _USE_OLD_STDCPP when compiling with stdcpp64
*                       and stdhpp64, for the Win64 system CRTs.
*       07-15-01  PML   Remove all ALPHA, MIPS, and PPC code
*
****/

#pragma once

#ifndef _CRTBLD
/*
 * This is an internal C runtime header file. It is used when building
 * the C runtimes only. It is not to be used as a public header file.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

#if     defined(_SYSCRT) && defined(_WIN64)
#define _USE_OLD_STDCPP 1
#endif

//BUGBUG if there is no build break then remove below line
/*
 * Numeric error helpers
 */
//void __helper_divide_by_0();

#if     defined(_M_X64) || defined(_M_ARM)
#define _UNALIGNED __unaligned
#elif   defined(_M_IX86)
#define _UNALIGNED
#else
#error Unknown target architecture.
#endif

/*
 * Are the macro definitions below still needed in this file?
 */
#if     defined(_POSIX_)

#define _INTSIZEOF(n)    ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define _VA_START(ap,v) ap = (va_list)&v + _INTSIZEOF(v)
#define _VA_ARG(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define _VA_END(ap) ap = (va_list)0

#endif
