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
/* _Dscale function -- IEEE 754 version */
#include "xmath.h"
_C_STD_BEGIN

_CRTIMP2_PURE short __CLRCALL_PURE_OR_CDECL _Dscale(double *px, long lexp)
	{	/* scale *px by 2^xexp with checking */
	_Dval *ps = (_Dval *)(char *)px;
	short xchar = (short)((ps->_Sh[_D0] & _DMASK) >> _DOFF);

	if (xchar == _DMAX)
		return ((short)((ps->_Sh[_D0] & _DFRAC) != 0 || ps->_Sh[_D1] != 0
			|| ps->_Sh[_D2] != 0 || ps->_Sh[_D3] != 0 ? _NANCODE : _INFCODE));
	else if (xchar == 0 && 0 < (xchar = _Dnorm(ps)))
		return (0);

	if (0 < lexp && _DMAX - xchar <= lexp)
		{	/* overflow, return +/-INF */
		*px = ps->_Sh[_D0] & _DSIGN ? -_Inf._Double : _Inf._Double;
		return (_INFCODE);
		}
	else if (-xchar < lexp)
		{	/* finite result, repack */
		ps->_Sh[_D0] = (unsigned short)(ps->_Sh[_D0] & ~_DMASK
			| (lexp + xchar) << _DOFF);
		return (_FINITE);
		}
	else
		{	/* denormalized, scale */
		unsigned short sign = (unsigned short)(ps->_Sh[_D0] & _DSIGN);

		ps->_Sh[_D0] = (unsigned short)(1 << _DOFF | ps->_Sh[_D0] & _DFRAC);
		lexp += xchar - 1;
		if (lexp < -(48 + 1 + _DOFF) || 0 <= lexp)
			{	/* certain underflow, return +/-0 */
			ps->_Sh[_D0] = sign;
			ps->_Sh[_D1] = 0;
			ps->_Sh[_D2] = 0;
			ps->_Sh[_D3] = 0;
			return (0);
			}
		else
			{	/* nonzero, align fraction */
			short xexp = (short)lexp;
			unsigned short psx = 0;

			for (; xexp <= -16; xexp += 16)
				{	/* scale by words */
				psx = ps->_Sh[_D3] | (psx != 0 ? 1 : 0);
				ps->_Sh[_D3] = ps->_Sh[_D2];
				ps->_Sh[_D2] = ps->_Sh[_D1];
				ps->_Sh[_D1] = ps->_Sh[_D0];
				ps->_Sh[_D0] = 0;
				}
			if ((xexp = (short)-xexp) != 0)
				{	/* scale by bits */
				psx = (ps->_Sh[_D3] << (16 - xexp)) | (psx != 0 ? 1 : 0);
				ps->_Sh[_D3] = (unsigned short)(ps->_Sh[_D3] >> xexp
					| ps->_Sh[_D2] << (16 - xexp));
				ps->_Sh[_D2] = (unsigned short)(ps->_Sh[_D2] >> xexp
					| ps->_Sh[_D1] << (16 - xexp));
				ps->_Sh[_D1] = (unsigned short)(ps->_Sh[_D1] >> xexp
					| ps->_Sh[_D0] << (16 - xexp));
				ps->_Sh[_D0] >>= xexp;
				}

			ps->_Sh[_D0] |= sign;
			if ((0x8000 < psx || 0x8000 == psx && (ps->_Sh[_D3] & 0x0001) != 0)
				&& (++ps->_Sh[_D3] & 0xffff) == 0
				&& (++ps->_Sh[_D2] & 0xffff) == 0
				&& (++ps->_Sh[_D1] & 0xffff) == 0)
				++ps->_Sh[_D0];	/* round up */
			else if (ps->_Sh[_D0] == sign && ps->_Sh[_D1] == 0
				&& ps->_Sh[_D2] == 0 && ps->_Sh[_D3] == 0)
				return (0);
			return (_FINITE);
			}
		}
	}
_C_STD_END

/*
 * Copyright (c) 1992-2007 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.03:0009 */
