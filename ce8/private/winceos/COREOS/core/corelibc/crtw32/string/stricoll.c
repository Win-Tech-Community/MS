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
*stricoll.c - Collate locale strings without regard to case
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Compare two strings using the locale LC_COLLATE information.
*
*Revision History:
*       10-16-91  ETC   Created from strcoll.c
*       12-08-91  ETC   Remove availability under !_INTL; updated api; add mt.
*       04-06-92  KRS   Make work without _INTL switches too.
*       08-19-92  KRS   Activate NLS support.
*       09-02-92  SRW   Get _INTL definition via ..\crt32.def
*       12-16-92  KRS   Optimize for CompareStringW  by using -1 for string len.
*       04-06-93  SKS   Replace _CRTAPI* with __cdecl
*       04-14-93  CFW   Error sets errno, cleanup.
*       06-02-93  SRW   ignore _INTL if _NTSUBSET_ defined.
*       09-15-93  CFW   Use ANSI conformant "__" names.
*       09-22-93  CFW   Use __crtxxx internal NLS API wrapper.
*       09-29-93  GJF   Merged NT SDK and Cuda versions.
*       11-09-93  CFW   Use LC_COLLATE code page for __crtxxx() conversion.
*       04-11-93  CFW   Change NLSCMPERROR to _NLCMPERROR.
*       09-06-94  CFW   Remove _INTL switch.
*       10-24-94  GJF   Sped up C locale, multi-thread case.
*       12-29-94  CFW   Merge non-Win32.
*       09-26-95  GJF   New locking macro, and scheme, for functions which
*                       reference the locale.
*       10-30-95  GJF   Specify SORT_STRINGSORT to CompareString.
*       11-25-95  BWT   stricmp simply calls strcmpi... Use strcmpi instead.
*       07-16-96  SKS   Added missing call to _unlock_locale()
*       11-24-97  GJF   Removed bogus codepage determination.
*       01-12-98  GJF   Use _lc_collate_cp codepage.
*       08-11-98  GJF   Revised multithread support based on threadlocinfo
*                       struct.
*       05-17-99  PML   Remove all Macintosh support.
*       11-12-01  GB    Added support for new locale implementation.
*       10-06-03  AC    Added validation.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <errno.h>
#include <awint.h>
#include <string.h>
#include <internal.h>
#include <windows.h>
#include <mtdll.h>
#include <setlocal.h>

/***
*int _stricoll() - Collate locale strings without regard to case
*
*Purpose:
*       Compare two strings using the locale LC_COLLATE information
*       without regard to case.
*
*Entry:
*       const char *s1 = pointer to the first string
*       const char *s2 = pointer to the second string
*
*Exit:
*       Less than 0    = first string less than second string
*       0              = strings are equal
*       Greater than 0 = first string greater than second string
*       Returns _NLSCMPERROR is something went wrong
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

extern "C" int __cdecl _stricoll_l (
        const char *_string1,
        const char *_string2,
        _locale_t plocinfo
        )
{
    int ret;
    _LocaleUpdate _loc_update(plocinfo);

    /* validation section */
    _VALIDATE_RETURN(_string1 != NULL, EINVAL, _NLSCMPERROR);
    _VALIDATE_RETURN(_string2 != NULL, EINVAL, _NLSCMPERROR);

    if ( _loc_update.GetLocaleT()->locinfo->locale_name[LC_COLLATE] == NULL )
    {
        return _stricmp(_string1, _string2);
    }

    if ( 0 == (ret = __crtCompareStringA(_loc_update.GetLocaleT(),
                    _loc_update.GetLocaleT()->locinfo->locale_name[LC_COLLATE],
                    SORT_STRINGSORT | NORM_IGNORECASE,
                    _string1,
                    -1,
                    _string2,
                    -1,
                    _loc_update.GetLocaleT()->locinfo->lc_collate_cp)) )
    {
        errno = EINVAL;
        return _NLSCMPERROR;
    }

    return (ret - 2);

}

extern "C" int __cdecl _stricoll (
        const char *_string1,
        const char *_string2
        )
{
#if     !defined(_NTSUBSET_)
    if (__locale_changed == 0)
    {
        return _stricmp(_string1, _string2);
    }
    else
    {
        return _stricoll_l(_string1, _string2, NULL);
    }

#else
    return _strcmpi(_string1, _string2);
#endif
}
