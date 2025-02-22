//
// dmwaveobj.cpp
// 
// Copyright (c) 1997-1999 Microsoft Corporation. All rights reserved.
//
#ifdef XBOX
#include <xtl.h>
#define COM_NO_WINDOWS_H
#define RPC_NO_WINDOWS_H
#define _WINGDI_
#endif // XBOX

#include <objbase.h>
#include <mmsystem.h>
#include <dsoundp.h>

#include "dmusicc.h"
#include "alist.h"
#include "debug.h"
#include "dlsstrm.h"
#include <mmreg.h>
#include <msacm.h>
#include "debug.h"
#include "dmcollec.h"
#include "dmcrchk.h"
#include "dmwavobj.h"
#include "dmportdl.h"

#ifdef XBOX
#define NO_COMPRESSION_SUPPORT
#define IGNORE_ACM(wFormatTag) ((wFormatTag == WAVE_FORMAT_PCM) || (wFormatTag == WAVE_FORMAT_XBOX_ADPCM)) 
#else
#define IGNORE_ACM(wFormatTag) (wFormatTag == WAVE_FORMAT_PCM) 
#endif // XBOX
#define USE_ACM(format) (!IGNORE_ACM(format))

//////////////////////////////////////////////////////////////////////
// Class CWaveObj
 
//////////////////////////////////////////////////////////////////////
// CWaveObj::CWaveObj

CWaveObj::CWaveObj() :
m_pExtractWaveFormatData(NULL),
m_dwDataOffset(0),
m_dwDataSizeWrite(0),
m_dwDataSizeRead(0),
m_dwId(0),
m_pParent(NULL),
m_cbSizeOffsetTable(0),
#ifdef DXAPI
m_pCopyright(NULL),
m_dwCountExtChk(0),
#endif
m_dwSize(0),
m_fCSInitialized(FALSE),
m_fReadDecompressionFormat(FALSE)
#ifdef DBG
,
m_bLoaded(false)
#endif
{
	InitializeCriticalSection(&m_DMWaveCriticalSection);
    m_fCSInitialized = TRUE;
	ZeroMemory(&m_WaveFormatRead, sizeof(m_WaveFormatRead));
	ZeroMemory(&m_WaveFormatWrite, sizeof(m_WaveFormatWrite));
}

//////////////////////////////////////////////////////////////////////
// CWavebj::~CWavebj

CWaveObj::~CWaveObj()
{
    if (m_fCSInitialized)
    {
    	Cleanup();
	    DeleteCriticalSection(&m_DMWaveCriticalSection);
    }
}

//////////////////////////////////////////////////////////////////////
// CWaveObj::Load

HRESULT CWaveObj::Load(DWORD dwId, CRiffParser *pParser, CCollection* pParent)
{
	// Argument validation
	assert(pParent);

#ifdef DBG
	if(dwId >= CDirectMusicPortDownload::sNextDLId)
	{
		assert(FALSE);
	}
#endif

	m_dwId = dwId;
	m_pParent = pParent;
	m_pParent->AddRef();

	HRESULT hr = S_OK;
	
	RIFFIO ck;
	EnterCriticalSection(&m_DMWaveCriticalSection);
	
    pParser->EnterList(&ck);
    while (pParser->NextChunk(&hr))
    {
		switch(ck.ckid)
		{
			case mmioFOURCC('w','a','v','u') :
			{
				// Read the flag which indiactes Runtime or Designtime File
				bool bTemp = false;;
				hr = pParser->Read(&bTemp, sizeof(bool));
				if(SUCCEEDED(hr))
				{
					// Read the flag that indicates compression
					hr = pParser->Read(&bTemp, sizeof(bool));
					if(SUCCEEDED(hr))
					{
						// this is a compressed wave file
						if(bTemp == true)
						{
							hr = pParser->Read(&m_WaveFormatDecompress, sizeof(WAVEFORMATEX));

							if(FAILED(hr))
							{
								hr = E_FAIL;
								m_fReadDecompressionFormat = FALSE;
							}
							else
							{
								m_WaveFormatDecompress.nAvgBytesPerSec = m_WaveFormatDecompress.nSamplesPerSec * m_WaveFormatDecompress.nBlockAlign;
								m_fReadDecompressionFormat = TRUE;
							}
						}
					}
				}

				break;
			}
#ifdef DXAPI
			case FOURCC_LIST :
				switch(ck.fccType)
				{
                case mmioFOURCC('I','N','F','O') :
					m_pCopyright = new CCopyright;
					if(m_pCopyright)
					{
						hr = m_pCopyright->Load(pParser);
						if((m_pCopyright->m_byFlags & DMC_FOUNDICOP) == 0)
						{
							delete m_pCopyright;
							m_pCopyright = NULL;
						}
					}
					else
					{
						hr =  E_OUTOFMEMORY;
					}
					break;
				default :
					// If we get here we have an unknown chunk
					CExtensionChunk* pExtensionChunk = new CExtensionChunk;
					if(pExtensionChunk)
					{
						hr = pExtensionChunk->Load(pParser);
						m_ExtensionChunkList.AddHead(pExtensionChunk);
						m_dwCountExtChk++;
					}
					else
					{
						hr = E_OUTOFMEMORY;
					}
					break;
                }
				break;
#endif
			case mmioFOURCC('f','m','t',' ') :
				hr = pParser->Read(&m_WaveFormatRead, sizeof(WAVEFORMATEX));
				if(SUCCEEDED(hr))
				{
					if(USE_ACM(m_WaveFormatRead.wFormatTag))
					{
#ifdef NO_COMPRESSION_SUPPORT
						hr = E_FAIL;
#else  // NO_COMPRESSION_SUPPORT
                        if(m_WaveFormatRead.cbSize)
                        {
							m_pExtractWaveFormatData = new BYTE[m_WaveFormatRead.cbSize];
							if(m_pExtractWaveFormatData)
							{
								hr = pParser->Read(m_pExtractWaveFormatData, m_WaveFormatRead.cbSize);
							}
                        }
						if(SUCCEEDED(hr))
                        {
							hr = CanDecompress();
                        }
#endif // NO_COMPRESSION_SUPPORT
					}
					else
					{
						// If WAVE_FORMAT_PCM this member should be zero
						m_WaveFormatRead.cbSize = 0;
						CopyMemory(&m_WaveFormatWrite, &m_WaveFormatRead, sizeof(m_WaveFormatRead));
					}
				}
				break;
			case mmioFOURCC('d','a','t','a') :
                pParser->MarkPosition();
				m_dwDataOffset = (DWORD) ck.liPosition.QuadPart;
				m_dwDataSizeRead = ck.cksize;
				hr = m_pParent->ValidateOffset(m_dwDataOffset + m_dwDataSizeRead);
				break;

			default :
#ifdef DXAPI
				// If we get here we have an unknown chunk
				CExtensionChunk* pExtensionChunk = new CExtensionChunk;
				if(pExtensionChunk)
				{
					hr = pExtensionChunk->Load(pParser);
					m_ExtensionChunkList.AddHead(pExtensionChunk);
					m_dwCountExtChk++;
				}
				else
				{
					hr = E_OUTOFMEMORY;
				}
#endif
				break;
            }
	}
    pParser->LeaveList();
	
#ifdef DBG
	if(SUCCEEDED(hr))
	{
		m_bLoaded = true;
	}
#endif

	if(FAILED(hr))
	{
		Cleanup();
	}
	
	LeaveCriticalSection(&m_DMWaveCriticalSection);

	return hr;
}

//////////////////////////////////////////////////////////////////////
// CWaveObj::Cleanup

void CWaveObj::Cleanup()
{
	EnterCriticalSection(&m_DMWaveCriticalSection);

	delete [] m_pExtractWaveFormatData;
	m_pExtractWaveFormatData = NULL;
#ifdef DXAPI
	while(!m_ExtensionChunkList.IsEmpty())
	{
		CExtensionChunk* pExtChk = m_ExtensionChunkList.RemoveHead();
		delete pExtChk;
	}
	delete m_pCopyright;
	m_pCopyright = NULL;
#endif
	
	if(m_pParent)
	{
		m_pParent->Release();
		m_pParent = NULL;
	}

#ifdef DBG
	m_bLoaded = false;
#endif
	
	LeaveCriticalSection(&m_DMWaveCriticalSection);
}

//////////////////////////////////////////////////////////////////////
// CWaveObj::Size
#ifdef DXAPI
HRESULT CWaveObj::Size(DWORD* pdwSize,DWORD *pdwSampleSize)
{
	// Assumption validation
#ifdef DBG
	assert(m_bLoaded);
#endif
 	assert(pdwSize);

	// If have already calculated the size we do not need to do it again
	if(m_dwSize)
	{
		*pdwSize = m_dwSize;
		*pdwSampleSize = m_WaveFormatWrite.wBitsPerSample;
		return S_OK;
	}
	
	HRESULT hr = S_OK;
	
	DWORD dwTotalSize = 0;
	DWORD dwOffsetCount = 0;
	DWORD dwCountExtChk = 0;

	EnterCriticalSection(&m_DMWaveCriticalSection);

	// Calculate the space needed for DMUS_DOWNLOADINFO 
	dwTotalSize += CHUNK_ALIGN(sizeof(DMUS_DOWNLOADINFO));

	// Calculate the space needed for Wave's extension chunks
	CExtensionChunk* pExtChk = m_ExtensionChunkList.GetHead();
	for(; pExtChk; pExtChk = pExtChk->GetNext())
	{
		dwTotalSize += pExtChk->Size();
		dwOffsetCount += pExtChk->Count();
		dwCountExtChk++;
	}

	// We want to validate the number of extension chunks
	if(m_dwCountExtChk == dwCountExtChk)
    {
		// Calculate the space needed for wave's copyright
		if(m_pCopyright)
		{
			dwTotalSize += m_pCopyright->Size();
			dwOffsetCount += m_pCopyright->Count();
		}
		// If wave does not have one use collection's
		else if(m_pParent && m_pParent->m_pCopyright && (m_pParent->m_pCopyright)->m_pDMCopyright)
		{
			dwTotalSize += (m_pParent->m_pCopyright)->Size();
			dwOffsetCount += (m_pParent->m_pCopyright)->Count();
		}
		// Calculate space needed for WAVE and WAVEDATA
		dwTotalSize += CHUNK_ALIGN(sizeof(DMUS_WAVE)) + 
			CHUNK_ALIGN(sizeof(DMUS_WAVEDATA));
		dwOffsetCount += 2;

		// Calculate space needed for offset table
		m_cbSizeOffsetTable = dwOffsetCount * sizeof(ULONG);
		dwTotalSize += m_cbSizeOffsetTable;

		// Calculate space needed for wave data
		// We allocated DMUS_MIN_DATA_SIZE worth when we allocated for DMUS_WAVEDATA
		m_dwDataSizeWrite = m_dwDataSizeRead;
		
		if(USE_ACM(m_WaveFormatRead.wFormatTag))
		{
#ifdef NO_COMPRESSION_SUPPORT
			hr = E_FAIL;
#else  // NO_COMPRESSION_SUPPORT
			hr = CalcDataSize(&m_dwDataSizeWrite);
#endif // NO_COMPRESSION_SUPPORT
		}
		
		
		if(SUCCEEDED(hr) && m_dwDataSizeWrite > DMUS_MIN_DATA_SIZE)
		{
			dwTotalSize += (m_dwDataSizeWrite - DMUS_MIN_DATA_SIZE);		
		}
		dwTotalSize = CHUNK_ALIGN(dwTotalSize);
	}
	else
	{
		hr = E_FAIL;
	}
	
	// If everything went well, we have the size
	if(SUCCEEDED(hr))
	{
		m_dwSize = dwTotalSize;
		*pdwSize = m_dwSize;
		*pdwSampleSize = m_WaveFormatWrite.wBitsPerSample;
	}

	LeaveCriticalSection(&m_DMWaveCriticalSection);

	return hr;
}
#else
HRESULT CWaveObj::Size(DWORD* pdwSize,DWORD *pdwSampleSize)
{
	// Assumption validation
#ifdef DBG
	assert(m_bLoaded);
#endif
 	assert(pdwSize);

	// If have already calculated the size we do not need to do it again
	if(m_dwSize)
	{
		*pdwSize = m_dwSize;
		*pdwSampleSize = m_WaveFormatWrite.wBitsPerSample;
		return S_OK;
	}
	
	HRESULT hr = S_OK;
	
	DWORD dwTotalSize = 0;
	DWORD dwOffsetCount = 0;

	EnterCriticalSection(&m_DMWaveCriticalSection);

	// Calculate the space needed for DMUS_DOWNLOADINFO 
	dwTotalSize = CHUNK_ALIGN(sizeof(DMUS_DOWNLOADINFO));

	// Calculate the space needed for Wave's extension chunks
    {
		// Calculate space needed for WAVE and WAVEDATA
		dwTotalSize += CHUNK_ALIGN(sizeof(DMUS_WAVE)) + 
			CHUNK_ALIGN(sizeof(DMUS_WAVEDATA));
		dwOffsetCount += 2;

		// Calculate space needed for offset table
		m_cbSizeOffsetTable = dwOffsetCount * sizeof(ULONG);
		dwTotalSize += m_cbSizeOffsetTable;

		// Calculate space needed for wave data
		// We allocated DMUS_MIN_DATA_SIZE worth when we allocated for DMUS_WAVEDATA
		m_dwDataSizeWrite = m_dwDataSizeRead;
		
		if(USE_ACM(m_WaveFormatRead.wFormatTag))
		{
#ifdef NO_COMPRESSION_SUPPORT
			hr = E_FAIL;
#else  // NO_COMPRESSION_SUPPORT
			hr = CalcDataSize(&m_dwDataSizeWrite);
#endif // NO_COMPRESSION_SUPPORT
		}
		
		
		if(SUCCEEDED(hr) && m_dwDataSizeWrite > DMUS_MIN_DATA_SIZE)
		{
			dwTotalSize += (m_dwDataSizeWrite - DMUS_MIN_DATA_SIZE);		
		}
		dwTotalSize = CHUNK_ALIGN(dwTotalSize);
	}
	
	// If everything went well, we have the size
	if(SUCCEEDED(hr))
	{
		m_dwSize = dwTotalSize;
		*pdwSize = m_dwSize;
		*pdwSampleSize = m_WaveFormatWrite.wBitsPerSample;
	}

	LeaveCriticalSection(&m_DMWaveCriticalSection);

	return hr;
}
#endif

//////////////////////////////////////////////////////////////////////
// CWaveObj::Write

HRESULT CWaveObj::Write(void* pvoid)
{
	// Assumption and argument validation
#ifdef DBG
	assert(m_bLoaded);
#endif

	assert(pvoid);

	DWORD dwSize;
	DWORD dwSampleSize;

	HRESULT hr = Size(&dwSize,&dwSampleSize);
	
	if(FAILED(hr))
	{       
		return hr;
	}

	EnterCriticalSection(&m_DMWaveCriticalSection);

	DWORD dwCurIndex = 0;   // Used to determine what index to store offset in Offset Table
	DWORD dwCurOffset = 0;  // Offset relative to beginning of passed in memory

	// Write DMUS_DOWNLOADINFO
	DMUS_DOWNLOADINFO *pDLInfo = (DMUS_DOWNLOADINFO *) pvoid;
	pDLInfo->dwDLType = DMUS_DOWNLOADINFO_WAVE;
	pDLInfo->dwDLId = m_dwId;
	pDLInfo->dwNumOffsetTableEntries = (m_cbSizeOffsetTable/sizeof(DWORD));
	pDLInfo->cbSize = dwSize;
	
	dwCurOffset += CHUNK_ALIGN(sizeof(DMUS_DOWNLOADINFO));

	DMUS_OFFSETTABLE* pDMOffsetTable = (DMUS_OFFSETTABLE *)(((BYTE*)pvoid) + dwCurOffset);
	
	// Increment pass the DMUS_OFFSETTABLE structure; we will fill the other members in later
	dwCurOffset += CHUNK_ALIGN(m_cbSizeOffsetTable);

	// First entry in ulOffsetTable is the first data chunk - the DMUS_WAVE in this case.
	pDMOffsetTable->ulOffsetTable[0] = dwCurOffset;

	dwCurIndex = 2;		// First two items are DMUS_WAVE and DMUS_WAVEDATA;

	DMUS_WAVE* pDMWave = (DMUS_WAVE*)(((BYTE*)pvoid) + dwCurOffset);
	pDMWave->ulWaveDataIdx = 1;		// Point to the DMUS_WAVEDATA chunk.

	dwCurOffset += CHUNK_ALIGN(sizeof(DMUS_WAVE));

	DMUS_WAVEDATA* pDMWaveData = (DMUS_WAVEDATA*)(((BYTE*)pvoid) + dwCurOffset);
	pDMOffsetTable->ulOffsetTable[1] = dwCurOffset;
	
	DWORD dwPos = 0;
	DWORD dwRead = 0;
	
	m_dwDataSizeAfterACM = m_dwDataSizeWrite;
	hr = GetData(pDMWaveData->byData, m_dwDataSizeWrite, &dwPos, &dwRead);

	pDMWaveData->cbSize = m_dwDataSizeAfterACM; 
	
	if(SUCCEEDED(hr))
	{
		if(m_dwDataSizeWrite < DMUS_MIN_DATA_SIZE)
		{
			dwCurOffset += sizeof(DMUS_WAVEDATA);
		}
		else
		{
			dwCurOffset += sizeof(DMUS_WAVEDATA) + m_dwDataSizeWrite - DMUS_MIN_DATA_SIZE;
		}
		dwCurOffset = CHUNK_ALIGN(dwCurOffset);

		CopyMemory(&(pDMWave->WaveformatEx), &m_WaveFormatWrite, sizeof(WAVEFORMATEX));	

#ifdef DXAPI
		// Write extension chunks
		CExtensionChunk* pExtChk = m_ExtensionChunkList.GetHead();
		if(pExtChk)
		{
			pDMWave->ulFirstExtCkIdx = dwCurIndex;
		}
		else
		{
			// If no extension chunks set to zero
			pDMWave->ulFirstExtCkIdx = 0;
		}

		DWORD dwCountExtChk = m_dwCountExtChk;
		DWORD dwIndexNextExtChk = 0;
		
		for(; pExtChk && SUCCEEDED(hr); pExtChk = pExtChk->GetNext())
		{
		
			if(dwCountExtChk == 1)
			{
				dwIndexNextExtChk = 0;
			}
			else
			{
				dwIndexNextExtChk = dwCurIndex + 1;
			}
			
			pDMOffsetTable->ulOffsetTable[dwCurIndex] = dwCurOffset;
			hr = pExtChk->Write(((BYTE *)pvoid + dwCurOffset), 
								&dwCurOffset,
								dwIndexNextExtChk);
			
			dwCountExtChk--;
			dwCurIndex++;
		}
#endif
    }
#ifdef DXAPI
	if(SUCCEEDED(hr))
	{
		// Write copyright information
		if(m_pCopyright)
		{
			pDMOffsetTable->ulOffsetTable[dwCurIndex] = dwCurOffset;
			pDMWave->ulCopyrightIdx = dwCurIndex;
			hr = m_pCopyright->Write(((BYTE *)pvoid + dwCurOffset),
									 &dwCurOffset);
			dwCurIndex++;
		}
		// If instrument does not have one use collection's
		else if(m_pParent && m_pParent->m_pCopyright && (m_pParent->m_pCopyright)->m_pDMCopyright)
		{
			pDMOffsetTable->ulOffsetTable[dwCurIndex] = dwCurOffset;
			pDMWave->ulCopyrightIdx = dwCurIndex;
			hr = (m_pParent->m_pCopyright)->Write(((BYTE *)pvoid + dwCurOffset), 
												  &dwCurOffset);
			dwCurIndex++;
		}
		else
		{
			pDMWave->ulCopyrightIdx = 0;
		}
	}
	if(FAILED(hr))
	{
		ZeroMemory(pvoid, dwSize);
	}
#endif
	LeaveCriticalSection(&m_DMWaveCriticalSection);

	return hr;
}

//////////////////////////////////////////////////////////////////////
// CWaveObj::GetData

HRESULT CWaveObj::GetData(BYTE* pbBuffer, DWORD dwSize, DWORD* pdwPos, DWORD* pdwRead)
{
	// Argument validation
	assert(pbBuffer);
	assert(pdwPos);

#ifdef DBG
	if(pdwRead)
	{
		assert(pdwRead);
	}
#endif

	if(*pdwPos > (m_dwDataOffset + m_dwDataSizeWrite))
	{
		return DMUS_E_INVALIDPOS;
	}

    assert(m_pParent);

	IStream* pStream = m_pParent->m_pStream;

	// Validation
	assert(pStream);
	
	HRESULT hr = S_OK;

	LARGE_INTEGER li;
	li.QuadPart = m_dwDataOffset + *pdwPos;
	hr = pStream->Seek(li, STREAM_SEEK_SET,NULL);
	if(SUCCEEDED(hr))
	{
		if(IGNORE_ACM(m_WaveFormatRead.wFormatTag))
		{
			hr = ReadData(pStream, pbBuffer, dwSize, pdwPos, pdwRead);
		}
		else
		{
#ifdef NO_COMPRESSION_SUPPORT
			hr = E_FAIL;
#else  // NO_COMPRESSION_SUPPORT
			hr = ReadCompressedData(pStream, pbBuffer, dwSize, pdwPos, pdwRead);
#endif // NO_COMPRESSION_SUPPORT
		}
	}
	return hr;
}

#ifndef NO_COMPRESSION_SUPPORT


//////////////////////////////////////////////////////////////////////
// CWaveObj::ReadCompressedData

HRESULT CWaveObj::ReadCompressedData(IStream* pStream, BYTE* pbBuffer, DWORD dwSize, DWORD* pdwPos, DWORD* pdwRead)
{
	// Argument validation
	assert(pbBuffer);
	assert(pdwPos);
	assert(pStream);

#ifdef DBG
	if(pdwRead)
	{
		assert(pdwRead);
	}
#endif
	HRESULT hr = E_FAIL;

	DWORD dwRead = 0;

	DWORD dwLeftToRead = m_dwDataSizeRead - *pdwPos;

	DWORD dwToRead  = dwLeftToRead < dwSize ? dwLeftToRead : dwSize;

	BYTE *pbCompressedBuffer = new  BYTE[dwToRead];
	
	if(pbCompressedBuffer == NULL)
	{
		return hr;
	}
	
	hr = pStream->Read(pbCompressedBuffer, dwToRead, &dwRead);
	
	DWORD temp = m_dwDataSizeWrite;
	
	if(SUCCEEDED(hr))
	{
		WAVEFORMATEX* pwfx = NULL;
		if(m_WaveFormatRead.wFormatTag == MSAUDIO_FORMAT_TAG || m_WaveFormatRead.wFormatTag == WMAUDIO_FORMAT_TAG)
		{
			if(FAILED(hr = AllocWMAudioFormat(&m_WaveFormatRead, &pwfx)))
			{
				delete[] pbCompressedBuffer;
				return hr;
			}
		}
		else
		{
			pwfx = (WAVEFORMATEX*) new BYTE[sizeof(m_WaveFormatRead) + m_WaveFormatRead.cbSize];
			if(pwfx == NULL)
			{
				delete[] pbCompressedBuffer;
				return E_OUTOFMEMORY;
			}
		
			CopyMemory(pwfx, &m_WaveFormatRead, sizeof(m_WaveFormatRead));
			if(m_pExtractWaveFormatData)
			{
				CopyMemory((((BYTE *)pwfx) + sizeof(m_WaveFormatRead)), m_pExtractWaveFormatData, m_WaveFormatRead.cbSize); 
			}
		}

		assert(pwfx);

		hr = DecompressWave(pwfx, 
							&m_WaveFormatWrite, 
							pbCompressedBuffer,
							pbBuffer,
							dwToRead, 
							temp);

		if(SUCCEEDED(hr))
		{
			*pdwPos += dwRead;
		}

		if(pdwRead)
		{
			if(SUCCEEDED(hr))
			{
				*pdwRead = dwRead;
			}
			else
			{
				*pdwRead = 0;
			}
		}

		if(pwfx)
		{
			delete[] pwfx;
		}
	}
	else
	{
		if(pdwRead)
		{
			*pdwRead = 0;
		}
	}

	delete[] pbCompressedBuffer;

	return hr;
}

#endif // ! NO_COMPRESSION_SUPPORT

//////////////////////////////////////////////////////////////////////
// CWaveObj::ReadData

HRESULT CWaveObj::ReadData(IStream* pStream, BYTE* pbBuffer, DWORD dwSize, DWORD* pdwPos, DWORD* pdwRead)
{
	// Argument validation
	assert(pbBuffer);
	assert(pdwPos);
	assert(pStream);

#ifdef DBG
	if(pdwRead)
	{
		assert(pdwRead);
	}
#endif

	HRESULT hr = E_FAIL;

	DWORD dwRead = 0;

	DWORD dwLeftToRead = m_dwDataSizeRead - *pdwPos;

	DWORD dwToRead  = dwLeftToRead < dwSize ? dwLeftToRead : dwSize;

	hr = pStream->Read(pbBuffer, dwToRead, &dwRead);

	if(SUCCEEDED(hr))
	{
		if(pdwRead)
		{
			*pdwRead = dwRead;
		}

		*pdwPos += dwRead;
	}
	else
	{
		if(pdwRead)
		{
			*pdwRead = 0;
		}
	}

	return hr;
}


#ifndef NO_COMPRESSION_SUPPORT

//////////////////////////////////////////////////////////////////////
// CWaveObj::CalcDataSize

HRESULT CWaveObj::CalcDataSize(DWORD *pdwSize)
{
	assert(pdwSize);

    WAVEFORMATEX *pwfx = NULL;
    if(m_WaveFormatRead.wFormatTag == MSAUDIO_FORMAT_TAG || m_WaveFormatRead.wFormatTag == WMAUDIO_FORMAT_TAG)
	{
		if(FAILED(AllocWMAudioFormat(&m_WaveFormatRead, &pwfx)))
		{
			return E_FAIL;
		}
	}
    else
    {
	    pwfx = (WAVEFORMATEX *) new BYTE[sizeof(m_WaveFormatRead) + m_WaveFormatRead.cbSize];

	    if(pwfx == NULL)
	    {
		    *pdwSize = 0;		
		    return E_FAIL;
	    }
	    
	    CopyMemory(pwfx, &m_WaveFormatRead, sizeof(m_WaveFormatRead));
	    if(m_pExtractWaveFormatData)
	    {
		    CopyMemory((((BYTE *)pwfx) + sizeof(m_WaveFormatRead)), m_pExtractWaveFormatData, m_WaveFormatRead.cbSize); 
	    }
    }

    assert(pwfx);

	HACMSTREAM has;
	MMRESULT mmr = acmStreamOpen(&has, NULL, pwfx, &m_WaveFormatWrite, NULL, 0, 0, 0);
	
	if(mmr != MMSYSERR_NOERROR)
	{
		*pdwSize = 0;
		delete [] (BYTE *)pwfx;
		return E_FAIL;	
	}

	mmr = acmStreamSize(has, m_dwDataSizeRead, pdwSize, ACM_STREAMSIZEF_SOURCE);

	if(mmr != MMSYSERR_NOERROR || *pdwSize == 0)
	{
		*pdwSize = 0;
		acmStreamClose(has, 0);
		delete [] (BYTE *)pwfx;
		return E_FAIL;	
	}

	mmr = acmStreamClose(has, 0);

	if(mmr != MMSYSERR_NOERROR)
	{
		*pdwSize = 0;
		delete [] (BYTE *)pwfx;
		return E_FAIL;
	}

	delete [] (BYTE *)pwfx;

	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// CWaveObj::CanDecompress

HRESULT CWaveObj::CanDecompress()
{
	HRESULT hr = E_FAIL;

	ZeroMemory(&m_WaveFormatWrite, sizeof(m_WaveFormatWrite));
	m_WaveFormatWrite.wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormatWrite.nChannels = 1;
	m_WaveFormatWrite.wBitsPerSample = 16;

	WAVEFORMATEX* pwfx = NULL; 
	
	if(SUCCEEDED(hr = AllocWMAudioFormat(&m_WaveFormatRead, &pwfx)))
	{
		pwfx = (WAVEFORMATEX *) new BYTE[sizeof(m_WaveFormatRead) + m_WaveFormatRead.cbSize];
		if(pwfx == NULL)
		{
			return E_OUTOFMEMORY;
		}
		
		CopyMemory(pwfx, &m_WaveFormatRead, sizeof(m_WaveFormatRead));
		if(m_pExtractWaveFormatData)
		{
			CopyMemory((((BYTE *)pwfx) + sizeof(m_WaveFormatRead)), m_pExtractWaveFormatData, m_WaveFormatRead.cbSize); 
		}
	}
	else
	{
	    pwfx = &m_WaveFormatRead;
	}

	assert(pwfx);

	if(m_fReadDecompressionFormat == TRUE)
    {
        CopyMemory(&m_WaveFormatWrite, &m_WaveFormatDecompress, sizeof(m_WaveFormatDecompress));
        hr = S_OK;
    }
    else
    {
		// We first try to find a driver that can support wBitsPerSample == 16 if we can not find one 
		// then we try to find a driver that can support wBitsPerSample == 8. If we do not find either we 
		// return an error since we can not decompress.
		MMRESULT mmr = acmFormatSuggest(NULL,
										pwfx,
										&m_WaveFormatWrite,
										sizeof(WAVEFORMATEX),
										ACM_FORMATSUGGESTF_NCHANNELS 
										| ACM_FORMATSUGGESTF_WBITSPERSAMPLE 
										| ACM_FORMATSUGGESTF_WFORMATTAG);


		if(mmr != MMSYSERR_NOERROR)
		{
			m_WaveFormatWrite.wBitsPerSample = 8;
			
			MMRESULT mmr = acmFormatSuggest(NULL,
											pwfx,
											&m_WaveFormatWrite,
											sizeof(WAVEFORMATEX),
											ACM_FORMATSUGGESTF_NCHANNELS 
											| ACM_FORMATSUGGESTF_WBITSPERSAMPLE 
											| ACM_FORMATSUGGESTF_WFORMATTAG);
		}

		if(mmr == MMSYSERR_NOERROR) 
		{
			hr = S_OK;
		}
	}

	if (pwfx && pwfx != &m_WaveFormatRead)
	{
		delete[] (BYTE*)pwfx;
	}

	return hr; 
}

//////////////////////////////////////////////////////////////////////
// CWaveObj::DecompressWave

HRESULT CWaveObj::DecompressWave(WAVEFORMATEX *pwfxSrc, 
								 WAVEFORMATEX *pwfxDst, 
								 BYTE *pbCompressedBuffer,
								 BYTE *pbDecompressBuffer,
								 DWORD dwSizeCompressed, 
								 DWORD dwSizeDecompressed)
{
	// We're just fooling the compressor!
    WORD wOriginalSampleRate = (WORD)pwfxDst->nSamplesPerSec;
    if(pwfxSrc->nSamplesPerSec != pwfxDst->nSamplesPerSec)
    {
        pwfxDst->nSamplesPerSec = pwfxSrc->nSamplesPerSec;
        pwfxDst->nAvgBytesPerSec = pwfxDst->nSamplesPerSec * pwfxDst->nBlockAlign;
    }

	HACMSTREAM has;
	MMRESULT mmr = acmStreamOpen(&has, NULL, pwfxSrc, pwfxDst, NULL, 0, 0, 0);
	
	if(mmr != MMSYSERR_NOERROR)
	{
		return E_FAIL;	
	}

	ACMSTREAMHEADER ashdr;
	ZeroMemory(&ashdr, sizeof(ashdr));
	ashdr.cbStruct = sizeof(ashdr);
	ashdr.pbSrc = pbCompressedBuffer;
	ashdr.cbSrcLength = dwSizeCompressed;
	ashdr.cbDstLength = dwSizeDecompressed;
	ashdr.pbDst = pbDecompressBuffer;
	
	mmr = acmStreamPrepareHeader(has, &ashdr, 0);
	
	if(mmr != MMSYSERR_NOERROR || (ashdr.fdwStatus & ACMSTREAMHEADER_STATUSF_PREPARED) == 0)
	{
		acmStreamClose(has, 0);
		return E_FAIL;	
	}

	mmr = acmStreamConvert(has, &ashdr, 0);

	DWORD dwTemp = ashdr.cbDstLength;
    m_dwDataSizeAfterACM = ashdr.cbDstLengthUsed;

	// Need to reset or acmStreamUnprepareHeader will return with an error
	ashdr.cbSrcLength = dwSizeCompressed;
	ashdr.cbDstLength = dwSizeDecompressed;

	if(mmr != MMSYSERR_NOERROR)
	{
		acmStreamUnprepareHeader(has, &ashdr, 0);
		acmStreamClose(has, 0);
		return E_FAIL;	
	}

	mmr = acmStreamUnprepareHeader(has, &ashdr, 0);
	if(mmr != MMSYSERR_NOERROR)
	{
		acmStreamClose(has, 0);		
		return E_FAIL;	
	}
	
	m_dwDataSizeWrite = dwTemp;

	mmr = acmStreamClose(has, 0);

	return mmr == MMSYSERR_NOERROR ? S_OK : E_FAIL;
}



HRESULT CWaveObj::AllocWMAudioFormat(const WAVEFORMATEX* pwfxSrc, WAVEFORMATEX** ppwfxWMAudioWave)
{
	assert(pwfxSrc);
	if(pwfxSrc == NULL)
	{
		return E_POINTER;
	}

	if(pwfxSrc->wFormatTag != 352 && pwfxSrc->wFormatTag != 353)
	{
		return E_FAIL;
	}

	// The new WAVEFORMATEX growsby the length of the key strings
	int nKeyLength = sizeof(MSAUDIO_DEC_KEY);
	DWORD nWaveFormatSize = sizeof(WAVEFORMATEX) + pwfxSrc->cbSize + nKeyLength;

	WAVEFORMATEX* pwfxTemp = (WAVEFORMATEX*)(new BYTE[nWaveFormatSize]);
    if(pwfxTemp == NULL)
    {
        return E_OUTOFMEMORY;
    }
	
	ZeroMemory(pwfxTemp, nWaveFormatSize);

	// Copy the old values
	CopyMemory(pwfxTemp, pwfxSrc, sizeof(WAVEFORMATEX));
	CopyMemory((((BYTE*)pwfxTemp) + sizeof(WAVEFORMATEX)), m_pExtractWaveFormatData, pwfxSrc->cbSize); 

	// Copy the key string 
	strcpy((char*)(pwfxTemp) + sizeof(WAVEFORMATEX) + pwfxTemp->cbSize, MSAUDIO_DEC_KEY);
	pwfxTemp->cbSize += sizeof(MSAUDIO_DEC_KEY);

	*ppwfxWMAudioWave = pwfxTemp;

	return S_OK;
}

#endif // ! NO_COMPRESSION_SUPPORT
