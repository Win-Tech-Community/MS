
/****************************************************************************
              Copyright (C) 1992, Microsoft Corporation
Method:              cl strcoll1.c
                     strcoll1
Switches:            NONE
Hard/Soft Needs:
Abstract:            This test verifies the strcoll() function.
OS Version:          REAL/PROT/ALL
CPU:                 8086
Dependencies:        NONE
Environment Vars:    NONE
Verification Method: COMPILE/EXECUTE/COMPARE
Notes:               Must include STRING.H
                     Tests decribed in the testplan STRING.DOC
Products:            C800
Test Type:       DEPTH

Revision History:
 Date              emailname      description
---------------------------------------------------------------------------
 [ 0] 26-May-92    edv            created

---------------------------------------------------------------------------
EndHeader:
*****************************************************************************/

#include <string.h>
#include <locale.h>
#include <test.h>

static char test[] = __FILE__;
static int perfect;


static char stringval1[51] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYy";
static char stringval2[51] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxyz";
/*                                                                     ^
                                                            ___________|
*/

int strcoll1Entry(){
    int i, outcome;
    char string1[51], string2[51];

    startest();

    setlocale( LC_COLLATE, "C" );

/*  Scenario 1: Verify that the function returns a negative value
                when string1 < string2.
*/
    for (i = 0; i < 51; i++ )
    {
        string1[i] = stringval1[i];
        string2[i] = stringval2[i];
    }
    outcome = 999;
    outcome = strcoll( string1, string2 );
    checke( (outcome < 0), 1 );



/*  Scenario 2: Verify that the function returns a positive value
                when string1 > string2.
*/
    for (i = 0; i < 51; i++ )
    {
        string1[i] = stringval2[i];
        string2[i] = stringval1[i];
    }
    outcome = -999;
    outcome = strcoll( string1, string2 );
    checke( (outcome > 0), 1 );



/*  Scenario 3: Verify that the function returns zero when string1 = string2.
*/
    for (i = 0; i < 51; i++ )
    {
        string1[i] = stringval1[i];
        string2[i] = stringval1[i];
    }
    outcome = 999;
    outcome = strcoll( string1, string2 );
    checke( (outcome == 0), 1 );


    finish();
}
