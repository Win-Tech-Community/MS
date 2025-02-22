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
*execvpe.c - execute a file with given environ; search along PATH
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _execvpe() - execute a file with given environ
*
*Revision History:
*       10-17-83  RN    written
*       10-29-85  TC    added execvpe capability
*       11-19-86  SKS   handle both kinds of slashes
*       12-01-86  JMB   added Kanji file name support under conditional KANJI
*                       switches, corrected header info
*                       removed bogus check for env = b after call to strncpy().
*       12-11-87  JCR   Added "_LOAD_DS" to declaration
*       09-05-88  SKS   Treat EACCES the same as ENOENT -- keep trying
*       10-18-88  GJF   Removed copy of PATH string to local array, changed
*                       bbuf to be a malloc-ed buffer. Removed bogus limits
*                       on the size of that PATH string.
*       10-26-88  GJF   Don't search PATH when relative pathname is given (per
*                       Stevesa). Also, if the name built from PATH component
*                       and filename is a UNC name, allow any error.
*       11-20-89  GJF   Fixed copyright. Added const attribute to types of
*                       filename, argvector and envptr. Also, added "#include
*                       <jstring.h>" under KANJI switch (same as 5-17-89 change
*                       to CRT version).
*       03-08-90  GJF   Replaced _LOAD_DS with _CALLTYPE1, added #include
*                       <cruntime.h> and removed #include <register.h>. Also,
*                       cleaned up the formatting a bit.
*       07-24-90  SBM   Removed redundant includes, replaced <assertm.h> by
*                       <assert.h>
*       09-27-90  GJF   New-style function declarator.
*       01-17-91  GJF   ANSI naming.
*       11-30-92  KRS   Port _MBCS code from 16-bit tree.
*       04-06-93  SKS   Replace _CRTAPI* with __cdecl
*       12-07-93  CFW   Wide char enable.
*       01-10-95  CFW   Debug CRT allocs.
*       02-06-95  CFW   assert -> _ASSERTE.
*       02-06-98  GJF   Changes for Win64: changed return type to intptr_t.
*       11-02-03  AC    Added validation.
*       03-24-04  MSL   Fixed spelling
*       10-31-04  AC    Prefast fixes
*                       VSW#373224
*       01-14-05  AC    Prefast (espx) fixes
*       03-23-05  MSL   Fix unreported DBCS issue
*       04-01-05  MSL   Integer overflow fix during allocation 
*       03-27-06  AC    Fix usage of errno
*                       VSW#585562
*
*******************************************************************************/

#include <cruntime.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <mbstring.h>
#include <tchar.h>
#include <dbgint.h>
#include <internal.h>

#define SLASHCHAR _T('\\')
#define XSLASHCHAR _T('/')

#define SLASH _T("\\")
#define DELIMITER _T(";")

#ifdef _MBCS
/* note, the macro below assumes p is to pointer to a single-byte character
 * or the 1st byte of a double-byte character, in a string.
 */
#define ISPSLASH(p)     ( ((p) == _mbschr((p), SLASHCHAR)) || ((p) == \
_mbschr((p), XSLASHCHAR)) )
#else
#define ISSLASH(c)      ( ((c) == SLASHCHAR) || ((c) == XSLASHCHAR) )
#endif


/***
*int _execvpe(filename, argvector, envvector) - execute a file
*
*Purpose:
*       Executes a file with given arguments and environment.
*       try to execute the file. start with the name itself (directory '.'),
*       and if that doesn't work start prepending pathnames from the
*       environment until one works or we run out. if the file is a pathname,
*       don't go to the environment to get alternate paths. If a needed text
*       file is busy, wait a little while and try again before despairing
*       completely
*
*Entry:
*       _TSCHAR *filename        - file to execute
*       _TSCHAR **argvector - vector of arguments
*       _TSCHAR **envvector - vector of environment variables
*
*Exit:
*       destroys the calling process (hopefully)
*       if fails, returns -1
*
*Exceptions:
*
*******************************************************************************/

intptr_t __cdecl _texecvpe (
        const _TSCHAR *filename,
        const _TSCHAR * const *argvector,
        const _TSCHAR * const *envptr
        )
{
        _TSCHAR *envbuf = NULL;
        _TSCHAR *env;
        _TSCHAR *bbuf = NULL;
        _TSCHAR *buf;
        _TSCHAR *pfin;

        /* validation section */
        _VALIDATE_RETURN(filename != NULL, EINVAL, -1);
        _VALIDATE_RETURN(*filename != _T('\0'), EINVAL, -1);
        _VALIDATE_RETURN(argvector != NULL, EINVAL, -1);
        _VALIDATE_RETURN(*argvector != NULL, EINVAL, -1);
        _VALIDATE_RETURN(**argvector != _T('\0'), EINVAL, -1);

        /* it is ok to reset errno here, because if exec succeeds, we'll lose errno,
         * and if exec fails, errno will be set to something != 0
         */
        errno = 0;

        _texecve(filename,argvector,envptr);

        if ( (errno != ENOENT)
        || (_tcschr(filename, SLASHCHAR) != NULL)
        || (_tcschr(filename, XSLASHCHAR) != NULL)
        || *filename && *(filename+1) == _T(':')
        || (_ERRCHECK_EINVAL(_tdupenv_s_crt(&envbuf, NULL, _T("PATH"))) != 0)
        || envbuf == NULL
        )
                goto reterror;

        /* allocate a buffer to hold alternate pathnames for the executable
         */
        if ( (buf = bbuf = _calloc_crt(_MAX_PATH, sizeof(_TSCHAR))) == NULL )
            goto reterror;

        env = envbuf;
        do {
            /* copy a component into bbuf[], taking care not to overflow it
                */
            while ( (*env) && (*env != _T(';')) && (buf < (bbuf + (_MAX_PATH-2))) )
            {
                if(_istleadbyte(*env))
                {
                    if(env[1]==_T('\0') || buf+1>=(bbuf + (_MAX_PATH-2)))
                    {
                        /* dump if leadbyte followed by 0, or if leadbyte would be last item in buffer */
                        break;
                    }
                    /* copy leadbyte char; already checked for space for two */
                    *buf++ = *env++;
                }
                *buf++ = *env++;
            }

            *buf = _T('\0');
            if (buf > bbuf)
            {
                pfin = --buf;
            }
            else
            {
                pfin = buf;
            }
            buf = bbuf;

#ifdef _MBCS
            if (*pfin == SLASHCHAR) {
                    if (pfin != _mbsrchr(buf,SLASHCHAR))
                            /* *pfin is the second byte of a double-byte
                                * character
                                */
                            _ERRCHECK(strcat_s( buf, _MAX_PATH, SLASH ));
            }
            else if (*pfin != XSLASHCHAR)
                    _ERRCHECK(strcat_s(buf, _MAX_PATH, SLASH));
#else
            if (*pfin != SLASHCHAR && *pfin != XSLASHCHAR)
                    _ERRCHECK(_tcscat_s(buf, _MAX_PATH, SLASH));
#endif

            /* check that the final path will be of legal size. if so,
                * build it. otherwise, return to the caller (return value
                * and errno rename set from initial call to _execve()).
                */
            if ( (_tcslen(buf) + _tcslen(filename)) < _MAX_PATH )
                    _ERRCHECK(_tcscat_s(buf, _MAX_PATH, filename));
            else
                    break;

            /* it is ok to reset errno here, because if exec succeeds, we'll lose errno,
             * and if exec fails, errno will be set to something != 0
             */
            errno = 0;

            _texecve(buf, argvector, envptr);

            if ( (errno != ENOENT)
#ifdef _MBCS
            && (!ISPSLASH(buf) || !ISPSLASH(buf+1)) )
#else
            && (!ISSLASH(*buf) || !ISSLASH(*(buf+1))) )
#endif
                    break;
            
        } while ( *env && env++ );

reterror:
        if (bbuf != NULL)
                _free_crt(bbuf);
        if (envbuf != NULL)
                _free_crt(envbuf);

        return(-1);
}
