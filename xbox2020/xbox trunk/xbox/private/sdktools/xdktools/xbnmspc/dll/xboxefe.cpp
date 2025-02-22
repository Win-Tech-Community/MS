/*****************************************************************************
 *
 *    xboxefe.cpp - IEnumFORMATETC interface
 *
 *****************************************************************************/

#include "priv.h"
#include "xboxefe.h"
#include "xboxobj.h"


/*****************************************************************************
 *    CXboxEfe::_NextOne
 *****************************************************************************/

HRESULT CXboxEfe::_NextOne(FORMATETC * pfetc)
{
    HRESULT hr = S_FALSE;

    while (ShouldSkipDropFormat(m_dwIndex))
        m_dwIndex++;

    ASSERT(m_hdsaFormatEtc);
    if (m_dwIndex < (DWORD) DSA_GetItemCount(m_hdsaFormatEtc))
    {
        DSA_GetItem(m_hdsaFormatEtc, m_dwIndex, (LPVOID) pfetc);
        m_dwIndex++;         // We are off to the next one
        hr = S_OK;
    }

    if ((S_OK != hr) && m_pfo)
    {
        // We finished looking thru the types supported by the IDataObject.
        // Now look for other items inserted by IDataObject::SetData()
        if (m_dwExtraIndex < (DWORD) DSA_GetItemCount(m_pfo->m_hdsaSetData))
        {
            FORMATETC_STGMEDIUM fs;

            DSA_GetItem(m_pfo->m_hdsaSetData, m_dwExtraIndex, (LPVOID) &fs);
            *pfetc = fs.formatEtc;
            m_dwExtraIndex++;         // We are off to the next one
            hr = S_OK;
        }
    }
    return hr;
}


//===========================
// *** IEnumFORMATETC Interface ***
//===========================

/*****************************************************************************
 *
 *    IEnumFORMATETC::Next
 *
 *    Creates a brand new enumerator based on an existing one.
 *
 *
 *    OLE random documentation of the day:  IEnumXXX::Next.
 *
 *    rgelt - Receives an array of size celt (or larger).
 *
 *    "Receives an array"?  No, it doesn't receive an array.
 *    It *is* an array.  The array receives *elements*.
 *
 *    "Or larger"?  Does this mean I can return more than the caller
 *    asked for?  No, of course not, because the caller didn't allocate
 *    enough memory to hold that many return values.
 *
 *    No semantics are assigned to the possibility of celt = 0.
 *    Since I am a mathematician, I treat it as vacuous success.
 *
 *    pcelt is documented as an INOUT parameter, but no semantics
 *    are assigned to its input value.
 *
 *    The dox don't say that you are allowed to return *pcelt < celt
 *    for reasons other than "no more elements", but the shell does
 *    it everywhere, so maybe it's legal...
 *
 *****************************************************************************/

HRESULT CXboxEfe::Next(ULONG celt, FORMATETC * rgelt, ULONG *pceltFetched)
{
    HRESULT hres = S_FALSE;
    DWORD dwIndex;

    // Do they want more and do we have more to give?
    for (dwIndex = 0; dwIndex < celt; dwIndex++)
    {
        if (S_FALSE == _NextOne(&rgelt[dwIndex]))        // Yes, so give away...
            break;

        ASSERT(NULL == rgelt[dwIndex].ptd); // We don't do this correctly.
#ifdef DEBUG
        char szName[MAX_PATH];
        GetCfBufA(rgelt[dwIndex].cfFormat, szName, ARRAYSIZE(szName));
        //TraceMsg(TF_XBOX_IDENUM, "CXboxEfe::Next() - Returning %hs", szName);
#endif // DEBUG
    }

    if (pceltFetched)
        *pceltFetched = dwIndex;

    // Were we able to give any?
    if ((0 != dwIndex) || (0 == celt))
        hres = S_OK;

    return hres;
}


/*****************************************************************************
 *    IEnumFORMATETC::Skip
 *****************************************************************************/

HRESULT CXboxEfe::Skip(ULONG celt)
{
    m_dwIndex += celt;

    return S_OK;
}


/*****************************************************************************
 *    IEnumFORMATETC::Reset
 *****************************************************************************/

HRESULT CXboxEfe::Reset(void)
{
    m_dwIndex = 0;
    return S_OK;
}


/*****************************************************************************
 *
 *    IEnumFORMATETC::Clone
 *
 *    Creates a brand new enumerator based on an existing one.
 *
 *****************************************************************************/

HRESULT CXboxEfe::Clone(IEnumFORMATETC **ppenum)
{
    return CXboxEfe_Create((DWORD) DSA_GetItemCount(m_hdsaFormatEtc), m_hdsaFormatEtc, m_dwIndex, m_pfo, ppenum);
}


/*****************************************************************************
 *
 *    CXboxEfe_Create
 *
 *    Creates a brand new enumerator based on a list of possibilities.
 *
 *    Note that we are EVIL and know about CFSTR_FILECONTENTS here:
 *    A FORMATETC of FileContents is always valid.  This is important,
 *    because CXboxObj doesn't actually have a STGMEDIUM for file contents.
 *    (Due to lindex weirdness.)
 *
 *****************************************************************************/

HRESULT CXboxEfe_Create(DWORD dwSize, FORMATETC rgfe[], STGMEDIUM rgstg[], CXboxObj * pfo, CXboxEfe ** ppfefe)
{
    CXboxEfe * pfefe;
    HRESULT hres = E_OUTOFMEMORY;

    pfefe = *ppfefe = new CXboxEfe(dwSize, rgfe, rgstg, pfo);
    if (EVAL(pfefe))
    {
        if (!pfefe->m_hdsaFormatEtc)
            pfefe->Release();
        else
            hres = S_OK;
    }

    if (FAILED(hres) && pfefe)
        IUnknown_Set(ppfefe, NULL);

    return hres;
}


/*****************************************************************************
 *
 *    CXboxEfe_Create
 *
 *    Creates a brand new enumerator based on a list of possibilities.
 *
 *    Note that we are EVIL and know about CFSTR_FILECONTENTS here:
 *    A FORMATETC of FileContents is always valid.  This is important,
 *    because CXboxObj doesn't actually have a STGMEDIUM for file contents.
 *    (Due to lindex weirdness.)
 *
 *****************************************************************************/

HRESULT CXboxEfe_Create(DWORD dwSize, FORMATETC rgfe[], STGMEDIUM rgstg[], CXboxObj * pfo, IEnumFORMATETC ** ppenum)
{
    CXboxEfe * pfefe;
    HRESULT hres = CXboxEfe_Create(dwSize, rgfe, rgstg, pfo, &pfefe);

    if (EVAL(pfefe))
    {
        hres = pfefe->QueryInterface(IID_IEnumFORMATETC, (LPVOID *) ppenum);
        pfefe->Release();
    }

    return hres;
}


/*****************************************************************************
 *
 *    CXboxEfe_Create
 *****************************************************************************/

HRESULT CXboxEfe_Create(DWORD dwSize, HDSA m_hdsaFormatEtc, DWORD dwIndex, CXboxObj * pfo, IEnumFORMATETC ** ppenum)
{
    CXboxEfe * pfefe;
    HRESULT hres = E_OUTOFMEMORY;

    pfefe = new CXboxEfe(dwSize, m_hdsaFormatEtc, pfo, dwIndex);
    if (EVAL(pfefe))
    {
        hres = pfefe->QueryInterface(IID_IEnumFORMATETC, (LPVOID *) ppenum);
        pfefe->Release();
    }

    return hres;
}


/****************************************************\
    Constructor
\****************************************************/
CXboxEfe::CXboxEfe(DWORD dwSize, FORMATETC rgfe[], STGMEDIUM rgstg[], CXboxObj * pfo) : m_cRef(1)
{
    DllAddRef();

    // This needs to be allocated in Zero Inited Memory.
    // Assert that all Member Variables are inited to Zero.
    ASSERT(!m_dwIndex);
    ASSERT(!m_hdsaFormatEtc);
    ASSERT(!m_pfo);

    m_hdsaFormatEtc = DSA_Create(sizeof(rgfe[0]), 10);
    if (EVAL(m_hdsaFormatEtc))
    {
        DWORD dwIndex;

        for (dwIndex = 0; dwIndex < dwSize; dwIndex++)
        {
#ifdef    DEBUG
            char szNameDebug[MAX_PATH];
            GetCfBufA(rgfe[dwIndex].cfFormat, szNameDebug, ARRAYSIZE(szNameDebug));
#endif // DEBUG
    
            if (rgfe[dwIndex].tymed == TYMED_ISTREAM ||
                (rgstg && rgfe[dwIndex].tymed == rgstg[dwIndex].tymed))
            {
#ifdef DEBUG
                //TraceMsg(TF_XBOX_IDENUM, "CXboxEfe() Keeping %hs", szNameDebug);
#endif // DEBUG
                DSA_SetItem(m_hdsaFormatEtc, dwIndex, &rgfe[dwIndex]);
            }
            else
            {
#ifdef DEBUG
                //TraceMsg(TF_XBOX_IDENUM, "CXboxEfe() Ignoring %hs", szNameDebug);
#endif // DEBUG
            }
        }
    }

    if (pfo)
    {
        m_pfo = pfo;
        m_pfo->AddRef();
    }

    LEAK_ADDREF(LEAK_CXboxEfe);
}


/****************************************************\
    Constructor
\****************************************************/
CXboxEfe::CXboxEfe(DWORD dwSize, HDSA hdsaFormatEtc, CXboxObj * pfo, DWORD dwIndex) : m_cRef(1)
{
    DllAddRef();

    // This needs to be allocated in Zero Inited Memory.
    // Assert that all Member Variables are inited to Zero.
    ASSERT(!m_dwIndex);
    ASSERT(!m_hdsaFormatEtc);
    ASSERT(!m_pfo);

    ASSERT(hdsaFormatEtc);
    m_hdsaFormatEtc = DSA_Create(sizeof(FORMATETC), 10);
    if (EVAL(m_hdsaFormatEtc))
    {
        // BUGBUG: What do we do with dwIndex param?
        for (dwIndex = 0; dwIndex < (DWORD) DSA_GetItemCount(hdsaFormatEtc); dwIndex++)
        {
            DSA_SetItem(m_hdsaFormatEtc, dwIndex, DSA_GetItemPtr(hdsaFormatEtc, dwIndex));
        }
    }

    if (pfo)
    {
        m_pfo = pfo;
        m_pfo->AddRef();
    }


    LEAK_ADDREF(LEAK_CXboxEfe);
}


/****************************************************\
    Destructor
\****************************************************/
CXboxEfe::~CXboxEfe()
{
    DSA_Destroy(m_hdsaFormatEtc);

    if (m_pfo)
        m_pfo->Release();

    DllRelease();
    LEAK_DELREF(LEAK_CXboxEfe);
}


//===========================
// *** IUnknown Interface ***
//===========================

ULONG CXboxEfe::AddRef()
{
    m_cRef++;
    return m_cRef;
}

ULONG CXboxEfe::Release()
{
    ASSERT(m_cRef > 0);
    m_cRef--;

    if (m_cRef > 0)
        return m_cRef;

    delete this;
    return 0;
}

HRESULT CXboxEfe::QueryInterface(REFIID riid, void **ppvObj)
{
    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IEnumFORMATETC))
    {
        *ppvObj = SAFECAST(this, IEnumFORMATETC*);
    }
    else
    {
        TraceMsg(TF_XBOXQI, "CXboxEfe::QueryInterface() failed.");
        *ppvObj = NULL;
        return E_NOINTERFACE;
    }

    AddRef();
    return S_OK;
}
