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
*mbsncmp.c - Compare n characters of two MBCS strings
*
*       Copyright (c) Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Compare n characters of two MBCS strings
*
*Revision History:
*       11-19-92  KRS   Ported from 16-bit sources.
*       10-05-93  GJF   Replaced _CRTAPI1 with __cdecl.
*       04-12-94  CFW   Make function generic.
*       04-15-93  CFW   Add _MB_CP_LOCK.
*       04-21-93  CFW   Update pointer.
*       05-05-94  CFW   Work around NT/Chico bug: CompareString ignores
*                       control characters.
*       05-09-94  CFW   Optimize for SBCS, no re-scan if CompareString fixed.
*       05-12-94  CFW   Back to hard-coded, CompareString sort is backwards.
*       05-19-94  CFW   Enable non-Win32.
*       09-11-97  GJF   Replaced __mbcodepage == 0 with _ISNOTMBCP.
*       04-15-98  GJF   Revised multithread support based on threadmbcinfo
*                       structs
*       10-09-03  AC    Added validation.
*
*******************************************************************************/

#ifdef  _MBCS

#include <mtdll.h>
#include <cruntime.h>
#include <mbdata.h>
#include <mbctype.h>
#include <string.h>
#include <mbstring.h>
#include <internal.h>
#include <locale.h>
#include <setlocal.h>

/***
*int mbsncmp(s1, s2, n) - Compare n characters of two MBCS strings
*
*Purpose:
*       Compares up to n charcters of two strings for lexical order.
*       Strings are compared on a character basis, not a byte basis.
*
*Entry:
*       unsigned char *s1, *s2 = strings to compare
*       size_t n = maximum number of characters to compare
*
*Exit:
*       Returns <0 if s1 < s2
*       Returns  0 if s1 == s2
*       Returns >0 if s1 > s2
*       Returns _NLSCMPERROR is something went wrong
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

extern "C" int __cdecl _mbsncmp_l(
        const unsigned char *s1,
        const unsigned char *s2,
        size_t n,
        _locale_t plocinfo
        )
{
        unsigned short c1, c2;
        _LocaleUpdate _loc_update(plocinfo);

        if (n==0)
            return(0);

        if (_loc_update.GetLocaleT()->mbcinfo->ismbcodepage == 0)
            return strncmp((const char *)s1, (const char *)s2, n);

        /* validation section */
        _VALIDATE_RETURN(s1 != NULL, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(s2 != NULL, EINVAL, _NLSCMPERROR);

        while (n--) {

            c1 = *s1++;
            if ( _ismbblead_l(c1, _loc_update.GetLocaleT()) )
                c1 = ( (*s1 == '\0') ? 0 : ((c1<<8) | *s1++) );

            c2 = *s2++;
            if ( _ismbblead_l(c2, _loc_update.GetLocaleT()) )
                c2 = ( (*s2 == '\0') ? 0 : ((c2<<8) | *s2++) );

            if (c1 != c2)
                return( (c1 > c2) ? 1 : -1);

            if (c1 == 0)
                return(0);
        }

        return(0);
}

extern "C" int (__cdecl _mbsncmp)(
        const unsigned char *s1,
        const unsigned char *s2,
        size_t n
        )
{
    return _mbsncmp_l(s1, s2, n, NULL);
}
#endif  /* _MBCS */
