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
// xlocale -- class locale exotic char member functions
#include <istream>
#include <locale>
#include <xdebug>
_STD_BEGIN

 #pragma warning(disable: 4786)

 #pragma warning(disable: 4074)
 #pragma init_seg(compiler)

typedef char_traits<char> _Traits;
typedef istreambuf_iterator<char, _Traits> _Initer;
typedef ostreambuf_iterator<char, _Traits> _Outiter;

	// facets associated with C categories
#define ADDFAC(Facet, cat, ptrimp, ptrloc) \
	if ((_CATMASK(Facet::_Getcat()) & cat) == 0) \
		; \
	else if (ptrloc == 0) \
		ptrimp->_Addfac(_NEW_CRT Facet(lobj), Facet::id); \
	else \
		ptrimp->_Addfac((locale::facet *)&_USE(*ptrloc, Facet), Facet::id);

// moved from locale to ease subsetting
typedef collate<char> _T5;
typedef messages<char> _T6;
typedef money_get<char, _Initer> _T7;
typedef money_put<char, _Outiter> _T9;
typedef moneypunct<char, false> _T11;
typedef moneypunct<char, true> _T12;
typedef time_get<char, _Initer> _T13;
typedef time_put<char, _Outiter> _T14;


void __CLRCALL_OR_CDECL locale::_Locimp::_Makexloc(const _Locinfo& lobj,
	locale::category cat, _Locimp *ptrimp, const locale *ptrloc)
	{	// setup exotic char part of a new locale
	ADDFAC(_T5, cat, ptrimp, ptrloc);
	ADDFAC(_T6, cat, ptrimp, ptrloc);
	ADDFAC(_T7, cat, ptrimp, ptrloc);
	ADDFAC(_T9, cat, ptrimp, ptrloc);
	ADDFAC(_T11, cat, ptrimp, ptrloc);
	ADDFAC(_T12, cat, ptrimp, ptrloc);
	ADDFAC(_T13, cat, ptrimp, ptrloc);
	ADDFAC(_T14, cat, ptrimp, ptrloc);
	}
_STD_END

/*
 * Copyright (c) 1992-2007 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.03:0009 */
