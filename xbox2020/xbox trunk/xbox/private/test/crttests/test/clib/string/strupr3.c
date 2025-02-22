
/***************************************************************************

         Copyright (C) Microsoft Corp. 1993


Test:   _strupr

Abstract:   Vefifies that _strupr is effected by a change in the locale,
            and handles chars >127.

===========================================================================
Syntax

===========================================================================
Priority:               1
Products:               WIN NT


Revision History:

    Date        emailname       description
----------------------------------------------------------------------------
    11-03-93    lhanson         created
    11-22-94    a-timke         Modified for NT3.5 results.
----------------------------------------------------------------------------

EndHeader:

****************************************************************************/

#include <string.h>
#include <locale.h>
#include <test.h>

static char test[] = __FILE__;
static int perfect;


int strupr3Entry(){
    unsigned char *psz1_us = "AaBbC\x9A\x8B\xE0\xEF\xF0Zz";
    unsigned char *psz1    = "AaBbC\x9A\x8B\xE0\xEF\xF0Zz";
    unsigned char *psz2    = "AABBC\x8A\x8B\xC0\xCF\xD0ZZ";

    startest();

    checke(_strupr(psz1_us), psz1_us);
    checkne(strcmp(psz1_us, psz2), 0);

    checkne(setlocale( LC_ALL, "French_France.OCP" ), NULL);

    checke(_strupr(psz1), psz1);
#if defined(TEST_WIN95) /*prior to NLS work of 2/97.*/
    checke(strcmp(psz1, psz2), 0);
#else
    checke(strcmp(psz1, psz2), 1);
#endif
    finish();
}
