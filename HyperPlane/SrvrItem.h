
// SrvrItem.h : interface of the CHyperPlaneSrvrItem class
//

#pragma once

class CHyperPlaneSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CHyperPlaneSrvrItem)

// Constructors
public:
	CHyperPlaneSrvrItem(CHyperPlaneDoc* pContainerDoc);

// Attributes
	CHyperPlaneDoc* GetDocument() const
		{ return reinterpret_cast<CHyperPlaneDoc*>(COleServerItem::GetDocument()); }

// Overrides
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

// Implementation
public:
	~CHyperPlaneSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

