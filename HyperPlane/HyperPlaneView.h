
// HyperPlaneView.h : interface of the CHyperPlaneView class
//

#pragma once

#include "HyperPlaneViewPort.h"
#include "HyperPlaneViewAngle.h"
#include "HyperPlanePolygon.h"
#include "HyperPlaneTypes.h"


class CHyperPlaneCntrItem;

class CHyperPlaneView : public CView
{
protected: // create from serialization only
	CHyperPlaneView();
	DECLARE_DYNCREATE(CHyperPlaneView)

// Attributes
public:
	CHyperPlaneDoc* GetDocument() const;
	// m_pSelection holds the selection to the current CHyperPlaneCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CHyperPlaneCntrItem objects.  This selection
	//  mechanism is provided just to help you get started

	// TODO: replace this selection mechanism with one appropriate to your app
	CHyperPlaneCntrItem* m_pSelection;

// Operations
public:
	HyperPlaneViewPort firstdraw;
	HyperPlaneViewAngle firstangle, firstangle_1, firstangle_2, firstangle_3;

	HyperPlaneViewAngle object1a, object2a, object3a;
	HyperPlaneViewAngle object1b, object2b, object3b;
	HyperPlaneViewAngle object1c, object2c, object3c;
	HyperPlaneViewAngle object1d, object2d, object3d;
	
	//HyperPlanePolygon polygon1;

	CRect devicerect;
	int clickCount;

public:
	CPoint tmp_r0_00, tmp_r1_00, tmp_r2_00, tmp_r3_00, tmp_ar0_00, tmp_ar1_00, tmp_ar2_00, tmp_ar3_00;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void HPTypeLoopDrawer_Test(CDC* pDC);
	virtual void HPAngle_Test(CDC* pDC);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support

// Implementation
public:
	virtual ~CHyperPlaneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_b_mouseclick;
	bool m_b_mousemove;
	bool m_b_mouserelease;
	CPoint m_mouseclick;
	CPoint m_mousemove;
	CPoint m_mouserelease;
	int m_c_rgba_red, m_c_rgba_green, m_c_rgba_blue, m_c_rgba_alpha;

	std::shared_ptr<HyperPlanePolygon> CreateHyperPlanePolygon() const; // Create a new HyperPlanePolygon on the heap

	CPoint m_CursorPos; // Cursor position
	CPoint m_FirstPos; // Original position in a move
	std::shared_ptr<HyperPlanePolygon> m_pTempElement;
	std::shared_ptr<HyperPlanePolygon> m_pSelected; // Records element under the cursor
	bool m_MoveMode{ false }; // Move element flag

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnFilePrint();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HyperPlaneView.cpp
inline CHyperPlaneDoc* CHyperPlaneView::GetDocument() const
   { return reinterpret_cast<CHyperPlaneDoc*>(m_pDocument); }
#endif

