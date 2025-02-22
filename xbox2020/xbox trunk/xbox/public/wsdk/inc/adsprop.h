//+----------------------------------------------------------------------------
//
//  Windows NT Active Directory Service Property Pages
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992-1999.
//
//  File:       adsprop.h
//
//  Contents:   Functions and definitions used in the creation of AD property
//              sheets.
//
//  History:    28-Sept-98 Eric Brown created.
//
//-----------------------------------------------------------------------------

#ifndef _ADSPROP_H_
#define _ADSPROP_H_

#if _MSC_VER > 1000
#pragma once
#endif
#ifdef __cplusplus
extern "C" {
#endif

#define WM_ADSPROP_NOTIFY_PAGEINIT   (WM_USER + 1101) // where LPARAM is the PADSPROPINITPARAMS pointer.
#define WM_ADSPROP_NOTIFY_PAGEHWND   (WM_USER + 1102) // where WPARAM => page's HWND
#define WM_ADSPROP_NOTIFY_CHANGE     (WM_USER + 1103) // used to send a change notification to a parent sheet
#define WM_ADSPROP_NOTIFY_APPLY      (WM_USER + 1104) // pages send this to the notification object.
#define WM_ADSPROP_NOTIFY_SETFOCUS   (WM_USER + 1105) // used internally by the notification object.
#define WM_ADSPROP_NOTIFY_FOREGROUND (WM_USER + 1106) // used internally by the notification object.
#define WM_ADSPROP_NOTIFY_EXIT       (WM_USER + 1107) // sent on page release

//+----------------------------------------------------------------------------
//
//  Structure:  ADSPROPINITPARAMS
//
//  Usage:      Used to pass page initialization information to new pages from
//              the notify object.
//
//-----------------------------------------------------------------------------
typedef struct _ADSPROPINITPARAMS {
    DWORD              dwSize;          // Set this to the size of the struct.
    DWORD              dwFlags;         // Reserved for future use.
    HRESULT            hr;              // If this is non-zero, then the others
    IDirectoryObject * pDsObj;          // should be ignored.
    LPWSTR             pwzCN;
    PADS_ATTR_INFO     pWritableAttrs;
} ADSPROPINITPARAMS, * PADSPROPINITPARAMS;

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropCreateNotifyObj
//
//  Synopsis:   Checks to see if the notification window/object exists for this
//              sheet instance and if not creates it.
//
//  Arguments:  [pAppThdDataObj] - the unmarshalled data object pointer.
//              [pwzADsObjName]  - object path name.
//              [phNotifyObj]    - to return the notificion window handle.
//
//  Returns:    HRESULTs.
//
//-----------------------------------------------------------------------------
STDAPI
ADsPropCreateNotifyObj(LPDATAOBJECT pAppThdDataObj, PWSTR pwzADsObjName,
                       HWND * phNotifyObj);

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropGetInitInfo
//
//  Synopsis:   Pages call this at their init time to retreive DS object info.
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [pInitParams] - struct filled in with DS object info. This
//                              struct must be allocated by the caller before
//                              the call.
//
//  Returns:    FALSE if the notify window has gone away for some reason or
//              if the parameters are invalid.
//
//  Notes:      This call results in the sending of the
//              WM_ADSPROP_NOTIFY_PAGEINIT message to the notify window.
//              pInitParams->pWritableAttrs can be NULL if there are no
//              writable attributes.
//
//-----------------------------------------------------------------------------
STDAPI_(BOOL)
ADsPropGetInitInfo(HWND hNotifyObj, PADSPROPINITPARAMS pInitParams);

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropSetHwnd
//
//  Synopsis:   Pages call this at their dialog init time to send their hwnd.
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [hPage]       - the page's window handle.
//
//  Returns:    FALSE if the notify window has gone away for some reason.
//
//  Notes:      Sends the WM_ADSPROP_NOTIFY_PAGEHWND message to the notify
//              window.
//
//-----------------------------------------------------------------------------
STDAPI_(BOOL)
ADsPropSetHwnd(HWND hNotifyObj, HWND hPage);

//+----------------------------------------------------------------------------
//
//  function:   ADsPropCheckIfWritable
//
//  Synopsis:   See if the attribute is writable by checking if it is in
//              the allowedAttributesEffective array.
//
//  Arguments:  [pwzAttr]        - the attribute name.
//              [pWritableAttrs] - the array of writable attributes.
//
//  Returns:    FALSE if the attribute name is not found in the writable-attrs
//              array or if the array pointer is NULL.
//
//-----------------------------------------------------------------------------
STDAPI_(BOOL)
ADsPropCheckIfWritable(const PWSTR pwzAttr, const PADS_ATTR_INFO pWritableAttrs);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _ADSPROP_H_
