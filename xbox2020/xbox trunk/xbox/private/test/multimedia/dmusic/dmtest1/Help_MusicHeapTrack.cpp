/*++

Copyright (c) 2001 Microsoft Corporation

Module Name:

	MusicHeapTrack.cpp

Abstract:

	User-defined DirectMusic heap object 

Author:

	Dan Haffner(danhaff) 05-Jul-2001

Environment:

	Xbox only

Revision History:

	05-Jul-2001 danhaff
		Initial Version; copied out of dmusic/debug.cpp and modified.

--*/

//------------------------------------------------------------------------------
//	Includes:
//------------------------------------------------------------------------------
#include <globals.h>
#include "help_musicheap.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class CMusicHeapTrack : public IMusicHeap
{

public:

    CMusicHeapTrack(void);
    ~CMusicHeapTrack(void);
    HRESULT Initialize(bool bIsPhysicalHeap);


    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppvObj);
    ULONG STDMETHODCALLTYPE AddRef(void);
    ULONG STDMETHODCALLTYPE Release(void);

    /*  IDirectMusicHeap */
    STDMETHOD(Allocate) (DWORD dwSize, PVOID* ppData);
    STDMETHOD(GetSize) (THIS_ PVOID pData, LPDWORD pcbSize);
    STDMETHOD(Free)(void *pv);

    // IMusicHeap
    STDMETHOD(GetHeapAllocation          )(DWORD *pdwHeapAllocation);
    STDMETHOD(GetHeapAllocationPeak      )(DWORD *pdwHeapAllocationPeak);
    STDMETHOD(GetHeapAllocationBlocks    )(DWORD *pdwHeapAllocationBlocks);
    STDMETHOD(GetHeapAllocationBlocksPeak)(DWORD *pdwHeapAllocationBlocksPeak);
    STDMETHOD(SetSize                    )(DWORD dwLimit);

private:
    void* Alloc(size_t cb);

    CRITICAL_SECTION m_csHeap;
    DWORD m_dwHeapAllocation;
    DWORD m_dwHeapAllocationPeak;
    DWORD m_dwHeapAllocationBlocks;
    DWORD m_dwHeapAllocationBlocksPeak;
    bool m_bPhysicalHeap;
    LONG m_cRef;
    bool m_bLimit;
    DWORD m_dwLimit;
};


CMusicHeapTrack::CMusicHeapTrack(void)
{
    InitializeCriticalSection(&m_csHeap);
    m_cRef = 1;
    m_bPhysicalHeap = false;
    m_dwHeapAllocation = 0;
    m_dwHeapAllocationPeak = 0;
    m_dwHeapAllocationBlocks = 0;
    m_dwHeapAllocationBlocksPeak = 0;
    m_bLimit  = FALSE;
    m_dwLimit = 0;

}

CMusicHeapTrack::~CMusicHeapTrack(void)
{
    DeleteCriticalSection(&m_csHeap);
}

HRESULT CMusicHeapTrack::Initialize(bool bIsPhysicalHeap)
{
    m_bPhysicalHeap = bIsPhysicalHeap;
    return S_OK;
}

ULONG STDMETHODCALLTYPE CMusicHeapTrack::AddRef( void)         
{
return InterlockedIncrement(&m_cRef);
}



ULONG STDMETHODCALLTYPE CMusicHeapTrack::Release(void) 
{
    ULONG cRef;            
    cRef = InterlockedDecrement(&m_cRef);
    if (cRef == 0)
        delete this;
    return cRef;
}

STDMETHODIMP CMusicHeapTrack::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
return E_NOTIMPL;
}



STDMETHODIMP CMusicHeapTrack::Allocate(DWORD dwSize, PVOID* ppData)
{
    PVOID pData = Alloc(dwSize);
    if(!pData){
        return E_OUTOFMEMORY;
    }
    *ppData = pData;
    return S_OK;
}



void* CMusicHeapTrack::Alloc(size_t cb)
{
    DWORD* pBlock = 0;

    EnterCriticalSection(&m_csHeap);
    if (m_bLimit)
    {
        if(cb + sizeof(DWORD) + m_dwHeapAllocation > m_dwLimit)
        {        
            Log(ABORTLOGLEVEL, "");
            Log(ABORTLOGLEVEL, "%s HEAP OUT OF MEMORY!!!", m_bPhysicalHeap ? "PHYSICAL" : "NON-PHYSICAL");
            Log(ABORTLOGLEVEL, "Requested size                 = %u", cb);
            Log(ABORTLOGLEVEL, "m_dwHeapAllocation             = %u", m_dwHeapAllocation);
            Log(ABORTLOGLEVEL, "m_dwHeapSize                   = %u", m_dwLimit);
            Log(ABORTLOGLEVEL, "m_dwHeapAllocationBlocks       = %u", m_dwHeapAllocationBlocks);
            Log(ABORTLOGLEVEL, "m_dwHeapAllocationBlocksPeak   = %u", m_dwHeapAllocationBlocksPeak);
            Log(ABORTLOGLEVEL, "");
            ASSERT(FALSE);
            LeaveCriticalSection(&m_csHeap);
            return NULL;
        }
    }
    
    if (!m_bPhysicalHeap)
        pBlock = (DWORD *)LocalAlloc(LMEM_FIXED, cb + sizeof(DWORD));
    else
        pBlock = (DWORD *)XPhysicalAlloc(cb + sizeof(DWORD), MAXULONG_PTR, 0, PAGE_READWRITE);

    if(!pBlock)
    {
        LeaveCriticalSection(&m_csHeap);
        return NULL;
    }


    m_dwHeapAllocation += (cb + sizeof(DWORD));
    if(m_dwHeapAllocation > m_dwHeapAllocationPeak){
        m_dwHeapAllocationPeak = m_dwHeapAllocation;
    }
    ++m_dwHeapAllocationBlocks;
    if(m_dwHeapAllocationBlocks > m_dwHeapAllocationBlocksPeak){
        m_dwHeapAllocationBlocksPeak = m_dwHeapAllocationBlocks;
    }

    LeaveCriticalSection(&m_csHeap);

    *pBlock = cb;
    return pBlock + 1;
}

STDMETHODIMP CMusicHeapTrack::GetSize(PVOID pData, LPDWORD pcbSize)
{
    ASSERT(pData);
    DWORD* pBlock = ((DWORD*) pData) - 1;
    *pcbSize = *pBlock;

    return S_OK;
}

STDMETHODIMP CMusicHeapTrack::Free(void *pv)
{
    ASSERT(pv);
    DWORD* pBlock = ((DWORD*) pv) - 1;
    DWORD cb = *pBlock;
    EnterCriticalSection(&m_csHeap);
    ASSERT(cb+sizeof(DWORD) < 64 * 1024 * 1024);
    
    //Update our stats
    m_dwHeapAllocation -= (cb + sizeof(DWORD));
    --m_dwHeapAllocationBlocks;

    //Set all block memory to a certain value.
    memset((void *)pBlock, 0xFE, cb+sizeof(DWORD));

    LeaveCriticalSection(&m_csHeap);
    if (m_bPhysicalHeap)
        XPhysicalFree(pBlock);
    else
        LocalFree(pBlock);

    return S_OK;
}



STDMETHODIMP CMusicHeapTrack::GetHeapAllocation          (DWORD *pdwHeapAllocation)
{
    *pdwHeapAllocation = m_dwHeapAllocation;
    return S_OK;
};

STDMETHODIMP CMusicHeapTrack::GetHeapAllocationPeak      (DWORD *pdwHeapAllocationPeak)
{
    *pdwHeapAllocationPeak = m_dwHeapAllocationPeak;
    return S_OK;
};

STDMETHODIMP CMusicHeapTrack::GetHeapAllocationBlocks    (DWORD *pdwHeapAllocationBlocks)
{
    *pdwHeapAllocationBlocks = m_dwHeapAllocationBlocks;
    return S_OK;
};

STDMETHODIMP CMusicHeapTrack::GetHeapAllocationBlocksPeak(DWORD *pdwHeapAllocationBlocksPeak)
{
    *pdwHeapAllocationBlocksPeak = m_dwHeapAllocationBlocksPeak;
    return S_OK;
};


STDMETHODIMP CMusicHeapTrack::SetSize(DWORD dwLimit)
{
ASSERT(dwLimit < 64 * 1024 * 1024);
m_bLimit = TRUE;
m_dwLimit = dwLimit;
return S_OK;
};



HRESULT CreateMusicHeapTrack(IMusicHeap** ppHeap, bool bPhysical)
{
    HRESULT hr = S_OK;
    CMusicHeapTrack* pHeap = new CMusicHeapTrack();
    if(!pHeap)
    {
        hr = E_OUTOFMEMORY;
    }
    if(SUCCEEDED(hr))
    {
        hr = pHeap->Initialize(bPhysical);
        if(SUCCEEDED(hr))
            *ppHeap = pHeap;
        else
            pHeap->Release();
    }
    return hr;
}

