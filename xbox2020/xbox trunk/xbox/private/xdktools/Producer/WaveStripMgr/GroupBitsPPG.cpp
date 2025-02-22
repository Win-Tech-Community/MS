// GroupBitsPPG.cpp : implementation file
//

#include "stdafx.h"
#include <RiffStrm.h>
#include "TrackMgr.h"
#include "GroupBitsPPG.h"
#include "TabWaveTrack.h"
#include "TabWavePart.h"
#include "SegmentIO.h"
#include "TrackFlagsPPG.h"
#include <dmusici.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// {D5A4FD39-5753-45d1-953E-E6E01A717957}
static const GUID GUID_WaveStripPPGMgr = 
{ 0xd5a4fd39, 0x5753, 0x45d1, { 0x95, 0x3e, 0xe6, 0xe0, 0x1a, 0x71, 0x79, 0x57 } };

short CGroupBitsPropPageMgr::sm_nActiveTab = 3;
short* CGroupBitsPPG::sm_pnActiveTab = NULL;


/////////////////////////////////////////////////////////////////////////////
// CGroupBitsPropPageMgr property page

CGroupBitsPropPageMgr::CGroupBitsPropPageMgr()
{
	// Must use other constructor!!!
	ASSERT( 0 );
}

CGroupBitsPropPageMgr::CGroupBitsPropPageMgr( IDMUSProdFramework* pIFramework, CTrackMgr* pTrackMgr )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	// Store Framework pointer
	ASSERT( pIFramework != NULL ); 
	m_pIFramework = pIFramework;
	m_pIFramework->AddRef();

	ASSERT( pTrackMgr != NULL ); 
	m_pTrackMgr = pTrackMgr;

	// Store GUID
	m_GUIDManager = GUID_WaveStripPPGMgr;

	// Initialize our pointers to NULL
	m_pTabGroupBits = NULL;
	m_pTrackFlagsPPG = NULL;
	m_pTabWaveTrack = NULL;
	m_pTabWavePart = NULL;

	CStaticPropPageManager::CStaticPropPageManager();
}

CGroupBitsPropPageMgr::~CGroupBitsPropPageMgr()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	if( m_pTabGroupBits )
	{
		delete m_pTabGroupBits;
		m_pTabGroupBits = NULL;
	}

	if( m_pTrackFlagsPPG )
	{
		delete m_pTrackFlagsPPG;
		m_pTrackFlagsPPG = NULL;
	}

	if( m_pTabWaveTrack )
	{
		delete m_pTabWaveTrack;
		m_pTabWaveTrack = NULL;
	}

	if( m_pTabWavePart )
	{
		delete m_pTabWavePart;
		m_pTabWavePart = NULL;
	}

	if( m_pIFramework )
	{
		m_pIFramework->Release();
		m_pIFramework = NULL;
	}

	CStaticPropPageManager::~CStaticPropPageManager();
}


HRESULT CGroupBitsPropPageMgr::QueryInterface( REFIID riid, LPVOID *ppv )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	return CStaticPropPageManager::QueryInterface( riid, ppv );
}

/////////////////////////////////////////////////////////////////////////////
// CGroupBitsPropPageMgr IDMUSProdPropPageManager implementation

/////////////////////////////////////////////////////////////////////////////
// CGroupBitsPropPageMgr::GetPropertySheetTitle

HRESULT CGroupBitsPropPageMgr::GetPropertySheetTitle( BSTR* pbstrTitle, 
	BOOL* pfAddPropertiesText )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	if( (pbstrTitle == NULL)
	||  (pfAddPropertiesText == NULL) )
	{
		return E_POINTER;
	}

	*pfAddPropertiesText = TRUE;

	CString cstrPart;
	cstrPart.LoadString( IDS_PROPPAGE_GROUP_BITS );
	*pbstrTitle = cstrPart.AllocSysString();

	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CGroupBitsPropPageMgr::GetPropertySheetPages

HRESULT CGroupBitsPropPageMgr::GetPropertySheetPages( IDMUSProdPropSheet* pIPropSheet, 
	LONG* hPropSheetPage[], short* pnNbrPages )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	if( (hPropSheetPage == NULL)
	||  (pnNbrPages == NULL) )
	{
		return E_POINTER;
	}

	if( pIPropSheet == NULL )
	{
		return E_INVALIDARG;
	}

	m_pIPropSheet = pIPropSheet;
	m_pIPropSheet->AddRef();

	hPropSheetPage[0] = NULL;
	*pnNbrPages = 0;

	HPROPSHEETPAGE hPage;
	short nNbrPages = 0;

	// Add group bits tab
	if( m_pTabGroupBits == NULL )
	{
		m_pTabGroupBits = new CGroupBitsPPG();
	}
	if( m_pTabGroupBits )
	{
		hPage = ::CreatePropertySheetPage( (LPCPROPSHEETPAGE)&m_pTabGroupBits->m_psp );
		if( hPage )
		{
			hPropSheetPage[nNbrPages] = (LONG *)hPage;
			nNbrPages++;
		}			

		// Weak reference
		m_pTabGroupBits->m_pIPropSheet = m_pIPropSheet;

		// Tell the property page to update the active tab setting
		CGroupBitsPPG::sm_pnActiveTab = &CGroupBitsPropPageMgr::sm_nActiveTab;
	}

	// Add track flags tab
	if( NULL == m_pTrackFlagsPPG )
	{
		m_pTrackFlagsPPG = new CTrackFlagsPPG();
	}
	if( m_pTrackFlagsPPG )
	{
		hPage = ::CreatePropertySheetPage( (LPCPROPSHEETPAGE)&m_pTrackFlagsPPG->m_psp );
		if( hPage )
		{
			hPropSheetPage[nNbrPages] = (LONG *)hPage;
			nNbrPages++;
		}			

		// Weak reference
		m_pTrackFlagsPPG->m_pIPropSheet = m_pIPropSheet;

		// Tell the property page to update the active tab setting
		CTrackFlagsPPG::sm_pnActiveTab = &CGroupBitsPropPageMgr::sm_nActiveTab;
	}

	// Add wave track tab
	if( m_pTabWaveTrack == NULL )
	{
		m_pTabWaveTrack = new CTabWaveTrack();
	}
	if( m_pTabWaveTrack )
	{
		hPage = ::CreatePropertySheetPage( (LPCPROPSHEETPAGE)&m_pTabWaveTrack->m_psp );
		if( hPage )
		{
			hPropSheetPage[nNbrPages] = (LONG *)hPage;
			nNbrPages++;
		}			

		// Weak reference
		m_pTabWaveTrack->m_pIPropSheet = m_pIPropSheet;

		// Point the property page back to this property page manager
		m_pTabWaveTrack->m_pPropPageMgr = this;
	}

	// Add wave part tab
	if( m_pTabWavePart == NULL )
	{
		m_pTabWavePart = new CTabWavePart();
	}
	if( m_pTabWavePart )
	{
		hPage = ::CreatePropertySheetPage( (LPCPROPSHEETPAGE)&m_pTabWavePart->m_psp );
		if( hPage )
		{
			hPropSheetPage[nNbrPages] = (LONG *)hPage;
			nNbrPages++;
		}			

		// Weak reference
		m_pTabWavePart->m_pIPropSheet = m_pIPropSheet;

		// Point the property page back to this property page manager
		m_pTabWavePart->m_pPropPageMgr = this;
	}

	// Set number of pages
	*pnNbrPages = nNbrPages;
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CGroupBitsPropPageMgr::RefreshData

HRESULT CGroupBitsPropPageMgr::RefreshData()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	if( m_pTabGroupBits )
	{
		m_pTabGroupBits->RefreshData();
	}

	if( m_pTrackFlagsPPG )
	{
		m_pTrackFlagsPPG->RefreshData();
	}

	if( m_pTabWaveTrack )
	{
		m_pTabWaveTrack->RefreshData();
	}

	if( m_pTabWavePart )
	{
		m_pTabWavePart->RefreshData();
	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CGroupBitsPropPageMgr::SetObject

HRESULT CGroupBitsPropPageMgr::SetObject( IDMUSProdPropPageObject* pINewPropPageObject )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	if( m_pTabGroupBits )
	{
		m_pTabGroupBits->SetObject( pINewPropPageObject );
	}

	if( m_pTrackFlagsPPG )
	{
		m_pTrackFlagsPPG->SetObject( pINewPropPageObject );
	}

	if( m_pTabWaveTrack )
	{
		m_pTabWaveTrack->SetObject( pINewPropPageObject );
	}

	if( m_pTabWavePart )
	{
		m_pTabWavePart->SetObject( pINewPropPageObject );
	}

	return CStaticPropPageManager::SetObject( pINewPropPageObject );
}


/////////////////////////////////////////////////////////////////////////////
// CGroupBitsPPG property page

CGroupBitsPPG::CGroupBitsPPG() : CPropertyPage(CGroupBitsPPG::IDD)
{
	//{{AFX_DATA_INIT(CGroupBitsPPG)
	//}}AFX_DATA_INIT

	m_pPPO = NULL;
	m_pIPropSheet = NULL;

	m_PPGTrackParams.dwPageIndex = 0;
	m_PPGTrackParams.dwGroupBits = 0;
	
	m_fNeedToDetach = FALSE;
}

CGroupBitsPPG::~CGroupBitsPPG()
{
	if( m_pPPO )
	{
		m_pPPO->Release();
		m_pPPO = NULL;
	}
}

void CGroupBitsPPG::DoDataExchange(CDataExchange* pDX)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupBitsPPG)
	DDX_Control(pDX, IDC_COMBO_GROUP_LIST, m_GroupDropDownList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupBitsPPG, CPropertyPage)
	//{{AFX_MSG_MAP(CGroupBitsPPG)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP_LIST, OnSelchangeComboGroupList)
	ON_MESSAGE( WM_APP, OnApp )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// private functions
void CGroupBitsPPG::SetObject( IDMUSProdPropPageObject* pPPO )
{
	if( m_pPPO )
	{
		m_pPPO->Release();
	}
	m_pPPO = pPPO;
	if( m_pPPO )
	{
		m_pPPO->AddRef();
	}
}

void CGroupBitsPPG::EnableControls( BOOL fEnable )
{
	if( ::IsWindow(m_hWnd) == FALSE )
	{
		return;
	}

	if( ::IsWindow(m_GroupDropDownList.m_hWnd))
	{
		m_GroupDropDownList.EnableWindow(fEnable);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGroupBitsPPG message handlers

int CGroupBitsPPG::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	// Attach the window to the property page structure.
	// This has been done once already in the main application
	// since the main application owns the property sheet.
	// It needs to be done here so that the window handle can
	// be found in the DLLs handle map.
	if( !FromHandlePermanent( m_hWnd ) )
	{
		HWND hWnd = m_hWnd;
		m_hWnd = NULL;
		Attach( hWnd );
		m_fNeedToDetach = TRUE;
	}

	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CGroupBitsPPG::OnDestroy() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	// Detach the window from the property page structure.
	// This will be done again by the main application since
	// it owns the property sheet.  It needs o be done here
	// so that the window handle can be removed from the
	// DLLs handle map.
	if( m_fNeedToDetach && m_hWnd )
	{
		HWND hWnd = m_hWnd;
		Detach();
		m_hWnd = hWnd;
	}

	CPropertyPage::OnDestroy();
}

void CGroupBitsPPG::RefreshData( void )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	if( m_pPPO == NULL )
	{
		EnableControls( FALSE );
		return;
	}

	ioGroupBitsPPG* pioGroupBitsPPG = &m_PPGTrackParams;
	if( FAILED( m_pPPO->GetData( (void**)&pioGroupBitsPPG ) ) )
	{
		EnableControls( FALSE );
		return;
	}

	// Make sure controls have been created
	if( ::IsWindow(m_hWnd) == FALSE )
	{
		return;
	}

	// Prevent control notifications from being dispatched during UpdateData
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	HWND hWndOldLockout = pThreadState->m_hLockoutNotifyWindow;
	ASSERT(hWndOldLockout != m_hWnd);   // must not recurse
	pThreadState->m_hLockoutNotifyWindow = m_hWnd;

	EnableControls( TRUE );

	// Group Bits combo box
	if (!m_PPGTrackParams.dwGroupBits)
	{
		m_PPGTrackParams.dwGroupBits = 1;
	}
	for (int iIndex = 0; iIndex < 32; iIndex++)
	{
		if (m_PPGTrackParams.dwGroupBits & (1 << iIndex) )
			break;
	}
	m_GroupDropDownList.SetCurSel(iIndex);

	pThreadState->m_hLockoutNotifyWindow = hWndOldLockout;
}

BOOL CGroupBitsPPG::OnSetActive() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	RefreshData();

	// Store active tab
	if( sm_pnActiveTab && m_pIPropSheet )
	{
		m_pIPropSheet->GetActivePage( sm_pnActiveTab );
	}

	return CPropertyPage::OnSetActive();
}

void CGroupBitsPPG::UpdatePPO()
{
	if( m_pPPO )
	{
		VERIFY( SUCCEEDED( m_pPPO->SetData(&m_PPGTrackParams) ) );
	}
}

void CGroupBitsPPG::OnSelchangeComboGroupList() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	PostMessage( WM_APP, 0, 0 );
}

LRESULT CGroupBitsPPG::OnApp(WPARAM, LPARAM)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Custom handler for OnSelChanged to work-around bug in user32.dll
	int iIndex = m_GroupDropDownList.GetCurSel();

	if (iIndex >= 0 && iIndex < 32)
	{
		m_PPGTrackParams.dwGroupBits = (1 << iIndex);
	}
	else
	{
		ASSERT(FALSE);
		return 0;
	}

	UpdatePPO();
	return 0;
}
