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
#include <perfloggerapi.h>
#include "perfhlp.h"

// --------------------------------------------------------------------
// Set static class variables to default values
// --------------------------------------------------------------------
BOOL CPerflog::m_fInitPeformed = FALSE;
BOOL CPerflog::m_fInitSucceeded = FALSE;
BOOL CPerflog::m_fUseReleaseDirectory = TRUE;
DWORD CPerflog::m_dwLastLogFileSize = 0;
LPTSTR CPerflog::m_pszLogFileName = NULL;
LPTSTR CPerflog::m_pszTestAppName = NULL;
DWORD CPerflog::m_dwMarkerCount = MARK_TEST;
LPCRITICAL_SECTION CPerflog::m_lpCriticalSection;

// --------------------------------------------------------------------
// Initialize : performs timer calibration, initializes perf library
// and captures the name of the perflog output file.
// --------------------------------------------------------------------
BOOL CPerflog::Initialize(LPCTSTR pszTestName, BOOL fUseReleaseDirectory)
{
    BOOL fRet = FALSE;

    // We only need to initialize once
    if (m_fInitPeformed)
    {
        return m_fInitSucceeded;
    }

    m_fInitPeformed = TRUE;
    m_fUseReleaseDirectory = fUseReleaseDirectory;
    m_pszLogFileName = (TCHAR*) malloc(sizeof(TCHAR) * MAX_PATH);
    m_pszTestAppName = (TCHAR*) malloc(sizeof(TCHAR) * MAX_PATH);

    if ((NULL == m_pszLogFileName) || (NULL == m_pszTestAppName))
    {
        RETAILMSG(1, (_T("Error: CPerflog::Initialize : Out of memory")));
        goto done;
    }

    // Configure the output directory
    if (!SetPerfOutputDirectory())
    {
        RETAILMSG(1, (_T("Error: CPerflog::Initialize : SetPerfOutputDirectory() failed")));
        goto done;
    }

    // Copy the app name localy
    VERIFY(SUCCEEDED(StringCchCopy(m_pszTestAppName, MAX_PATH, pszTestName)));

    // Initialize the app name
    Perf_SetTestName(m_pszTestAppName);

    // Calibrate the perflog timer
    PerformCalibration();

    // Because the perflogger library does not provide an interface
    // to query the name of the output log file, we will search for a
    // file with a specific name pattern in the release directory
    // Capture the name of the file generated by perflog
    if (!FindLogFile())
    {
        RETAILMSG(1, (_T("Error: CPerflog::Initialize : FindLogFile() failed")));
        goto done;
    }

    // initialize the critical section
    m_lpCriticalSection = (LPCRITICAL_SECTION) malloc((size_t)sizeof(CRITICAL_SECTION));
    InitializeCriticalSection(m_lpCriticalSection);

    fRet = TRUE;
done:
    m_fInitSucceeded = fRet;
    return fRet;
}

// --------------------------------------------------------------------
// Initialize : performs timer calibration, initializes perf library
// and captures the name of the perflog output file.
// --------------------------------------------------------------------
BOOL CPerflog::Initialize(BOOL fUseReleaseDirectory)
{
    return Initialize(DEFAULT_PERF_TEST_NAME, fUseReleaseDirectory);
}

// --------------------------------------------------------------------
// Performs timer calibration
// --------------------------------------------------------------------
void CPerflog::PerformCalibration()
{
    for(int dwCount = 0; dwCount < CALIBRATION_COUNT; dwCount++)
    {
        Perf_MarkBegin(MARK_CALIBRATE);
        Perf_MarkEnd(MARK_CALIBRATE);
    }
}

// --------------------------------------------------------------------
// Helper method for configuring PERFLOG output directory
// --------------------------------------------------------------------
BOOL CPerflog::SetPerfOutputDirectory()
{
    BOOL fRet = FALSE;
    HKEY hKey = NULL;
    DWORD dwDisp = 0;
    DWORD dwValue = m_fUseReleaseDirectory ? 0 : 1;

    // PERFLOG.DLL uses the value from HLKM\Software\Microsoft\Perf
    // to determine whether to put the log file in the release directory
    // or in the root directory of the CE device
    if (ERROR_SUCCESS != RegCreateKeyEx(
        HKEY_LOCAL_MACHINE,
        _T("Software\\Microsoft\\Perf"),
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        0,
        NULL,
        &hKey,
        &dwDisp))
    {
        RETAILMSG(1, (_T("Error : CPerflog::SetPerfOutputDirectory : RegCreateKeyEx failed")));
        goto done;
    }

    if (ERROR_SUCCESS != RegSetValueEx(
        hKey,
        L"NoRelease",
        0,
        REG_DWORD,
        (const BYTE*) &dwValue,
        sizeof(DWORD)))
    {
        RETAILMSG(1, (_T("Error : CPerflog::SetPerfOutputDirectory : RegSetValueEx failed")));
        goto done;
    }

    fRet = TRUE;
done:
    // Close the registry key
    if (NULL != hKey)
    {
        RegCloseKey(hKey);
    }

    return fRet;
}

// --------------------------------------------------------------------
// Searches the appropriate directory for the log file
// --------------------------------------------------------------------
BOOL CPerflog::FindLogFile()
{
    BOOL fRet = FALSE;
    HANDLE hFindFile = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA findFileData = {0};
    TCHAR szSearchPattern[MAX_PATH] = _T("");

    // Set up the search pattern
    if (m_fUseReleaseDirectory)
    {
        VERIFY(SUCCEEDED(StringCchPrintf(
            szSearchPattern,
            MAX_PATH,
            _T("\\Release\\%s*_VER*.LOG"),
            m_pszTestAppName)));
    }
    else
    {
        VERIFY(SUCCEEDED(StringCchPrintf(
            szSearchPattern,
            MAX_PATH,
            _T("\\%s*_VER*.LOG"),
            m_pszTestAppName)));
    }

    hFindFile = FindFirstFile(szSearchPattern, &findFileData);

    if (INVALID_HANDLE_VALUE == hFindFile)
    {
        RETAILMSG(1, (_T("Error : CPerflog::FindLogFile() : FindFirstFile() failed")));
        goto done;
    }

    // Save original size of perflog file
    m_dwLastLogFileSize = findFileData.nFileSizeLow;

    // Save PERLOG.DLL output log file name
    if (m_fUseReleaseDirectory)
    {
        VERIFY(SUCCEEDED(StringCchPrintf(m_pszLogFileName,
            MAX_PATH,
            _T("\\Release\\%s"),
            findFileData.cFileName)));
    }
    else
    {
        VERIFY(SUCCEEDED(StringCchPrintf(m_pszLogFileName,
            MAX_PATH,
            _T("\\%s"),
            findFileData.cFileName)));
    }

    fRet = TRUE;
done:
    if (INVALID_HANDLE_VALUE != hFindFile)
    {
        FindClose(hFindFile);
    }
    return fRet;
}

// --------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------
CPerflog::CPerflog(LPCTSTR pszPerfMarkerName, LPCTSTR pszPerfMarkerParams)
{
    m_fLogStarted = FALSE;
    m_fSysMonStarted = FALSE;
    m_pszPerfMarkerName = NULL;
    m_pszPerfMarkerParams = NULL;
    m_pszPerfMarkerString = NULL;

    // update m_dwPerfMaker
    EnterCriticalSection(m_lpCriticalSection);
    m_dwPerfMaker = m_dwMarkerCount;
    m_dwMarkerCount++; // Increment the marker count
    LeaveCriticalSection(m_lpCriticalSection);

    m_pszPerfMarkerString = (TCHAR*) malloc(sizeof(TCHAR) * MAX_MARKER_LENGTH);
    m_pszPerfMarkerName = (TCHAR*) malloc(sizeof(TCHAR) * MAX_NAME_LENGTH);
    m_pszPerfMarkerParams = (TCHAR*) malloc(sizeof(TCHAR) * MAX_PARAM_LENGTH);
    if ((NULL == m_pszPerfMarkerName) ||
        (NULL == m_pszPerfMarkerParams) ||
        (NULL == m_pszPerfMarkerString))
    {
        RETAILMSG(1, (_T("Error : CPerflog::CPerflog() : Out of Memory")));
        return;
    }
    memset(m_pszPerfMarkerString, '\0', MAX_MARKER_LENGTH);

    // Copy the marker name
    if (NULL != pszPerfMarkerName)
    {
        VERIFY(SUCCEEDED(StringCchCopy(
            m_pszPerfMarkerName,
            MAX_NAME_LENGTH,
            pszPerfMarkerName)));
    }
    else
    {
        VERIFY(SUCCEEDED(StringCchCopy(
            m_pszPerfMarkerName,
            MAX_NAME_LENGTH,
            DEFAULT_PERF_MARKER_NAME)));
    }

    // Copy the marker parameters
    if (NULL != pszPerfMarkerParams)
    {
        VERIFY(SUCCEEDED(StringCchCopy(
            m_pszPerfMarkerParams,
            MAX_PARAM_LENGTH,
            pszPerfMarkerParams)));
    }
    else
    {
        VERIFY(SUCCEEDED(StringCchCopy(
            m_pszPerfMarkerParams,
            MAX_PARAM_LENGTH,
            DEFAULT_PERF_MARKER_PARAMS)));
    }

    // Concatinate marker parameters into one string
    VERIFY(SUCCEEDED(StringCchCatN(
        m_pszPerfMarkerString,
        MAX_MARKER_LENGTH,
        m_pszPerfMarkerName,
        MAX_NAME_LENGTH)));

    VERIFY(SUCCEEDED(StringCchCatN(
        m_pszPerfMarkerString,
        MAX_MARKER_LENGTH,
        m_pszPerfMarkerParams,
        MAX_PARAM_LENGTH)));


}

// --------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------
CPerflog::~CPerflog()
{
    CHECK_DELETE(m_pszPerfMarkerName);
    CHECK_DELETE(m_pszPerfMarkerParams);
    CHECK_DELETE(m_pszPerfMarkerString);
}

// Returns whether or not the perflog class has been initialized
// --------------------------------------------------------------------
BOOL CPerflog::CheckInit()
{
    BOOL fRet = m_fInitPeformed && m_fInitSucceeded;
    if (!fRet)
    {
        RETAILMSG(1, (_T("Error : CPerflog::CheckInit() : PERFLOG not initialized")));
    }
    return fRet;
}

// --------------------------------------------------------------------
// Starts log timer
// --------------------------------------------------------------------
BOOL CPerflog::StartLog()
{
    if (!CheckInit())
    {
        return FALSE;
    }

    // Check if the log is already running
    if (m_fLogStarted)
    {
        return FALSE;
    }

    if (!Perf_RegisterMark(m_dwPerfMaker, m_pszPerfMarkerString))
    {
        RETAILMSG(1, (_T("Error : CPerflog::StartLog() : Perf_RegisterMark() failed")));
        return FALSE;
    }

    if (!Perf_MarkBegin(m_dwPerfMaker))
    {
        RETAILMSG(1, (_T("Error : CPerflog::StartLog() : Perf_MarkBegin() failed")));
        return FALSE;
    }

    m_fLogStarted = TRUE;

    return TRUE;
}

// --------------------------------------------------------------------
// Stops log timer
// --------------------------------------------------------------------
BOOL CPerflog::EndLog()
{
    if (!CheckInit())
    {
        return FALSE;
    }

    // Check if the log has been started
    if (!m_fLogStarted)
    {
        return FALSE;
    }

    if (!Perf_MarkEnd(m_dwPerfMaker))
    {
        RETAILMSG(1, (_T("Error : CPerflog::StartLog() : Perf_MarkEnd() failed")));
        return FALSE;
    }

    m_fLogStarted = FALSE;

    return TRUE;
}

// --------------------------------------------------------------------
// Starts the sysmon thread with specified logging interval (in msec)
// --------------------------------------------------------------------
BOOL CPerflog::StartSystemMonitor(DWORD dwInterval)
{
    if (!CheckInit())
    {
        return FALSE;
    }

    // Check if the sysmon thread is already running
    if (m_fSysMonStarted)
    {
        return FALSE;
    }

    Perf_StartSysMonitor(
        m_pszPerfMarkerName,
        SYS_MON_CPU|SYS_MON_LOG,
        dwInterval,
        10);

    m_fSysMonStarted = TRUE;

    return TRUE;
}

// --------------------------------------------------------------------
// Stop the system monitor thread
// --------------------------------------------------------------------
BOOL CPerflog::StopSystemMonitor()
{
    if (!CheckInit())
    {
        return FALSE;
    }

    // Check if the sysmon thread is already running
    if (!m_fSysMonStarted)
    {
        return FALSE;
    }

    Perf_StopSysMonitor();

    m_fSysMonStarted = FALSE;

    return TRUE;
}

// --------------------------------------------------------------------
// Dumps new log contents into specified output file
// --------------------------------------------------------------------
BOOL CPerflog::DumpLogToFile(LPCTSTR pszFileName)
{
    BOOL fRet = FALSE;
    HANDLE hFileIn = INVALID_HANDLE_VALUE;
    HANDLE hFileOut = INVALID_HANDLE_VALUE;
    DWORD dwBytesToCopy = 0;
    DWORD dwBytesRead = 0;
    DWORD dwBytesWritten = 0;
    DWORD dwWriteSize = DEFAULT_WRITE_SIZE;
    PBYTE pBuffer = NULL;
    BY_HANDLE_FILE_INFORMATION fileInfo = {0};

    if (!CheckInit())
    {
        return FALSE;
    }

    // Check input parameter
    if (NULL == pszFileName)
    {
        RETAILMSG(1, (_T("Error : CPerflog::DumpToLogFile() : file name parameter is NULL")));
        goto done;
    }

    RETAILMSG(1, (_T("Info : CPerflog::DumpToLogFile() : Attempting to copy log file %s into %s starting at offset %u"),
        m_pszLogFileName,
        pszFileName,
        m_dwLastLogFileSize));

    // Allocate room for I/O buffer
    pBuffer = (LPBYTE)LocalAlloc(LMEM_FIXED, dwWriteSize);

    if (NULL == pBuffer)
    {
        RETAILMSG(1, (_T("Error : CPerflog::DumpToLogFile() : Out of Memory")));
        goto done;
    }

    // Open the log file for read
    hFileIn = CreateFile(
        m_pszLogFileName,
        GENERIC_READ,
        FILE_SHARE_READ|FILE_SHARE_WRITE,
        0,
        OPEN_EXISTING,
        0,
        0);

    if (INVALID_HANDLE_VALUE == hFileIn)
    {
        RETAILMSG(1, (_T("Error : CPerflog::DumpToLogFile() : CreateFile() failed")));
        goto done;
    }

    // Get the file size of the source file
    if (!GetFileInformationByHandle(hFileIn, &fileInfo))
    {
        RETAILMSG(1, (_T("Error : CPerflog::DumpToLogFile() : GetFileInformationByHandle() failed")));
        goto done;
    }

    dwBytesToCopy = fileInfo.nFileSizeLow - m_dwLastLogFileSize;

    if (0xFFFFFFFF == SetFilePointer(hFileIn, m_dwLastLogFileSize, NULL, FILE_BEGIN))
    {
        RETAILMSG(1, (_T("Error : CPerflog::DumpToLogFile() : Could not copy contents of log file %s"),
            m_pszLogFileName));
        goto done;
    }

    // Open the output file for write
    hFileOut = CreateFile(
        pszFileName,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (INVALID_HANDLE_VALUE == hFileOut)
    {
        RETAILMSG(1, (_T("Error : CPerflog::DumpToLogFile() : CreateFile() failed")));
        goto done;
    }

    // Start copying
    while (dwBytesToCopy > 0)
    {
        dwWriteSize = min(DEFAULT_WRITE_SIZE, dwBytesToCopy);
        // Read in data from source file
        if (!ReadFile(hFileIn, pBuffer, dwWriteSize, &dwBytesRead, NULL))
        {
            RETAILMSG(1, (_T("Error : CPerflog::DumpToLogFile() : ReadFile() failed")));
            goto done;
        }
        // Write data out to file
        if (!WriteFile(hFileOut, pBuffer, dwBytesRead, &dwBytesWritten, NULL))
        {
            RETAILMSG(1, (_T("Error : CPerflog::DumpToLogFile() : WriteFile() failed")));
            goto done;
        }
        dwBytesToCopy -=  dwBytesWritten;
    }

    fRet = TRUE;
done:
    // Clean up
    CHECK_CLOSE_HANDLE(hFileIn);
    CHECK_CLOSE_HANDLE(hFileOut);
    CHECK_LOCAL_FREE(pBuffer);

    return fRet;
}