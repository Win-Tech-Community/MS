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
/***
*rtti.cpp - C++ runtime type information
*
*
*Purpose:
*       Implementation of C++ standard runtime type information
*
****/

extern "C" {
#include <windows.h>
};

#include <stdio.h>
#include <typeinfo>
#include <rtti.h>

static PVOID __cdecl FindCompleteObject(PVOID *);
static _RTTIBaseClassDescriptor * __cdecl FindSITargetTypeInstance(PVOID,_RTTICompleteObjectLocator *,_RTTITypeDescriptor *,int,_RTTITypeDescriptor *);
static _RTTIBaseClassDescriptor * __cdecl FindMITargetTypeInstance(PVOID,_RTTICompleteObjectLocator *,_RTTITypeDescriptor *,int,_RTTITypeDescriptor *);
static _RTTIBaseClassDescriptor * __cdecl FindVITargetTypeInstance(PVOID,_RTTICompleteObjectLocator *,_RTTITypeDescriptor *,int,_RTTITypeDescriptor *);
static ptrdiff_t __cdecl PMDtoOffset(PVOID, const PMD&);


/////////////////////////////////////////////////////////////////////////////
//
// __RTCastToVoid - Implements dynamic_cast<void*>
//
// Output: Pointer to complete object containing *inptr
//
// Side-effects: NONE.
//

extern "C" PVOID __cdecl __RTCastToVoid (PVOID inptr)                   // Pointer to polymorphic object
{

    if (inptr == NULL)
        return NULL;

    __try {
        return FindCompleteObject((PVOID *)inptr);
    }
    __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER: EXCEPTION_CONTINUE_SEARCH) {
        throw std::__non_rtti_object ("Access violation - no RTTI data!");
    }
}


/////////////////////////////////////////////////////////////////////////////
//
// __RTtypeid - Implements typeid() operator
//
// Output: Pointer to type descriptor of complete object containing *inptr
//
// Side-effects: NONE.
//

extern "C" PVOID __cdecl __RTtypeid (PVOID inptr)               // Pointer to polymorphic object
{

    if (!inptr) {
        throw std::bad_typeid ("Attempted a typeid of NULL pointer!");          // WP 5.2.7
    }

    __try {
        // Ptr to CompleteObjectLocator should be stored at vfptr[-1]
        _RTTICompleteObjectLocator *pCompleteLocator = (_RTTICompleteObjectLocator *) ((*((void***)inptr))[-1]);

#if 0
        if (!IsBadReadPtr((const void *)pCompleteLocator->pTypeDescriptor, sizeof(TypeDescriptor))) {
            return (PVOID) pCompleteLocator->pTypeDescriptor;
        }
        else {
            throw std::__non_rtti_object ("Bad read pointer - no RTTI data!");
            return NULL;
        }
#else
        return (PVOID) pCompleteLocator->pTypeDescriptor;
#endif
    }
    __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER: EXCEPTION_CONTINUE_SEARCH) {
        throw std::__non_rtti_object ("Access violation - no RTTI data!");
    }
}


/////////////////////////////////////////////////////////////////////////////
//
// __RTDynamicCast - Runtime implementation of dynamic_cast<> operator
//
// Output: Pointer to the appropriate sub-object, if possible; NULL otherwise
//
// Side-effects: Throws bad_cast() if cast fails & input of dynamic_cast<> is a reference
//

extern "C" PVOID __cdecl __RTDynamicCast (
                                        PVOID inptr,                                    // Pointer to polymorphic object
                                        LONG VfDelta,                                   // Offset of vfptr in object
                                        PVOID SrcType,                                  // Static type of object pointed to by inptr
                                        PVOID TargetType,                               // Desired result of cast
                                        BOOL isReference)                               // TRUE if input is reference, FALSE if input is ptr
{
    PVOID pResult = NULL;
    _RTTIBaseClassDescriptor *pBaseClass;

    if (inptr == NULL)
        return NULL;

    __try {
        PVOID pCompleteObject = FindCompleteObject((PVOID *)inptr);
        _RTTICompleteObjectLocator *pCompleteLocator = (_RTTICompleteObjectLocator *) ((*((void***)inptr))[-1]);

        // Adjust by vfptr displacement, if any
        inptr = (PVOID *) ((char *)inptr - VfDelta);
        // Calculate offset of source object in complete object
        int inptr_delta = (char *)inptr - (char *)pCompleteObject;

        if (!(CHD_ATTRIBUTES(*COL_PCHD(*pCompleteLocator)) & CHD_MULTINH)) {             // if not multiple inheritance
            pBaseClass = FindSITargetTypeInstance(pCompleteObject,
                                                  pCompleteLocator,
                                                  (_RTTITypeDescriptor *) SrcType,
                                                  inptr_delta,
                                                  (_RTTITypeDescriptor *) TargetType);
        } else if (!(CHD_ATTRIBUTES(*COL_PCHD(*pCompleteLocator)) & CHD_VIRTINH)) { // if multiple, but not virtual, inheritance
            pBaseClass = FindMITargetTypeInstance(pCompleteObject,
                                                  pCompleteLocator,
                                                  (_RTTITypeDescriptor *) SrcType,
                                                  inptr_delta,
                                                  (_RTTITypeDescriptor *) TargetType);
        } else {                                                                   // if virtual inheritance
            pBaseClass = FindVITargetTypeInstance(pCompleteObject,
                                                  pCompleteLocator,
                                                  (_RTTITypeDescriptor *) SrcType,
                                                  inptr_delta,
                                                  (_RTTITypeDescriptor *) TargetType);
        }

        if (pBaseClass != NULL) {
            // Calculate ptr to result base class from pBaseClass->where
            pResult = ((char *) pCompleteObject) + PMDtoOffset(pCompleteObject, pBaseClass->where);
        }else {
            pResult = NULL;
            if (isReference) {
                throw std::bad_cast("Bad dynamic_cast!");
            }
        }

    }
    __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER: EXCEPTION_CONTINUE_SEARCH) {
        pResult = NULL;
        throw std::__non_rtti_object ("Access violation - no RTTI data!");
    }

    return pResult;

}

/////////////////////////////////////////////////////////////////////////////
//
// FindCompleteObject - Calculate member offset from PMD & this
//
// Output: pointer to the complete object containing class *inptr
//
// Side-effects: NONE.
//

static PVOID __cdecl FindCompleteObject (PVOID *inptr)          // Pointer to polymorphic object
{
    // Ptr to CompleteObjectLocator should be stored at vfptr[-1]
    _RTTICompleteObjectLocator *pCompleteLocator = (_RTTICompleteObjectLocator *) ((*((void***)inptr))[-1]);
    char *pCompleteObject = (char *)inptr - pCompleteLocator->offset;
    // Adjust by construction displacement, if any
    if (pCompleteLocator->cdOffset)
        pCompleteObject += *(ptrdiff_t *)((char *)inptr - pCompleteLocator->cdOffset);
    return (PVOID) pCompleteObject;
}


/////////////////////////////////////////////////////////////////////////////
//
// FindSITargetTypeInstance - workhorse routine of __RTDynamicCast() in a Single-Inheritance hierarchy
//
// Output: pointer to the appropriate sub-object of targetted type; NULL if cast fails
//
// Side-effects: NONE.
//

static _RTTIBaseClassDescriptor * __cdecl FindSITargetTypeInstance (
                                PVOID pCompleteObject,                          // pointer to complete object
                                _RTTICompleteObjectLocator *pCOLocator, // pointer to Locator of complete object
                                _RTTITypeDescriptor *pSrcTypeID,        // pointer to TypeDescriptor of source object
                                int SrcOffset,                                          // offset of source object in complete object
                                _RTTITypeDescriptor *pTargetTypeID)     // pointer to TypeDescriptor of result of cast
{
    _RTTIBaseClassDescriptor *pBase;
    _RTTIBaseClassDescriptor * const *pBasePtr;
    DWORD i;

    for (i = 0, pBasePtr = pCOLocator->pClassDescriptor->pBaseClassArray->arrayOfBaseClassDescriptors;
         i < pCOLocator->pClassDescriptor->numBaseClasses;
         i++, pBasePtr++) {

        // Test type of selected base class
        pBase = *pBasePtr;
        if (TYPEIDS_EQ(pBase->pTypeDescriptor, pTargetTypeID) &&
            !(BCD_ATTRIBUTES(*pBase) & BCD_NOTVISIBLE)) {
            return pBase;
        }
    }
    return NULL;
}


/////////////////////////////////////////////////////////////////////////////
//
// FindMITargetTypeInstance - workhorse routine of __RTDynamicCast() in a Multiple-Inheritance hierarchy
//
// Output: pointer to the appropriate sub-object of targetted type; NULL if cast fails
//
// Side-effects: NONE.
//

static _RTTIBaseClassDescriptor * __cdecl FindMITargetTypeInstance (
                                PVOID pCompleteObject,                          // pointer to complete object
                                _RTTICompleteObjectLocator *pCOLocator, // pointer to Locator of complete object
                                _RTTITypeDescriptor *pSrcTypeID,        // pointer to TypeDescriptor of source object
                                int SrcOffset,                                          // offset of source object in complete object
                                _RTTITypeDescriptor *pTargetTypeID)     // pointer to TypeDescriptor of result of cast
{
    _RTTIBaseClassDescriptor *pBase, *pSubBase;
    _RTTIBaseClassDescriptor * const *pBasePtr, * const *pSubBasePtr;
    DWORD i, j;

                                // First, try down-casts
    for (i = 0, pBasePtr = pCOLocator->pClassDescriptor->pBaseClassArray->arrayOfBaseClassDescriptors;
         i < pCOLocator->pClassDescriptor->numBaseClasses;
         i++, pBasePtr++) {
        
        pBase = *pBasePtr;
                                // Test type of selected base class
        if (TYPEIDS_EQ(pBase->pTypeDescriptor, pTargetTypeID)) {
                                // If base class is proper type, see if it contains our instance of source class
            for (j = 0, pSubBasePtr = pBasePtr+1;
                 j < pBase->numContainedBases;
                 j++, pSubBasePtr++) {

                pSubBase = *pSubBasePtr;
                if (TYPEIDS_EQ(pSubBase->pTypeDescriptor, pSrcTypeID) &&
                    (PMDtoOffset(pCompleteObject, pSubBase->where) == SrcOffset)) {
                                // Yes, this is the proper instance of source class
                    return pBase;
                }
            }
        }
    }

                                // Down-cast failed, try cross-cast
    for (i = 0, pBasePtr = pCOLocator->pClassDescriptor->pBaseClassArray->arrayOfBaseClassDescriptors;
         i < pCOLocator->pClassDescriptor->numBaseClasses;
         i++, pBasePtr++) {

        pBase = *pBasePtr;
                                // Check if base class has proper type, is accessible & is unambiguous
        if (TYPEIDS_EQ(pBase->pTypeDescriptor, pTargetTypeID) &&
            !(BCD_ATTRIBUTES(*pBase) & BCD_NOTVISIBLE) &&
            !(BCD_ATTRIBUTES(*pBase) & BCD_AMBIGUOUS)) {
            return pBase;
        }
    }

    return NULL;
}


/////////////////////////////////////////////////////////////////////////////
//
// FindVITargetTypeInstance - workhorse routine of __RTDynamicCast() in a Virtual-Inheritance hierarchy
//
// Output: pointer to the appropriate sub-object of targetted type; NULL if cast fails
//
// Side-effects: NONE.
//

static _RTTIBaseClassDescriptor * __cdecl FindVITargetTypeInstance (
                                PVOID pCompleteObject,                          // pointer to complete object
                                _RTTICompleteObjectLocator *pCOLocator, // pointer to Locator of complete object
                                _RTTITypeDescriptor *pSrcTypeID,        // pointer to TypeDescriptor of source object
                                int SrcOffset,                                          // offset of source object in complete object
                                _RTTITypeDescriptor *pTargetTypeID)     // pointer to TypeDescriptor of result of cast
{
    _RTTIBaseClassDescriptor *pBase, *pSubBase;
    _RTTIBaseClassDescriptor * const *pBasePtr, * const *pSubBasePtr;
    _RTTIBaseClassDescriptor *pResult = NULL;
    DWORD i, j;

                                // First, try down-casts
    for (i = 0, pBasePtr = pCOLocator->pClassDescriptor->pBaseClassArray->arrayOfBaseClassDescriptors;
         i < pCOLocator->pClassDescriptor->numBaseClasses;
         i++, pBasePtr++) {
        
        pBase = *pBasePtr;
                                // Test type of selected base class
        if (TYPEIDS_EQ(pBase->pTypeDescriptor, pTargetTypeID)) {
                                // If base class is proper type, see if it contains our instance of source class
            for (j = 0, pSubBasePtr = pBasePtr+1;
                 j < pBase->numContainedBases;
                 j++, pSubBasePtr++) {

                pSubBase = *pSubBasePtr;
                if (TYPEIDS_EQ(pSubBase->pTypeDescriptor, pSrcTypeID) &&
                    (PMDtoOffset(pCompleteObject, pSubBase->where) == SrcOffset)) {
                                // Yes, this is the proper instance of source class - make sure it is unambiguous
                                // Ambiguity now determined by inequality of offsets of source class within complete object, not pointer inequality
                    if ((pResult != NULL) && (PMDtoOffset(pCompleteObject, pResult->where) != PMDtoOffset(pCompleteObject, pBase->where))) {
                                // We already found an earlier instance, hence ambiguity
                        return NULL;
                    }
                    else {
                                // Unambiguous
                        pResult = pBase;
                    }
                }
            }
        }
    }

    if (pResult != NULL)
        return pResult;

                                // Down-cast failed, try cross-cast
    for (i = 0, pBasePtr = pCOLocator->pClassDescriptor->pBaseClassArray->arrayOfBaseClassDescriptors;
         i < pCOLocator->pClassDescriptor->numBaseClasses;
         i++, pBasePtr++) {

        pBase = *pBasePtr;
                                // Check if base class has proper type, is accessible & is unambiguous
        if (TYPEIDS_EQ(pBase->pTypeDescriptor, pTargetTypeID) &&
            !(BCD_ATTRIBUTES(*pBase) & BCD_NOTVISIBLE) &&
            !(BCD_ATTRIBUTES(*pBase) & BCD_AMBIGUOUS)) {
            return pBase;

        }
    }

    return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//
// PMDtoOffset - Calculate member offset from PMD & this
//
// Output: The offset of the base within the complete object.
//
// Side-effects: NONE.
//


static ptrdiff_t __cdecl PMDtoOffset(
                                PVOID pThis,                    // ptr to complete object
                                const PMD& pmd)                 // pointer-to-member-data structure
{
    ptrdiff_t RetOff = 0;

    if (pmd.pdisp >= 0) {                       // if base is in the virtual part of class
        RetOff = pmd.pdisp;
        RetOff += *(ptrdiff_t*)((char*)*(ptrdiff_t*)((char*)pThis + RetOff) + pmd.vdisp);
    }

    RetOff += pmd.mdisp;

    return RetOff;
}
