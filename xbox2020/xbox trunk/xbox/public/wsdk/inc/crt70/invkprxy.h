/***
* invkprxy.h - Native C++ compiler COM support - IDispatch::Invoke helpers
*
*   Copyright (C) 1996-2000 Microsoft Corporation
*   All rights reserved.
*
****/

#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(_INC_INVKPRXY)
#define _INC_INVKPRXY 1

HRESULT __stdcall _com_handle_excepinfo(EXCEPINFO& excepInfo, IErrorInfo** pperrinfo);
HRESULT __cdecl _com_invoke_helper(IDispatch* pDispatch,
                                DISPID dwDispID,
                                WORD wFlags,
                                VARTYPE vtRet,
                                void* pvRet,
                                const wchar_t* pwParamInfo,
                                va_list argList,
                                IErrorInfo** pperrinfo);
HRESULT __cdecl _com_dispatch_raw_method(IDispatch* pDispatch,
                                DISPID dwDispID,
                                WORD wFlags,
                                VARTYPE vtRet,
                                void* pvRet,
                                const wchar_t* pwParamInfo,
                                ...);
HRESULT __stdcall _com_dispatch_raw_propget(IDispatch* pDispatch,
                                DISPID dwDispID,
                                VARTYPE vtProp,
                                void* pvProp);
HRESULT __cdecl _com_dispatch_raw_propput(IDispatch* pDispatch,
                                DISPID dwDispID,
                                VARTYPE vtProp,
                                ...);

#endif // _INC_INVKPRXY
