/*++

Copyright (C) 1999 Microsoft Corporation

Module Name:

    OBJPATH.H

Abstract:

    object path parser

History:

--*/

#ifndef _OBJPATH_H_
#define _OBJPATH_H_

#include <opathlex.h>

#define DELETE_ME

struct KeyRef
{
    LPWSTR  m_pName;
    VARIANT m_vValue;

    KeyRef();
    KeyRef(LPCWSTR wszKeyName, const VARIANT* pvValue);
   ~KeyRef();
};

struct ParsedObjectPath
{
    LPWSTR      m_pServer;              // NULL if no server
    DWORD       m_dwNumNamespaces;      // 0 if no namespaces
    DWORD       m_dwAllocNamespaces;    // size of m_paNamespaces
    LPWSTR     *m_paNamespaces;         // NULL if no namespaces
    LPWSTR      m_pClass;               // Class name
    DWORD       m_dwNumKeys;            // 0 if no keys (just a class name)
    DWORD       m_dwAllocKeys;          // size of m_paKeys
    KeyRef    **m_paKeys;               // NULL if no keys specified
    BOOL        m_bSingletonObj;        // true if object of class with no keys
    ParsedObjectPath();
   ~ParsedObjectPath();

public:
    BOOL SetClassName(LPCWSTR wszClassName);
    BOOL AddKeyRef(LPCWSTR wszKeyName, const VARIANT* pvValue);
    BOOL AddKeyRef(KeyRef* pAcquireRef);
    BOOL AddKeyRefEx(LPCWSTR wszKeyName, const VARIANT* pvValue);
    BOOL AddNamespace(LPCWSTR wszNamespace);
    LPWSTR GetKeyString();
    LPWSTR GetNamespacePart();
    LPWSTR GetParentNamespacePart();
    void ClearKeys () ;
    BOOL IsRelative(LPCWSTR wszMachine, LPCWSTR wszNamespace);
    BOOL IsLocal(LPCWSTR wszMachine);
    BOOL IsClass();
    BOOL IsInstance();
    BOOL IsObject();
};

// NOTE:
// The m_vValue in the KeyRef may not be of the expected type, i.e., the parser
// cannot distinguish 16 bit integers from 32 bit integers if they fall within the
// legal subrange of a 16 bit value.  Therefore, the parser only uses the following
// types for keys:
//      VT_I4, VT_R8, VT_BSTR
// If the underlying type is different, the user of this parser must do appropriate
// type conversion.
//  
typedef enum
{
    e_ParserAcceptRelativeNamespace,    // Allow a relative namespace
    e_ParserAbsoluteNamespaceOnly,      // Require a full object path
    e_ParserAcceptAll                   // Accept any recognizable subset of a path
} ObjectParserFlags;

class CObjectPathParser
{
    LPWSTR m_pInitialIdent;
    int m_nCurrentToken;
    CGenLexer *m_pLexer;
    ParsedObjectPath *m_pOutput;
    KeyRef *m_pTmpKeyRef;
    
    ObjectParserFlags m_eFlags;

private:
    void Zero();
    void Empty();

    int begin_parse();

    int ns_or_server();
    int ns_or_class();
    int objref();
    int ns_list();
    int ident_becomes_ns();
    int ident_becomes_class();
    int objref_rest();
    int ns_list_rest();
    int key_const();
    int keyref_list();
    int keyref();
    int keyref_term();
    int propname();    
    int optional_objref();

    int NextToken();

public:
    enum { NoError, SyntaxError, InvalidParameter, OutOfMemory };

    CObjectPathParser(ObjectParserFlags eFlags = e_ParserAbsoluteNamespaceOnly);
   ~CObjectPathParser();

    int Parse(
        LPCWSTR RawPath,
        ParsedObjectPath **pOutput
        );
    static int WINAPI Unparse(
        ParsedObjectPath* pInput,
        DELETE_ME LPWSTR* pwszPath);

    static LPWSTR WINAPI GetRelativePath(LPWSTR wszFullPath);

    void Free(ParsedObjectPath *pOutput);
    void Free( LPWSTR wszUnparsedPath );
};

#endif
