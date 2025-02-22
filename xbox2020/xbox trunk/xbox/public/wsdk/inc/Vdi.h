/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Fri Jun 12 10:46:49 1998
 */
/* Compiler settings for vdi.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __vdi_h__
#define __vdi_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IClientVirtualDevice_FWD_DEFINED__
#define __IClientVirtualDevice_FWD_DEFINED__
typedef interface IClientVirtualDevice IClientVirtualDevice;
#endif 	/* __IClientVirtualDevice_FWD_DEFINED__ */


#ifndef __IClientVirtualDeviceSet_FWD_DEFINED__
#define __IClientVirtualDeviceSet_FWD_DEFINED__
typedef interface IClientVirtualDeviceSet IClientVirtualDeviceSet;
#endif 	/* __IClientVirtualDeviceSet_FWD_DEFINED__ */


#ifndef __IServerVirtualDevice_FWD_DEFINED__
#define __IServerVirtualDevice_FWD_DEFINED__
typedef interface IServerVirtualDevice IServerVirtualDevice;
#endif 	/* __IServerVirtualDevice_FWD_DEFINED__ */


#ifndef __IServerVirtualDeviceSet_FWD_DEFINED__
#define __IServerVirtualDeviceSet_FWD_DEFINED__
typedef interface IServerVirtualDeviceSet IServerVirtualDeviceSet;
#endif 	/* __IServerVirtualDeviceSet_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_vdi_0000
 * at Fri Jun 12 10:46:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 



#pragma pack(push, _vdi_h_)

#pragma pack(8)
struct  VDConfig
    {
    unsigned long deviceCount;
    unsigned long features;
    unsigned long prefixZoneSize;
    unsigned long alignment;
    unsigned long softFileMarkBlockSize;
    unsigned long EOMWarningSize;
    unsigned long serverTimeOut;
    unsigned long blockSize;
    unsigned long maxIODepth;
    unsigned long maxTransferSize;
    unsigned long bufferAreaSize;
    };

enum VDFeatures
    {	VDF_Removable	= 0x1,
	VDF_Rewind	= 0x2,
	VDF_Position	= 0x10,
	VDF_SkipBlocks	= 0x20,
	VDF_ReversePosition	= 0x40,
	VDF_Discard	= 0x80,
	VDF_FileMarks	= 0x100,
	VDF_RandomAccess	= 0x200,
	VDF_WriteMedia	= 0x10000,
	VDF_ReadMedia	= 0x20000,
	VDF_LatchStats	= 0x80000000,
	VDF_LikePipe	= 0,
	VDF_LikeTape	= VDF_FileMarks | VDF_Removable | VDF_Rewind | VDF_Position | VDF_SkipBlocks | VDF_ReversePosition,
	VDF_LikeDisk	= VDF_RandomAccess
    };

enum VDCommands
    {	VDC_Read	= 1,
	VDC_Write	= VDC_Read + 1,
	VDC_ClearError	= VDC_Write + 1,
	VDC_Rewind	= VDC_ClearError + 1,
	VDC_WriteMark	= VDC_Rewind + 1,
	VDC_SkipMarks	= VDC_WriteMark + 1,
	VDC_SkipBlocks	= VDC_SkipMarks + 1,
	VDC_Load	= VDC_SkipBlocks + 1,
	VDC_GetPosition	= VDC_Load + 1,
	VDC_SetPosition	= VDC_GetPosition + 1,
	VDC_Discard	= VDC_SetPosition + 1,
	VDC_Flush	= VDC_Discard + 1
    };

enum VDWhence
    {	VDC_Beginning	= 0,
	VDC_Current	= VDC_Beginning + 1,
	VDC_End	= VDC_Current + 1
    };
struct  VDC_Command
    {
    DWORD commandCode;
    DWORD size;
    DWORDLONG position;
    BYTE __RPC_FAR *buffer;
    };


extern RPC_IF_HANDLE __MIDL_itf_vdi_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vdi_0000_v0_0_s_ifspec;

#ifndef __IClientVirtualDevice_INTERFACE_DEFINED__
#define __IClientVirtualDevice_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IClientVirtualDevice
 * at Fri Jun 12 10:46:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IClientVirtualDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("40700424-0080-11d2-851f-00c04fc21759")
    IClientVirtualDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCommand( 
            /* [in] */ DWORD dwTimeOut,
            /* [out] */ struct VDC_Command __RPC_FAR *__RPC_FAR *ppCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompleteCommand( 
            /* [in] */ struct VDC_Command __RPC_FAR *pCmd,
            /* [in] */ DWORD dwCompletionCode,
            /* [in] */ DWORD dwBytesTransferred,
            /* [in] */ DWORDLONG dwlPosition) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClientVirtualDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClientVirtualDevice __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClientVirtualDevice __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClientVirtualDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommand )( 
            IClientVirtualDevice __RPC_FAR * This,
            /* [in] */ DWORD dwTimeOut,
            /* [out] */ struct VDC_Command __RPC_FAR *__RPC_FAR *ppCmd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CompleteCommand )( 
            IClientVirtualDevice __RPC_FAR * This,
            /* [in] */ struct VDC_Command __RPC_FAR *pCmd,
            /* [in] */ DWORD dwCompletionCode,
            /* [in] */ DWORD dwBytesTransferred,
            /* [in] */ DWORDLONG dwlPosition);
        
        END_INTERFACE
    } IClientVirtualDeviceVtbl;

    interface IClientVirtualDevice
    {
        CONST_VTBL struct IClientVirtualDeviceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClientVirtualDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClientVirtualDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClientVirtualDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClientVirtualDevice_GetCommand(This,dwTimeOut,ppCmd)	\
    (This)->lpVtbl -> GetCommand(This,dwTimeOut,ppCmd)

#define IClientVirtualDevice_CompleteCommand(This,pCmd,dwCompletionCode,dwBytesTransferred,dwlPosition)	\
    (This)->lpVtbl -> CompleteCommand(This,pCmd,dwCompletionCode,dwBytesTransferred,dwlPosition)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IClientVirtualDevice_GetCommand_Proxy( 
    IClientVirtualDevice __RPC_FAR * This,
    /* [in] */ DWORD dwTimeOut,
    /* [out] */ struct VDC_Command __RPC_FAR *__RPC_FAR *ppCmd);


void __RPC_STUB IClientVirtualDevice_GetCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClientVirtualDevice_CompleteCommand_Proxy( 
    IClientVirtualDevice __RPC_FAR * This,
    /* [in] */ struct VDC_Command __RPC_FAR *pCmd,
    /* [in] */ DWORD dwCompletionCode,
    /* [in] */ DWORD dwBytesTransferred,
    /* [in] */ DWORDLONG dwlPosition);


void __RPC_STUB IClientVirtualDevice_CompleteCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClientVirtualDevice_INTERFACE_DEFINED__ */


#ifndef __IClientVirtualDeviceSet_INTERFACE_DEFINED__
#define __IClientVirtualDeviceSet_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IClientVirtualDeviceSet
 * at Fri Jun 12 10:46:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IClientVirtualDeviceSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("40700425-0080-11d2-851f-00c04fc21759")
    IClientVirtualDeviceSet : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LPCWSTR lpName,
            /* [in] */ struct VDConfig __RPC_FAR *pCfg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConfiguration( 
            /* [in] */ DWORD dwTimeOut,
            /* [out] */ struct VDConfig __RPC_FAR *pCfg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenDevice( 
            /* [in] */ LPCWSTR lpName,
            /* [out] */ IClientVirtualDevice __RPC_FAR *__RPC_FAR *ppVirtualDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SignalAbort( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenInSecondary( 
            /* [in] */ LPCWSTR lpSetName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBufferHandle( 
            /* [in] */ BYTE __RPC_FAR *pBuffer,
            /* [out] */ DWORD __RPC_FAR *pBufferHandle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapBufferHandle( 
            /* [in] */ DWORD dwBuffer,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClientVirtualDeviceSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClientVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClientVirtualDeviceSet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClientVirtualDeviceSet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IClientVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ LPCWSTR lpName,
            /* [in] */ struct VDConfig __RPC_FAR *pCfg);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfiguration )( 
            IClientVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ DWORD dwTimeOut,
            /* [out] */ struct VDConfig __RPC_FAR *pCfg);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenDevice )( 
            IClientVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ LPCWSTR lpName,
            /* [out] */ IClientVirtualDevice __RPC_FAR *__RPC_FAR *ppVirtualDevice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IClientVirtualDeviceSet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SignalAbort )( 
            IClientVirtualDeviceSet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenInSecondary )( 
            IClientVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ LPCWSTR lpSetName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBufferHandle )( 
            IClientVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *pBuffer,
            /* [out] */ DWORD __RPC_FAR *pBufferHandle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapBufferHandle )( 
            IClientVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ DWORD dwBuffer,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer);
        
        END_INTERFACE
    } IClientVirtualDeviceSetVtbl;

    interface IClientVirtualDeviceSet
    {
        CONST_VTBL struct IClientVirtualDeviceSetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClientVirtualDeviceSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClientVirtualDeviceSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClientVirtualDeviceSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClientVirtualDeviceSet_Create(This,lpName,pCfg)	\
    (This)->lpVtbl -> Create(This,lpName,pCfg)

#define IClientVirtualDeviceSet_GetConfiguration(This,dwTimeOut,pCfg)	\
    (This)->lpVtbl -> GetConfiguration(This,dwTimeOut,pCfg)

#define IClientVirtualDeviceSet_OpenDevice(This,lpName,ppVirtualDevice)	\
    (This)->lpVtbl -> OpenDevice(This,lpName,ppVirtualDevice)

#define IClientVirtualDeviceSet_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IClientVirtualDeviceSet_SignalAbort(This)	\
    (This)->lpVtbl -> SignalAbort(This)

#define IClientVirtualDeviceSet_OpenInSecondary(This,lpSetName)	\
    (This)->lpVtbl -> OpenInSecondary(This,lpSetName)

#define IClientVirtualDeviceSet_GetBufferHandle(This,pBuffer,pBufferHandle)	\
    (This)->lpVtbl -> GetBufferHandle(This,pBuffer,pBufferHandle)

#define IClientVirtualDeviceSet_MapBufferHandle(This,dwBuffer,ppBuffer)	\
    (This)->lpVtbl -> MapBufferHandle(This,dwBuffer,ppBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IClientVirtualDeviceSet_Create_Proxy( 
    IClientVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ LPCWSTR lpName,
    /* [in] */ struct VDConfig __RPC_FAR *pCfg);


void __RPC_STUB IClientVirtualDeviceSet_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClientVirtualDeviceSet_GetConfiguration_Proxy( 
    IClientVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ DWORD dwTimeOut,
    /* [out] */ struct VDConfig __RPC_FAR *pCfg);


void __RPC_STUB IClientVirtualDeviceSet_GetConfiguration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClientVirtualDeviceSet_OpenDevice_Proxy( 
    IClientVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ LPCWSTR lpName,
    /* [out] */ IClientVirtualDevice __RPC_FAR *__RPC_FAR *ppVirtualDevice);


void __RPC_STUB IClientVirtualDeviceSet_OpenDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClientVirtualDeviceSet_Close_Proxy( 
    IClientVirtualDeviceSet __RPC_FAR * This);


void __RPC_STUB IClientVirtualDeviceSet_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClientVirtualDeviceSet_SignalAbort_Proxy( 
    IClientVirtualDeviceSet __RPC_FAR * This);


void __RPC_STUB IClientVirtualDeviceSet_SignalAbort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClientVirtualDeviceSet_OpenInSecondary_Proxy( 
    IClientVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ LPCWSTR lpSetName);


void __RPC_STUB IClientVirtualDeviceSet_OpenInSecondary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClientVirtualDeviceSet_GetBufferHandle_Proxy( 
    IClientVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *pBuffer,
    /* [out] */ DWORD __RPC_FAR *pBufferHandle);


void __RPC_STUB IClientVirtualDeviceSet_GetBufferHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IClientVirtualDeviceSet_MapBufferHandle_Proxy( 
    IClientVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ DWORD dwBuffer,
    /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer);


void __RPC_STUB IClientVirtualDeviceSet_MapBufferHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClientVirtualDeviceSet_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_vdi_0007
 * at Fri Jun 12 10:46:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


struct  VDS_Command
    {
    DWORD commandCode;
    DWORD size;
    DWORDLONG inPosition;
    DWORDLONG outPosition;
    BYTE __RPC_FAR *buffer;
    BYTE __RPC_FAR *completionRoutine;
    BYTE __RPC_FAR *completionContext;
    DWORD completionCode;
    DWORD bytesTransferred;
    };


extern RPC_IF_HANDLE __MIDL_itf_vdi_0007_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vdi_0007_v0_0_s_ifspec;

#ifndef __IServerVirtualDevice_INTERFACE_DEFINED__
#define __IServerVirtualDevice_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IServerVirtualDevice
 * at Fri Jun 12 10:46:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IServerVirtualDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("b5e7a131-a7bd-11d1-84c2-00c04fc21759")
    IServerVirtualDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendCommand( 
            /* [in] */ struct VDS_Command __RPC_FAR *pCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CloseDevice( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IServerVirtualDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IServerVirtualDevice __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IServerVirtualDevice __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IServerVirtualDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCommand )( 
            IServerVirtualDevice __RPC_FAR * This,
            /* [in] */ struct VDS_Command __RPC_FAR *pCmd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseDevice )( 
            IServerVirtualDevice __RPC_FAR * This);
        
        END_INTERFACE
    } IServerVirtualDeviceVtbl;

    interface IServerVirtualDevice
    {
        CONST_VTBL struct IServerVirtualDeviceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServerVirtualDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IServerVirtualDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IServerVirtualDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IServerVirtualDevice_SendCommand(This,pCmd)	\
    (This)->lpVtbl -> SendCommand(This,pCmd)

#define IServerVirtualDevice_CloseDevice(This)	\
    (This)->lpVtbl -> CloseDevice(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IServerVirtualDevice_SendCommand_Proxy( 
    IServerVirtualDevice __RPC_FAR * This,
    /* [in] */ struct VDS_Command __RPC_FAR *pCmd);


void __RPC_STUB IServerVirtualDevice_SendCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDevice_CloseDevice_Proxy( 
    IServerVirtualDevice __RPC_FAR * This);


void __RPC_STUB IServerVirtualDevice_CloseDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IServerVirtualDevice_INTERFACE_DEFINED__ */


#ifndef __IServerVirtualDeviceSet_INTERFACE_DEFINED__
#define __IServerVirtualDeviceSet_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IServerVirtualDeviceSet
 * at Fri Jun 12 10:46:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IServerVirtualDeviceSet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("b5e7a132-a7bd-11d1-84c2-00c04fc21759")
    IServerVirtualDeviceSet : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ LPCWSTR lpName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConfiguration( 
            /* [out] */ struct VDConfig __RPC_FAR *pCfg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetConfiguration( 
            /* [in] */ struct VDConfig __RPC_FAR *pCfg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ExecuteCompletionAgent( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenDevice( 
            /* [in] */ LPCWSTR lpName,
            /* [out] */ IServerVirtualDevice __RPC_FAR *__RPC_FAR *ppVirtualDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AllocateBuffer( 
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer,
            /* [in] */ DWORD dwSize,
            /* [in] */ DWORD dwAlignment) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeBuffer( 
            /* [in] */ BYTE __RPC_FAR *pBuffer,
            /* [in] */ DWORD dwSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsSharedBuffer( 
            /* [in] */ BYTE __RPC_FAR *pBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SignalAbort( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IServerVirtualDeviceSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IServerVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IServerVirtualDeviceSet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IServerVirtualDeviceSet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IServerVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ LPCWSTR lpName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfiguration )( 
            IServerVirtualDeviceSet __RPC_FAR * This,
            /* [out] */ struct VDConfig __RPC_FAR *pCfg);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfiguration )( 
            IServerVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ struct VDConfig __RPC_FAR *pCfg);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecuteCompletionAgent )( 
            IServerVirtualDeviceSet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenDevice )( 
            IServerVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ LPCWSTR lpName,
            /* [out] */ IServerVirtualDevice __RPC_FAR *__RPC_FAR *ppVirtualDevice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateBuffer )( 
            IServerVirtualDeviceSet __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer,
            /* [in] */ DWORD dwSize,
            /* [in] */ DWORD dwAlignment);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeBuffer )( 
            IServerVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *pBuffer,
            /* [in] */ DWORD dwSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSharedBuffer )( 
            IServerVirtualDeviceSet __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SignalAbort )( 
            IServerVirtualDeviceSet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IServerVirtualDeviceSet __RPC_FAR * This);
        
        END_INTERFACE
    } IServerVirtualDeviceSetVtbl;

    interface IServerVirtualDeviceSet
    {
        CONST_VTBL struct IServerVirtualDeviceSetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServerVirtualDeviceSet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IServerVirtualDeviceSet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IServerVirtualDeviceSet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IServerVirtualDeviceSet_Open(This,lpName)	\
    (This)->lpVtbl -> Open(This,lpName)

#define IServerVirtualDeviceSet_GetConfiguration(This,pCfg)	\
    (This)->lpVtbl -> GetConfiguration(This,pCfg)

#define IServerVirtualDeviceSet_SetConfiguration(This,pCfg)	\
    (This)->lpVtbl -> SetConfiguration(This,pCfg)

#define IServerVirtualDeviceSet_ExecuteCompletionAgent(This)	\
    (This)->lpVtbl -> ExecuteCompletionAgent(This)

#define IServerVirtualDeviceSet_OpenDevice(This,lpName,ppVirtualDevice)	\
    (This)->lpVtbl -> OpenDevice(This,lpName,ppVirtualDevice)

#define IServerVirtualDeviceSet_AllocateBuffer(This,ppBuffer,dwSize,dwAlignment)	\
    (This)->lpVtbl -> AllocateBuffer(This,ppBuffer,dwSize,dwAlignment)

#define IServerVirtualDeviceSet_FreeBuffer(This,pBuffer,dwSize)	\
    (This)->lpVtbl -> FreeBuffer(This,pBuffer,dwSize)

#define IServerVirtualDeviceSet_IsSharedBuffer(This,pBuffer)	\
    (This)->lpVtbl -> IsSharedBuffer(This,pBuffer)

#define IServerVirtualDeviceSet_SignalAbort(This)	\
    (This)->lpVtbl -> SignalAbort(This)

#define IServerVirtualDeviceSet_Close(This)	\
    (This)->lpVtbl -> Close(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_Open_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ LPCWSTR lpName);


void __RPC_STUB IServerVirtualDeviceSet_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_GetConfiguration_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This,
    /* [out] */ struct VDConfig __RPC_FAR *pCfg);


void __RPC_STUB IServerVirtualDeviceSet_GetConfiguration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_SetConfiguration_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ struct VDConfig __RPC_FAR *pCfg);


void __RPC_STUB IServerVirtualDeviceSet_SetConfiguration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_ExecuteCompletionAgent_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This);


void __RPC_STUB IServerVirtualDeviceSet_ExecuteCompletionAgent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_OpenDevice_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ LPCWSTR lpName,
    /* [out] */ IServerVirtualDevice __RPC_FAR *__RPC_FAR *ppVirtualDevice);


void __RPC_STUB IServerVirtualDeviceSet_OpenDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_AllocateBuffer_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer,
    /* [in] */ DWORD dwSize,
    /* [in] */ DWORD dwAlignment);


void __RPC_STUB IServerVirtualDeviceSet_AllocateBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_FreeBuffer_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *pBuffer,
    /* [in] */ DWORD dwSize);


void __RPC_STUB IServerVirtualDeviceSet_FreeBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_IsSharedBuffer_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *pBuffer);


void __RPC_STUB IServerVirtualDeviceSet_IsSharedBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_SignalAbort_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This);


void __RPC_STUB IServerVirtualDeviceSet_SignalAbort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IServerVirtualDeviceSet_Close_Proxy( 
    IServerVirtualDeviceSet __RPC_FAR * This);


void __RPC_STUB IServerVirtualDeviceSet_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IServerVirtualDeviceSet_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_vdi_0009
 * at Fri Jun 12 10:46:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 



#pragma pack(pop, _vdi_h_)


extern RPC_IF_HANDLE __MIDL_itf_vdi_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vdi_0009_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
