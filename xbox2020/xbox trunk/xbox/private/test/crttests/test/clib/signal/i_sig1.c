
/*****************************************************************************
 *									     *
 * Test Name: i_sig1.c    Date: 1/29/91   Author: Microsoft                  *
 *===========================================================================*
 *									     *
 * Suite: signal                                                             *
 *===========================================================================*
 *									     *
 * Tested Op/Func: signal						     *
 *---------------------------------------------------------------------------*
 * PURPOSE: This tests that ^C interrupts caused by the user will            *
 *	    result in our installed exception handler to be called.          *
 *									     *
 * METHOD: This test must be ran manually.  It installs a handler for ^C     *
 *         then loops forcing the user to hit ^C eight times.                *
 *                                                                           *
 * MEMORY MODEL(S):                                                          *
 *      32-bit								     *
 * COMPILE/LINK OPTIONS:                                                     *
 *      No restrictions.                                                     *
 * OPERATING SYSTEM(S):                                                      *
 *      NT.  								     *
 * HARDWARE:                                                                 *	
 *      No restrictions                                                      *
 * SOFTWARE:                                                                 *
 *      No restrictions                                                      *
 * CONFIG.SYS:                                                               *
 *      Should contain what is required for compiler/linker                  *
 * ENVIRONMENT VARIABLES:                                                    *
 *      Should contain what is required for compiler/linker                  *
 *---------------------------------------------------------------------------*
 * TEST-RESULT OUTPUT: The outputs for this test shall be as follows:        *
 *      It will tell you to type ^C, over and over, until you do so 8 times. *
 *	Then it will exit.					             *
 *---------------------------------------------------------------------------*
 * MODIFICATION HISTORY:                                                     *
 *                                                                           *
 *  Date       Initials Version PTR #   Description                          *
 *  ---------  -------- ------- ------- -------------------------------------*
 *  1/29/91    SDK      1.00                                                 *
 *									     *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <test.h>

static void __cdecl myhandler(int);

static int T(event_ocurred) = PDV(0);
static int T(event_count)   = PDV(0);

static int T(perfect) = PDV(0);

static char test[] = "i_sig1";

int i_sig1Entry(void){
	int i;

	startest();

	/* install handler for ^C handler. */

	if ( signal(SIGINT, myhandler) == SIG_ERR ) {
		printf("handler install for SIGINT failed!\n");
		exit(1);
	}

	/* Wait for ^C's. */

	for ( i = 0 ; (i < 1000) && (V(event_count) < 8) ; i++ ) {

	    if ( event_ocurred ) {
		printf("^C was hit\n");
		V(event_ocurred) = 0;
	    } else
		printf("Type ^C\n");
	}

	finish();
}

static void __cdecl myhandler(int sigid)
{
	V(event_ocurred) = 1;

	V(event_count)++;

	if ( sigid != SIGINT )
	    fail(1);
}
