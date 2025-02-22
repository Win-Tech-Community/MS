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
*wcscoll.c - Collate wide-character locale strings
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Compare two wchar_t strings using the locale LC_COLLATE information.
*
*Revision History:
*       09-09-91  ETC   Created from strcoll.c.
*       04-06-92  KRS   Make work without _INTL also.
*       08-19-92  KRS   Activate NLS support.
*       09-02-92  SRW   Get _INTL definition via ..\crt32.def
*       04-06-93  SKS   Replace _CRTAPI* with __cdecl
*       04-14-93  CFW   Error sets errno, cleanup.
*       06-02-93  SRW   ignore _INTL if _NTSUBSET_ defined.
*       09-15-93  CFW   Use ANSI conformant "__" names.
*       09-22-93  CFW   Use __crtxxx internal NLS API wrapper.
*       09-29-93  GJF   Merged NT SDK and Cuda versions.
*       11-09-93  CFW   Use LC_COLLATE code page for __crtxxx() conversion.
*       02-07-94  CFW   POSIXify.
*       04-11-93  CFW   Change NLSCMPERROR to _NLCMPERROR.
*       09-06-94  CFW   Remove _INTL switch.
*       10-25-94  GJF   Sped up C locale, multi-thread case.
*       09-26-95  GJF   New locking macro, and scheme, for functions which
*                       reference the locale.
*       10-30-95  GJF   Specify SORT_STRINGSORT to CompareString.
*       07-16-96  SKS   Added missing call to _unlock_locale()
*       11-24-97  GJF   Removed bogus codepage determination.
*       01-12-98  GJF   Use _lc_collate_cp codepage.
*       08-12-98  GJF   Revised multithread support based on threadlocinfo
*                       struct.
*       11-12-01  GB    Added support for new locale implementation.
*       10-08-03  AC    Added validation.
*       10-08-04  AGH   Added validations to wcscoll
*
*******************************************************************************/

#ifndef _POSIX_

#include <cruntime.h>
#include <internal.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <errno.h>
#include <awint.h>
#include <mtdll.h>
#include <setlocal.h>

/***
*int wcscoll() - Collate wide-character locale strings
*
*Purpose:
*       Compare two wchar_t strings using the locale LC_COLLATE information.
*       In the C locale, wcscmp() is used to make the comparison.
*
*Entry:
*       const wchar_t *s1 = pointer to the first string
*       const wchar_t *s2 = pointer to the second string
*
*Exit:
*       -1 = first string less than second string
*        0 = strings are equal
*        1 = first string greater than second string
*       Returns _NLSCMPERROR is something went wrong
*       This range of return values may differ from other *cmp/*coll functions.
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

extern "C" int __cdecl _wcscoll_l (
        const wchar_t *_string1,
        const wchar_t *_string2,
        _locale_t plocinfo
        )
{
    int ret;
    _LocaleUpdate _loc_update(plocinfo);

    /* validation section */
    _VALIDATE_RETURN(_string1 != NULL, EINVAL, _NLSCMPERROR);
    _VALIDATE_RETURN(_string2 != NULL, EINVAL, _NLSCMPERROR);

    if ( _loc_update.GetLocaleT()->locinfo->locale_name[LC_COLLATE] == NULL )
        return (wcscmp(_string1, _string2));

    if ( 0 == (ret = __crtCompareStringW(
                    _loc_update.GetLocaleT()->locinfo->locale_name[LC_COLLATE],
                    SORT_STRINGSORT,
                    _string1,
                    -1,
                    _string2,
                    -1)) ) 
    {
        errno = EINVAL;
        return _NLSCMPERROR;
    }

    return (ret - 2);

}

extern "C" int __cdecl wcscoll (
        const wchar_t *_string1,
        const wchar_t *_string2
        )
{
#if     !defined(_NTSUBSET_)
    if (__locale_changed == 0)
    {
        /* validation section */
        _VALIDATE_RETURN(_string1 != NULL, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(_string2 != NULL, EINVAL, _NLSCMPERROR);

        return (wcscmp(_string1, _string2));
    }
    else
    {
        return _wcscoll_l(_string1, _string2, NULL);
    }
#else
    return wcscmp(_string1, _string2);
#endif
}
#endif /* _POSIX_ */
