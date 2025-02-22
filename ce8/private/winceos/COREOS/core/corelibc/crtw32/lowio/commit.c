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
*commit.c - flush buffer to disk
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains _commit() - flush buffer to disk
*
*Revision History:
*       05-25-90  SBM   initial version
*       07-24-90  SBM   Removed '32' from API names
*       09-28-90  GJF   New-style function declarator.
*       12-03-90  GJF   Appended Win32 version onto the source with #ifdef-s.
*                       It is close enough to the Cruiser version that it
*                       should be more closely merged with it later on (much
*                       later on).
*       12-04-90  SRW   Changed to include <oscalls.h> instead of <doscalls.h>
*       12-06-90  SRW   Changed to use _osfile and _osfhnd instead of _osfinfo
*       02-07-91  SRW   Changed to call _get_osfhandle [_WIN32_]
*       04-09-91  PNT   Added _MAC_ conditional
*       02-13-92  GJF   Replaced _nfile by _nhandle for Win32.
*       04-06-93  SKS   Replace _CRTAPI* with __cdecl
*       09-06-94  CFW   Remove Cruiser support.
*       01-04-95  GJF   _WIN32_ -> _WIN32
*       02-15-95  GJF   Appended Mac version of source file (somewhat cleaned
*                       up), with appropriate #ifdef-s.
*       06-11-95  GJF   Replaced _osfile[] with __osfile() (macro referencing
*                       field in ioinfo struct).
*       06-26-95  GJF   Added initial check that the file handle is open.
*       07-08-96  GJF   Replaced defined(_WIN32) with !defined(_MAC) and
*                       defined(_M_M68K) || defined(_M_MPPC) with 
*                       defined(_MAC). Removed REG1 and REG2 (old register
*                       macros). Replaced oscalls.h with windows.h. Also, 
*                       detab-ed and cleaned up the format a bit.
*       12-17-97  GJF   Exception-safe locking.
*       05-17-99  PML   Remove all Macintosh support.
*       09-11-03  SJ    Secure CRT Work - Assertions & Validations
*       11-13-03  SJ    File Handle checks made consistent - VSW#199372
*       10-31-04  AC    Prefast fixes
*                       VSW#373224
*
*******************************************************************************/

#include <cruntime.h>
#include <windows.h>
#include <errno.h>
#include <io.h>
#include <internal.h>
#include <msdos.h>      /* for FOPEN */
#include <mtdll.h>
#include <stdlib.h>     /* for _doserrno */

/***
*int _commit(filedes) - flush buffer to disk
*
*Purpose:
*       Flushes cache buffers for the specified file handle to disk
*
*Entry:
*       int filedes - file handle of file
/*
*Exit:
*       returns success code
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _commit (
        int filedes
        )
{
        int retval;

        /* if filedes out of range, complain */
        _CHECK_FH_RETURN( filedes, EBADF, -1 );
        _CHECK_IO_INIT(EBADF);
        _VALIDATE_RETURN((filedes >= 0 && (unsigned)filedes < (unsigned)_nhandle), EBADF, -1);
        _VALIDATE_RETURN((_osfile(filedes) & FOPEN), EBADF, -1);
        
        _lock_fh(filedes);
        __try {
                if (_osfile(filedes) & FOPEN) {

        if ( !FlushFileBuffers((HANDLE)_get_osfhandle(filedes)) ) {
                retval = GetLastError();
        }
        else {
                retval = 0;     /* return success */
        }

        /* map the OS return code to C errno value and return code */
        if (retval == 0)
                goto good;

        _doserrno = retval;

                }

        errno = EBADF;
        retval = -1;

        _ASSERTE(("Invalid file descriptor. File possibly closed by a different thread",0));
good :
        ; }
        __finally {
                _unlock_fh(filedes);
        }
        return (retval);
}
