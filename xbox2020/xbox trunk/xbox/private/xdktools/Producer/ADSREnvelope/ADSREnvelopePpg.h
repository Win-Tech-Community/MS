#if !defined(AFX_ADSRENVELOPEPPG_H__71AE3636_A9BD_11D0_BCBA_00AA00C08146__INCLUDED_)
#define AFX_ADSRENVELOPEPPG_H__71AE3636_A9BD_11D0_BCBA_00AA00C08146__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// ADSREnvelopePpg.h : Declaration of the CADSREnvelopePropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CADSREnvelopePropPage : See ADSREnvelopePpg.cpp.cpp for implementation.

class CADSREnvelopePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CADSREnvelopePropPage)
	DECLARE_OLECREATE_EX(CADSREnvelopePropPage)

// Constructor
public:
	CADSREnvelopePropPage();

// Dialog Data
	//{{AFX_DATA(CADSREnvelopePropPage)
	enum { IDD = IDD_PROPPAGE_ADSRENVELOPE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CADSREnvelopePropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADSRENVELOPEPPG_H__71AE3636_A9BD_11D0_BCBA_00AA00C08146__INCLUDED)
