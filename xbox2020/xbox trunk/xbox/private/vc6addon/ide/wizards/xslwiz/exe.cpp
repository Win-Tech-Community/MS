// exe.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "exe.h"
#include "exeaw.h"

#include <atlimpl.cpp>

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

static AFX_EXTENSION_MODULE XslDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("EXE.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(XslDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(XslDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&Xslaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("EXE.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(XslDLL);
	}
	return 1;   // ok
}
