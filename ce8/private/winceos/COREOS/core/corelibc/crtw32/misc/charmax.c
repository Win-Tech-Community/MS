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
*charmax.c - definition of _charmax variable
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _charmax
*
*       According to ANSI, certain elements of the lconv structure must be
*       initialized to CHAR_MAX and the value of CHAR_MAX changes when
*       the user compiles -J.  To reflect this change in the lconv structure,
*       we initialize the structure to SCHAR_MAX, and when any of the users
*       modules are compiled -J, the structure is updated.
*
*       Note that this is not done for DLLs linked to the CRT DLL, because
*       we do not want such DLLs to override the -J setting for an EXE
*       linked to the CRT DLL.  See comments in crtexe.c.
*
*       Files involved:
*
*       locale.h - if -J, generates an unresolved external to _charmax
*       charmax.c - defines _charmax and sets to UCHAR_MAX (255), places
*               _lconv_init in startup initializer table if pulled in by -J
*       lconv.c - initializes lconv structure to SCHAR_MAX (127),
*               since libraries built without -J
*       lcnvinit.c - sets lconv members to 25.
**
*Revision History:
*       04-06-93  CFW   Module created.
*       04-14-93  CFW   Change _charmax from short to int, cleanup.
*       09-15-93  SKS   Use ANSI conformant "__" names.
*       11-01-93  GJF   Cleaned up a bit.
*       04-28-99  PML   Wrap __declspec(allocate()) in _CRTALLOC macro.
*       03-27-01  PML   .CRT$XI routines must now return 0 or _RT_* fatal
*                       error code (vs7#231220)
*       02-11-05  AC    Remove redundant #pragma section
*                       VSW#445138
*
*******************************************************************************/

#include <sect_attribs.h>
#include <internal.h>

int __lconv_init(void);

int _charmax = 255;

_CRTALLOC(".CRT$XIC") static _PIFV pinit = __lconv_init;
