// $$root$$.h : main header file for the $$ROOT$$ application
//

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$:
// See $$root$$.cpp for the implementation of this class
//

class $$APP_CLASS$$ : public $$APP_BASE_CLASS$$
{
public:
	$$APP_CLASS$$();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL($$APP_CLASS$$)
	public:
	virtual BOOL InitInstance();
$$IF(PROJTYPE_MDI)
$$IF(NODOCVIEW)
	virtual int ExitInstance();
$$ENDIF
$$ENDIF
	//}}AFX_VIRTUAL

// Implementation
$$IF(FULL_SERVER || MINI_SERVER || CONTAINER_SERVER || AUTOMATION)
	COleTemplateServer m_server;
$$IF(VERBOSE)
		// Server object for document creation
$$ENDIF
$$ENDIF
$$IF(NODOCVIEW)
$$IF(PROJTYPE_MDI)
protected:
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;
$$ENDIF

public:
$$ENDIF
	//{{AFX_MSG($$APP_CLASS$$)
	afx_msg void OnAppAbout();
$$IF(NODOCVIEW)
$$IF(PROJTYPE_MDI)
	afx_msg void OnFileNew();
$$ENDIF
$$ENDIF
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
$$ENDIF
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

$$IF(VBX)
/////////////////////////////////////////////////////////////////////////////
// VB-Event extern declarations

//{{AFX_VBX_REGISTER()
//}}AFX_VBX_REGISTER
$$ENDIF //VBX

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
