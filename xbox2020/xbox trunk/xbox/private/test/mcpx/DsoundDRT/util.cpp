/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       util.cpp
 *  Content:    DirectSound utility functions.
 *  History:
 *   Date       By      Reason
 *   ====       ==      ======
 *  06/07/01    dereks  Created.
 *
 ****************************************************************************/

#include "util.h"

/****************************************************************************
 *
 *  __MALLOC
 *
 *  Description:
 *      Allocates memory (duh).
 *
 *  Arguments:
 *      DWORD [in]: number of bytes to allocate.
 *
 *  Returns:  
 *      LPVOID: base pointer.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "__MALLOC"

LPVOID
__MALLOC
(
    DWORD                   dwSize
)
{

#ifdef ALLOC_ALIGNED

    static const DWORD      dwAlignment     = PAGE_SIZE;

#else // ALLOC_ALIGNED

    static const DWORD      dwAlignment     = 4;

#endif // ALLOC_ALIGNED

#ifdef ALLOC_NOCACHE

    static const DWORD      dwFlags         = PAGE_READWRITE | PAGE_NOCACHE;

#else // ALLOC_NOCACHE

    static const DWORD      dwFlags         = PAGE_READWRITE;

#endif // ALLOC_NOCACHE

#ifdef ALLOC_CONTIGUOUS

 //   return MmAllocateContiguousMemoryEx(dwSize, 0, 0xFFFFFFFF, dwAlignment, dwFlags);
	return XPhysicalAlloc( dwSize, MAXULONG_PTR, 0, PAGE_READWRITE | PAGE_NOCACHE );

#else // ALLOC_CONTIGUOUS

    DWORD                   dwAllocSize     = dwSize;
    DWORD                   dwOffset;
    LPVOID                  pvBuffer;
    DWORD                   dwOldProtect;
    BOOL                    fProtect;

#ifdef ALLOC_GUARD_PAGE

    dwAllocSize += (PAGE_SIZE * 2) - 1;

#ifndef ALLOC_ALIGNED

    dwAllocSize += sizeof(DWORD);

#endif // ALLOC_ALIGNED

    dwAllocSize /= PAGE_SIZE;
    dwAllocSize *= PAGE_SIZE;

#endif // ALLOC_GUARD_PAGE

    if(pvBuffer = VirtualAlloc(NULL, dwAllocSize, MEM_COMMIT, dwFlags))
    {

#ifdef ALLOC_GUARD_PAGE

        fProtect = VirtualProtect((LPBYTE)pvBuffer + dwAllocSize - PAGE_SIZE, PAGE_SIZE, PAGE_NOACCESS, &dwOldProtect);
        ASSERT(fProtect);

#ifndef ALLOC_ALIGNED

        dwOffset = dwAllocSize - dwSize - PAGE_SIZE;

        pvBuffer = (LPBYTE)pvBuffer + dwOffset;

        *((LPDWORD)pvBuffer - 1) = dwOffset;

#endif // ALLOC_ALIGNED

#endif // ALLOC_GUARD_PAGE

    }

    return pvBuffer;

#endif // ALLOC_CONTIGUOUS

}


/****************************************************************************
 *
 *  __FREE
 *
 *  Description:
 *      Frees memory allocated with __MALLOC.
 *
 *  Arguments:
 *      LPVOID * [in/out]: base pointer.
 *
 *  Returns:  
 *      (void)
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "__FREE"

void
__FREE
(
    LPVOID *                ppvBuffer
)
{

    LPVOID                  pvBuffer    = *ppvBuffer;
    DWORD                   dwOffset;

    *ppvBuffer = NULL;

    if(pvBuffer)
    {

#ifdef ALLOC_CONTIGUOUS

//        MmFreeContiguousMemory(pvBuffer);
		XPhysicalFree( pvBuffer );

#else // ALLOC_CONTIGUOUS

#if defined(ALLOC_ALIGNED) || !defined(ALLOC_GUARD_PAGE)

        dwOffset = 0;

#else // defined(ALLOC_ALIGNED) || !defined(ALLOC_GUARD_PAGE)

        dwOffset = *((LPDWORD)pvBuffer - 1);

#endif // defined(ALLOC_ALIGNED) || !defined(ALLOC_GUARD_PAGE)
    
        VirtualFree((LPBYTE)pvBuffer - dwOffset, 0, MEM_RELEASE);

#endif // ALLOC_CONTIGUOUS

    }
}


/****************************************************************************
 *
 *  ReadXMO
 *
 *  Description:
 *      Reads data from an XMO.
 *
 *  Arguments:
 *      XMediaObject * [in]: XMO.
 *      LPVOID [out]: data buffer.
 *      DWORD [in]: data buffer size.
 *      LPDWORD [out]: amount read.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "ReadXMO"

HRESULT
ReadXMO
(
    XMediaObject *          pMediaObject,
    LPVOID                  pvBuffer,
    DWORD                   dwBufferSize,
    LPDWORD                 pdwRead
)
{
    HANDLE                  hCompletionEvent    = NULL;
    XMEDIAINFO              xmi;
    XMEDIAPACKET            xmp;
    HRESULT                 hr;

    //
    // Check to see if the XMO is ASYNC.  It's massive overhead to do this
    // every time we want to read, but hey, it's test code.
    //

    ZeroMemory(&xmi, sizeof(xmi));

    hr = ValidateResult(pMediaObject->GetInfo(&xmi));

    //
    // If we are ASYNC, create an event so we can simulate SYNC.
    //
    
    if(SUCCEEDED(hr) && (xmi.dwFlags & XMO_STREAMF_OUTPUT_ASYNC))
    {
        hCompletionEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    }

    //
    // Read from the XMO
    //

    if(SUCCEEDED(hr))
    {
        ZeroMemory(&xmp, sizeof(xmp));

        xmp.pvBuffer = pvBuffer;
        xmp.dwMaxSize = dwBufferSize,
        xmp.pdwCompletedSize = pdwRead;
        xmp.hCompletionEvent = hCompletionEvent;

        hr = ValidateResult(pMediaObject->Process(NULL, &xmp));
    }

    //
    // Wait for processing to complete
    //

    if(SUCCEEDED(hr) && hCompletionEvent)
    {
        WaitForSingleObject(hCompletionEvent, INFINITE);
    }

    //
    // Clean up
    //

    SAFECLOSEHANDLE(hCompletionEvent);

    return hr;
}


/****************************************************************************
 *
 *  WriteXMO
 *
 *  Description:
 *      Writes data to an XMO.
 *
 *  Arguments:
 *      XMediaObject * [in]: XMO.
 *      LPVOID [out]: data buffer.
 *      DWORD [in]: data buffer size.
 *      LPDWORD [out]: amount written.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "WriteXMO"

HRESULT
WriteXMO
(
    XMediaObject *          pMediaObject,
    LPVOID                  pvBuffer,
    DWORD                   dwBufferSize,
    LPDWORD                 pdwWritten
)
{
    HANDLE                  hCompletionEvent    = NULL;
    XMEDIAINFO              xmi;
    XMEDIAPACKET            xmp;
    HRESULT                 hr;

    //
    // Check to see if the XMO is ASYNC.  It's massive overhead to do this
    // every time we want to read, but hey, it's test code.
    //

    ZeroMemory(&xmi, sizeof(xmi));

    hr = ValidateResult(pMediaObject->GetInfo(&xmi));

    //
    // If we are ASYNC, create an event so we can simulate SYNC.
    //
    
    if(SUCCEEDED(hr) && (xmi.dwFlags & XMO_STREAMF_OUTPUT_ASYNC))
    {
        hCompletionEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    }

    //
    // Write to the XMO
    //

    if(SUCCEEDED(hr))
    {
        ZeroMemory(&xmp, sizeof(xmp));

        xmp.pvBuffer = pvBuffer;
        xmp.dwMaxSize = dwBufferSize,
        xmp.pdwCompletedSize = pdwWritten;
        xmp.hCompletionEvent = hCompletionEvent;

        hr = ValidateResult(pMediaObject->Process(&xmp, NULL));
    }

    //
    // Wait for processing to complete
    //

    if(SUCCEEDED(hr) && hCompletionEvent)
    {
        WaitForSingleObject(hCompletionEvent, INFINITE);
    }

    //
    // Clean up
    //

    SAFECLOSEHANDLE(hCompletionEvent);

    return hr;
}


/****************************************************************************
 *
 *  TransformXMO
 *
 *  Description:
 *      Passes data through a transform XMO.
 *
 *  Arguments:
 *      XMediaObject * [in]: XMO.
 *      LPCVOID [in]: source buffer.
 *      DWORD [in]: source buffer size.
 *      LPDWORD [out]: amount read.
 *      LPVOID [in]: destination buffer.
 *      DWORD [in]: destination buffer size.
 *      LPDWORD [out]: amount written.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "TransformXMO"

HRESULT
TransformXMO
(
    XMediaObject *          pMediaObject,
    LPCVOID                 pvSource,
    DWORD                   dwSourceSize,
    LPDWORD                 pdwRead,
    LPVOID                  pvDest,
    DWORD                   dwDestSize,
    LPDWORD                 pdwWritten
)
{
    XMEDIAINFO              xmi;
    XMEDIAPACKET            xmpInput;
    XMEDIAPACKET            xmpOutput;
    HRESULT                 hr;

#ifdef TRANSFORMXMO_SINGLEBLOCK

    DWORD                   dwTotalRead     = 0;
    DWORD                   dwTotalWritten  = 0;
    DWORD                   dwRead;
    DWORD                   dwWritten;

#endif // TRANSFORMXMO_SINGLEBLOCK

    //
    // Verify that the XMO is synchronous
    //

    ZeroMemory(&xmi, sizeof(xmi));

    hr = ValidateResult(pMediaObject->GetInfo(&xmi));

    if(SUCCEEDED(hr))
    {
		ASSERT(!(xmi.dwFlags & (XMO_STREAMF_INPUT_ASYNC | XMO_STREAMF_OUTPUT_ASYNC)));
    }

    //
    // Call the XMO
    //

    if(SUCCEEDED(hr))
    {
        ZeroMemory(&xmpInput, sizeof(xmpInput));
        ZeroMemory(&xmpOutput, sizeof(xmpOutput));

#ifdef TRANSFORMXMO_SINGLEBLOCK

        while(SUCCEEDED(hr) && (dwTotalRead < dwSourceSize) && (dwTotalWritten < dwDestSize))
        {
            xmpInput.pvBuffer = (LPBYTE)pvSource + dwTotalRead;
            xmpInput.dwMaxSize = min(xmi.dwInputSize, dwSourceSize - dwTotalRead);
            xmpInput.pdwCompletedSize = &dwRead;

            xmpOutput.pvBuffer = (LPBYTE)pvDest + dwTotalWritten;
            xmpOutput.dwMaxSize = min(xmi.dwOutputSize, dwDestSize - dwTotalWritten);
            xmpOutput.pdwCompletedSize = &dwWritten;

#else // TRANSFORMXMO_SINGLEBLOCK

            xmpInput.pvBuffer = (LPVOID)pvSource;
            xmpInput.dwMaxSize = dwSourceSize,
            xmpInput.pdwCompletedSize = pdwRead;

            xmpOutput.pvBuffer = pvDest;
            xmpOutput.dwMaxSize = dwDestSize,
            xmpOutput.pdwCompletedSize = pdwWritten;

#endif // TRANSFORMXMO_SINGLEBLOCK

            hr = ValidateResult(pMediaObject->Process(&xmpInput, &xmpOutput));

#ifdef TRANSFORMXMO_SINGLEBLOCK

            dwTotalRead += dwRead;
            dwTotalWritten += dwWritten;
        }

#endif // TRANSFORMXMO_SINGLEBLOCK

    }

#ifdef TRANSFORMXMO_SINGLEBLOCK

    if(SUCCEEDED(hr) && pdwRead)
    {
        *pdwRead = dwTotalRead;
    }

    if(SUCCEEDED(hr) && pdwWritten)
    {
        *pdwWritten = dwTotalWritten;
    }

#endif // TRANSFORMXMO_SINGLEBLOCK

    return hr;
}


/****************************************************************************
 *
 *  LoadWaveFile
 *
 *  Description:
 *      Loads a wave file into an XMO object.
 *
 *  Arguments:
 *      LPCSTR [in]: file name.
 *      LPCWAVEFORMATEX [out]: wave file format.
 *      XMediaObject ** [out]: wave file XMO.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "LoadWaveFile"

HRESULT
LoadWaveFile
(
    LPCSTR                  pszFileName,
    LPCWAVEFORMATEX *       ppwfxFormat,
    XFileMediaObject **     ppMediaObject
)
{
    DbgPrint("Loading %s\n", pszFileName);

    return ValidateResult(XWaveFileCreateMediaObject(pszFileName, ppwfxFormat, 
													 ppMediaObject));
}


/****************************************************************************
 *
 *  GetStdWaveFile
 *
 *  Description:
 *      Gets a standard wave file path.
 *
 *  Arguments:
 *      LPCWAVEFORMATEX [in]: format.
 *      LPSTR [out]: file path.
 *
 *  Returns:  
 *      (void)
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "GetStdWaveFile"

void
GetStdWaveFile
(
    LPCWAVEFORMATEX         pwfxFormat,
    LPSTR                   pszFileName
)
{
    static const LPCSTR     pszParent       = "t:\\media\\audio\\";
    static const LPCSTR     pszPcm          = "pcm\\";
    static const LPCSTR     pszAdpcm        = "adpcm\\";
    static const LPCSTR     pszFileTemplate = "%uk%ub%ls.wav";
    static const LPCSTR     pszMono         = "m";
    static const LPCSTR     pszStereo       = "s";

    strcpy(pszFileName, pszParent);

    switch(pwfxFormat->wFormatTag)
    {
        case WAVE_FORMAT_PCM:
            strcat(pszFileName, pszPcm);
            break;

        case WAVE_FORMAT_XBOX_ADPCM:
            strcat(pszFileName, pszAdpcm);
            break;

        default:
            ASSERT(!"Unsupported format");
            break;
    }

    sprintf(pszFileName + strlen(pszFileName), pszFileTemplate, pwfxFormat->nSamplesPerSec / 1000, pwfxFormat->wBitsPerSample, (1 == pwfxFormat->nChannels) ? pszMono : pszStereo);
}


/****************************************************************************
 *
 *  GetStdWaveFile
 *
 *  Description:
 *      Gets a standard wave file path.
 *
 *  Arguments:
 *      LPCWAVEFORMATEX [in]: format.
 *
 *  Returns:  
 *      LPSTR: file path.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "GetStdWaveFile"

LPCSTR
GetStdWaveFile
(
    LPCWAVEFORMATEX         pwfxFormat
)
{
    static CHAR             szFileName[MAX_PATH];

    GetStdWaveFile(pwfxFormat, szFileName);

    return szFileName;
}


/****************************************************************************
 *
 *  LoadWaveFile
 *
 *  Description:
 *      Loads a standard wave file into an XMO object.
 *
 *  Arguments:
 *      LPCWAVEFORMATEX [in]: format.
 *      XMediaObject ** [out]: wave file XMO.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "LoadWaveFile"

HRESULT
LoadStdWaveFile
(
    LPCWAVEFORMATEX         pwfxFormat,
    XFileMediaObject **     ppMediaObject
)
{
    return LoadWaveFile(GetStdWaveFile(pwfxFormat), NULL, ppMediaObject);
}


/****************************************************************************
 *
 *  CreateBufferFromFile
 *
 *  Description:
 *      Creates a DirectSound buffer from a file.
 *
 *  Arguments:
 *      LPCSTR [in]: file path.
 *      DWORD [in]: buffer creation flags.
 *      DWORD [in]: output mixbin mask.
 *      DWORD [in]: submix output buffer.
 *      LPDIRECTSOUNDBUFFER * [out]: buffer.
 *      LPDWORD [in/out]: buffer size, in bytes.
 *      LPCWAVEFORMATEX [out]: buffer format.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateBufferFromFile"

HRESULT
CreateBufferFromFile
(
    LPCSTR                  pszFile, 
    DWORD                   dwFlags, 
    LPDSMIXBINS				pMixBins, 
    LPDIRECTSOUNDBUFFER     pOutputBuffer, 
    LPDIRECTSOUNDBUFFER *   ppBuffer, 
    LPDWORD                 pdwBufferBytes, 
    LPCWAVEFORMATEX *       ppwfxFormat
)
{
    LPXFILEMEDIAOBJECT      pWaveFile       = NULL;
    LPDIRECTSOUNDBUFFER     pBuffer         = NULL;
    LPCWAVEFORMATEX         pwfxFormat;
    DWORD                   dwBufferBytes;
    DSBUFFERDESC            dsbd;
    LPVOID                  pvLock;
    HRESULT                 hr;
	WIN32_FIND_DATA			findData;
	HANDLE					hFind;
	DWORD					dwFreeSGEs;

	// Max valid buffer size
	hr = GetFreeSGEs(&dwFreeSGEs);

	// Get the file size
	if(SUCCEEDED(hr))
	{
		// Determine the file size
		hFind = FindFirstFile(pszFile, &findData);
		hr = (hFind == INVALID_HANDLE_VALUE) ? E_FAIL : S_OK;
	}

	// Is the buffer too large to load?
	if(SUCCEEDED(hr))
	{
		FindClose(hFind);
		if((findData.nFileSizeHigh > 0) || 
		   (findData.nFileSizeLow > (dwFreeSGEs * 4096)))
		{
			hr = E_FAIL;
		}
	}
	
    //
    // Open the wave file
    //

	if(SUCCEEDED(hr))
		hr = ValidateResult(LoadWaveFile(pszFile, &pwfxFormat, &pWaveFile));

    if(SUCCEEDED(hr) && ppwfxFormat)
    {
        *ppwfxFormat = pwfxFormat;
    }

    //
    // Get the file size.  If it's longer than the size passed to us, trim
    // it down.
    //

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(pWaveFile->GetLength(&dwBufferBytes));
    }

    if(SUCCEEDED(hr))
    {
        hr = ClampBufferSize(&dwBufferBytes,pwfxFormat->nBlockAlign);
    }

    if(SUCCEEDED(hr) && pdwBufferBytes)
    {
        if(!*pdwBufferBytes || (*pdwBufferBytes > dwBufferBytes))
        {
            *pdwBufferBytes = dwBufferBytes;
        }
        else
        {
            dwBufferBytes = *pdwBufferBytes;
			dwBufferBytes -= dwBufferBytes % pwfxFormat->nBlockAlign;
        }
    }

    //
    // Create the buffer
    //

    if(SUCCEEDED(hr))
    {
        ZeroMemory(&dsbd, sizeof(dsbd));

        dsbd.dwSize = sizeof(dsbd);
        dsbd.dwFlags = dwFlags;
        dsbd.dwBufferBytes = dwBufferBytes;
        dsbd.lpwfxFormat = (LPWAVEFORMATEX)pwfxFormat;
        dsbd.lpMixBins = pMixBins;
        
        hr = ValidateResult(DirectSoundCreateBuffer(&dsbd, &pBuffer));
    }

    //
    // Read wave data into the buffer
    //

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(pBuffer->Lock(0, dwBufferBytes, &pvLock, &dsbd.dwBufferBytes, NULL, NULL, 0));
    }

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(ReadXMO(pWaveFile, pvLock, dwBufferBytes, &dsbd.dwBufferBytes));
    }

    if(SUCCEEDED(hr))
    {
        ASSERT(dsbd.dwBufferBytes == dwBufferBytes);

        hr = ValidateResult(pBuffer->Unlock(pvLock, dwBufferBytes, NULL, 0));
    }

    //
    // Set the output buffer
    //

    if(SUCCEEDED(hr) && pOutputBuffer)
    {
        hr = ValidateResult(pBuffer->SetOutputBuffer(pOutputBuffer));
    }

    //
    // Success
    //

    if(SUCCEEDED(hr))
    {
        ASSERT(ppBuffer);

        *ppBuffer = pBuffer;
    }
    else
    {
        RELEASE(pBuffer);
    }

    RELEASE(pWaveFile);

    return hr;
}


/****************************************************************************
 *
 *  CreateStdBuffer
 *
 *  Description:
 *      Creates a sound buffer from one of the standard wave files.
 *
 *  Arguments:
 *      DWORD [in]: buffer creation flags.
 *      LPCWAVEFORMATEX [in]: buffer format.
 *      DWORD [in]: output mixbin mask.
 *      DWORD [in]: submix output buffer.
 *      LPDIRECTSOUNDBUFFER * [out]: buffer.
 *      LPDWORD [in/out]: buffer size, in bytes.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateStdBuffer"

HRESULT
CreateStdBuffer
(
    DWORD                   dwFlags, 
    LPCWAVEFORMATEX         pwfxFormat, 
    LPDSMIXBINS				pMixBins, 
    LPDIRECTSOUNDBUFFER     pOutputBuffer, 
    LPDIRECTSOUNDBUFFER *   ppBuffer, 
    LPDWORD                 pdwBufferBytes
)
{
    return ValidateResult(CreateBufferFromFile(GetStdWaveFile(pwfxFormat), 
											   dwFlags, pMixBins, pOutputBuffer, 
											   ppBuffer, pdwBufferBytes, NULL));
}


/****************************************************************************
 *
 *  WaitBuffer
 *
 *  Description:
 *      Waits for a buffer's status to change.
 *
 *  Arguments:
 *      LPDIRECTSOUNDBUFFER [in]: buffer.
 *      BOOL [in]: TRUE to wait for the buffer to start playing, FALSE to
 *                 wait for it to stop.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "WaitBuffer"

HRESULT
WaitBuffer
(
    LPDIRECTSOUNDBUFFER     pBuffer,
    BOOL                    fPlaying
)
{
    const DWORD             dwStatusMask    = DSBSTATUS_PLAYING;
    const DWORD             dwWaitStatus    = fPlaying ? DSBSTATUS_PLAYING : 0;
    DWORD                   dwStatus;
    HRESULT                 hr;

    while(TRUE)
    {
        hr = ValidateResult(pBuffer->GetStatus(&dwStatus));

        if(FAILED(hr))
        {
            break;
        }

        if((dwStatus & dwStatusMask) == dwWaitStatus)
        {
            DbgPrint("Buffer %s", fPlaying ? "playing\n" : "stopped\n");
            break;
        }
    }

    return hr;
}


/****************************************************************************
 *
 *  PlayBuffer
 *
 *  Description:
 *      Plays a sound buffer.
 *
 *  Arguments:
 *      LPDIRECTSOUNDBUFFER [in]: buffer.
 *      BOOL [in]: TRUE to loop.
 *      DWORD [in]: delay, in milliseconds.
 *      BOOL [in]: TRUE to wait for buffer to start playing.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "PlayBuffer"

HRESULT
PlayBuffer
(
    LPDIRECTSOUNDBUFFER     pBuffer,
    BOOL                    fLoop,
    DWORD                   dwDelay,
    BOOL                    fWait
)
{
    REFERENCE_TIME          rtTimeStamp = -(LONGLONG)dwDelay * 10000;
    HRESULT                 hr;

    if(dwDelay)
    {
        DbgPrint("Playing buffer (delayed %lu ms)\n", dwDelay);
    }
    else
    {
        DbgPrint("Playing buffer\n");
        fWait = FALSE;
    }

    hr = ValidateResult(pBuffer->PlayEx(rtTimeStamp, fLoop ? DSBPLAY_LOOPING : 0));

    if(SUCCEEDED(hr) && fWait)
    {
        hr = WaitBuffer(pBuffer, TRUE);
    }

    return hr;
}


/****************************************************************************
 *
 *  PlayBufferToCompletion
 *
 *  Description:
 *      Plays a sound buffer to completion.
 *
 *  Arguments:
 *      LPDIRECTSOUNDBUFFER [in]: buffer.
 *      DWORD [in]: delay, in milliseconds.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "PlayBufferToCompletion"

HRESULT
PlayBufferToCompletion
(
    LPDIRECTSOUNDBUFFER     pBuffer,
    BOOL                    fLoop,
    DWORD                   dwDelay
)
{
    HRESULT                 hr;

    hr = PlayBuffer(pBuffer, fLoop, dwDelay, TRUE);

    if(SUCCEEDED(hr))
    {
        hr = WaitBuffer(pBuffer, FALSE);
    }

    return hr;
}


/****************************************************************************
 *
 *  StopBuffer
 *
 *  Description:
 *      Stops a sound buffer.
 *
 *  Arguments:
 *      LPDIRECTSOUNDBUFFER [in]: buffer.
 *      DWORD [in]: flags.
 *      DWORD [in]: delay, in milliseconds.
 *      BOOL [in]: TRUE to reset cursor position.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "StopBuffer"

HRESULT
StopBuffer
(
    LPDIRECTSOUNDBUFFER     pBuffer,
    DWORD                   dwFlags,
    DWORD                   dwDelay,
    BOOL                    fReset,
    BOOL                    fWait
)
{
    REFERENCE_TIME          rtTimeStamp = -(LONGLONG)dwDelay * 10000;
    HRESULT                 hr;

    if(fReset)
    {
        fWait = TRUE;
    }

    if(dwDelay)
    {
        DbgPrint("Stopping buffer (delayed %lu ms)\n", dwDelay);
    }
    else
    {
        DbgPrint("Stopping buffer\n");
    }

    hr = ValidateResult(pBuffer->StopEx(rtTimeStamp, dwFlags));

    if(SUCCEEDED(hr) && fWait)
    {
        hr = WaitBuffer(pBuffer, FALSE);
    }

    if(SUCCEEDED(hr) && fReset)
    {
        DbgPrint("Resetting cursor position\n");
        
        hr = ValidateResult(pBuffer->SetCurrentPosition(0));
    }

    return hr;
}


/****************************************************************************
 *
 *  CreateStreamFromFile
 *
 *  Description:
 *      Creates a DirectSound stream based on a given wave file.
 *
 *  Arguments:
 *      LPCSTR [in]: file path.
 *      DWORD [in]: stream creation flags.
 *      DWORD [in]: output mixbin mask.
 *      LPDWORD [in/out]: packet size, in bytes.
 *      LPFNXMEDIAOBJECTCALLBACK [in]: stream callback function.
 *      LPVOID [in]: stream callback context.
 *      LPDIRECTSOUNDBUFFER [in]: submix output buffer.
 *      LPDIRECTSOUNDSTREAM * [out]: stream object.
 *      LPVOID * [out]: audio data buffer.
 *      LPDWORD [out]: audio data buffer size, in bytes.
 *      LPDWORD [in/out]: packet count.
 *      LPCWAVEFORMATEX [out]: stream format.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateStreamFromFile"

HRESULT
CreateStreamFromFile
(
    LPCSTR                      pszFile, 
    DWORD                       dwFlags, 
    LPDSMIXBINS					pMixBins, 
    LPDWORD                     pdwPacketSize,
    LPFNXMEDIAOBJECTCALLBACK    pfnCallback,
    LPVOID                      pvContext,
    LPDIRECTSOUNDBUFFER         pOutputBuffer, 
    LPDIRECTSOUNDSTREAM *       ppStream, 
    LPVOID *                    ppvAudioData,
    LPDWORD                     pdwAudioDataSize,
    LPDWORD                     pdwPacketCount,
    LPCWAVEFORMATEX *           ppwfxFormat
)
{
    LPXFILEMEDIAOBJECT          pWaveFile       = NULL;
    LPDIRECTSOUNDSTREAM         pStream         = NULL;
    LPVOID                      pvAudioData     = NULL;
    LPCWAVEFORMATEX             pwfxFormat;
    DWORD                       dwDuration;
    DWORD                       dwPacketCount;
    DSSTREAMDESC                dssd;
    HRESULT                     hr;

    //
    // Open the wave file
    //

    hr = ValidateResult(LoadWaveFile(pszFile, &pwfxFormat, &pWaveFile));

    if(SUCCEEDED(hr) && ppwfxFormat)
    {
        *ppwfxFormat = pwfxFormat;
    }

    //
    // Block-align the packet size
    //

    if(SUCCEEDED(hr))
    {
        *pdwPacketSize /= pwfxFormat->nBlockAlign;
        *pdwPacketSize *= pwfxFormat->nBlockAlign;
    }

    //
    // Get the file size
    //

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(pWaveFile->GetLength(&dwDuration));
    }

    //
    // Allocate a buffer for the wave data
    //

    if(SUCCEEDED(hr))
    {
        hr = MALLOC(pvAudioData, BYTE, dwDuration);
    }

    //
    // Read wave data
    //

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(ReadXMO(pWaveFile, pvAudioData, dwDuration, &dwDuration));
    }

    //
    // Calculate the number of packets required
    //

    if(SUCCEEDED(hr))
    {
        dwPacketCount = dwDuration / *pdwPacketSize;
    }

    if(SUCCEEDED(hr) && pdwPacketCount)
    {
        if(!*pdwPacketCount || (*pdwPacketCount > dwPacketCount))
        {
            *pdwPacketCount = dwPacketCount;
        }
        else
        {
            dwPacketCount = *pdwPacketCount;
        }
    }

    //
    // Create the stream
    //

    if(SUCCEEDED(hr))
    {
        ZeroMemory(&dssd, sizeof(dssd));

        dssd.dwFlags = dwFlags;
        dssd.dwMaxAttachedPackets = dwPacketCount;
        dssd.lpwfxFormat = (LPWAVEFORMATEX)pwfxFormat;
        dssd.lpfnCallback = pfnCallback;
        dssd.lpvContext = pvContext;
        dssd.lpMixBins = pMixBins;

        hr = ValidateResult(DirectSoundCreateStream(&dssd, &pStream));
    }

    //
    // Set the output buffer
    //

    if(SUCCEEDED(hr) && pOutputBuffer)
    {
        hr = ValidateResult(pStream->SetOutputBuffer(pOutputBuffer));
    }

    //
    // Success
    //

    if(SUCCEEDED(hr))
    {
        *ppStream = pStream;
        *ppvAudioData = pvAudioData;
        *pdwAudioDataSize = dwDuration;
    }
    else
    {
        RELEASE(pStream);
        FREE(pvAudioData);
    }

    return hr;
}


/****************************************************************************
 *
 *  CreateStdStream
 *
 *  Description:
 *      Creates a DirectSound stream based on a standard wave file.
 *
 *  Arguments:
 *      DWORD [in]: stream creation flags.
 *      LPCWAVEFORMATEX [in]: stream format.
 *      DWORD [in]: output mixbin mask.
 *      LPDWORD [in/out]: packet size, in bytes.
 *      LPFNXMEDIAOBJECTCALLBACK [in]: stream callback function.
 *      LPVOID [in]: stream callback context.
 *      LPDIRECTSOUNDBUFFER [in]: submix output buffer.
 *      LPDIRECTSOUNDSTREAM * [out]: stream object.
 *      LPVOID * [out]: audio data buffer.
 *      LPDWORD [out]: audio data buffer size, in bytes.
 *      LPDWORD [in/out]: packet count.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateStdStream"

HRESULT
CreateStdStream
(
    DWORD                       dwFlags, 
    LPCWAVEFORMATEX             pwfxFormat,
    LPDSMIXBINS					pMixBins, 
    LPDWORD                     pdwPacketSize,
    LPFNXMEDIAOBJECTCALLBACK    pfnCallback,
    LPVOID                      pvContext,
    LPDIRECTSOUNDBUFFER         pOutputBuffer, 
    LPDIRECTSOUNDSTREAM *       ppStream, 
    LPVOID *                    ppvAudioData,
    LPDWORD                     pdwAudioDataSize,
    LPDWORD                     pdwPacketCount
)
{
    return ValidateResult(CreateStreamFromFile(GetStdWaveFile(pwfxFormat), dwFlags, pMixBins, pdwPacketSize, pfnCallback, pvContext, pOutputBuffer, ppStream, ppvAudioData, pdwAudioDataSize, pdwPacketCount));
}


/****************************************************************************
 *
 *  CreateQueuedStreamFromFile
 *
 *  Description:
 *      Creates a DirectSound stream based on a given wave file and submits
 *      data to it.
 *
 *  Arguments:
 *      LPCSTR [in]: file path.
 *      DWORD [in]: stream creation flags.
 *      DWORD [in]: output mixbin mask.
 *      LPDWORD [in/out]: packet size, in bytes.
 *      HANDLE [in]: completion event for the last packet.
 *      LPDIRECTSOUNDBUFFER [in]: submix output buffer.
 *      LPDIRECTSOUNDSTREAM * [out]: stream object.
 *      LPVOID * [out]: audio data buffer.
 *      LPCWAVEFORMATEX [out]: stream format.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateQueuedStreamFromFile"

HRESULT
CreateQueuedStreamFromFile
(
    LPCSTR                  pszFile, 
    DWORD                   dwFlags, 
    LPDSMIXBINS				pMixBins, 
    LPDWORD                 pdwPacketSize,
    HANDLE                  hCompletionEvent,
    LPDIRECTSOUNDBUFFER     pOutputBuffer, 
    LPDIRECTSOUNDSTREAM *   ppStream, 
    LPVOID *                ppvAudioData,
    LPCWAVEFORMATEX *       ppwfxFormat
)
{
    LPDIRECTSOUNDSTREAM     pStream         = NULL;
    LPVOID                  pvAudioData     = NULL;
    DWORD                   dwAudioDataSize = 0;
    DWORD                   dwPacketCount   = 0;
    XMEDIAPACKET            xmp;
    HRESULT                 hr;
    DWORD                   i;

    //
    // Create the stream
    //

    hr = ValidateResult(CreateStreamFromFile(pszFile, dwFlags, pMixBins, pdwPacketSize, NULL, NULL, pOutputBuffer, &pStream, &pvAudioData, &dwAudioDataSize, &dwPacketCount, ppwfxFormat));

    //
    // Pause the stream
    //

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(PauseStream(pStream));
    }

    //
    // Submit all packets
    //

    if(SUCCEEDED(hr))
    {
        ZeroMemory(&xmp, sizeof(xmp));

        xmp.pvBuffer = pvAudioData;
        xmp.dwMaxSize = *pdwPacketSize;
        
        for(i = 0; SUCCEEDED(hr) && (i < dwPacketCount - 1); i++)
        {
            hr = ValidateResult(pStream->Process(&xmp, NULL));

            if(SUCCEEDED(hr))
            {
                xmp.pvBuffer = (LPBYTE)xmp.pvBuffer + xmp.dwMaxSize;
            }
        }
    }

    if(SUCCEEDED(hr))
    {
        xmp.dwMaxSize = dwAudioDataSize - (*pdwPacketSize * (dwPacketCount - 1));
        xmp.hCompletionEvent = hCompletionEvent;

        hr = ValidateResult(pStream->Process(&xmp, NULL));
    }

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(pStream->Discontinuity());
    }

    //
    // Success
    //

    if(SUCCEEDED(hr))
    {
        *ppStream = pStream;
        *ppvAudioData = pvAudioData;
    }
    else
    {
        RELEASE(pStream);
        FREE(pvAudioData);
    }

    return hr;
}


/****************************************************************************
 *
 *  CreateStdQueuedStream
 *
 *  Description:
 *      Creates a DirectSound stream based on a given wave file and submits
 *      data to it.
 *
 *  Arguments:
 *      DWORD [in]: stream creation flags.
 *      LPCWAVEFORMATEX [in]: stream format.
 *      DWORD [in]: output mixbin mask.
 *      LPDWORD [in/out]: packet size, in bytes.
 *      HANDLE [in]: completion event for the last packet.
 *      LPDIRECTSOUNDBUFFER [in]: submix output buffer.
 *      LPDIRECTSOUNDSTREAM * [out]: stream object.
 *      LPVOID * [out]: audio data buffer.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateStdQueuedStream"

HRESULT
CreateStdQueuedStream
(
    DWORD                   dwFlags, 
    LPCWAVEFORMATEX         pwfxFormat,
    LPDSMIXBINS				pMixBins, 
    LPDWORD                 pdwPacketSize,
    HANDLE                  hCompletionEvent,
    LPDIRECTSOUNDBUFFER     pOutputBuffer, 
    LPDIRECTSOUNDSTREAM *   ppStream, 
    LPVOID *                ppvAudioData
)
{
    return CreateQueuedStreamFromFile(GetStdWaveFile(pwfxFormat), dwFlags, pMixBins, pdwPacketSize, hCompletionEvent, pOutputBuffer, ppStream, ppvAudioData);
}


/****************************************************************************
 *
 *  ResubmitPacketCallback
 *
 *  Description:
 *      Stream callback function that automatically resubmits the completed
 *      packet.
 *
 *  Arguments:
 *      LPVOID [in]: stream context.
 *      LPVOID [in]: packet context.
 *      DWORD [in]: packet status.
 *
 *  Returns:  
 *      (void)
 *
 ****************************************************************************/
 
#undef DPF_FNAME
#define DPF_FNAME "ResubmitPacketCallback"

void CALLBACK
ResubmitPacketCallback
(
    LPVOID                  pvStreamContext,
    LPVOID                  pvPacketContext,
    DWORD                   dwStatus
)
{
    LPXMEDIAOBJECT *        ppStream    = (LPXMEDIAOBJECT *)pvStreamContext;
    LPXMEDIAPACKET          pPacket     = (LPXMEDIAPACKET)pvPacketContext;
    
    if(XMEDIAPACKET_STATUS_SUCCESS == dwStatus)
    {
        (*ppStream)->Process(pPacket, NULL);
    }
}


/****************************************************************************
 *
 *  GenerateTone
 *
 *  Description:
 *      Generates a PCM sine-wave tone.
 *
 *  Arguments:
 *      LPVOID [out]: audio data buffer.
 *      DWORD [in]: audio data buffer size, in bytes.
 *      DWORD [in]: playback frequency.
 *      DWORD [in]: bits per sample.
 *      DWORD [in]: channel count.
 *      DWORD [in]: tone frequency.
 *
 *  Returns:  
 *      (void)
 *
 ****************************************************************************/
 
#undef DPF_FNAME
#define DPF_FNAME "GenerateTone"

void
GenerateTone
(
    LPVOID                      pvBuffer,
    DWORD                       dwBufferBytes,
    DWORD                       dwPlaybackFrequency,
    DWORD                       dwBitsPerSample,
    DWORD                       dwChannelCount,
    DWORD                       dwToneFrequency
)
{
    switch(dwBitsPerSample)
    {
        case 8:
            GenerateTone8(pvBuffer, dwBufferBytes, dwPlaybackFrequency, dwChannelCount, dwToneFrequency);
            break;

        case 16:
            GenerateTone16(pvBuffer, dwBufferBytes, dwPlaybackFrequency, dwChannelCount, dwToneFrequency);
            break;

        default:
            ASSERT(!"Unexpected bit resolution");
            break;
    }            
}


/****************************************************************************
 *
 *  GenerateTone8
 *
 *  Description:
 *      Generates an 8-bit sine-wave tone.
 *
 *  Arguments:
 *      LPVOID [out]: audio data buffer.
 *      DWORD [in]: audio data buffer size, in bytes.
 *      DWORD [in]: playback frequency.
 *      DWORD [in]: channel count.
 *      DWORD [in]: tone frequency.
 *
 *  Returns:  
 *      (void)
 *
 ****************************************************************************/
 
#undef DPF_FNAME
#define DPF_FNAME "GenerateTone8"

void
GenerateTone8
(
    LPVOID                      pvBuffer,
    DWORD                       dwBufferBytes,
    DWORD                       dwPlaybackFrequency,
    DWORD                       dwChannelCount,
    DWORD                       dwToneFrequency
)
{
    static const double         dbScale     = 255.0;
    static const unsigned char  bHalfScale  = 128;
    const double                dbPhase     = 2.0 * D3DX_PI / (double)dwPlaybackFrequency;
    const double                dbFactor    = dbPhase * (double)dwToneFrequency;
    unsigned char *             pbBuffer    = (unsigned char *)pvBuffer;
    unsigned char               bSample;
    DWORD                       i, z;

    for(i = 0; i < dwBufferBytes / dwChannelCount; i++)
    {
        bSample = (unsigned char)(sin((double)i * dbFactor) * dbScale) + bHalfScale;

        for(z = 0; z < dwChannelCount; z++)
        {
            *pbBuffer++ = bSample;
        }
    }
}


/****************************************************************************
 *
 *  GenerateTone16
 *
 *  Description:
 *      Generates a 16-bit sine-wave tone.
 *
 *  Arguments:
 *      LPVOID [out]: audio data buffer.
 *      DWORD [in]: audio data buffer size, in bytes.
 *      DWORD [in]: channel count.
 *      DWORD [in]: playback frequency.
 *      DWORD [in]: tone frequency.
 *
 *  Returns:  
 *      (void)
 *
 ****************************************************************************/
 
#undef DPF_FNAME
#define DPF_FNAME "GenerateTone16"

void
GenerateTone16
(
    LPVOID                  pvBuffer,
    DWORD                   dwBufferBytes,
    DWORD                   dwPlaybackFrequency,
    DWORD                   dwChannelCount,
    DWORD                   dwToneFrequency
)
{
    static const double     dbScale     = 32767.0;
    const double            dbPhase     = 2.0 * D3DX_PI / (double)dwPlaybackFrequency;
    const double            dbFactor    = dbPhase * (double)dwToneFrequency;
    short *                 pnBuffer    = (short *)pvBuffer;
    short                   nSample;
    DWORD                   i, z;

    for(i = 0; i < dwBufferBytes / (2 * dwChannelCount); i++)
    {
        nSample = (short)(sin((double)i * dbFactor) * dbScale);

        for(z = 0; z < dwChannelCount; z++)
        {
            *pnBuffer++ = nSample;
        }
    }
}


/****************************************************************************
 *
 *  GenerateNoise
 *
 *  Description:
 *      Generates white noise.
 *
 *  Arguments:
 *      LPVOID [out]: audio data buffer.
 *      DWORD [in]: audio data buffer size, in bytes.
 *
 *  Returns:  
 *      (void)
 *
 ****************************************************************************/
 
#undef DPF_FNAME
#define DPF_FNAME "GenerateNoise"

void
GenerateNoise
(
    LPVOID                  pvBuffer,
    DWORD                   dwBufferSize
)
{
    DWORD                   i;

    for(i = 0; i < dwBufferSize; i++)
    {
        *(((LPBYTE)pvBuffer) + i) = (BYTE)(rand() % 0xFF);
    }
}


/****************************************************************************
 *
 *  MakeMultiChannel
 *
 *  Description:
 *      Converts a mono or stereo PCM sound file to multichannel.
 *
 *  Arguments:
 *      LPCWAVEFORMATEX [in]: source format.
 *      LPWAVEFORMATEX [out]: destination format.  Only nChannels needs to
 *                            be filled in.
 *      LPCVOID [in]: source data.
 *      DWORD [in]: source data size, in bytes.
 *      LPVOID * [out]: destination data.
 *      LPDWORD [out]: destinatin data size, in bytes.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "MakeMultiChannel"

HRESULT
MakeMultiChannel
(
    LPCWAVEFORMATEX         pwfxSrc,
    LPWAVEFORMATEX          pwfxDst,
    LPCVOID                 pvSrcData,
    DWORD                   dwSrcDataSize,
    LPVOID *                ppvDstData,
    LPDWORD                 pdwDstDataSize
)
{
    LPVOID                  pvDstData;
    DWORD                   dwDstDataSize;
    DWORD                   dwMultiplier;
    DWORD                   dwSampleCount;
    HRESULT                 hr;
    DWORD                   a, b;

    ASSERT(WAVE_FORMAT_PCM == pwfxSrc->wFormatTag);
    ASSERT(!(pwfxDst->nChannels % pwfxSrc->nChannels));
    
    XAudioCreatePcmFormat(pwfxDst->nChannels, pwfxSrc->nSamplesPerSec, pwfxSrc->wBitsPerSample, pwfxDst);

    dwMultiplier = pwfxDst->nChannels / pwfxSrc->nChannels;
    dwSampleCount = dwSrcDataSize / pwfxSrc->nBlockAlign;
    dwDstDataSize = dwSampleCount * pwfxDst->nBlockAlign;

    hr = MALLOC(pvDstData, BYTE, dwDstDataSize);

    if(SUCCEEDED(hr))
    {
        *ppvDstData = pvDstData;
        *pdwDstDataSize = dwDstDataSize;

        while(dwSampleCount--)
        {
            for(a = 0; a < dwMultiplier; a++)
            {
                for(b = 0; b < pwfxSrc->nChannels; b++)
                {
                    if(8 == pwfxSrc->wBitsPerSample)
                    {
                        *(unsigned char *)pvDstData = *(const unsigned char *)pvSrcData;
                        pvDstData = (unsigned char *)pvDstData + 1;
                    }
                    else
                    {
                        *(short *)pvDstData = *(const short *)pvSrcData;
                        pvDstData = (short *)pvDstData + 1;
                    }
                }
            }

            pvSrcData = (LPBYTE)pvSrcData + pwfxSrc->nBlockAlign;
        }
    }

    return hr;
}


/****************************************************************************
 *
 *  PauseStream
 *
 *  Description:
 *      Pauses or resumes a stream.
 *
 *  Arguments:
 *      LPDIRECTSOUNDSTREAM [in]: stream.
 *      BOOL [in]: TRUE to pause, FALSE to resume.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "PauseStream"

HRESULT
PauseStream
(
    LPDIRECTSOUNDSTREAM     pStream,
    BOOL                    fPause
)
{
    HRESULT                 hr;

    if(fPause)
    {
        DbgPrint("Pausing stream\n");
    }
    else
    {
        DbgPrint("Resuming paused stream\n");
    }

    hr = ValidateResult(pStream->Pause(fPause));

    return hr;
}


/****************************************************************************
 *
 *  CreateFormat
 *
 *  Description:
 *      Creates a WAVEFORMATEX structure.
 *
 *  Arguments:
 *      DWORD [in]: format tag.
 *      DWORD [in]: sampling rate.
 *      DWORD [in]: bit resolution.
 *      DWORD [in]: channel count.
 *
 *  Returns:  
 *      LPCWAVEFORMATEX: format data.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateFormat"

LPCWAVEFORMATEX
CreateFormat
(
    DWORD                   dwFormatTag,
    DWORD                   dwSamplesPerSec,
    DWORD                   dwBitsPerSample,
    DWORD                   dwChannels
)
{
    static UNIWAVEFORMAT    wfx;
    
    switch(dwFormatTag)
    {
        case WAVE_FORMAT_PCM:
            XAudioCreatePcmFormat((WORD)dwChannels, dwSamplesPerSec, (WORD)dwBitsPerSample, &wfx.wfx);
            break;

        case WAVE_FORMAT_XBOX_ADPCM:
            XAudioCreateAdpcmFormat((WORD)dwChannels, dwSamplesPerSec, &wfx.wfAdpcm);
            break;

        default:
            ASSERT(!"Unexpected format tag");
            break;
    }

    return &wfx.wfx;
}


/****************************************************************************
 *
 *  GetFreeSGEs
 *
 *  Description:
 *      Gets the count of free buffer SGEs.
 *
 *  Arguments:
 *      LPDWORD [out]: SGE count.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "GetFreeSGEs"

HRESULT
GetFreeSGEs
(
    LPDWORD                 pdwFreeSGEs
)
{
    DSCAPS                  dsc;
    HRESULT                 hr;
    
    hr = ValidateResult(GetDirectSoundCaps(&dsc));

    if(SUCCEEDED(hr))
    {
        *pdwFreeSGEs = dsc.dwFreeBufferSGEs-1;
    }

    return hr;
}


/****************************************************************************
 *
 *  ClampBufferSize
 *
 *  Description:
 *      Clamps a buffer size so that it will fit in the available SGEs.
 *
 *  Arguments:
 *      LPDWORD [in/out]: buffer size, in bytes.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "ClampBufferSize"

HRESULT
ClampBufferSize
(
    LPDWORD                 pdwBufferBytes,
	DWORD					dwBlockAlign
)
{

#ifdef ALLOC_CONTIGUOUS

    static const DWORD      dwSGESlop           = 0;

#else ALLOC_CONTIGUOUS

    static const DWORD      dwSGESlop           = 1;

#endif // ALLOC_CONTIGUOUS

    DWORD                   dwFreeSGEs;
    DWORD                   dwMaxBufferBytes;
    HRESULT                 hr;
    
    hr = ValidateResult(GetFreeSGEs(&dwFreeSGEs));

    if(SUCCEEDED(hr) && (dwFreeSGEs <= dwSGESlop))
    {
        DbgPrint("Out of SGEs\n");
        hr = DSERR_OUTOFMEMORY;
    }
        
    if(SUCCEEDED(hr))
    {
        dwMaxBufferBytes = (dwFreeSGEs - dwSGESlop) * 4096;
		dwMaxBufferBytes -= dwMaxBufferBytes % dwBlockAlign;

        if(*pdwBufferBytes > dwMaxBufferBytes)
        {
            DbgPrint("Clamping buffer size from %lu to %lu\n", *pdwBufferBytes, dwMaxBufferBytes);
            *pdwBufferBytes = dwMaxBufferBytes;
        }
    }

    return hr;
}


/****************************************************************************
 *
 *  LoadEffectsImage
 *
 *  Description:
 *      Loads the default effects image.
 *
 *  Arguments:
 *      LPDIRECTSOUND [in]: DirectSound object.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "LoadEffectsImage"

HRESULT
LoadEffectsImage
(
    LPDIRECTSOUND           pDirectSound,
    LPCSTR                  pszImageFile
)
{
    LPVOID                  pvImageData     = NULL;
    HRESULT                 hr              = DS_OK;
    HANDLE                  hImageFile;
    DWORD                   dwImageSize;
    DSEFFECTIMAGELOC        EffectLoc;

    if(INVALID_HANDLE_VALUE == (hImageFile = CreateFile(pszImageFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)))
    {
        DbgPrint("Can't find image file\n");
        hr = E_FAIL;
    }

    if(SUCCEEDED(hr))
    {
        dwImageSize = GetFileSize(hImageFile, NULL);

        hr = MALLOC(pvImageData, BYTE, dwImageSize);
    }

    if(SUCCEEDED(hr))
    {
        if(!ReadFile(hImageFile, pvImageData, dwImageSize, &dwImageSize, NULL))
        {
            DbgPrint("Can't read image file\n");
            hr = E_FAIL;
        }
    }

    if(SUCCEEDED(hr))
    {
      //  EffectLoc.dwI3DL2ReverbIndex = I3DL2_CHAIN_I3DL2_REVERB;
      //  EffectLoc.dwCrosstalkIndex = I3DL2_CHAIN_XTALK;
		EffectLoc.dwI3DL2ReverbIndex = 0;
		EffectLoc.dwCrosstalkIndex = 0;
        
        hr = ValidateResult(pDirectSound->DownloadEffectsImage(pvImageData, dwImageSize, &EffectLoc, NULL));
    }

    SAFECLOSEHANDLE(hImageFile);
    FREE(pvImageData);

    return hr;
}


/****************************************************************************
 *
 *  GetDirectSoundCaps
 *
 *  Description:
 *      Gets DirectSound capabilities.
 *
 *  Arguments:
 *      LPDSCAPS [out]: caps.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "GetDirectSoundCaps"

HRESULT
GetDirectSoundCaps
(
    LPDSCAPS                pdsc
)
{
    LPDIRECTSOUND           pDirectSound    = NULL;
    HRESULT                 hr;

    hr = ValidateResult(DirectSoundCreate(NULL, &pDirectSound, NULL));

    if(SUCCEEDED(hr))
        hr = ValidateResult(pDirectSound->GetCaps(pdsc));

    RELEASE(pDirectSound);

    return hr;
}


/****************************************************************************
 *
 *  CreateToneBuffer
 *
 *  Description:
 *      Creates a simple sine-wave tone buffer.
 *
 *  Arguments:
 *      DWORD [in]: buffer creation flags.
 *      DWORD [in]: sampling rate.
 *      DWORD [in]: bits per sample.
 *      DWORD [in]: channel count.
 *      DWORD [in]: tone frequency.
 *      DWORD [in]: buffer size in bytes, or 0 for default.
 *      DWORD [in]: buffer mixbin assignments.
 *      LPDIRECTSOUNDBUFFER * [out]: buffer.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateToneBuffer"

HRESULT
CreateToneBuffer
(
    DWORD                   dwFlags,
    DWORD                   dwSamplesPerSec,
    DWORD                   dwBitsPerSample,
    DWORD                   dwChannelCount,
    DWORD                   dwToneFrequency,
    DWORD                   dwBufferBytes,
    LPDSMIXBINS				pMixBins,
    LPDIRECTSOUNDBUFFER *   ppBuffer
)
{
    const LPCWAVEFORMATEX   pwfxFormat      = CreateFormat(WAVE_FORMAT_PCM, dwSamplesPerSec, dwBitsPerSample, dwChannelCount);
    LPDIRECTSOUNDBUFFER     pBuffer         = NULL;
    DSBUFFERDESC            dsbd;
    LPVOID                  pvLock;
    DWORD                   dwLock;
    HRESULT                 hr;

    ASSERT(!(dwSamplesPerSec % dwToneFrequency));

    //
    // Create the buffer
    //

    if(!dwBufferBytes)
    {
        dwBufferBytes = (dwSamplesPerSec / dwToneFrequency) * pwfxFormat->nBlockAlign;
    }

    ZeroMemory(&dsbd, sizeof(dsbd));

    dsbd.dwSize = sizeof(dsbd);
    dsbd.dwFlags = dwFlags;
    dsbd.lpwfxFormat = (LPWAVEFORMATEX)pwfxFormat;
    dsbd.dwBufferBytes = dwBufferBytes;
    dsbd.lpMixBins = pMixBins;

    hr = ValidateResult(DirectSoundCreateBuffer(&dsbd, &pBuffer));

    //
    // Write the audio data
    //

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(pBuffer->Lock(0, dwBufferBytes, &pvLock, &dwLock, NULL, NULL, 0));
    }

    if(SUCCEEDED(hr))
    {
        GenerateTone(pvLock, dwLock, dwSamplesPerSec, dwBitsPerSample, dwChannelCount, dwToneFrequency);
    }

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(pBuffer->Unlock(pvLock, dwLock, NULL, 0));
    }

    //
    // Success
    //

    if(SUCCEEDED(hr))
    {
        *ppBuffer = pBuffer;
    }
    else
    {
        RELEASE(pBuffer);
    }

    return hr;
}


/****************************************************************************
 *
 *  CreateImpulseBuffer
 *
 *  Description:
 *      Creates a simple sine-wave impulse buffer.
 *
 *  Arguments:
 *      DWORD [in]: buffer creation flags.
 *      DWORD [in]: sampling rate.
 *      DWORD [in]: bits per sample.
 *      DWORD [in]: channel count.
 *      DWORD [in]: tone frequency.
 *      DWORD [in]: lead-in length, in seconds.
 *      DWORD [in]: rolloff length, in seconds.
 *      DWORD [in]: buffer mixbin assignments.
 *      LPDIRECTSOUNDBUFFER * [out]: buffer.
 *
 *  Returns:  
 *      HRESULT: COM result code.
 *
 ****************************************************************************/

#undef DPF_FNAME
#define DPF_FNAME "CreateImpulseBuffer"

HRESULT
CreateImpulseBuffer
(
    DWORD                   dwFlags,
    DWORD                   dwSamplesPerSec,
    DWORD                   dwBitsPerSample,
    DWORD                   dwChannelCount,
    DWORD                   dwToneFrequency,
    DWORD                   dwLeadIn,
    DWORD                   dwRollOff,
    LPDSMIXBINS				pMixBins,
    LPDIRECTSOUNDBUFFER *   ppBuffer
)
{
    const LPCWAVEFORMATEX   pwfxFormat      = CreateFormat(WAVE_FORMAT_PCM, dwSamplesPerSec, dwBitsPerSample, dwChannelCount);
    LPDIRECTSOUNDBUFFER     pBuffer         = NULL;
    DWORD                   dwImpulseLength;
    DSBUFFERDESC            dsbd;
    LPVOID                  pvLock;
    DWORD                   dwLock;
    HRESULT                 hr;

    ASSERT(!(dwSamplesPerSec % dwToneFrequency));
    ASSERT(!((dwSamplesPerSec / dwToneFrequency) % 2));

    //
    // Convert the lead-in, rolloff and impulse length to bytes
    //

    dwLeadIn *= pwfxFormat->nAvgBytesPerSec;
    dwRollOff *= pwfxFormat->nAvgBytesPerSec;
    dwImpulseLength = (dwSamplesPerSec / dwToneFrequency / 2) * pwfxFormat->nBlockAlign;

    //
    // Create the buffer
    //

    ZeroMemory(&dsbd, sizeof(dsbd));

    dsbd.dwSize = sizeof(dsbd);
    dsbd.dwFlags = dwFlags;
    dsbd.lpwfxFormat = (LPWAVEFORMATEX)pwfxFormat;
    dsbd.dwBufferBytes = dwLeadIn + dwImpulseLength + dwRollOff;
    dsbd.lpMixBins = pMixBins;

    hr = ValidateResult(DirectSoundCreateBuffer(&dsbd, &pBuffer));

    //
    // Write the audio data
    //

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(pBuffer->Lock(dwLeadIn, dwImpulseLength, &pvLock, &dwLock, NULL, NULL, 0));
        // hr = ValidateResult(pBuffer->Lock(0, dsbd.dwBufferBytes, &pvLock, &dwLock, NULL, NULL, 0));
    }

    if(SUCCEEDED(hr))
    {
        GenerateTone(pvLock, dwLock, dwSamplesPerSec, dwBitsPerSample, dwChannelCount, dwToneFrequency);
    }

    if(SUCCEEDED(hr))
    {
        hr = ValidateResult(pBuffer->Unlock(pvLock, dwLock, NULL, 0));
    }

    //
    // Success
    //

    if(SUCCEEDED(hr))
    {
        *ppBuffer = pBuffer;
    }
    else
    {
        RELEASE(pBuffer);
    }

    return hr;
}



