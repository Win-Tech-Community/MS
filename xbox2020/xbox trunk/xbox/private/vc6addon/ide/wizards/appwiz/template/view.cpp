// $$view_ifile$$.cpp : implementation of the $$VIEW_CLASS$$ class
//

#include "stdafx.h"
#include "$$root$$.h"

$$IF(CRecordView || CDaoRecordView || COleDBRecordView)
#include "$$recset_hfile$$.h"
$$ENDIF
#include "$$doc_hfile$$.h"
$$IF(CONTAINER || CONTAINER_SERVER)
#include "$$cntritem_hfile$$.h"
$$ENDIF
#include "$$view_hfile$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$VIEW_CLASS$$

IMPLEMENT_DYNCREATE($$VIEW_CLASS$$, $$VIEW_BASE_CLASS$$)

BEGIN_MESSAGE_MAP($$VIEW_CLASS$$, $$VIEW_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$VIEW_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
$$ENDIF
$$IF(CONTAINER || CONTAINER_SERVER)
	ON_WM_DESTROY()
$$IF(!CRichEditView)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
$$ENDIF //!CRichEditView
$$ENDIF //CONTAINERS
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
$$ENDIF
	//}}AFX_MSG_MAP
$$IF(PRINT)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, $$VIEW_BASE_CLASS$$::OnFilePrint)
$$IF(!CHtmlView)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, $$VIEW_BASE_CLASS$$::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, $$VIEW_BASE_CLASS$$::OnFilePrintPreview)
$$ENDIF
$$ENDIF //PRINT
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// $$VIEW_CLASS$$ construction/destruction

$$VIEW_CLASS$$::$$VIEW_CLASS$$()
$$IF(CFormView || CRecordView || CDaoRecordView || COleDBRecordView)
	: $$VIEW_BASE_CLASS$$($$VIEW_CLASS$$::IDD)
$$ENDIF
{
$$IF(CFormView || CRecordView || CDaoRecordView || COleDBRecordView)
	//{{AFX_DATA_INIT($$VIEW_CLASS$$)
		// NOTE: the ClassWizard will add member initialization here
$$IF(|| CRecordView || CDaoRecordView || COleDBRecordView)
	m_pSet = NULL;
$$ENDIF
	//}}AFX_DATA_INIT
$$ENDIF
$$IF(CONTAINER || CONTAINER_SERVER)
$$IF(!CRichEditView)
	m_pSelection = NULL;
$$ENDIF //!CRichEditView
$$ENDIF //CONTAINERS
$$IF(VERBOSE)
	// TODO: add construction code here

$$ENDIF
}

$$VIEW_CLASS$$::~$$VIEW_CLASS$$()
{
}
$$IF(CFormView || CRecordView || CDaoRecordView || COleDBRecordView)

void $$VIEW_CLASS$$::DoDataExchange(CDataExchange* pDX)
{
	$$VIEW_BASE_CLASS$$::DoDataExchange(pDX);
	//{{AFX_DATA_MAP($$VIEW_CLASS$$)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
$$ENDIF

BOOL $$VIEW_CLASS$$::PreCreateWindow(CREATESTRUCT& cs)
{
$$IF(VERBOSE)
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

$$ENDIF //VERBOSE
$$IF(CEditView)
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
$$ELSE //!CEditView
	return $$VIEW_BASE_CLASS$$::PreCreateWindow(cs);
$$ENDIF //CEditView
}
$$IF(CFormView || CRecordView || CDaoRecordView || COleDBRecordView)
$$ELIF(!CRichEditView)

/////////////////////////////////////////////////////////////////////////////
// $$VIEW_CLASS$$ drawing

void $$VIEW_CLASS$$::OnDraw(CDC* pDC)
{
	$$DOC_CLASS$$* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
$$IF(PROJTYPE_EXPLORER)
$$IF(CListView)
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
$$ENDIF
$$ENDIF
$$IF(VERBOSE)
	// TODO: add draw code for native data here
$$ENDIF //VERBOSE
$$IF(CONTAINER || CONTAINER_SERVER)
$$IF(!ACTIVE_DOC_CONTAINER)
$$IF(!CRichEditView)
$$IF(VERBOSE)
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by $$CNTRITEM_CLASS$$,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.
$$ENDIF //VERBOSE

	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = ($$CNTRITEM_CLASS$$*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, CRect(10, 10, 210, 210));
$$ENDIF //!CRichEditView
$$ENDIF //ACTIVE_DOC_CONTAINER
$$ENDIF //CONTAINERS
}
$$ENDIF // !(CFormView || CRecordView || CDaoRecordView)
$$IF(CScrollView || CONTAINER || CONTAINER_SERVER || CRecordView || CDaoRecordView || COleDBRecordView || CListView || CTreeView || CFormView || CHtmlView)

void $$VIEW_CLASS$$::OnInitialUpdate()
{
$$IF(CRecordView || CDaoRecordView || COleDBRecordView)
	m_pSet = &GetDocument()->$$RECSET_VARIABLE$$;
$$IF(COleDBRecordView)
	{
		CWaitCursor wait;
		HRESULT hr = m_pSet->Open();
		if (hr != S_OK)
		{
			AfxMessageBox(_T("Record set failed to open."), MB_OK);
$$IF(VERBOSE)
			// Disable the Next and Previous record commands,
			// since attempting to change the current record without an
			// open RecordSet will cause a crash.
$$ENDIF
			m_bOnFirstRecord = TRUE;
			m_bOnLastRecord = TRUE;
		}				
	}
$$ENDIF
$$ENDIF
	$$VIEW_BASE_CLASS$$::OnInitialUpdate();
$$IF(CRecordView || CDaoRecordView || CFormView)
$$IF(PROJTYPE_SDI)
	GetParentFrame()->RecalcLayout();
$$ENDIF
	ResizeParentToFit();
$$ENDIF

$$IF(VERBOSE)
$$IF(CListView)

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
$$ELIF(CTreeView)

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
$$ELIF(CHtmlView)
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
$$ENDIF //Views
$$ENDIF //VERBOSE
$$IF(CHtmlView)
	Navigate2(_T("http://www.microsoft.com/visualc/"),NULL,NULL);
$$ENDIF //CHTMLVIEW
$$IF(CONTAINER || CONTAINER_SERVER)
$$IF(!CRichEditView)

$$IF(VERBOSE)
	// TODO: remove this code when final selection model code is written
$$ENDIF //VERBOSE
	m_pSelection = NULL;    // initialize selection

$$ENDIF //!CRichEditView
$$IF(ACTIVE_DOC_CONTAINER)
	//Active documents should always be activated
	COleDocument* pDoc = (COleDocument*) GetDocument();
	if (pDoc != NULL)
	{
		// activate the first one
		POSITION posItem = pDoc->GetStartPosition();
		if (posItem != NULL)
		{
			CDocItem* pItem = pDoc->GetNextItem(posItem);

			// only if it's an Active document
			COleDocObjectItem *pDocObjectItem =
				DYNAMIC_DOWNCAST(COleDocObjectItem, pItem);

			if (pDocObjectItem != NULL)
			{
				pDocObjectItem->DoVerb(OLEIVERB_SHOW, this);
			}
		}
	}
$$ENDIF
$$IF(CRichEditView)

$$IF(VERBOSE)
	// Set the printing margins (720 twips = 1/2 inch).
$$ENDIF //VERBOSE
	SetMargins(CRect(720, 720, 720, 720));
$$ENDIF	//CRichEditView
$$ENDIF //CONTAINERS
$$IF(CScrollView)
	CSize sizeTotal;
$$IF(VERBOSE)
	// TODO: calculate the total size of this view
$$ENDIF
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
$$ENDIF
}
$$ENDIF // CScrollView || CONTAINER || CONTAINER_SERVER || CRecordView || CDaoRecordView || CFormView || CHtmlView
$$IF(PRINT)

/////////////////////////////////////////////////////////////////////////////
// $$VIEW_CLASS$$ printing

$$IF(!CHtmlView)
BOOL $$VIEW_CLASS$$::OnPreparePrinting(CPrintInfo* pInfo)
{
$$IF(CEditView)
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
$$ELSE
$$IF(ACTIVE_DOC_CONTAINER)
	if (!CView::DoPreparePrinting(pInfo))
		return FALSE;
	
	if (!COleDocObjectItem::OnPreparePrinting(this, pInfo))
		return FALSE;

	return TRUE;
$$ELSE
	// default preparation
	return DoPreparePrinting(pInfo);
$$ENDIF // ACTIVE_DOC_CONTAINER
$$ENDIF // CEditView
}

$$IF(!CRichEditView)
$$IF(CEditView)
void $$VIEW_CLASS$$::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
$$ELSE
void $$VIEW_CLASS$$::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
$$ENDIF //CEditView
{
$$IF(CEditView)
$$IF(VERBOSE)
	// Default CEditView begin printing.
$$ENDIF //VERBOSE
	CEditView::OnBeginPrinting(pDC, pInfo);
$$ELSE
$$IF(VERBOSE)
	// TODO: add extra initialization before printing
$$ENDIF //VERBOSE
$$ENDIF //CEditView
}

$$IF(CEditView)
void $$VIEW_CLASS$$::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
$$ELSE
void $$VIEW_CLASS$$::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
$$ENDIF //CEditView
{
$$IF(CEditView)
$$IF(VERBOSE)
	// Default CEditView end printing
$$ENDIF //VERBOSE
	CEditView::OnEndPrinting(pDC, pInfo);
$$ELSE
$$IF(VERBOSE)
	// TODO: add cleanup after printing
$$ENDIF //VERBOSE
$$ENDIF //CEditView
}
$$ENDIF //!CRichEditView
$$ENDIF // !CHtmlView
$$IF(CFormView || ACTIVE_DOC_CONTAINER)

$$IF(ACTIVE_DOC_CONTAINER)
void $$VIEW_CLASS$$::OnPrint(CDC* pDC, CPrintInfo* pInfo)
$$ELSE
void $$VIEW_CLASS$$::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
$$ENDIF
{
$$IF(VERBOSE)
	// TODO: add customized printing code here
$$ENDIF
$$IF(ACTIVE_DOC_CONTAINER)
	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);
$$ENDIF
}
$$ENDIF //CFormView || OLEDOCCONTAINER
$$ENDIF //PRINT
$$IF(CONTAINER || CONTAINER_SERVER)

void $$VIEW_CLASS$$::OnDestroy()
{
$$IF(VERBOSE)
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
$$ENDIF
   $$VIEW_BASE_CLASS$$::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}

$$IF(!CRichEditView)

/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL $$VIEW_CLASS$$::IsSelected(const CObject* pDocItem) const
{
$$IF(VERBOSE)
	// The implementation below is adequate if your selection consists of
	//  only $$CNTRITEM_CLASS$$ objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

$$ENDIF
	return pDocItem == m_pSelection;
}

void $$VIEW_CLASS$$::OnInsertObject()
{
$$IF(VERBOSE)
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new $$CNTRITEM_CLASS$$ object.
$$ENDIF
	COleInsertDialog dlg;
$$IF(ACTIVE_DOC_CONTAINER)
	if (dlg.DoModal(COleInsertDialog::DocObjectsOnly) != IDOK)
		return;
$$ELSE
	if (dlg.DoModal() != IDOK)
		return;
$$ENDIF

	BeginWaitCursor();

	$$CNTRITEM_CLASS$$* pItem = NULL;
	TRY
	{
$$IF(VERBOSE)
		// Create new item connected to this document.
$$ENDIF
		$$DOC_CLASS$$* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new $$CNTRITEM_CLASS$$(pDoc);
		ASSERT_VALID(pItem);

$$IF(VERBOSE)
		// Initialize the item from the dialog data.
$$ENDIF
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
$$IF(ACTIVE_DOC_CONTAINER)
		pItem->DoVerb(OLEIVERB_SHOW, this);
$$ELSE
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);
$$ENDIF

		ASSERT_VALID(pItem);
$$IF(VERBOSE)

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application
$$ENDIF

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

$$IF(VERBOSE)
// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
$$ENDIF
void $$VIEW_CLASS$$::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

$$IF(VERBOSE)
// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
$$ENDIF
void $$VIEW_CLASS$$::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	$$VIEW_BASE_CLASS$$::OnSetFocus(pOldWnd);
}

void $$VIEW_CLASS$$::OnSize(UINT nType, int cx, int cy)
{
	$$VIEW_BASE_CLASS$$::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}
$$ENDIF //!CRichEditView
$$ENDIF //CONTAINER || CONTAINER_SERVER
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

$$IF(VERBOSE)
// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
$$ENDIF
void $$VIEW_CLASS$$::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}
$$ENDIF //SERVERS

/////////////////////////////////////////////////////////////////////////////
// $$VIEW_CLASS$$ diagnostics

#ifdef _DEBUG
void $$VIEW_CLASS$$::AssertValid() const
{
	$$VIEW_BASE_CLASS$$::AssertValid();
}

void $$VIEW_CLASS$$::Dump(CDumpContext& dc) const
{
	$$VIEW_BASE_CLASS$$::Dump(dc);
}

$$DOC_CLASS$$* $$VIEW_CLASS$$::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS($$DOC_CLASS$$)));
	return ($$DOC_CLASS$$*)m_pDocument;
}
#endif //_DEBUG
$$IF(CRecordView || CDaoRecordView ||COleDBRecordView)

/////////////////////////////////////////////////////////////////////////////
// $$VIEW_CLASS$$ database support
$$IF(CRecordView)
CRecordset* $$VIEW_CLASS$$::OnGetRecordset()
$$ELIF(CDaoRecordView)
CDaoRecordset* $$VIEW_CLASS$$::OnGetRecordset()
$$ELSE
CRowset* $$VIEW_CLASS$$::OnGetRowset()
$$ENDIF
{
	return m_pSet;
}

$$ENDIF //CRecordView || CDaoRecordView

/////////////////////////////////////////////////////////////////////////////
// $$VIEW_CLASS$$ message handlers
$$IF(PROJTYPE_EXPLORER)
$$IF(CListView)
void $$VIEW_CLASS$$::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
$$IF(VERBOSE)
	//TODO: add code to react to the user changing the view style of your window
$$ENDIF
}
$$ENDIF
$$ENDIF
