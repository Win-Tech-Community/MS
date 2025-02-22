#include <xtl.h>
#include <xonline.h>
#include <stdio.h>

/* This sample program tests PIN decoding functions with multiple gamepads

/* This sample application links against libraries which were not part
   of the SDK as of the writing of this code. Namely XOnline APIs. Update
   project settings when these APIs will be released witin the SDK */

void __cdecl main()
{
	int i;
	HRESULT hr;
	XINPUT_STATE inputState;
	BYTE pinDigit;
	char debugString[256];

	//each gamepad has a handle plus a special handle for decoding pin
	HANDLE gamepad[4];
	XPININPUTHANDLE pinHandle[4];

	//these strings are used to identify enumerated button codes
	char buttonStrings[12][20] = { "up", "down", "left", "right", "A", "B", "X", "Y", "black", "silver", "LT", "RT"};
	
	//initialize gamepads
	XInitDevices( 0, NULL );
	Sleep(1000);	//this should be replaced with a check for device presence before XInputOpen, this is a lazy hack
	for(i=0; i<4; i++)
	{
		gamepad[i] = XInputOpen( XDEVICE_TYPE_GAMEPAD, XDEVICE_PORT0 + i, XDEVICE_NO_SLOT, NULL );
	}

	//start decoding for each gamepad
	for(i=0; i<4; i++ )
	{
		if( gamepad[i]!=0 )
		{
			XInputGetState( gamepad[i], &inputState );
			pinHandle[i] = XOnlinePINStartInput( &inputState );
		}
	}

	//decode button presses from all gamepad indefinately
	while( 1 )
	{
		for( i=0; i<4; i++)
		{
			if( gamepad[i]!= 0 )
			{
				XInputGetState( gamepad[i], &inputState);
				hr = XOnlinePINDecodeInput( pinHandle[i], &inputState, &pinDigit );
				if( hr == S_OK )
				{
					sprintf( debugString, "Gamepad #%d key is: ", i );
					OutputDebugString( debugString );
					OutputDebugString( &buttonStrings[pinDigit-1][0] );
					OutputDebugString( "\n" );
				} //if
			} //if
		} //for
	} //while

	//these calls are never executed but in a "normal" program should be used
	XOnlinePINEndInput( pinHandle );

	//close input devices
	for(i=0; i<4; i++)
	{
		if( gamepad[i] != 0 )
			XInputClose( gamepad[i] );;
	}
}
