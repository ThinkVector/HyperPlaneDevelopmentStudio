
// HyperPlaneDoc.h : interface of the CHyperPlaneDoc class
//


#pragma once

//new added
#include "HyperPlaneViewAngle.h"
#include "HyperPlaneViewPort.h"
#include "HyperPlanePolygon.h"
#include "HyperPlaneTypes.h"
//new added

//new iterator for hyperplane polygon object
using PolygonObjectIterator = std::list<std::shared_ptr<HyperPlanePolygon>>::const_iterator;
//new iterator for hyperplane polygon object

class CHyperPlaneSrvrItem;

class CHyperPlaneDoc : public COleServerDocEx
{
protected: // create from serialization only
	CHyperPlaneDoc();
	DECLARE_DYNCREATE(CHyperPlaneDoc)

// Attributes
public:
	CHyperPlaneSrvrItem* GetEmbeddedItem()
	{
		return reinterpret_cast<CHyperPlaneSrvrItem*>(COleServerDocEx::GetEmbeddedItem());
	}

// Operations
public:
	//adding objects list to new object
	void AddPolygonObject(std::shared_ptr<HyperPlanePolygon>& _pPolygonObject);
	void DeletePolygonObject(std::shared_ptr<HyperPlanePolygon>& _pPolygonObject);

	//types constructors
	HyperPlaneObjectType GetObjectType()const 
	{ 
		return m_t_objecttype; 
	}
	HyperPlaneObjectColorType GetObjectColorType()const 
	{ 
		return m_t_objectcolortype; 
	}

	// Finds the element under the point
	std::shared_ptr<HyperPlanePolygon> FindElement(const CPoint& point)const
	{
		for (const auto& posObjx : m_PolygonObjectList)
		{
			if (posObjx->GetEnclosingRect().PtInRect(point))
				return posObjx;
		}
		return nullptr;
	}

	//iterator type
	// Provide a begin iterator for the HyperPlanePolygonObject
	PolygonObjectIterator begin() const
	{
		return std::begin(m_PolygonObjectList); 
	}
	// Provide an end iterator for the HyperPlanePolygonObject
	PolygonObjectIterator end() const
	{
		return std::end(m_PolygonObjectList);
	}

//Operations
protected:
	//types operation
	HyperPlaneObjectType m_t_objecttype{ HyperPlaneObjectType::LINEAR_CURVE };	//current object type
	HyperPlaneObjectColorType m_t_objectcolortype{ HyperPlaneObjectColorType::BLUE_SINGLE };	//current object color type

	//create shared object list address operation
	std::list<std::shared_ptr<HyperPlanePolygon>> m_PolygonObjectList;

// Overrides
protected:
	virtual COleServerItem* OnGetEmbeddedItem();
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CHyperPlaneDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

