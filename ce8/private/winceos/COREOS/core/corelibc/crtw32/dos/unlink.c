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
*unlink.c - unlink a file
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines unlink() - unlink a file
*
*Revision History:
*       06-06-89  PHG   Module created, based on asm version
*       03-07-90  GJF   Made calling type _CALLTYPE2 (for now), added #include
*                       <cruntime.h>, fixed compiler warnings and fixed the
*                       copyright. Also, cleaned up the formatting a bit.
*       07-24-90  SBM   Removed '32' from API names
*       09-27-90  GJF   New-style function declarators.
*       12-04-90  SRW   Changed to include <oscalls.h> instead of <doscalls.h>
*       12-06-90  SRW   Added _CRUISER_ and _WIN32 conditionals.
*       01-16-91  GJF   ANSI naming.
*       04-10-91  PNT   Added _MAC_ conditional
*       03-16-92  PLM   MAC verison ccreated from OS/2 version
*       04-10-91  PNT   Added _MAC_ conditional (Mac version only)
*       11-02-92  PLM   Added directory test and extracted code for remove() (Mac version only)
*       04-06-93  SKS   Replace _CRTAPI* with __cdecl
*       11-01-93  CFW   Enable Unicode variant, rip out Cruiser.
*       02-08-95  JWM   Spliced _WIN32 & Mac versions.
*       07-01-96  GJF   Replaced defined(_WIN32) with !defined(_MAC). Also,
*                       detab-ed and cleaned up the format a bit.
*       05-17-99  PML   Remove all Macintosh support.
*
*******************************************************************************/

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <dbgint.h>

/***
*int _unlink(path) - unlink(delete) the given file
*
*Purpose:
*       This version deletes the given file because there is no
*       distinction between a linked file and non-linked file.
*
*       NOTE: remove() is an alternative entry point to the _unlink()
*       routine* interface is identical.
*
*Entry:
*       _TSCHAR *path - file to unlink/delete
*
*Exit:
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/
#ifndef _UNICODE

int __cdecl remove (
        const char *path
        )
{
    wchar_t* pathw = NULL;
    int retval;

    if (path)
    {
        if (!__copy_path_to_wide_string(path, &pathw))
            return -1;
    }

    /* call the wide-char variant */
    retval = _wremove(pathw);

    _free_crt(pathw); /* _free_crt leaves errno alone if everything completes as expected */

    return retval;
}

#else /* _UNICODE */

int __cdecl _wremove (
        const wchar_t *path
        )
{
        ULONG dosretval;

        if (!DeleteFileW(path))
            dosretval = GetLastError();
        else
            dosretval = 0;

        if (dosretval) {
            /* error occured -- map error code and return */
            _dosmaperr(dosretval);
            return -1;
        }

        return 0;
}

#endif /* _UNICODE */

int __cdecl _tunlink (
        const _TSCHAR *path
        )
{
        /* remove is synonym for unlink */
        return _tremove(path);
}
