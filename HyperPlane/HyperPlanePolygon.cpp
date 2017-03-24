// HyperPlanePolygon.cpp : implementation file
//

#include "stdafx.h"
#include "HyperPlane.h"
#include "HyperPlanePolygon.h"

// HyperPlanePolygon member functions
//***********************************
HyperPlanePolygon::HyperPlanePolygon(const CPoint & _p_start, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha, int _w_penwidth) :
	hpp_p_start{ _p_start }, hpp_rgba_red{ _rgba_red }, hpp_rgba_green{ _rgba_green }, hpp_rgba_blue{ _rgba_blue }, hpp_rgba_alpha{ _rgba_alpha }, hpp_w_pen{ _w_penwidth } {}

//HyperPlanePolygon & HyperPlanePolygon::operator=(const HyperPlanePolygon & _other)
//{
//	// TODO: insert return statement here
//	//HyperPlanePolygon _tmpobject;
//	//return _tmpobject;
//
//	return *this;
//}

//HyperPlanePolygon * HyperPlanePolygon::operator=(const HyperPlanePolygon * _other)
//{
//	return this;
//
//	//return nullptr;
//}

void HyperPlanePolygon::CreatePen(CPen& _pen_apen, std::shared_ptr<HyperPlanePolygon> _posObjList)
{
	if (!_pen_apen.CreatePen(PS_SOLID, hpp_w_pen, 
		this == _posObjList.get() ?
		COLORREF(RGB(select_c_rgba_red, select_c_rgba_green, select_c_rgba_blue)) : 
		COLORREF(RGB(hpp_rgba_red, hpp_rgba_blue, hpp_rgba_red)) 
	))
	{
		// Pen creation failed     
		AfxMessageBox(_T("Drawing pen width creation failed."), MB_OK);
		AfxAbort();
	}
}
//***********************************
// HyperPlanePolygon member functions



// HPLine member functions
//************************
HPLine::HPLine(const CPoint& _p_start, const CPoint& _p_end, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha) :
	HyperPlanePolygon{ _p_start, _rgba_red, _rgba_green, _rgba_blue, _rgba_alpha }, hpp_p_end{ _p_end }
{
	// Define the enclosing regional rectangle
	hpp_r_region = CRect{ hpp_p_start, hpp_p_end };
	hpp_r_region.NormalizeRect();
	hpp_r_region.InflateRect(hpp_w_pen, hpp_w_pen);
}

void HPLine::Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList)
{
	// Create a pen for this object and initialize it  
	CPen aPen;
	CreatePen(aPen, _posObjList);
	CPen* pOldPen {pDC->SelectObject(&aPen)};	// Select the pen
	
	// Now draw the line  
	pDC->MoveTo(hpp_p_start);
	pDC->LineTo(hpp_p_end);
	pDC->SelectObject(pOldPen);	// Restore the old pen
}
//************************
// HPLine member functions

// HPRectangle member functions
//*****************************
HPRectangle::HPRectangle(const CPoint & _p_start, const CPoint & _p_end, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha) :
	HyperPlanePolygon{ _p_start, _rgba_red, _rgba_green, _rgba_blue, _rgba_alpha }
{
	// Normalize the rectangle defining points  
	hpp_p_start = CPoint{ (std::min)(_p_start.x, _p_end.x),(std::min)(_p_start.y, _p_end.y) };
	hpp_p_bottomright = CPoint{ (std::max)(_p_start.x, _p_end.x), (std::max)(_p_start.y, _p_end.y) };
	// Ensure width and height between the points is at least 2  
	if ((hpp_p_bottomright.x - hpp_p_start.x) < 2)    hpp_p_bottomright.x = hpp_p_start.x + 2;
	if ((hpp_p_bottomright.y - hpp_p_start.y) < 2)    hpp_p_bottomright.y = hpp_p_start.y + 2;
	// Define the enclosing rectangle  
	hpp_r_region = CRect{ hpp_p_start, hpp_p_bottomright };
	hpp_r_region.InflateRect(hpp_w_pen, hpp_w_pen);
}

void HPRectangle::Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList)
{
	// Create a pen for this object and initialize it  
	CPen aPen;
	CreatePen(aPen, _posObjList);          
	
	// Select the pen and the null brush  
	CPen* pOldPen {pDC->SelectObject(&aPen)};  
	CBrush* pOldBrush {dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH))};          
	
	// Now draw the rectangle  
	pDC->Rectangle(hpp_p_start.x, hpp_p_start.y, hpp_p_bottomright.x, hpp_p_bottomright.y);
	
	pDC->SelectObject(pOldBrush);	// Restore the old brush  
	pDC->SelectObject(pOldPen);		// Restore the old pen
}
//*****************************
// HPRectangle member functions

// HPCircle member functions
//**************************
HPCircle::HPCircle(const CPoint & _p_start, const CPoint & _p_end, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha) :
	HyperPlanePolygon{ _p_start, _rgba_red, _rgba_green, _rgba_blue, _rgba_alpha }
{
	// Calculate the radius using floating-point values  
	// because that is required by sqrt() function (in cmath)   
	long radius {static_cast<long> (sqrt(static_cast<double>((_p_end.x- _p_start.x)*(_p_end.x- _p_start.x)+ (_p_end.y- _p_start.y)*(_p_end.y- _p_start.y))))};
	if(radius < 1L) radius = 1L;       
	// Circle radius must be >= 1
	// Define left-top and right-bottom points of rectangle for MM_TEXT mode  
	hpp_p_start = CPoint { _p_start.x - radius, _p_start.y - radius};
	hpp_p_bottomright = CPoint { _p_start.x + radius, _p_start.y + radius};
	// Define the enclosing rectangle  
	hpp_r_region = CRect { hpp_p_start.x, hpp_p_start.y,hpp_p_bottomright.x, hpp_p_bottomright.y};
	hpp_r_region.InflateRect(hpp_w_pen, hpp_w_pen);
}

void HPCircle::Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList)
{
	// Create a pen for this object and initialize it   
	CPen aPen;   
	CreatePen(aPen, _posObjList);

	CPen* pOldPen {pDC->SelectObject(&aPen)};	// Select the pen
	
	// Select a null brush
	CBrush* pOldBrush {dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH))};
	
	// Now draw the circle
	pDC->Ellipse(hpp_p_start.x, hpp_p_start.y, hpp_p_bottomright.x, hpp_p_bottomright.y);
	
	pDC->SelectObject(pOldPen);		// Restore the old pen   
	pDC->SelectObject(pOldBrush);	// Restore the old brush 
}
//**************************
// HPCircle member functions

// HPCurve member functions
//*************************
HPCurve::HPCurve(const CPoint & _p_first, const CPoint & _p_second, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha) :
	HyperPlanePolygon{ _p_first, _rgba_red, _rgba_green, _rgba_blue, _rgba_alpha }
{
	hpp_p_points.push_back(_p_second);
	hpp_r_region = CRect{ 
		(std::min)(_p_first.x, _p_second.x), (std::min)(_p_first.y, _p_second.y),
		(std::max)(_p_first.x, _p_second.x), (std::max)(_p_first.y, _p_second.y) };
	hpp_r_region.InflateRect(hpp_w_pen, hpp_w_pen);
}

void HPCurve::AddPointSegment(const CPoint & _p_point)
{
	hpp_p_points.push_back(_p_point);	// Add the point to the end
										
	// Modify the enclosing rectangle for the new point   
	hpp_r_region.DeflateRect(hpp_w_pen, hpp_w_pen);
	hpp_r_region = CRect {
		(std::min)(_p_point.x, hpp_r_region.left),
		(std::min)(_p_point.y, hpp_r_region.top),
		(std::max)(_p_point.x, hpp_r_region.right),
		(std::max)(_p_point.y, hpp_r_region.bottom)};
	
	hpp_r_region.InflateRect(hpp_w_pen, hpp_w_pen);
}

void HPCurve::Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList)
{
	// Create a pen for this object and initialize it   
	CPen aPen;
	CreatePen(aPen, _posObjList);
	CPen* pOldPen {pDC->SelectObject(&aPen)};	// Select the pen

	// Now draw the curve   
	pDC->MoveTo(hpp_p_start);   
	for(const auto& point : hpp_p_points)    
		pDC->LineTo(point);

	pDC->SelectObject(pOldPen);	// Restore the old pen
}
//*************************
// HPCurve member functions
