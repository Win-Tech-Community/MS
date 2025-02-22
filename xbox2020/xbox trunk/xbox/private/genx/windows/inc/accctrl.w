//+-------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1993-1998.
//
//  File:       accctrl.h
//
//  Contents:   common includes for new style Win32 Access Control
//              APIs
//
//
//--------------------------------------------------------------------
#ifndef __ACCESS_CONTROL__
#define __ACCESS_CONTROL__

#ifndef __midl
#include <wtypes.h>
#endif

;begin_both
#ifdef __cplusplus
extern "C" {
#endif
;end_both

#define AccFree LocalFree

//
// Definition:
// This enumerated type defines the objects supported by the get/set API within
// this document.  See section 3.1, Object Types for a detailed definition of the
// supported object types, and their name formats.
//
typedef enum _SE_OBJECT_TYPE
{
    SE_UNKNOWN_OBJECT_TYPE = 0,
    SE_FILE_OBJECT,
    SE_SERVICE,
    SE_PRINTER,
    SE_REGISTRY_KEY,
    SE_LMSHARE,
    SE_KERNEL_OBJECT,
    SE_WINDOW_OBJECT,
    SE_DS_OBJECT,
    SE_DS_OBJECT_ALL,
    SE_PROVIDER_DEFINED_OBJECT,
    SE_WMIGUID_OBJECT
} SE_OBJECT_TYPE;

//
// Definition: TRUSTEE_TYPE
// This enumerated type specifies the type of trustee account for the trustee
// returned by the API described in this document.
// TRUSTEE_IS_UNKNOWN - The trustee is an unknown, but not necessarily invalid
//                      type.  This field is not validated on input to the APIs
//                      that take Trustees.
// TRUSTEE_IS_USER      The trustee account is a user account.
// TRUSTEE_IS_GROUP     The trustee account is a group account.
//

typedef enum _TRUSTEE_TYPE
{
    TRUSTEE_IS_UNKNOWN,
    TRUSTEE_IS_USER,
    TRUSTEE_IS_GROUP,
    TRUSTEE_IS_DOMAIN,
    TRUSTEE_IS_ALIAS,
    TRUSTEE_IS_WELL_KNOWN_GROUP,
    TRUSTEE_IS_DELETED,
    TRUSTEE_IS_INVALID,
    TRUSTEE_IS_COMPUTER
} TRUSTEE_TYPE;


//
// Definition: TRUSTEE_FORM
// This enumerated type specifies the form the trustee identifier is in for a
// particular trustee.
// TRUSTEE_IS_SID       The trustee is identified with a SID rather than with a name.
// TRUSTEE_IS_NAME      The trustee is identified with a name.
//

typedef enum _TRUSTEE_FORM
{
    TRUSTEE_IS_SID,
    TRUSTEE_IS_NAME,
    TRUSTEE_BAD_FORM,
    TRUSTEE_IS_OBJECTS_AND_SID,
    TRUSTEE_IS_OBJECTS_AND_NAME
} TRUSTEE_FORM;


//
// Definition: MULTIPLE_TRUSTEE_OPERATION
// If the trustee is a multiple trustee, this enumerated type specifies the type.
// TRUSTEE_IS_IMPERSONATE       The trustee is an impersonate trustee and the multiple
//                          trustee field in the trustee points to another trustee
//                          that is a trustee for the server that will be doing the
//                          impersonation.
//

typedef enum _MULTIPLE_TRUSTEE_OPERATION
{
    NO_MULTIPLE_TRUSTEE,
    TRUSTEE_IS_IMPERSONATE,
} MULTIPLE_TRUSTEE_OPERATION;


typedef struct  _OBJECTS_AND_SID
{
    DWORD   ObjectsPresent;
    GUID    ObjectTypeGuid;
    GUID    InheritedObjectTypeGuid;
    SID     * pSid;
} OBJECTS_AND_SID, *POBJECTS_AND_SID;

typedef struct  _OBJECTS_AND_NAME_%
{
    DWORD          ObjectsPresent;
    SE_OBJECT_TYPE ObjectType;
    LPTSTR%  ObjectTypeName;
    LPTSTR%  InheritedObjectTypeName;
    LPTSTR%  ptstrName;
} OBJECTS_AND_NAME_%, *POBJECTS_AND_NAME_%;

//
// Definition: TRUSTEE
// This structure is used to pass account information into and out of the system
// using the API defined in this document.
// PMultipleTrustee     - if NON-NULL, points to another trustee structure, as
//                    defined by the multiple trustee operation field.
// MultipleTrusteeOperation - Defines the multiple trustee operation/type.
// TrusteeForm - defines if the trustee is defined by name or SID.
// TrusteeType - defines if the trustee type is unknown, a user or a group.
// PwcsName     - points to the trustee name or the trustee SID.
//

typedef struct _TRUSTEE_%
{
    struct _TRUSTEE_%          *pMultipleTrustee;
    MULTIPLE_TRUSTEE_OPERATION  MultipleTrusteeOperation;
    TRUSTEE_FORM                TrusteeForm;
    TRUSTEE_TYPE                TrusteeType;
#ifdef __midl
    [switch_is(TrusteeForm)]
    union
    {
    [case(TRUSTEE_IS_NAME)]
        LPTSTR%                 ptstrName;
    [case(TRUSTEE_IS_SID)]
        SID                    *pSid;
    [case(TRUSTEE_IS_OBJECTS_AND_SID)]
        OBJECTS_AND_SID        *pObjectsAndSid;
    [case(TRUSTEE_IS_OBJECTS_AND_NAME)]
        OBJECTS_AND_NAME_%     *pObjectsAndName;
    };
#else
    LPTSTR%                     ptstrName;
#endif
} TRUSTEE_%, *PTRUSTEE_%, TRUSTEE%, *PTRUSTEE%;

//
// Definition: ACCESS_MODE
// This enumerated type specifies how permissions are (requested)/to be applied
//  for the trustee by the access control entry.  On input this field can by any
//  of the values, although it is not meaningful to mix access control and audit
//  control entries.  On output this field will be either SET_ACCESS, DENY_ACCESS,
// SET_AUDIT_SUCCESS, SET_AUDIT_FAILURE.
// The following descriptions define how this type effects an explicit access
// request to apply access permissions to an object.
// GRANT_ACCESS - The trustee will have at least the requested permissions upon
//                successful completion of the command. (If the trustee has
//                additional permissions they will not be removed).
// SET_ACCESS - The trustee will have exactly the requested permissions upon
//              successful completion of the command.
// DENY_ACCESS - The trustee will be denied the specified permissions.
// REVOKE_ACCESS - Any explicit access rights the trustee has will be revoked.
// SET_AUDIT_SUCCESS - The trustee will be audited for successful opens of the
//                     object using the requested permissions.
// SET_AUDIT_FAILURE - The trustee will be audited for failed opens of the object
//                     using the requested permissions.
//

typedef enum _ACCESS_MODE
{
    NOT_USED_ACCESS = 0,
    GRANT_ACCESS,
    SET_ACCESS,
    DENY_ACCESS,
    REVOKE_ACCESS,
    SET_AUDIT_SUCCESS,
    SET_AUDIT_FAILURE
} ACCESS_MODE;

//
// Definition: Inheritance flags
// These bit masks are provided to allow simple application of inheritance in
// explicit access requests on containers.
// NO_INHERITANCE       The specific access permissions will only be applied to
//                  the container, and will not be inherited by objects created
//                  within the container.
// SUB_CONTAINERS_ONLY_INHERIT  The specific access permissions will be inherited
//                              and applied to sub containers created within the
//                              container, and will be applied to the container
//                              itself.
// SUB_OBJECTS_ONLY_INHERIT     The specific access permissions will only be inherited
//                              by objects created within the specific container.
//                              The access permissions will not be applied to the
//                              container itself.
// SUB_CONTAINERS_AND_OBJECTS_INHERIT   The specific access permissions will be
//                                      inherited by containers created within the
//                                      specific container, will be applied to
//                                      objects created within the container, but
//                                      will not be applied to the container itself.
//
#define NO_INHERITANCE 0x0
#define SUB_OBJECTS_ONLY_INHERIT            0x1
#define SUB_CONTAINERS_ONLY_INHERIT         0x2
#define SUB_CONTAINERS_AND_OBJECTS_INHERIT  0x3
#define INHERIT_NO_PROPAGATE                0x4
#define INHERIT_ONLY                        0x8

//
// Informational bit that is returned
//
#define INHERITED_ACCESS_ENTRY              0x10

//
// Informational bit that tells where a node was inherited from.  Valid only
// for NT 5 APIs
//
#define INHERITED_PARENT                    0x10000000
#define INHERITED_GRANDPARENT               0x20000000


//
// Definition: EXPLICIT_ACCESS
// This structure is used to pass access control entry information into and out
// of the system using the API defined in this document.
// grfAccessPermissions - This contains the access permissions to assign for the
//                     trustee.  It is in the form of an NT access mask.
// grfAccessMode - This field defines how the permissions are to be applied for
//                 the trustee.
// grfInheritance - For containers, this field defines how the access control
//                  entry is/(is requested) to be inherited on
//                  objects/sub-containers created within the container.
// Trustee - This field contains the definition of the trustee account the
//           explicit access applies to.
//

typedef struct _EXPLICIT_ACCESS_%
{
    DWORD        grfAccessPermissions;
    ACCESS_MODE  grfAccessMode;
    DWORD        grfInheritance;
    TRUSTEE_%    Trustee;
} EXPLICIT_ACCESS_%, *PEXPLICIT_ACCESS_%, EXPLICIT_ACCESS%, *PEXPLICIT_ACCESS%;



//----------------------------------------------------------------------------
//
//                                  NT5 APIs
//
//----------------------------------------------------------------------------

//
// Default provider
//
#define ACCCTRL_DEFAULT_PROVIDERA   "Windows NT Access Provider"
#define ACCCTRL_DEFAULT_PROVIDERW  L"Windows NT Access Provider"

#ifdef UNICODE
#define ACCCTRL_DEFAULT_PROVIDER ACCCTRL_DEFAULT_PROVIDERW
#else
#define ACCCTRL_DEFAULT_PROVIDER ACCCTRL_DEFAULT_PROVIDERA
#endif




//
/// Access rights
//
typedef     ULONG   ACCESS_RIGHTS, *PACCESS_RIGHTS;

//
// Inheritance flags
//
typedef ULONG INHERIT_FLAGS, *PINHERIT_FLAGS;


//
// Access / Audit structures
//
typedef struct _ACTRL_ACCESS_ENTRY%
{
    TRUSTEE_%       Trustee;
    ULONG           fAccessFlags;
    ACCESS_RIGHTS   Access;
    ACCESS_RIGHTS   ProvSpecificAccess;
    INHERIT_FLAGS   Inheritance;
    LPTSTR%         lpInheritProperty;
} ACTRL_ACCESS_ENTRY%, *PACTRL_ACCESS_ENTRY%;



typedef struct _ACTRL_ACCESS_ENTRY_LIST%
{
    ULONG                   cEntries;
#ifdef __midl
    [size_is(cEntries)]
#endif
    ACTRL_ACCESS_ENTRY%    *pAccessList;
} ACTRL_ACCESS_ENTRY_LIST%, *PACTRL_ACCESS_ENTRY_LIST%;



typedef struct _ACTRL_PROPERTY_ENTRY%
{
    LPTSTR%                     lpProperty;
    PACTRL_ACCESS_ENTRY_LIST%   pAccessEntryList;
    ULONG                       fListFlags;
} ACTRL_PROPERTY_ENTRY%, *PACTRL_PROPERTY_ENTRY%;



typedef struct _ACTRL_ALIST%
{
    ULONG                       cEntries;
#ifdef __midl
    [size_is(cEntries)]
#endif
    PACTRL_PROPERTY_ENTRY%      pPropertyAccessList;
} ACTRL_ACCESS%, *PACTRL_ACCESS%, ACTRL_AUDIT%, *PACTRL_AUDIT%;



//
// TRUSTEE_ACCESS flags
//
#define TRUSTEE_ACCESS_ALLOWED      0x00000001L
#define TRUSTEE_ACCESS_READ         0x00000002L
#define TRUSTEE_ACCESS_WRITE        0x00000004L

#define TRUSTEE_ACCESS_EXPLICIT     0x00000001L
#define TRUSTEE_ACCESS_READ_WRITE   (TRUSTEE_ACCESS_READ |                  \
                                     TRUSTEE_ACCESS_WRITE)


#define TRUSTEE_ACCESS_ALL          0xFFFFFFFFL

typedef struct _TRUSTEE_ACCESS%
{
    LPTSTR%         lpProperty;
    ACCESS_RIGHTS   Access;
    ULONG           fAccessFlags;
    ULONG           fReturnedAccess;
} TRUSTEE_ACCESS%, *PTRUSTEE_ACCESS%;



//
// Generic permission values
//
#define ACTRL_RESERVED          0x00000000
#define ACTRL_PERM_1            0x00000001
#define ACTRL_PERM_2            0x00000002
#define ACTRL_PERM_3            0x00000004
#define ACTRL_PERM_4            0x00000008
#define ACTRL_PERM_5            0x00000010
#define ACTRL_PERM_6            0x00000020
#define ACTRL_PERM_7            0x00000040
#define ACTRL_PERM_8            0x00000080
#define ACTRL_PERM_9            0x00000100
#define ACTRL_PERM_10           0x00000200
#define ACTRL_PERM_11           0x00000400
#define ACTRL_PERM_12           0x00000800
#define ACTRL_PERM_13           0x00001000
#define ACTRL_PERM_14           0x00002000
#define ACTRL_PERM_15           0x00004000
#define ACTRL_PERM_16           0x00008000
#define ACTRL_PERM_17           0x00010000
#define ACTRL_PERM_18           0x00020000
#define ACTRL_PERM_19           0x00040000
#define ACTRL_PERM_20           0x00080000

//
// Access permissions
//
#define ACTRL_ACCESS_ALLOWED        0x00000001
#define ACTRL_ACCESS_DENIED         0x00000002
#define ACTRL_AUDIT_SUCCESS         0x00000004
#define ACTRL_AUDIT_FAILURE         0x00000008

//
// Property list flags
//
#define ACTRL_ACCESS_PROTECTED      0x00000001

//
// Standard and object rights
//
#define ACTRL_SYSTEM_ACCESS         0x04000000
#define ACTRL_DELETE                0x08000000
#define ACTRL_READ_CONTROL          0x10000000
#define ACTRL_CHANGE_ACCESS         0x20000000
#define ACTRL_CHANGE_OWNER          0x40000000
#define ACTRL_SYNCHRONIZE           0x80000000
#define ACTRL_STD_RIGHTS_ALL        0xf8000000
#define ACTRL_STD_RIGHT_REQUIRED    ( ACTRL_STD_RIGHTS_ALL & ~ACTRL_SYNCHRONIZE )

#ifndef _DS_CONTROL_BITS_DEFINED_
#define _DS_CONTROL_BITS_DEFINED_
#define ACTRL_DS_OPEN                           ACTRL_RESERVED
#define ACTRL_DS_CREATE_CHILD                   ACTRL_PERM_1
#define ACTRL_DS_DELETE_CHILD                   ACTRL_PERM_2
#define ACTRL_DS_LIST                           ACTRL_PERM_3
#define ACTRL_DS_SELF                           ACTRL_PERM_4
#define ACTRL_DS_READ_PROP                      ACTRL_PERM_5
#define ACTRL_DS_WRITE_PROP                     ACTRL_PERM_6
#define ACTRL_DS_DELETE_TREE                    ACTRL_PERM_7
#define ACTRL_DS_LIST_OBJECT                    ACTRL_PERM_8
#define ACTRL_DS_CONTROL_ACCESS                 ACTRL_PERM_9
#endif

#define ACTRL_FILE_READ                         ACTRL_PERM_1
#define ACTRL_FILE_WRITE                        ACTRL_PERM_2
#define ACTRL_FILE_APPEND                       ACTRL_PERM_3
#define ACTRL_FILE_READ_PROP                    ACTRL_PERM_4
#define ACTRL_FILE_WRITE_PROP                   ACTRL_PERM_5
#define ACTRL_FILE_EXECUTE                      ACTRL_PERM_6
#define ACTRL_FILE_READ_ATTRIB                  ACTRL_PERM_8
#define ACTRL_FILE_WRITE_ATTRIB                 ACTRL_PERM_9
#define ACTRL_FILE_CREATE_PIPE                  ACTRL_PERM_10
#define ACTRL_DIR_LIST                          ACTRL_PERM_1
#define ACTRL_DIR_CREATE_OBJECT                 ACTRL_PERM_2
#define ACTRL_DIR_CREATE_CHILD                  ACTRL_PERM_3
#define ACTRL_DIR_DELETE_CHILD                  ACTRL_PERM_7
#define ACTRL_DIR_TRAVERSE                      ACTRL_PERM_6
#define ACTRL_KERNEL_TERMINATE                  ACTRL_PERM_1
#define ACTRL_KERNEL_THREAD                     ACTRL_PERM_2
#define ACTRL_KERNEL_VM                         ACTRL_PERM_3
#define ACTRL_KERNEL_VM_READ                    ACTRL_PERM_4
#define ACTRL_KERNEL_VM_WRITE                   ACTRL_PERM_5
#define ACTRL_KERNEL_DUP_HANDLE                 ACTRL_PERM_6
#define ACTRL_KERNEL_PROCESS                    ACTRL_PERM_7
#define ACTRL_KERNEL_SET_INFO                   ACTRL_PERM_8
#define ACTRL_KERNEL_GET_INFO                   ACTRL_PERM_9
#define ACTRL_KERNEL_CONTROL                    ACTRL_PERM_10
#define ACTRL_KERNEL_ALERT                      ACTRL_PERM_11
#define ACTRL_KERNEL_GET_CONTEXT                ACTRL_PERM_12
#define ACTRL_KERNEL_SET_CONTEXT                ACTRL_PERM_13
#define ACTRL_KERNEL_TOKEN                      ACTRL_PERM_14
#define ACTRL_KERNEL_IMPERSONATE                ACTRL_PERM_15
#define ACTRL_KERNEL_DIMPERSONATE               ACTRL_PERM_16
#define ACTRL_PRINT_SADMIN                      ACTRL_PERM_1
#define ACTRL_PRINT_SLIST                       ACTRL_PERM_2
#define ACTRL_PRINT_PADMIN                      ACTRL_PERM_3
#define ACTRL_PRINT_PUSE                        ACTRL_PERM_4
#define ACTRL_PRINT_JADMIN                      ACTRL_PERM_5
#define ACTRL_SVC_GET_INFO                      ACTRL_PERM_1
#define ACTRL_SVC_SET_INFO                      ACTRL_PERM_2
#define ACTRL_SVC_STATUS                        ACTRL_PERM_3
#define ACTRL_SVC_LIST                          ACTRL_PERM_4
#define ACTRL_SVC_START                         ACTRL_PERM_5
#define ACTRL_SVC_STOP                          ACTRL_PERM_6
#define ACTRL_SVC_PAUSE                         ACTRL_PERM_7
#define ACTRL_SVC_INTERROGATE                   ACTRL_PERM_8
#define ACTRL_SVC_UCONTROL                      ACTRL_PERM_9
#define ACTRL_REG_QUERY                         ACTRL_PERM_1
#define ACTRL_REG_SET                           ACTRL_PERM_2
#define ACTRL_REG_CREATE_CHILD                  ACTRL_PERM_3
#define ACTRL_REG_LIST                          ACTRL_PERM_4
#define ACTRL_REG_NOTIFY                        ACTRL_PERM_5
#define ACTRL_REG_LINK                          ACTRL_PERM_6
#define ACTRL_WIN_CLIPBRD                       ACTRL_PERM_1
#define ACTRL_WIN_GLOBAL_ATOMS                  ACTRL_PERM_2
#define ACTRL_WIN_CREATE                        ACTRL_PERM_3
#define ACTRL_WIN_LIST_DESK                     ACTRL_PERM_4
#define ACTRL_WIN_LIST                          ACTRL_PERM_5
#define ACTRL_WIN_READ_ATTRIBS                  ACTRL_PERM_6
#define ACTRL_WIN_WRITE_ATTRIBS                 ACTRL_PERM_7
#define ACTRL_WIN_SCREEN                        ACTRL_PERM_8
#define ACTRL_WIN_EXIT                          ACTRL_PERM_9




typedef struct _ACTRL_OVERLAPPED
{
    union {
        PVOID Provider;
        ULONG Reserved1;
    };

    ULONG       Reserved2;
    HANDLE      hEvent;

} ACTRL_OVERLAPPED, *PACTRL_OVERLAPPED;

typedef struct _ACTRL_ACCESS_INFO%
{
    ULONG       fAccessPermission;
    LPTSTR%     lpAccessPermissionName;
} ACTRL_ACCESS_INFO%, *PACTRL_ACCESS_INFO%;

typedef struct _ACTRL_CONTROL_INFO%
{
    LPTSTR%     lpControlId;
    LPTSTR%     lpControlName;
} ACTRL_CONTROL_INFO%, *PACTRL_CONTROL_INFO%;


#define ACTRL_ACCESS_NO_OPTIONS                 0x00000000
#define ACTRL_ACCESS_SUPPORTS_OBJECT_ENTRIES    0x00000001


#ifdef __cplusplus      ;both
}                       ;both
#endif                  ;both


#endif // __ACCESS_CONTROL__
