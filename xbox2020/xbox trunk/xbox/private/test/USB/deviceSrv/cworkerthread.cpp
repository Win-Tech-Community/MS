/*

Copyright (C) 1999 Microsoft Corporation

Module Name:

    CWorkerThread.cpp

Abstract:

    

Author:

    Josh Poley (jpoley) 1-1-1999

Revision History:

*/


#include "CWorkerThread.h"

namespace DeviceServer {

/*****************************************************************************

Routine Description:

    LocalThreadFunct

Arguments:

    LPVOID lpParameter  - a valid CWorkerThread class

Return Value:

    0 on error, ~0 on execption, or the thread's exit value

Notes:


*****************************************************************************/
static DWORD WINAPI LocalThreadFunct(LPVOID lpParameter)
    {
    DWORD returnCode = 0;
    HWND window = NULL;
    UINT msg = 0;
    LPARAM lparam = 0;
    CWorkerThread *localPointer = (CWorkerThread*)lpParameter;

    if(!localPointer)
        {
        // a valid CWorkerThread class must be supplied via the lpParameter!
        //_ASSERT(localPointer);
        return 0;
        }

    // turn off the exit flag and set notification values
    localPointer->Lock();
    localPointer->bExit = FALSE;
    window = localPointer->notifyWindow;
    msg = localPointer->notifyMsg;
    lparam = localPointer->notifylParam;
    localPointer->Unlock();

    // set the thread id
    localPointer->SetThreadID(GetCurrentThreadId());

    // run the main thread function (this is the custom function)
#ifdef _DEBUG
    returnCode = localPointer->ThreadFunct();
#else
    //try
        {
        returnCode = localPointer->ThreadFunct();
        }
    //catch(...)
    //    {
    //    returnCode = ~0;
    //    }
#endif

    // invalidate the thread handle & id
    localPointer->SetThreadID(~0);
    localPointer->SetThreadHandle(~0);

    // store the return code from the main thread function
    localPointer->Lock();
    localPointer->dwThreadExitCode = returnCode;
    localPointer->Unlock();

    // send notification if necessary
    if(window)
        {
        //PostMessage(window, msg, (WPARAM)returnCode, lparam);
        }

    // exit thread
    return returnCode;
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::Run
    start up a worker thread

Arguments:

    none

Return Value:

    none

Notes:

*****************************************************************************/
void CWorkerThread::Run(void)
    {
    DWORD handle = _beginthread((void (__cdecl *)(void *))LocalThreadFunct, 0, this);
    SetThreadHandle(handle);
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::CWorkerThread
    worker thread data constructor

Arguments:

    none

Return Value:

    none

Notes:

*****************************************************************************/
CWorkerThread::CWorkerThread()
    {
    InitializeCriticalSection(&criter);
    SetThreadHandle(~0);
    SetThreadID(~0);

    Lock();

    notifyWindow = NULL;
    notifyMsg = 0;
    notifylParam = 0;

    dwLocalThreadID = 0;

    bExit = FALSE;
    dwThreadExitCode = 0;

    Unlock();
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::CWorkerThread
    worker thread data constructor

Arguments:

    DWORD localID

Return Value:

    none

Notes:

*****************************************************************************/
CWorkerThread::CWorkerThread(DWORD localID)
    {
    InitializeCriticalSection(&criter);
    SetThreadHandle(~0);
    SetThreadID(~0);

    Lock();

    notifyWindow = NULL;
    notifyMsg = 0;
    notifylParam = 0;
    
    dwLocalThreadID = localID;

    bExit = FALSE;
    dwThreadExitCode = 0;

    Unlock();
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::~CWorkerThread
    worker thread data destructor

Arguments:

    none

Return Value:

    none

Notes:

    If the thread does not exit, this function will be caught in an infinate 
        loop.

*****************************************************************************/
CWorkerThread::~CWorkerThread()
    {
    if(GetThreadHandle() != ~0)
        {
        DWORD timeout = 1000; // start with 1 sec

        // if your code infinite loops here, you have a blocking problem
        while(!SoftBreak(timeout))
            {
            timeout *= 2;
            if(timeout == 64000) OutputDebugStringA("CWorkerThread::~CWorkerThread(): Possible deadlock\n");
            }
        }

    DeleteCriticalSection(&criter);
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::SoftBreak

Arguments:

    DWORD dwTimeOut - timeout value in ms

Return Value:

    TRUE - the thread exited, FALSE - timedout before the thread exited

Notes:

*****************************************************************************/
BOOL CWorkerThread::SoftBreak(DWORD dwTimeOut)
    {
    Lock();
    bExit = TRUE;
    Unlock();

    return WaitForExit(dwTimeOut);
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::HardBreak

Arguments:

    none

Return Value:

    TRUE - operation succedded, FALSE - the operation failed.

Notes:

    This function does not perform any locking or unlocking.

    WARNING: Do not use this function execpt in DIRE situations. This WILL 
        cause leaks, and perhaps blocking or crashes if critical sections 
        are not released!

*****************************************************************************/
BOOL CWorkerThread::HardBreak(void)
    {
    DWORD dwHandle = dwThreadHandle;
    bExit = TRUE;
    dwThreadHandle = ~0;
    dwThreadExitCode = ~0;
    dwThreadID = ~0;

    if(dwHandle != ~0)
        {
        OutputDebugStringA("CWorkerThead::HardBreak() called!\n");
        //
        // schanbai 11/20/2000
        // comment out as there is no TerminateThread under Xbox
        //
#if 0
        return TerminateThread((void*)dwHandle, ~0);
#else
        return FALSE;
#endif
        }

    return FALSE;
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::WaitForExit

Arguments:

    DWORD dwTimeOut - timeout value in ms

Return Value:

    TRUE - the thread exited, FALSE - timeout was reached

Notes:

*****************************************************************************/
BOOL CWorkerThread::WaitForExit(DWORD dwTimeOut)
    {
    DWORD dwStartTime = GetTickCount();
    DWORD dwCurTime;

    while(GetThreadHandle() != ~0)
        {
        Sleep(20);
        dwCurTime = GetTickCount();
        if(dwCurTime - dwStartTime >= dwTimeOut)
            {
            return FALSE;
            }
        }

    return TRUE;
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::Lock

Arguments:

    DWORD dwTimeOut - timeout value in ms
   
Return Value:

    TRUE - critical section entered, FALSE - timeout

Notes:

*****************************************************************************/
#ifdef _WIN32_WINNT // TryEnterCriticalSection only available on NT
#include "winbase.h"
BOOL CWorkerThread::Lock(DWORD dwTimeOut)
    {
    DWORD dwStartTime = GetTickCount();
    DWORD dwCurTime;

    while(!TryEnterCriticalSection(&criter))
        {
        Sleep(20);
        dwCurTime = GetTickCount();
        if(dwCurTime - dwStartTime >= dwTimeOut)
            {
            return FALSE;
            }
        }

    return TRUE;
    }
#endif


/*****************************************************************************

Routine Description:

    CWorkerThread::SetExitNotify

Arguments:

    HWND   notifyDestination  - handle to the destination window
    UINT   message            - the message to send
    LPARAM lParam             - custom parameter to send

Return Value:

    none

Notes:

    WPARAM of the message is always the return code for the thread

*****************************************************************************/
void CWorkerThread::SetExitNotify(HWND notifyDestination, UINT message, LPARAM lParam)
    {
    Lock();
    notifyWindow = notifyDestination;
    notifyMsg = message;
    notifylParam = lParam;
    Unlock();
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::SuspendThread

Arguments:

    none

Return Value:

    DWORD - the thread's suspend count, 0xFFFFFFFF on error.

Notes:

    This function just calls the WIN API SuspendThread

*****************************************************************************/
DWORD CWorkerThread::SuspendThread(void)
    {
    DWORD dwHandle = GetThreadHandle();

    if(dwHandle != ~0)
        {
        return ::SuspendThread((void*)dwHandle);
        }

    return 0xFFFFFFFF;
    }


/*****************************************************************************

Routine Description:

    CWorkerThread::ResumeThread

Arguments:

    none

Return Value:

    DWORD - the thread's suspend count, 0xFFFFFFFF on error.

Notes:

    This function just calls the WIN API ResumeThread

*****************************************************************************/
DWORD CWorkerThread::ResumeThread(void)
    {
    DWORD dwHandle = GetThreadHandle();

    if(dwHandle != ~0)
        {
        return ::ResumeThread((void*)dwHandle);
        }

    return 0xFFFFFFFF;
    }
} // namespace DeviceServer