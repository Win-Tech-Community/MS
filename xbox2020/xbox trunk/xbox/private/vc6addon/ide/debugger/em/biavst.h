#include "stdarg.h"

#undef i386
#undef _X86_
#undef MIPS
#undef _MIPS_
#undef ALPHA
#undef _ALPHA_
#undef PPC
#undef _PPC_


//
// _X86_ causes:
//      nt.h        include "nti386.h"
//      nti386.h    an x86 typedef for _DBGKD_CONTROL_REPORT et al
//      nti386.h    the 386 CONTEXT record and friends
//
// _ALPHA_ causes:
//      ntdef.h     UNALIGNED to be defined as __unaligned
//      nt.h        include "ntalpha.h"
//      ntalpha.h   an alpha typedef for _DBGKD_CONTROL_REPORT et al
//      ntalpha.h   the alpha CONTEXT record and friends
//
// _MIPS_ causes:
//      nt.h        include "ntmips.h"
//      ntdef.h     UNALIGNED to be defined as __unaligned
//      ntmips.h    _cdecl to be defined as ""
//      ntmips.h    ifdef MIPS:
//                      a MIPS typedef for _DBGKD_CONTROL_REPORT et al
//                      the MIPS CONTEXT record and friends
//
// _PPC_ causes:
//      ntdef.h     UNALIGNED to be defined as __unaligned
//      nt.h        include "ntppc.h"
//      ntppc.h     a ppc typedef for _DBGKD_CONTROL_REPORT et al
//      ntppc.h     the ppc CONTEXT record and friends
//
//
//



#if defined(TARGET_MIPS)

#define _MIPS_ 1

#if defined(HOST_MIPS)
#define MIPS 1
#endif

#if defined(HOST_i386)
#define __unaligned
#endif

#define _CONTEXT _MIPS_CONTEXT
#define CONTEXT MIPS_CONTEXT
#define PCONTEXT PMIPS_CONTEXT
#define LPCONTEXT LPMIPS_CONTEXT


#include <windows.h>
#include <basetsd.h>
#include <nt.h>
#include <windbgkd.h>
#include <imagehlp.h>

#if !defined(HOST_MIPS)
#undef MIPS
#undef _MIPS_
#endif

#if defined(HOST_i386)
#undef _cdecl
#undef UNALIGNED
#define UNALIGNED
#endif

#ifdef _BASETSD_H_
#undef _BASETSD_H_
#endif

#elif defined(TARGET_PPC)

#define _PPC_ 1

#if defined(HOST_MIPS)
#define MIPS 1
#endif

#if defined(HOST_i386)
#define __unaligned
#endif

#define _CONTEXT _PPC_CONTEXT
#define CONTEXT PPC_CONTEXT
#define PCONTEXT PPPC_CONTEXT
#define LPCONTEXT LPPPC_CONTEXT


#include <windows.h>
#include <basetsd.h>
#include <windbgkd.h>
#include <imagehlp.h>

#if !defined(HOST_MIPS)
#undef MIPS
#undef _MIPS_
#endif

#if defined(HOST_i386)
#undef _cdecl
#undef UNALIGNED
#define UNALIGNED
#endif

#ifdef _BASETSD_H_
#undef _BASETSD_H_
#endif






#elif defined(TARGET_i386)

#define _X86_ 1

#if defined(HOST_MIPS)
#define MIPS 1
#endif

#define _CONTEXT _I386_CONTEXT
#define CONTEXT I386_CONTEXT
#define PCONTEXT PI386_CONTEXT
#define LPCONTEXT LPI386_CONTEXT

#include <windows.h>
#include <basetsd.h>
#include <windbgkd.h>
#include <imagehlp.h>

#if defined(HOST_MIPS)
#undef _cdecl
#define _cdecl
#endif

#if defined(HOST_ALPHA)
#undef _cdecl
#define _cdecl
#endif

#ifdef _BASETSD_H_
#undef _BASETSD_H_
#endif


#elif defined(TARGET_ALPHA)

#define _ALPHA_ 1

#if defined(HOST_i386)
#define __unaligned
#endif

#if defined(HOST_MIPS)
#define MIPS 1
#endif

#define _CONTEXT _ALPHA_CONTEXT
#define CONTEXT ALPHA_CONTEXT
#define PCONTEXT PALPHA_CONTEXT
#define LPCONTEXT LPALPHA_CONTEXT

#include <windows.h>
#include <basetsd.h>
#include <windbgkd.h>
#include <imagehlp.h>

#if defined(HOST_MIPS)
#undef _cdecl
#define _cdecl
#endif

#if defined(HOST_i386)
#undef UNALIGNED
#define UNALIGNED
#endif

#if !defined(HOST_ALPHA)
#undef _ALPHA_
#endif

#ifdef _BASETSD_H_
#undef _BASETSD_H_
#endif

#else

#error "Unsupported target CPU"

#endif
