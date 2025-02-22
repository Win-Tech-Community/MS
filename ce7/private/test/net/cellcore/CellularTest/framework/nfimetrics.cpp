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

#include <windows.h>
#include "framework.h"
#include "radiotest_metric.h"

BOOL NFIMetrics::LoadTestSuites(FUNCTION_TABLE_ENTRY * &pFTE)
{
    if (m_pFTE)
    {
        pFTE = m_pFTE;
        return TRUE;
    }

    CaseInfo rgCase [] =
    {
        {500, 0},
        {501, 0}    // signal on/off
    };

    // + 2 means that add begin and end flag of FTE.
    m_dwCaseNumber = sizeof(rgCase) / sizeof(rgCase[0]) + 2;

    m_pFTE = new FUNCTION_TABLE_ENTRY[m_dwCaseNumber];
    if (!m_pFTE)
    {
        g_pLog->Log(
            LOG, 
            L"ERROR: Memory is not enough. Creating NFI test suite is failed."
            );
        return FALSE;
    }

    // load test suites
    BOOL fRet = TRUE;
    fRet = LoadCaseList(rgCase);

    if (fRet)
    {
        pFTE = m_pFTE;
    }
    return fRet;
}

NFIMetrics::NFIMetrics()
{
}

NFIMetrics::~NFIMetrics()
{
    if (m_pFTE)
    {
        g_pLog->Log(LOG, L"INFO: ~NFIMetrics 0x%x.", m_pFTE);
        delete m_pFTE;
        m_pFTE = NULL;
    }
}

void NFIMetrics::PrintHeader (void)
{
    CMetrics::PrintHeader();
    PrintBorder();
}

void NFIMetrics::PrintSummary (void)
{
    CMetrics::PrintSummary();
    PrintBorder();
}

void NFIMetrics::PrintCheckPoint(void)
{
    CMetrics::PrintCheckPoint();
    PrintBorder();
}