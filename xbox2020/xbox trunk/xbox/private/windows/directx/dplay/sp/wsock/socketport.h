/*==========================================================================
 *
 *  Copyright (C) 1998-2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:		CSocketPort.h
 *  Content:	Winsock socket port that manages data flow on a given adapter,
 *				address and port.
 *
 *  History:
 *   Date		By		Reason
 *   ====		==		======
 *	01/20/99	jtk		Created
 *	05/11/99	jtk		Split out to make a base class
 *  03/22/2000	jtk		Updated with changes to interface names
 ***************************************************************************/

#ifndef __SOCKET_PORT_H__
#define __SOCKET_PORT_H__

//**********************************************************************
// Constant definitions
//**********************************************************************

//
// states of socket port
//
typedef	enum
{
	SOCKET_PORT_STATE_UNKNOWN = 0,
	SOCKET_PORT_STATE_INITIALIZED,
	SOCKET_PORT_STATE_UNBOUND,
} SOCKET_PORT_STATE;

//
// enumeration of socket types
//
typedef	enum	_GATEWAY_BIND_TYPE
{
	GATEWAY_BIND_TYPE_UNKNOWN = 0,		// uninitialized
	GATEWAY_BIND_TYPE_SPECIFIC,			// map the local port to the same port on the Rsip server (DPNSVR listen socket port)
	GATEWAY_BIND_TYPE_DEFAULT,			// map the local port to any random port on the Rsip server
	GATEWAY_BIND_TYPE_NONE				// don't map the local port on the Rsip server
} GATEWAY_BIND_TYPE;

//
// value used to designate an invalid enum key
//
#define	INVALID_ENUM_KEY	0

//
// enumerated type to indicate how a send completed
//
typedef enum
{
	SEND_UNKNOWN,					// unknown state
	SEND_FAILED,					// send failed
	SEND_IN_PROGRESS,				// send is pending in Winsock
	SEND_WINSOCK_BUSY,				// send couldn't be queued (we'll need to buffer ourselves)
	SEND_COMPLETED_IMMEDIATELY_WS1	// send completed immediately (Winsock1 only)

} SEND_COMPLETION_CODE;

//**********************************************************************
// Macro definitions
//**********************************************************************

//**********************************************************************
// Structure definitions
//**********************************************************************

//
// forward references
//
class	CSocketPort;

//**********************************************************************
// Variable definitions
//**********************************************************************

//**********************************************************************
// Function prototypes
//**********************************************************************

//
// send function pointer
//
typedef	SEND_COMPLETION_CODE	(CSocketPort::*PSEND_FUNCTION)( CWriteIOData *const pWriteData );
typedef	BOOL	(CSocketPort::*PSOCKET_SERVICE_FUNCTION)( void );

//**********************************************************************
// Class definition
//**********************************************************************

//
// reference to other classes and structures
//
class	CAdapterEntry;
class	CEndpoint;
class	CEndpointEnumKey;
class	CSPData;
typedef	struct	_THREAD_POOL_JOB	THREAD_POOL_JOB;

//
// main class definition
//
class	CSocketPort
{
	STDNEWDELETE

	public:
		CSocketPort();
		~CSocketPort();

		HRESULT	Initialize( CSPData *const pSPData, CSocketAddress *const pAddress );
		HRESULT	Deinitialize( void );
		HRESULT	BindToNetwork( const GATEWAY_BIND_TYPE GatewayBindType );
		HRESULT	UnbindFromNetwork( void );

		const CSocketAddress *const	GetNetworkAddress( void ) const { return m_pNetworkSocketAddress; }
		const SOCKET	GetSocket( void ) const { return m_Socket; }

		void	AddRef( void ) { DNInterlockedIncrement( &m_iRefCount ); }

		#undef DPF_MODNAME
		#define DPF_MODNAME "CSocketPort::DecRef"
		void	DecRef( void )
		{
			DNASSERT( m_State != SOCKET_PORT_STATE_UNKNOWN );

			//
			// Decrement the reference counts and return this item to the pool if nobody
			// is referencing it anymore.
			//
			if ( DNInterlockedDecrement( &m_iRefCount ) == 0 )
			{
				HRESULT	hr;


				DNASSERT( m_iEndpointRefCount == 0 );

				//
				// There's no need to lock this socket port because this is the last
				// reference to it, nobody else will access it.
				//
				hr = Deinitialize();
				if ( hr != DPN_OK )
				{
					DPF( 0, "Problem deinitializing socket port in DecRef!" );
					DisplayDNError( 0, hr );
				}

				ReturnSelfToPool();
			}
		}
		
		void	EndpointAddRef( void );
		DWORD	EndpointDecRef( void );
		
		void	Lock( void ) { DNEnterCriticalSection( &m_Lock ); }
		void	Unlock( void ) { DNLeaveCriticalSection( &m_Lock ); }

		HRESULT	BindEndpoint( CEndpoint *const pEndpoint );
		void	UnbindEndpoint( CEndpoint *const pEndpoint );
		
		#undef DPF_MODNAME
		#define DPF_MODNAME "CSocketPort::GetEnumKey"
		const DWORD	GetEnumKey( void )
		{
			DWORD	dwReturn;


			DBG_CASSERT( ENUM_RTT_MASK == 0x0F );
			Lock();
			m_iEnumKey++;
			dwReturn = m_iEnumKey << 4;
			Unlock();

			return	dwReturn;
		}

		void	DisconnectAllEndpoints( void );
		void	ReturnSelfToPool( void );

		#undef DPF_MODNAME
		#define DPF_MODNAME "CSocketPort::SendUserData"
		void	SendUserData( CWriteIOData *const pWriteData )
		{
			//
			// check for need to escape user data
			//
			switch ( pWriteData->m_pBuffers[ 0 ].pBufferData[ 0 ] )
			{
				case SP_HEADER_LEAD_BYTE:
				{
					//
					// possible token interpretation problem, escape user data by prepending a buffer
					//
					pWriteData->m_pBuffers = &pWriteData->m_pBuffers[ -1 ];
					pWriteData->m_uBufferCount++;
					DBG_CASSERT( sizeof( &pWriteData->m_PrependBuffer.EscapedUserDataHeader ) == sizeof( BYTE* ) ) ;
					pWriteData->m_pBuffers[ 0 ].pBufferData = reinterpret_cast<BYTE*>( &pWriteData->m_PrependBuffer.EscapedUserDataHeader );
					pWriteData->m_pBuffers[ 0 ].dwBufferSize = sizeof( pWriteData->m_PrependBuffer.EscapedUserDataHeader );
					
					DNASSERT( pWriteData->m_PrependBuffer.EscapedUserDataHeader.bSPLeadByte == SP_HEADER_LEAD_BYTE );
					pWriteData->m_PrependBuffer.EscapedUserDataHeader.bSPCommandByte = ESCAPED_USER_DATA_KIND;
					pWriteData->m_PrependBuffer.EscapedUserDataHeader.wPad = ESCAPED_USER_DATA_PAD_VALUE;

					break;
				}

				default:
				{
					//
					// Assume user data.  There's no need to prepend a buffer because the
					// receiving machine will reailze that it's not a 'special' message and
					// will default the contents to 'user data'.
					//
					break;
				}
			}

			SendData( pWriteData );
		}

		#undef DPF_MODNAME
		#define DPF_MODNAME "CSocketPort::SendEnumResponseData"
		void	SendEnumResponseData( CWriteIOData *const pWriteData, const UINT_PTR uEnumResponseKey )
		{
			//
			// inlined to keep servers fast
			//
			pWriteData->m_pBuffers = &pWriteData->m_pBuffers[ -1 ];
			pWriteData->m_uBufferCount++;
			DBG_CASSERT( sizeof( &pWriteData->m_PrependBuffer.EnumResponseDataHeader ) == sizeof( BYTE* ) );
			pWriteData->m_pBuffers[ 0 ].pBufferData = reinterpret_cast<BYTE*>( &pWriteData->m_PrependBuffer.EnumResponseDataHeader );
			pWriteData->m_pBuffers[ 0 ].dwBufferSize = sizeof( pWriteData->m_PrependBuffer.EnumResponseDataHeader );
			
			DNASSERT( pWriteData->m_PrependBuffer.EnumResponseDataHeader.bSPLeadByte == SP_HEADER_LEAD_BYTE );
			pWriteData->m_PrependBuffer.EnumResponseDataHeader.bSPCommandByte = ENUM_RESPONSE_DATA_KIND;

			DNASSERT( uEnumResponseKey <= WORD_MAX );
			pWriteData->m_PrependBuffer.EnumResponseDataHeader.wEnumResponsePayload = static_cast<WORD>( uEnumResponseKey );

			SendData( pWriteData );
		}

		void	SendEnumQueryData( CWriteIOData *const pWriteData, const UINT_PTR uEnumKey );
		void	SendProxiedEnumData( CWriteIOData *const pWriteData, const CSocketAddress *const pReturnAddress, const UINT_PTR uOldEnumKey );

		CSocketAddress	*GetBoundNetworkAddress( const SP_ADDRESS_TYPE AddressType ) const;
		IDirectPlay8Address	*GetDP8BoundNetworkAddress( const SP_ADDRESS_TYPE AddressType ) const;
		void	MungeAddressWithPAST( CSocketAddress *const pSocketAddress ) const;


		HRESULT	AddToMulticastGroup( const void *const pGroupData, const UINT_PTR uGroupDataSize );
		HRESULT	RemoveFromMulticastGroup( const void *const pGroupData, const UINT_PTR uGroupDataSize );

		//
		// set the Rsip module for this socket port
		//
		CAdapterEntry	*GetAdapterEntry( void ) const { return m_pAdapterEntry; }

		#undef DPF_MODNAME
		#define DPF_MODNAME "CSocketPort::SetAdapterEntry"
		void	SetAdapterEntry( CAdapterEntry *const pAdapterEntry )
		{
			DNASSERT( ( m_pAdapterEntry == NULL ) || ( pAdapterEntry == NULL ) );
			m_pAdapterEntry = pAdapterEntry;
		}

		void	Winsock2ReceiveComplete( CReadIOData *const pReadData );
		void	CancelReceive( CReadIOData *const pRead );

		//
		// Public service functions for Winsock1 since we can't get asynchronous
		// notification.
		//
		BOOL	SendFromWriteQueue( void );
		void	SendComplete( CWriteIOData *const pWriteData, const HRESULT hResult );

		//
		// functions for active list
		//
		#undef DPF_MODNAME
		#define DPF_MODNAME "CSocketPort::AddToActiveList"
		void	AddToActiveList( CBilink *const pBilink )
		{
			DNASSERT( pBilink != NULL );
			m_ActiveListLinkage.InsertBefore( pBilink );
		}

		void	RemoveFromActiveList( void ) { m_ActiveListLinkage.RemoveFromList(); }

		#undef DPF_MODNAME
		#define DPF_MODNAME "CSocketPort::SocketPortFromBilink"
		static CSocketPort	*SocketPortFromBilink( CBilink *const pBilink )
		{
			DNASSERT( pBilink != NULL );
			DBG_CASSERT( sizeof( BYTE* ) == sizeof( pBilink ) );
			DBG_CASSERT( sizeof( CSocketPort* ) == sizeof( BYTE* ) );
			return	reinterpret_cast<CSocketPort*>( &reinterpret_cast<BYTE*>( pBilink )[ -OFFSETOF( CSocketPort, m_ActiveListLinkage ) ] );
		}

		void	SetWinsockBufferSize( const INT iBufferSize ) const;

	protected:

	private:
		CSPData						*m_pSPData;					// pointer to SPData
		CThreadPool					*m_pThreadPool;				// pointer to thread pool
		DNCRITICAL_SECTION			m_Lock;						// thread lock
		volatile LONG				m_iRefCount;				// count of all outstanding references (endpoint and I/O)
		volatile LONG				m_iEndpointRefCount;		// count of outstanding endpoint references
		volatile SOCKET_PORT_STATE	m_State;					// state of socket port
		
		volatile SOCKET				m_Socket;					// communications socket
		CSocketAddress				*m_pNetworkSocketAddress;	// network address this socket is bound to
		CSocketAddress				*m_pPASTSocketAddress;		// external network address visible via PAST server
																// this may be the same as the m_NetworkSocketAddress
		
		CAdapterEntry	*m_pAdapterEntry;		// pointer to adapter entry to use
		DWORD			m_dwPASTBindID;			// RSIP bind ID associated with this socket
		CBilink			m_ActiveListLinkage;	// linkage to list of active socket ports

		DNCRITICAL_SECTION								m_EndpointDataLock;			// lock for endpoint data
		CClassHash< HANDLE, const CSocketAddress* >		m_ConnectEndpointList;		// list of connect endpoints
		CClassHash< HANDLE, const CEndpointEnumKey* >	m_EnumEndpointList;			// list of enum endpoints
		HANDLE											m_hListenEndpoint;			// associated listen endpoint (there can only be one!)

		volatile LONG	m_iEnumKey;						// current 'key' to be assigned to an enum
		CSendQueue		m_SendQueue;					// outgoing send queue
		THREAD_POOL_JOB	*m_pRemoveSocketPortData;		// pointer to preallocated job for removing socket port
		PSEND_FUNCTION	m_pSendFunction;				// pointer to appropriate send function

		DEBUG_ONLY(	BOOL	m_fInitialized );


		void	LockEndpointData( void ) { DNEnterCriticalSection( &m_EndpointDataLock ); }
		void	UnlockEndpointData( void ) { DNLeaveCriticalSection( &m_EndpointDataLock ); }

		HRESULT	BindToNextAvailablePort( const CSocketAddress *const pNetworkSocketAddress ) const;
		
		HRESULT	BindToPASTServer( const CSocketAddress *const pBoundSocketAddress,
								  CSocketAddress *const pPASTSocketAddress,
								  const GATEWAY_BIND_TYPE GatewayBindType );
		
		HRESULT	StartReceiving( void );

		SEND_COMPLETION_CODE	Winsock2Send( CWriteIOData *const pWriteData );
		HRESULT					Winsock2Receive( void );

		void	SendData( CWriteIOData *const pWriteData );
		void	ProcessReceivedData( CReadIOData *const pReadData );

		//
		// make copy constructor and assignment operator private and unimplemented
		// to prevent illegal copies from being made
		//
		CSocketPort( const CSocketPort & );
		CSocketPort& operator=( const CSocketPort & );
};

#undef DPF_MODNAME

#endif	// __SOCKET_PORT_H__

