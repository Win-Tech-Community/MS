#ifdef _XBOX
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#include <ntos.h>
#include <ntrtl.h>
#include <nturtl.h>
#include <ntdddisk.h>
#include <ntddcdrm.h>
#include <ntddscsi.h>
#include <ntddcdvd.h>
#include <smcdef.h>
#include <scsi.h>
#include <init.h>
#ifdef __cplusplus
}
#endif // __cplusplus
#include <dsoundp.h>
#include <xtl.h>
#include <xgraphics.h>
#include <xboxp.h>
#include <xapip.h>
#include <av.h>


#ifndef D3DLOCK_DISCARD
#define D3DLOCK_DISCARD 0
#endif

#endif

#ifdef _WINDOWS
#include <winsock2.h>
#include <windows.h>
#endif

#include <tchar.h>
typedef TCHAR* PTCHAR;

// "Filesystem" Character Type...What do *most* of the file system API's use...
#if defined(_XBOX)
typedef char FSCHAR;
#define _FS(s) s
#else
typedef TCHAR FSCHAR;
#define _FS(s) _T(s)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include <crtdbg.h>

#if !defined(_NOD3D)
#define D3D_OVERLOADS
#include <d3d8.h>
#include <d3dx8.h>

#endif


////////////////////////////////////////////////////////////////////////////

#ifdef  __cplusplus

#define EXTERN_C extern "C"


#define RELEASENULL(object) { if ((object) != NULL) { (object)->Release(); (object) = NULL; } }

#else // !__cplusplus

#define EXTERN_C extern
#define bool BOOL
#define true TRUE
#define false FALSE
#define inline _inline

#endif

#define CopyChars(dest, src, count) CopyMemory(dest, src, (count) * sizeof (TCHAR))
#define countof(n) (sizeof (n) / sizeof (n[0]))


#ifdef _UNICODE
extern void Unicode(TCHAR* wsz, const char* sz, int nMaxChars);
extern void Ansi(char* sz, const TCHAR* wsz, int nMaxChars);
#endif

#undef ASSERT
#undef VERIFY
#undef ASSERTHR
#undef VERIFYHR
#undef TRACE
#undef ALERT

#ifdef _DEBUG

#define ASSERT(f)		if (!(f)) RtlAssert(#f, __FILE__, __LINE__, NULL)
#define VERIFY(f)		ASSERT(f)
#define ASSERTHR(f)		do { HRESULT hrverify = (f); if (FAILED(hrverify) && AssertFailed(_T(__FILE__), __LINE__, hrverify)) _CrtDbgBreak(); } while (0)
#define VERIFYHR(f)		ASSERTHR(f)
#define TRACE			Trace
#define ALERT			Alert

EXTERN_C bool AssertFailed(const TCHAR* szFile, int nLine, HRESULT hr);
EXTERN_C void Trace(const TCHAR* szMsg, ...);

#else // !_DEBUG

#define ASSERT(f)		((void)0)
#define VERIFY(f)		((void)(f))
#define ASSERTHR(f)		((void)0)
#define VERIFYHR(f)		((void)(f))
#define TRACE			1 ? (void)0 : Trace
#define ALERT			1 ? (void)0 : Alert

inline void Trace(const TCHAR* szMsg, ...) { }

#endif

EXTERN_C void Alert(const TCHAR* szMsg, ...);


////////////////////////////////////////////////////////////////////////////

#ifdef _XBOX
#include "xprofp.h"

#ifdef _PROFILE
#define START_PROFILE() XProfpControl(XPROF_START, 0)
#define END_PROFILE() XProfpControl(XPROF_STOP, 0)
#else
#define START_PROFILE()
#define END_PROFILE()
#endif
#else
#define START_PROFILE()
#define END_PROFILE()
#endif

////////////////////////////////////////////////////////////////////////////
// Stuff from Windows that Xbox should have...
//
/*
#ifdef _XBOX
typedef  PVOID           HDEVNOTIFY;

typedef struct tagRGBQUAD {
        BYTE    rgbBlue;
        BYTE    rgbGreen;
        BYTE    rgbRed;
        BYTE    rgbReserved;
} RGBQUAD;
typedef RGBQUAD FAR* LPRGBQUAD;

#define MAX_COMPUTERNAME_LENGTH 15 // REVIEW: What is this really?
#endif
*/