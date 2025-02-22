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
*osfinfo.c - Win32 _osfhnd[] support routines
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines the internally used routine _alloc_osfhnd()
*       and the user visible routine _get_osfhandle().
*
*Revision History:
*       11-16-90  GJF   What can I say? The custom heap business was getting
*                       a little slow...
*       12-03-90  GJF   Fixed my syntax errors.
*       12-06-90  SRW   Changed to use _osfile and _osfhnd instead of _osfinfo
*       12-28-90  SRW   Added cast of void * to char * for Mips C Compiler
*       02-18-91  SRW   Fixed bug in _alloc_osfhnd with setting FOPEN bit
*                       (only caller should do that) [_WIN32_]
*       02-18-91  SRW   Fixed bug in _alloc_osfhnd with checking against
*                       _NFILE_ instead of _nfile [_WIN32_]
*       02-18-91  SRW   Added debug output to _alloc_osfhnd if out of
*                       file handles. [_WIN32_]
*       02-25-91  SRW   Renamed _get_free_osfhnd to be _alloc_osfhnd [_WIN32_]
*       02-25-91  SRW   Exposed _get_osfhandle and _open_osfhandle [_WIN32_]
*       08-08-91  GJF   Use ANSI-fied form of constant names.
*       11-25-91  GJF   Lock fh before checking whether it's free.
*       12-31-91  GJF   Improved multi-thread lock usage [_WIN32_].
*       02-13-92  GJF   Replaced _nfile with _nhandle
*       07-15-92  GJF   Fixed setting of flags in _open_osfhnd.
*       02-19-93  GJF   If GetFileType fails in _open_osfhandle, don't unlock
*                       fh (it wasn't locked)!
*       04-06-93  SKS   Replace _CRTAPI* with __cdecl
*       09-06-94  CFW   Replace MTHREAD with _MT.
*       01-04-95  GJF   _WIN32_ -> _WIN32
*       02-15-95  GJF   Appended Mac version of source file (somewhat cleaned
*                       up), with appropriate #ifdef-s.
*       06-02-95  GJF   Only call SetStdHandle for console apps.
*       06-12-95  GJF   Revised to use __pioinfo[].
*       06-29-95  GJF   Have __lock_fhandle ensure the lock is initialized.
*       02-17-96  SKS   Fix error in file handle locking code
*       07-09-96  GJF   Replaced defined(_WIN32) with !defined(_MAC) and
*                       defined(_M_M68K) || defined(_M_MPPC) with 
*                       defined(_MAC). Removed DLL_FOR_WIN32S
*       08-29-97  GJF   Check for and propagate _O_NOINHERIT in 
*                       _open_osfhandle.
*       02-10-98  GJF   Changes for Win64: changed everything that holds HANDLE
*                       values to intptr_t.
*       05-17-99  PML   Remove all Macintosh support.
*       10-14-99  PML   Replace InitializeCriticalSection with wrapper function
*                       __crtInitCritSecAndSpinCount
*       02-20-01  PML   vs7#172586 Avoid _RT_LOCK by preallocating all locks
*                       that will be required, and returning failure back on
*                       inability to allocate a lock.
*       04-29-02  GB    Added try-finally arounds lock-unlock.
*       09-11-03  SJ    Secure CRT Work - Assertions & Validations
*       11-13-03  SJ    File Handle checks made consistent - VSW#199372
*       03-13-04  MSL   Avoid returning from within __try for prefast. Also removed
*                       incorrect debug message
*       10-31-04  AC    Prefast fixes
*                       VSW#373224
*       04-01-05  MSL   Integer overflow protection
*       05-10-05  PML   _alloc_osfhnd now sets FOPEN (VSW#443926)
*
*******************************************************************************/

#include <cruntime.h>
#include <oscalls.h>
#include <errno.h>
#include <internal.h>
#include <fcntl.h>
#include <malloc.h>
#include <msdos.h>
#include <mtdll.h>
#include <stdlib.h>
#include <dbgint.h>
#include <io.h>


/***
*int _alloc_osfhnd() - get free _ioinfo struct
*
*Purpose:
*       Finds the first free entry in the arrays of ioinfo structs and
*       returns the index of that entry (which is the CRT file handle to the
*       caller) to the caller.  The FOPEN flag is turned on in the new entry,
*       to prevent multithreaded race conditions/deadlocks.
*
*Entry:
*       none
*
*Exit:
*       returns index of the entry, if successful
*       return -1, if no free entry is available or out of memory
*
*       MULTITHREAD NOTE: IF SUCCESSFUL, THE HANDLE IS LOCKED WHEN IT IS
*       RETURNED TO THE CALLER!  ALSO, FOPEN HAS BEEN TURNED ON, SO IF THE
*       CALLER ABANDONS THE HANDLE, FOPEN MUST BE CLEARED!
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _alloc_osfhnd(
        void
        )
{
        int fh = -1;    /* file handle */
        int i;
        ioinfo *pio;
        int failed=FALSE;

        if (!_mtinitlocknum(_OSFHND_LOCK))
            return -1;

        _CHECK_IO_INIT(-1);  /* ensure __pioinfo[] array is initialized */

        _mlock(_OSFHND_LOCK);   /* lock the __pioinfo[] array */

        __TRY

            /*
             * Search the arrays of ioinfo structs, in order, looking for the
             * first free entry. The compound index of this free entry is the
             * return value. Here, the compound index of the ioinfo struct
             * *(__pioinfo[i] + j) is k = i * IOINFO_ARRAY_ELTS + j, and k = 0,
             * 1, 2,... is the order of the search.
             */
            for ( i = 0 ; i < IOINFO_ARRAYS ; i++ ) {
                /*
                 * If __pioinfo[i] is non-empty array, search it looking for
                 * the first free entry. Otherwise, allocate a new array and use
                 * its first entry.
                 */
                if ( __pioinfo[i] != NULL ) {
                    /*
                     * Search for an available entry.
                     */
                    for ( pio = __pioinfo[i] ;
                          pio < __pioinfo[i] + IOINFO_ARRAY_ELTS ;
                          pio++ )
                    {
                        if ( (pio->osfile & FOPEN) == 0 ) {
                            /*
                             * Make sure the lock is initialized.
                             */
                            if ( pio->lockinitflag == 0 ) {
                                _mlock( _LOCKTAB_LOCK );
                                __TRY
                                    if ( pio->lockinitflag == 0 ) {
#ifdef _WIN32_WCE
                                        InitializeCriticalSection( &(pio->lock) );
#else
                                        InitializeCriticalSectionAndSpinCount( &(pio->lock), _CRT_SPINCOUNT );
#endif // _WIN32_WCE
                                        pio->lockinitflag++;
                                    }
                                __FINALLY
                                    _munlock( _LOCKTAB_LOCK );
                                __END_TRY_FINALLY
                            }

                            if(!failed)
                            {
                                EnterCriticalSection( &(pio->lock) );

                                /*
                                * Check for the case where another thread has
                                * managed to grab the handle out from under us.
                                */
                                if ( (pio->osfile & FOPEN) != 0 ) {
                                        LeaveCriticalSection( &(pio->lock) );
                                        continue;
                                }
                            }

                            if(!failed)
                            {
                                pio->osfile = FOPEN;
                                pio->osfhnd = (intptr_t)INVALID_HANDLE_VALUE;
                                fh = i * IOINFO_ARRAY_ELTS + (int)(pio - __pioinfo[i]);
                                break;
                            }
                        }
                    }

                    /*
                     * Check if a free entry has been found.
                     */
                    if ( fh != -1 )
                        break;
                }
                else {
                    /*
                     * Allocate and initialize another array of ioinfo structs.
                     */
                    if ( (pio = _calloc_crt( IOINFO_ARRAY_ELTS, sizeof(ioinfo) ))
                        != NULL )
                    {

                        /*
                         * Update __pioinfo[] and _nhandle
                         */
                        __pioinfo[i] = pio;
                        _nhandle += IOINFO_ARRAY_ELTS;

                        for ( ; pio < __pioinfo[i] + IOINFO_ARRAY_ELTS ; pio++ ) {
                            pio->osfile = 0;
                            pio->osfhnd = (intptr_t)INVALID_HANDLE_VALUE;
                            pio->pipech = 10;
                            pio->lockinitflag = 0;
                        }

                        /*
                         * The first element of the newly allocated array of ioinfo
                         * structs, *(__pioinfo[i]), is our first free entry.
                         */
                        fh = i * IOINFO_ARRAY_ELTS;
                        _osfile(fh) = FOPEN;
                        if ( !__lock_fhandle( fh ) ) {
                            /*
                             * The lock initialization failed, return the failure
                             */
                            fh = -1;
                        }
                    }

                    break;
                }
            }
        __FINALLY
            _munlock(_OSFHND_LOCK); /* unlock the __pioinfo[] table */
        __END_TRY_FINALLY

        /*
         * return the index of the previously free table entry, if one was
         * found. return -1 otherwise.
         */
        return( fh );
}


/***
*int _set_osfhnd(int fh, long value) - set Win32 HANDLE value
*
*Purpose:
*       If fh is in range and if _osfhnd(fh) is marked with
*       INVALID_HANDLE_VALUE then set _osfhnd(fh) to the passed value.
*
*Entry:
*       int fh      - CRT file handle
*       long value  - new Win32 HANDLE value for this handle
*
*Exit:
*       Returns zero if successful.
*       Returns -1 and sets errno to EBADF otherwise.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _set_osfhnd (
        int fh,
        intptr_t value
        )
{
        if ( fh >= 0 && ((unsigned)fh < (unsigned)_nhandle) &&
             (_osfhnd(fh) == (intptr_t)INVALID_HANDLE_VALUE)
           ) {
#ifndef _WIN32_WCE
            if ( __app_type == _CONSOLE_APP ) {
                switch (fh) {
                case 0:
                    SetStdHandle( STD_INPUT_HANDLE, (HANDLE)value );
                    break;
                case 1:
                    SetStdHandle( STD_OUTPUT_HANDLE, (HANDLE)value );
                    break;
                case 2:
                    SetStdHandle( STD_ERROR_HANDLE, (HANDLE)value );
                    break;
                }
            }
#endif // _WIN32_WCE

            _osfhnd(fh) = value;
            return(0);
        } else {
            errno = EBADF;      /* bad handle */
            _doserrno = 0L;     /* not an OS error */
            return -1;
        }
}


/***
*int _free_osfhnd(int fh) - mark osfhnd field of ioinfo struct as free
*
*Purpose:
*       If fh is in range, the corrsponding ioinfo struct is marked as
*       being open, and the osfhnd field is NOT set to INVALID_HANDLE_VALUE,
*       then mark it with INVALID_HANDLE_VALUE.
*
*Entry:
*       int fh -    CRT file handle
*
*Exit:
*       Returns zero if successful.
*       Returns -1 and sets errno to EBADF otherwise.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _free_osfhnd (
        int fh      /* user's file handle */
        )
{
        if ( (fh >= 0 && (unsigned)fh < (unsigned)_nhandle) &&
             (_osfile(fh) & FOPEN) &&
             (_osfhnd(fh) != (intptr_t)INVALID_HANDLE_VALUE) )
        {
#ifndef _WIN32_WCE
            if ( __app_type == _CONSOLE_APP ) {
                switch (fh) {
                case 0:
                    SetStdHandle( STD_INPUT_HANDLE, NULL );
                    break;
                case 1:
                    SetStdHandle( STD_OUTPUT_HANDLE, NULL );
                    break;
                case 2:
                    SetStdHandle( STD_ERROR_HANDLE, NULL );
                    break;
                }
            }
#endif

            _osfhnd(fh) = (intptr_t)INVALID_HANDLE_VALUE;
            return(0);
        } else {
            errno = EBADF;      /* bad handle */
            _doserrno = 0L;     /* not an OS error */
            return -1;
        }
}


/***
*long _get_osfhandle(int fh) - get Win32 HANDLE value
*
*Purpose:
*       If fh is in range and marked open, return _osfhnd(fh).
*
*Entry:
*       int fh  - CRT file handle
*
*Exit:
*       Returns the Win32 HANDLE successful.
*       Returns -1 and sets errno to EBADF otherwise.
*
*Exceptions:
*
*******************************************************************************/

intptr_t __cdecl _get_osfhandle (
        int fh      /* user's file handle */
        )
{
        _CHECK_FH_CLEAR_OSSERR_RETURN( fh, EBADF, -1 );
        _CHECK_IO_INIT(-1); /* _get_osfhandle can be called externally, so ensure _pioinf is intitalized */
        _VALIDATE_CLEAR_OSSERR_RETURN((fh >= 0 && (unsigned)fh < (unsigned)_nhandle), EBADF, -1);
        _VALIDATE_CLEAR_OSSERR_RETURN((_osfile(fh) & FOPEN), EBADF, -1);

        return( _osfhnd(fh) );
}

/***
*int _open_osfhandle(long osfhandle, int flags) - open C Runtime file handle
*
*Purpose:
*       This function allocates a free C Runtime file handle and associates
*       it with the Win32 HANDLE specified by the first parameter.
*
*Entry:
*       long osfhandle - Win32 HANDLE to associate with C Runtime file handle.
*       int flags      - flags to associate with C Runtime file handle.
*
*Exit:
*       returns index of entry in fh, if successful
*       return -1, if no free entry is found
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _open_osfhandle(
        intptr_t osfhandle,
        int flags
        )
{
        int fh;
        char fileflags;         /* _osfile flags */
        DWORD isdev;            /* device indicator in low byte */
        int success = FALSE;

        /* copy relevant flags from second parameter */

        fileflags = 0;

        if ( flags & _O_APPEND )
            fileflags |= FAPPEND;

        if ( flags & _O_TEXT )
            fileflags |= FTEXT;

        if ( flags & _O_NOINHERIT )
            fileflags |= FNOINHERIT;

#ifdef _WIN32_WCE
#define FILE_TYPE_DISK      0x0001
         // assume disk file type 
         isdev = FILE_TYPE_DISK; 
#else
        /* find out what type of file (file/device/pipe) */

        isdev = GetFileType((HANDLE)osfhandle);
        if (isdev == FILE_TYPE_UNKNOWN) {
            /* OS error */
            _dosmaperr( GetLastError() );   /* map error */
            return -1;
        }

        /* is isdev value to set flags */
        if (isdev == FILE_TYPE_CHAR)
            fileflags |= FDEV;
        else if (isdev == FILE_TYPE_PIPE)
            fileflags |= FPIPE;
#endif // _WIN32_WCE

        /* attempt to allocate a C Runtime file handle */

        if ( (fh = _alloc_osfhnd()) == -1 ) {
            errno = EMFILE;         /* too many open files */
            _doserrno = 0L;         /* not an OS error */
            return -1;              /* return error to caller */
        }
        __TRY

            /*
             * the file is open. now, set the info in _osfhnd array
             */

            _set_osfhnd(fh, osfhandle);

            fileflags |= FOPEN;     /* mark as open */

            _osfile(fh) = fileflags;    /* set osfile entry */
            _textmode(fh) = 0;
            _tm_unicode(fh) = 0;

            success = TRUE;

        __FINALLY
            if (!success)
            {
                _osfile(fh) &= ~FOPEN;
            }
            _unlock_fh(fh);         /* unlock handle */
        __END_TRY_FINALLY

            return success ? fh : -1;   /* return handle */
}


/***
*void __lock_fhandle(int fh) - lock file handle
*
*Purpose:
*       Assert the lock associated with the passed file handle.
*
*Entry:
*       int fh  - CRT file handle
*
*Exit:
*       Returns FALSE if the attempt to initialize the lock fails.  This can
*       only happen the first time the lock is taken, so the return status only
*       needs to be checked on the first such attempt, which is always in
*       _alloc_osfhnd (except for inherited or standard handles, and the lock
*       is allocated manually in _ioinit for those).
*
*Exceptions:
*
*******************************************************************************/

int __cdecl __lock_fhandle (
        int fh
        )
{
        ioinfo *pio = _pioinfo(fh);
        int retval=TRUE;

        /*
         * Make sure the lock has been initialized.
         */
        if ( pio->lockinitflag == 0 ) {

            _mlock( _LOCKTAB_LOCK );
            __TRY
                if ( pio->lockinitflag == 0 ) {
#ifdef _WIN32_WCE 
                    InitializeCriticalSection( &(pio->lock) );
#else
                    InitializeCriticalSectionAndSpinCount( &(pio->lock), _CRT_SPINCOUNT );
#endif _WIN32_WCE    
                pio->lockinitflag++;
                }
            __FINALLY
                _munlock( _LOCKTAB_LOCK);
            __END_TRY_FINALLY
        }

        if(retval)
        {
            EnterCriticalSection( &(_pioinfo(fh)->lock) );
        }

        return retval;
}


/***
*void _unlock_fhandle(int fh) - unlock file handle
*
*Purpose:
*       Release the lock associated with passed file handle.
*
*Entry:
*       int fh  - CRT file handle
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _unlock_fhandle (
        int fh
        )
{
        LeaveCriticalSection( &(_pioinfo(fh)->lock) );
}

