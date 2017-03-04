
// CntrItem.h : interface of the CHyperPlaneCntrItem class
//

#pragma once

class CHyperPlaneDoc;
class CHyperPlaneView;

class CHyperPlaneCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CHyperPlaneCntrItem)

// Constructors
public:
	CHyperPlaneCntrItem(CHyperPlaneDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer

// Attributes
public:
	CHyperPlaneDoc* GetDocument()
		{ return reinterpret_cast<CHyperPlaneDoc*>(COleClientItem::GetDocument()); }
	CHyperPlaneView* GetActiveView()
		{ return reinterpret_cast<CHyperPlaneView*>(COleClientItem::GetActiveView()); }

public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();

protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);
	virtual BOOL CanActivate();

// Implementation
public:
	~CHyperPlaneCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

