// TimeSignatureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <dmusprod.h>
#include "MIDIStripMgrApp.h"
#include "MIDIStripMgr.h"
#include "Pattern.h"
#include "TimeSignatureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg dialog

CTimeSignatureDlg::CTimeSignatureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeSignatureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeSignatureDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_TimeSignature.m_bBeatsPerMeasure = 4;
	m_TimeSignature.m_bBeat = 4;
	m_TimeSignature.m_wGridsPerBeat = 4;
	m_nContext = 0;
}


void CTimeSignatureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeSignatureDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_GRID, m_cmbxGrid);
	DDX_Control(pDX, IDC_BPM_SPIN, m_spinBPM);
	DDX_Control(pDX, IDC_BPM, m_editBPM);
	DDX_Control(pDX, IDC_BEAT, m_cmbxBeat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeSignatureDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeSignatureDlg)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_CBN_SELCHANGE(IDC_BEAT, OnSelChangeBeat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg::OnInitDialog

BOOL CTimeSignatureDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Set beats per measure
	m_editBPM.LimitText( 3 );
	m_spinBPM.SetRange( MIN_BEATS_PER_MEASURE, MAX_BEATS_PER_MEASURE );
	m_spinBPM.SetPos( m_TimeSignature.m_bBeatsPerMeasure );

	// Fill beat combo box
	CString cstrText;
	int i;

	for ( i = IDS_BEAT1 ;  i <= IDS_BEAT6 ;  i++ )
	{
		cstrText.LoadString( i );
		m_cmbxBeat.AddString( cstrText );
	}

	// Set beat
	CString cstrBeat;

	cstrBeat.Format( "%d", m_TimeSignature.m_bBeat );
	int nPos = m_cmbxBeat.FindStringExact( -1, cstrBeat ); 
	m_cmbxBeat.SetCurSel( nPos );

	// Fill grids per beat combo box
	for( i = MIN_GRIDS_PER_BEAT ;  i <= MAX_GRIDS_PER_BEAT ;  i++ )
	{
		m_cmbxGrid.AddString( _T("") );
	}

	// Set grids per beat
	m_cmbxGrid.SetCurSel( m_TimeSignature.m_wGridsPerBeat - 1 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg::OnSelChangeBeat

void CTimeSignatureDlg::OnSelChangeBeat() 
{
	m_cmbxGrid.Invalidate();	
}


/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg::ValidateBeatsPerMeasure

BOOL CTimeSignatureDlg::ValidateBeatsPerMeasure()
{
	CString cstrBeatsPerMeasure;

	m_editBPM.GetWindowText( cstrBeatsPerMeasure );

	// Strip leading and trailing spaces
	cstrBeatsPerMeasure.TrimRight();
	cstrBeatsPerMeasure.TrimLeft();

	WORD wBeatsPerMeasure = (WORD)_ttoi( cstrBeatsPerMeasure );

	// Validate new length
	if( wBeatsPerMeasure < MIN_BEATS_PER_MEASURE
	||  wBeatsPerMeasure > MAX_BEATS_PER_MEASURE )
	{
		CString cstrMsg;
		CString cstrMin;
		CString cstrMax;
		
		cstrMin.Format( "%d", MIN_BEATS_PER_MEASURE );
		cstrMax.Format( "%d", MAX_BEATS_PER_MEASURE );
		
		HINSTANCE hInstance = AfxGetResourceHandle();
		AfxSetResourceHandle( AfxGetInstanceHandle() );
		AfxFormatString2( cstrMsg, IDS_ERR_MIN_MAX, cstrMin, cstrMax );
		AfxSetResourceHandle( hInstance );
		AfxMessageBox( cstrMsg );

		m_editBPM.SetFocus();
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg::ValidateBeat

BOOL CTimeSignatureDlg::ValidateBeat()
{
	int nPos = m_cmbxBeat.GetCurSel();
	if( nPos == CB_ERR )
	{
		HINSTANCE hInstance = AfxGetResourceHandle();
		AfxSetResourceHandle( AfxGetInstanceHandle() );
		AfxMessageBox( IDS_ERR_BEAT );
		AfxSetResourceHandle( hInstance );

		m_cmbxBeat.SetFocus();
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg::ValidateGridsPerBeat

BOOL CTimeSignatureDlg::ValidateGridsPerBeat()
{
	int nPos = m_cmbxGrid.GetCurSel();
	if( nPos == CB_ERR )
	{
		HINSTANCE hInstance = AfxGetResourceHandle();
		AfxSetResourceHandle( AfxGetInstanceHandle() );
		AfxMessageBox( IDS_ERR_GRIDS_PER_BEAT );
		AfxSetResourceHandle( hInstance );

		m_cmbxGrid.SetFocus();
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg::OnOK

void CTimeSignatureDlg::OnOK() 
{
	if( ValidateBeatsPerMeasure() == FALSE
	||  ValidateBeat() == FALSE
	||  ValidateGridsPerBeat() == FALSE )
	{
		return;
	}

	// Get beats per measure
	CString cstrBeatsPerMeasure;

	m_editBPM.GetWindowText( cstrBeatsPerMeasure );
	cstrBeatsPerMeasure.TrimRight();
	cstrBeatsPerMeasure.TrimLeft();
	m_TimeSignature.m_bBeatsPerMeasure = (BYTE)_ttoi( cstrBeatsPerMeasure );

	// Get beat
	int nPos = m_cmbxBeat.GetCurSel();
	if( nPos != CB_ERR )
	{
		CString cstrBeat;

		m_cmbxBeat.GetLBText( nPos, cstrBeat );
		m_TimeSignature.m_bBeat = (BYTE)_ttoi( cstrBeat );
	}

	// Get grids per beat
	nPos = m_cmbxGrid.GetCurSel();
	if( nPos != CB_ERR )
	{
		m_TimeSignature.m_wGridsPerBeat = (WORD)(nPos + 1);
	}

	CDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg::OnMeasureItem

void CTimeSignatureDlg::OnMeasureItem( int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct ) 
{
	switch( nIDCtl )
	{
		case IDC_GRID:
		{
			CBitmap bitmap;

			// Set height
			HINSTANCE hInstance = AfxGetResourceHandle();
			AfxSetResourceHandle( AfxGetInstanceHandle() );
			if( bitmap.LoadBitmap( IDB_GPB1 ) )
			{
				BITMAP bm;

				bitmap.GetBitmap( &bm );
				lpMeasureItemStruct->itemHeight = bm.bmHeight + 3;
			}
			AfxSetResourceHandle( hInstance );

			// Set width
			RECT rect;

			CWnd* pWnd = GetDlgItem( IDC_GRID );
			if( pWnd )
			{
				pWnd->GetClientRect( &rect );
				lpMeasureItemStruct->itemWidth = rect.right - rect.left;
			}
			return;
		}
	}
	
	CDialog::OnMeasureItem( nIDCtl, lpMeasureItemStruct );
}


/////////////////////////////////////////////////////////////////////////////
// CTimeSignatureDlg::OnDrawItem

void CTimeSignatureDlg::OnDrawItem( int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct ) 
{
	switch( nIDCtl )
	{
		case IDC_GRID:
		{
			if( lpDrawItemStruct->itemID == -1 )
			{
				return;
			}

			CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
			if( pDC == NULL )
			{
				return;
			}

            if( lpDrawItemStruct->itemAction & ODA_FOCUS )
			{
		        InflateRect( &lpDrawItemStruct->rcItem, -1, -1 ) ;
                pDC->DrawFocusRect( &lpDrawItemStruct->rcItem );
		        InflateRect( &lpDrawItemStruct->rcItem, 1, 1 ) ;
				return;
			}

            if( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE
            ||  lpDrawItemStruct->itemAction & ODA_SELECT )
			{
				CBitmap bitmap;

				// Get the resource id for the bitmap
				int nBeatPos = m_cmbxBeat.GetCurSel();
				int nResourceID = lpDrawItemStruct->itemID;
				if( nBeatPos != CB_ERR
				&&  nBeatPos != 2 )		// 2 = quarter note gets the beat
				{
					nResourceID += MAX_GRIDS_PER_BEAT;
				}
				ASSERT( (nResourceID >= 0) && (nResourceID <= MAX_GRIDS_PER_BEAT_ENTRIES) ); 

				// Load the bitmap
				HINSTANCE hInstance = AfxGetResourceHandle();
				AfxSetResourceHandle( AfxGetInstanceHandle() );

				if( bitmap.LoadBitmap( g_nGridsPerBeatBitmaps[nResourceID] ) )
				{
					CDC dcBitmap;

					if( dcBitmap.CreateCompatibleDC( pDC ) )
					{
						BITMAP bm;

						// Get the size of the bitmap
						bitmap.GetBitmap( &bm );

						// Clear the rectangle
						pDC->FillRect( &lpDrawItemStruct->rcItem,
									   CBrush::FromHandle( (HBRUSH)GetStockObject(WHITE_BRUSH) ) );

						// Paint the bitmap
						CBitmap* pOldBitmap = dcBitmap.SelectObject( &bitmap );
						pDC->BitBlt( lpDrawItemStruct->rcItem.left + 5, lpDrawItemStruct->rcItem.top + 1,
									 bm.bmWidth, bm.bmHeight,
									 &dcBitmap, 0, 0, SRCCOPY );
						dcBitmap.SelectObject( pOldBitmap );
					}
				}

				AfxSetResourceHandle( hInstance );

				// Invert if selected
                if( lpDrawItemStruct->itemState & ODS_SELECTED )
				{
					pDC->InvertRect( &lpDrawItemStruct->rcItem );
				}
			}

			return;
		}
	}
	
	CDialog::OnDrawItem( nIDCtl, lpDrawItemStruct );
}
