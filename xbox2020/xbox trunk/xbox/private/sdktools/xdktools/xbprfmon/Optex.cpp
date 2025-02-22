/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    Optex.cpp

Abstract:

    This module implements the COptex (optimized mutex) synchronization
    object.

Author:

    Jeffrey M. Richter (v-jeffrr) 01-Aug-1998

--*/

#include "xbprfmonp.h"

BOOL COptex::CommonConstructor(PVOID pszName, BOOL fUnicode, DWORD dwSpinCount)
{
    m_hevt = m_hfm = NULL;
    m_pSharedInfo = NULL;

    SYSTEM_INFO sinf;
    GetSystemInfo(&sinf);
    m_fUniprocessorHost = (sinf.dwNumberOfProcessors == 1);

    char szNameA[100];
    if (fUnicode) {   // Convert Unicode name to ANSI
        wsprintfA(szNameA, "%S", pszName);
        pszName = (PVOID)szNameA;
    }

    char sz[100];
    wsprintfA(sz, "JMR_Optex_Event_%s", pszName);
    m_hevt = CreateEventA(NULL, FALSE, FALSE, sz);
    chASSERT(m_hevt != NULL);

    if (m_hevt != NULL) {
        wsprintfA(sz, "JMR_Optex_MMF_%s", pszName);
        m_hfm = CreateFileMappingA((HANDLE) 0xFFFFFFFF, NULL,
                                   PAGE_READWRITE, 0,
                                   sizeof(*m_pSharedInfo), sz);
        chASSERT(m_hfm != NULL);

        if (m_hfm != NULL) {
            m_pSharedInfo = (PSHAREDINFO)MapViewOfFile(
                m_hfm, FILE_MAP_WRITE, 0, 0, 0);

            //
            // Note: SHAREDINFO's m_lLockCount, m_dwThreadId, and m_lRecurseCount
            // members need to be initialized to 0. Fortunately, a new pagefile
            // MMF sets all of its data to 0 when created. This saves use from
            // some thread synchronization work.
            //

            if (m_pSharedInfo != NULL) {
                SetSpinCount(dwSpinCount);
            }
        }
    }

    return ((m_hevt != NULL) && (m_hfm != NULL) && (m_pSharedInfo != NULL));
}

COptex::~COptex()
{
#ifdef _DEBUG
    if (m_pSharedInfo->m_dwThreadId == GetCurrentThreadId()) {
        DebugBreak();
    }
#endif
    UnmapViewOfFile(m_pSharedInfo);
    CloseHandle(m_hfm);
    CloseHandle(m_hevt);
}

void COptex::SetSpinCount(DWORD dwSpinCount)
{
    if (!m_fUniprocessorHost) {
        InterlockedExchange((PLONG)&m_pSharedInfo->m_dwSpinCount, dwSpinCount);
    }
}

void COptex::Enter(void)
{
    //
    // Spin, trying to get the Optex
    //
    if (TryEnter()) {
        return;
    }

    DWORD dwThreadId = GetCurrentThreadId();  // The calling thread's ID

    if (InterlockedIncrement(&m_pSharedInfo->m_lLockCount) == 1) {

        //
        // Optex is unowned, let this thread own it once
        //
        InterlockedExchange((PLONG) &m_pSharedInfo->m_dwThreadId, dwThreadId);
        m_pSharedInfo->m_lRecurseCount = 1;

    } else {

        //
        // Optex is owned by a thread
        //
        if (m_pSharedInfo->m_dwThreadId == dwThreadId) {

            //
            // Optex is owned by this thread, own it again
            //
            m_pSharedInfo->m_lRecurseCount++;

        } else {

            //
            // Optex is owned by another thread
            // Wait for the owning thread to release the Optex
            //
            WaitForSingleObject(m_hevt, INFINITE);

            //
            // We got ownership of the Optex
            //
            InterlockedExchange((PLONG) &m_pSharedInfo->m_dwThreadId, dwThreadId); // We own it now
            m_pSharedInfo->m_lRecurseCount = 1;       // We own it once
        }
    }
}

BOOL COptex::TryEnter(VOID)
{
    DWORD dwThreadId = GetCurrentThreadId();  // The calling thread's ID

    //
    // If the lock count is zero, the Optex is unowned and
    // this thread can become the owner of it now.
    //

    BOOL fThisThreadOwnsTheOptex = FALSE;
    DWORD dwSpinCount = m_pSharedInfo->m_dwSpinCount;
    do {
        fThisThreadOwnsTheOptex = (0 == (DWORD)
            InterlockedCompareExchangePointer(
                (PVOID*)&m_pSharedInfo->m_lLockCount, (PVOID)1, (PVOID)0));

        if (fThisThreadOwnsTheOptex) {

            //
            // We now own the Optex
            //
            InterlockedExchange((PLONG)&m_pSharedInfo->m_dwThreadId, dwThreadId); // We own it
            m_pSharedInfo->m_lRecurseCount = 1;     // We own it once

        } else {

            //
            // Some thread owns the Optex
            //
            if (m_pSharedInfo->m_dwThreadId == dwThreadId) {
                //
                // We already own the Optex
                //
                InterlockedIncrement(&m_pSharedInfo->m_lLockCount);
                m_pSharedInfo->m_lRecurseCount++;   // We own it again
                fThisThreadOwnsTheOptex = TRUE;     // Return that we own the Optex
            }
        }
    } while (!fThisThreadOwnsTheOptex && (dwSpinCount-- > 0));

    //
    // Return whether or not this thread owns the Optex
    //
    return fThisThreadOwnsTheOptex;
}

void COptex::Leave(void)
{
#ifdef _DEBUG
    if (m_pSharedInfo->m_dwThreadId != GetCurrentThreadId()) {
        DebugBreak();
    }
#endif

    if (--m_pSharedInfo->m_lRecurseCount > 0) {

        //
        // We still own the Optex
        //
        InterlockedDecrement(&m_pSharedInfo->m_lLockCount);

    } else {

        //
        // We don't own the Optex
        //
        InterlockedExchange((PLONG) &m_pSharedInfo->m_dwThreadId, 0);
        if (InterlockedDecrement(&m_pSharedInfo->m_lLockCount) > 0) {
            //
            // Other threads are waiting, wake one of them
            //
            SetEvent(m_hevt);
        }
    }
}

