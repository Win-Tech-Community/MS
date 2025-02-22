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
*strrev.c - reverse a string in place
*
*	Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*	defines _strrev() - reverse a string in place (not including
*	'\0' character)
*
*Revision History:
*	02-27-90   GJF	Fixed calling type, #include <cruntime.h>, fixed
*			copyright.
*	10-02-90   GJF	New-style function declarator.
*	01-18-91   GJF	ANSI naming.
*	09-03-93   GJF	Replaced _CALLTYPE1 with __cdecl.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>

/***
*char *_strrev(string) - reverse a string in place
*
*Purpose:
*	Reverses the order of characters in the string.  The terminating
*	null character remains in place.
*
*Entry:
*	char *string - string to reverse
*
*Exit:
*	returns string - now with reversed characters
*
*Exceptions:
*
*******************************************************************************/

char * __cdecl _strrev (
	char * string
	)
{
	char *start = string;
	char *left = string;
	char ch;

	while (*string++)		  /* find end of string */
		;
	string -= 2;

	while (left < string)
	{
		ch = *left;
		*left++ = *string;
		*string-- = ch;
	}

	return(start);
}
