//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft shared
// source or premium shared source license agreement under which you licensed
// this source code. If you did not accept the terms of the license agreement,
// you are not authorized to use this source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the SOURCE.RTF on your install media or the root of your tools installation.
// THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//
// new and delete operators for debug CRT heap use by C++ Library

 #if defined(_DEBUG)
  #include <xdebug>
  #include <crtdbg.h>

void * __CRTDECL operator new(size_t sz, const std::_DebugHeapTag_t &tag,
	char *file, int line) _THROW_BAD_ALLOC
	{	// allocate storage with debugging information
	void *p = _malloc_dbg(sz, tag._Type, file, line);
	if (p == 0)
		{	// report out of memory
		_STD _Xbad_alloc();
		}
	return (p);
	}

void * __CRTDECL operator new[](size_t sz, const std::_DebugHeapTag_t &tag,
	char *file, int line) _THROW_BAD_ALLOC
	{	// allocate array storage with debugging information
	return (operator new(sz, tag, file, line));
	}

void  __CRTDECL operator delete(void *p, const std::_DebugHeapTag_t &tag, char *, int)
	_THROW0()
	{	// free storage
	_free_dbg(p, tag._Type);
	}

void  __CRTDECL operator delete[](void *p, const std::_DebugHeapTag_t &tag,
	char *file, int line) _THROW0()
	{	// free array storage
	operator delete(p, tag, file, line);
	}

_STD_BEGIN
const _DebugHeapTag_t _DebugHeapTag = {_CRT_BLOCK};
_MRTIMP2 const _DebugHeapTag_t& __cdecl _DebugHeapTag_func()
{
    return _DebugHeapTag;
}
_STD_END

#pragma comment(linker, "/disallowlib:libc.lib")
#pragma comment(linker, "/disallowlib:libcmt.lib")

 #endif /* defined(_DEBUG) */

/*
 * Copyright (c) 1992-2007 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.03:0009 */
