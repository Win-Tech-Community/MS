// FILE:        flags.cpp
// DESC:        flags class methods
// AUTHOR:      Todd M. Frost
// COMMENTS:

//#include "windows.h"
#include "d3dlocus.h"
#include "flags.h"

#ifdef CLASSNAME
#undef CLASSNAME
#endif
#define CLASSNAME TEXT("CFlags")

// NAME:        CFlags()
// DESC:        constructor for flags class
// INPUT:       none
// OUTPUT:      none

CFlags::CFlags(VOID)
{
    m_dwCurrent = (DWORD) 0;
    m_dwSaved = (DWORD) 0;
}

// NAME:        ~CFlags()
// DESC:        destructor for flags class
// INPUT:       none
// OUTPUT:      none

CFlags::~CFlags(VOID)
{
}
