/*++

Copyright (c) 1998-1999 Microsoft Corporation

Module Name:

    msptrmvc.cpp

Abstract:

    MSP base classes: declaration of video capture terminal.

--*/


#ifndef _MSPTRMVC_H_
#define _MSPTRMVC_H_
    
/////////////////////////////////////////////////////////////////////////////
// CVideoCaptureTerminal

class CVideoCaptureTerminal : 
    public CSingleFilterStaticTerminal
{
public:

    CVideoCaptureTerminal();
    virtual ~CVideoCaptureTerminal();

public:

    static HRESULT CreateTerminal(
        IN    CComPtr<IMoniker>    pMoniker,
        IN    MSP_HANDLE           htAddress,
        OUT   ITTerminal         **ppTerm
        );

// If we add any additional interfaces to this class then
// we must uncomment and expand the following.
//
// BEGIN_COM_MAP(CVideoCaptureTerminal)
//    COM_INTERFACE_ENTRY_CHAIN(CSingleFilterStaticTerminal)
// END_COM_MAP()

DECLARE_LOG_ADDREF_RELEASE(CVideoCaptureTerminal);

private:

    // CBaseTerminal required overrides 

    virtual HRESULT AddFiltersToGraph();

    virtual LONG CountOfMediaTypes()
    {
        return 1;
    }

    virtual DWORD GetSupportedMediaTypes(void)
    {
        return (DWORD) TAPIMEDIATYPE_VIDEO;
    }

    // Helper methods.
    HRESULT CreateFilters();
    HRESULT FindCapturePin();
};



inline 
CVideoCaptureTerminal::CVideoCaptureTerminal(
    )                                   
{
    m_TerminalDirection = TD_CAPTURE;
    m_TerminalType = TT_STATIC;
}

#endif // _MSPTRMVC_H_
