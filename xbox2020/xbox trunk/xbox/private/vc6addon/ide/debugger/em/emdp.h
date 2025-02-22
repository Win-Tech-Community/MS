/*++

Copyright (c) 1992  Microsoft Corporation

Module Name:

    emdp.h

Author:

    Wesley Witt (wesw) 21-Sep-1993

--*/

#ifndef OSDEBUG4
#error ("must define OSDEBUG4!")
#endif

#include <windows.h>
#include <stdio.h>
#include <dde.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <memory.h>
#include <string.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <tchar.h>

#include <imagehlp.h>
#include <cvinfo.h>

#pragma warning( disable: 4200)

#include "od.h"
#include "odp.h"
#include "odassert.h"

// BUGBUG kentf have to include shapi.h for LPDEBUGDATA?
#define FLOAT10 double
typedef LPADDR PADDR;
#define EXPCALL __stdcall

#include "shapi.h"

#include "emdm.h"
#include "win32dm.h"

#include "emcpu.h"
#include "emdata.h"
#include "emproto.h"

extern CRITICAL_SECTION csInTL;
#define GuardTL() EnterCriticalSection(&csInTL)
#define ReleaseTL() LeaveCriticalSection(&csInTL)

extern HINSTANCE hInstance;
