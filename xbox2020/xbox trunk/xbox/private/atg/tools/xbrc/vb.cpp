//-----------------------------------------------------------------------------
// File: VB.cpp
//
// Desc: Contains the vertexbuffer-specific logic for the bundler tool
//
// Hist: 2001.02.06 - New for March XDK release
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include "VB.h"
#include "Bundler.h"
#include <stdio.h>




//-----------------------------------------------------------------------------
// Name: CVertexBuffer()
// Desc: Initializes member variables
//-----------------------------------------------------------------------------
CVertexBuffer::CVertexBuffer( CBundler* pBundler )
{
    m_pBundler = pBundler;
    m_DataCount = m_FormatCount = 0;
    m_bRawVertices = FALSE;
}




//-----------------------------------------------------------------------------
// Name: ~CVertexBuffer (destructor)
// Desc: Performs any cleanup needed before the object is destroyed
//-----------------------------------------------------------------------------
CVertexBuffer::~CVertexBuffer()
{
}




//-----------------------------------------------------------------------------
// Name: AddVertexData()
// Desc: Adds a single value to the vertex data stream
//-----------------------------------------------------------------------------
HRESULT CVertexBuffer::AddVertexData( DOUBLE val )
{
    if(m_DataCount >= MAX_VB_DATA)
    {
        m_pBundler->ErrorMsg( "Error: Vertex Data Buffer Overflow\n" );
        return E_FAIL;
    }
    m_Data[m_DataCount++] = val;
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: LoadVertexDataFromFile
// Desc: Loads entire vertex data stream from file
//-----------------------------------------------------------------------------
HRESULT CVertexBuffer::LoadVertexDataFromFile( CHAR* strFilename )
{
    // Open the file
    HANDLE hFile = CreateFileA( strFilename, 
                                GENERIC_READ, 
                                FILE_SHARE_READ, 
                                NULL,
                                OPEN_EXISTING,
                                FILE_FLAG_SEQUENTIAL_SCAN,
                                NULL );
    if( INVALID_HANDLE_VALUE == hFile )
        return E_FAIL;

    // Make sure we can fit the whole thing in memory.
    // TODO: Dynamically allocate memory for vertex buffers
    DWORD dwSize = GetFileSize( hFile, NULL );
    if( dwSize > sizeof( m_Data ) )
    {
        m_pBundler->ErrorMsg( "Error: Vertex data file too large.\n" );
        return E_FAIL;
    }

    // Read the data
    DWORD dwRead;
    ReadFile( hFile, m_Data, dwSize, &dwRead, NULL );
    if( dwRead != dwSize )
        return E_FAIL;

    CloseHandle( hFile );

    m_bRawVertices = TRUE;
    m_DataCount = dwRead;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: AddVertexFormat()
// Desc: Adds a single value to the vertex data format
//-----------------------------------------------------------------------------
HRESULT CVertexBuffer::AddVertexFormat( DWORD format )
{
    if(m_FormatCount >= MAX_VB_FORMATS)
    {
        m_pBundler->ErrorMsg( "Error: Vertex Format Buffer Overflow\n" );
        return E_FAIL;
    }
    m_Format[m_FormatCount++] = format;
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SaveToBundle()
// Desc: Handles saving the appropriate data to the packed resource file
//-----------------------------------------------------------------------------
HRESULT CVertexBuffer::SaveToBundle( DWORD * pcbHeader, DWORD * pcbData )
{
    HRESULT hr;

    if(m_FormatCount == 0)
    {
        m_pBundler->ErrorMsg( "Error: No attribute formats specified\n" );
        return E_FAIL;
    }
    
    if(m_DataCount == 0)
    {
        m_pBundler->ErrorMsg( "Error: No attribute data specified\n" );
        return E_FAIL;
    }
    
    // Pad data file to proper alignment for the start of the vertex buffer
    hr = m_pBundler->PadToAlignment( XD3DVERTEXBUFFER_ALIGNMENT );
    if( FAILED( hr ) )
        return hr;

    // Save resource header
    hr = SaveHeaderInfo( m_pBundler->m_cbData, pcbHeader );
    if( FAILED( hr ) )
        return hr;

    // Save vertexbuffer data
    hr = SaveVertexBufferData( pcbData );
    if( FAILED( hr ) )
        return hr;
     
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SaveHeaderInfo()
// Desc: Saves the appropriate data to the header file
//-----------------------------------------------------------------------------
HRESULT CVertexBuffer::SaveHeaderInfo( DWORD dwStart, DWORD * pcbHeader )
{
    XD3DVertexBuffer xd3dvb;

    xd3dvb.Common = XD3DCOMMON_TYPE_VERTEXBUFFER |    // Type
                    1;                                // Initial Refcount

    xd3dvb.Data   = dwStart;                    // Offset of data in data file
    xd3dvb.Lock   = 0;                          // Must be zero


    // Write the resource header out
    if( FAILED( m_pBundler->WriteHeader( &xd3dvb, sizeof( xd3dvb ) ) ) )
        return E_FAIL;

    *pcbHeader = sizeof( xd3dvb );

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: SaveVertexBufferData()
// Desc: Saves the raw VertexBuffer data to the XPR file
//-----------------------------------------------------------------------------
HRESULT CVertexBuffer::SaveVertexBufferData( DWORD * pcbData )
{
    DWORD cData, cFormat, cVertex;
    FLOAT fOut[4];
    DWORD dwOut[4];
    SHORT sOut[4];
    BYTE  bOut[4];

    // calculate how many bytes per vertex
    m_cBytesPerVertex = 0;
    m_cInputValuesPerVertex = 0;
    for(cFormat=0; cFormat < m_FormatCount; cFormat++)
    {
		DWORD inputs;
		DWORD bytesout;
		switch (m_Format[cFormat])
		{
			case XD3DVSDT_FLOAT1     : 	inputs = 1; bytesout = sizeof(FLOAT);   break;
			case XD3DVSDT_FLOAT2     : 	inputs = 2; bytesout = 2*sizeof(FLOAT); break;
			case XD3DVSDT_FLOAT3     : 	inputs = 3; bytesout = 3*sizeof(FLOAT); break;
			case XD3DVSDT_FLOAT4     : 	inputs = 4; bytesout = 4*sizeof(FLOAT); break;
    		case XD3DVSDT_D3DCOLOR   : 	inputs = 4; bytesout = 4*sizeof(BYTE);  break;
    		case XD3DVSDT_SHORT2     : 	inputs = 2; bytesout = 2*sizeof(SHORT); break;
    		case XD3DVSDT_SHORT4     : 	inputs = 4; bytesout = 4*sizeof(SHORT); break;
    		case XD3DVSDT_NORMSHORT1 : 	inputs = 1; bytesout = sizeof(SHORT);   break;
    		case XD3DVSDT_NORMSHORT2 : 	inputs = 2; bytesout = 2*sizeof(SHORT); break;
    		case XD3DVSDT_NORMSHORT3 : 	inputs = 3; bytesout = 3*sizeof(SHORT); break;
    		case XD3DVSDT_NORMSHORT4 : 	inputs = 4; bytesout = 4*sizeof(SHORT); break;
    		case XD3DVSDT_NORMPACKED3: 	inputs = 3; bytesout = sizeof(DWORD);   break;
    		case XD3DVSDT_SHORT1     : 	inputs = 1; bytesout = sizeof(SHORT);   break;
    		case XD3DVSDT_SHORT3     : 	inputs = 3; bytesout = 3*sizeof(SHORT); break;
    		case XD3DVSDT_PBYTE1     : 	inputs = 1; bytesout = sizeof(BYTE);    break;
    		case XD3DVSDT_PBYTE2     : 	inputs = 2; bytesout = 2*sizeof(BYTE);  break;
    		case XD3DVSDT_PBYTE3     : 	inputs = 3; bytesout = 3*sizeof(BYTE);  break;
    		case XD3DVSDT_PBYTE4     : 	inputs = 4; bytesout = 4*sizeof(BYTE);  break;
    		case XD3DVSDT_FLOAT2H    : 	inputs = 3; bytesout = 3*sizeof(FLOAT); break;
			default:
				m_pBundler->ErrorMsg("Error: Bad vertex buffer format token\n");
				return E_FAIL;
		}
        m_cBytesPerVertex += bytesout;
        m_cInputValuesPerVertex += inputs;
    }
	
    // If we read raw vertex info from a file, just spew it out
	if (m_bRawVertices)
	{
        m_cVertices = m_DataCount / m_cBytesPerVertex;
        m_cTotalBytesinVB = m_DataCount;
        *pcbData = m_DataCount;

        if( FAILED( m_pBundler->WriteData( m_Data, m_DataCount ) ) )
            return E_FAIL;
        else
            return S_OK;
	}
	else
	{
		m_cVertices = m_DataCount/m_cInputValuesPerVertex;
		m_cTotalBytesinVB = m_cVertices*m_cBytesPerVertex;
		*pcbData = 0;
	}

    if((m_cVertices * m_cInputValuesPerVertex) != m_DataCount)
    {
        m_pBundler->ErrorMsg( "Warning: Extra Vertex Buffer Data:\n");
        m_pBundler->ErrorMsg( "         Format specifies %d values per vertex\n", m_cInputValuesPerVertex);
        m_pBundler->ErrorMsg( "         %d values supplied\n", m_DataCount);
        m_pBundler->ErrorMsg( "         Enough for %d vertices with %d values left over\n", m_cVertices, 
                             m_DataCount - m_cVertices * m_cInputValuesPerVertex);
    }

    for(cData = 0, cVertex = 0; cVertex < m_cVertices; cVertex++ )
    {
        for(cFormat=0; cFormat < m_FormatCount; cFormat++)
        {
            switch(m_Format[cFormat])
            {
				case XD3DVSDT_FLOAT1:
					*pcbData += sizeof(FLOAT);
					fOut[0] = (FLOAT)m_Data[cData++];
					if( FAILED( m_pBundler->WriteData( fOut, sizeof(FLOAT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_FLOAT2:
					*pcbData += 2*sizeof(FLOAT);
					fOut[0] = (FLOAT)m_Data[cData++];
					fOut[1] = (FLOAT)m_Data[cData++];
					if( FAILED( m_pBundler->WriteData( fOut, 2*sizeof(FLOAT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_FLOAT2H:
				case XD3DVSDT_FLOAT3:
					*pcbData += 3*sizeof(FLOAT);
					fOut[0] = (FLOAT)m_Data[cData++];
					fOut[1] = (FLOAT)m_Data[cData++];
					fOut[2] = (FLOAT)m_Data[cData++];
					if( FAILED( m_pBundler->WriteData( fOut, 3*sizeof(FLOAT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_FLOAT4:
					*pcbData += 4*sizeof(FLOAT);
					fOut[0] = (FLOAT)m_Data[cData++];
					fOut[1] = (FLOAT)m_Data[cData++];
					fOut[2] = (FLOAT)m_Data[cData++];
					fOut[3] = (FLOAT)m_Data[cData++];
					if( FAILED( m_pBundler->WriteData( fOut, 4*sizeof(FLOAT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_D3DCOLOR:
					*pcbData += 4*sizeof(BYTE);
					bOut[2] = (BYTE)(m_Data[cData++] * 255.0);	// r
					bOut[1] = (BYTE)(m_Data[cData++] * 255.0);	// g
					bOut[0] = (BYTE)(m_Data[cData++] * 255.0);	// b
					bOut[3] = (BYTE)(m_Data[cData++] * 255.0);	// a
					if( FAILED( m_pBundler->WriteData( bOut, 4*sizeof(BYTE) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_SHORT1:
					*pcbData += sizeof(SHORT);
					sOut[0] = (SHORT)m_Data[cData++];
					if( FAILED( m_pBundler->WriteData( sOut, sizeof(SHORT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_SHORT2:
					*pcbData += 2*sizeof(SHORT);
					sOut[0] = (SHORT)m_Data[cData++];
					sOut[1] = (SHORT)m_Data[cData++];
					if( FAILED( m_pBundler->WriteData( sOut, 2*sizeof(SHORT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_SHORT3:
					*pcbData += 3*sizeof(SHORT);
					sOut[0] = (SHORT)m_Data[cData++];
					sOut[1] = (SHORT)m_Data[cData++];
					sOut[2] = (SHORT)m_Data[cData++];
					if( FAILED( m_pBundler->WriteData( sOut, 3*sizeof(SHORT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_SHORT4:
					*pcbData += 4*sizeof(SHORT);
					sOut[0] = (SHORT)m_Data[cData++];
					sOut[1] = (SHORT)m_Data[cData++];
					sOut[2] = (SHORT)m_Data[cData++];
					sOut[3] = (SHORT)m_Data[cData++];
					if( FAILED( m_pBundler->WriteData( sOut, 4*sizeof(SHORT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_NORMSHORT1:
					*pcbData += sizeof(SHORT);
					sOut[0] = (SHORT)(m_Data[cData++]*32767.0);
					if( FAILED( m_pBundler->WriteData( sOut, sizeof(SHORT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_NORMSHORT2:
					*pcbData += 2*sizeof(SHORT);
					sOut[0] = (SHORT)(m_Data[cData++]*32767.0);
					sOut[1] = (SHORT)(m_Data[cData++]*32767.0);
					if( FAILED( m_pBundler->WriteData( sOut, 2*sizeof(SHORT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_NORMSHORT3:
					*pcbData += 3*sizeof(SHORT);
					sOut[0] = (SHORT)(m_Data[cData++]*32767.0);
					sOut[1] = (SHORT)(m_Data[cData++]*32767.0);
					sOut[2] = (SHORT)(m_Data[cData++]*32767.0);
					if( FAILED( m_pBundler->WriteData( sOut, 3*sizeof(SHORT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_NORMSHORT4:
					*pcbData += 4*sizeof(SHORT);
					sOut[0] = (SHORT)(m_Data[cData++]*32767.0);
					sOut[1] = (SHORT)(m_Data[cData++]*32767.0);
					sOut[2] = (SHORT)(m_Data[cData++]*32767.0);
					sOut[3] = (SHORT)(m_Data[cData++]*32767.0);
					if( FAILED( m_pBundler->WriteData( sOut, 4*sizeof(SHORT) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_NORMPACKED3:
					*pcbData += sizeof(DWORD);
					dwOut[0] = (DWORD)(m_Data[cData++]*2147483648.0);
					dwOut[1] = (DWORD)(m_Data[cData++]*2147483648.0);
					dwOut[2] = (DWORD)(m_Data[cData++]*2147483648.0);
					dwOut[3] = (dwOut[0] & 0xffe00000) |
							   ((dwOut[1] >> 11) & 0x001ffc00) |
							   ((dwOut[2] >> 22) & 0x000003ff);
					if( FAILED( m_pBundler->WriteData( &(dwOut[3]), sizeof(DWORD) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_PBYTE1:
					*pcbData += sizeof(BYTE);
					bOut[0] = (BYTE)(m_Data[cData++] * 255.0);
					if( FAILED( m_pBundler->WriteData( bOut, sizeof(BYTE) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_PBYTE2:
					*pcbData += 2*sizeof(BYTE);
					bOut[0] = (BYTE)(m_Data[cData++] * 255.0);
					bOut[1] = (BYTE)(m_Data[cData++] * 255.0);
					if( FAILED( m_pBundler->WriteData( bOut, 2*sizeof(BYTE) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_PBYTE3:
					*pcbData += 3*sizeof(BYTE);
					bOut[0] = (BYTE)(m_Data[cData++] * 255.0);
					bOut[1] = (BYTE)(m_Data[cData++] * 255.0);
					bOut[2] = (BYTE)(m_Data[cData++] * 255.0);
					if( FAILED( m_pBundler->WriteData( bOut, 3*sizeof(BYTE) ) ) )
						return E_FAIL;
					break;
				case XD3DVSDT_PBYTE4:
					*pcbData += 4*sizeof(BYTE);
					bOut[0] = (BYTE)(m_Data[cData++] * 255.0);
					bOut[1] = (BYTE)(m_Data[cData++] * 255.0);
					bOut[2] = (BYTE)(m_Data[cData++] * 255.0);
					bOut[3] = (BYTE)(m_Data[cData++] * 255.0);
					if( FAILED( m_pBundler->WriteData( bOut, 4*sizeof(BYTE) ) ) )
						return E_FAIL;
					break;
            }
        }
    }
    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: VertexFormatFromString
// Desc: helper function to match a format string to the format constant
//-----------------------------------------------------------------------------
DWORD CVertexBuffer::VertexFormatFromString( CONST CHAR *strBuff )
{
	if((strcmp(strBuff, "D3DVSDT_FLOAT1") == 0) ||
	   (strcmp(strBuff, "FLOAT1") == 0))
		return XD3DVSDT_FLOAT1;
	else if((strcmp(strBuff, "D3DVSDT_FLOAT2") == 0) ||
			(strcmp(strBuff, "FLOAT2") == 0))
		return XD3DVSDT_FLOAT2;
	else if((strcmp(strBuff, "D3DVSDT_FLOAT3") == 0) ||
			(strcmp(strBuff, "FLOAT3") == 0))
		return XD3DVSDT_FLOAT3;
	else if((strcmp(strBuff, "D3DVSDT_FLOAT4") == 0) ||
			(strcmp(strBuff, "FLOAT4") == 0))
		return XD3DVSDT_FLOAT4;
	else if((strcmp(strBuff, "D3DVSDT_D3DCOLOR") == 0) ||
			(strcmp(strBuff, "D3DCOLOR") == 0))
		return XD3DVSDT_D3DCOLOR;
	else if((strcmp(strBuff, "D3DVSDT_SHORT2") == 0) ||
			(strcmp(strBuff, "SHORT2") == 0))
		return XD3DVSDT_SHORT2;
	else if((strcmp(strBuff, "D3DVSDT_SHORT4") == 0) ||
			(strcmp(strBuff, "SHORT4") == 0))
		return XD3DVSDT_SHORT4;
	else if((strcmp(strBuff, "D3DVSDT_NORMSHORT1") == 0) ||
			(strcmp(strBuff, "NORMSHORT1") == 0))
		return XD3DVSDT_NORMSHORT1;
	else if((strcmp(strBuff, "D3DVSDT_NORMSHORT2") == 0) ||
			(strcmp(strBuff, "NORMSHORT2") == 0))
		return XD3DVSDT_NORMSHORT2;
	else if((strcmp(strBuff, "D3DVSDT_NORMSHORT3") == 0) ||
			(strcmp(strBuff, "NORMSHORT3") == 0))
		return XD3DVSDT_NORMSHORT3;
	else if((strcmp(strBuff, "D3DVSDT_NORMSHORT4") == 0) ||
			(strcmp(strBuff, "NORMSHORT4") == 0))
		return XD3DVSDT_NORMSHORT4;
	else if((strcmp(strBuff, "D3DVSDT_NORMPACKED3") == 0) ||
			(strcmp(strBuff, "NORMPACKED3") == 0))
		return XD3DVSDT_NORMPACKED3;
	else if((strcmp(strBuff, "D3DVSDT_SHORT1") == 0) ||
			(strcmp(strBuff, "SHORT1") == 0))
		return XD3DVSDT_SHORT1;
	else if((strcmp(strBuff, "D3DVSDT_SHORT3") == 0) ||
			(strcmp(strBuff, "SHORT3") == 0))
		return XD3DVSDT_SHORT3;
	else if((strcmp(strBuff, "D3DVSDT_PBYTE1") == 0) ||
			(strcmp(strBuff, "PBYTE1") == 0))
		return XD3DVSDT_PBYTE1;
	else if((strcmp(strBuff, "D3DVSDT_PBYTE2") == 0) ||
			(strcmp(strBuff, "PBYTE2") == 0))
		return XD3DVSDT_PBYTE2;
	else if((strcmp(strBuff, "D3DVSDT_PBYTE3") == 0) ||
			(strcmp(strBuff, "PBYTE3") == 0))
		return XD3DVSDT_PBYTE3;
	else if((strcmp(strBuff, "D3DVSDT_PBYTE4") == 0) ||
			(strcmp(strBuff, "PBYTE4") == 0))
		return XD3DVSDT_PBYTE4;
	else if((strcmp(strBuff, "D3DVSDT_FLOAT2H") == 0) ||
			(strcmp(strBuff, "FLOAT2H") == 0))
		return XD3DVSDT_FLOAT2H;
	else
		return -1;
}
	
