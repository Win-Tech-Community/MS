/*++

Copyright (c) 1997-1999 Microsoft Corporation

Module Name:

    MSPLOG.h

Abstract:

    Definitions for logging support.

--*/

#ifndef _MSPLOG_H_
    #define _MSPLOG_H_

    #ifdef MSPLOG

        #include <rtutils.h>

        #define MSP_ERROR ((DWORD)0x00010000 | TRACE_USE_MASK)
        #define MSP_WARN  ((DWORD)0x00020000 | TRACE_USE_MASK)
        #define MSP_INFO  ((DWORD)0x00040000 | TRACE_USE_MASK)
        #define MSP_TRACE ((DWORD)0x00080000 | TRACE_USE_MASK)
        #define MSP_EVENT ((DWORD)0x00100000 | TRACE_USE_MASK)

        BOOL NTAPI MSPLogRegister(LPCTSTR szName);
        void NTAPI MSPLogDeRegister();
        void NTAPI LogPrint(IN DWORD dwDbgLevel, IN LPCSTR DbgMessage, IN ...);

        #define MSPLOGREGISTER(arg) MSPLogRegister(arg)
        #define MSPLOGDEREGISTER() MSPLogDeRegister()
        #define LOG(arg) LogPrint arg

    #else // MSPLOG

        #define MSPLOGREGISTER(arg)
        #define MSPLOGDEREGISTER() 
        #define LOG(arg)

    #endif // MSPLOG

    
    #define DECLARE_LOG_ADDREF_RELEASE(x)
    #define CMSPComObject CComObject

#endif // _MSPLOG_H_
