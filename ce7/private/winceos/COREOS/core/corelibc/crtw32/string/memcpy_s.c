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
*memcpy_s.c - contains memcpy_s routine
*
*Purpose:
*       memcpy_s() copies a source memory buffer to a destination buffer.
*       Overlapping buffers are not treated specially, so propagation may occur.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>
#include <internal.h>

/***
*memcpy_s - Copy source buffer to destination buffer
*
*Purpose:
*       memcpy_s() copies a source memory buffer to a destination memory buffer.
*       This routine does NOT recognize overlapping buffers, and thus can lead
*       to propagation.
*
*       For cases where propagation must be avoided, memmove_s() must be used.
*
*Entry:
*       void *dst = pointer to destination buffer
*       size_t sizeInBytes = size in bytes of the destination buffer
*       const void *src = pointer to source buffer
*       size_t count = number of bytes to copy
*
*Exit:
*       Returns 0 if everything is ok, else return the error code.
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*       On error, the error code is returned and the destination buffer is zeroed.
*
*******************************************************************************/

errno_t __cdecl memcpy_s(
    void * dst,
    size_t sizeInBytes,
    const void * src,
    size_t count
)
{
    if (count == 0)
    {
        /* nothing to do */
        return 0;
    }

    /* validation section */
    _VALIDATE_RETURN_ERRCODE(dst != NULL, EINVAL);
    if (src == NULL || sizeInBytes < count)
    {
        /* zeroes the destination buffer */
        memset(dst, 0, sizeInBytes);

        _VALIDATE_RETURN_ERRCODE(src != NULL, EINVAL);
        _VALIDATE_RETURN_ERRCODE(sizeInBytes >= count, ERANGE);
        /* useless, but prefast is confused */
        return EINVAL;
    }

    memcpy(dst, src, count);
    return 0;
}
