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
*mbsnbicmp.c - Compare n bytes of strings, ignoring case (MBCS)
*
*       Copyright (c) Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Compare n bytes of strings, ignoring case (MBCS)
*
*Revision History:
*       08-03-93  KRS   Ported from 16-bit sources.
*       09-29-93  CFW   Merge _KANJI and _MBCS_OS
*       10-05-93  GJF   Replaced _CRTAPI1 with __cdecl.
*       10-12-93  CFW   Compare lower case, not upper.
*       04-12-94  CFW   Make function generic.
*       05-05-94  CFW   Work around NT/Chico bug: CompareString ignores
*                       control characters.
*       05-09-94  CFW   Return EQUAL when loop exits.
*       05-09-94  CFW   Optimize for SBCS, no re-scan if CompareString fixed.
*       05-12-94  CFW   Back to hard-coded, CompareString sort is backwards.
*       05-16-94  CFW   Use _mbbtolower/upper.
*       05-19-94  CFW   Enable non-Win32.
*       05-20-94  CFW   Update: if last char is LB, must still test values.
*       05-27-94  CFW   Last char LB should end string.
*       09-11-97  GJF   Replaced __mbcodepage == 0 with _ISNOTMBCP.
*       04-13-98  GJF   Revised multithread support based on threadmbcinfo
*                       structs
*       10-02-03  AC    Added validation.
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
* _mbsnbicmp - Compare n bytes of strings, ignoring case (MBCS)
*
*Purpose:
*       Compares up to n bytes of two strings for lexical order.
*       Strings are compared on a character basis, not a byte basis.
*       Case of characters is not considered.
*
*Entry:
*       unsigned char *s1, *s2 = strings to compare
*       size_t n = maximum number of bytes to compare
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

int __cdecl _mbsnbicmp_l(
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
            return _strnicmp((const char *)s1, (const char *)s2, n);

        /* validation section */
        _VALIDATE_RETURN(s1 != NULL, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(s2 != NULL, EINVAL, _NLSCMPERROR);

        while (n--) {

            c1 = *s1++;
            if ( _ismbblead_l(c1, _loc_update.GetLocaleT()) )
            {
                if (n==0)
                {
                    c1 = 0; /* 'naked' lead - end of string */
                    c2 = _ismbblead_l(*s2, _loc_update.GetLocaleT()) ? 0 : *s2;
                    goto test;
                }
                if (*s1 == '\0')
                    c1 = 0;
                else {
                    c1 = ((c1<<8) | *s1++);

                    if ( ((c1 >= _MBUPPERLOW1_MT(_loc_update.GetLocaleT())) && 
                          (c1 <= _MBUPPERHIGH1_MT(_loc_update.GetLocaleT()))) )
                        c1 += _MBCASEDIFF1_MT(_loc_update.GetLocaleT());
                    else if ( ((c1 >= _MBUPPERLOW2_MT(_loc_update.GetLocaleT())) && 
                               (c1 <= _MBUPPERHIGH2_MT(_loc_update.GetLocaleT()))) )
                        c1 += _MBCASEDIFF2_MT(_loc_update.GetLocaleT());
                }
            }
            else
                c1 = _mbbtolower_l(c1, _loc_update.GetLocaleT());

                c2 = *s2++;
                if ( _ismbblead_l(c2, _loc_update.GetLocaleT()) )
                {
                    if (n==0)
                    {
                        c2 = 0; /* 'naked' lead - end of string */
                        goto test;
                    }
                    n--;
                    if (*s2 == '\0')
                        c2 = 0;
                    else {
                        c2 = ((c2<<8) | *s2++);

                        if ( ((c2 >= _MBUPPERLOW1_MT(_loc_update.GetLocaleT())) && 
                              (c2 <= _MBUPPERHIGH1_MT(_loc_update.GetLocaleT()))) )
                            c2 += _MBCASEDIFF1_MT(_loc_update.GetLocaleT());
                        else if ( ((c2 >= _MBUPPERLOW2_MT(_loc_update.GetLocaleT())) && 
                                   (c2 <= _MBUPPERHIGH2_MT(_loc_update.GetLocaleT()))) )
                            c2 += _MBCASEDIFF2_MT(_loc_update.GetLocaleT());
                    }
                }
                else
                    c2 = _mbbtolower_l(c2, _loc_update.GetLocaleT());

test:
            if (c1 != c2)
                return( (c1 > c2) ? 1 : -1);

            if (c1 == 0)
                return(0);
        }

        return(0);
}

int (__cdecl _mbsnbicmp)(
        const unsigned char *s1,
        const unsigned char *s2,
        size_t n
        )
{
    return _mbsnbicmp_l(s1, s2, n, NULL);
}
#endif  /* _MBCS */
