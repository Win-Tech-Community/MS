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
#include "tuxmain.h"
#include "handles.h"

#ifndef BRUSH_H
#define BRUSH_H

class CBrush
{
    public:
        CBrush(CSection * Section) : m_SectionList(Section), m_hBrush(NULL),
                                                      m_StockBrush(NULL), m_tsBrushNameArray(NULL), 
                                                      m_nBrushIndex(0), m_nMaxBrushIndex(0)
                        { info(DETAIL, TEXT("In CBrush overloaded constructor.")); }
        ~CBrush() { info(DETAIL, TEXT("In CBrush Destructor.")); }
        CBrush() {}

        BOOL Initialize(TestSuiteInfo *);
        BOOL PreRun(TestInfo *, HDC hdc);
        BOOL PostRun(HDC hdc);
        BOOL Cleanup();
        HBRUSH GetBrush();

    private:

        // attached brush list, with the name of the brush and the current index
        CSection *m_SectionList;
        HBRUSH *m_hBrush;
        HBRUSH m_StockBrush;
        TSTRING *m_tsBrushNameArray;
        int m_nBrushIndex, m_nMaxBrushIndex;
};

#endif
