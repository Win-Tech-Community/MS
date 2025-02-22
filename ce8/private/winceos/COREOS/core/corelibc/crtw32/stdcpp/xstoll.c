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
/* _Stoll function */
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "xmath.h"
_C_STD_BEGIN

#define MYMIN	(-_LLONG_MAX - _C2)	/* LLONG_MIN */
#define MYMAX	_LLONG_MAX	/* LLONG_MAX */

_CRTIMP2_PURE _ULonglong __CLRCALL_PURE_OR_CDECL _Stoullx(const char *, char **, int, int *);

_CRTIMP2_PURE _Longlong __CLRCALL_PURE_OR_CDECL _Stollx(const char * s, char ** endptr,
	int base, int *perr)
	{	/* convert string to long long, with checking */
	const char *sc;
	char *se, sign;
	_ULonglong x;

	if (endptr == 0)
		endptr = &se;
	for (sc = s; isspace((unsigned char)*sc); ++sc)
		;
	sign = (char)(*sc == '-' || *sc == '+' ? *sc++ : '+');
	x = _Stoullx(sc, endptr, base, perr);
	if (sc == *endptr)
		*endptr = (char *)s;
	if (s == *endptr && x != 0 || sign == '+' && MYMAX < x
		|| sign == '-' && 0 - (_ULonglong)MYMIN < x)
		{	/* overflow */
		errno = ERANGE;
		if (perr != 0)
			*perr = 1;
		return (sign == '-' ? MYMIN : MYMAX);
		}
	else
		return ((_Longlong)(sign == '-' ? 0 - x : x));
	}

_CRTIMP2_PURE _Longlong (__CLRCALL_PURE_OR_CDECL _Stoll)(const char * s, char ** endptr, int base)
	{	/* convert string, discard error code */
	return (_Stollx(s, endptr, base, 0));
	}
_C_STD_END

/*
 * Copyright (c) 1992-2007 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.03:0009 */
