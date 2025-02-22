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
/* _FSinh function */
#include "xmath.h"
_C_STD_BEGIN

/* coefficients */
#define NP	(sizeof (p) / sizeof (p[0]) - 1)
static const float p[] = {	/* courtesy Dr. Tim Prince */
	0.00020400F,
	0.00832983F,
	0.16666737F,
	0.99999998F};

_CRTIMP2_PURE float __CLRCALL_PURE_OR_CDECL _FSinh(float x, float y)
	{	/* compute y*sinh(x), |y| <= 1 */
	short neg;

	switch (_FDtest(&x))
		{	/* test for special codes */
	case _NANCODE:
		return (x);
	case _INFCODE:
		return (y != 0.0F ? x : FSIGN(x) ? -y : y);
	case 0:
		return (x * y);
	default:	/* finite */
		if (y == 0.0F)
			return (x < 0.0F ? -y : y);
		if (x < 0.0F)
			x = -x, neg = 1;
		else
			neg = 0;

		if (x < _FRteps._Float)
			x *= y;	/* x tiny */
		else if (x < 1.0F)
			{
			float w = x * x;

			x += ((p[0] * w + p[1]) * w + p[2]) * w * x;
			x *= y;
			}
		else if (x < _FXbig)
			{	/* worth adding in exp(-x) */
			_FExp(&x, 1.0F, -1);
			x = y * (x - 0.25F / x);
			}
		else
			switch (_FExp(&x, y, -1))
				{	/* report over/underflow */
			case 0:
				_Feraise(_FE_UNDERFLOW);
				break;
			case _INFCODE:
				_Feraise(_FE_OVERFLOW);
				}
		return (neg ? -x : x);
		}
	}
#undef NP
_C_STD_END

/*
 * Copyright (c) 1992-2007 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.03:0009 */
