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
#include <tchar.h>
#include <kato.h>
#include <tux.h>
#include "tuxmain.h"
#include "katolog.h"

#include <pm.h>
#include "pwrtstutil.h"

#ifndef UNDER_CE
#include <stdio.h>
#endif


// Global CKato logging object.  Set while processing SPM_LOAD_DLL message.
CKato *g_pKato = NULL;

// Global shell info structure.  Set while processing SPM_SHELL_INFO message.
SPS_SHELL_INFO *g_pShellInfo;

// Global critical section to be used by threaded tests if necessary.
CRITICAL_SECTION g_csProcess;

//******************************************************************************
//***** Windows CE specific code
//******************************************************************************
#ifdef UNDER_CE

#ifndef STARTF_USESIZE
#define STARTF_USESIZE     0x00000002
#endif

#ifndef STARTF_USEPOSITION
#define STARTF_USEPOSITION 0x00000004
#endif

#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset(Destination, 0, Length)
#endif

#ifndef _vsntprintf
#define _vsntprintf(d,c,f,a) wvsprintf(d,f,a)
#endif

BOOL WINAPI DllMain(HANDLE hInstance, ULONG dwReason, LPVOID lpReserved) {
   return TRUE;
}
#endif


//******************************************************************************
VOID Debug(LPCTSTR szFormat, ...) {
   const DWORD BUFF_SIZE            = 1024;
   const DWORD SMALL_BUFF_SIZE      = 16;
   TCHAR szBuffer[BUFF_SIZE]        = TEXT("");
   TCHAR szPrefix[SMALL_BUFF_SIZE]  = TEXT("IFDTESTTUX: ");
   TCHAR szPostfix[SMALL_BUFF_SIZE] = TEXT("\r\n");

   size_t dwPrefixLen;
   size_t dwPostfixLen;
   StringCchLength(szPrefix, SMALL_BUFF_SIZE, &dwPrefixLen);
   StringCchLength(szPostfix, SMALL_BUFF_SIZE, &dwPostfixLen);

   StringCchCat(szBuffer, BUFF_SIZE, szPrefix);

   va_list pArgs;
   va_start(pArgs, szFormat);

   size_t tempSize = (dwPrefixLen + dwPostfixLen < BUFF_SIZE) ? BUFF_SIZE - dwPrefixLen - dwPostfixLen : 0;
   if (dwPrefixLen < BUFF_SIZE && tempSize > 0)
   {
       StringCchVPrintf(szBuffer + dwPrefixLen,
                        tempSize,
                        szFormat,
                        pArgs);
   }
   va_end(pArgs);

   StringCchCat(szBuffer, BUFF_SIZE, szPostfix);

   g_pKato->Log(LOG_DETAIL, szBuffer);
}


void InitializeIFDTest();


//******************************************************************************
//***** ShellProc()
//******************************************************************************

SHELLPROCAPI ShellProc(UINT uMsg, SPPARAM spParam) {

   switch (uMsg) {

      //------------------------------------------------------------------------
      // Message: SPM_LOAD_DLL
      //
      // Sent once to the DLL immediately after it is loaded.  The spParam
      // parameter will contain a pointer to a SPS_LOAD_DLL structure.  The DLL
      // should set the fUnicode member of this structre to TRUE if the DLL is
      // built with the UNICODE flag set.  By setting this flag, Tux will ensure
      // that all strings passed to your DLL will be in UNICODE format, and all
      // strings within your function table will be processed by Tux as UNICODE.
      // The DLL may return SPR_FAIL to prevent the DLL from continuing to load.
      //------------------------------------------------------------------------

      case SPM_LOAD_DLL: {
         // If we are UNICODE, then tell Tux this by setting the following flag.
         #ifdef UNICODE
            ((LPSPS_LOAD_DLL)spParam)->fUnicode = TRUE;
         #endif

         // Get/Create our global logging object.
         g_pKato = (CKato*)KatoGetDefaultObject();

         // Initialize our global critical section.
         InitializeCriticalSection(&g_csProcess);

         Debug(TEXT("ShellProc(SPM_LOAD_DLL, ...) called"));
         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_UNLOAD_DLL
      //
      // Sent once to the DLL immediately before it is unloaded.
      //------------------------------------------------------------------------

      case SPM_UNLOAD_DLL: {
         Debug(TEXT("ShellProc(SPM_UNLOAD_DLL, ...) called"));

         // This is a good place to delete our global critical section.
         DeleteCriticalSection(&g_csProcess);

         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_SHELL_INFO
      //
      // Sent once to the DLL immediately after SPM_LOAD_DLL to give the DLL
      // some useful information about its parent shell and environment.  The
      // spParam parameter will contain a pointer to a SPS_SHELL_INFO structure.
      // The pointer to the structure may be stored for later use as it will
      // remain valid for the life of this Tux Dll.  The DLL may return SPR_FAIL
      // to prevent the DLL from continuing to load.
      //------------------------------------------------------------------------

      case SPM_SHELL_INFO: {
         Debug(TEXT("ShellProc(SPM_SHELL_INFO, ...) called"));

         // Store a pointer to our shell info for later use.
         g_pShellInfo = (LPSPS_SHELL_INFO)spParam;

         // Display our Dlls command line if we have one.
         if (g_pShellInfo->szDllCmdLine && *g_pShellInfo->szDllCmdLine) {
#ifdef UNDER_CE
            Debug(TEXT("Command Line: \"%s\"."), g_pShellInfo->szDllCmdLine);
#else
            MessageBox(g_pShellInfo->hWnd, g_pShellInfo->szDllCmdLine,
                       TEXT("IFDTESTTUX.DLL Command Line Arguments"), MB_OK);
#endif UNDER_CE
         }

         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_REGISTER
      //
      // This is the only ShellProc() message that a DLL is required to handle
      // (except for SPM_LOAD_DLL if you are UNICODE).  This message is sent
      // once to the DLL immediately after the SPM_SHELL_INFO message to query
      // the DLL for its function table.  The spParam will contain a pointer to
      // a SPS_REGISTER structure.  The DLL should store its function table in
      // the lpFunctionTable member of the SPS_REGISTER structure.  The DLL may
      // return SPR_FAIL to prevent the DLL from continuing to load.
      //------------------------------------------------------------------------

      case SPM_REGISTER: {
         Debug(TEXT("ShellProc(SPM_REGISTER, ...) called"));
         ((LPSPS_REGISTER)spParam)->lpFunctionTable = g_lpFTE;
         #ifdef UNICODE
            return SPR_HANDLED | SPF_UNICODE;
         #else
            return SPR_HANDLED;
         #endif
      }

      //------------------------------------------------------------------------
      // Message: SPM_START_SCRIPT
      //
      // Sent to the DLL immediately before a script is started.  It is sent to
      // all Tux DLLs, including loaded Tux DLLs that are not in the script.
      // All DLLs will receive this message before the first TestProc() in the
      // script is called.
      //------------------------------------------------------------------------

      case SPM_START_SCRIPT: {
         Debug(TEXT("ShellProc(SPM_START_SCRIPT, ...) called"));
         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_STOP_SCRIPT
      //
      // Sent to the DLL when the script has stopped.  This message is sent when
      // the script reaches its end, or because the user pressed stopped prior
      // to the end of the script.  This message is sent to all Tux DLLs,
      // including loaded Tux DLLs that are not in the script.
      //------------------------------------------------------------------------

      case SPM_STOP_SCRIPT: {
         Debug(TEXT("ShellProc(SPM_STOP_SCRIPT, ...) called"));
         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_BEGIN_DLL
      //
      // Sent to the DLL before a group of tests from that DLL is about to be
      // executed.  This gives the DLL a time to initialize or allocate data for
      // the tests to follow.  Only the DLL that is next to run receives this
      // message.  The prior DLL, if any, will first receive a SPM_END_DLL
      // message.  For global initialization and de-initialization, the DLL
      // should probably use SPM_START_SCRIPT and SPM_STOP_SCRIPT, or even
      // SPM_LOAD_DLL and SPM_UNLOAD_DLL.
      //
      // The DLL may return SPR_FAIL to cause all tests in this dll to be
      // skipped.
      //------------------------------------------------------------------------

      case SPM_BEGIN_DLL: {
         Debug(TEXT("ShellProc(SPM_BEGIN_DLL, ...) called"));
         g_pKato->BeginLevel(0, TEXT("BEGIN DLL: IFDTESTTUX.DLL"));

         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_END_DLL
      //
      // Sent to the DLL after a group of tests from that DLL has completed
      // running.  This gives the DLL a time to cleanup after it has been run.
      // This message does not mean that the DLL will not be called again to run
      // tests; it just means that the next test to run belongs to a different
      // DLL.  SPM_BEGIN_DLL and SPM_END_DLL allow the DLL to track when it
      // is active and when it is not active.
      //------------------------------------------------------------------------

      case SPM_END_DLL: {
         Debug(TEXT("ShellProc(SPM_END_DLL, ...) called"));
         g_pKato->EndLevel(TEXT("END DLL: IFDTESTTUX.DLL"));
         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_BEGIN_TEST
      //
      // Sent to the DLL immediately before a test executes.  This gives the DLL
      // a chance to perform any common action that occurs at the beginning of
      // each test, such as entering a new logging level.  The spParam parameter
      // will contain a pointer to a SPS_BEGIN_TEST structure, which contains
      // the function table entry and some other useful information for the next
      // test to execute.  If the ShellProc function returns SPR_SKIP, then the
      // test case will not execute.
      //------------------------------------------------------------------------

      case SPM_BEGIN_TEST: {
         Debug(TEXT("ShellProc(SPM_BEGIN_TEST, ...) called"));

         // Start our logging level.
         LPSPS_BEGIN_TEST pBT = (LPSPS_BEGIN_TEST)spParam;
         g_pKato->BeginLevel(pBT->lpFTE->dwUniqueID,
                             TEXT("BEGIN TEST: \"%s\", Threads=%u, Seed=%u"),
                             pBT->lpFTE->lpDescription, pBT->dwThreadCount,
                             pBT->dwRandomSeed);

         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_END_TEST
      //
      // Sent to the DLL after a single test executes from the DLL.  This gives
      // the DLL a time perform any common action that occurs at the completion
      // of each test, such as exiting the current logging level.  The spParam
      // parameter will contain a pointer to a SPS_END_TEST structure, which
      // contains the function table entry and some other useful information for
      // the test that just completed.
      //------------------------------------------------------------------------

      case SPM_END_TEST: {
         Debug(TEXT("ShellProc(SPM_END_TEST, ...) called"));

         // End our logging level.
         LPSPS_END_TEST pET = (LPSPS_END_TEST)spParam;
         g_pKato->EndLevel(TEXT("END TEST: \"%s\", %s, Time=%u.%03u"),
                           pET->lpFTE->lpDescription,
                           pET->dwResult == TPR_SKIP ? TEXT("SKIPPED") :
                           pET->dwResult == TPR_PASS ? TEXT("PASSED") :
                           pET->dwResult == TPR_FAIL ? TEXT("FAILED") : TEXT("ABORTED"),
                           pET->dwExecutionTime / 1000, pET->dwExecutionTime % 1000);

         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_EXCEPTION
      //
      // Sent to the DLL whenever code execution in the DLL causes and exception
      // fault.  By default, Tux traps all exceptions that occur while executing
      // code inside a Tux DLL.
      //------------------------------------------------------------------------

      case SPM_EXCEPTION: {
         Debug(TEXT("ShellProc(SPM_EXCEPTION, ...) called"));
         g_pKato->Log(LOG_EXCEPTION, TEXT("Exception occurred!"));
         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_SETUP_GROUP
      //
      // Sent to the DLL whenever a new group of tests is about to run.
      // A 'group' is defined as a series of tests that are listed after a
      // FUNCTION_TABLE_ENTRY with lpTestProc = NULL.
      //
      // The DLL may return SPR_FAIL to cause all tests in this group to be
      // skipped.
      //------------------------------------------------------------------------

      case SPM_SETUP_GROUP: {
         LPSPS_SETUP_GROUP pSG = (LPSPS_SETUP_GROUP) spParam;
         Debug(TEXT("ShellProc(SPM_SETUP_GROUP, ...) called"));

         return SPR_HANDLED;
      }

      //------------------------------------------------------------------------
      // Message: SPM_TEARDOWN_GROUP
      //
      // Sent to the DLL whenever a group of tests has finished running. See
      // the handler for SPM_SETUP_GROUP for more information about this grouping.
      //
      // The DLL's return value is ignored.
      //------------------------------------------------------------------------

      case SPM_TEARDOWN_GROUP: {
         LPSPS_TEARDOWN_GROUP pTG = (LPSPS_TEARDOWN_GROUP) spParam;
         Debug(TEXT("ShellProc(SPM_TEARDOWN_GROUP, ...) called"));

         return SPR_HANDLED;
      }
   }

   return SPR_NOT_HANDLED;
}

//******************************************************************************
//***** TestProc()'s
//******************************************************************************
