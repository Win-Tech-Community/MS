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
*mbscpy_s.inl - implementation of _mbscpy_s
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file contains the algorithm for _mbscpy_s.
*
*Revision History:
*       07-23-04  AC    Created
*       08-03-04  AC    Added support for locale argument
*       09-27-04  ESC   Update to handle lead byte of (lead,null) as string terminator.
*       01-14-05  AC    Small prefast (espx) fix
*       05-27-05  MSL   Source processing
*
****/

 
_FUNC_PROLOGUE
#if _USE_LOCALE_ARG
errno_t __cdecl _FUNC_NAME(unsigned char *_DEST, size_t _SizeInBytes, const unsigned char *_SRC, _LOCALE_ARG_DECL)
#else
errno_t __cdecl _FUNC_NAME(unsigned char *_DEST, size_t _SizeInBytes, const unsigned char *_SRC)
#endif
{
    unsigned char *p;
    size_t available;
    BOOL fIsLeadPrefix;
 
    /* validation section */
    _VALIDATE_STRING(_DEST, _SizeInBytes);
    _VALIDATE_POINTER_RESET_STRING(_SRC, _DEST, _SizeInBytes);
 
#if _USE_LOCALE_ARG
    _LOCALE_UPDATE;
    if (_LOCALE_SHORTCUT_TEST)
    {
        return _SB_FUNC_NAME((char *)_DEST, _SizeInBytes, (const char *)_SRC);
    }
#endif
 
    p = _DEST;
    available = _SizeInBytes;
    while ((*p++ = *_SRC++) != 0 && --available > 0)
    {
    }

    /*
     * If we ran out of destination bytes then we did so before copying null.
     * Only exception to that is if last mbc was invalid (leadbyte+null), which
     * is treated as null. In that case clear the copied lead byte and return ok.
     */
 
    if (available == 0)
    {
        if (*_SRC == 0) {
            _ISMBBLEADPREFIX(fIsLeadPrefix,_DEST,p-1);
            if (fIsLeadPrefix)
            {
                p[-1] = 0;
                _RETURN_MBCS_ERROR;
            }
        }
        _RESET_STRING(_DEST, _SizeInBytes);
        _RETURN_BUFFER_TOO_SMALL(_DEST, _SizeInBytes);
    }

    /*
     * Otherwise we have space left in the dst buffer and stopped copying because
     * we saw a null in the src. If null is part of invalid MBC (lead byte + null)
     * then clear the lead byte also.
     */

    _ISMBBLEADPREFIX(fIsLeadPrefix, _DEST, p-2);
    if (fIsLeadPrefix && (p - 2) >= _DEST)
    {
        p[-2] = 0;
        available++;
        _FILL_STRING(_DEST, _SizeInBytes, _SizeInBytes - available + 1);
        _RETURN_MBCS_ERROR;
    }
 
    _FILL_STRING(_DEST, _SizeInBytes, _SizeInBytes - available + 1);
    _RETURN_NO_ERROR;
}
 
