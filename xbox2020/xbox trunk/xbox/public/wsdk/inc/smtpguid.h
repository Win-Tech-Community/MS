//+------------------------------------------------------------
//
// Copyright (C) 1998 - 1999, Microsoft Corporation
//
// File: smtpguid.h
//
// Contents: Event related GUIDS published from SMTPSVC
//
// Instructions: Include this file to declare the various
//               GUIDS/strings as external global variables.
//               To actually define these global variables, 
//               #define SMTPINITGUID and #include <initguid.h> before this
//               header file. 
//
// History:
// Jeffrey C Stamerjohn 1998/07/14 15:22:29: Created.
//
//-------------------------------------------------------------
#ifndef __SMTPGUID_H__
#define __SMTPGUID_H__

#ifdef SMTPINITGUID
#define DECLARE_EVENTGUID_STRING( Name, Value ) \
    CONST WCHAR Name##[] = L##Value

#else //SMTPINITGUID
#define DECLARE_EVENTGUID_STRING( Name, Value ) \
    extern CONST WCHAR Name##[]

#endif //SMTPINITGUID

// SMTP SourceType GUID
// {fb65c4dc-e468-11d1-aa67-00c04fa345f6}
DECLARE_EVENTGUID_STRING( g_szGuidSmtpSourceType, "{fb65c4dc-e468-11d1-aa67-00c04fa345f6}");
DEFINE_GUID(GUID_SMTP_SOURCE_TYPE, 0xfb65c4dc, 0xe468, 0x11d1, 0xaa, 0x67, 0x0, 0xc0, 0x4f, 0xa3, 0x45, 0xf6);

/* 
** SMTP Source GUID
*/
// {1b3c0666-e470-11d1-aa67-00c04fa345f6}
DECLARE_EVENTGUID_STRING( g_szGuidSmtpSvcSource, "{1b3c0666-e470-11d1-aa67-00c04fa345f6}");
DEFINE_GUID(GUID_SMTPSVC_SOURCE, 0x1b3c0666, 0xe470, 0x11d1, 0xaa, 0x67, 0x0, 0xc0, 0x4f, 0xa3, 0x45, 0xf6);

/*
**  Protocol Events
*/
// SMTP OnInboundCommand
// {F6628C8D-0D5E-11d2-AA68-00C04FA35B82}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnInboundCommand, "{F6628C8D-0D5E-11d2-AA68-00C04FA35B82}");
DEFINE_GUID(CATID_SMTP_ON_INBOUND_COMMAND, 0xf6628c8d, 0xd5e, 0x11d2, 0xaa, 0x68, 0x0, 0xc0, 0x4f, 0xa3, 0x5b, 0x82);

// SMTP OnServerResponse
// {F6628C8E-0D5E-11d2-AA68-00C04FA35B82}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnServerResponse, "{F6628C8E-0D5E-11d2-AA68-00C04FA35B82}");
DEFINE_GUID(CATID_SMTP_ON_SERVER_RESPONSE, 0xf6628c8e, 0xd5e, 0x11d2, 0xaa, 0x68, 0x0, 0xc0, 0x4f, 0xa3, 0x5b, 0x82);

// SMTP OnSessionStart
// {F6628C8F-0D5E-11d2-AA68-00C04FA35B82}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnSessionStart, "{F6628C8F-0D5E-11d2-AA68-00C04FA35B82}");
DEFINE_GUID(CATID_SMTP_ON_SESSION_START, 0xf6628c8f, 0xd5e, 0x11d2, 0xaa, 0x68, 0x0, 0xc0, 0x4f, 0xa3, 0x5b, 0x82);

// SMTP OnMessageStart
// {F6628C90-0D5E-11d2-AA68-00C04FA35B82}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnMessageStart, "{F6628C90-0D5E-11d2-AA68-00C04FA35B82}");
DEFINE_GUID(CATID_SMTP_ON_MESSAGE_START, 0xf6628c90, 0xd5e, 0x11d2, 0xaa, 0x68, 0x0, 0xc0, 0x4f, 0xa3, 0x5b, 0x82);

// SMTP OnPerRecipient
// {F6628C91-0D5E-11d2-AA68-00C04FA35B82}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnPerRecipient, "{F6628C91-0D5E-11d2-AA68-00C04FA35B82}");
DEFINE_GUID(CATID_SMTP_ON_PER_RECIPIENT, 0xf6628c91, 0xd5e, 0x11d2, 0xaa, 0x68, 0x0, 0xc0, 0x4f, 0xa3, 0x5b, 0x82);

// Smtp OnBeforeData
// {F6628C92-0D5E-11d2-AA68-00C04FA35B82}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnBeforeData, "{F6628C92-0D5E-11d2-AA68-00C04FA35B82}");
DEFINE_GUID(CATID_SMTP_ON_BEFORE_DATA, 0xf6628c92, 0xd5e, 0x11d2, 0xaa, 0x68, 0x0, 0xc0, 0x4f, 0xa3, 0x5b, 0x82);

// SMTP OnSessionEnd
// {F6628C93-0D5E-11d2-AA68-00C04FA35B82} 
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnSessionEnd, "{F6628C93-0D5E-11d2-AA68-00C04FA35B82}");
DEFINE_GUID(CATID_SMTP_ON_SESSION_END, 0xf6628c93, 0xd5e, 0x11d2, 0xaa, 0x68, 0x0, 0xc0, 0x4f, 0xa3, 0x5b, 0x82);


/*
** Transport Events
*/

// SMTP Store Events
// {59175850-e533-11d1-aa67-00c04fa345f6}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpStoreDriver, "{59175850-e533-11d1-aa67-00c04fa345f6}");
DEFINE_GUID(CATID_SMTP_STORE_DRIVER, 0x59175850, 0xe533, 0x11d1, 0xaa, 0x67, 0x0, 0xc0, 0x4f, 0xa3, 0x45, 0xf6);

// SMTP OnTransportSubmission
// {FF3CAA23-00B9-11d2-9DFB-00C04FA322BA}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnTransportSubmission, "{FF3CAA23-00B9-11d2-9DFB-00C04FA322BA}");
DEFINE_GUID(CATID_SMTP_TRANSPORT_SUBMISSION, 0xff3caa23, 0xb9, 0x11d2, 0x9d, 0xfb, 0x0, 0xc0, 0x4f, 0xa3, 0x22, 0xba);


// SMTP onPrecategorize
// {A3ACFB0D-83FF-11d2-9E14-00C04FA322BA}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnPrecategorize, "{A3ACFB0D-83FF-11d2-9E14-00C04FA322BA}");
DEFINE_GUID(CATID_SMTP_TRANSPORT_PRECATEGORIZE, 0xa3acfb0d, 0x83ff, 0x11d2, 0x9e, 0x14, 0x0, 0xc0, 0x4f, 0xa3, 0x22, 0xba);

// SMTP Categorizer events
// {960252A3-0A3A-11d2-9E00-00C04FA322BA}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnCategorize, "{960252A3-0A3A-11d2-9E00-00C04FA322BA}");
DEFINE_GUID(CATID_SMTP_TRANSPORT_CATEGORIZE, 0x960252a3, 0xa3a, 0x11d2, 0x9e, 0x0, 0x0, 0xc0, 0x4f, 0xa3, 0x22, 0xba);

// SMTP onPostcategorize
// {76719654-05A6-11d2-9DFD-00C04FA322BA}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnPostcategorize, "{76719654-05A6-11d2-9E00-00C04FA322BA}");
DEFINE_GUID(CATID_SMTP_TRANSPORT_POSTCATEGORIZE, 
0x76719654, 0x5a6, 0x11d2, 0x9d, 0xfd, 0x0, 0xc0, 0x4f, 0xa3, 0x22, 0xba);


// SMTP OnTransportRouter
// {283430C9-1850-11d2-9E03-00C04FA322BA}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpOnTransportRouter, "{283430C9-1850-11d2-9E03-00C04FA322BA}");
DEFINE_GUID(CATID_SMTP_TRANSPORT_ROUTER, 0x283430c9, 0x1850, 0x11d2, 0x9e, 0x3, 0x0, 0xc0, 0x4f, 0xa3, 0x22, 0xba);

// SMTP MsgTrackLog
// {c6df52aa-7db0-11d2-94f4-00c04f79f1d6}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpMsgTrackLog, "{c6df52aa-7db0-11d2-94f4-00c04f79f1d6}");
DEFINE_GUID(CATID_SMTP_MSGTRACKLOG, 0xc6df52aa, 0x7db0, 0x11d2, 0x94, 0xf4, 0x0, 0xc0, 0x4f, 0x79, 0xf1, 0xd6);

// SMTP DnsResolver
// {bd0b4366-8e03-11d2-94f6-00c04f79f1d6}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpDnsResolver, "{bd0b4366-8e03-11d2-94f6-00c04f79f1d6}");
DEFINE_GUID(CATID_SMTP_DNSRESOLVERRECORDSINK, 0xbd0b4366, 0x8e03, 0x11d2, 0x94, 0xf6, 0x0, 0xc0, 0x4f, 0x79, 0xf1, 0xd6);

// SMTP MaxMsgSize
// {ebf159de-a67e-11d2-94f7-00c04f79f1d6}
DECLARE_EVENTGUID_STRING( g_szcatidSmtpMaxMsgSize, "{ebf159de-a67e-11d2-94f7-00c04f79f1d6}");
DEFINE_GUID(CATID_SMTP_MAXMSGSIZE, 0xebf159de, 0xa67e, 0x11d2, 0x94, 0xf7, 0x0, 0xc0, 0x4f, 0x79, 0xf1, 0xd6);

//
// CLSID of the CoCreateable categorizer
//
// {B23C35B7-9219-11d2-9E17-00C04FA322BA}"
DEFINE_GUID(CLSID_SmtpCat,
            0xb23c35b7, 0x9219, 0x11d2, 0x9e, 0x17, 0x0, 0xc0, 0x4f, 0xa3, 0x22, 0xba);

#define SZ_PROGID_SMTPCAT   "Smtp.Cat"


#endif //__SMTPGUID_H__
