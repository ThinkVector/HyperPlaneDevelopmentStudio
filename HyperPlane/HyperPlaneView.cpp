
// HyperPlaneView.cpp : implementation of the CHyperPlaneView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HyperPlane.h"
#endif

#include "HyperPlaneDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "HyperPlaneView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHyperPlaneView

IMPLEMENT_DYNCREATE(CHyperPlaneView, CView)

BEGIN_MESSAGE_MAP(CHyperPlaneView, CView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, &CHyperPlaneView::OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, &CHyperPlaneView::OnCancelEditCntr)
	ON_COMMAND(ID_FILE_PRINT, &CHyperPlaneView::OnFilePrint)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, &CHyperPlaneView::OnCancelEditSrvr)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHyperPlaneView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CHyperPlaneView construction/destruction

CHyperPlaneView::CHyperPlaneView()
{
	EnableActiveAccessibility();
	m_pSelection = NULL;
	// TODO: add construction code here

	devicerect = new CRect;
	firstdraw.PortInitialize(devicerect);
	firstdraw.PortOn(true);
	clickCount = 1;

	//initilize angular triple object
	tmp_r0_00	= CPoint(0, 0); tmp_r1_00	= CPoint(40, 0); tmp_r2_00		= CPoint(90, 0); tmp_r3_00		= CPoint(120, 0);
	tmp_ar0_00	= CPoint(0, 0); tmp_ar1_00	= CPoint(34, 10); tmp_ar2_00	= CPoint(70, 40); tmp_ar3_00	= CPoint(110, 15);
	firstangle_1.SetHyperPlaneViewLinear(tmp_r0_00, tmp_r1_00, tmp_r2_00, tmp_r3_00, tmp_ar0_00, tmp_ar1_00, tmp_ar2_00, tmp_ar3_00);
	
	tmp_r0_00	= CPoint(0, 0); tmp_r1_00	= CPoint(-60, 0); tmp_r2_00		= CPoint(-90, 0); tmp_r3_00		= CPoint(-120, 0);
	tmp_ar0_00	= CPoint(0, 0); tmp_ar1_00	= CPoint(-34, 60); tmp_ar2_00	= CPoint(-70, 40); tmp_ar3_00	= CPoint(-110, 75);
	firstangle_2.SetHyperPlaneViewLinear(tmp_r0_00, tmp_r1_00, tmp_r2_00, tmp_r3_00, tmp_ar0_00, tmp_ar1_00, tmp_ar2_00, tmp_ar3_00);

	tmp_r0_00	= CPoint(0, 0); tmp_r1_00	= CPoint(-70, 0); tmp_r2_00		= CPoint(-200, 0); tmp_r3_00	= CPoint(-220, 0);
	tmp_ar0_00	= CPoint(0, 0); tmp_ar1_00	= CPoint(-30, 80); tmp_ar2_00	= CPoint(-170, 80); tmp_ar3_00	= CPoint(-190, 120);
	firstangle_3.SetHyperPlaneViewLinear(tmp_r0_00, tmp_r1_00, tmp_r2_00, tmp_r3_00, tmp_ar0_00, tmp_ar1_00, tmp_ar2_00, tmp_ar3_00);
	
	tmp_r0_00 = tmp_r1_00 = tmp_r2_00 = tmp_r3_00 = tmp_ar0_00 = tmp_ar1_00 = tmp_ar2_00 = tmp_ar3_00 = CPoint(0,0);

	//create workable object a,b,c,d set
	object1a = firstangle_1;
	object1b = firstangle_1;
	object1c = firstangle_1;
	object1d = firstangle_1;
	object2a = firstangle_2;
	object2b = firstangle_2;
	object2c = firstangle_2;
	object2d = firstangle_2;
	object3a = firstangle_3;
	object3b = firstangle_3;
	object3c = firstangle_3;
	object3d = firstangle_3;

}

CHyperPlaneView::~CHyperPlaneView()
{
}

BOOL CHyperPlaneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHyperPlaneView drawing

void CHyperPlaneView::OnDraw(CDC* pDC)
{
	if (!pDC)
		return;

	CHyperPlaneDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CHyperPlaneCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.
	if (m_pSelection != NULL)
	{
		CSize size;
		CRect rect(10, 10, 210, 210);
		
		if (m_pSelection->GetExtent(&size, m_pSelection->m_nDrawAspect))
		{
			pDC->HIMETRICtoLP(&size);
			rect.right = size.cx + 10;
			rect.bottom = size.cy + 10;
		}
		m_pSelection->Draw(pDC, rect);
	}

	GetClientRect(&devicerect);
	firstdraw.PortInitialize(devicerect);

	firstdraw.Draw(pDC);

	if(clickCount % 2 == 0)
	{
		//angular lined pen 
		object1a.ChangeCenter(CPoint (100, 150));
		object1a.HyperPlaneViewAngular2(pDC, 1);
		object2a.ChangeCenter(CPoint(100 + 240, 150));
		object2a.HyperPlaneViewAngular2(pDC, 1);
		object3a.ChangeCenter(CPoint(100 + 460, 150));
		object3a.HyperPlaneViewAngular2(pDC, 1);

		//angular areaded pen 
		object1b.ChangeCenter(CPoint(100, 400));
		object1b.HyperPlaneViewAngular(pDC, 1);
		object2b.ChangeCenter(CPoint(100 + 240, 400));
		object2b.HyperPlaneViewAngular(pDC, 1);
		object3b.ChangeCenter(CPoint(100 + 460, 400));
		object3b.HyperPlaneViewAngular(pDC, 1);

		//linear lined pen 
		object1c.ChangeCenter(CPoint(100 + 600, 150));
		object1c.HyperPlaneViewLinear2(pDC, 1);
		object2c.ChangeCenter(CPoint(100 + 240 + 600, 150));
		object2c.HyperPlaneViewLinear2(pDC, 1);
		object3c.ChangeCenter(CPoint(100 + 460 + 600, 150));
		object3c.HyperPlaneViewLinear2(pDC, 1);

		//linear areaded pen 
		object1d.ChangeCenter(CPoint(100 + 600, 400));
		object1d.HyperPlaneViewLinear(pDC);
		object2d.ChangeCenter(CPoint(100 + 240 + 600, 400));
		object2d.HyperPlaneViewLinear(pDC);
		object3d.ChangeCenter(CPoint(100 + 460 + 600, 400));
		object3d.HyperPlaneViewLinear(pDC);

		//angular linear mix pen
		object1a.ChangeCenter(CPoint(100, 700));
		object1a.HyperPlaneViewAngular2(pDC, 1);
		object2a.ChangeCenter(CPoint(100 + 240, 700));
		object2a.HyperPlaneViewAngular2(pDC, 1);
		object3a.ChangeCenter(CPoint(100 + 460, 700));
		object3a.HyperPlaneViewAngular2(pDC, 1);
		object1c.ChangeCenter(CPoint(100, 700));
		object1c.HyperPlaneViewLinear2(pDC, 1);
		object2c.ChangeCenter(CPoint(100 + 240, 700));
		object2c.HyperPlaneViewLinear2(pDC, 1);
		object3c.ChangeCenter(CPoint(100 + 460, 700));
		object3c.HyperPlaneViewLinear2(pDC, 1);
	}
}

void CHyperPlaneView::HPTypeLoopDrawer_Test(CDC* pDC)
{
	// H type plane array continues loop drawer.
	// Test apply for left, up, right, down 
	// iteration for diagonal of rectangle
	//**********************
	//
	//            XXX XXX
	//            X.X X.X
	//            X.XXX.X
	//            X.....X
	//            X.XXX.X
	//            X.X X.X
	//            XXX XXX
	//
	//**********************
	//
	//            XXXXXXXX
	//            X..XX..X
	//            X..XX..X
	//            XX....XX
	//            XX....XX
	//            X..XX..X
	//            X..XX..X
	//            XXXXXXXX
	//
	//**********************


	//**********************
	// x^3/3 + y^3/3 = r^3/3 possible 1 unit partial angle of circle
	// so in +1 point in plane system does not shown right with this equation
	// so 1 unit partial angle goes point +1 in plane system does not drawable real point with this equation
	// this point must be angular diferential, not pointable
	//**********************

	int cx, cy;
	CRect rect;
	GetClientRect(&rect);

	cx = (rect.Width()) / 2;
	cy = (rect.Height()) / 2;

	//Set analitic view port to center (0,0)
	pDC->SetViewportOrg(cx, cy);
	pDC->MoveTo(0, 0); pDC->LineTo(0, cy);
	pDC->MoveTo(0, 0); pDC->LineTo(cx, 0);
	pDC->MoveTo(0, 0); pDC->LineTo(0, -cy);
	pDC->MoveTo(0, 0); pDC->LineTo(-cx, 0);
	//****************************************

	int xloop=-100;
	int yloop=100;

	int counter = 0;
	int rcountmax = 26;
	int rcount = 17;
	int ri = 1;
	int iy = 1;
	int ix = 1;
	int radius = 0;

	CPoint prevpoint;
	CPoint currentpoint;
	CPoint nextpoint;
	prevpoint = CPoint(0,0);
	currentpoint = CPoint(0, 0);
	nextpoint = CPoint(0, 0);

	CPoint L4U3B5_current= CPoint(xloop, yloop);
	int L4U3B5[4] = { -2, -2, 1, -2 };
	int L4U3B5_i = 0;

	int moving[26] = { -1, 2, 2, 2, 2, 2, 1, 1, -2, 1, 1, 2, 1, 1, -2, -2, -2, -2, -1, -1, 2, -1, -1, -2, -2, -1 };
	

	prevpoint = CPoint(xloop, yloop);

	while (counter < (100))
	{

		rcount = ri + rcount;
		if (rcount > rcountmax)
		{
			rcount = 0;
		}

		pDC->MoveTo(prevpoint);
		currentpoint = CPoint(xloop, yloop);
		pDC->LineTo(currentpoint);
		prevpoint = currentpoint;
		if (0)radius = 0;


			if (moving[rcount] == 1)
			{
				xloop++;
				yloop--;
				counter++;
			}
			else if(moving[rcount] == -1)
			{
				yloop--;
				xloop--;
			}
			else if (moving[rcount] == 2)
			{
				yloop--;
			}
			else if (moving[rcount] == -2)
			{
				xloop++;
			}

			
			pDC->MoveTo(L4U3B5_current);	

			if (L4U3B5_i == 3)L4U3B5_i = 0;
			else L4U3B5_i++;

			if (L4U3B5[L4U3B5_i] == -2)
			{
				L4U3B5_current.x++;
				L4U3B5_current.y--;
			}
			else if(L4U3B5[L4U3B5_i] == 1)
			{
				L4U3B5_current.x++;
			}
			
			pDC->LineTo(L4U3B5_current);
			
			
		
	}


	xloop = -100+9;
	yloop = 100-17;

	counter = 0;
	rcountmax = 26;
	rcount = 17;
	ri = 1;
	iy = 1;
	ix = 1;

	prevpoint = CPoint(0, 0);
	currentpoint = CPoint(0, 0);
	nextpoint = CPoint(0, 0);

	prevpoint = CPoint(xloop, yloop);

	while (counter < (100))
	{
		rcount = ri + rcount;
		if (rcount > rcountmax)
		{
			rcount = 0;
		}

		pDC->MoveTo(prevpoint);
		currentpoint = CPoint(xloop, yloop);
		pDC->LineTo(currentpoint);
		prevpoint = currentpoint;


		if (moving[rcount] == 1)
		{
			xloop--;
			yloop++;
			counter++;
		}
		else if (moving[rcount] == -1)
		{
			yloop++;
			xloop++;
		}
		else if (moving[rcount] == 2)
		{
			yloop++;
		}
		else if (moving[rcount] == -2)
		{
			xloop--;

		}

	}


	//H type plane array continues loop drawer
}

void CHyperPlaneView::HPAngle_Test(CDC* pDC)
{
	;
}

void CHyperPlaneView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}


// CHyperPlaneView printing


void CHyperPlaneView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHyperPlaneView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHyperPlaneView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHyperPlaneView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CHyperPlaneView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CView::OnDestroy();
}



// OLE Client support and commands

BOOL CHyperPlaneView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CHyperPlaneCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CHyperPlaneView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CHyperPlaneCntrItem object
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CHyperPlaneCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document
		CHyperPlaneDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CHyperPlaneCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);
		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted

		// TODO: reimplement selection as appropriate for your application
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

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation
void CHyperPlaneView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place
void CHyperPlaneView::OnSetFocus(CWnd* pOldWnd)
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

	CView::OnSetFocus(pOldWnd);
}

void CHyperPlaneView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

void CHyperPlaneView::OnFilePrint()
{
	//By default, we ask the Active document to print itself
	//using IOleCommandTarget. If you don't want this behavior
	//remove the call to COleDocObjectItem::DoDefaultPrinting.
	//If the call fails for some reason, we will try printing
	//the docobject using the IPrint interface.
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL); 
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;
	
	CView::OnFilePrint();

}


void CHyperPlaneView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHyperPlaneView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation
void CHyperPlaneView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// CHyperPlaneView diagnostics

#ifdef _DEBUG
void CHyperPlaneView::AssertValid() const
{
	CView::AssertValid();
}

void CHyperPlaneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHyperPlaneDoc* CHyperPlaneView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHyperPlaneDoc)));
	return (CHyperPlaneDoc*)m_pDocument;
}
#endif //_DEBUG


// CHyperPlaneView message handlers

//Mouse event constructors.
//*************************
void CHyperPlaneView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default   
	if(clickCount %2 == 0)Invalidate();
	else OnInitialUpdate();
	clickCount++;

	CView::OnLButtonUp(nFlags, point);
}
//*************************
//Mouse event constructor.