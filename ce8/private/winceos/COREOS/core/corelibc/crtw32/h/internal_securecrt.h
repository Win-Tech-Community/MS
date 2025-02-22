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
*internal_securecrt.h - contains declarations of internal routines and variables for securecrt
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Declares routines and variables used internally in the SecureCRT implementation.
*       In this include file we define the macros needed to implement the secure functions
*       inlined in the *.inl files like tcscpy_s.inl, etc.
*       Note that this file is used for the CRT implementation, while internal_safecrt is used
*       to build the downlevel library safecrt.lib.
*
*       [Internal]
*
*Revision History:
*       08-03-04    AC   Created
*       09-27-04    ESC  Added _ISMBBLEADPREFIX macro
*       01-14-05    AC   Changed condition evalution for prefast
*
****/

#pragma once

#ifndef _INC_INTERNAL_SECURECRT
#define _INC_INTERNAL_SECURECRT

#include <internal.h>

/* string resetting */
#define _FILL_STRING _SECURECRT__FILL_STRING

#define _FILL_BYTE _SECURECRT__FILL_BYTE

#define _RESET_STRING(_String, _Size) \
    *(_String) = 0; \
    _FILL_STRING((_String), (_Size), 1);

/* validations */
#define _VALIDATE_STRING_ERROR(_String, _Size, _Ret) \
    _VALIDATE_RETURN((_String) != NULL && (_Size) > 0, EINVAL, (_Ret))

#define _VALIDATE_STRING(_String, _Size) \
    _VALIDATE_STRING_ERROR((_String), (_Size), EINVAL)

#define _VALIDATE_POINTER_ERROR_RETURN(_Pointer, _ErrorCode, _Ret) \
    _VALIDATE_RETURN((_Pointer) != NULL, (_ErrorCode), (_Ret))

#define _VALIDATE_POINTER_ERROR(_Pointer, _Ret) \
    _VALIDATE_POINTER_ERROR_RETURN((_Pointer), EINVAL, (_Ret))

#define _VALIDATE_POINTER(_Pointer) \
    _VALIDATE_POINTER_ERROR((_Pointer), EINVAL)

#define _VALIDATE_CONDITION_ERROR_RETURN(_Condition, _ErrorCode, _Ret) \
    _VALIDATE_RETURN((_Condition), (_ErrorCode), (_Ret))

#define _VALIDATE_CONDITION_ERROR(_Condition, _Ret) \
    _VALIDATE_CONDITION_ERROR_RETURN((_Condition), EINVAL, (_Ret))

#define _VALIDATE_POINTER_RESET_STRING_ERROR(_Pointer, _String, _Size, _Ret) \
    if ((_Pointer) == NULL) \
    { \
        _RESET_STRING((_String), (_Size)); \
        _VALIDATE_POINTER_ERROR_RETURN((_Pointer), EINVAL, (_Ret)) \
    }

#define _VALIDATE_POINTER_RESET_STRING(_Pointer, _String, _Size) \
    _VALIDATE_POINTER_RESET_STRING_ERROR((_Pointer), (_String), (_Size), EINVAL)

#define _RETURN_BUFFER_TOO_SMALL_ERROR(_String, _Size, _Ret) \
    _VALIDATE_RETURN((L"Buffer is too small" && 0), ERANGE, _Ret)

#define _RETURN_BUFFER_TOO_SMALL(_String, _Size) \
    _RETURN_BUFFER_TOO_SMALL_ERROR((_String), (_Size), ERANGE)

#define _RETURN_DEST_NOT_NULL_TERMINATED(_String, _Size) \
    _VALIDATE_RETURN((L"String is not null terminated" && 0), EINVAL, EINVAL)

#define _RETURN_EINVAL \
    _VALIDATE_RETURN((L"Invalid parameter", 0), EINVAL, EINVAL)

#define _RETURN_ERROR(_Msg, _Ret) \
    _VALIDATE_RETURN(((_Msg), 0), EINVAL, _Ret)

/* returns without calling _invalid_parameter */
#define _RETURN_NO_ERROR \
    return 0

/* Note that _RETURN_TRUNCATE does not set errno */
#define _RETURN_TRUNCATE \
    return STRUNCATE

#define _SET_MBCS_ERROR \
    (errno = EILSEQ)

#define _RETURN_MBCS_ERROR \
    return _SET_MBCS_ERROR

/* locale dependent */
#define _LOCALE_ARG \
    _LocInfo

#define _LOCALE_ARG_DECL \
    _locale_t _LOCALE_ARG

#define _LOCALE_UPDATE \
    _LocaleUpdate _LocUpdate(_LOCALE_ARG)

#define _ISMBBLEAD(_Character) \
    _ismbblead_l((_Character), _LocUpdate.GetLocaleT())

#define _MBSDEC(_String, _Current) \
    _mbsdec((_String), (_Current))

#define _ISMBBLEADPREFIX(_Result, _StringStart, _BytePtr)               \
    {                                                                   \
        unsigned char *_Tmp_VAR, *_StringStart_VAR, *_BytePtr_VAR;      \
                                                                        \
        _StringStart_VAR = (_StringStart);                              \
        _BytePtr_VAR = (_BytePtr);                                      \
        _Tmp_VAR = _BytePtr_VAR;                                        \
        while ((_Tmp_VAR >= _StringStart_VAR) && _ISMBBLEAD(*_Tmp_VAR)) \
        {                                                               \
            _Tmp_VAR--;                                                 \
        }                                                               \
        (_Result) = ((_BytePtr_VAR - _Tmp_VAR) & 1) != 0;               \
    }

#define _LOCALE_SHORTCUT_TEST \
    _LocUpdate.GetLocaleT()->mbcinfo->ismbcodepage == 0

#define _USE_LOCALE_ARG 1

/* misc */
#define _ASSIGN_IF_NOT_NULL(_Pointer, _Value) \
    if ((_Pointer) != NULL) \
    { \
        *(_Pointer) = (_Value); \
    }

#endif /* _INC_INTERNAL_SECURECRT */
