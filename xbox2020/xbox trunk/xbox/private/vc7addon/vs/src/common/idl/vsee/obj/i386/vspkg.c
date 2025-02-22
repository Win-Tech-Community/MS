
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Apr 29 23:13:10 2002
 */
/* Compiler settings for vspkg.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
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

MIDL_DEFINE_GUID(IID, IID_IVsEnumBSTRs,0x52383877,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackageDescription,0x52383865,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsJARPackageDescription,0x52383866,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsCABPackageDescription,0x52383867,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsDeploymentCABPackageDescription,0x3C0B95F0,0x8B92,0x11d1,0xA2,0x18,0x00,0x00,0xF8,0x02,0x6F,0x55);


MIDL_DEFINE_GUID(IID, IID_IVsEnumPackageItems,0x52383868,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackageItem,0x52383869,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsJARPackageItem,0x5238386a,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsCABPackageItem,0x5238386b,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingEngineStatusCallback,0xFB61C8EA,0xA6E4,0x11d0,0x8A,0x43,0x00,0xA0,0xC9,0x1E,0x2A,0xCD);


MIDL_DEFINE_GUID(IID, IID_IVsCABPackagingEngineStatusCallback,0x52383875,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingEngine,0xFB61C8E9,0xA6E4,0x11d0,0x8A,0x43,0x00,0xA0,0xC9,0x1E,0x2A,0xCD);


MIDL_DEFINE_GUID(IID, IID_IVsCABPackagingEngine,0x52383876,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackageExplorerStatusCallback,0x52383862,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackageExplorer,0x52383863,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingHelper,0x5238386c,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingWrapperProjectCfg,0x52383874,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingEngineFilter,0x5238386d,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingGeneralPPageController,0x5238386e,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingGeneralPPageSettings,0x5238386f,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingGeneralProperties,0x52383870,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingOutputsProperties,0xa57e3daf,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingPropertyObject,0x5238387a,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsCABPPageController,0x52383871,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsCABPPageSettings,0x52383872,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsCABProperties,0x52383873,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsSigningProperties,0xa57e3d86,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsSigningJavaPermissionProperties,0xa57e3d87,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsOSDProperties,0xa57e3d88,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsSetupPPageController,0x4C2B25CE,0x02F7,0x11d1,0xA4,0xBE,0x00,0x60,0x97,0xC9,0x93,0x3C);


MIDL_DEFINE_GUID(IID, IID_IVsSetupPPageSettings,0x4C2B25C9,0x02F7,0x11d1,0xA4,0xBE,0x00,0x60,0x97,0xC9,0x93,0x3C);


MIDL_DEFINE_GUID(IID, IID_IVsSetupProperties,0x4C2B25C8,0x02F7,0x11d1,0xA4,0xBE,0x00,0x60,0x97,0xC9,0x93,0x3C);


MIDL_DEFINE_GUID(IID, IID_IVsEnumVSSETUPFILEPROP,0x1eecc150,0x93a6,0x11d1,0x92,0x9f,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsSetupFilePlacementProperties,0x5238387d,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsSetupPackageDescription,0x4C2B25CA,0x02F7,0x11d1,0xA4,0xBE,0x00,0x60,0x97,0xC9,0x93,0x3C);


MIDL_DEFINE_GUID(IID, IID_IVsSetupPackageItem,0x4C2B25CB,0x02F7,0x11d1,0xA4,0xBE,0x00,0x60,0x97,0xC9,0x93,0x3C);


MIDL_DEFINE_GUID(IID, IID_IVsSetupPackagingEngineStatusCallback,0x4C2B25CC,0x02F7,0x11d1,0xA4,0xBE,0x00,0x60,0x97,0xC9,0x93,0x3C);


MIDL_DEFINE_GUID(IID, IID_IVsSetupPackagingEngine,0xA54695A1,0x038A,0x11d1,0xA4,0xBF,0x00,0x60,0x97,0xC9,0x93,0x3C);


MIDL_DEFINE_GUID(IID, IID_IVsINFBasicGeneration,0x52DCF8A2,0x0A94,0x11d1,0xA5,0x3E,0x00,0x60,0x97,0xB7,0x18,0x6F);


MIDL_DEFINE_GUID(IID, IID_IVsPackagingEnginePropertyInterfaceBroker,0x52383878,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsJARProperties,0x52383879,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsJARPPageController,0x5238387b,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsJARPPageSettings,0x5238387c,0xc56b,0x11d0,0x8a,0x49,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsOpenSoftwareDistributionInfo,0xa57e3d75,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsCABPermissionsPageSettings,0xa57e3d77,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsVMPermission,0xa57e3d79,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsVMPermissionProvider,0xa57e3d78,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsEnumVMPermissions,0xa57e3d7a,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsVMPermissionCollection,0xa57e3d7b,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsVMPermissionProperty,0xa57e3d7c,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsEnumVMPermissionProperties,0xa57e3d7d,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsCABExternalDependenciesPageSettings,0xa57e3d7e,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsPNPAdditionalFilesPageSettings,0xa57e3d7f,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsWebLibrary,0xa57e3d82,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsWebLibraryProvider,0xa57e3d83,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsEnumWebLibraries,0xa57e3d80,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsWebLibraryCollection,0xa57e3d81,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsAdditionalItemProvider,0xa57e3d84,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsAdditionalItemCollection,0xa57e3d85,0xd2d3,0x11d0,0x8a,0x50,0x00,0xa0,0xc9,0x1e,0x2a,0xcd);


MIDL_DEFINE_GUID(IID, IID_IVsSubProcess,0x4bfaa76b,0xcde4,0x11d0,0xa9,0x5b,0x00,0xaa,0x00,0x47,0x86,0xa8);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

