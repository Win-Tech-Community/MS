
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Apr 29 23:11:41 2002
 */
/* Compiler settings for coloader.idl:
    Oicf, W0, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IVsLoader,0x79B1DAE1,0xD1B1,0x11D2,0x99,0x30,0x00,0xC0,0x4F,0x68,0xFD,0xAF);


MIDL_DEFINE_GUID(IID, LIBID_COLOADERLib,0x79B1DAD0,0xD1B1,0x11D2,0x99,0x30,0x00,0xC0,0x4F,0x68,0xFD,0xAF);


MIDL_DEFINE_GUID(CLSID, CLSID_VsFreeLoader,0x79B1DAE2,0xD1B1,0x11D2,0x99,0x30,0x00,0xC0,0x4F,0x68,0xFD,0xAF);


MIDL_DEFINE_GUID(CLSID, CLSID_VsBothLoader,0x79B1DAE4,0xD1B1,0x11D2,0x99,0x30,0x00,0xC0,0x4F,0x68,0xFD,0xAF);


MIDL_DEFINE_GUID(CLSID, CLSID_VsApartmentLoader,0x79B1DAE6,0xD1B1,0x11D2,0x99,0x30,0x00,0xC0,0x4F,0x68,0xFD,0xAF);


MIDL_DEFINE_GUID(CLSID, CLSID_VsDefaultLoader,0x392ffaad,0x3ed8,0x4d49,0x87,0x96,0x8b,0x3b,0xa1,0xd4,0x55,0xb4);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

