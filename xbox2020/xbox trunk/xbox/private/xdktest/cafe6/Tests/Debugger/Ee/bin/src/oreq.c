/* The Plum Hall Validation Suite for C
 * Unpublished copyright (c) 1986-1991, Chiron Systems Inc and Plum Hall Inc.
 * VERSION: 3
 * DATE:    91/07/01
 * The "ANSI" mode of the Suite corresponds to the official ANSI C, X3.159-1989.
 * As per your license agreement, your distribution is not to be moved or copied outside the Designated Site
 * without specific permission from Plum Hall Inc.
 */

#include <windows.h>
#include "types.h"

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lszCmdLine, int nCmdShow)

	{
	typedef union {
		CHAR c;
		SHORT s;
		INT i;
		UCHAR uc;
		USHORT us;
		UINT ui;
		LONG l;
		ULONG ul;
		FLOAT f;
		DOUBLE d;
		SCHAR sc;
		LDOUBLE ld;
		} D;
	auto D D1;
	auto D D2;
	auto D D3;
	auto D D4;
	auto D D5;
	auto D D6;
	auto D D7;
	auto D D8;
	auto D D9;
	auto D D10;
	auto D D11;
	auto D D12;
	D1.c = 7;
	D2.sc = 8;
	D3.s = 9;
	D4.i = 10;
	D5.uc = 11;
	D6.us = 12;
	D7.ui = 13;
	D8.l = 14;
	D9.ul = 15;
	D10.f = 16;
	D11.d = 17;
	D12.ld = 18;
	{
	typedef union {
		CHAR c;
		SHORT s;
		INT i;
		UCHAR uc;
		USHORT us;
		UINT ui;
		LONG l;
		ULONG ul;
		FLOAT f;
		DOUBLE d;
		SCHAR sc;
		LDOUBLE ld;
		} E;
	auto E E1, *pE1 = &E1;
	auto E E2, *pE2 = &E2;
	auto E E3, *pE3 = &E3;
	auto E E4, *pE4 = &E4;
	auto E E5, *pE5 = &E5;
	auto E E6, *pE6 = &E6;
	auto E E7, *pE7 = &E7;
	auto E E8, *pE8 = &E8;
	auto E E9, *pE9 = &E9;
	auto E E10, *pE10 = &E10;
	auto E E11, *pE11 = &E11;
	auto E E12, *pE12 = &E12;
	pE1->c = 7;
	pE2->sc = 8;
	pE3->s = 9;
	pE4->i = 10;
	pE5->uc = 11;
	pE6->us = 12;
	pE7->ui = 13;
	pE8->l = 14;
	pE9->ul = 15;
	pE10->f = 16;
	pE11->d = 17;
	pE12->ld = 18;
	{
	D1.c = 7; pE1->c = 7;
	D1.c |= pE1->c;

	break_here:

	D1.c = 7;
	pE1->c = 7; D1.c = 7;
	pE1->c |= D1.c;
	pE1->c = 7;
	D1.c = 7; pE2->sc = 8;
	D1.c |= pE2->sc;
	D1.c = 7;
	pE2->sc = 8; D1.c = 7;
	pE2->sc |= D1.c;
	pE2->sc = 8;
	D1.c = 7; pE3->s = 9;
	D1.c |= pE3->s;
	D1.c = 7;
	pE3->s = 9; D1.c = 7;
	pE3->s |= D1.c;
	pE3->s = 9;
	D1.c = 7; pE4->i = 10;
	D1.c |= pE4->i;
	D1.c = 7;
	pE4->i = 10; D1.c = 7;
	pE4->i |= D1.c;
	pE4->i = 10;
	D1.c = 7; pE5->uc = 11;
	D1.c |= pE5->uc;
	D1.c = 7;
	pE5->uc = 11; D1.c = 7;
	pE5->uc |= D1.c;
	pE5->uc = 11;
	D1.c = 7; pE6->us = 12;
	D1.c |= pE6->us;
	D1.c = 7;
	pE6->us = 12; D1.c = 7;
	pE6->us |= D1.c;
	pE6->us = 12;
	D1.c = 7; pE7->ui = 13;
	D1.c |= pE7->ui;
	D1.c = 7;
	pE7->ui = 13; D1.c = 7;
	pE7->ui |= D1.c;
	pE7->ui = 13;
	D1.c = 7; pE8->l = 14;
	D1.c |= pE8->l;
	D1.c = 7;
	pE8->l = 14; D1.c = 7;
	pE8->l |= D1.c;
	pE8->l = 14;
	D1.c = 7; pE9->ul = 15;
	D1.c |= pE9->ul;
	D1.c = 7;
	pE9->ul = 15; D1.c = 7;
	pE9->ul |= D1.c;
	pE9->ul = 15;
	D2.sc = 8; pE1->c = 7;
	D2.sc |= pE1->c;
	D2.sc = 8;
	pE1->c = 7; D2.sc = 8;
	pE1->c |= D2.sc;
	pE1->c = 7;
	D2.sc = 8; pE2->sc = 8;
	D2.sc |= pE2->sc;
	D2.sc = 8;
	pE2->sc = 8; D2.sc = 8;
	pE2->sc |= D2.sc;
	pE2->sc = 8;
	D2.sc = 8; pE3->s = 9;
	D2.sc |= pE3->s;
	D2.sc = 8;
	pE3->s = 9; D2.sc = 8;
	pE3->s |= D2.sc;
	pE3->s = 9;
	D2.sc = 8; pE4->i = 10;
	D2.sc |= pE4->i;
	D2.sc = 8;
	pE4->i = 10; D2.sc = 8;
	pE4->i |= D2.sc;
	pE4->i = 10;
	D2.sc = 8; pE5->uc = 11;
	D2.sc |= pE5->uc;
	D2.sc = 8;
	pE5->uc = 11; D2.sc = 8;
	pE5->uc |= D2.sc;
	pE5->uc = 11;
	D2.sc = 8; pE6->us = 12;
	D2.sc |= pE6->us;
	D2.sc = 8;
	pE6->us = 12; D2.sc = 8;
	pE6->us |= D2.sc;
	pE6->us = 12;
	D2.sc = 8; pE7->ui = 13;
	D2.sc |= pE7->ui;
	D2.sc = 8;
	pE7->ui = 13; D2.sc = 8;
	pE7->ui |= D2.sc;
	pE7->ui = 13;
	D2.sc = 8; pE8->l = 14;
	D2.sc |= pE8->l;
	D2.sc = 8;
	pE8->l = 14; D2.sc = 8;
	pE8->l |= D2.sc;
	pE8->l = 14;
	D2.sc = 8; pE9->ul = 15;
	D2.sc |= pE9->ul;
	D2.sc = 8;
	pE9->ul = 15; D2.sc = 8;
	pE9->ul |= D2.sc;
	pE9->ul = 15;
	D3.s = 9; pE1->c = 7;
	D3.s |= pE1->c;
	D3.s = 9;
	pE1->c = 7; D3.s = 9;
	pE1->c |= D3.s;
	pE1->c = 7;
	D3.s = 9; pE2->sc = 8;
	D3.s |= pE2->sc;
	D3.s = 9;
	pE2->sc = 8; D3.s = 9;
	pE2->sc |= D3.s;
	pE2->sc = 8;
	D3.s = 9; pE3->s = 9;
	D3.s |= pE3->s;
	D3.s = 9;
	pE3->s = 9; D3.s = 9;
	pE3->s |= D3.s;
	pE3->s = 9;
	D3.s = 9; pE4->i = 10;
	D3.s |= pE4->i;
	D3.s = 9;
	pE4->i = 10; D3.s = 9;
	pE4->i |= D3.s;
	pE4->i = 10;
	D3.s = 9; pE5->uc = 11;
	D3.s |= pE5->uc;
	D3.s = 9;
	pE5->uc = 11; D3.s = 9;
	pE5->uc |= D3.s;
	pE5->uc = 11;
	D3.s = 9; pE6->us = 12;
	D3.s |= pE6->us;
	D3.s = 9;
	pE6->us = 12; D3.s = 9;
	pE6->us |= D3.s;
	pE6->us = 12;
	D3.s = 9; pE7->ui = 13;
	D3.s |= pE7->ui;
	D3.s = 9;
	pE7->ui = 13; D3.s = 9;
	pE7->ui |= D3.s;
	pE7->ui = 13;
	D3.s = 9; pE8->l = 14;
	D3.s |= pE8->l;
	D3.s = 9;
	pE8->l = 14; D3.s = 9;
	pE8->l |= D3.s;
	pE8->l = 14;
	D3.s = 9; pE9->ul = 15;
	D3.s |= pE9->ul;
	D3.s = 9;
	pE9->ul = 15; D3.s = 9;
	pE9->ul |= D3.s;
	pE9->ul = 15;
	D4.i = 10; pE1->c = 7;
	D4.i |= pE1->c;
	D4.i = 10;
	pE1->c = 7; D4.i = 10;
	pE1->c |= D4.i;
	pE1->c = 7;
	D4.i = 10; pE2->sc = 8;
	D4.i |= pE2->sc;
	D4.i = 10;
	pE2->sc = 8; D4.i = 10;
	pE2->sc |= D4.i;
	pE2->sc = 8;
	D4.i = 10; pE3->s = 9;
	D4.i |= pE3->s;
	D4.i = 10;
	pE3->s = 9; D4.i = 10;
	pE3->s |= D4.i;
	pE3->s = 9;
	D4.i = 10; pE4->i = 10;
	D4.i |= pE4->i;
	D4.i = 10;
	pE4->i = 10; D4.i = 10;
	pE4->i |= D4.i;
	pE4->i = 10;
	D4.i = 10; pE5->uc = 11;
	D4.i |= pE5->uc;
	D4.i = 10;
	pE5->uc = 11; D4.i = 10;
	pE5->uc |= D4.i;
	pE5->uc = 11;
	D4.i = 10; pE6->us = 12;
	D4.i |= pE6->us;
	D4.i = 10;
	pE6->us = 12; D4.i = 10;
	pE6->us |= D4.i;
	pE6->us = 12;
	D4.i = 10; pE7->ui = 13;
	D4.i |= pE7->ui;
	D4.i = 10;
	pE7->ui = 13; D4.i = 10;
	pE7->ui |= D4.i;
	pE7->ui = 13;
	D4.i = 10; pE8->l = 14;
	D4.i |= pE8->l;
	D4.i = 10;
	pE8->l = 14; D4.i = 10;
	pE8->l |= D4.i;
	pE8->l = 14;
	D4.i = 10; pE9->ul = 15;
	D4.i |= pE9->ul;
	D4.i = 10;
	pE9->ul = 15; D4.i = 10;
	pE9->ul |= D4.i;
	pE9->ul = 15;
	D5.uc = 11; pE1->c = 7;
	D5.uc |= pE1->c;
	D5.uc = 11;
	pE1->c = 7; D5.uc = 11;
	pE1->c |= D5.uc;
	pE1->c = 7;
	D5.uc = 11; pE2->sc = 8;
	D5.uc |= pE2->sc;
	D5.uc = 11;
	pE2->sc = 8; D5.uc = 11;
	pE2->sc |= D5.uc;
	pE2->sc = 8;
	D5.uc = 11; pE3->s = 9;
	D5.uc |= pE3->s;
	D5.uc = 11;
	pE3->s = 9; D5.uc = 11;
	pE3->s |= D5.uc;
	pE3->s = 9;
	D5.uc = 11; pE4->i = 10;
	D5.uc |= pE4->i;
	D5.uc = 11;
	pE4->i = 10; D5.uc = 11;
	pE4->i |= D5.uc;
	pE4->i = 10;
	D5.uc = 11; pE5->uc = 11;
	D5.uc |= pE5->uc;
	D5.uc = 11;
	pE5->uc = 11; D5.uc = 11;
	pE5->uc |= D5.uc;
	pE5->uc = 11;
	D5.uc = 11; pE6->us = 12;
	D5.uc |= pE6->us;
	D5.uc = 11;
	pE6->us = 12; D5.uc = 11;
	pE6->us |= D5.uc;
	pE6->us = 12;
	D5.uc = 11; pE7->ui = 13;
	D5.uc |= pE7->ui;
	D5.uc = 11;
	pE7->ui = 13; D5.uc = 11;
	pE7->ui |= D5.uc;
	pE7->ui = 13;
	D5.uc = 11; pE8->l = 14;
	D5.uc |= pE8->l;
	D5.uc = 11;
	pE8->l = 14; D5.uc = 11;
	pE8->l |= D5.uc;
	pE8->l = 14;
	D5.uc = 11; pE9->ul = 15;
	D5.uc |= pE9->ul;
	D5.uc = 11;
	pE9->ul = 15; D5.uc = 11;
	pE9->ul |= D5.uc;
	pE9->ul = 15;
	D6.us = 12; pE1->c = 7;
	D6.us |= pE1->c;
	D6.us = 12;
	pE1->c = 7; D6.us = 12;
	pE1->c |= D6.us;
	pE1->c = 7;
	D6.us = 12; pE2->sc = 8;
	D6.us |= pE2->sc;
	D6.us = 12;
	pE2->sc = 8; D6.us = 12;
	pE2->sc |= D6.us;
	pE2->sc = 8;
	D6.us = 12; pE3->s = 9;
	D6.us |= pE3->s;
	D6.us = 12;
	pE3->s = 9; D6.us = 12;
	pE3->s |= D6.us;
	pE3->s = 9;
	D6.us = 12; pE4->i = 10;
	D6.us |= pE4->i;
	D6.us = 12;
	pE4->i = 10; D6.us = 12;
	pE4->i |= D6.us;
	pE4->i = 10;
	D6.us = 12; pE5->uc = 11;
	D6.us |= pE5->uc;
	D6.us = 12;
	pE5->uc = 11; D6.us = 12;
	pE5->uc |= D6.us;
	pE5->uc = 11;
	D6.us = 12; pE6->us = 12;
	D6.us |= pE6->us;
	D6.us = 12;
	pE6->us = 12; D6.us = 12;
	pE6->us |= D6.us;
	pE6->us = 12;
	D6.us = 12; pE7->ui = 13;
	D6.us |= pE7->ui;
	D6.us = 12;
	pE7->ui = 13; D6.us = 12;
	pE7->ui |= D6.us;
	pE7->ui = 13;
	D6.us = 12; pE8->l = 14;
	D6.us |= pE8->l;
	D6.us = 12;
	pE8->l = 14; D6.us = 12;
	pE8->l |= D6.us;
	pE8->l = 14;
	D6.us = 12; pE9->ul = 15;
	D6.us |= pE9->ul;
	D6.us = 12;
	pE9->ul = 15; D6.us = 12;
	pE9->ul |= D6.us;
	pE9->ul = 15;
	D7.ui = 13; pE1->c = 7;
	D7.ui |= pE1->c;
	D7.ui = 13;
	pE1->c = 7; D7.ui = 13;
	pE1->c |= D7.ui;
	pE1->c = 7;
	D7.ui = 13; pE2->sc = 8;
	D7.ui |= pE2->sc;
	D7.ui = 13;
	pE2->sc = 8; D7.ui = 13;
	pE2->sc |= D7.ui;
	pE2->sc = 8;
	D7.ui = 13; pE3->s = 9;
	D7.ui |= pE3->s;
	D7.ui = 13;
	pE3->s = 9; D7.ui = 13;
	pE3->s |= D7.ui;
	pE3->s = 9;
	D7.ui = 13; pE4->i = 10;
	D7.ui |= pE4->i;
	D7.ui = 13;
	pE4->i = 10; D7.ui = 13;
	pE4->i |= D7.ui;
	pE4->i = 10;
	D7.ui = 13; pE5->uc = 11;
	D7.ui |= pE5->uc;
	D7.ui = 13;
	pE5->uc = 11; D7.ui = 13;
	pE5->uc |= D7.ui;
	pE5->uc = 11;
	D7.ui = 13; pE6->us = 12;
	D7.ui |= pE6->us;
	D7.ui = 13;
	pE6->us = 12; D7.ui = 13;
	pE6->us |= D7.ui;
	pE6->us = 12;
	D7.ui = 13; pE7->ui = 13;
	D7.ui |= pE7->ui;
	D7.ui = 13;
	pE7->ui = 13; D7.ui = 13;
	pE7->ui |= D7.ui;
	pE7->ui = 13;
	D7.ui = 13; pE8->l = 14;
	D7.ui |= pE8->l;
	D7.ui = 13;
	pE8->l = 14; D7.ui = 13;
	pE8->l |= D7.ui;
	pE8->l = 14;
	D7.ui = 13; pE9->ul = 15;
	D7.ui |= pE9->ul;
	D7.ui = 13;
	pE9->ul = 15; D7.ui = 13;
	pE9->ul |= D7.ui;
	pE9->ul = 15;
	D8.l = 14; pE1->c = 7;
	D8.l |= pE1->c;
	D8.l = 14;
	pE1->c = 7; D8.l = 14;
	pE1->c |= D8.l;
	pE1->c = 7;
	D8.l = 14; pE2->sc = 8;
	D8.l |= pE2->sc;
	D8.l = 14;
	pE2->sc = 8; D8.l = 14;
	pE2->sc |= D8.l;
	pE2->sc = 8;
	D8.l = 14; pE3->s = 9;
	D8.l |= pE3->s;
	D8.l = 14;
	pE3->s = 9; D8.l = 14;
	pE3->s |= D8.l;
	pE3->s = 9;
	D8.l = 14; pE4->i = 10;
	D8.l |= pE4->i;
	D8.l = 14;
	pE4->i = 10; D8.l = 14;
	pE4->i |= D8.l;
	pE4->i = 10;
	D8.l = 14; pE5->uc = 11;
	D8.l |= pE5->uc;
	D8.l = 14;
	pE5->uc = 11; D8.l = 14;
	pE5->uc |= D8.l;
	pE5->uc = 11;
	D8.l = 14; pE6->us = 12;
	D8.l |= pE6->us;
	D8.l = 14;
	pE6->us = 12; D8.l = 14;
	pE6->us |= D8.l;
	pE6->us = 12;
	D8.l = 14; pE7->ui = 13;
	D8.l |= pE7->ui;
	D8.l = 14;
	pE7->ui = 13; D8.l = 14;
	pE7->ui |= D8.l;
	pE7->ui = 13;
	D8.l = 14; pE8->l = 14;
	D8.l |= pE8->l;
	D8.l = 14;
	pE8->l = 14; D8.l = 14;
	pE8->l |= D8.l;
	pE8->l = 14;
	D8.l = 14; pE9->ul = 15;
	D8.l |= pE9->ul;
	D8.l = 14;
	pE9->ul = 15; D8.l = 14;
	pE9->ul |= D8.l;
	pE9->ul = 15;
	D9.ul = 15; pE1->c = 7;
	D9.ul |= pE1->c;
	D9.ul = 15;
	pE1->c = 7; D9.ul = 15;
	pE1->c |= D9.ul;
	pE1->c = 7;
	D9.ul = 15; pE2->sc = 8;
	D9.ul |= pE2->sc;
	D9.ul = 15;
	pE2->sc = 8; D9.ul = 15;
	pE2->sc |= D9.ul;
	pE2->sc = 8;
	D9.ul = 15; pE3->s = 9;
	D9.ul |= pE3->s;
	D9.ul = 15;
	pE3->s = 9; D9.ul = 15;
	pE3->s |= D9.ul;
	pE3->s = 9;
	D9.ul = 15; pE4->i = 10;
	D9.ul |= pE4->i;
	D9.ul = 15;
	pE4->i = 10; D9.ul = 15;
	pE4->i |= D9.ul;
	pE4->i = 10;
	D9.ul = 15; pE5->uc = 11;
	D9.ul |= pE5->uc;
	D9.ul = 15;
	pE5->uc = 11; D9.ul = 15;
	pE5->uc |= D9.ul;
	pE5->uc = 11;
	D9.ul = 15; pE6->us = 12;
	D9.ul |= pE6->us;
	D9.ul = 15;
	pE6->us = 12; D9.ul = 15;
	pE6->us |= D9.ul;
	pE6->us = 12;
	D9.ul = 15; pE7->ui = 13;
	D9.ul |= pE7->ui;
	D9.ul = 15;
	pE7->ui = 13; D9.ul = 15;
	pE7->ui |= D9.ul;
	pE7->ui = 13;
	D9.ul = 15; pE8->l = 14;
	D9.ul |= pE8->l;
	D9.ul = 15;
	pE8->l = 14; D9.ul = 15;
	pE8->l |= D9.ul;
	pE8->l = 14;
	D9.ul = 15; pE9->ul = 15;
	D9.ul |= pE9->ul;
	D9.ul = 15;
	pE9->ul = 15; D9.ul = 15;
	pE9->ul |= D9.ul;
	pE9->ul = 15;
	
	return 0;
	}}
	}
