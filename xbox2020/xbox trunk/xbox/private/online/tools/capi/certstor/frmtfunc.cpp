//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1995 - 1997
//
//  File:       frmtfunc.cpp
//
//  Contents:   OID format functions
//
//  Functions:  CryptFrmtFuncDllMain
//              CryptFormatObject
//              CryptQueryObject
//
//  History:    15-05-97    xiaohs   created
//--------------------------------------------------------------------------

#include "global.hxx"
#include <dbgdef.h>
#include "frmtfunc.h"

HMODULE hFrmtFuncInst;

static HCRYPTOIDFUNCSET hFormatFuncSet;



//function type define
typedef BOOL (WINAPI *PFN_FORMAT_FUNC)(
	IN DWORD dwCertEncodingType,
    IN DWORD dwFormatType,
	IN DWORD dwFormatStrType,
	IN void	 *pFormatStruct,
    IN LPCSTR lpszStructType,
    IN const BYTE *pbEncoded,
    IN DWORD cbEncoded,
	OUT void *pbFormat,
    IN OUT DWORD *pcbFormat
    );

static BOOL
WINAPI
FormatBytesToHex(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);


static BOOL	
WINAPI	
CryptDllFormatAttr(
				DWORD		dwEncodingType,	
				DWORD		dwFormatType,
				DWORD		dwFormatStrType,
				void		*pStruct,
				LPCSTR		lpszStructType,
				const BYTE	*pbEncoded,
				DWORD		cbEncoded,
				void		*pBuffer,
				DWORD		*pcBuffer);


static BOOL	
WINAPI	
CryptDllFormatName(
				DWORD		dwEncodingType,	
				DWORD		dwFormatType,
				DWORD		dwFormatStrType,
				void		*pStruct,
				LPCSTR		lpszStructType,
				const BYTE	*pbEncoded,
				DWORD		cbEncoded,
				void		*pbBuffer,
				DWORD		*pcbBuffer);

static BOOL
WINAPI
FormatBasicConstraints2(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatBasicConstraints(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);


static BOOL
WINAPI
FormatCRLReasonCode(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatEnhancedKeyUsage(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);


static BOOL
WINAPI
FormatAltName(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatAuthorityKeyID(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatAuthorityKeyID2(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatNextUpdateLocation(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatSubjectKeyID(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatFinancialCriteria(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);


static BOOL
WINAPI
FormatSMIMECapabilities(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatKeyUsage(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);


static BOOL
WINAPI
FormatAuthortiyInfoAccess(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatKeyAttributes(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);


static BOOL
WINAPI
FormatKeyRestriction(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatCRLDistPoints(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatCertPolicies(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);

static BOOL
WINAPI
FormatSPAgencyInfo(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat);


static const CRYPT_OID_FUNC_ENTRY DefaultFormatTable[] = {
    CRYPT_DEFAULT_OID, FormatBytesToHex};

static const CRYPT_OID_FUNC_ENTRY OIDFormatTable[] = {
				szOID_COMMON_NAME,						CryptDllFormatAttr,	
				szOID_SUR_NAME,                      	CryptDllFormatAttr,
				szOID_DEVICE_SERIAL_NUMBER,          	CryptDllFormatAttr,
				szOID_COUNTRY_NAME,                  	CryptDllFormatAttr,
				szOID_LOCALITY_NAME,                 	CryptDllFormatAttr,
				szOID_STATE_OR_PROVINCE_NAME,        	CryptDllFormatAttr,
				szOID_STREET_ADDRESS,                	CryptDllFormatAttr,
				szOID_ORGANIZATION_NAME,             	CryptDllFormatAttr,
				szOID_ORGANIZATIONAL_UNIT_NAME,      	CryptDllFormatAttr,
				szOID_TITLE,                         	CryptDllFormatAttr,
				szOID_DESCRIPTION,                   	CryptDllFormatAttr,
				szOID_SEARCH_GUIDE,                  	CryptDllFormatAttr,
				szOID_BUSINESS_CATEGORY,             	CryptDllFormatAttr,
				szOID_POSTAL_ADDRESS,                	CryptDllFormatAttr,
				szOID_POSTAL_CODE,                   	CryptDllFormatAttr,
				szOID_POST_OFFICE_BOX,               	CryptDllFormatAttr,
				szOID_PHYSICAL_DELIVERY_OFFICE_NAME, 	CryptDllFormatAttr,
				szOID_TELEPHONE_NUMBER,              	CryptDllFormatAttr,
				szOID_TELEX_NUMBER,                  	CryptDllFormatAttr,
				szOID_TELETEXT_TERMINAL_IDENTIFIER,  	CryptDllFormatAttr,
				szOID_FACSIMILE_TELEPHONE_NUMBER,    	CryptDllFormatAttr,
				szOID_X21_ADDRESS,                   	CryptDllFormatAttr,
				szOID_INTERNATIONAL_ISDN_NUMBER,     	CryptDllFormatAttr,
				szOID_REGISTERED_ADDRESS,            	CryptDllFormatAttr,
				szOID_DESTINATION_INDICATOR,         	CryptDllFormatAttr,
				szOID_PREFERRED_DELIVERY_METHOD,     	CryptDllFormatAttr,
				szOID_PRESENTATION_ADDRESS,          	CryptDllFormatAttr,
				szOID_SUPPORTED_APPLICATION_CONTEXT, 	CryptDllFormatAttr,
				szOID_MEMBER,                        	CryptDllFormatAttr,
				szOID_OWNER,                         	CryptDllFormatAttr,
				szOID_ROLE_OCCUPANT,                 	CryptDllFormatAttr,
				szOID_SEE_ALSO,                      	CryptDllFormatAttr,
				szOID_USER_PASSWORD,                 	CryptDllFormatAttr,
				szOID_USER_CERTIFICATE,              	CryptDllFormatAttr,
				szOID_CA_CERTIFICATE,                	CryptDllFormatAttr,
				szOID_AUTHORITY_REVOCATION_LIST,     	CryptDllFormatAttr,
				szOID_CERTIFICATE_REVOCATION_LIST,   	CryptDllFormatAttr,
				szOID_CROSS_CERTIFICATE_PAIR,        	CryptDllFormatAttr,
				szOID_GIVEN_NAME,                    	CryptDllFormatAttr,
				szOID_INITIALS,                     	CryptDllFormatAttr,
                szOID_DOMAIN_COMPONENT,                 CryptDllFormatAttr,
                szOID_PKCS_12_FRIENDLY_NAME_ATTR,       CryptDllFormatAttr,
                szOID_PKCS_12_LOCAL_KEY_ID,             CryptDllFormatAttr,
				X509_NAME,								CryptDllFormatName,
				X509_UNICODE_NAME,						CryptDllFormatName,
				szOID_BASIC_CONSTRAINTS2,				FormatBasicConstraints2,
				X509_BASIC_CONSTRAINTS2,				FormatBasicConstraints2,
                szOID_BASIC_CONSTRAINTS,                FormatBasicConstraints,
                X509_BASIC_CONSTRAINTS,                 FormatBasicConstraints,
				szOID_CRL_REASON_CODE,					FormatCRLReasonCode,
				X509_CRL_REASON_CODE,					FormatCRLReasonCode,
				szOID_ENHANCED_KEY_USAGE,				FormatEnhancedKeyUsage,
				X509_ENHANCED_KEY_USAGE,				FormatEnhancedKeyUsage,
                szOID_SUBJECT_ALT_NAME,                 FormatAltName,
                szOID_ISSUER_ALT_NAME,                  FormatAltName,
                szOID_SUBJECT_ALT_NAME2,                FormatAltName,
                szOID_ISSUER_ALT_NAME2,                 FormatAltName,
                X509_ALTERNATE_NAME,                    FormatAltName,
                szOID_AUTHORITY_KEY_IDENTIFIER,         FormatAuthorityKeyID,
                X509_AUTHORITY_KEY_ID,                  FormatAuthorityKeyID,
                szOID_AUTHORITY_KEY_IDENTIFIER2,        FormatAuthorityKeyID2,
                X509_AUTHORITY_KEY_ID2,                 FormatAuthorityKeyID2,
                szOID_NEXT_UPDATE_LOCATION,             FormatNextUpdateLocation,
                szOID_SUBJECT_KEY_IDENTIFIER,           FormatSubjectKeyID,
                SPC_FINANCIAL_CRITERIA_OBJID,           FormatFinancialCriteria,
                SPC_FINANCIAL_CRITERIA_STRUCT,          FormatFinancialCriteria,
                szOID_RSA_SMIMECapabilities,            FormatSMIMECapabilities,
                PKCS_SMIME_CAPABILITIES,                FormatSMIMECapabilities,
                szOID_KEY_USAGE,                        FormatKeyUsage,
                X509_KEY_USAGE,                         FormatKeyUsage,
                szOID_AUTHORITY_INFO_ACCESS,            FormatAuthortiyInfoAccess,
                X509_AUTHORITY_INFO_ACCESS,             FormatAuthortiyInfoAccess,
                szOID_KEY_ATTRIBUTES,                   FormatKeyAttributes,
                X509_KEY_ATTRIBUTES,                    FormatKeyAttributes,
                szOID_KEY_USAGE_RESTRICTION,            FormatKeyRestriction,
                X509_KEY_USAGE_RESTRICTION,             FormatKeyRestriction,
                szOID_CRL_DIST_POINTS,                  FormatCRLDistPoints,
                X509_CRL_DIST_POINTS,                   FormatCRLDistPoints,
                szOID_CERT_POLICIES,                    FormatCertPolicies,
                X509_CERT_POLICIES,                     FormatCertPolicies,
				SPC_SP_AGENCY_INFO_OBJID,               FormatSPAgencyInfo,
                SPC_SP_AGENCY_INFO_STRUCT,              FormatSPAgencyInfo,
};

DWORD	dwOIDFormatCount=sizeof(OIDFormatTable)/sizeof(OIDFormatTable[0]);

//+-------------------------------------------------------------------------
//  Dll initialization
//--------------------------------------------------------------------------
BOOL
WINAPI
CryptFrmtFuncDllMain(
        HMODULE hModule,
        DWORD  fdwReason,
        LPVOID lpReserved)
{
    BOOL    fRet;

    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:

		hFrmtFuncInst = hModule;

        if (NULL == (hFormatFuncSet = CryptInitOIDFunctionSet(
                CRYPT_OID_FORMAT_OBJECT_FUNC,
                0)))                                // dwFlags
            goto CryptInitFrmtFuncError;

		//install the default formatting routine
		if (!CryptInstallOIDFunctionAddress(
                NULL,                       // hModule
                X509_ASN_ENCODING,
                CRYPT_OID_FORMAT_OBJECT_FUNC,
                1,
                DefaultFormatTable,
                0))                         // dwFlags
            goto CryptInstallFrmtFuncError;

		//install the OID formatting routine
		if (!CryptInstallOIDFunctionAddress(
                NULL,                       // hModule
                X509_ASN_ENCODING,
                CRYPT_OID_FORMAT_OBJECT_FUNC,
                dwOIDFormatCount,
                OIDFormatTable,
                0))                         // dwFlags
            goto CryptInstallFrmtFuncError;


		break;

    case DLL_PROCESS_DETACH:
    case DLL_THREAD_DETACH:
    default:
        break;
    }

    fRet = TRUE;
CommonReturn:
    return fRet;

ErrorReturn:
    fRet = FALSE;
    goto CommonReturn;
TRACE_ERROR(CryptInitFrmtFuncError)
TRACE_ERROR(CryptInstallFrmtFuncError)
}


//------------------------------------------------------------------------
//	   Convert the byte to its Hex presentation.
//
//	   Precondition: byte is less than 15
//
//------------------------------------------------------------------------
ULONG	ByteToHex(BYTE	byte,	LPWSTR	wszZero, LPWSTR wszA)
{
	ULONG	uValue=0;

	if(((ULONG)byte)<=9)
	{
		uValue=((ULONG)byte)+ULONG(*wszZero);	
	}
	else
	{
		uValue=(ULONG)byte-10+ULONG(*wszA);

	}

	return uValue;

}
//--------------------------------------------------------------------------
//
//	 Format the encoded bytes into a hex string in the format of
//   xxxx xxxx xxxx xxxx ...
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatBytesToHex(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	LPWSTR	pwszBuffer=NULL;
	DWORD	dwBufferSize=0;
	DWORD	dwBufferIndex=0;
	DWORD	dwEncodedIndex=0;
	WCHAR	wszSpace[CHAR_SIZE];
	WCHAR	wszZero[CHAR_SIZE];
	WCHAR	wszA[CHAR_SIZE];
	WCHAR	wszHex[HEX_SIZE];
	
	//check for input parameters
	if(( pbEncoded!=NULL && cbEncoded==0)
		||(pbEncoded==NULL && cbEncoded!=0)
		|| (pcbFormat==NULL))
	{
		SetLastError(E_INVALIDARG);
		return FALSE;
	}

	//check for simple case.  No work needed
	if(pbEncoded==NULL && cbEncoded==0)
	{
		*pcbFormat=0;
		return TRUE;
	}


	//calculate the memory needed, in bytes
	//we need 3 wchars per byte, along with the NULL terminator
	dwBufferSize=sizeof(WCHAR)*(cbEncoded*3+1);


	//length only calculation
	if(pcbFormat!=NULL && pbFormat==NULL)
	{
		*pcbFormat=dwBufferSize;
		return TRUE;
	}

	//load the string
	if(!LoadStringU(hFrmtFuncInst, IDS_FRMT_SPACE, wszSpace,
		CHAR_SIZE)
	  ||!LoadStringU(hFrmtFuncInst, IDS_FRMT_ZERO, wszZero,
	    CHAR_SIZE)
	  ||!LoadStringU(hFrmtFuncInst, IDS_FRMT_A, wszA,
	   CHAR_SIZE)
	  ||!LoadStringU(hFrmtFuncInst, IDS_FRMT_HEX, wszHex,
	  HEX_SIZE)
	  )
	{
		SetLastError(E_UNEXPECTED);
		return FALSE;
	}

	pwszBuffer=(LPWSTR)malloc(dwBufferSize);

	if(!pwszBuffer)
	{
		SetLastError(E_OUTOFMEMORY);
		return FALSE;
	}

	dwBufferIndex=0;

	//format the wchar buffer one byte at a time
	for(dwEncodedIndex=0; dwEncodedIndex<cbEncoded; dwEncodedIndex++)
	{
		//copy the space between every two bytes.  Skip for the 1st byte
        if((0!=dwEncodedIndex) && (0==(dwEncodedIndex % 2 )))
        {
		    pwszBuffer[dwBufferIndex]=wszSpace[0];
		    dwBufferIndex++;
        }


		//format the higher 4 bits
		pwszBuffer[dwBufferIndex]=(WCHAR)ByteToHex(
			 (pbEncoded[dwEncodedIndex]&UPPER_BITS)>>4,
			 wszZero, wszA);

		dwBufferIndex++;

		//format the lower 4 bits
		pwszBuffer[dwBufferIndex]=(WCHAR)ByteToHex(
			 pbEncoded[dwEncodedIndex]&LOWER_BITS,
			 wszZero, wszA);

		dwBufferIndex++;

	}

	//add the NULL terminator to the string
	pwszBuffer[dwBufferIndex]=wszSpace[1];

    //calculate the real size for the buffer
    dwBufferSize=sizeof(WCHAR)*(wcslen(pwszBuffer)+1);

	//copy the buffer
	memcpy(pbFormat, pwszBuffer,
		(*pcbFormat>=dwBufferSize) ? dwBufferSize : *pcbFormat);

	free(pwszBuffer);

	//make sure the user has supplied enough memory
	if(*pcbFormat < dwBufferSize)
	{
		*pcbFormat=dwBufferSize;
		SetLastError(ERROR_MORE_DATA);
		return FALSE;
	}
		
	*pcbFormat=dwBufferSize;
	return TRUE;
}


 //+-------------------------------------------------------------------------
// format the specified data structure according to the certificate
// encoding type.
//--------------------------------------------------------------------------
BOOL
WINAPI
CryptFormatObject(
    IN DWORD dwCertEncodingType,
    IN DWORD dwFormatType,
	IN DWORD dwFormatStrType,
	IN void	 *pFormatStruct,
    IN LPCSTR lpszStructType,
    IN const BYTE *pbEncoded,
    IN DWORD cbEncoded,
	OUT void *pbFormat,
    IN OUT DWORD *pcbFormat
    )
{
    BOOL				fResult=FALSE;
    void				*pvFuncAddr;
    HCRYPTOIDFUNCADDR   hFuncAddr;

    if (CryptGetOIDFunctionAddress(
            hFormatFuncSet,
            dwCertEncodingType,
            lpszStructType,
            0,                      // dwFlags
            &pvFuncAddr,
            &hFuncAddr))
	{
        fResult = ((PFN_FORMAT_FUNC) pvFuncAddr)(
				dwCertEncodingType,
				dwFormatType,
				dwFormatStrType,
				pFormatStruct,
				lpszStructType,
				pbEncoded,
				cbEncoded,
				pbFormat,
				pcbFormat
            );
        CryptFreeOIDFunctionAddress(hFuncAddr, 0);
    }
	else
	{
        //do not call the default hex dump if CRYPT_FORMAT_STR_NO_HEX is set
        if(0==(dwFormatStrType & CRYPT_FORMAT_STR_NO_HEX))
        {
		    //call the default routine automatically
		    if (CryptGetOIDFunctionAddress(
                hFormatFuncSet,
                dwCertEncodingType,
                CRYPT_DEFAULT_OID,
                0,                      // dwFlags
                &pvFuncAddr,
                &hFuncAddr))
		    {
			    fResult = ((PFN_FORMAT_FUNC) pvFuncAddr)(
					dwCertEncodingType,
					dwFormatType,
					dwFormatStrType,
					pFormatStruct,
					lpszStructType,
					pbEncoded,
					cbEncoded,
					pbFormat,
					pcbFormat);

			    CryptFreeOIDFunctionAddress(hFuncAddr, 0);
		    }
            else
            {
			    *pcbFormat = 0;
			    fResult = FALSE;
            }
        }
		else
		{
			*pcbFormat = 0;
			fResult = FALSE;
		}
	}
    return fResult;
}



//-----------------------------------------------------------
//
//  This is the actual format routine for an particular RDN attribute.
//
//	lpszStructType is any OID for CERT_RDN_ATTR.  pbEncoded is
//	an encoded BLOB for CERT_NAME_INFO struct.  When pBuffer==NULL,
//	*pcbBuffer return the size of memory to be allocated in bytes.
//	Please notice the string is not NULL terminated.
//
//	For example, to ask for an unicode string of common name,
//	pass lpszStructType=szOID_COMMON_NAME,
//	pass dwFormatType==CRYPT_FORMAT_SIMPL,
//  pBuffer will be set the L"xiaohs@microsoft.com".
//
//
//-------------------------------------------------------------
static BOOL	WINAPI	CryptDllFormatAttr(
				DWORD		dwEncodingType,	
				DWORD		dwFormatType,
				DWORD		dwFormatStrType,
				void		*pStruct,
				LPCSTR		lpszStructType,
				const BYTE	*pbEncoded,
				DWORD		cbEncoded,
				void		*pBuffer,
				DWORD		*pcbBuffer)
{
		BOOL		fResult=FALSE;
		WCHAR		*pwszSeperator=NULL;
		BOOL		fHeader=FALSE;
		BOOL		fLengthOnly=FALSE;
		DWORD		dwBufferCount=0;
		DWORD		dwBufferLimit=0;
		DWORD		dwBufferIncrement=0;
		DWORD		dwSeperator=0;
		DWORD		dwHeader=0;
		DWORD		dwIndex=0;
		DWORD		dwOIDSize=0;
		WCHAR		*pwszBuffer=NULL;
		WCHAR		*pwszHeader=NULL;
		BOOL		fAddSeperator=FALSE;


		DWORD			cbStructInfo=0;
		CERT_NAME_INFO	*pStructInfo=NULL;
		DWORD			dwRDNIndex=0;
		DWORD			dwAttrIndex=0;
		DWORD			dwAttrCount=0;
		CERT_RDN_ATTR	*pCertRDNAttr=NULL;
		PCCRYPT_OID_INFO pOIDInfo=NULL;

		
		//check input parameters
		if(lpszStructType==NULL ||
			(pbEncoded==NULL && cbEncoded!=0) ||
			pcbBuffer==NULL	
		  )
			goto InvalidArg;

		if(cbEncoded==0)
		{
			*pcbBuffer=0;
			goto InvalidArg;
		}

		//get the seperator of the attributes
		//wszCOMMA is the default seperator
		if(dwFormatType & CRYPT_FORMAT_COMMA)
			pwszSeperator=wszCOMMA;
		else
		{
			if(dwFormatType & CRYPT_FORMAT_SEMICOLON)
				pwszSeperator=wszSEMICOLON;
			else
			{
				if(dwFormatType & CRYPT_FORMAT_CRLF)
					pwszSeperator=wszCRLF;
				else
                {
					pwszSeperator=wszPLUS;
                }
			}
		}

		//calculate the length of the seperator
		dwSeperator=wcslen(pwszSeperator)*sizeof(WCHAR);

		//check the requirement for the header
		if(dwFormatType & CRYPT_FORMAT_X509 ||
			dwFormatType & CRYPT_FORMAT_OID)
		{	
			fHeader=TRUE;
		}


		if(NULL==pBuffer)
			fLengthOnly=TRUE;

		//decode the X509_UNICODE_NAME
		if(!CryptDecodeObject(dwEncodingType, X509_UNICODE_NAME,
			pbEncoded, cbEncoded, CRYPT_DECODE_NOCOPY_FLAG,
			NULL, &cbStructInfo))
			goto DecodeError;

		//allocate memory
		pStructInfo=(CERT_NAME_INFO *)malloc(cbStructInfo);
		if(!pStructInfo)
			goto MemoryError;	

		//decode the struct
 		if(!CryptDecodeObject(dwEncodingType, X509_UNICODE_NAME,
			pbEncoded, cbEncoded, CRYPT_DECODE_NOCOPY_FLAG,
			pStructInfo, &cbStructInfo))
			goto DecodeError;


		 //allocate the buffer for formatting
		if(!fLengthOnly)
		{
			pwszBuffer=(WCHAR *)malloc(g_AllocateSize);
			if(!pwszBuffer)
				goto MemoryError;
				
			dwBufferLimit=g_AllocateSize;
		}

	   	//search for the OID requested.  If found one, put it
		//to the buffer.  If no requested attribut is found,
		//return.
		for(dwRDNIndex=0; dwRDNIndex<pStructInfo->cRDN; dwRDNIndex++)
		{
			//the following line is for code optimization
			dwAttrCount=(pStructInfo->rgRDN)[dwRDNIndex].cRDNAttr;

			for(dwAttrIndex=0; dwAttrIndex<dwAttrCount; dwAttrIndex++)
			{
				//look for the specific OIDs in the function
				if(_stricmp(lpszStructType,
				(pStructInfo->rgRDN)[dwRDNIndex].rgRDNAttr[dwAttrIndex].pszObjId)==0)
				{
					pCertRDNAttr=&((pStructInfo->rgRDN)[dwRDNIndex].rgRDNAttr[dwAttrIndex]);

					//init the dwBufferIncrement
					dwBufferIncrement=0;

					//get the header of the tag
					if(fHeader)
					{
						if(dwFormatType & CRYPT_FORMAT_X509)
						{
							//get the OID's name
							pOIDInfo=CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY,
														  (void *)lpszStructType,
														  CRYPT_RDN_ATTR_OID_GROUP_ID);

							if(pOIDInfo)
							{
								//allocate memory, including the NULL terminator
								pwszHeader=(WCHAR *)malloc((wcslen(pOIDInfo->pwszName)+wcslen(wszEQUAL)+1)*
									sizeof(WCHAR));

								if(!pwszHeader)
									goto MemoryError;

								wcscpy(pwszHeader,pOIDInfo->pwszName);

							}
						}

						//use the OID is no mapping is found or
						//OID is requested in the header
						if(pwszHeader==NULL)
						{

							//get the wide character string to the OID
							if(!(dwOIDSize=MultiByteToWideChar(CP_ACP,0,
							lpszStructType,strlen(lpszStructType),NULL,0)))
								goto szTOwszError;

							//allocate memory, including the NULL terminator
							pwszHeader=(WCHAR *)malloc((dwOIDSize+wcslen(wszEQUAL)+1)*
										sizeof(WCHAR));

							if(!pwszHeader)
								goto MemoryError;

							if(!(dwHeader=MultiByteToWideChar(CP_ACP,0,
							lpszStructType,strlen(lpszStructType),pwszHeader,dwOIDSize)))
								 goto szTOwszError;

							//NULL terminate the string
							*(pwszHeader+dwHeader)=L'\0';
							
						}

						//add the euqal sign
						wcscat(pwszHeader,	wszEQUAL);

						//get the header size, in bytes, excluding the NULL terminator
						dwHeader=wcslen(pwszHeader)*sizeof(WCHAR);
						dwBufferIncrement+=dwHeader;
					}


					//allocate enough memory.  Including the NULL terminator
					dwBufferIncrement+=pCertRDNAttr->Value.cbData;
					dwBufferIncrement+=dwSeperator;
					dwBufferIncrement+=2;
	

					if(!fLengthOnly && ((dwBufferCount+dwBufferIncrement)>dwBufferLimit))
					{
					   //reallocate the memory
						pwszBuffer=(WCHAR *)realloc(pwszBuffer,
								max(dwBufferLimit+g_AllocateSize,
								dwBufferLimit+dwBufferIncrement));

						if(!pwszBuffer)
							goto MemoryError;

						dwBufferLimit+=max(g_AllocateSize,dwBufferIncrement);

					}
					
					//add the header if necessary
					if(fHeader)
					{							
						if(!fLengthOnly)
						{
							memcpy((BYTE *)(pwszBuffer+dwBufferCount/sizeof(WCHAR)),
								pwszHeader,dwHeader);
						}

						dwBufferCount+=dwHeader;

						//do not need to do header anymore
						fHeader=FALSE;
					}

					//add the seperator	after the 1st iteration
					if(fAddSeperator)
					{
						
						if(!fLengthOnly)
						{
							memcpy((BYTE *)(pwszBuffer+dwBufferCount/sizeof(WCHAR)),
								pwszSeperator,dwSeperator);
						}

						dwBufferCount+=dwSeperator;
					}
					else
						fAddSeperator=TRUE;

					//add the attr content
					if(!fLengthOnly)
					{
						memcpy((BYTE *)(pwszBuffer+dwBufferCount/sizeof(WCHAR)),
							(pCertRDNAttr->Value.pbData),
							pCertRDNAttr->Value.cbData);
					}

					//increment the buffercount
					dwBufferCount+=pCertRDNAttr->Value.cbData;

				}
			}
		}


		//return the result as requested
		//check if the requested OID is actually in the DN
		if(0==dwBufferCount)
		{
			*pcbBuffer=dwBufferCount;
			goto NotFoundError;
		}


		//we need to NULL terminate the string
		if(!fLengthOnly)
			*(pwszBuffer+dwBufferCount/sizeof(WCHAR))=L'\0';

		dwBufferCount+=2;

		if(pBuffer==NULL)
		{
			*pcbBuffer=dwBufferCount;
			fResult=TRUE;
			goto CommonReturn;
		}

		if((*pcbBuffer)<dwBufferCount)
		{
			*pcbBuffer=dwBufferCount;
			goto MoreDataError;		
		}


		*pcbBuffer=dwBufferCount;
		memcpy(pBuffer, pwszBuffer,dwBufferCount);

		fResult=TRUE;

CommonReturn:
		if(pwszHeader)
			free(pwszHeader);

		if(pwszBuffer)
			free(pwszBuffer);

		if(pStructInfo)
			free(pStructInfo);

		return fResult;

ErrorReturn:
    fResult = FALSE;
    goto CommonReturn;


SET_ERROR(InvalidArg, E_INVALIDARG);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(DecodeError);
TRACE_ERROR(szTOwszError);
SET_ERROR(NotFoundError, E_FAIL);
SET_ERROR(MoreDataError, ERROR_MORE_DATA);
}




//-----------------------------------------------------------
//
//  This is the actual format routine for an complete CERT_NAME
//
//
//	lpszStructType should be X509_NAME  pbEncoded is
//	an encoded BLOB for CERT_NAME_INFO struct.  When pBuffer==NULL,
//	*pcbBuffer return the size of memory to be allocated in bytes.
//	Please notice the string is NULL terminated.
//
//-------------------------------------------------------------
static BOOL	WINAPI	CryptDllFormatName(
				DWORD		dwEncodingType,	
				DWORD		dwFormatType,
				DWORD		dwFormatStrType,
				void		*pStruct,
				LPCSTR		lpszStructType,
				const BYTE	*pbEncoded,
				DWORD		cbEncoded,
				void		*pbBuffer,
				DWORD		*pcbBuffer)
{
    //makesure lpszStructType is X509_NAME or X509_UNICODE_NAME
	if((X509_NAME != lpszStructType) &&
		    (X509_UNICODE_NAME != lpszStructType))
    {
        SetLastError(E_INVALIDARG);
        return FALSE;
    }

 	//check input parameters
	if((pbEncoded==NULL && cbEncoded!=0) || pcbBuffer==NULL)
    {
        SetLastError(E_INVALIDARG);
        return FALSE;
    }

	if(cbEncoded==0)
    {
        SetLastError(E_INVALIDARG);
        return FALSE;
    }

    //call CryptDllFormatNameAll with no prefix
    return  CryptDllFormatNameAll(dwEncodingType,	
                                  dwFormatType,
                                  dwFormatStrType,
                                  pStruct,
                                  0,
                                  FALSE,
                                  pbEncoded,
                                  cbEncoded,
                                  &pbBuffer,
                                  pcbBuffer);

}


//-----------------------------------------------------------
//
//  This is the actual format routine for an complete CERT_NAME
//
//
//	lpszStructType should be X509_NAME  pbEncoded is
//	an encoded BLOB for CERT_NAME_INFO struct.  When pBuffer==NULL,
//	*pcbBuffer return the size of memory to be allocated in bytes.
//	Please notice the string is NULL terminated.
//
//-------------------------------------------------------------
BOOL	CryptDllFormatNameAll(
				DWORD		dwEncodingType,	
				DWORD		dwFormatType,
				DWORD		dwFormatStrType,
				void		*pStruct,
                UINT        idsPreFix,
                BOOL        fToAllocate,
				const BYTE	*pbEncoded,
				DWORD		cbEncoded,
				void		**ppbBuffer,
				DWORD		*pcbBuffer)
{

		BOOL			    fResult=FALSE;
		DWORD			    dwIndex=0;
		DWORD			    dwStrType=0;
		CERT_NAME_BLOB	    Cert_Name_Blob;
		DWORD			    dwSize=0;
        LPWSTR              pwszName=NULL;
        LPWSTR              pwszMulti=NULL;

		Cert_Name_Blob.cbData=cbEncoded;
		Cert_Name_Blob.pbData=(BYTE *)pbEncoded;

	
		//calculate the dwStryType to use for CertNameToStrW
        dwStrType=FormatToStr(dwFormatType);

        //overwrite dwStrType to default if we are doing MULTI line format
        //since the options will be ignored
        //We want to use + and , for the seperator
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
        {

            dwStrType &=~(CERT_NAME_STR_CRLF_FLAG);
            dwStrType &=~(CERT_NAME_STR_COMMA_FLAG);
            dwStrType &=~(CERT_NAME_STR_SEMICOLON_FLAG);
            dwStrType &=~(CERT_NAME_STR_NO_QUOTING_FLAG);
            dwStrType &=~(CERT_NAME_STR_NO_PLUS_FLAG);


        }

        //if this function is not called from CryptDllFormatName,
        //make sure that we use the RESERSE Flag
        if(TRUE == fToAllocate)
            dwStrType |= CERT_NAME_STR_REVERSE_FLAG;

		//call the CertNameToStrW to convert
        dwSize=CertNameToStrW(dwEncodingType,
                        &Cert_Name_Blob,
                        dwStrType,
                        NULL,
                        0);

        if(0==dwSize)
            goto CertNameToStrError;

        pwszName=(LPWSTR)malloc(sizeof(WCHAR)*(dwSize));
        if(NULL==pwszName)
            goto MemoryError;

        dwSize=CertNameToStrW(dwEncodingType,
                        &Cert_Name_Blob,
                        dwStrType,
                        pwszName,
                        dwSize);
        if(0==dwSize)
            goto CertNameToStrError;

        //we do not need to parse the string for single line format
        if(0==(dwFormatStrType &  CRYPT_FORMAT_STR_MULTI_LINE))
        {
            //calculate the bytes needed
            dwSize=sizeof(WCHAR)*(wcslen(pwszName)+1);

            //if FALSE==fToAllocate, we do not allocate the memory on user's
            //behalf; otherwize, allocate memory to eliminate the need for
            //double call
            if(FALSE==fToAllocate)
            {
                if(NULL==(*ppbBuffer))
                {
                    *pcbBuffer=dwSize;
                    fResult=TRUE;
                    goto CommonReturn;
                }

                if(*pcbBuffer < dwSize)
                {
                    *pcbBuffer=dwSize;
                    goto MoreDataError;
                }

                memcpy(*ppbBuffer, pwszName, dwSize);
                *pcbBuffer=dwSize;
            }
            else
            {
                *ppbBuffer=malloc(dwSize);

                if(NULL==(*ppbBuffer))
                    goto MemoryError;

                memcpy(*ppbBuffer, pwszName, dwSize);

                //pcbBuffer can be NULL in this case
            }
        }
        else
        {
            //we need to parse the string to make the multiple format
            if(!GetCertNameMulti(pwszName, idsPreFix, &pwszMulti))
                goto GetCertNameError;

            //calculate the bytes needee
            dwSize=sizeof(WCHAR)*(wcslen(pwszMulti)+1);

            //if FALSE==fToAllocate, we do not allocate the memory on user's
            //behalf; otherwize, allocate memory to eliminate the need for
            //double call
            if(FALSE==fToAllocate)
            {
                if(NULL==(*ppbBuffer))
                {
                    *pcbBuffer=dwSize;
                    fResult=TRUE;
                    goto CommonReturn;
                }

                if(*pcbBuffer < dwSize)
                {
                    *pcbBuffer=dwSize;
                    goto MoreDataError;
                }

                memcpy(*ppbBuffer, pwszMulti, dwSize);
                *pcbBuffer=dwSize;

            }
            else
            {
                *ppbBuffer=malloc(dwSize);

                if(NULL==(*ppbBuffer))
                    goto MemoryError;

                memcpy(*ppbBuffer, pwszMulti, dwSize);

                //pcbBuffer can be NULL in this case
            }
        }


        fResult=TRUE;


CommonReturn:

    if(pwszName)
        free(pwszName);

    if(pwszMulti)
        free(pwszMulti);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(CertNameToStrError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(GetCertNameError);

}

//--------------------------------------------------------------------------
//
//	 FormatBasicConstraints2:   szOID_BASIC_CONSTRAINTS2
//                              X509_BASIC_CONSTRAINTS2
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatBasicConstraints2(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
	WCHAR							wszSubject[SUBJECT_SIZE];
	WCHAR							wszNone[NONE_SIZE];
	PCERT_BASIC_CONSTRAINTS2_INFO	pInfo=NULL;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
	UINT							idsSub=0;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_BASIC_CONSTRAINTS2,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

	//load the string for the subjectType
    if (pInfo->fCA)
		idsSub=IDS_SUB_CA;
	else
		idsSub=IDS_SUB_EE;

	if(!LoadStringU(hFrmtFuncInst,idsSub, wszSubject, sizeof(wszSubject)/sizeof(wszSubject[0])))
		goto LoadStringError;

    if (pInfo->fPathLenConstraint)
	{
        //decide between signle line and multi line display
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            idsSub=IDS_BASIC_CONS2_PATH_MULTI;
        else
            idsSub=IDS_BASIC_CONS2_PATH;

        if(!FormatMessageUnicode(&pwszFormat,idsSub,
								wszSubject, pInfo->dwPathLenConstraint))
			goto FormatMsgError;
	}
    else
	{
		if(!LoadStringU(hFrmtFuncInst,IDS_NONE, wszNone, sizeof(wszNone)/sizeof(wszNone[0])))
			goto LoadStringError;

        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            idsSub=IDS_BASIC_CONS2_NONE_MULTI;
        else
            idsSub=IDS_BASIC_CONS2_NONE;

        if(!FormatMessageUnicode(&pwszFormat,idsSub,
								wszSubject, wszNone))
			goto FormatMsgError;
	}


	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:
	if(pwszFormat)
		LocalFree((HLOCAL)pwszFormat);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);

}


//--------------------------------------------------------------------------
//
//	 FormatSPCObject:
//
//   idsPreFix is the pre fix for mulit-line display
//--------------------------------------------------------------------------
BOOL FormatSPCObject(
	DWORD		                dwFormatType,
	DWORD		                dwFormatStrType,
    void		                *pFormatStruct,
    UINT                        idsPreFix,
    PSPC_SERIALIZED_OBJECT      pInfo,
    LPWSTR                      *ppwszFormat)
{

    BOOL        fResult=FALSE;
    LPWSTR      pwszHex=NULL;
    LPWSTR      pwszClassId=NULL;
    WCHAR       wszPreFix[PRE_FIX_SIZE];
    DWORD       cbNeeded=0;

    LPWSTR      pwszClassFormat=NULL;
    LPWSTR      pwszDataFormat=NULL;

    assert(pInfo);

    *ppwszFormat=NULL;

   //load the pre-dix
   if(0!=idsPreFix)
   {
       if(!LoadStringU(hFrmtFuncInst, idsPreFix,
                        wszPreFix, sizeof(wszPreFix)/sizeof(wszPreFix[0])))
        goto LoadStringError;

   }


    cbNeeded=0;

    if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->ClassId,
                        16,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

    pwszClassId=(LPWSTR)malloc(cbNeeded);
    if(NULL==pwszClassId)
         goto MemoryError;

    if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->ClassId,
                        16,
                        pwszClassId,
	                    &cbNeeded))
        goto FormatBytesToHexError;


    //format
    if(!FormatMessageUnicode(&pwszClassFormat, IDS_SPC_OBJECT_CLASS, pwszClassId))
            goto FormatMsgError;

    //strcat
    *ppwszFormat=(LPWSTR)malloc(sizeof(WCHAR) * (wcslen(pwszClassFormat)+wcslen(wszPreFix)+wcslen(wszCOMMA)+1));
    if(NULL==*ppwszFormat)
        goto MemoryError;

    **ppwszFormat=L'\0';

    if(0!=idsPreFix)
        wcscat(*ppwszFormat, wszPreFix);

    wcscat(*ppwszFormat, pwszClassFormat);

    //format based on the availability of SerializedData
    if(0!=pInfo->SerializedData.cbData)
    {
        //cancatenate the ", " or \n"
        if(NULL != (*ppwszFormat))
        {
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
               wcscat(*ppwszFormat, wszNEWLN);
            else
               wcscat(*ppwszFormat, wszCOMMA);
        }

       cbNeeded=0;

       if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->SerializedData.pbData,
                        pInfo->SerializedData.cbData,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        pwszHex=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszHex)
            goto MemoryError;

        if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->SerializedData.pbData,
                        pInfo->SerializedData.cbData,
                        pwszHex,
	                    &cbNeeded))
            goto FormatBytesToHexError;

          if(!FormatMessageUnicode(&pwszDataFormat, IDS_SPC_OBJECT_DATA,pwszHex))
            goto FormatMsgError;

        //strcat
        *ppwszFormat=(LPWSTR)realloc(*ppwszFormat,
                sizeof(WCHAR)* (wcslen(*ppwszFormat)+wcslen(pwszDataFormat)+wcslen(wszPreFix)+1));
        if(NULL==*ppwszFormat)
            goto MemoryError;

        if(0!=idsPreFix)
            wcscat(*ppwszFormat, wszPreFix);

        wcscat(*ppwszFormat, pwszDataFormat);

    }

	fResult=TRUE;
	

CommonReturn:
    if(pwszHex)
        free(pwszHex);

    if(pwszClassId)
        free(pwszClassId);

    if(pwszClassFormat)
        LocalFree((HLOCAL)pwszClassFormat);

    if(pwszDataFormat)
        LocalFree((HLOCAL)pwszDataFormat);

	return fResult;

ErrorReturn:
    if(*ppwszFormat)
    {
        free(*ppwszFormat);
        *ppwszFormat=NULL;
    }


	fResult=FALSE;
	goto CommonReturn;


TRACE_ERROR(FormatBytesToHexError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatMsgError);
TRACE_ERROR(LoadStringError);
}


//--------------------------------------------------------------------------
//
//	 FormatSPCLink:
//--------------------------------------------------------------------------
BOOL FormatSPCLink(
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
    void		*pFormatStruct,
    UINT        idsPreFix,
    PSPC_LINK   pInfo,
    LPWSTR      *ppwsz)
{

    BOOL        fResult=FALSE;
    LPWSTR      pwszObj=NULL;
    DWORD       cbNeeded=0;
    UINT        ids=0;
    LPWSTR      pwszFormat=NULL;


    assert(pInfo);

    *ppwsz=NULL;

    switch(pInfo->dwLinkChoice)
    {
        case SPC_URL_LINK_CHOICE:
                if(!FormatMessageUnicode(&pwszFormat, IDS_SPC_URL_LINK,pInfo->pwszUrl))
                    goto FormatMsgError;
            break;

        case SPC_MONIKER_LINK_CHOICE:
                if(!FormatSPCObject(
                            dwFormatType,
                            dwFormatStrType,
                            pFormatStruct,
                            idsPreFix,
                            &(pInfo->Moniker),
                            &pwszObj))
                    goto FormatSPCObjectError;


                //decide between single line and mulitple line format
                if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                    ids=IDS_SPC_MONIKER_LINK_MULTI;
                else
                    ids=IDS_SPC_MONIKER_LINK;

                if(!FormatMessageUnicode(&pwszFormat,ids,pwszObj))
                    goto FormatMsgError;
            break;


        case SPC_FILE_LINK_CHOICE:
               if(!FormatMessageUnicode(&pwszFormat, IDS_SPC_FILE_LINK, pInfo->pwszFile))
                    goto FormatMsgError;

            break;

        default:

               if(!FormatMessageUnicode(&pwszFormat, IDS_SPC_LINK_UNKNOWN,
                        pInfo->dwLinkChoice))
                    goto FormatMsgError;
    }

    *ppwsz=(LPWSTR)malloc(sizeof(WCHAR) * (wcslen(pwszFormat)+1));
    if(NULL==(*ppwsz))
        goto MemoryError;

    memcpy(*ppwsz, pwszFormat, sizeof(WCHAR) * (wcslen(pwszFormat)+1));
	fResult=TRUE;
	

CommonReturn:

    if(pwszObj)
        free(pwszObj);

    if(pwszFormat)
        LocalFree((HLOCAL)pwszFormat);

	return fResult;

ErrorReturn:

    if(*ppwsz)
    {
        free(*ppwsz);
        *ppwsz=NULL;
    }

	fResult=FALSE;
	goto CommonReturn;

TRACE_ERROR(FormatMsgError);
TRACE_ERROR(FormatSPCObjectError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
}


//--------------------------------------------------------------------------
//
//	 FormatSPCImage:
//--------------------------------------------------------------------------
BOOL FormatSPCImage(
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
    void		*pFormatStruct,
    UINT        idsPreFix,
    PSPC_IMAGE  pInfo,
    LPWSTR      *ppwszImageFormat)
{
    BOOL        fResult=FALSE;
    LPWSTR       pwszFormat=NULL;
    LPWSTR       pwszLink=NULL;
    LPWSTR       pwszLinkFormat=NULL;
    LPWSTR      pwszHex=NULL;
    LPWSTR      pwszHexFormat=NULL;
    UINT        ids=0;

    DWORD       cbNeeded=0;

    assert(pInfo);

    //init
    *ppwszImageFormat=NULL;

	pwszFormat=(LPWSTR)malloc(sizeof(WCHAR));
    if(NULL==pwszFormat)
        goto MemoryError;

    *pwszFormat=L'\0';

    if(pInfo->pImageLink)
    {
        if(!FormatSPCLink(dwFormatType,
                          dwFormatStrType,
                          pFormatStruct,
                          idsPreFix,
                          pInfo->pImageLink,
                          &pwszLink))
            goto FormatSPCLinkError;

       //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_IMAGE_LINK_MULTI;
        else
            ids=IDS_IMAGE_LINK;


        if(!FormatMessageUnicode(&pwszLinkFormat, ids,
                            &pwszLink))
            goto FormatMsgError;

        pwszFormat=(LPWSTR)realloc(pwszFormat, 
                    sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszCOMMA)+wcslen(pwszLinkFormat)+1));
        if(NULL==pwszFormat)
            goto MemoryError;

        wcscat(pwszFormat, pwszLinkFormat);
    }

    if(0!=pInfo->Bitmap.cbData)
    {
        //strcat ", "
        if(0!=wcslen(pwszFormat))
        {
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                wcscat(pwszFormat, wszCOMMA);
        }

       cbNeeded=0;

       if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->Bitmap.pbData,
                        pInfo->Bitmap.cbData,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        pwszHex=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszHex)
            goto MemoryError;

        if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->Bitmap.pbData,
                        pInfo->Bitmap.cbData,
                        pwszHex,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_IMAGE_BITMAP_MULTI;
        else
            ids=IDS_IMAGE_BITMAP;


        if(!FormatMessageUnicode(&pwszHexFormat, ids, pwszHex))
            goto FormatMsgError;


        pwszFormat=(LPWSTR)realloc(pwszFormat, 
            sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszCOMMA)+wcslen(pwszHexFormat)+1));
        if(NULL==pwszFormat)
            goto MemoryError;

        wcscat(pwszFormat, pwszHexFormat);

       //free memory
        free(pwszHex);
        pwszHex=NULL;
        LocalFree((HLOCAL)pwszHexFormat);
        pwszHexFormat=NULL;

    }

   if(0!=pInfo->Metafile.cbData)
    {
        //strcat ", "
        if(0!=wcslen(pwszFormat))
        {
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                wcscat(pwszFormat, wszCOMMA);
        }

       cbNeeded=0;

       if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->Metafile.pbData,
                        pInfo->Metafile.cbData,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        pwszHex=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszHex)
            goto MemoryError;

        if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->Metafile.pbData,
                        pInfo->Metafile.cbData,
                        pwszHex,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_IMAGE_METAFILE_MULTI;
        else
            ids=IDS_IMAGE_METAFILE;

        if(!FormatMessageUnicode(&pwszHexFormat, ids, pwszHex))
            goto FormatMsgError;


        pwszFormat=(LPWSTR)realloc(pwszFormat, 
            sizeof(WCHAR) *(wcslen(pwszFormat)+wcslen(wszCOMMA)+wcslen(pwszHexFormat)+1));
        if(NULL==pwszFormat)
            goto MemoryError;

        wcscat(pwszFormat, pwszHexFormat);

       //free memory
        free(pwszHex);
        pwszHex=NULL;
        LocalFree((HLOCAL)pwszHexFormat);
        pwszHexFormat=NULL;

    }

   if(0!=pInfo->EnhancedMetafile.cbData)
    {
        //strcat ", "
        if(0!=wcslen(pwszFormat))
        {
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                wcscat(pwszFormat, wszCOMMA);
        }

       cbNeeded=0;

       if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->EnhancedMetafile.pbData,
                        pInfo->EnhancedMetafile.cbData,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        pwszHex=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszHex)
            goto MemoryError;

        if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->EnhancedMetafile.pbData,
                        pInfo->EnhancedMetafile.cbData,
                        pwszHex,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_IMAGE_ENHANCED_METAFILE_MULTI;
        else
            ids=IDS_IMAGE_ENHANCED_METAFILE;

        if(!FormatMessageUnicode(&pwszHexFormat, ids, pwszHex))
            goto FormatMsgError;


        pwszFormat=(LPWSTR)realloc(pwszFormat, 
            sizeof(WCHAR) *(wcslen(pwszFormat)+wcslen(wszCOMMA)+wcslen(pwszHexFormat)+1));
        if(NULL==pwszFormat)
            goto MemoryError;

        wcscat(pwszFormat, pwszHexFormat);

       //free memory
        free(pwszHex);
        pwszHex=NULL;
        LocalFree((HLOCAL)pwszHexFormat);
        pwszHexFormat=NULL;

    }

   if(0!=pInfo->GifFile.cbData)
    {
        //strcat ", "
        if(0!=wcslen(pwszFormat))
        {
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                wcscat(pwszFormat, wszCOMMA);
        }

       cbNeeded=0;

       if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->GifFile.pbData,
                        pInfo->GifFile.cbData,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        pwszHex=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszHex)
            goto MemoryError;

        if(!FormatBytesToHex(
                        0,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->GifFile.pbData,
                        pInfo->GifFile.cbData,
                        pwszHex,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_IMAGE_GIFFILE_MULTI;
        else
            ids=IDS_IMAGE_GIFFILE;

        if(!FormatMessageUnicode(&pwszHexFormat, IDS_IMAGE_GIFFILE,
            pwszHex))
            goto FormatMsgError;


        pwszFormat=(LPWSTR)realloc(pwszFormat, 
            sizeof(WCHAR) *(wcslen(pwszFormat)+wcslen(wszCOMMA)+wcslen(pwszHexFormat)+1));
        if(NULL==pwszFormat)
            goto MemoryError;

        wcscat(pwszFormat, pwszHexFormat);

       //free memory
        free(pwszHex);
        pwszHex=NULL;
        LocalFree((HLOCAL)pwszHexFormat);
        pwszHexFormat=NULL;

    }

    if(0==wcslen(pwszFormat))
    {
        //fine if nothing is formatted
        *ppwszImageFormat=NULL;
    }
    else
    {
        *ppwszImageFormat=(LPWSTR)malloc(sizeof(WCHAR)*(wcslen(pwszFormat)+1));  

        if(NULL == ppwszImageFormat)
            goto MemoryError;

        memcpy(*ppwszImageFormat, pwszFormat, sizeof(WCHAR)*(wcslen(pwszFormat)+1));
    }

	fResult=TRUE;
	

CommonReturn:
    if(pwszHex)
        free(pwszHex);

    if(pwszHexFormat)
        LocalFree((HLOCAL)pwszHexFormat);

    if(pwszLink)
        free(pwszLink);

    if(pwszLinkFormat)
        LocalFree((HLOCAL)pwszLinkFormat);

    if(pwszFormat)
        free(pwszFormat);

	return fResult;

ErrorReturn:

    if(*ppwszImageFormat)
    {
        free(*ppwszImageFormat);
        *ppwszImageFormat=NULL;
    }

	fResult=FALSE;
	goto CommonReturn;

TRACE_ERROR(FormatSPCLinkError);
TRACE_ERROR(FormatMsgError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatBytesToHexError);

}


//--------------------------------------------------------------------------
//
//	 FormatSPAgencyInfo:   SPC_SP_AGENCY_INFO_STRUCT
//                         SPC_SP_AGENCY_INFO_OBJID
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatSPAgencyInfo(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwsz=NULL;
	PSPC_SP_AGENCY_INFO         	pInfo=NULL;

    LPWSTR                           pwszPolicyInfo=NULL;
    LPWSTR                           pwszPolicyInfoFormat=NULL;
    LPWSTR                           pwszLogoLink=NULL;
    LPWSTR                           pwszLogoLinkFormat=NULL;
    LPWSTR                           pwszPolicyDsplyFormat=NULL;
    LPWSTR                           pwszLogoImage=NULL;
    LPWSTR                           pwszLogoImageFormat=NULL;

	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
	HRESULT                          hr=S_OK;
    UINT                            ids=0;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,SPC_SP_AGENCY_INFO_STRUCT,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

	pwsz=(LPWSTR)malloc(sizeof(WCHAR));
    if(NULL==pwsz)
        goto MemoryError;

    *pwsz=L'\0';

    //format pPolicyInformation
    if(pInfo->pPolicyInformation)
    {

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_TWO_TABS;
        else
            ids=0;

        if(!FormatSPCLink(dwFormatType,
                             dwFormatStrType,
                             pFormatStruct,
                             ids,
                             pInfo->pPolicyInformation,
                             &pwszPolicyInfo))
            goto FormatSPCLinkError;

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_AGENCY_POLICY_INFO_MULTI;
        else
            ids=IDS_AGENCY_POLICY_INFO;

        if(!FormatMessageUnicode(&pwszPolicyInfoFormat, ids, pwszPolicyInfo))
            goto FormatMsgError;

        //strcat
        pwsz=(LPWSTR)realloc(pwsz, 
            sizeof(WCHAR) *(wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszPolicyInfoFormat)+1));
        if(NULL==pwsz)
            goto MemoryError;

        wcscat(pwsz, pwszPolicyInfoFormat);
    }


    //format pwszPolicyDisplayText
    if(pInfo->pwszPolicyDisplayText)
    {
        //strcat ", "
        if(0!=wcslen(pwsz))
        {
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                wcscat(pwsz, wszCOMMA);
        }

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_AGENCY_POLICY_DSPLY_MULTI;
        else
            ids=IDS_AGENCY_POLICY_DSPLY;

        if(!FormatMessageUnicode(&pwszPolicyDsplyFormat, ids, pInfo->pwszPolicyDisplayText))
            goto FormatMsgError;

        //strcat
        pwsz=(LPWSTR)realloc(pwsz,
            sizeof(WCHAR) *(wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszPolicyDsplyFormat)+1));
        if(NULL==pwsz)
            goto MemoryError;

        wcscat(pwsz, pwszPolicyDsplyFormat);
    }

    //pLogoImage
    if(pInfo->pLogoImage)
    {

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_THREE_TABS;
        else
            ids=0;


        if(!FormatSPCImage(dwFormatType,
                             dwFormatStrType,
                             pFormatStruct,
                             ids,
                             pInfo->pLogoImage,
                             &pwszLogoImage))
            goto FormatSPCImageError;

        //spcImage can include nothing
        if(NULL!=pwszLogoImage)
        {
            //strcat ", "
            if(0!=wcslen(pwsz))
            {
                if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                    wcscat(pwsz, wszCOMMA);
            }

            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_AGENCY_LOGO_IMAGE_MULTI;
            else
                ids=IDS_AGENCY_LOGO_IMAGE;


            if(!FormatMessageUnicode(&pwszLogoImageFormat,ids,pwszLogoImage))
                goto FormatMsgError;

            //strcat
            pwsz=(LPWSTR)realloc(pwsz,
                sizeof(WCHAR) *(wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszLogoImageFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, pwszLogoImageFormat);
        }

    }

    //format pLogoLink
    if(pInfo->pLogoLink)
    {
        //strcat ", "
        if(0!=wcslen(pwsz))
        {
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                wcscat(pwsz, wszCOMMA);
        }

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_TWO_TABS;
        else
            ids=0;


        if(!FormatSPCLink(dwFormatType,
                             dwFormatStrType,
                             pFormatStruct,
                             ids,
                             pInfo->pLogoLink,
                             &pwszLogoLink))
            goto FormatSPCLinkError;


        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_AGENCY_LOGO_LINK_MULTI;
        else
            ids=IDS_AGENCY_LOGO_LINK;

        if(!FormatMessageUnicode(&pwszLogoLinkFormat, ids, pwszLogoLink))
            goto FormatMsgError;

        //strcat
        pwsz=(LPWSTR)realloc(pwsz,
            sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszLogoLinkFormat)+1));
        if(NULL==pwsz)
            goto MemoryError;

        wcscat(pwsz, pwszLogoLinkFormat);
    }

    if(0==wcslen(pwsz))
    {
       //no data
        pwszFormat=(LPWSTR)malloc((NO_INFO_SIZE+1)*sizeof(WCHAR));
        if(NULL==pwszFormat)
            goto MemoryError;

        if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, pwszFormat, NO_INFO_SIZE))
            goto LoadStringError;

    }
    else
    {
        pwszFormat=pwsz;
        pwsz=NULL;
    }


	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:

    if(pwszPolicyInfo)
        free(pwszPolicyInfo);

    if(pwszPolicyInfoFormat)
        LocalFree((HLOCAL)pwszPolicyInfoFormat);

    if(pwszLogoLink)
        free(pwszLogoLink);

    if(pwszLogoLinkFormat)
        LocalFree((HLOCAL)pwszLogoLinkFormat);

    if(pwszPolicyDsplyFormat)
        LocalFree((HLOCAL)pwszPolicyDsplyFormat);

    if(pwszLogoImage)
        free(pwszLogoImage);

    if(pwszLogoImageFormat)
        LocalFree((HLOCAL)pwszLogoImageFormat);

	if(pwszFormat)
		free(pwszFormat);

    if(pwsz)
        free(pwsz);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatSPCLinkError);
TRACE_ERROR(FormatSPCImageError);

}

//--------------------------------------------------------------------------
//
//	 FormatCertQualifier:
//--------------------------------------------------------------------------
BOOL FormatCertQualifier(
	DWORD		                    dwCertEncodingType,
	DWORD		                    dwFormatType,
	DWORD		                    dwFormatStrType,
	void		                    *pFormatStruct,
    PCERT_POLICY_QUALIFIER_INFO     pInfo,
    LPWSTR                          *ppwszFormat)
{
    BOOL        fResult=FALSE;
    LPWSTR      pwszHex=NULL;
    DWORD       cbNeeded=0;
    UINT        ids=0;

    *ppwszFormat=NULL;

    if(pInfo->Qualifier.cbData)
    {
       //get the Hex dump of the Key Usage
       cbNeeded=0;

       if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->Qualifier.pbData,
                        pInfo->Qualifier.cbData,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        pwszHex=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszHex)
            goto MemoryError;

        if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        NULL,
                        pInfo->Qualifier.pbData,
                        pInfo->Qualifier.cbData,
                        pwszHex,
	                    &cbNeeded))
            goto FormatBytesToHexError;


        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_POLICY_QUALIFIER_MULTI;
        else
            ids=IDS_POLICY_QUALIFIER;


        if(!FormatMessageUnicode(ppwszFormat, ids,
            pInfo->pszPolicyQualifierId, pwszHex))
            goto FormatMsgError;
    }
    else
    {
        if(!FormatMessageUnicode(ppwszFormat, IDS_POLICY_QUALIFIER_NO_BLOB,
            pInfo->pszPolicyQualifierId))
            goto FormatMsgError;

    }

	fResult=TRUE;
	

CommonReturn:

    if(pwszHex)
        free(pwszHex);

	return fResult;

ErrorReturn:

    if(*ppwszFormat)
    {
        LocalFree((HLOCAL)(*ppwszFormat));
        *ppwszFormat=NULL;
    }


	fResult=FALSE;
	goto CommonReturn;


TRACE_ERROR(FormatBytesToHexError);
TRACE_ERROR(FormatMsgError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
}


//--------------------------------------------------------------------------
//
//	 FormatCertPolicies:     X509_CERT_POLICIES
//                           szOID_CERT_POLICIES
//
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatCertPolicies(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
    LPWSTR                           pwsz=NULL;
    LPWSTR                           pwszPolicyFormat=NULL;
    LPWSTR                           pwszQualifiers=NULL;
    LPWSTR                           pwszQualifierFormat=NULL;
    LPWSTR                           pwszOneQualifier=NULL;

	PCERT_POLICIES_INFO	            pInfo=NULL;

    PCERT_POLICY_INFO               pPolicyInfo=NULL;
    DWORD                           dwIndex=0;
    DWORD                           dwQualifierIndex=0;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    HRESULT                         hr=S_OK;
    UINT                            ids=0;


	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_CERT_POLICIES,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

    pwsz=(LPWSTR)malloc(sizeof(WCHAR));
    if(NULL==pwsz)
        goto MemoryError;

    *pwsz=L'\0';

    for(dwIndex=0; dwIndex < pInfo->cPolicyInfo; dwIndex++)
    {
       //strcat ", "
       if(0!=wcslen(pwsz))
       {
            if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
               wcscat(pwsz, wszCOMMA);
       }

        pPolicyInfo=&(pInfo->rgPolicyInfo[dwIndex]);


        pwszQualifiers=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwszQualifiers)
        goto MemoryError;

        *pwszQualifiers=L'\0';

         //format the qualifiers
         for(dwQualifierIndex=0;  dwQualifierIndex < pPolicyInfo->cPolicyQualifier;
            dwQualifierIndex++)
         {

            //strcat ", "
            if(0!=wcslen(pwszQualifiers))
            {
                if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                    wcscat(pwszQualifiers, wszCOMMA);
            }

             if(!FormatCertQualifier(dwCertEncodingType,
                                     dwFormatType,
                                     dwFormatStrType,
                                     pFormatStruct,
                                     &(pPolicyInfo->rgPolicyQualifier[dwQualifierIndex]),
                                     &pwszOneQualifier))
                    goto FormatCertQualifierError;

            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_POLICY_QUALIFIER_INFO_MULTI;
            else
                ids=IDS_POLICY_QUALIFIER_INFO;


             //format
             if(!FormatMessageUnicode(&pwszQualifierFormat,ids,
                    dwIndex+1,
                    dwQualifierIndex+1,
                    pwszOneQualifier))
                    goto FormatMsgError;

             //strcat
             pwszQualifiers=(LPWSTR)realloc(pwszQualifiers, 
                 sizeof(WCHAR) * (wcslen(pwszQualifiers)+wcslen(wszCOMMA)+wcslen(pwszQualifierFormat)+1));
             if(NULL==pwszQualifiers)
                 goto MemoryError;

             wcscat(pwszQualifiers, pwszQualifierFormat);

             LocalFree((HLOCAL)pwszOneQualifier);
             pwszOneQualifier=NULL;

             LocalFree((HLOCAL)pwszQualifierFormat);
             pwszQualifierFormat=NULL;
         }

         //now, format the certPolicyInfo
         if(0!=pPolicyInfo->cPolicyQualifier)
         {

            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_CERT_POLICY_MULTI;
            else
                ids=IDS_CERT_POLICY;

             if(!FormatMessageUnicode(&pwszPolicyFormat,ids,
                        dwIndex+1, pPolicyInfo->pszPolicyIdentifier,
                        pwszQualifiers))
                goto FormatMsgError;

         }
         else
         {

            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_CERT_POLICY_NO_QUA_MULTI;
            else
                ids=IDS_CERT_POLICY_NO_QUA;

             if(!FormatMessageUnicode(&pwszPolicyFormat, ids,
                        dwIndex+1, pPolicyInfo->pszPolicyIdentifier))
                goto FormatMsgError;

         }

         //strcat
         pwsz=(LPWSTR)realloc(pwsz, 
             sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszPolicyFormat)+1));
         if(NULL==pwsz)
             goto MemoryError;

         wcscat(pwsz, pwszPolicyFormat);

         free(pwszQualifiers);
         pwszQualifiers=NULL;

         LocalFree((HLOCAL)pwszPolicyFormat);
         pwszPolicyFormat=NULL;
    }


    if(0==wcslen(pwsz))
    {
       //no data
        pwszFormat=(LPWSTR)malloc(sizeof(WCHAR)*(NO_INFO_SIZE+1));
        if(NULL==pwszFormat)
            goto MemoryError;

        if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, pwszFormat, NO_INFO_SIZE))
            goto LoadStringError;

    }
    else
    {
        pwszFormat=pwsz;
        pwsz=NULL;
    }

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:
    if(pwszOneQualifier)
        LocalFree((HLOCAL)pwszOneQualifier);

    if(pwszQualifierFormat)
        LocalFree((HLOCAL)pwszQualifierFormat);

    if(pwszQualifiers)
      free(pwszQualifiers);

    if(pwszPolicyFormat)
        LocalFree((HLOCAL)pwszPolicyFormat);

    if(pwsz)
        free(pwsz);

	if(pwszFormat)
		free(pwszFormat);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
SET_ERROR(MemoryError,E_OUTOFMEMORY);
TRACE_ERROR(FormatCertQualifierError);
}


//--------------------------------------------------------------------------
//
//	 FormatDistPointName:  Pre-condition: dwDistPointNameChoice!=0
//--------------------------------------------------------------------------
BOOL    FormatDistPointName(DWORD		            dwCertEncodingType,
	                        DWORD		            dwFormatType,
	                        DWORD		            dwFormatStrType,
	                        void		            *pFormatStruct,
                            PCRL_DIST_POINT_NAME    pInfo,
                            LPWSTR                  *ppwszFormat)
{
    BOOL            fResult=FALSE;
    DWORD           cbNeeded=0;
    LPWSTR          pwszCRLIssuer=NULL;
    UINT            ids=0;

    *ppwszFormat=NULL;

    if(CRL_DIST_POINT_FULL_NAME==pInfo->dwDistPointNameChoice)
    {
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
              ids=IDS_THREE_TABS;

        cbNeeded=0;
        if(!FormatAltNameInfo(dwCertEncodingType,
                                 dwFormatType,
                                 dwFormatStrType,
                                 pFormatStruct,
                                 ids,
                                 FALSE,
                                 &(pInfo->FullName),
                                 NULL,
                                 &cbNeeded))
                goto FormatAltNameError;

        pwszCRLIssuer=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszCRLIssuer)
            goto MemoryError;

         if(!FormatAltNameInfo(dwCertEncodingType,
                                 dwFormatType,
                                 dwFormatStrType,
                                 pFormatStruct,
                                 ids,
                                 FALSE,
                                 &(pInfo->FullName),
                                 pwszCRLIssuer,
                                 &cbNeeded))
              goto FormatAltNameError;

        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
              ids=IDS_CRL_DIST_FULL_NAME_MULTI;
        else
              ids=IDS_CRL_DIST_FULL_NAME;


         if(!FormatMessageUnicode(ppwszFormat, ids,pwszCRLIssuer))
             goto FormatMsgError;
    }
    else
    {
        if(CRL_DIST_POINT_ISSUER_RDN_NAME==pInfo->dwDistPointNameChoice)
        {
            *ppwszFormat=(LPWSTR)malloc(sizeof(WCHAR)*(CRL_DIST_NAME_SIZE+1));
            if(NULL==*ppwszFormat)
                goto MemoryError;

            if(!LoadStringU(hFrmtFuncInst, IDS_CRL_DIST_ISSUER_RDN,
                    *ppwszFormat,CRL_DIST_NAME_SIZE))
                goto LoadStringError;

        }
        else
        {
            if(!FormatMessageUnicode(ppwszFormat, IDS_DWORD,
                pInfo->dwDistPointNameChoice))
                goto FormatMsgError;
        }

    }
	fResult=TRUE;
	

CommonReturn:
    if(pwszCRLIssuer)
        free(pwszCRLIssuer);

	return fResult;

ErrorReturn:
    if(*ppwszFormat)
    {
        LocalFree((HLOCAL)(*ppwszFormat));
        *ppwszFormat=NULL;
    }

	fResult=FALSE;
	goto CommonReturn;


TRACE_ERROR(FormatMsgError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(LoadStringError);
TRACE_ERROR(FormatAltNameError);

}
//--------------------------------------------------------------------------
//
//	 FormatCRLReason:  Pre-condition: pReason.cbData != 0
//--------------------------------------------------------------------------
BOOL    FormatCRLReason(DWORD		    dwCertEncodingType,
	                    DWORD		    dwFormatType,
	                    DWORD		    dwFormatStrType,
	                    void		    *pFormatStruct,
	                    LPCSTR		    lpszStructType,
                        PCRYPT_BIT_BLOB pInfo,
                        LPWSTR          *ppwszFormat)
{
    LPWSTR                          pwszFormat=NULL;
    LPWSTR                          pwszByte=NULL;

    WCHAR                           wszReason[CRL_REASON_SIZE+1];
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
                                               				
		*ppwszFormat=NULL;

        pwszFormat=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwszFormat)
            goto MemoryError;

        *pwszFormat=L'\0';

        //format the 1st byte
        if(pInfo->pbData[0] & CRL_REASON_UNUSED_FLAG)
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_UNSPECIFIED, wszReason, CRL_REASON_SIZE))
		        goto LoadStringError;

            pwszFormat=(LPWSTR)realloc(pwszFormat, 
				sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszReason)+1+wcslen(wszCOMMA)));
            if(NULL==pwszFormat)
                goto MemoryError;

            wcscat(pwszFormat, wszReason);
            wcscat(pwszFormat, wszCOMMA);
        }

        if(pInfo->pbData[0] & CRL_REASON_KEY_COMPROMISE_FLAG)
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_KEY_COMPROMISE, wszReason,CRL_REASON_SIZE))
		        goto LoadStringError;

            pwszFormat=(LPWSTR)realloc(pwszFormat, 
				sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszReason)+1+wcslen(wszCOMMA)));
            if(NULL==pwszFormat)
                goto MemoryError;

            wcscat(pwszFormat, wszReason);
            wcscat(pwszFormat, wszCOMMA);
        }

        if(pInfo->pbData[0] & CRL_REASON_CA_COMPROMISE_FLAG )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_CA_COMPROMISE,wszReason, CRL_REASON_SIZE))
		        goto LoadStringError;

            pwszFormat=(LPWSTR)realloc(pwszFormat, 
				sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszReason)+1+wcslen(wszCOMMA)));
            if(NULL==pwszFormat)
                goto MemoryError;

            wcscat(pwszFormat, wszReason);
            wcscat(pwszFormat, wszCOMMA);
       }


        if(pInfo->pbData[0] & CRL_REASON_AFFILIATION_CHANGED_FLAG )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_AFFILIATION_CHANGED, wszReason, CRL_REASON_SIZE))
		        goto LoadStringError;

            pwszFormat=(LPWSTR)realloc(pwszFormat, 
				sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszReason)+1+wcslen(wszCOMMA)));
            if(NULL==pwszFormat)
                goto MemoryError;

            wcscat(pwszFormat, wszReason);
            wcscat(pwszFormat, wszCOMMA);
        }

        if(pInfo->pbData[0] & CRL_REASON_SUPERSEDED_FLAG )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_SUPERSEDED, wszReason, CRL_REASON_SIZE))
		        goto LoadStringError;

			pwszFormat=(LPWSTR)realloc(pwszFormat, 
				sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszReason)+1+wcslen(wszCOMMA)));
            if(NULL==pwszFormat)
                goto MemoryError;

            wcscat(pwszFormat, wszReason);
            wcscat(pwszFormat, wszCOMMA);
        }

        if(pInfo->pbData[0] & CRL_REASON_CESSATION_OF_OPERATION_FLAG )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_CESSATION_OF_OPERATION, wszReason, CRL_REASON_SIZE))
		        goto LoadStringError;

            pwszFormat=(LPWSTR)realloc(pwszFormat, 
				sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszReason)+1+wcslen(wszCOMMA)));
            if(NULL==pwszFormat)
                goto MemoryError;

            wcscat(pwszFormat, wszReason);
            wcscat(pwszFormat, wszCOMMA);
       }

         if(pInfo->pbData[0] & CRL_REASON_CERTIFICATE_HOLD_FLAG  )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_CERTIFICATE_HOLD, wszReason, CRL_REASON_SIZE))
		        goto LoadStringError;

            pwszFormat=(LPWSTR)realloc(pwszFormat, 
				sizeof(WCHAR) * (wcslen(pwszFormat)+wcslen(wszReason)+1+wcslen(wszCOMMA)));
            if(NULL==pwszFormat)
                goto MemoryError;

            wcscat(pwszFormat, wszReason);
            wcscat(pwszFormat, wszCOMMA);
        }

        if(0==wcslen(pwszFormat))
        {
           pwszFormat=(LPWSTR)realloc(pwszFormat, sizeof(WCHAR) * (UNKNOWN_CRL_REASON_SIZE+1));

           if(!LoadStringU(hFrmtFuncInst, IDS_UNKNOWN_CRL_REASON, pwszFormat,
               UNKNOWN_CRL_REASON_SIZE))
		            goto LoadStringError;
        }
        else
        {
            //get rid of the last comma
            *(pwszFormat+wcslen(pwszFormat)-wcslen(wszCOMMA))=L'\0';
        }

        //get the Hex dump of the Key Usage
       cbNeeded=0;

       if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        pInfo->pbData,
                        pInfo->cbData,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        pwszByte=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszByte)
            goto MemoryError;

        if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        pInfo->pbData,
                        pInfo->cbData,
                        pwszByte,
	                    &cbNeeded))
            goto FormatBytesToHexError;


    //convert the WSZ
    if(!FormatMessageUnicode(ppwszFormat, IDS_BIT_BLOB, pwszFormat,
        pwszByte))
        goto FormatMsgError;

	fResult=TRUE;
	

CommonReturn:
    if(pwszFormat)
        free(pwszFormat);

    if(pwszByte)
        free(pwszByte);

	return fResult;

ErrorReturn:
    if(*ppwszFormat)
    {
        LocalFree((HLOCAL)(*ppwszFormat));
        *ppwszFormat=NULL;
    }

	fResult=FALSE;
	goto CommonReturn;

TRACE_ERROR(LoadStringError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatBytesToHexError);
TRACE_ERROR(FormatMsgError);

}

//--------------------------------------------------------------------------
//
//	 FormatCRLDistPoints:   X509_CRL_DIST_POINTS
//                          szOID_CRL_DIST_POINTS
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatCRLDistPoints(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							    pwszFormat=NULL;
    LPWSTR                              pwsz=NULL;
    LPWSTR                              pwszEntryFormat=NULL;
    LPWSTR                              pwszEntryTagFormat=NULL;

    LPWSTR                              pwszPointName=NULL;
    LPWSTR                              pwszNameFormat=NULL;
    LPWSTR                              pwszCRLReason=NULL;
    LPWSTR                              pwszReasonFormat=NULL;
    LPWSTR                              pwszCRLIssuer=NULL;
    LPWSTR                              pwszIssuerFormat=NULL;

	PCRL_DIST_POINTS_INFO	        pInfo=NULL;

	DWORD							cbNeeded=0;
    DWORD                           dwIndex=0;
	BOOL							fResult=FALSE;
    HRESULT                         hr=S_OK;
    UINT                            ids=0;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_CRL_DIST_POINTS,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

    pwsz=(LPWSTR)malloc(sizeof(WCHAR));
    if(NULL==pwsz)
        goto MemoryError;
    *pwsz=L'\0';

    for(dwIndex=0; dwIndex<pInfo->cDistPoint; dwIndex++)
    {

        //format distribution name
        if(0!=pInfo->rgDistPoint[dwIndex].DistPointName.dwDistPointNameChoice)
        {
            if(!FormatDistPointName(
                    dwCertEncodingType,
                    dwFormatType,
                    dwFormatStrType,
                    pFormatStruct,
                    &(pInfo->rgDistPoint[dwIndex].DistPointName),
                    &pwszPointName))
                goto FormatDistPointNameError;

           //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_CRL_DIST_NAME_MULTI;
            else
                ids=IDS_CRL_DIST_NAME;


            if(!FormatMessageUnicode(&pwszNameFormat, ids,pwszPointName))
                goto FormatMsgError;
        }

        //format the CRL reason
        if(0!=pInfo->rgDistPoint[dwIndex].ReasonFlags.cbData)
        {
            if(!FormatCRLReason(dwCertEncodingType,
                                dwFormatType,
                                dwFormatStrType,
                                pFormatStruct,
                                lpszStructType,
                                &(pInfo->rgDistPoint[dwIndex].ReasonFlags),
                                &pwszCRLReason))
                goto FormatCRLReasonError;


            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_CRL_DIST_REASON_MULTI;
            else
                ids=IDS_CRL_DIST_REASON;

            if(!FormatMessageUnicode(&pwszReasonFormat, ids ,pwszCRLReason))
                goto FormatMsgError;

        }

        //format the Issuer
       if(0!=pInfo->rgDistPoint[dwIndex].CRLIssuer.cAltEntry)
       {
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_TWO_TABS;
            else
                ids=0;


            cbNeeded=0;
            if(!FormatAltNameInfo(dwCertEncodingType,
                                 dwFormatType,
                                 dwFormatStrType,
                                 pFormatStruct,
                                 ids,
                                 FALSE,
                                 &(pInfo->rgDistPoint[dwIndex].CRLIssuer),
                                 NULL,
                                 &cbNeeded))
                goto FormatAltNameError;

           pwszCRLIssuer=(LPWSTR)malloc(cbNeeded);
           if(NULL==pwszCRLIssuer)
               goto MemoryError;

            if(!FormatAltNameInfo(dwCertEncodingType,
                                 dwFormatType,
                                 dwFormatStrType,
                                 pFormatStruct,
                                 ids,
                                 FALSE,
                                 &(pInfo->rgDistPoint[dwIndex].CRLIssuer),
                                 pwszCRLIssuer,
                                 &cbNeeded))
                goto FormatAltNameError;

            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_CRL_DIST_ISSUER_MULTI;
            else
                ids=IDS_CRL_DIST_ISSUER;

            if(!FormatMessageUnicode(&pwszIssuerFormat,ids,pwszCRLIssuer))
                goto FormatMsgError;
       }

       cbNeeded=0;

       if(pwszNameFormat)
           cbNeeded+=wcslen(pwszNameFormat);

       if(pwszReasonFormat)
           cbNeeded+=wcslen(pwszReasonFormat);

       if(pwszIssuerFormat)
           cbNeeded+=wcslen(pwszIssuerFormat);

       if(0!=cbNeeded)
       {

            //add ", " between each element for single line format
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
            {
                if(0!=wcslen(pwsz))
                    wcscat(pwsz, wszCOMMA);
            }

            //strcat all the information, including the COMMA
            cbNeeded += wcslen(wszCOMMA)*2;

            pwszEntryFormat=(LPWSTR)malloc(sizeof(WCHAR) * (cbNeeded+1));
            if(NULL==pwszEntryFormat)
                goto MemoryError;

            *pwszEntryFormat=L'\0';

            //strcat all three fields one at a time
            if(pwszNameFormat)
                wcscat(pwszEntryFormat, pwszNameFormat);

            if(pwszReasonFormat)
            {
                if(0!=wcslen(pwszEntryFormat))
                {
                    if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                        wcscat(pwszEntryFormat, wszCOMMA);
                }

                wcscat(pwszEntryFormat, pwszReasonFormat);
            }

            if(pwszIssuerFormat)
            {
                if(0!=wcslen(pwszEntryFormat))
                {
                    if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                        wcscat(pwszEntryFormat, wszCOMMA);
                }

                wcscat(pwszEntryFormat, pwszIssuerFormat);
            }

            //format the entry
            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_CRL_DIST_ENTRY_MULTI;
            else
                ids=IDS_CRL_DIST_ENTRY;

            if(!FormatMessageUnicode(&pwszEntryTagFormat, ids, dwIndex+1,
                pwszEntryFormat))
                goto FormatMsgError;

            //strcat the entry
            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszEntryTagFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, pwszEntryTagFormat);

            //free memory
            free(pwszEntryFormat);
            pwszEntryFormat=NULL;

            LocalFree(pwszEntryTagFormat);
            pwszEntryTagFormat=NULL;
       }

       //free memory
       if(pwszPointName)
       {
           LocalFree((HLOCAL)pwszPointName);
           pwszPointName=NULL;
       }

       if(pwszCRLReason)
       {
           LocalFree((HLOCAL)(pwszCRLReason));
           pwszCRLReason=NULL;
       }

       if(pwszCRLIssuer)
       {
           free(pwszCRLIssuer);
           pwszCRLIssuer=NULL;
       }

       if(pwszNameFormat)
       {
            LocalFree((HLOCAL)pwszNameFormat);
            pwszNameFormat=NULL;
       }

       if(pwszReasonFormat)
       {
            LocalFree((HLOCAL)pwszReasonFormat);
            pwszReasonFormat=NULL;
       }

       if(pwszIssuerFormat)
       {
            LocalFree((HLOCAL)pwszIssuerFormat);
            pwszIssuerFormat=NULL;
       }
    }

    if(0==wcslen(pwsz))
    {
       //no data
        pwszFormat=(LPWSTR)malloc(sizeof(WCHAR)*(NO_INFO_SIZE+1));
        if(NULL==pwszFormat)
            goto MemoryError;

        if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, pwszFormat, NO_INFO_SIZE))
            goto LoadStringError;

    }
    else
    {
        pwszFormat=pwsz;
        pwsz=NULL;

    }

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:
    if(pwszEntryFormat)
      free(pwszEntryFormat);

    if(pwszEntryTagFormat)
      LocalFree((HLOCAL)pwszEntryTagFormat);

    //free memory
    if(pwszPointName)
       LocalFree((HLOCAL)pwszPointName);

    if(pwszCRLReason)
       LocalFree((HLOCAL)(pwszCRLReason));

    if(pwszCRLIssuer)
       free(pwszCRLIssuer);

    if(pwszNameFormat)
        LocalFree((HLOCAL)pwszNameFormat);

    if(pwszReasonFormat)
        LocalFree((HLOCAL)pwszReasonFormat);

    if(pwszIssuerFormat)
        LocalFree((HLOCAL)pwszIssuerFormat);

    if(pwsz)
        free(pwsz);

	if(pwszFormat)
		free(pwszFormat);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatDistPointNameError);
TRACE_ERROR(FormatCRLReasonError);
TRACE_ERROR(FormatAltNameError);

}

//--------------------------------------------------------------------------
//
//	FormatCertPolicyID:
//
//      Pre-condition: pCertPolicyID has to include the valid information.that is,
//      cCertPolicyElementId can not be 0.
//--------------------------------------------------------------------------
BOOL FormatCertPolicyID(PCERT_POLICY_ID pCertPolicyID, LPWSTR  *ppwszFormat)
{

    BOOL        fResult=FALSE;
    LPSTR       pszFormat=NULL;
    DWORD       dwIndex=0;
    HRESULT     hr=S_OK;

    *ppwszFormat=NULL;

    if(0==pCertPolicyID->cCertPolicyElementId)
        goto InvalidArg;

    pszFormat=(LPSTR)malloc(sizeof(CHAR));
    if(NULL==pszFormat)
        goto MemoryError;

    *pszFormat='\0';


    for(dwIndex=0; dwIndex<pCertPolicyID->cCertPolicyElementId; dwIndex++)
    {

        pszFormat=(LPSTR)realloc(pszFormat, strlen(pszFormat)+
                strlen(pCertPolicyID->rgpszCertPolicyElementId[dwIndex])+strlen(strCOMMA)+1);
        if(NULL==pszFormat)
            goto MemoryError;

        strcat(pszFormat,pCertPolicyID->rgpszCertPolicyElementId[dwIndex]);

        strcat(pszFormat, strCOMMA);
    }

    //get rid of the last COMMA
    *(pszFormat+strlen(pszFormat)-strlen(strCOMMA))='\0';

    //convert to WCHAR
    if(S_OK!=(hr=SZtoWSZ(pszFormat, ppwszFormat)))
        goto SZtoWSZError;

	fResult=TRUE;

CommonReturn:

    if(pszFormat)
        free(pszFormat);

	return fResult;

ErrorReturn:
    if(*ppwszFormat)
    {
        free(*ppwszFormat);
        *ppwszFormat=NULL;
    }

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
SET_ERROR_VAR(SZtoWSZError,hr);
}

//--------------------------------------------------------------------------
//
//	 FormatKeyRestriction:   X509_KEY_USAGE_RESTRICTION
//                           szOID_KEY_USAGE_RESTRICTION
//
//
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatKeyRestriction(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							    pwszFormat=NULL;
    LPWSTR                              pwsz=NULL;
	PCERT_KEY_USAGE_RESTRICTION_INFO	pInfo=NULL;
    LPWSTR                              pwszPolicy=NULL;
    LPWSTR                              pwszPolicyFormat=NULL;
    LPWSTR                              pwszKeyUsage=NULL;
    LPWSTR                              pwszKeyUsageFormat=NULL;



	DWORD							    cbNeeded=0;
    DWORD                               dwIndex=0;
	BOOL							    fResult=FALSE;
    HRESULT                             hr=S_OK;
    UINT                                ids=0;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_KEY_USAGE_RESTRICTION,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

    pwsz=(LPWSTR)malloc(sizeof(WCHAR));
    if(NULL==pwsz)
        goto MemoryError;

    *pwsz=L'\0';

    for(dwIndex=0; dwIndex<pInfo->cCertPolicyId; dwIndex++)
    {

       if(0!=((pInfo->rgCertPolicyId)[dwIndex].cCertPolicyElementId))
       {
            //concatecate the comma if not the 1st item
            if(0!=wcslen(pwsz))
            {
                if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                    wcscat(pwsz, wszCOMMA);
            }

            if(!FormatCertPolicyID(&((pInfo->rgCertPolicyId)[dwIndex]), &pwszPolicy))
                goto FormatCertPolicyIDError;

            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_KEY_RES_ID_MULTI;
            else
                ids=IDS_KEY_RES_ID;

            if(!FormatMessageUnicode(&pwszPolicyFormat, ids,dwIndex+1,pwszPolicy))
                goto FormatMsgError;

            //allocate memory, including the ", "
            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszPolicyFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, pwszPolicyFormat);


            free(pwszPolicy);
            pwszPolicy=NULL;

            LocalFree((HLOCAL)pwszPolicyFormat);
            pwszPolicyFormat=NULL;
       }
    }

    //format the RestrictedKeyUsage
    if(0!=pInfo->RestrictedKeyUsage.cbData)
    {
       //concatecate the comma if not the 1st item
        if(0!=wcslen(pwsz))
        {
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                wcscat(pwsz, wszCOMMA);
        }


        cbNeeded=0;

        if(!FormatKeyUsageBLOB(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        &(pInfo->RestrictedKeyUsage),
                        NULL,
	                    &cbNeeded))
             goto FormatKeyUsageBLOBError;

        pwszKeyUsage=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszKeyUsage)
               goto MemoryError;

       if(!FormatKeyUsageBLOB(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        &(pInfo->RestrictedKeyUsage),
                        pwszKeyUsage,
	                    &cbNeeded))
              goto FormatKeyUsageBLOBError;

      //decide between single line and mulitple line format
      if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_KEY_RES_USAGE_MULTI;
       else
                ids=IDS_KEY_RES_USAGE;

        //format the element string
        if(!FormatMessageUnicode(&pwszKeyUsageFormat, ids, pwszKeyUsage))
            goto FormatMsgError;

        pwsz=(LPWSTR)realloc(pwsz, 
            sizeof(WCHAR) * (wcslen(pwsz)+wcslen(pwszKeyUsageFormat)+1));
        if(NULL==pwsz)
            goto MemoryError;

        wcscat(pwsz, pwszKeyUsageFormat);
    }

    if(0==wcslen(pwsz))
    {
       //no data
        pwszFormat=(LPWSTR)malloc(sizeof(WCHAR)*(NO_INFO_SIZE+1));
        if(NULL==pwszFormat)
            goto MemoryError;

        if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, pwszFormat, NO_INFO_SIZE))
            goto LoadStringError;

    }
    else
    {
        pwszFormat=pwsz;
        pwsz=NULL;
    }

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:
    if(pwszPolicy)
        free(pwszPolicy);

    if(pwszPolicyFormat)
        LocalFree((HLOCAL)pwszPolicyFormat);

    if(pwszKeyUsage)
        free(pwszKeyUsage);

    if(pwszKeyUsageFormat)
        LocalFree((HLOCAL)pwszKeyUsageFormat);

    if(pwszFormat)
		free(pwszFormat);

    if(pwsz)
        free(pwsz);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatCertPolicyIDError);
TRACE_ERROR(FormatKeyUsageBLOBError);

}

//-----------------------------------------------------------------------
//
//	 FormatFileTime
//
//   Pre-condition: pFileTime points to valid data
//
//------------------------------------------------------------------------
BOOL	FormatFileTime(FILETIME *pFileTime,LPWSTR   *ppwszFormat)
{
	SYSTEMTIME		SysTime;
	FILETIME		LocalFileTime;
	BOOL			fResult=FALSE;
    WCHAR           wszDay[DAY_SIZE];
    WCHAR           wszMonth[MONTH_SIZE];
    UINT            idsDay=0;
    UINT            idsMonth=0;

    *ppwszFormat=NULL;


	//now we format FileTime to SysTime as default.
	if(FileTimeToLocalFileTime(pFileTime, &LocalFileTime)
		&& FileTimeToSystemTime(&LocalFileTime,&SysTime)
	   )
	{
        //Sunday is 0
        idsDay=IDS_SUNDAY+SysTime.wDayOfWeek;
        //January is 1
        idsMonth=IDS_JAN+SysTime.wMonth-1;

        //load the string
        if(!LoadStringU(hFrmtFuncInst,idsDay, wszDay, sizeof(wszDay)/sizeof(wszDay[0])))
            goto LoadStringError;

        if(!LoadStringU(hFrmtFuncInst,idsMonth, wszMonth,
                    sizeof(wszMonth)/sizeof(wszMonth[0])))
            goto LoadStringError;

        //"%d:%d:%d  %s  %s %d, %d"
		if(!FormatMessageUnicode(ppwszFormat, IDS_FILE_TIME,
			 SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			 wszDay, wszMonth,
			 SysTime.wDay, SysTime.wYear))
             goto FormatMsgError;

	}
	else
	{
	  	//if failed, pFileTime is more than 0x8000000000000000.
		// all we can do is to print out the integer
        //"HighDateTime: %d LowDateTime: %d"
        if(!FormatMessageUnicode(ppwszFormat, IDS_FILE_TIME_DWORD,
			pFileTime->dwHighDateTime, pFileTime->dwLowDateTime))
            goto FormatMsgError;

	}



	fResult=TRUE;

CommonReturn:

	return fResult;

ErrorReturn:
    if(*ppwszFormat)
    {
        LocalFree((HLOCAL)(*ppwszFormat));
        *ppwszFormat=NULL;
    }

	fResult=FALSE;
	goto CommonReturn;

TRACE_ERROR(FormatMsgError);
TRACE_ERROR(LoadStringError);

}




//--------------------------------------------------------------------------
//
//	 FormatKeyAttributes:   X509_KEY_ATTRIBUTES
//                          szOID_KEY_ATTRIBUTES
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatKeyAttributes(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{

    LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwsz=NULL;

    LPWSTR                          pwszKeyIDFormat=NULL;
    LPWSTR                          pwszKeyID=NULL;

    LPWSTR                          pwszKeyUsageFormat=NULL;
    LPWSTR                          pwszKeyUsage=NULL;

    LPWSTR                          pwszKeyBeforeFormat=NULL;
    LPWSTR                          pwszKeyBefore=NULL;

    LPWSTR                          pwszKeyAfterFormat=NULL;
    LPWSTR                          pwszKeyAfter=NULL;
	PCERT_KEY_ATTRIBUTES_INFO   	pInfo=NULL;


	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    HRESULT                         hr=S_OK;
    UINT                            ids=0;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_KEY_ATTRIBUTES,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

    pwsz=(LPWSTR)malloc(sizeof(WCHAR));
    if(NULL==pwsz)
        goto MemoryError;

    *pwsz=L'\0';


    if(0!=pInfo->KeyId.cbData)
    {
        cbNeeded=0;

        if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        pInfo->KeyId.pbData,
                        pInfo->KeyId.cbData,
                        NULL,
	                    &cbNeeded))
             goto FormatBytesToHexError;

        pwszKeyID=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszKeyID)
               goto MemoryError;

       if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        pInfo->KeyId.pbData,
                        pInfo->KeyId.cbData,
                        pwszKeyID,
	                    &cbNeeded))
              goto FormatBytesToHexError;


        //format the element string

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_KEY_ATTR_ID_MULTI;
        else
            ids=IDS_KEY_ATTR_ID;

        if(!FormatMessageUnicode(&pwszKeyIDFormat, ids, pwszKeyID))
            goto FormatMsgError;

        pwsz=(LPWSTR)realloc(pwsz, 
            sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszKeyIDFormat)+1));
        if(NULL==pwsz)
            goto MemoryError;

        wcscat(pwsz, pwszKeyIDFormat);
    }


    //check the no data situation
    if(0!=pInfo->IntendedKeyUsage.cbData)
    {
        //strcat a ", " symbol for signle line format
       if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
        {
            if(0!=wcslen(pwsz))
                wcscat(pwsz, wszCOMMA);
        }


        cbNeeded=0;

        if(!FormatKeyUsageBLOB(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        &(pInfo->IntendedKeyUsage),
                        NULL,
	                    &cbNeeded))
             goto FormatKeyUsageBLOBError;

        pwszKeyUsage=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszKeyUsage)
               goto MemoryError;

       if(!FormatKeyUsageBLOB(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        &(pInfo->IntendedKeyUsage),
                        pwszKeyUsage,
	                    &cbNeeded))
              goto FormatKeyUsageBLOBError;


        //format the element string

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            ids=IDS_KEY_ATTR_USAGE_MULTI;
        else
            ids=IDS_KEY_ATTR_USAGE;

        if(!FormatMessageUnicode(&pwszKeyUsageFormat, ids, pwszKeyUsage))
            goto FormatMsgError;

        pwsz=(LPWSTR)realloc(pwsz, 
            sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszKeyUsageFormat)+1));
        if(NULL==pwsz)
            goto MemoryError;

        wcscat(pwsz, pwszKeyUsageFormat);

    }

    if(NULL!=pInfo->pPrivateKeyUsagePeriod)
    {
        //format only if there is some information
        if(!((0==pInfo->pPrivateKeyUsagePeriod->NotBefore.dwHighDateTime)
           &&(0==pInfo->pPrivateKeyUsagePeriod->NotBefore.dwLowDateTime)))
        {
            //strcat a ", " symbol for signle line format
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
            {
                if(0!=wcslen(pwsz))
                    wcscat(pwsz, wszCOMMA);
            }


            if(!FormatFileTime(&(pInfo->pPrivateKeyUsagePeriod->NotBefore),
                            &pwszKeyBefore))
                goto FormatFileTimeError;


            //format the element string

            //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_KEY_ATTR_BEFORE_MULTI;
            else
                ids=IDS_KEY_ATTR_BEFORE;

            if(!FormatMessageUnicode(&pwszKeyBeforeFormat, ids,
                    pwszKeyBefore))
                goto FormatMsgError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR)*(wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszKeyBeforeFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, pwszKeyBeforeFormat);
        }

        if(!((0==pInfo->pPrivateKeyUsagePeriod->NotAfter.dwHighDateTime)
           &&(0==pInfo->pPrivateKeyUsagePeriod->NotAfter.dwLowDateTime)))
        {

            //strcat a ", " symbol for signle line format
            if(0== (dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
            {
                if(0!=wcslen(pwsz))
                    wcscat(pwsz, wszCOMMA);
            }


            if(!FormatFileTime(&(pInfo->pPrivateKeyUsagePeriod->NotAfter),
                            &pwszKeyAfter))
                goto FormatFileTimeError;

            //format the element string

           //decide between single line and mulitple line format
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_KEY_ATTR_AFTER_MULTI;
            else
                ids=IDS_KEY_ATTR_AFTER;

            if(!FormatMessageUnicode(&pwszKeyAfterFormat, ids,
                    pwszKeyAfter))
                goto FormatMsgError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszKeyAfterFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, pwszKeyAfterFormat);

        }

    }

    if(0==wcslen(pwsz))
    {
       pwszFormat=(LPWSTR)malloc(sizeof(WCHAR)*(NO_INFO_SIZE+1));
       if(NULL==pwszFormat)
           goto MemoryError;

       if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, pwszFormat,NO_INFO_SIZE))
           goto LoadStringError;

    }
    else
    {
        pwszFormat=pwsz;
        pwsz=NULL;

    }

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:

    if(pwszKeyIDFormat)
        LocalFree((HLOCAL)pwszKeyIDFormat);

    if(pwszKeyID)
        free(pwszKeyID);

    if(pwszKeyUsageFormat)
        LocalFree((HLOCAL)pwszKeyUsageFormat);

    if(pwszKeyUsage)
        free(pwszKeyUsage);

    if(pwszKeyBeforeFormat)
        LocalFree((HLOCAL)pwszKeyBeforeFormat);

    if(pwszKeyBefore)
        LocalFree((HLOCAL)pwszKeyBefore);

    if(pwszKeyAfterFormat)
        LocalFree((HLOCAL)pwszKeyAfterFormat);

    if(pwszKeyAfter)
        LocalFree((HLOCAL)pwszKeyAfter);

	if(pwszFormat)
		free(pwszFormat);

    if(pwsz)
        free(pwsz);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatKeyUsageBLOBError);
TRACE_ERROR(FormatFileTimeError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatBytesToHexError);
TRACE_ERROR(FormatMsgError);
}

//--------------------------------------------------------------------------
//
//	 FormatAuthortiyInfoAccess:   X509_AUTHORITY_INFO_ACCESS
//                                szOID_AUTHORITY_INFO_ACCESS
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatAuthortiyInfoAccess(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
    BOOL                            fMethodAllocated=FALSE;
    WCHAR                           wszNoInfo[NO_INFO_SIZE];
    WCHAR                           wszUnknownAccess[UNKNOWN_ACCESS_METHOD_SIZE];
    PCCRYPT_OID_INFO                pOIDInfo=NULL;
    CERT_ALT_NAME_INFO              CertAltNameInfo;


	LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwsz=NULL;
    LPWSTR                          pwszMethod=NULL;
    LPWSTR                          pwszAltName=NULL;
    LPWSTR                          pwszEntryFormat=NULL;
	PCERT_AUTHORITY_INFO_ACCESS	    pInfo=NULL;

    DWORD                           dwIndex=0;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    HRESULT                         hr=S_OK;
    UINT                            ids=0;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_AUTHORITY_INFO_ACCESS,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;


    if(0==pInfo->cAccDescr)
    {
        //load the string "Info Not Available"
	    if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, wszNoInfo, sizeof(wszNoInfo)/sizeof(wszNoInfo[0])))
		    goto LoadStringError;

        pwszFormat=wszNoInfo;
    }
    else
    {
        pwsz=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwsz)
            goto MemoryError;

        *pwsz=L'\0';

        //load the string "Unknown Access Method:
	    if(!LoadStringU(hFrmtFuncInst,IDS_UNKNOWN_ACCESS_METHOD, wszUnknownAccess,
            sizeof(wszUnknownAccess)/sizeof(wszUnknownAccess[0])))
		    goto LoadStringError;

        for(dwIndex=0; dwIndex < pInfo->cAccDescr; dwIndex++)
        {
            fMethodAllocated=FALSE;

            //need a ", " between each element for single line format
            if(0!=wcslen(pwsz))
            {
                if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE) )
                    wcscat(pwsz, wszCOMMA);
            }

            //get the name of the access method
            if(pInfo->rgAccDescr[dwIndex].pszAccessMethod)
            {

                pOIDInfo=CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY,
									 (void *)(pInfo->rgAccDescr[dwIndex].pszAccessMethod),
									  CRYPT_EXT_OR_ATTR_OID_GROUP_ID);

                //get the access method OID
                if(pOIDInfo)
			    {
				    //allocate memory, including the NULL terminator
				    pwszMethod=(LPWSTR)malloc((wcslen(pOIDInfo->pwszName)+1)*
				    					sizeof(WCHAR));

				    if(NULL==pwszMethod)
					    goto MemoryError;

                    fMethodAllocated=TRUE;

				    wcscpy(pwszMethod,pOIDInfo->pwszName);

			    }else
                    pwszMethod=wszUnknownAccess;
            }

            memset(&CertAltNameInfo, 0, sizeof(CERT_ALT_NAME_INFO));
            CertAltNameInfo.cAltEntry=1;
            CertAltNameInfo.rgAltEntry=&(pInfo->rgAccDescr[dwIndex].AccessLocation);

            //need to tell if it is for multi line format.  We need two \t\t
            //in front of each alt name entry
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_TWO_TABS;
            else
                ids=0;

            //get the alternative name entry
            cbNeeded=0;
            if(!FormatAltNameInfo(dwCertEncodingType,
                                 dwFormatType,
                                 dwFormatStrType,
                                 pFormatStruct,
                                 ids,
                                 FALSE,
                                 &CertAltNameInfo,
                                 NULL,
                                 &cbNeeded))
                goto FormatAltNameError;

           pwszAltName=(LPWSTR)malloc(cbNeeded);
           if(NULL==pwszAltName)
               goto MemoryError;

            if(!FormatAltNameInfo(dwCertEncodingType,
                                 dwFormatType,
                                 dwFormatStrType,
                                 pFormatStruct,
                                 ids,
                                 FALSE,
                                 &CertAltNameInfo,
                                 pwszAltName,
                                 &cbNeeded))
                goto FormatAltNameError;

            //format the entry
            if(pInfo->rgAccDescr[dwIndex].pszAccessMethod)
            {

                //decide between single line and mulitple line format
                if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                    ids=IDS_AUTHORITY_ACCESS_INFO_MULTI;
                else
                    ids=IDS_AUTHORITY_ACCESS_INFO;


                if(!FormatMessageUnicode(&pwszEntryFormat, ids,
                    dwIndex+1, pwszMethod, pInfo->rgAccDescr[dwIndex].pszAccessMethod,
                    pwszAltName))
                    goto FormatMsgError;
            }
            else
            {
                //decide between single line and mulitple line format
                if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                    ids=IDS_AUTHORITY_ACCESS_NO_METHOD_MULTI;
                else
                    ids=IDS_AUTHORITY_ACCESS_NO_METHOD;


                if(!FormatMessageUnicode(&pwszEntryFormat, ids, dwIndex+1, pwszAltName))
                    goto FormatMsgError;

            }

            //reallocat the memory.  Leave space for szComma
            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(pwszEntryFormat)+
                                        wcslen(wszCOMMA)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, pwszEntryFormat);

            //free memory
            LocalFree((HLOCAL)pwszEntryFormat);
            pwszEntryFormat=NULL;

            free(pwszAltName);
            pwszAltName=NULL;

            if(TRUE==fMethodAllocated)
                free(pwszMethod);

            pwszMethod=NULL;

        }

        //convert to WCHAR
        pwszFormat=pwsz;
    }


	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:

    if(pwsz)
        free(pwsz);

    if(pwszEntryFormat)
         LocalFree((HLOCAL)pwszEntryFormat);

    if(pwszAltName)
        free(pwszAltName);

    if(fMethodAllocated)
    {
        if(pwszMethod)
             free(pwszMethod);
    }

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
TRACE_ERROR(FormatAltNameError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);

}

//--------------------------------------------------------------------------
//
//	 FormatKeyUsageBLOB
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatKeyUsageBLOB(
	DWORD		    dwCertEncodingType,
	DWORD		    dwFormatType,
	DWORD		    dwFormatStrType,
	void		    *pFormatStruct,
	LPCSTR		    lpszStructType,
    PCRYPT_BIT_BLOB	pInfo,
	void	        *pbFormat,
	DWORD	        *pcbFormat)
{
   	LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwsz=NULL;
    LPWSTR                          pwszByte=NULL;

    WCHAR                           wszKeyUsage[KEY_USAGE_SIZE+1];
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;


        pwsz=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwsz)
            goto MemoryError;

        *pwsz=L'\0';

        //format the 1st byte
        if(pInfo->pbData[0] & CERT_DIGITAL_SIGNATURE_KEY_USAGE)
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_DIG_SIG, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
        }

        if(pInfo->pbData[0] & CERT_NON_REPUDIATION_KEY_USAGE)
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_NON_REPUDIATION, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
        }

        if(pInfo->pbData[0] & CERT_KEY_ENCIPHERMENT_KEY_USAGE )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_KEY_ENCIPHERMENT, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
       }


        if(pInfo->pbData[0] & CERT_DATA_ENCIPHERMENT_KEY_USAGE )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_DATA_ENCIPHERMENT, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
        }

        if(pInfo->pbData[0] & CERT_KEY_AGREEMENT_KEY_USAGE )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_KEY_AGREEMENT, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
        }

        if(pInfo->pbData[0] & CERT_KEY_CERT_SIGN_KEY_USAGE )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_CERT_SIGN, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
       }

         if(pInfo->pbData[0] & CERT_OFFLINE_CRL_SIGN_KEY_USAGE )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_OFFLINE_CRL_SIGN, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
        }

        if(pInfo->pbData[0] & CERT_CRL_SIGN_KEY_USAGE )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_CRL_SIGN, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
       }

        if(pInfo->pbData[0] & CERT_ENCIPHER_ONLY_KEY_USAGE  )
        {
            if(!LoadStringU(hFrmtFuncInst, IDS_ENCIPHER_ONLY, wszKeyUsage, KEY_USAGE_SIZE))
		        goto LoadStringError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz, wszKeyUsage);
            wcscat(pwsz, wszCOMMA);
        }

        //deal with the second byte
        if(pInfo->cbData>=2)
        {

            if(pInfo->pbData[1] & CERT_DECIPHER_ONLY_KEY_USAGE  )
            {
                if(!LoadStringU(hFrmtFuncInst, IDS_DECIPHER_ONLY, wszKeyUsage, KEY_USAGE_SIZE))
		            goto LoadStringError;

                pwsz=(LPWSTR)realloc(pwsz, 
                    sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszKeyUsage)+1+wcslen(wszCOMMA)));
                if(NULL==pwsz)
                    goto MemoryError;

                wcscat(pwsz, wszKeyUsage);
                wcscat(pwsz, wszCOMMA);
            }
        }

        if(0==wcslen(pwsz))
        {
           pwsz=(LPWSTR)realloc(pwsz, sizeof(WCHAR) * (UNKNOWN_KEY_USAGE_SIZE+1));

           if(!LoadStringU(hFrmtFuncInst, IDS_UNKNOWN_KEY_USAGE, pwsz,
               UNKNOWN_KEY_USAGE_SIZE))
		            goto LoadStringError;
        }
        else
        {
            //get rid of the last comma
            *(pwsz+wcslen(pwsz)-wcslen(wszCOMMA))=L'\0';
        }

        //get the Hex dump of the Key Usage
       cbNeeded=0;

       if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        pInfo->pbData,
                        pInfo->cbData,
                        NULL,
	                    &cbNeeded))
            goto FormatBytesToHexError;

        pwszByte=(LPWSTR)malloc(cbNeeded);
        if(NULL==pwszByte)
            goto MemoryError;

        if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        pInfo->pbData,
                        pInfo->cbData,
                        pwszByte,
	                    &cbNeeded))
            goto FormatBytesToHexError;


    //convert the WSZ
    if(!FormatMessageUnicode(&pwszFormat, IDS_BIT_BLOB, pwsz,
        pwszByte))
        goto FormatMsgError;

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:

    if(pwszFormat)
        LocalFree((HLOCAL)pwszFormat);

    if(pwsz)
        free(pwsz);

    if(pwszByte)
        free(pwszByte);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatBytesToHexError);
TRACE_ERROR(FormatMsgError);

}
//--------------------------------------------------------------------------
//
//	 FormatKeyUsage:  X509_KEY_USAGE
//                    szOID_KEY_USAGE
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatKeyUsage(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
    WCHAR                           wszNoInfo[NO_INFO_SIZE];
	PCRYPT_BIT_BLOB	                pInfo=NULL;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_KEY_USAGE,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

   //load the string "Info Not Available"
	if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, wszNoInfo, sizeof(wszNoInfo)/sizeof(wszNoInfo[0])))
		 goto LoadStringError;

    //check the no data situation
    if(0==pInfo->cbData)
        pwszFormat=wszNoInfo;
    else
    {
        if(1==pInfo->cbData)
        {
           if(0==pInfo->pbData[0])
                pwszFormat=wszNoInfo;
        }
        else
        {
            if(2==pInfo->cbData)
            {
                if((0==pInfo->pbData[0])&&(0==pInfo->pbData[1]))
                    pwszFormat=wszNoInfo;
            }
        }
    }

    if(NULL==pwszFormat)
    {

        fResult=FormatKeyUsageBLOB(dwCertEncodingType,
                                   dwFormatType,
                                   dwFormatStrType,
                                   pFormatStruct,
                                   lpszStructType,
                                   pInfo,
                                   pbFormat,
                                   pcbFormat);

        if(FALSE==fResult)
            goto FormatKeyUsageBLOBError;
    }
    else
    {
       	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	    //length only calculation
	    if(NULL==pbFormat)
	    {
		    *pcbFormat=cbNeeded;
		    fResult=TRUE;
		    goto CommonReturn;
    	}


	    if((*pcbFormat)<cbNeeded)
        {
            *pcbFormat=cbNeeded;
		    goto MoreDataError;
        }

	    //copy the data
	    memcpy(pbFormat, pwszFormat, cbNeeded);

	    //copy the size
	    *pcbFormat=cbNeeded;

	    fResult=TRUE;
    }


CommonReturn:
   	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatKeyUsageBLOBError);
}


//--------------------------------------------------------------------------
//
//	 FormatSMIMECapabilities:   PKCS_SMIME_CAPABILITIES
//                              szOID_RSA_SMIMECapabilities
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatSMIMECapabilities(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwsz=NULL;
    LPWSTR                          pwszElementFormat=NULL;
    LPWSTR                          pwszParam=NULL;


	WCHAR							wszNoInfo[NO_INFO_SIZE];
    BOOL                            fParamAllocated=FALSE;
	PCRYPT_SMIME_CAPABILITIES	    pInfo=NULL;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    DWORD                           dwIndex =0;
    HRESULT                         hr=S_OK;
    UINT                            idsSub=0;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,PKCS_SMIME_CAPABILITIES,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

	//check to see if information if available
    if(0==pInfo->cCapability)
    {
         //load the string "Info Not Available"
	    if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, wszNoInfo, sizeof(wszNoInfo)/sizeof(wszNoInfo[0])))
		    goto LoadStringError;

        pwszFormat=wszNoInfo;
    }
    else
    {
        pwsz=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwsz)
            goto MemoryError;

        *pwsz=L'\0';

        for(dwIndex=0; dwIndex < pInfo->cCapability; dwIndex++)
        {
            fParamAllocated=FALSE;

           //strcat ", " if single line.  No need for multi-line
            if(0!=wcslen(pwsz))
            {
                if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                 wcscat(pwsz, wszCOMMA);
            }


            if(0!=(pInfo->rgCapability)[dwIndex].Parameters.cbData)
            {
                cbNeeded=0;

                if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        (pInfo->rgCapability)[dwIndex].Parameters.pbData,
                        (pInfo->rgCapability)[dwIndex].Parameters.cbData,
                        NULL,
	                    &cbNeeded))
                        goto FormatBytesToHexError;

                pwszParam=(LPWSTR)malloc(cbNeeded);
                if(NULL==pwszParam)
                    goto MemoryError;

                fParamAllocated=TRUE;

                if(!FormatBytesToHex(
                        dwCertEncodingType,
                        dwFormatType,
                        dwFormatStrType,
                        pFormatStruct,
                        lpszStructType,
                        (pInfo->rgCapability)[dwIndex].Parameters.pbData,
                        (pInfo->rgCapability)[dwIndex].Parameters.cbData,
                        pwszParam,
	                    &cbNeeded))
                        goto FormatBytesToHexError;

                //decide between single line and mulitple line format
                if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                    idsSub=IDS_MIME_CAPABILITY_MULTI;
                else
                    idsSub=IDS_MIME_CAPABILITY;

                 //format the element string
                if(!FormatMessageUnicode(&pwszElementFormat, idsSub,
                        dwIndex+1,
                        (pInfo->rgCapability)[dwIndex].pszObjId,
                        pwszParam))
                    goto FormatMsgError;
            }
            else
            {
                //decide between single line and mulitple line format
                if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                    idsSub=IDS_MIME_CAPABILITY_NO_PARAM_MULTI;
                else
                    idsSub=IDS_MIME_CAPABILITY_NO_PARAM;

                 //format the element string
                if(!FormatMessageUnicode(&pwszElementFormat, idsSub,
                        dwIndex+1,
                        (pInfo->rgCapability)[dwIndex].pszObjId))
                    goto FormatMsgError;
            }

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszElementFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            //strcat the element
            wcscat(pwsz, pwszElementFormat);

            //free the memory
            LocalFree((HLOCAL)pwszElementFormat);
            pwszElementFormat=NULL;

            if(fParamAllocated)
                free(pwszParam);

            pwszParam=NULL;

        }

        pwszFormat=pwsz;

    }


	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:

    if(pwszElementFormat)
        LocalFree((HLOCAL)pwszElementFormat);

    if(fParamAllocated)
    {
        if(pwszParam)
            free(pwszParam);
    }


	if(pInfo)
		free(pInfo);

    if(pwsz)
        free(pwsz);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatBytesToHexError);
}

//--------------------------------------------------------------------------
//
//	 FormatFinancialCriteria: SPC_FINANCIAL_CRITERIA_OBJID
//                            SPC_FINANCIAL_CRITERIA_STRUCT
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatFinancialCriteria(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
	WCHAR							wszYesNo[YES_NO_SIZE];
	WCHAR							wszAvailable[AVAIL_SIZE];
	PSPC_FINANCIAL_CRITERIA     	pInfo=NULL;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    UINT                            idsInfo=0;


	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,SPC_FINANCIAL_CRITERIA_STRUCT,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

	//load the string for financial info
    if(TRUE==pInfo->fFinancialInfoAvailable)
    {
        if(TRUE==pInfo->fMeetsCriteria)
            idsInfo=IDS_YES;
        else
            idsInfo=IDS_NO;

        //load the string for "yes" or "no"
        if(!LoadStringU(hFrmtFuncInst,idsInfo, wszYesNo, sizeof(wszYesNo)/sizeof(wszYesNo[0])))
		        goto LoadStringError;

        //mark the avaiblility of the financial info
        idsInfo=IDS_AVAILABLE;
    }
    else
        idsInfo=IDS_NOT_AVAILABLE;

	if(!LoadStringU(hFrmtFuncInst,idsInfo, wszAvailable,
        sizeof(wszAvailable)/sizeof(wszAvailable[0])))
		goto LoadStringError;

    //format the output string
    if(TRUE==pInfo->fFinancialInfoAvailable)
    {
        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            idsInfo=IDS_SPC_FINANCIAL_AVAIL_MULTI;
        else
            idsInfo=IDS_SPC_FINANCIAL_AVAIL;

        if(!FormatMessageUnicode(&pwszFormat, idsInfo,
            wszAvailable, wszYesNo))
            goto FormatMsgError;
    }
    else
    {
        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            idsInfo=IDS_SPC_FINANCIAL_NOT_AVAIL_MULTI;
        else
            idsInfo=IDS_SPC_FINANCIAL_NOT_AVAIL;

        if(!FormatMessageUnicode(&pwszFormat, idsInfo,
            wszAvailable))
            goto FormatMsgError;
    }

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:
	if(pwszFormat)
		LocalFree((HLOCAL)pwszFormat);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);

}

//--------------------------------------------------------------------------
//
//	 FormatNextUpdateLocation: szOID_NEXT_UPDATE_LOCATION
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatNextUpdateLocation(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	PCERT_ALT_NAME_INFO	            pInfo=NULL;
	BOOL							fResult=FALSE;

	//check for input parameters
	if((NULL==pbEncoded && cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,szOID_NEXT_UPDATE_LOCATION,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

	//format the alternative name
    fResult=FormatAltNameInfo(dwCertEncodingType, dwFormatType,dwFormatStrType,
                            pFormatStruct,
                            0,      //no prefix
                            TRUE,
                            pInfo, pbFormat, pcbFormat);

    if(FALSE==fResult)
        goto FormatAltNameError;

CommonReturn:

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(FormatAltNameError);

}

//--------------------------------------------------------------------------
//
//	 FormatSubjectKeyID: szOID_SUBJECT_KEY_IDENTIFIER
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatSubjectKeyID(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	PCRYPT_DATA_BLOB	            pInfo=NULL;
	BOOL							fResult=FALSE;
    WCHAR                           wszNoInfo[NO_INFO_SIZE];
    DWORD                           cbNeeded=0;

	//check for input parameters
	if((NULL==pbEncoded && cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,szOID_SUBJECT_KEY_IDENTIFIER,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

	//format the key subject ID
    //handle NULL data case
    if(0==pInfo->cbData)
    {
         //load the string "Info Not Available"
	    if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, wszNoInfo, sizeof(wszNoInfo)/sizeof(wszNoInfo[0])))
		    goto LoadStringError;

        cbNeeded=sizeof(WCHAR)*(wcslen(wszNoInfo)+1);

	    //length only calculation
	    if(NULL==pbFormat)
	    {
		    *pcbFormat=cbNeeded;
		    fResult=TRUE;
		    goto CommonReturn;
	    }


	    if((*pcbFormat)<cbNeeded)
        {
            *pcbFormat=cbNeeded;
		    goto MoreDataError;
        }

	    //copy the data
	    memcpy(pbFormat, wszNoInfo, cbNeeded);

	    //copy the size
	    *pcbFormat=cbNeeded;

	    fResult=TRUE;

    }
    else
    {

        fResult=FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            pFormatStruct,
                            lpszStructType,
                            pInfo->pbData,
                            pInfo->cbData,
                            pbFormat,
                            pcbFormat);


        if(FALSE==fResult)
            goto FormatBytestToHexError;
    }


CommonReturn:

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(FormatBytestToHexError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);

}

//--------------------------------------------------------------------------
//
//	 FormatAuthorityKeyID: szOID_AUTHORITY_KEY_IDENTIFIER
//                         X509_AUTHORITY_KEY_ID
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatAuthorityKeyID(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwsz=NULL;

    LPWSTR                          pwszKeyID=NULL;
    LPWSTR                          pwszKeyIDFormat=NULL;
    LPWSTR                          pwszCertIssuer=NULL;
    LPWSTR                          pwszCertIssuerFormat=NULL;
    LPWSTR                          pwszCertNumber=NULL;
    LPWSTR                          pwszCertNumberFormat=NULL;
    BYTE                            *pByte=NULL;

    DWORD                           dwByteIndex=0;
    WCHAR                           wszNoInfo[NO_INFO_SIZE];
	PCERT_AUTHORITY_KEY_ID_INFO	    pInfo=NULL;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    HRESULT                         hr=S_OK;
    UINT                            ids=0;

	
	//check for input parameters
	if((NULL==pbEncoded && cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_AUTHORITY_KEY_ID,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

    //load the string "Info Not Available"
    if((0==pInfo->KeyId.cbData)&&(0==pInfo->CertIssuer.cbData)
        &&(0==pInfo->CertSerialNumber.cbData))
    {
	    if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, wszNoInfo, sizeof(wszNoInfo)/sizeof(wszNoInfo[0])))
		    goto LoadStringError;

        pwszFormat=wszNoInfo;
    }
    else
    {
        pwsz=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwsz)
            goto MemoryError;
        *pwsz=L'\0';

        //format the three fields in the struct: KeyID; CertIssuer; CertSerialNumber
        if(0!=pInfo->KeyId.cbData)
        {
            cbNeeded=0;

            if(!FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            NULL,
                            NULL,
                            pInfo->KeyId.pbData,
                            pInfo->KeyId.cbData,
                            NULL,
                            &cbNeeded))
                goto KeyIDBytesToHexError;

            pwszKeyID=(LPWSTR)malloc(cbNeeded);

            if(NULL==pwszKeyID)
                goto MemoryError;

            if(!FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            NULL,
                            NULL,
                            pInfo->KeyId.pbData,
                            pInfo->KeyId.cbData,
                            pwszKeyID,
                            &cbNeeded))
                goto KeyIDBytesToHexError;

            if(!FormatMessageUnicode(&pwszKeyIDFormat, IDS_AUTH_KEY_ID,pwszKeyID))
                goto FormatMsgError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszKeyIDFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            //strcat the KeyID
            wcscat(pwsz,pwszKeyIDFormat);

            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                wcscat(pwsz, wszNEWLN);
        }

        //format certIssuer
        if(0!=pInfo->CertIssuer.cbData)
        {
            //strcat ", " if there is data before
            if(0!=wcslen(pwsz))
            {
                if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                    wcscat(pwsz, wszCOMMA);
            }

            if(!CryptDllFormatNameAll(
				dwCertEncodingType,	
				dwFormatType,
				dwFormatStrType,
				pFormatStruct,
                IDS_ONE_TAB,
                TRUE,             //memory allocation
				pInfo->CertIssuer.pbData,
				pInfo->CertIssuer.cbData,
				(void **)&pwszCertIssuer,
				NULL))
                goto GetCertNameError;

            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_AUTH_CERT_ISSUER_MULTI;
            else
                ids=IDS_AUTH_CERT_ISSUER;

            if(!FormatMessageUnicode(&pwszCertIssuerFormat, ids,pwszCertIssuer))
                goto FormatMsgError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszCertIssuerFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz,pwszCertIssuerFormat);

            //no need for \n for CERT_NAME
        }

        //format CertSerialNumber
        if(0!=pInfo->CertSerialNumber.cbData)
        {

            //strcat ", " if there is data before
            if(0!=wcslen(pwsz))
            {
                if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                    wcscat(pwsz, wszCOMMA);
            }

            //copy the serial number into the correct order
            pByte=(BYTE *)malloc(pInfo->CertSerialNumber.cbData);
            if(NULL==pByte)
                goto MemoryError;

            for(dwByteIndex=0; dwByteIndex <pInfo->CertSerialNumber.cbData;
                dwByteIndex++)
            {

                pByte[dwByteIndex]=*(pInfo->CertSerialNumber.pbData+
                        pInfo->CertSerialNumber.cbData-1-dwByteIndex);
            }

            cbNeeded=0;

            if(!FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            NULL,
                            NULL,
                            pByte,
                            pInfo->CertSerialNumber.cbData,
                            NULL,
                            &cbNeeded))
                goto CertNumberBytesToHexError;

            pwszCertNumber=(LPWSTR)malloc(cbNeeded);

            if(NULL==pwszCertNumber)
                goto MemoryError;

            if(!FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            NULL,
                            NULL,
                            pByte,
                            pInfo->CertSerialNumber.cbData,
                            pwszCertNumber,
                            &cbNeeded))
             goto CertNumberBytesToHexError;


            if(!FormatMessageUnicode(&pwszCertNumberFormat, IDS_AUTH_CERT_NUMBER,pwszCertNumber))
                goto FormatMsgError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszCertNumberFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz,pwszCertNumberFormat);

            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                wcscat(pwsz, wszNEWLN);

        }

        pwszFormat=pwsz;
    }


	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:
    if(pByte)
        free(pByte);

    if(pwszKeyID)
       free(pwszKeyID);

    if(pwszKeyIDFormat)
        LocalFree((HLOCAL)pwszKeyIDFormat);

    if(pwszCertIssuer)
       free(pwszCertIssuer);

    if(pwszCertIssuerFormat)
        LocalFree((HLOCAL)pwszCertIssuerFormat);

    if(pwszCertNumber)
       free(pwszCertNumber);


    if(pwszCertNumberFormat)
        LocalFree((HLOCAL)pwszCertNumberFormat);

    if(pwsz)
        free(pwsz);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
TRACE_ERROR(KeyIDBytesToHexError);
TRACE_ERROR(GetCertNameError);
TRACE_ERROR(CertNumberBytesToHexError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
}

//--------------------------------------------------------------------------
//
//	 FormatAuthorityKeyID2: szOID_AUTHORITY_KEY_IDENTIFIER2
//                          X509_AUTHORITY_KEY_ID2
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatAuthorityKeyID2(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
    LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwsz=NULL;

    LPWSTR                          pwszKeyID=NULL;
    LPWSTR                          pwszKeyIDFormat=NULL;
    LPWSTR                          pwszCertIssuer=NULL;
    LPWSTR                          pwszCertIssuerFormat=NULL;
    LPWSTR                          pwszCertNumber=NULL;
    LPWSTR                          pwszCertNumberFormat=NULL;
    BYTE                            *pByte=NULL;

    DWORD                           dwByteIndex=0;
    WCHAR                           wszNoInfo[NO_INFO_SIZE];
	PCERT_AUTHORITY_KEY_ID2_INFO	pInfo=NULL;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    HRESULT                         hr=S_OK;
    UINT                            ids=0;

	
	//check for input parameters
	if((NULL==pbEncoded && cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_AUTHORITY_KEY_ID2,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

    //load the string "Info Not Available"
    if((0==pInfo->KeyId.cbData)&&(0==pInfo->AuthorityCertIssuer.cAltEntry)
        &&(0==pInfo->AuthorityCertSerialNumber.cbData))
    {
	    if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, wszNoInfo, sizeof(wszNoInfo)/sizeof(wszNoInfo[0])))
		    goto LoadStringError;

        pwszFormat=wszNoInfo;
    }
    else
    {
        pwsz=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwsz)
            goto MemoryError;
        *pwsz=L'\0';

        //format the three fields in the struct: KeyID; CertIssuer; CertSerialNumber
        if(0!=pInfo->KeyId.cbData)
        {
            cbNeeded=0;

            if(!FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            NULL,
                            NULL,
                            pInfo->KeyId.pbData,
                            pInfo->KeyId.cbData,
                            NULL,
                            &cbNeeded))
                goto KeyIDBytesToHexError;

            pwszKeyID=(LPWSTR)malloc(cbNeeded);

            if(NULL==pwszKeyID)
                goto MemoryError;

            if(!FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            NULL,
                            NULL,
                            pInfo->KeyId.pbData,
                            pInfo->KeyId.cbData,
                            pwszKeyID,
                            &cbNeeded))
                goto KeyIDBytesToHexError;

            if(!FormatMessageUnicode(&pwszKeyIDFormat, IDS_AUTH_KEY_ID,pwszKeyID))
                goto FormatMsgError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+
                                wcslen(pwszKeyIDFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz,pwszKeyIDFormat);

            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                wcscat(pwsz, wszNEWLN);

        }

        //format certIssuer
        if(0!=pInfo->AuthorityCertIssuer.cAltEntry)
        {
            //strcat ", " if there is data before
            if(0!=wcslen(pwsz))
            {
                if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                    wcscat(pwsz, wszCOMMA);
            }


            cbNeeded=0;

            //need a \t before each entry of the alternative name
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                ids=IDS_ONE_TAB;
            else
                ids=0;

            //format the alternative name
            if(!FormatAltNameInfo(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            pFormatStruct,
                            ids,
                            FALSE,
                            &(pInfo->AuthorityCertIssuer),
                            NULL,
                            &cbNeeded))
                goto FormatAltNameError;

            pwszCertIssuer=(LPWSTR)malloc(cbNeeded);
            if(NULL==pwszCertIssuer)
                goto MemoryError;

            if(!FormatAltNameInfo(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            pFormatStruct,
                            ids,
                            FALSE,
                            &(pInfo->AuthorityCertIssuer),
                            pwszCertIssuer,
                            &cbNeeded))
                goto FormatAltNameError;

            //format the element.  Has to distinguish between the multi line
            //and single line for alternative name:
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            {
                if(!FormatMessageUnicode(&pwszCertIssuerFormat, IDS_AUTH_CERT_ISSUER_MULTI,pwszCertIssuer))
                    goto FormatMsgError;
            }
            else
            {
                if(!FormatMessageUnicode(&pwszCertIssuerFormat, IDS_AUTH_CERT_ISSUER,pwszCertIssuer))
                    goto FormatMsgError;
            }


            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)
                        +wcslen(pwszCertIssuerFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz,pwszCertIssuerFormat);

            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                wcscat(pwsz, wszNEWLN);
        }

        //format CertSerialNumber
        if(0!=pInfo->AuthorityCertSerialNumber.cbData)
        {
            //strcat ", " if there is data before
            if(0!=wcslen(pwsz))
            {
                if(0==(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE))
                    wcscat(pwsz, wszCOMMA);
            }

            //copy the serial number into the correct order
            pByte=(BYTE *)malloc(pInfo->AuthorityCertSerialNumber.cbData);
            if(NULL==pByte)
                goto MemoryError;

            for(dwByteIndex=0; dwByteIndex <pInfo->AuthorityCertSerialNumber.cbData;
                dwByteIndex++)
            {

                pByte[dwByteIndex]=*(pInfo->AuthorityCertSerialNumber.pbData+
                        pInfo->AuthorityCertSerialNumber.cbData-1-dwByteIndex);
            }

            cbNeeded=0;

            if(!FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            NULL,
                            NULL,
                            pByte,
                            pInfo->AuthorityCertSerialNumber.cbData,
                            NULL,
                            &cbNeeded))
                goto CertNumberBytesToHexError;

            pwszCertNumber=(LPWSTR)malloc(cbNeeded);

            if(NULL==pwszCertNumber)
                goto MemoryError;

            if(!FormatBytesToHex(dwCertEncodingType,
                            dwFormatType,
                            dwFormatStrType,
                            NULL,
                            NULL,
                            pByte,
                            pInfo->AuthorityCertSerialNumber.cbData,
                            pwszCertNumber,
                            &cbNeeded))
             goto CertNumberBytesToHexError;


            if(!FormatMessageUnicode(&pwszCertNumberFormat, IDS_AUTH_CERT_NUMBER,pwszCertNumber))
                goto FormatMsgError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)
                    +wcslen(pwszCertNumberFormat)+1));

            if(NULL==pwsz)
                goto MemoryError;

            wcscat(pwsz,pwszCertNumberFormat);

            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                wcscat(pwsz, wszNEWLN);
        }

        //convert the WCHAR version
        pwszFormat=pwsz;
    }


	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:
    if(pByte)
        free(pByte);

    if(pwszKeyID)
       free(pwszKeyID);

    if(pwszKeyIDFormat)
        LocalFree((HLOCAL)pwszKeyIDFormat);

    if(pwszCertIssuer)
       free(pwszCertIssuer);

    if(pwszCertIssuerFormat)
        LocalFree((HLOCAL)pwszCertIssuerFormat);

    if(pwszCertNumber)
       free(pwszCertNumber);


    if(pwszCertNumberFormat)
        LocalFree((HLOCAL)pwszCertNumberFormat);

    if(pwsz)
        free(pwsz);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
TRACE_ERROR(KeyIDBytesToHexError);
TRACE_ERROR(FormatAltNameError);
TRACE_ERROR(CertNumberBytesToHexError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);

}

//--------------------------------------------------------------------------
//
//	 FormatBasicConstraints:   szOID_BASIC_CONSTRAINTS
//                             X509_BASIC_CONSTRAINTS
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatBasicConstraints(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
	WCHAR							wszSubject[SUBJECT_SIZE * 2];
	WCHAR							wszNone[NONE_SIZE];
    LPWSTR                          pwszFormatSub=NULL;
    LPWSTR                          pwszFormatWhole=NULL;
    LPWSTR                          pwszSubtreeName=NULL;
    LPWSTR                          pwszSubtreeFormat=NULL;
    DWORD                           dwIndex=0;
	PCERT_BASIC_CONSTRAINTS_INFO	pInfo=NULL;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
	UINT							idsSub=0;
    HRESULT                         hr=S_OK;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_BASIC_CONSTRAINTS,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;


	//load the string for the subjectType
    //init to "\0"
    *wszSubject=L'\0';

    if(0!=pInfo->SubjectType.cbData)
    {
        //get the subjectType info
        if ((pInfo->SubjectType.pbData[0]) & CERT_CA_SUBJECT_FLAG)
        {
       	    if(!LoadStringU(hFrmtFuncInst,IDS_SUB_CA, wszSubject, sizeof(wszSubject)/sizeof(wszSubject[0])))
		        goto LoadStringError;
        }

        if ((pInfo->SubjectType.pbData[0]) & CERT_END_ENTITY_SUBJECT_FLAG)
        {
            if(wcslen(wszSubject)!=0)
            {
                 wcscat(wszSubject, wszCOMMA);
            }

       	    if(!LoadStringU(hFrmtFuncInst,IDS_SUB_EE, wszSubject+wcslen(wszSubject),
                        SUBJECT_SIZE))
		          goto LoadStringError;
       }

        //load string "NONE"
        if(0==wcslen(wszSubject))
        {
            if(!LoadStringU(hFrmtFuncInst,IDS_NONE, wszSubject, sizeof(wszSubject)/sizeof(wszSubject[0])))
		    goto LoadStringError;
        }

    }

    //path contraints
    if (pInfo->fPathLenConstraint)
	{
        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            idsSub=IDS_BASIC_CONS2_PATH_MULTI;
        else
            idsSub=IDS_BASIC_CONS2_PATH;

        if(!FormatMessageUnicode(&pwszFormatSub,idsSub,
								wszSubject, pInfo->dwPathLenConstraint))
			goto FormatMsgError;
	}
    else
	{
		if(!LoadStringU(hFrmtFuncInst,IDS_NONE, wszNone, sizeof(wszNone)/sizeof(wszNone[0])))
			goto LoadStringError;

        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            idsSub=IDS_BASIC_CONS2_NONE_MULTI;
        else
            idsSub=IDS_BASIC_CONS2_NONE;

        if(!FormatMessageUnicode(&pwszFormatSub,idsSub,
								wszSubject, wszNone))
			goto FormatMsgError;
	}

    pwszFormatWhole=(LPWSTR)malloc(sizeof(WCHAR) * (wcslen(pwszFormatSub)+1));
    if(!pwszFormatWhole)
        goto MemoryError;

    wcscpy(pwszFormatWhole, pwszFormatSub);

    //now, format SubTreeContraints one at a time

   for(dwIndex=0; dwIndex<pInfo->cSubtreesConstraint; dwIndex++)
    {
        //get WCHAR version of the name
        if(!CryptDllFormatNameAll(
				dwCertEncodingType,	
				dwFormatType,
				dwFormatStrType,
				pFormatStruct,
                IDS_ONE_TAB,
                TRUE,                 //memory allocation
				pInfo->rgSubtreesConstraint[dwIndex].pbData,
				pInfo->rgSubtreesConstraint[dwIndex].cbData,
				(void **)&pwszSubtreeName,
				NULL))
                goto GetCertNameError;

        //decide between single line and mulitple line format
        if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            idsSub=IDS_SUBTREE_CONSTRAINT_MULTI;
        else
            idsSub=IDS_SUBTREE_CONSTRAINT;

        if(!FormatMessageUnicode(&pwszSubtreeFormat,idsSub,
								dwIndex+1, pwszSubtreeName))
			goto FormatNameError;

        pwszFormatWhole=(LPWSTR)realloc(pwszFormatWhole, 
            sizeof(WCHAR) * (wcslen(pwszFormatWhole)+1+wcslen(pwszSubtreeFormat)));

        if(NULL == pwszFormatWhole)
            goto MemoryError;

        wcscat(pwszFormatWhole,pwszSubtreeFormat);

        LocalFree((HLOCAL)pwszSubtreeFormat);
        pwszSubtreeFormat=NULL;

        free(pwszSubtreeName);
        pwszSubtreeName=NULL;

    }

    //format to the wide char version
    pwszFormat=pwszFormatWhole;

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:

    if(pwszFormatSub)
        LocalFree((HLOCAL)pwszFormatSub);

    if(pwszSubtreeFormat)
        LocalFree((HLOCAL)pwszSubtreeFormat);

    if(pwszFormatWhole)
        free(pwszFormatWhole);

    if(pwszSubtreeName)
        free(pwszSubtreeName);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
TRACE_ERROR(FormatNameError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(GetCertNameError);
}


//--------------------------------------------------------------------------
//
//	 FormatCRLReasonCode:szOID_CRL_REASON_CODE
//                         X509_CRL_REASON_CODE
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatCRLReasonCode(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	WCHAR							wszReason[CRL_REASON_SIZE];
    LPWSTR                          pwszFormat=NULL;
	int								*pInfo=NULL;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
	UINT							idsCRLReason=0;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_CRL_REASON_CODE,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

	//decide which ids to use
	switch(*pInfo)
	{
		case CRL_REASON_UNSPECIFIED:
				idsCRLReason=IDS_UNSPECIFIED;
			break;
		case CRL_REASON_KEY_COMPROMISE:
				idsCRLReason=IDS_KEY_COMPROMISE;
			break;
		case CRL_REASON_CA_COMPROMISE:
				idsCRLReason=IDS_CA_COMPROMISE;
			break;
		case CRL_REASON_AFFILIATION_CHANGED:
				idsCRLReason=IDS_AFFILIATION_CHANGED;
			break;
		case CRL_REASON_SUPERSEDED:
				idsCRLReason=IDS_SUPERSEDED;
			break;
		case CRL_REASON_CESSATION_OF_OPERATION:
				idsCRLReason=IDS_CESSATION_OF_OPERATION;
			break;
		case CRL_REASON_CERTIFICATE_HOLD:
				idsCRLReason=IDS_CERTIFICATE_HOLD;
			break;
		case CRL_REASON_REMOVE_FROM_CRL:
				idsCRLReason=IDS_REMOVE_FROM_CRL;
			break;
		default:
				idsCRLReason=IDS_UNKNOWN_CRL_REASON;
			break;
	}

	//load string
	if(!LoadStringU(hFrmtFuncInst,idsCRLReason, wszReason, sizeof(wszReason)/sizeof(wszReason[0])))
		goto LoadStringError;

    //format
    if(!FormatMessageUnicode(&pwszFormat, IDS_CRL_REASON, wszReason, *pInfo))
        goto FormatMsgError;

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:
    if(pwszFormat)
        LocalFree((HLOCAL)pwszFormat);

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);

}

//--------------------------------------------------------------------------
//
//	 FormatEnhancedKeyUsage: szOID_ENHANCED_KEY_USAGE
//							 X509_ENHANCED_KEY_USAGE
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatEnhancedKeyUsage(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
    BOOL                            fOIDNameAllocated=FALSE;
	WCHAR							wszNoInfo[NO_INFO_SIZE];
    WCHAR                           wszUnknownOID[UNKNOWN_KEY_USAGE_SIZE];
	PCCRYPT_OID_INFO                pOIDInfo=NULL;

    LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwszOIDName=NULL;
	PCERT_ENHKEY_USAGE				pInfo=NULL;
	LPWSTR							pwsz=NULL;
    LPWSTR                          pwszOIDFormat=NULL;

	DWORD							dwIndex=0;
    DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    HRESULT                         hr=S_OK;

	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_ENHANCED_KEY_USAGE,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

	//load string NONE if there is no value available
	if(0==pInfo->cUsageIdentifier)
	{
		if(!LoadStringU(hFrmtFuncInst,IDS_NO_INFO, wszNoInfo, sizeof(wszNoInfo)/sizeof(wszNoInfo[0])))
			goto LoadStringError;

	    pwszFormat=wszNoInfo;
	}
	else
	{
        //load the string for "unknown key usage"
        if(!LoadStringU(hFrmtFuncInst,IDS_UNKNOWN_KEY_USAGE, wszUnknownOID,
            sizeof(wszUnknownOID)/sizeof(wszUnknownOID[0])))
			goto LoadStringError;

        pwsz=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwsz)
            goto MemoryError;
        *pwsz=L'\0';

		//build the comma/\n seperated string
		for(dwIndex=0; dwIndex<pInfo->cUsageIdentifier; dwIndex++)
        {
            fOIDNameAllocated=FALSE;

           	pOIDInfo=CryptFindOIDInfo(CRYPT_OID_INFO_OID_KEY,
									 (void *)(pInfo->rgpszUsageIdentifier[dwIndex]),
									  CRYPT_ENHKEY_USAGE_OID_GROUP_ID);

            if(pOIDInfo)
			{
				//allocate memory, including the NULL terminator
				pwszOIDName=(LPWSTR)malloc((wcslen(pOIDInfo->pwszName)+1)*
									sizeof(WCHAR));

				if(NULL==pwszOIDName)
					goto MemoryError;

                fOIDNameAllocated=TRUE;

				wcscpy(pwszOIDName,pOIDInfo->pwszName);

			}else
                pwszOIDName=wszUnknownOID;

            if(!FormatMessageUnicode(&pwszOIDFormat, IDS_ENHANCED_KEY_USAGE, pwszOIDName,
                          (pInfo->rgpszUsageIdentifier)[dwIndex]))
                   goto FormatMsgError;

            pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+
                            wcslen(wszCOMMA)+wcslen(pwszOIDFormat)+1));
            if(NULL==pwsz)
                goto MemoryError;

            //strcat the OID
            wcscat(pwsz, pwszOIDFormat);

            //strcat the , or '\n'
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                wcscat(pwsz, wszNEWLN);
            else
            {
                if(dwIndex!=(pInfo->cUsageIdentifier-1))
                    wcscat(pwsz, wszCOMMA);
            }


            LocalFree((HLOCAL)pwszOIDFormat);
            pwszOIDFormat=NULL;

            if(fOIDNameAllocated)
                free(pwszOIDName);

            pwszOIDName=NULL;
        }

        pwszFormat=pwsz;

	}

	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:

	if(pwsz)
		free(pwsz);

    if(pwszOIDFormat)
        LocalFree((HLOCAL)pwszOIDFormat);

    if(fOIDNameAllocated)
    {
        if(pwszOIDName)
            free(pwszOIDName);
    }


	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(FormatMsgError);
}

//--------------------------------------------------------------------------
//
//	 FormatAltNameInfo:
//
//--------------------------------------------------------------------------
BOOL FormatAltNameInfo(
    DWORD		            dwCertEncodingType,
	DWORD		            dwFormatType,
    DWORD                   dwFormatStrType,
    void	            	*pFormatStruct,
    UINT                    idsPreFix,
    BOOL                    fNewLine,
    PCERT_ALT_NAME_INFO	    pInfo,
    void	                *pbFormat,
	DWORD	                *pcbFormat)
{
	
	LPWSTR							pwszFormat=NULL;
    LPWSTR                          pwsz=NULL;

    LPWSTR                          pwszAltEntryFormat=NULL;
    LPWSTR                          pwszAltEntry=NULL;

	WCHAR							wszNoInfo[NO_INFO_SIZE];
    WCHAR                           wszAltName[ALT_NAME_SIZE];
    WCHAR                           wszPreFix[PRE_FIX_SIZE];
    BOOL                            fEntryAllocated=FALSE;
    DWORD                           dwIndex=0;
	DWORD							cbNeeded=0;
	BOOL							fResult=FALSE;
    HRESULT                         hr=S_OK;
    UINT                            idsAltEntryName=0;

	
    //load the string "info not available"
    if(!LoadStringU(hFrmtFuncInst,IDS_NO_ALT_NAME, wszNoInfo, sizeof(wszNoInfo)/sizeof(wszNoInfo[0])))
		goto LoadStringError;

	//build the list of alternative name entries
    //1st, check if any information is available
    if(0==pInfo->cAltEntry)
    {
	    pwszFormat=wszNoInfo;
    }
    else
    {
        //load the pre-dix
        if(0!=idsPreFix)
        {
            if(!LoadStringU(hFrmtFuncInst, idsPreFix,
                        wszPreFix, sizeof(wszPreFix)/sizeof(wszPreFix[0])))
                goto LoadStringError;

        }

        pwsz=(LPWSTR)malloc(sizeof(WCHAR));
        if(NULL==pwsz)
            goto MemoryError;

        //NULL terminate the string
        *pwsz=L'\0';

        //build the list of alternative name entries
        for(dwIndex=0; dwIndex<pInfo->cAltEntry; dwIndex++)
        {
            fEntryAllocated=FALSE;

             switch((pInfo->rgAltEntry)[dwIndex].dwAltNameChoice)
             {
                case CERT_ALT_NAME_OTHER_NAME:
                        idsAltEntryName=IDS_OTHER_NAME;
                        pwszAltEntry=wszNoInfo;
                    break;

                case CERT_ALT_NAME_RFC822_NAME:
                         idsAltEntryName=IDS_RFC822_NAME;
                         pwszAltEntry=(pInfo->rgAltEntry)[dwIndex].pwszRfc822Name;
                    break;
                case CERT_ALT_NAME_DNS_NAME:
                         idsAltEntryName=IDS_DNS_NAME;
                         pwszAltEntry=(pInfo->rgAltEntry)[dwIndex].pwszDNSName;
                   break;

                case CERT_ALT_NAME_X400_ADDRESS:
                         idsAltEntryName=IDS_X400_ADDRESS;
                         pwszAltEntry=wszNoInfo;
                   break;

                case CERT_ALT_NAME_DIRECTORY_NAME:

                         if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
                            idsAltEntryName=IDS_DIRECTORY_NAME_MULTI;
                         else
                            idsAltEntryName=IDS_DIRECTORY_NAME;

                        if(!CryptDllFormatNameAll(
				            dwCertEncodingType,	
				            dwFormatType,
				            dwFormatStrType,
				            pFormatStruct,
                            (0!=idsPreFix) ? idsPreFix+1 : IDS_ONE_TAB,
                            TRUE,           //memory allocation
				            (pInfo->rgAltEntry)[dwIndex].DirectoryName.pbData,
				            (pInfo->rgAltEntry)[dwIndex].DirectoryName.cbData,
				            (void **)&pwszAltEntry,
				            NULL))
                            goto GetCertNameError;

                         fEntryAllocated=TRUE;

                    break;

                case CERT_ALT_NAME_EDI_PARTY_NAME:
                        idsAltEntryName=IDS_EDI_PARTY_NAME;
                        pwszAltEntry=wszNoInfo;
                    break;

                case CERT_ALT_NAME_URL:
                         idsAltEntryName=IDS_URL;
                         pwszAltEntry=(pInfo->rgAltEntry)[dwIndex].pwszURL;
                   break;

                case CERT_ALT_NAME_IP_ADDRESS:
                        idsAltEntryName=IDS_IP_ADDRESS;

                        if(!FormatBytesToHex(dwCertEncodingType,
                                            dwFormatType,
                                            dwFormatStrType,
                                            pFormatStruct,
                                            NULL,
                                            (pInfo->rgAltEntry)[dwIndex].IPAddress.pbData,
                                            (pInfo->rgAltEntry)[dwIndex].IPAddress.cbData,
                                            NULL,
                                            &cbNeeded))
                            goto FormatByesToHexError;

                        pwszAltEntry=(LPWSTR)malloc(cbNeeded);

                        if(NULL==pwszAltEntry)
                            goto MemoryError;

                        if(!FormatBytesToHex(dwCertEncodingType,
                                            dwFormatType,
                                            dwFormatStrType,
                                            pFormatStruct,
                                            NULL,
                                            (pInfo->rgAltEntry)[dwIndex].IPAddress.pbData,
                                            (pInfo->rgAltEntry)[dwIndex].IPAddress.cbData,
                                            pwszAltEntry,
                                            &cbNeeded))
                            goto FormatByesToHexError;

                        fEntryAllocated=TRUE;


                    break;

                case CERT_ALT_NAME_REGISTERED_ID:

                        idsAltEntryName=IDS_REGISTERED_ID;

                        if(S_OK!=(hr=SZtoWSZ((pInfo->rgAltEntry)[dwIndex].pszRegisteredID,
                                            &pwszAltEntry)))
                            goto SZtoWSZError;

                        fEntryAllocated=TRUE;
                    break;

                default:
                        idsAltEntryName=IDS_UNKNOWN_VALUE;
                        pwszAltEntry=wszNoInfo;
                    break;

             }

             //load the alternative name string
            if(!LoadStringU(hFrmtFuncInst,idsAltEntryName, wszAltName, sizeof(wszAltName)/sizeof(wszAltName[0])))
		            goto LoadStringError;

            //format message
            if(idsAltEntryName!=IDS_UNKNOWN_VALUE)
            {
                if(!FormatMessageUnicode(&pwszAltEntryFormat,IDS_ALT_NAME_ENTRY, wszAltName,
                    pwszAltEntry))
                    goto FormatMsgError;
            }
            else
            {
                if(!FormatMessageUnicode(&pwszAltEntryFormat,IDS_ALT_NAME_ENTRY_UNKNOWN, wszAltName,
                    (pInfo->rgAltEntry)[dwIndex].dwAltNameChoice))
                    goto FormatMsgError;
            }

            //concatenate the string, including the postfix and prefix if necessary
            if(0!=idsPreFix)
                pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(wszPreFix)+wcslen(pwszAltEntryFormat)+1));
            else
                pwsz=(LPWSTR)realloc(pwsz, 
                sizeof(WCHAR) * (wcslen(pwsz)+wcslen(wszCOMMA)+wcslen(pwszAltEntryFormat)+1));

            if(NULL==pwsz)
                goto MemoryError;

            //strcat the preFix
            if(0!=idsPreFix)
                wcscat(pwsz, wszPreFix);

            //strcat the entry
            wcscat(pwsz, pwszAltEntryFormat);

            //strcat the postFix
            if(dwFormatStrType & CRYPT_FORMAT_STR_MULTI_LINE)
            {
                if((TRUE==fNewLine) || (dwIndex != (pInfo->cAltEntry-1)))
                {
                    //no need for \n if the name is directory name (CERT_NAME)
                    //in multi line format
                    if(idsAltEntryName !=IDS_DIRECTORY_NAME_MULTI)
                        wcscat(pwsz, wszNEWLN);
                }

            }
            else
            {
                if(dwIndex != (pInfo->cAltEntry-1))
                    wcscat(pwsz, wszCOMMA);
            }

            LocalFree((HLOCAL)pwszAltEntryFormat);
            pwszAltEntryFormat=NULL;

            if(fEntryAllocated)
                free(pwszAltEntry);
            pwszAltEntry=NULL;
        }

        //if the last entry in the alternative name is  IDS_DIRECTORY_NAME_MULTI,
        //we need to get rid of the last \n if fNewLine is FALSE
        if(FALSE==fNewLine)
        {

            if(idsAltEntryName==IDS_DIRECTORY_NAME_MULTI)
            {
                *(pwsz+wcslen(pwsz)-wcslen(wszNEWLN))=L'\0';
            }
        }

        //conver to the WCHAR format

        pwszFormat=pwsz;
    }


	cbNeeded=sizeof(WCHAR)*(wcslen(pwszFormat)+1);

	//length only calculation
	if(NULL==pbFormat)
	{
		*pcbFormat=cbNeeded;
		fResult=TRUE;
		goto CommonReturn;
	}


	if((*pcbFormat)<cbNeeded)
    {
        *pcbFormat=cbNeeded;
		goto MoreDataError;
    }

	//copy the data
	memcpy(pbFormat, pwszFormat, cbNeeded);

	//copy the size
	*pcbFormat=cbNeeded;

	fResult=TRUE;
	

CommonReturn:

    if(pwsz)
        free(pwsz);

    if(pwszAltEntryFormat)
        LocalFree((HLOCAL)pwszAltEntryFormat);

    if(fEntryAllocated)
    {
        if(pwszAltEntry)
            free(pwszAltEntry);
    }


	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

TRACE_ERROR(LoadStringError);
SET_ERROR(MoreDataError,ERROR_MORE_DATA);
TRACE_ERROR(FormatMsgError);
SET_ERROR_VAR(SZtoWSZError, hr);
TRACE_ERROR(GetCertNameError);
TRACE_ERROR(FormatByesToHexError);
SET_ERROR(MemoryError, E_OUTOFMEMORY);

}

//--------------------------------------------------------------------------
//
//	 FormatAltName:  X509_ALTERNATE_NAME
//                   szOID_SUBJECT_ALT_NAME
//                   szOID_ISSUER_ALT_NAME
//                   szOID_SUBJECT_ALT_NAME2
//                   szOID_ISSUER_ALT_NAME2
//
//--------------------------------------------------------------------------
static BOOL
WINAPI
FormatAltName(
	DWORD		dwCertEncodingType,
	DWORD		dwFormatType,
	DWORD		dwFormatStrType,
	void		*pFormatStruct,
	LPCSTR		lpszStructType,
	const BYTE *pbEncoded,
	DWORD		cbEncoded,
	void	   *pbFormat,
	DWORD	   *pcbFormat)
{
	
	BOOL							fResult=FALSE;
	PCERT_ALT_NAME_INFO	            pInfo=NULL;
	
	//check for input parameters
	if((NULL==pbEncoded&& cbEncoded!=0) ||
			(NULL==pcbFormat))
		goto InvalidArg;

	if(cbEncoded==0)
	{
		*pcbFormat=0;
		goto InvalidArg;
	}

    if (!DecodeGenericBLOB(dwCertEncodingType,X509_ALTERNATE_NAME,
			pbEncoded,cbEncoded, (void **)&pInfo))
		goto DecodeGenericError;

    fResult=FormatAltNameInfo(dwCertEncodingType, dwFormatType,dwFormatStrType,
                            pFormatStruct,
                            0,
                            TRUE,
                            pInfo, pbFormat, pcbFormat);

    if(FALSE==fResult)
        goto FormatAltNameError;

CommonReturn:

	if(pInfo)
		free(pInfo);

	return fResult;

ErrorReturn:

	fResult=FALSE;
	goto CommonReturn;

SET_ERROR(InvalidArg, E_INVALIDARG);
TRACE_ERROR(DecodeGenericError);
TRACE_ERROR(FormatAltNameError);

}

//--------------------------------------------------------------------------
//
//	  GetCertNameMulti
//
//    Get the multi line display of the certificate name
//--------------------------------------------------------------------------
BOOL    GetCertNameMulti(LPWSTR          pwszNameStr,
                         UINT            idsPreFix,
                         LPWSTR          *ppwsz)
{

    BOOL            fResult=FALSE;
    WCHAR           wszPreFix[PRE_FIX_SIZE];
    LPWSTR          pwszStart=NULL;
    LPWSTR          pwszEnd=NULL;
    DWORD           dwCopy=0;
    LPWSTR          pwszNameStart=NULL;
    BOOL            fDone=FALSE;
    BOOL            fInQuote=FALSE;


    //init
    *ppwsz=NULL;

    //load string for the preFix
    if(0!=idsPreFix && 1!=idsPreFix)
    {
        if(!LoadStringU(hFrmtFuncInst, idsPreFix, wszPreFix, PRE_FIX_SIZE))
            goto LoadStringError;
    }

   *ppwsz=(LPWSTR)malloc(sizeof(WCHAR));
   if(NULL==*ppwsz)
        goto MemoryError;
   **ppwsz=L'\0';

   //now, start the search for the symbol '+' or ','
   pwszStart=pwszNameStr;
   pwszEnd=pwszNameStr;

   //parse the whole string
   for(;FALSE==fDone; pwszEnd++)
   {
       //mark fInQuote to TRUE if we are inside " "
       if(L'\"'==*pwszEnd)
           fInQuote=!fInQuote;

       if((L'+'==*pwszEnd) || (L','==*pwszEnd) ||(L'\0'==*pwszEnd))
       {
           //make sure + and ; are not quoted
           if((L'+'==*pwszEnd) || (L','==*pwszEnd))
           {
                if(TRUE==fInQuote)
                    continue;

           }

           //skip the leading spaces
           for(;*pwszStart != L'\0'; pwszStart++)
           {
                if(*pwszStart != L' ')
                    break;
           }

           //we are done if NULL is reached
           if(L'\0'==*pwszStart)
               break;

           //calculate the length to copy
           dwCopy=(DWORD)(pwszEnd-pwszStart);

           if(0!=idsPreFix && 1!=idsPreFix)
                *ppwsz=(LPWSTR)realloc(*ppwsz,
                    (wcslen(*ppwsz)+dwCopy+wcslen(wszPreFix)+wcslen(wszNEWLN)+1)*sizeof(WCHAR));
           else
                *ppwsz=(LPWSTR)realloc(*ppwsz,
                    (wcslen(*ppwsz)+dwCopy+wcslen(wszNEWLN)+1)*sizeof(WCHAR));

           if(NULL == *ppwsz)
               goto MemoryError;

           //copy the prefix
           if(0!=idsPreFix && 1!=idsPreFix)
                wcscat(*ppwsz, wszPreFix);

           pwszNameStart=(*ppwsz)+wcslen(*ppwsz);

           //copy the string to *ppwsz
           memcpy(pwszNameStart, pwszStart, dwCopy*sizeof(WCHAR));
           pwszNameStart += dwCopy;

           //NULL terminate the string
           *pwszNameStart=L'\0';

           //copy the "\n"
           wcscat(*ppwsz, wszNEWLN);

           //reset pwszStart and pwszEnd.
           pwszStart=pwszEnd+1;

           if(L'\0'==*pwszEnd)
               fDone=TRUE;
       }

   }


    fResult=TRUE;

CommonReturn:

     return fResult;

ErrorReturn:

     if(*ppwsz)
     {
         free(*ppwsz);
         *ppwsz=NULL;
     }

     fResult=FALSE;

     goto CommonReturn;

SET_ERROR(MemoryError, E_OUTOFMEMORY);
TRACE_ERROR(LoadStringError);
}

//--------------------------------------------------------------------------
//
//	  FormatMessageUnicode
//
//--------------------------------------------------------------------------
BOOL	FormatMessageUnicode(LPWSTR	*ppwszFormat,UINT ids,...)
{
    // get format string from resources
    WCHAR		wszFormat[1000];
	va_list		argList;
	DWORD		cbMsg=0;
	BOOL		fResult=FALSE;
	HRESULT		hr=S_OK;

    if(NULL == ppwszFormat)
        goto InvalidArgErr;

    if(!LoadStringU(hFrmtFuncInst, ids, wszFormat, sizeof(wszFormat)))
		goto LoadStringError;

    // format message into requested buffer
    va_start(argList, ids);

    cbMsg = FormatMessageU(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING,
        wszFormat,
        0,                  // dwMessageId
        0,                  // dwLanguageId
        (LPWSTR) (ppwszFormat),
        0,                  // minimum size to allocate
        &argList);

    va_end(argList);

	if(!cbMsg)
		goto FormatMessageError;

	fResult=TRUE;

CommonReturn:
	
	return fResult;

ErrorReturn:
	fResult=FALSE;

	goto CommonReturn;


TRACE_ERROR(LoadStringError);
TRACE_ERROR(FormatMessageError);
SET_ERROR(InvalidArgErr, E_INVALIDARG);
}

//--------------------------------------------------------------------------
//
//	  FormatMessageStr
//
//--------------------------------------------------------------------------
/*BOOL	FormatMessageStr(LPSTR	*ppszFormat,UINT ids,...)
{
    // get format string from resources
    CHAR		szFormat[1000];
	va_list		argList;
	BOOL		fResult=FALSE;
	HRESULT		hr=S_OK;

    if(!LoadStringA(hFrmtFuncInst, ids, szFormat, sizeof(szFormat)))
		goto LoadStringError;

    // format message into requested buffer
    va_start(argList, ids);

    if(0==FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING,
        szFormat,
        0,                  // dwMessageId
        0,                  // dwLanguageId
        (LPSTR) ppszFormat,
        0,                  // minimum size to allocate
        &argList))
        goto FormatMessageError;

    va_end(argList);

	fResult=TRUE;

CommonReturn:
	
	return fResult;

ErrorReturn:
	fResult=FALSE;

	goto CommonReturn;


TRACE_ERROR(LoadStringError);
TRACE_ERROR(FormatMessageError);

} */

//--------------------------------------------------------------------------
//
//	  Decode a generic BLOB
//
//--------------------------------------------------------------------------
BOOL	DecodeGenericBLOB(DWORD dwEncodingType, LPCSTR lpszStructType,
			const BYTE *pbEncoded, DWORD cbEncoded,void **ppStructInfo)
{
	DWORD	cbStructInfo=0;

	//decode the object.  No copying
	if(!CryptDecodeObject(dwEncodingType,lpszStructType,pbEncoded, cbEncoded,
		0,NULL,	&cbStructInfo))
		return FALSE;

	*ppStructInfo=malloc(cbStructInfo);

	if(!(*ppStructInfo))
	{
		SetLastError(E_OUTOFMEMORY);
		return FALSE;
	}

	return CryptDecodeObject(dwEncodingType,lpszStructType,pbEncoded, cbEncoded,
		0,*ppStructInfo,&cbStructInfo);
}

////////////////////////////////////////////////////////
//
// Convert STR to WSTR
//
HRESULT	SZtoWSZ(LPSTR szStr,LPWSTR *pwsz)
{
	DWORD	dwSize=0;
	DWORD	dwError=0;

	*pwsz=NULL;

	//return NULL
	if(!szStr)
		return S_OK;

	dwSize=MultiByteToWideChar(0, 0,szStr, -1,NULL,0);

	if(dwSize==0)
	{
		dwError=GetLastError();
		return HRESULT_FROM_WIN32(dwError);
	}

	//allocate memory
	*pwsz=(LPWSTR)malloc(dwSize * sizeof(WCHAR));

	if(*pwsz==NULL)
		return E_OUTOFMEMORY;

	if(MultiByteToWideChar(0, 0,szStr, -1,
		*pwsz,dwSize))
	{
		return S_OK;
	}
	else
	{
		 free(*pwsz);
         *pwsz=NULL;
		 dwError=GetLastError();
		 return HRESULT_FROM_WIN32(dwError);
	}
}

//--------------------------------------------------------------------------
//
//	  Convert dwFormatType to dwStrType
//
//--------------------------------------------------------------------------
DWORD   FormatToStr(DWORD   dwFormatType)
{
    DWORD   dwStrType=0;

    //we default to CERT_X500_NAME_STR
    if(0==dwFormatType)
    {
        return CERT_X500_NAME_STR;
    }

    if(dwFormatType &  CRYPT_FORMAT_SIMPLE)
		dwStrType |= CERT_SIMPLE_NAME_STR;

	if(dwFormatType & CRYPT_FORMAT_X509)
		dwStrType |= CERT_X500_NAME_STR;

	if(dwFormatType & CRYPT_FORMAT_OID)
		dwStrType |= CERT_OID_NAME_STR;

	if(dwFormatType & CRYPT_FORMAT_RDN_SEMICOLON)
		dwStrType |= CERT_NAME_STR_SEMICOLON_FLAG;

	if(dwFormatType & CRYPT_FORMAT_RDN_CRLF)
		dwStrType |= CERT_NAME_STR_CRLF_FLAG;

	if(dwFormatType & CRYPT_FORMAT_RDN_UNQUOTE)
		dwStrType |= CERT_NAME_STR_NO_QUOTING_FLAG;

	if(dwFormatType & CRYPT_FORMAT_RDN_REVERSE)
		dwStrType |= CERT_NAME_STR_REVERSE_FLAG;

    return dwStrType;

}
