//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1996-1999
//
//  File:       softpub.h
//
//  Contents:   Microsoft Internet Security Authenticode Policy Provider
//
//  History:    05-Jun-1997 pberkman   created
//
//--------------------------------------------------------------------------

#ifndef SOFTPUB_H
#define SOFTPUB_H

#if _MSC_VER > 1000
#pragma once
#endif

#include "wintrust.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <pshpack8.h>

//////////////////////////////////////////////////////////////////////////////
//
// Softpub Policy Provider defines
//----------------------------------------------------------------------------
//  The following are definitions of the Microsoft Authenticode Policy Provider
//  (WINTRUST.DLL's Policy Provider)
//

#define SP_POLICY_PROVIDER_DLL_NAME         L"WINTRUST.DLL"

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_ACTION_GENERIC_VERIFY_V2 Guid  (Authenticode)
//----------------------------------------------------------------------------
//  Assigned to the pgActionID parameter of WinVerifyTrust to verify the
//  authenticity of a file/object using the Microsoft Authenticode
//  Policy Provider,
//
//          {00AAC56B-CD44-11d0-8CC2-00C04FC295EE}
//
#define WINTRUST_ACTION_GENERIC_VERIFY_V2                       \
            { 0xaac56b,                                         \
              0xcd44,                                           \
              0x11d0,                                           \
              { 0x8c, 0xc2, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee } \
            }

#define SP_INIT_FUNCTION                    L"SoftpubInitialize"
#define SP_OBJTRUST_FUNCTION                L"SoftpubLoadMessage"
#define SP_SIGTRUST_FUNCTION                L"SoftpubLoadSignature"
#define SP_CHKCERT_FUNCTION                 L"SoftpubCheckCert"
#define SP_FINALPOLICY_FUNCTION             L"SoftpubAuthenticode"
#define SP_CLEANUPPOLICY_FUNCTION           L"SoftpubCleanup"

//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_ACTION_TRUSTPROVIDER_TEST (Authenticode TEST)
//----------------------------------------------------------------------------
//  Assigned to the pgActionID parameter of WinVerifyTrust to dump
//  the CRYPT_PROVIDER_DATA structure to a file after calling the
//  Authenticode Policy Provider.
//
//          {573E31F8-DDBA-11d0-8CCB-00C04FC295EE}
//
#define WINTRUST_ACTION_TRUSTPROVIDER_TEST                      \
            { 0x573e31f8,                                       \
              0xddba,                                           \
              0x11d0,                                           \
              { 0x8c, 0xcb, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee } \
            }

#define SP_TESTDUMPPOLICY_FUNCTION_TEST     L"SoftpubDumpStructure"


//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_ACTION_GENERIC_CERT_VERIFY
//----------------------------------------------------------------------------
//  Assigned to the pgActionID parameter of WinVerifyTrust to verify
//  a certificate chain only.  This is only valid when passing in a
//  certificate context in the WinVerifyTrust input structures.
//
//          {189A3842-3041-11d1-85E1-00C04FC295EE}
//
#define WINTRUST_ACTION_GENERIC_CERT_VERIFY                     \
            { 0x189a3842,                                       \
              0x3041,                                           \
              0x11d1,                                           \
              { 0x85, 0xe1, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee } \
            }

#define SP_GENERIC_CERT_INIT_FUNCTION       L"SoftpubDefCertInit"


//////////////////////////////////////////////////////////////////////////////
//
// WINTRUST_ACTION_GENERIC_CHAIN_VERIFY
//----------------------------------------------------------------------------
//  Assigned to the pgActionID parameter of WinVerifyTrust to verify
//  certificate chains created from any object type: file, cert, signer, ...
//  A callback is provided to implement the final chain policy using
//  the chain context for each signer and counter signer.
//
//          {fc451c16-ac75-11d1-b4b8-00c04fb66ea0}
//
#define WINTRUST_ACTION_GENERIC_CHAIN_VERIFY                    \
            { 0xfc451c16,                                       \
              0xac75,                                           \
              0x11d1,                                           \
              { 0xb4, 0xb8, 0x00, 0xc0, 0x4f, 0xb6, 0x6e, 0xa0 }\
            }
#define GENERIC_CHAIN_FINALPOLICY_FUNCTION      L"GenericChainFinalProv"
#define GENERIC_CHAIN_CERTTRUST_FUNCTION        L"GenericChainCertificateTrust"


typedef struct _WTD_GENERIC_CHAIN_POLICY_SIGNER_INFO
    WTD_GENERIC_CHAIN_POLICY_SIGNER_INFO,
        *PWTD_GENERIC_CHAIN_POLICY_SIGNER_INFO;

struct _WTD_GENERIC_CHAIN_POLICY_SIGNER_INFO {
    union {
        DWORD                                   cbStruct;
        DWORD                                   cbSize;
    };
    PCCERT_CHAIN_CONTEXT                    pChainContext;

    // SGNR_TYPE_TIMESTAMP defined in wintrust.h
    DWORD                                   dwSignerType;
    PCMSG_SIGNER_INFO                       pMsgSignerInfo;
    DWORD                                   dwError;

    DWORD                                   cCounterSigner;
    PWTD_GENERIC_CHAIN_POLICY_SIGNER_INFO   *rgpCounterSigner;
};

typedef HRESULT (WINAPI *PFN_WTD_GENERIC_CHAIN_POLICY_CALLBACK)(
    IN PCRYPT_PROVIDER_DATA pProvData,
    IN DWORD dwStepError,
    IN DWORD dwRegPolicySettings,
    IN DWORD cSigner,
    IN PWTD_GENERIC_CHAIN_POLICY_SIGNER_INFO *rgpSigner,
    IN void *pvPolicyArg
    );

// The fields in the following data structure are passed to
// CertGetCertificateChain().
typedef struct _WTD_GENERIC_CHAIN_POLICY_CREATE_INFO {
    union {
        DWORD                                   cbStruct;
        DWORD                                   cbSize;
    };

    HCERTCHAINENGINE                        hChainEngine;
    PCERT_CHAIN_PARA                        pChainPara;
    DWORD                                   dwFlags;
    void                                    *pvReserved;
} WTD_GENERIC_CHAIN_POLICY_CREATE_INFO, *PWTD_GENERIC_CHAIN_POLICY_CREATE_INFO;

typedef struct _WTD_GENERIC_CHAIN_POLICY_DATA {
    union {
        DWORD                                   cbStruct;
        DWORD                                   cbSize;
    };

    PWTD_GENERIC_CHAIN_POLICY_CREATE_INFO   pSignerChainInfo;
    PWTD_GENERIC_CHAIN_POLICY_CREATE_INFO   pCounterSignerChainInfo;
    PFN_WTD_GENERIC_CHAIN_POLICY_CALLBACK   pfnPolicyCallback;
    void                                    *pvPolicyArg;
} WTD_GENERIC_CHAIN_POLICY_DATA, *PWTD_GENERIC_CHAIN_POLICY_DATA;


//////////////////////////////////////////////////////////////////////////////
//
// HTTPSPROV_ACTION Guid  (Authenticode add-on)
//----------------------------------------------------------------------------
//  Assigned to the pgActionID parameter of WinVerifyTrust to verify the
//  SSL/PCT connections through IE.
//
//          {573E31F8-AABA-11d0-8CCB-00C04FC295EE}
//
#define HTTPSPROV_ACTION                                        \
            { 0x573e31f8,                                       \
              0xaaba,                                           \
              0x11d0,                                           \
              { 0x8c, 0xcb, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee } \
            }

#define HTTPS_FINALPOLICY_FUNCTION          L"HTTPSFinalProv"
#define HTTPS_CHKCERT_FUNCTION              L"HTTPSCheckCertProv"
#define HTTPS_CERTTRUST_FUNCTION            L"HTTPSCertificateTrust"


//////////////////////////////////////////////////////////////////////////////
//
// OFFICESIGN_ACTION_VERIFY Guid  (Authenticode add-on)
//----------------------------------------------------------------------------
//  Assigned to the pgActionID parameter of WinVerifyTrust to verify the
//  authenticity of a Structured Storage file using the Microsoft Office
//  Authenticode add-on Policy Provider,
//
//          {5555C2CD-17FB-11d1-85C4-00C04FC295EE}
//
#define     OFFICESIGN_ACTION_VERIFY                                    \
                { 0x5555c2cd,                                           \
                  0x17fb,                                               \
                  0x11d1,                                               \
                  { 0x85, 0xc4, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee }     \
                }

#define     OFFICE_POLICY_PROVIDER_DLL_NAME             SP_POLICY_PROVIDER_DLL_NAME
#define     OFFICE_INITPROV_FUNCTION                    L"OfficeInitializePolicy"
#define     OFFICE_CLEANUPPOLICY_FUNCTION               L"OfficeCleanupPolicy"


//////////////////////////////////////////////////////////////////////////////
//
// DRIVER_ACTION_VERIFY Guid  (Authenticode add-on)
//----------------------------------------------------------------------------
//  Assigned to the pgActionID parameter of WinVerifyTrust to verify the
//  authenticity of a WHQL signed driver.  This is an Authenticode add-on
//  Policy Provider,
//
//          {F750E6C3-38EE-11d1-85E5-00C04FC295EE}
//
#define     DRIVER_ACTION_VERIFY                                        \
                { 0xf750e6c3,                                           \
                  0x38ee,                                               \
                  0x11d1,                                               \
                  { 0x85, 0xe5, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee }     \
                }

#define     DRIVER_INITPROV_FUNCTION                    L"DriverInitializePolicy"
#define     DRIVER_FINALPOLPROV_FUNCTION                L"DriverFinalPolicy"
#define     DRIVER_CLEANUPPOLICY_FUNCTION               L"DriverCleanupPolicy"

typedef struct DRIVER_VER_MAJORMINOR_
{
    DWORD           dwMajor;
    DWORD           dwMinor;

} DRIVER_VER_MAJORMINOR;

typedef struct DRIVER_VER_INFO_
{
    DWORD                               cbStruct;               // IN - set to sizeof(DRIVER_VER_INFO)

    DWORD                               dwReserved1;            // IN - set to NULL
    DWORD                               dwReserved2;            // IN - set to NULL

    DWORD                               dwPlatform;             // IN - OPTIONAL: platform to use
    DWORD				dwVersion;		// IN - OPTIONAL: major version to use, same as sOSVersionLow

    WCHAR                               wszVersion[MAX_PATH];   // OUT: version string from catalog file
    WCHAR                               wszSignedBy[MAX_PATH];  // OUT: signer display name from certificate
    PCCERT_CONTEXT                      pcSignerCertContext;    // OUT: client MUST free this!!!

    // 08-Dec-1997 pberkman: added
    DRIVER_VER_MAJORMINOR               sOSVersionLow;          // IN - OPTIONAL: lowest compatible version
    DRIVER_VER_MAJORMINOR		sOSVersionHigh; 	// IN - OPTIONAL: for now must be the same as sOSVersionLow

} DRIVER_VER_INFO, *PDRIVER_VER_INFO;

#include <poppack.h>


#ifdef __cplusplus
}
#endif

#endif // SOFTPUB_H
