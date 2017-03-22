
// HyperPlaneDoc.cpp : implementation of the CHyperPlaneDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HyperPlane.h"
#endif

#include "HyperPlaneDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHyperPlaneDoc

IMPLEMENT_DYNCREATE(CHyperPlaneDoc, COleServerDocEx)

BEGIN_MESSAGE_MAP(CHyperPlaneDoc, COleServerDocEx)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &COleServerDocEx::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, &COleServerDocEx::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, &COleServerDocEx::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, &COleServerDocEx::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &COleServerDocEx::OnUpdateEditLinksMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_POPUP, &CHyperPlaneDoc::OnUpdateObjectVerbPopup)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &COleServerDocEx::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &COleServerDocEx::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CHyperPlaneDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CHyperPlaneDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CHyperPlaneDoc, COleServerDocEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IHyperPlane to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {57AC423D-3BFB-4FBE-9DFD-6268C09C0159}
static const IID IID_IHyperPlane =
{ 0x57AC423D, 0x3BFB, 0x4FBE, { 0x9D, 0xFD, 0x62, 0x68, 0xC0, 0x9C, 0x1, 0x59 } };

BEGIN_INTERFACE_MAP(CHyperPlaneDoc, COleServerDocEx)
	INTERFACE_PART(CHyperPlaneDoc, IID_IHyperPlane, Dispatch)
END_INTERFACE_MAP()


// CHyperPlaneDoc construction/destruction

CHyperPlaneDoc::CHyperPlaneDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

void CHyperPlaneDoc::AddPolygonObject(std::shared_ptr<HyperPlanePolygon>& _pPolygonObject)
{
	m_PolygonObjectList.push_back(_pPolygonObject);
	UpdateAllViews(nullptr, 0, _pPolygonObject.get()); // Tell all the views
}

void CHyperPlaneDoc::DeletePolygonObject(std::shared_ptr<HyperPlanePolygon>& _pPolygonObject)
{
	m_PolygonObjectList.remove(_pPolygonObject);
	UpdateAllViews(nullptr, 0, _pPolygonObject.get()); // Tell all the views
}

CHyperPlaneDoc::~CHyperPlaneDoc()
{
	AfxOleUnlockApp();
}

BOOL CHyperPlaneDoc::OnNewDocument()
{
	if (!COleServerDocEx::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


// CHyperPlaneDoc server implementation

COleServerItem* CHyperPlaneDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CHyperPlaneSrvrItem* pItem = new CHyperPlaneSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}




// CHyperPlaneDoc serialization

void CHyperPlaneDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleServerDocEx enables serialization
	//  of the container document's COleClientItem objects.
	COleServerDocEx::Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CHyperPlaneDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CHyperPlaneDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHyperPlaneDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CHyperPlaneDoc diagnostics

#ifdef _DEBUG
void CHyperPlaneDoc::AssertValid() const
{
	COleServerDocEx::AssertValid();
}

void CHyperPlaneDoc::Dump(CDumpContext& dc) const
{
	COleServerDocEx::Dump(dc);
}
#endif //_DEBUG


// CHyperPlaneDoc commands
