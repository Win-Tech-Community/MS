/*===========================================================================*\
 | 
 |  FILE:	Plugin.cpp
 |			MAX Script SDK Example - adding a value class to MAX Script
 |			3D Studio MAX R3.0
 | 
 |  AUTH:   Harry Denholm
 |			Developer Consulting Group
 |			Copyright(c) Discreet 1999
 |
 |  HIST:	Started 1-4-99
 | 
\*===========================================================================*/

#include "MAXScrpt.h"


HMODULE hInstance = NULL;


BOOL APIENTRY
DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	static BOOL controlsInit = FALSE;
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			// Hang on to this DLL's instance handle.
			hInstance = hModule;
			if ( !controlsInit )
			{
				controlsInit = TRUE;				
				// Initialize Win95 controls
 				InitCommonControls();
			}
			break;
	}
		
	return(TRUE);
}

__declspec( dllexport ) const TCHAR *
LibDescription() { return _T("SimpleStore MAX Script SDK Example (Class)"); }

__declspec( dllexport ) ULONG
LibVersion() {  return VERSION_3DSMAX; }

