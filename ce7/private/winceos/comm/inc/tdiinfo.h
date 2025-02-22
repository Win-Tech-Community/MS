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
/*++


Module Name:

    tdiinfo.h

Abstract:

  	This file contains definitions for the extended TDI query and set info.
  	calls.

Revision History:

--*/

#ifndef TDI_INFO_INCLUDED
#define TDI_INFO_INCLUDED


#ifndef CTE_TYPEDEFS_DEFINED
#define CTE_TYPEDEFS_DEFINED

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

#endif // CTE_TYPEDEFS_DEFINED


//* Structure of an entity ID.
typedef struct TDIEntityID {
	ulong		tei_entity;
	ulong		tei_instance;
} TDIEntityID;

//* Structure of an object ID.
typedef struct TDIObjectID {
	TDIEntityID	toi_entity;
	ulong		toi_class;
	ulong		toi_type;
	ulong		toi_id;
} TDIObjectID;

#ifdef UNDER_CE
#define	MAX_TDI_ENTITIES			512
#else
#define	MAX_TDI_ENTITIES			4096
#endif	// UNDER_CE

#define	INFO_CLASS_GENERIC			0x100
#define	INFO_CLASS_PROTOCOL			0x200
#define	INFO_CLASS_IMPLEMENTATION	0x300

#define	INFO_TYPE_PROVIDER			0x100
#define	INFO_TYPE_ADDRESS_OBJECT	0x200
#define	INFO_TYPE_CONNECTION		0x300

#define	ENTITY_LIST_ID				0

#define	GENERIC_ENTITY				0

#define	CO_TL_ENTITY				0x400
#define	CL_TL_ENTITY				0x401

#define	ER_ENTITY					0x380

#define	CO_NL_ENTITY				0x300
#define	CL_NL_ENTITY				0x301

#define	AT_ENTITY					0x280

#define	IF_ENTITY					0x200

#define INVALID_ENTITY_INSTANCE     -1

#define	CONTEXT_SIZE				16


//* The following are IDs supported by all entities. They are of class
//	GENERIC and type PROVIDER.

#define	ENTITY_TYPE_ID				1			// The ID to get the entity
												// type. The return from this
												// type is an unsigned integer
												// (see below).


// Valid values to get back from entity type ID query.
#define	CO_TL_NBF					0x400		// Entity implements NBF prot.
#define	CO_TL_SPX					0x402		// Entity implements SPX prot.
#define	CO_TL_TCP					0x404		// Entity implements TCP prot.
#define	CO_TL_SPP					0x406		// Entity implements SPP prot.

#define	CL_TL_NBF					0x401		// CL NBF protocol.
#define	CL_TL_UDP					0x403		// Entity implements UDP.

#define	ER_ICMP						0x380		// The ICMP protocol.

#define	CL_NL_IPX					0x301		// Entity implements IPX.
#define	CL_NL_IP					0x303		// Entity implements IP.

#define	AT_ARP						0x280		// Entity implements ARP.
#define	AT_NULL						0x282		// Entity does no address
												// translation.

#define	IF_GENERIC					0x200		// Generic interface.
#define	IF_MIB						0x202		// Supports MIB-2 interface.


/*NOINC*/
//
// NT DeviceIoControl definitions for TdiExtendedInformationEx functions.
//

//
// QueryInformationEx IOCTL. The return buffer is passed as the OutputBuffer
// in the DeviceIoControl request. This structure is passed as the
// InputBuffer.
//
typedef struct tcp_request_query_information_ex {
    TDIObjectID     ID;             // object ID to query.
    ULONG_PTR       Context[CONTEXT_SIZE/sizeof(ULONG_PTR)];  // multi-request
                                    // context. Zeroed for the first request.
} TCP_REQUEST_QUERY_INFORMATION_EX, *PTCP_REQUEST_QUERY_INFORMATION_EX;

#if defined(_WIN64)
typedef struct tcp_request_query_information_ex32 {
    TDIObjectID     ID;
    ULONG32         Context[CONTEXT_SIZE/sizeof(ULONG32)];
} TCP_REQUEST_QUERY_INFORMATION_EX32, *PTCP_REQUEST_QUERY_INFORMATION_EX32;
#endif // _WIN64

//
// SetInformationEx IOCTL request structure. This structure is passed as the
// InputBuffer. The space allocated for the structure must be large enough
// to contain the structure and the set data buffer, which begins at the
// Buffer field. The OutputBuffer parameter in the DeviceIoControl is not used.
//
typedef struct tcp_request_set_information_ex {
	TDIObjectID     ID;             // object ID to set.
	unsigned int    BufferSize;     // size of the set data buffer in bytes
	unsigned char   Buffer[1];      // beginning of the set data buffer
} TCP_REQUEST_SET_INFORMATION_EX, *PTCP_REQUEST_SET_INFORMATION_EX;


#endif // TDI_INFO_INCLUDED

