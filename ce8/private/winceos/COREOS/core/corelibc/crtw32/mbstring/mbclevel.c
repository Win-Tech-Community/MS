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
*mbclevel.c - Tests if char is hiragana, katakana, alphabet or digit.
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Tests for the various industry defined levels of Microsoft Kanji
*       Code.
*
*Revision History:
*       11-19-92  KRS   Ported from 16-bit sources.
*       09-24-93  CFW   Removed #ifdef _KANJI
*       09-29-93  CFW   Return false if not Kanji code page.
*       10-05-93  GJF   Replace _CRTAPI1 with __cdecl.
*       07-26-94  CFW   Update #14685, add 0xEA9F-0xEAA4 to JIS-Kanji level 2.
*       04-24-98  GJF   Implemented multithread support based on threadmbcinfo
*                       structs
*
*******************************************************************************/

#ifdef  _MBCS

#include <mtdll.h>
#include <cruntime.h>
#include <mbdata.h>
#include <mbstring.h>
#include <mbctype.h>
#include <locale.h>
#include <setlocal.h>


/***
*int _ismbcl0(c) - Tests if char is hiragana, katakana, alphabet or digit.
*
*Purpose:
*       Tests if a given char is hiragana, katakana, alphabet, digit or symbol
*       of Microsoft Kanji code.
*
*Entry:
*       unsigned int c - Character to test.
*
*Exit:
*       Returns non-zero if 0x8140 <= c <= 0x889E, else 0.
*
*Exceptions:
*
*******************************************************************************/

extern "C" int __cdecl _ismbcl0_l(
        unsigned int c,
        _locale_t plocinfo
        )
{
    _LocaleUpdate _loc_update(plocinfo);

    return( (_loc_update.GetLocaleT()->mbcinfo->mbcodepage == _KANJI_CP) && 
            (_ismbblead_l(c >> 8, _loc_update.GetLocaleT())) &&
            (_ismbbtrail_l(c & 0x0ff, _loc_update.GetLocaleT())) &&
            (c < 0x889f) );
}

extern "C" int (__cdecl _ismbcl0)(
        unsigned int c
        )
{
    return _ismbcl0_l(c, NULL);
}


/***
*int _ismbcl1(c) - Tests for 1st-level Microsoft Kanji code set.
*
*Purpose:
*       Tests if a given char belongs to Microsoft 1st-level Kanji code set.
*
*Entry:
*       unsigned int c - character to test.
*
*Exit:
*       Returns non-zero if 1st-level, else 0.
*
*Exceptions:
*
*******************************************************************************/

extern "C" int __cdecl _ismbcl1_l(
        unsigned int c,
        _locale_t plocinfo
        )
{
    _LocaleUpdate _loc_update(plocinfo);

    return( (_loc_update.GetLocaleT()->mbcinfo->mbcodepage == _KANJI_CP) && 
            (_ismbblead_l(c >> 8, _loc_update.GetLocaleT())) &&
            (_ismbbtrail_l(c & 0x0ff, _loc_update.GetLocaleT())) && 
            (c >= 0x889f) && (c <= 0x9872) );
}

extern "C" int (__cdecl _ismbcl1)(
    unsigned int c
    )
{
    return _ismbcl1_l(c, NULL);
}


/***
*int _ismbcl2(c) - Tests for a 2nd-level Microsoft Kanji code character.
*
*Purpose:
*       Tests if a given char belongs to the Microsoft 2nd-level Kanji code set.
*
*Entry:
*       unsigned int c - character to test.
*
*Exit:
*       Returns non-zero if 2nd-level, else 0.
*
*Exceptions:
*
*******************************************************************************/

extern "C" int __cdecl _ismbcl2_l(
        unsigned int c,
        _locale_t plocinfo
        )
{
    _LocaleUpdate _loc_update(plocinfo);

    return( (_loc_update.GetLocaleT()->mbcinfo->mbcodepage == _KANJI_CP) &&
            (_ismbblead_l(c >> 8, _loc_update.GetLocaleT())) &&
            (_ismbbtrail_l(c & 0x0ff, _loc_update.GetLocaleT())) &&
            (c >= 0x989f) && (c <= 0xEAA4) );
}
extern "C" int __cdecl _ismbcl2(
        unsigned int c
        )
{
    return _ismbcl2_l(c, NULL);
}

#endif  /* _MBCS */
