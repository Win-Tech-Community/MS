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
*fgetwchr.c - get a wide character from stdin
*
*	Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*	defines _fgetwchar() and getwchar() - read a wide character from stdin
*
*Revision History:
*	04-26-93  CFW	Module created.
*	05-03-93  CFW	Bring wide char support from fgetwchr.c.
*	06-02-93  CFW	Wide get/put use wint_t.
*       02-07-94  CFW   POSIXify.
*
*******************************************************************************/

#ifndef _POSIX_

#include <cruntime.h>
#include <stdio.h>
#include <tchar.h>

/***
*wint_t _fgetwchar(), getwchar() - read a wide character from stdin
*
*Purpose:
*	Reads the next wide character from stdin.  Function version of
*	getwchar() macro.
*
*Entry:
*	None.
*
*Exit:
*	Returns wide character read or WEOF if at end-of-file or an error occured,
*	in which case the appropriate flag is set in the FILE structure.
*
*Exceptions:
*
*******************************************************************************/

wint_t __cdecl _fgetwchar (
	void
	)
{
	return(getwc(stdin));
}

#undef getwchar

wint_t __cdecl getwchar (
	void
	)
{
	return(_fgetwchar());
}

#endif /* _POSIX_ */
