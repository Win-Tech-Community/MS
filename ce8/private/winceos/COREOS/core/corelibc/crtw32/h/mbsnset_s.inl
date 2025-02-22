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
*mbsnset_s.inl - general implementation of _mbsnset_s and _mbsnbset_s
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file contains the general algorithm for _mbsnset_s and _mbsnbset_s.
*
*Revision History:
*       07-27-04  AC    Created
*       08-03-04  AC    Fixed small error (typo in macro _RETURN_DEST_NOT_NULL_TERMINATED)
*       08-04-04  AC    Added support for locale argument
*       09-27-04  ESC   Write 0 over invalid termination instead of ' '
*       10-30-04  AC    Fix according to the spec
*                       VSW#385890, 386380
*       11-15-04  AC    Fix minor issue
*                       VSW#409787
*       05-27-05  MSL   Source processing
*
****/
 
_FUNC_PROLOGUE
#if _USE_LOCALE_ARG
errno_t __cdecl _FUNC_NAME(unsigned char *_DEST, size_t _SizeInBytes, unsigned int _Value, size_t _COUNT, _LOCALE_ARG_DECL)
#else
errno_t __cdecl _FUNC_NAME(unsigned char *_DEST, size_t _SizeInBytes, unsigned int _Value, size_t _COUNT)
#endif
{
    int mbcs_error = 0;
    unsigned char *p;
    size_t available;
    unsigned char highval, lowval;
    int mblead = 0;
 
    /* validation section */
    if (_COUNT == 0 && _DEST == NULL && _SizeInBytes == 0)
    {
        /* this case is allowed; nothing to do */
        _RETURN_NO_ERROR;
    }
    _VALIDATE_STRING(_DEST, _SizeInBytes);
 
#if _USE_LOCALE_ARG
    _LOCALE_UPDATE;
    if (_LOCALE_SHORTCUT_TEST)
    {
        return _SB_FUNC_NAME((char *)_DEST, _SizeInBytes, (int)_Value, _COUNT);
    }
#endif

    p = _DEST;
    available = _SizeInBytes;
    highval = (unsigned char)(_Value >> 8);
    lowval = (unsigned char)(_Value & 0x00ff);
 
    /* ensure _Value is a valid mbchar */
    if ((highval != 0 && (lowval == 0 || !_ISMBBLEAD(highval))) ||
        (highval == 0 && _ISMBBLEAD(lowval)))
    {
        _RESET_STRING(_DEST, _SizeInBytes);
        _RETURN_MBCS_ERROR;
    }

    _ASSERT_EXPR((!_CrtGetCheckCount() || _COUNT < _SizeInBytes), L"Buffer is too small");

    if (highval != 0)
    {
#if _COUNT_IN_BYTES
        /* if _COUNT is odd, make it even subtracting 1 */
        /* divide _COUNT by 2 to have a count in chars instead of bytes */
        if ((_COUNT & 1) == 1)
        {
            --_COUNT;
            mbcs_error = 1;
        }
        _COUNT = _COUNT / 2;
#endif
        while (*p != 0 && _COUNT > 0 && --available > 0)
        {
            if (p[1] == 0)
            {
                /* do not orphan leadbyte */
                *p = 0;
                ++available;
                mbcs_error = 1;
                break;
            }
            /* track the mblead status in the original string */
            mblead = mblead ? 0 : _ISMBBLEAD(*p);
            *p++ = highval;
            if (--available == 0)
            {
                break;
            }
            mblead = mblead ? 0 : _ISMBBLEAD(*p);
            *p++ = lowval;
            --_COUNT;
        }
    }
    else
    {
        while (*p != 0 && _COUNT > 0 && --available > 0)
        {
            /* track the mblead status in the original string */
            mblead = mblead ? 0 : _ISMBBLEAD(*p);
            *p++ = lowval;
            --_COUNT;
        }
    }
 
    /* if the last written byte overlapps a leadbyte,
     * copy a space over the corresponding trailbyte */
    if (_COUNT == 0 && mblead && *p != 0 && --available > 0)
    {
        mbcs_error = 1;
        if (p[1] == 0)
        {
            /* special case: if the space would be followed by 0, just put a 0 */
            *p = 0;
            ++available;
        }
        else
        {
            *p++ = ' ';
        }
    }

    if (_COUNT == 0)
    {
        /* ensure the string is null-terminated */
        while (*p != 0 && --available > 0)
        {
            ++p;
        }
    }
 
    if (available == 0)
    {
        _RESET_STRING(_DEST, _SizeInBytes);
        _RETURN_DEST_NOT_NULL_TERMINATED(_DEST, _SizeInBytes);
    }
    _FILL_STRING(_DEST, _SizeInBytes, _SizeInBytes - available + 1);
    if (mbcs_error)
    {
        _RETURN_MBCS_ERROR;
    }
    else
    {
        _RETURN_NO_ERROR;
    }
}
 
