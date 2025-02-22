/*++

Copyright (c) 1997-1999 Microsoft Corporation

Module Name:

    rpcasync.h

Abstract:

    This module contains the RPC runtime APIs needed to use
    [async] RPC features.

--*/

#ifndef __RPCASYNC_H__
#define __RPCASYNC_H__

#if _MSC_VER > 1000
#pragma once
#endif

#if defined(__RPC_WIN64__)
#include <pshpack8.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define RPC_ASYNC_VERSION_1_0     sizeof(RPC_ASYNC_STATE)

typedef
enum _RPC_NOTIFICATION_TYPES
{
    RpcNotificationTypeNone,
    RpcNotificationTypeEvent,
    RpcNotificationTypeApc,
    RpcNotificationTypeIoc,
    RpcNotificationTypeHwnd,
    RpcNotificationTypeCallback
} RPC_NOTIFICATION_TYPES;

typedef
enum _RPC_ASYNC_EVENT {
    RpcCallComplete,
    RpcSendComplete,
    RpcReceiveComplete
    } RPC_ASYNC_EVENT;

struct _RPC_ASYNC_STATE;

typedef void RPC_ENTRY
RPCNOTIFICATION_ROUTINE (
                  struct _RPC_ASYNC_STATE *pAsync,
                  void *Context,
                  RPC_ASYNC_EVENT Event);
typedef RPCNOTIFICATION_ROUTINE *PFN_RPCNOTIFICATION_ROUTINE;

typedef struct _RPC_ASYNC_STATE {
    unsigned int    Size; // size of this structure
    unsigned long   Signature;
    long   Lock;
    unsigned long   Flags;
    void           *StubInfo;
    void           *UserInfo;
    void           *RuntimeInfo;
    RPC_ASYNC_EVENT Event;

    RPC_NOTIFICATION_TYPES NotificationType;
    union {
        //
        // Notification by APC
        //
        struct {
            PFN_RPCNOTIFICATION_ROUTINE NotificationRoutine;
            HANDLE hThread;
            } APC;

        //
        // Notification by IO completion port
        //
        struct {
            HANDLE hIOPort;
            DWORD dwNumberOfBytesTransferred;
            DWORD_PTR dwCompletionKey;
            LPOVERLAPPED lpOverlapped;
            } IOC;

        //
        // Notification by window message
        //
        struct {
            HWND hWnd;
            UINT Msg;
            } HWND;


        //
        // Notification by event
        //
        HANDLE hEvent;

        //
        // Notification by callback function
        //
        // This option is available only to OLE
        //
        PFN_RPCNOTIFICATION_ROUTINE NotificationRoutine;
        } u;

    LONG_PTR Reserved[4];
    } RPC_ASYNC_STATE, *PRPC_ASYNC_STATE;

// Possible values for Flags
#define RPC_C_NOTIFY_ON_SEND_COMPLETE      0x1
#define RPC_C_INFINITE_TIMEOUT             INFINITE

#define RpcAsyncGetCallHandle(pAsync) (((PRPC_ASYNC_STATE) pAsync)->RuntimeInfo)

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncInitializeHandle (
    PRPC_ASYNC_STATE pAsync,
    unsigned int     Size
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncRegisterInfo (
    PRPC_ASYNC_STATE pAsync
    ) ;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncGetCallStatus (
    PRPC_ASYNC_STATE pAsync
    ) ;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncCompleteCall (
    PRPC_ASYNC_STATE pAsync,
    void *Reply
    ) ;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncAbortCall (
    PRPC_ASYNC_STATE pAsync,
    unsigned long ExceptionCode
    ) ;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncCancelCall (
    IN PRPC_ASYNC_STATE pAsync,
    IN BOOL fAbort
    ) ;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncCleanupThread (
    IN DWORD dwTimeout
    );

typedef enum tagExtendedErrorParamTypes
{
    eeptAnsiString = 1,
    eeptUnicodeString,
    eeptLongVal,
    eeptShortVal,
    eeptPointerVal,
    eeptNone
} ExtendedErrorParamTypes;

#define MaxNumberOfEEInfoParams    4
#define RPC_EEINFO_VERSION         1

typedef struct tagRPC_EE_INFO_PARAM
{
    ExtendedErrorParamTypes ParameterType;
    union
        {
        LPSTR AnsiString;
        LPWSTR UnicodeString;
        long LVal;
        short SVal;
        ULONGLONG PVal;
        } u;
} RPC_EE_INFO_PARAM;

#define EEInfoPreviousRecordsMissing     1
#define EEInfoNextRecordsMissing         2
#define EEInfoUseFileTime                4

typedef struct tagRPC_EXTENDED_ERROR_INFO
{
    ULONG Version;
    LPWSTR ComputerName;
    ULONG ProcessID;
    union
        {
        SYSTEMTIME SystemTime;
        FILETIME FileTime;
        } u;
    ULONG GeneratingComponent;
    ULONG Status;
    USHORT DetectionLocation;
    USHORT Flags;
    int NumberOfParameters;
    RPC_EE_INFO_PARAM Parameters[MaxNumberOfEEInfoParams];
} RPC_EXTENDED_ERROR_INFO;

typedef struct tagRPC_ERROR_ENUM_HANDLE
{
    ULONG Signature;
    void *CurrentPos;
    void *Head;
} RPC_ERROR_ENUM_HANDLE;

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorStartEnumeration (
    IN OUT RPC_ERROR_ENUM_HANDLE *EnumHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorGetNextRecord (
    IN RPC_ERROR_ENUM_HANDLE *EnumHandle, 
    IN BOOL CopyStrings, 
    OUT RPC_EXTENDED_ERROR_INFO *ErrorInfo
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorEndEnumeration (
    IN OUT RPC_ERROR_ENUM_HANDLE *EnumHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorResetEnumeration (
    IN OUT RPC_ERROR_ENUM_HANDLE *EnumHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorGetNumberOfRecords (
    IN RPC_ERROR_ENUM_HANDLE *EnumHandle, 
    OUT int *Records
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorSaveErrorInfo (
    IN RPC_ERROR_ENUM_HANDLE *EnumHandle, 
    OUT PVOID *ErrorBlob, 
    OUT size_t *BlobSize
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorLoadErrorInfo (
    IN PVOID ErrorBlob, 
    IN size_t BlobSize, 
    OUT RPC_ERROR_ENUM_HANDLE *EnumHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorAddRecord (
    IN RPC_EXTENDED_ERROR_INFO *ErrorInfo
    );

RPCRTAPI
void 
RPC_ENTRY
RpcErrorClearInformation (
    void
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcGetAuthorizationContextForClient (
    IN RPC_BINDING_HANDLE ClientBinding OPTIONAL,
    IN BOOL ImpersonateOnReturn,
    IN PVOID Reserved1,
    IN PLARGE_INTEGER pExpirationTime OPTIONAL,
    IN LUID Reserved2,
    IN DWORD Reserved3,
    IN PVOID Reserved4,
    OUT PVOID *pAuthzClientContext
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcFreeAuthorizationContext (
    IN OUT PVOID *pAuthzClientContext
    );

//
// Internal APIs
//
RPC_STATUS RPC_ENTRY
I_RpcAsyncSetHandle (
    IN  PRPC_MESSAGE Message,
    IN  PRPC_ASYNC_STATE pAsync
    );

RPC_STATUS RPC_ENTRY
I_RpcAsyncAbortCall (
    IN PRPC_ASYNC_STATE pAsync,
    IN unsigned long ExceptionCode
    ) ;

#ifdef __cplusplus
}
#endif

#if defined(__RPC_WIN64__)
#include <poppack.h>
#endif

#endif /* __RPCASYNC_H__ */

