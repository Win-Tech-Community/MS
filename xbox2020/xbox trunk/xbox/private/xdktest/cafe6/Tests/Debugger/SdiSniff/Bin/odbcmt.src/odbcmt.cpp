// ODBCMT.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ODBCMT.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ODBCDoc.h"
#include "ODBCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CODBCCommandLineInfo: public CCommandLineInfo
{
public:
	int m_commandrun;
	CODBCCommandLineInfo::CODBCCommandLineInfo():CCommandLineInfo()
	{
		m_commandrun=0;
	}
	virtual void ParseParam(LPCTSTR lpszParam,BOOL bFlag,BOOL bLast)
	{
		if(bFlag==TRUE && (*lpszParam=='r' || *lpszParam=='R'))
		{
			if(lpszParam[1]==0)
				m_commandrun=1; //default
			else if(lpszParam[1]=='=' || lpszParam[1]==':')
				m_commandrun=atoi(lpszParam+2); //after '=' or ':'
		}
		CCommandLineInfo::ParseParam(lpszParam,bFlag,bLast);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CODBCMTApp

BEGIN_MESSAGE_MAP(CODBCMTApp, CWinApp)
	//{{AFX_MSG_MAP(CODBCMTApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODBCMTApp construction

CODBCMTApp::CODBCMTApp()
{
	m_commandrun=0;
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CODBCMTApp object

CODBCMTApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CODBCMTApp initialization

BOOL CODBCMTApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	SetRegistryKey(_T("Microsoft"));
	LoadStdProfileSettings(16);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_ODBCMTTYPE,
		RUNTIME_CLASS(CODBCMTDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CODBCMTView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CODBCCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if(cmdInfo.m_commandrun!=0 &&
		cmdInfo.m_nShellCommand==CCommandLineInfo::FileOpen)
		m_commandrun=cmdInfo.m_commandrun;
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
	{
		m_commandrun=0;
		return FALSE;
	}
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CODBCMTApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CODBCMTApp commands
