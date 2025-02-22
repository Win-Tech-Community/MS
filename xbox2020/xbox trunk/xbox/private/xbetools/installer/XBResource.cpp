//-----------------------------------------------------------------------------
// File: XBResource.cpp
//
// Desc: Loads resources from an XPR (Xbox Packed Resource) file.  
//
// Hist: 03.12.01 - New for April XDK release
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <xtl.h>
#include <xgraphics.h>
#include <stdio.h>
#include "XBUtil.h"
#include "XBResource.h"




//-----------------------------------------------------------------------------
// Name: XBResource_SizeOf()
// Desc: Determines the byte size of a D3DResource
//-----------------------------------------------------------------------------
DWORD XBResource_SizeOf( LPDIRECT3DRESOURCE8 pResource )
{
    switch( pResource->GetType() )
    {
        case D3DRTYPE_TEXTURE:       return sizeof(D3DTexture);
        case D3DRTYPE_VOLUMETEXTURE: return sizeof(D3DVolumeTexture);
        case D3DRTYPE_CUBETEXTURE:   return sizeof(D3DCubeTexture);
        case D3DRTYPE_VERTEXBUFFER:  return sizeof(D3DVertexBuffer);
        case D3DRTYPE_INDEXBUFFER:   return sizeof(D3DIndexBuffer);
        case D3DRTYPE_PALETTE:       return sizeof(D3DPalette);
    }
    return 0;
}




//-----------------------------------------------------------------------------
// Name: CXBPackedResource()
// Desc: Constructor
//-----------------------------------------------------------------------------
CXBPackedResource::CXBPackedResource()
{
    m_pSysMemData    = NULL;
    m_pVidMemData    = NULL;
    m_dwNumResources = 0L;
    m_pResourceTags  = NULL;
}




//-----------------------------------------------------------------------------
// Name: ~CXBPackedResource()
// Desc: Destructor
//-----------------------------------------------------------------------------
CXBPackedResource::~CXBPackedResource()
{
    Destroy();
}




//-----------------------------------------------------------------------------
// Name: GetData()
// Desc: Loads all the texture resources from the given XPR.
//-----------------------------------------------------------------------------
VOID* CXBPackedResource::GetData( const CHAR* strName )
{
    if( NULL==m_pResourceTags || NULL==strName )
        return NULL;

    for( DWORD i=0; i<m_dwNumResources; i++ )
    {
        if( !_stricmp( strName, m_pResourceTags[i].strName ) )
            return &m_pSysMemData[m_pResourceTags[i].dwOffset];
    }

    return NULL;
}




//-----------------------------------------------------------------------------
// Name: Create()
// Desc: Loads all the texture resources from the given XPR.
//-----------------------------------------------------------------------------
HRESULT CXBPackedResource::Create( LPDIRECT3DDEVICE8 pd3dDevice, 
                                   const CHAR* strFilename, DWORD dwNumResources,
                                   XBRESOURCE* pResourceTags )
{
    // Find the media file
    CHAR strResourcePath[512];
    if( FAILED( XBUtil_FindMediaFile( strResourcePath, strFilename ) ) )
        return E_FAIL;

    // Open the fileto read the XPR headers
    FILE* file = fopen( strResourcePath, "rb" );
    if( NULL == file )
        return E_FAIL;

    // Read in and verify the XPR magic header
    XPR_HEADER xprh;
    fread( &xprh, sizeof(XPR_HEADER), 1, file );
    if( xprh.dwMagic != XPR_MAGIC_VALUE )
    {
        OutputDebugString( _T("Invalid Xbox Packed Resource (.xpr) file") );
        fclose( file );
        return E_INVALIDARG;
    }

    // Compute memory requirements
    DWORD dwSysMemDataSize = xprh.dwHeaderSize - sizeof(XPR_HEADER);
    DWORD dwVidMemDataSize = xprh.dwTotalSize - xprh.dwHeaderSize;

    // Allocate memory
    m_pSysMemData = new BYTE[dwSysMemDataSize];
    m_pVidMemData = (BYTE*)D3D_AllocContiguousMemory( dwVidMemDataSize, D3DTEXTURE_ALIGNMENT );

    // Read in the data from the file
    fread( m_pSysMemData, dwSysMemDataSize, 1, file );
    fread( m_pVidMemData, dwVidMemDataSize, 1, file );

    // Done with the file
    fclose( file );
    
    // Under UMA emulation, we copy the data from AGP memory to video memory.
    // This will not be necessary with final hardware
    D3D_CopyContiguousMemoryToVideo( m_pVidMemData );

    // Loop over resources, calling Register()
    BYTE* pData = m_pSysMemData;

    for( DWORD i = 0; i < dwNumResources; i++ )
    {
		// Check for userdata
		if( *((DWORD*)pData) & 0x80000000 )
		{
			DWORD dwType = ((DWORD*)pData)[0];
			DWORD dwSize = ((DWORD*)pData)[1];
			pData += 8;

			pData += dwSize;
		}
		else
		{
			// Get the resource
			LPDIRECT3DRESOURCE8 pResource = (LPDIRECT3DRESOURCE8)pData;
    
	        // Register the resource
		    pResource->Register( m_pVidMemData );
        
			// Advance the pointer
			pData += XBResource_SizeOf( pResource );
		}
    }

    // Finally, store number of resources and the resource tags
    m_dwNumResources = dwNumResources;
    m_pResourceTags  = pResourceTags;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Destroy()
// Desc: Tears down the packed resource data
//-----------------------------------------------------------------------------
VOID CXBPackedResource::Destroy() 
{
    if( m_pSysMemData != NULL )
    {
        delete[] m_pSysMemData;
        m_pSysMemData = NULL;
    }
    if( m_pVidMemData != NULL )
    {
        D3D_FreeContiguousMemory( m_pVidMemData );
        m_pVidMemData = NULL;
    }
    m_dwNumResources = 0L;
    m_pResourceTags  = NULL;
}
