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
*execl.c - execute a file with a list of arguments
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _execl() - execute a file with a list of arguments
*
*Revision History:
*       10-14-83  RN    written
*       12-11-87  JCR   Added "_LOAD_DS" to declaration
*       11-20-89  GJF   Fixed copyright, indents. Added const attribute to
*                       types of filename and arglist. #include-d PROCESS.H
*                       and added ellipsis to match prototype.
*       03-08-90  GJF   Replaced _LOAD_DS with _CALLTYPE2, added #include
*                       <cruntime.h> and removed #include <register.h>.
*       07-24-90  SBM   Removed redundant includes, replaced <assertm.h> by
*                       <assert.h>
*       09-27-90  GJF   New-style function declarator.
*       01-17-91  GJF   ANSI naming.
*       02-14-90  SRW   Use NULL instead of _environ to get default.
*       04-06-93  SKS   Replace _CRTAPI* with __cdecl
*       07-16-93  SRW   ALPHA Merge
*       08-31-93  GJF   Merged NT SDK and Cuda versions
*       12-07-93  CFW   Wide char enable.
*       01-10-95  CFW   Debug CRT allocs.
*       02-06-95  CFW   assert -> _ASSERTE.
*       02-06-98  GJF   Changes for Win64: changed return type to intptr_t.
*       11-02-03  AC    Added validation.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>
#include <process.h>
#include <stdarg.h>
#include <internal.h>
#include <tchar.h>
#include <dbgint.h>

/***
*int _execl(filename, arglist) - execute a file with arg list
*
*Purpose:
*       Transform the argument list so it is a vector, then pass its address
*       to execve.  Use a pointer to the default environment vector.
*
*Entry:
*       _TSCHAR *filename - file to execute
*       _TSCHAR *arglist  - list of arguments
*       call as _execl(path, arg0, arg1, ..., argn, NULL);
*
*Exit:
*       destroys the calling process, hopefully
*       returns -1 if fails
*
*Exceptions:
*
*******************************************************************************/

intptr_t __cdecl _texecl (
        const _TSCHAR *filename,
        const _TSCHAR *arglist,
        ...
        )
{
#ifdef  _M_IX86

        /* validation section */
        _VALIDATE_RETURN(filename != NULL, EINVAL, -1);
        _VALIDATE_RETURN(*filename != _T('\0'), EINVAL, -1);
        _VALIDATE_RETURN(arglist != NULL, EINVAL, -1);
        _VALIDATE_RETURN(*arglist != _T('\0'), EINVAL, -1);

        return(_texecve(filename,&arglist,NULL));

#else   /* ndef _M_IX86 */

        va_list vargs;
        _TSCHAR * argbuf[64];
        _TSCHAR ** argv;
        intptr_t result;

        /* validation section */
        _VALIDATE_RETURN(filename != NULL, EINVAL, -1);
        _VALIDATE_RETURN(*filename != _T('\0'), EINVAL, -1);
        _VALIDATE_RETURN(arglist != NULL, EINVAL, -1);
        _VALIDATE_RETURN(*arglist != _T('\0'), EINVAL, -1);

        va_start(vargs, arglist);
#ifdef WPRFLAG
        argv = _wcapture_argv(&vargs, arglist, argbuf, 64);
#else
        argv = _capture_argv(&vargs, arglist, argbuf, 64);
#endif
        va_end(vargs);

        result = _texecve(filename,argv,NULL);
        if (argv && argv != argbuf)
            _free_crt(argv);
        return result;

#endif  /* _M_IX86 */
}
