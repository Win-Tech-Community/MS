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
// ----------------------------------------------------------------------------
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
// ----------------------------------------------------------------------------
//
// Definitions and declarations for the WLANPolicyNetwork_t class.
//
// ----------------------------------------------------------------------------

#ifndef _DEFINED_WLANPolicyNetwork_t_
#define _DEFINED_WLANPolicyNetwork_t_
#pragma once

#include "WLANTypes.hpp"
#if (WLAN_VERSION > 0)

#include <wlanapi.h>

namespace litexml
{
    class XmlElement_t;
};

namespace ce {
namespace qa {

// ----------------------------------------------------------------------------
//
// Represents a single network name and/or type in a WLAN policy
// network-filter list.
//
class WLANPolicyNetwork_t
{
private:
    
    // Network name (wide characters):
    //
    WCHAR m_WCName[DOT11_SSID_MAX_LENGTH+1];
    DWORD m_WCLength;

    // Network name (multi-byte characters):
    //
    char  m_MBName[DOT11_SSID_MAX_LENGTH+1];
    DWORD m_MBLength;
    
    // Network type:
    //
    static const DOT11_BSS_TYPE sm_DefNetworkType = dot11_BSS_type_any;
    DOT11_BSS_TYPE m_Type;

public:

    // Constructor:
    //
    WLANPolicyNetwork_t(void) { Clear(); }
    void
    Clear(void);

    // Converts the network name to or from WLAN format:
    //
    void
    ToDot11Name(
        DOT11_SSID *pDot11);
    void
    FromDot11Name(
        const DOT11_SSID &Dot11);

    // Network name:
    //
    const TCHAR *
    GetName(void) const
    {
#ifdef UNICODE
        return m_WCName;
#else
        return m_MBName;
#endif
    }
    DWORD
    GetNameLength(void) const
    {
#ifdef UNICODE
        return m_WCLength;
#else
        return m_MBLength;
#endif
    }
    
    const WCHAR *
    GetWCName(void) const { return m_WCName; }
    DWORD
    GetWCNameLength(void) const { return m_WCLength; }
    
    const char *
    GetMBName(void) const { return m_MBName; }
    DWORD
    GetMBNameLength(void) const { return m_MBLength; }
    
    void
    SetName(
        const BYTE *pName,
        DWORD        NameChars);    
    void
    SetName(
        const WCHAR *pName,
        int           NameChars = -1);    
    void
    SetName(
        const char *pName,
        int          NameChars = -1);
    
    // Network type:
    //
    DOT11_BSS_TYPE
    GetType(void) const { return m_Type; }
    void
    SetType(DOT11_BSS_TYPE Type) { m_Type = Type; }

  // XML encoding/decoding:

    // XML tags:
    //
    static const WCHAR XmlTagName[];
    static const WCHAR XmlNamespace[];

    // Encodes the object into a DOM element:
    //
    HRESULT
    EncodeToXml(
        litexml::XmlElement_t **ppRoot,
        const TCHAR            *pNamespace = XmlNamespace) const;

    // Initializes the object from the specified DOM element:
    //
    HRESULT
    DecodeFromXml(
        const litexml::XmlElement_t &Root);
    
};

};
};

#endif /* if (WLAN_VERSION > 0) */
#endif /* _DEFINED_WLANPolicyNetwork_t_ */
// ----------------------------------------------------------------------------
