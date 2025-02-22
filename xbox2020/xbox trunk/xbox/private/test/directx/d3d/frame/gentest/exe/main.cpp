/*******************************************************************************

Copyright (c) 2000 Microsoft Corporation.  All rights reserved.

File Name:

    main.cpp

Author:

    Matt Bronder

Description:

    Direct3D Immediate-Mode Framework.

*******************************************************************************/

#include "d3dlocus.h"

//extern "C" {
//extern BOOL D3D__SingleStepPusher;
//extern BOOL D3D__Parser;
//}

//******************************************************************************
// Function prototypes
//******************************************************************************

#ifdef UNDER_XBOX

typedef enum _FIRMWARE_REENTRY {
    HalHaltRoutine,
    HalRebootRoutine,
    HalQuickRebootRoutine,
    HalKdRebootRoutine,
    HalMaximumRoutine
} FIRMWARE_REENTRY, *PFIRMWARE_REENTRY;

extern "C" VOID
HalReturnToFirmware (
    IN FIRMWARE_REENTRY Routine
    );

#endif // UNDER_XBOX

extern "C" BOOL  PREPEND_MODULE(_ExhibitScene)(CDisplay* pDisplay, int *pnExitCode);
extern "C" BOOL  PREPEND_MODULE(_ValidateDisplay)(CDirect3D8* pd3d, D3DCAPS8* pd3dcaps, 
                                D3DDISPLAYMODE* pd3ddm);

//******************************************************************************
// Function exports to the harness
//******************************************************************************

#ifdef UNDER_XBOX

#pragma data_seg(D3D_SECTION_NAME)
extern "C" BOOL PREPEND_MODULE(_ExhibitScene)(CDisplay* pDisplay, int *pnExitCode);
extern "C" BOOL PREPEND_MODULE(_ValidateDisplay)(CDirect3D8* pd3d, D3DCAPS8* pd3dcaps, D3DDISPLAYMODE* pd3ddm);
D3DTESTFUNCTIONDESC PREPEND_MODULE(_d3dtfd) = {
    TEXT(MODULE_STRING),
    PREPEND_MODULE(_ValidateDisplay),
    PREPEND_MODULE(_ExhibitScene)
};
#pragma data_seg()

#endif // UNDER_XBOX

//******************************************************************************
// WinMain
//******************************************************************************

#ifndef UNDER_XBOX
#define RETURN(x)   return x
#else
#define RETURN(x)   return
#endif // UNDER_XBOX

//******************************************************************************
//
// Function:
//
//     WinMain
//
// Description:
//
//     Entry point for the application.
//
// Arguments:
//
//     HINSTANCE hInstance      - Application instance handle
//
//     HINSTANCE hPrevInstance  - Previous instance of the application (always
//                                NULL for Win32 applications)
//
//     LPSTR szCmdLine          - Pointer to a string specifying the command
//                                line used in launching the application
//                                (excluding the program name)
//
//     int nCmdShow             - State specifying how the window is to be 
//                                displayed on creation
//
// Return Value:
//
//     0 on success, -1 on failure.
//
//******************************************************************************
#ifndef UNDER_XBOX
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow) 
#else
void __cdecl main()
#endif // UNDER_XBOX
{
    CDisplay*       pDisplay;
    D3DCREATIONDESC d3dcd;
    int             ret;

    // Allow global access to the instance handle
#ifndef UNDER_XBOX
    RegisterTestInstance(hInstance);
#else
    RegisterTestInstance((HINSTANCE)&(PREPEND_MODULE(_d3dtfd)));
#endif

    // Set the test startup context
    RegisterStartupContext(0);

    // Seed the pseudo-random number generator
    srand(GetTickCount());

    // Create a heap for the application
    if (!CreateHeap()) {
        RETURN(0);
    }

    // Initialize logging
    CreateLog(INVALID_HANDLE_VALUE);

    // Set the validation procedure for the device
    InitCheckDisplayProc(PREPEND_MODULE(_ValidateDisplay));

    // Initialize creation parameters
    memset(&d3dcd, 0, sizeof(D3DCREATIONDESC));
    d3dcd.d3ddt = D3DDEVTYPE_HAL;
    d3dcd.bWindowed = FALSE;
    d3dcd.d3ddm.Width = 640;
    d3dcd.d3ddm.Height = 480;
    d3dcd.d3ddm.Format = D3DFMT_X8R8G8B8;
    d3dcd.d3ddm.RefreshRate = 60;
//    SetRect(&d3dcd.rectWnd, 20, 20, 320, 320);
    d3dcd.bDepthBuffer = TRUE;
    d3dcd.fmtd = D3DFMT_D24S8;
    d3dcd.mst = D3DMULTISAMPLE_NONE;
    d3dcd.bAntialias = FALSE;

    // Create the display
    pDisplay = new CDisplay();
    if (!pDisplay) {
        ReleaseLog();
        ReleaseHeap();
        RETURN(0);
    }

    // Initialize the display
    if (!pDisplay->Create(&d3dcd)) {
        DebugString(TEXT("CDisplay::Create failed"));
        pDisplay->Release();
        ReleaseLog();
        ReleaseHeap();
        RETURN(0);
    }

    // Render the 3D scene
    PREPEND_MODULE(_ExhibitScene)(pDisplay, &ret);

    // Clean up
    pDisplay->Release();

    // Stop logging
    ReleaseLog();

    // Release the heap
    ReleaseHeap();

    // Reboot on Xbox
#ifdef UNDER_XBOX
    HalReturnToFirmware(HalQuickRebootRoutine);
#endif

    RETURN(ret);
}
