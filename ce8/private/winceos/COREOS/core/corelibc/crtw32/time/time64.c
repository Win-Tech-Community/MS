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
*time64.c - get current system time
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _time64() - gets the current system time and converts it to
*       internal (__time64_t) format time.
*
*Revision History:
*       05-20-98  GJF   Created.
*       09-01-06  JKS   return (time_t)-1 on error according to C99 standard
*
*******************************************************************************/

#include <cruntime.h>
#include <time.h>
#include <ctime.h>
#include <internal.h>
#include <windows.h>

/*
 * Number of 100 nanosecond units from 1/1/1601 to 1/1/1970
 */
#define EPOCH_BIAS  116444736000000000i64

/*
 * Union to facilitate converting from FILETIME to unsigned __int64
 */
typedef union {
        unsigned __int64 ft_scalar;
        FILETIME ft_struct;
        } FT;


/***
*__time64_t _time64(timeptr) - Get current system time and convert to a
*       __time64_t value.
*
*Purpose:
*       Gets the current date and time and stores it in internal 64-bit format
*       (__time64_t). The time is returned and stored via the pointer passed in
*       timeptr. If timeptr == NULL, the time is only returned, not stored in
*       *timeptr. The internal (__time64_t) format is the number of seconds 
*       since 00:00:00, Jan 1 1970 (UTC).
*
*Entry:
*       __time64_t *timeptr - pointer to long to store time in.
*
*Exit:
*       returns the current time.
*
*Exceptions:
*
*******************************************************************************/

__time64_t __cdecl _time64 (
        __time64_t *timeptr
        )
{
        __time64_t tim;
        FT nt_time;

        GetSystemTimeAsFileTime( &(nt_time.ft_struct) );

        tim = (__time64_t)((nt_time.ft_scalar - EPOCH_BIAS) / 10000000i64);

        if (tim > _MAX__TIME64_T)
                tim = (__time64_t)(-1);

        if (timeptr)
                *timeptr = tim;         /* store time if requested */

        return tim;
}
