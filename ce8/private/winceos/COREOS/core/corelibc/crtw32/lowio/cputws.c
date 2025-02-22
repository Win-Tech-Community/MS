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
*cputws.c - write a wide string to console
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _cputs() - writes a wide string to the console
*
*Revision History:
*       10-29-08  RMS   Module Created.
*
*******************************************************************************/

#ifndef _POSIX_

#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <errno.h>
#include <cruntime.h>
#include <stdio.h>
#include <dbgint.h>
#include <file2.h>
#include <internal.h>
#include <mtdll.h>
#include <limits.h>

/*
 * declaration for console handle
 */
extern intptr_t _confh;

/***
*  _cputws() - _cputws() writes a wide char string to console.
*
*  Purpose:
*       Writes a wide char string to console.
*
*  Entry:
*       str:    pointer to string
*  Exit:
*       returns 0 if sucessful. Nonzero if unsucessful
*
*******************************************************************************/
int _CRTIMP __cdecl _cputws(
        const wchar_t *str
        )
{
#ifdef _WIN32_WCE
    return -1; 
#else
    size_t len;
    int retval = 0;

    _VALIDATE_CLEAR_OSSERR_RETURN((str != NULL), EINVAL, -1);
    
    if (_confh == -2)
        __initconout();

    if (_confh == -1)
        return -1;

    /* Write string to console file handle */

    len = wcslen(str);

    _mlock(_CONIO_LOCK);
    __try
    {
        while (len > 0)
        {
            // According to MSDN, http://msdn.microsoft.com/en-us/library/ms687401(VS.85).aspx,
            // the buffer size must be less than 64K.

#define cbWriteConsoleMax 65535
#define cchWriteConsoleMax (cbWriteConsoleMax / sizeof(wchar_t))

            DWORD cchWrite = (len > cchWriteConsoleMax) ? cchWriteConsoleMax : (DWORD) len;
            DWORD cchWritten;

            if (!WriteConsoleW((HANDLE) _confh,
                               str,
                               cchWrite,
                               &cchWritten,
                               NULL))
            {
                retval = -1;
                break;
            }

            str += cchWrite;
            len -= cchWrite;
        }
    }
    __finally {
        _munlock(_CONIO_LOCK);
    }

    return retval;
#endif // _WIN32_WCE
}

#endif /* _POSIX_ */
