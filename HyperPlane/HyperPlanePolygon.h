#pragma once

#include <iostream>		// For stream I/O
#include <algorithm>	// For min(), max() and swap() 
#include <utility>		// For operator templates 
#include <cmath>		// For operator templates 
#include <vector> 
#include <memory>		//The shared_ptr<T> type supports conversion 
						//to type bool so you can use it in an if 
						//expression. You call the GetElementType() 
						//function for the document object to get 
						//the current element type.
						//This can be static_pointer_cast, dynamic_pointer_cast 
						//or const_pointer_cast, which are equivalent
						//to static_cast, dynamic_cast, and const_cast 
						//for ordinary pointers. dynamic_pointer_cast
						//checks that the cast is valid at runtime.
						//These operations are defined by function 
						//templates in the <memory> header and in the std namespace.
#include <random>
#include <string>
#include <cstring>
//#include <math.h>
#include <array>
#include <numeric>
#include <deque>
#include <functional>
#include <list>
#include <stack>
#include <tuple>
#include <iomanip>
#include <map>
#include <iterator>

// HyperPlanePolygon command target

// Highlight color
static const int select_c_rgba_red = 128, select_c_rgba_green = 255, select_c_rgba_blue = 255, select_c_rgba_alpha = 255;

// HyperPlanePolygon : CObject members
// ***********************************
class HyperPlanePolygon : public CObject
{
public:
	virtual ~HyperPlanePolygon() {};
	//virtual void Draw(CDC* pDC) {} // Virtual draw operation without highlight color
	virtual void Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList = nullptr) {}
	const CRect& GetEnclosingRect() const { return hpp_r_region; }
	void CreatePen(CPen& _pen_apen, std::shared_ptr<HyperPlanePolygon> _posObjList);

	//HyperPlanePolygon& operator = (const HyperPlanePolygon &_other); // array of operator
	//HyperPlanePolygon* operator = (const HyperPlanePolygon *_other); // adress of operator

protected:
	//int hpp_i_count;
	//bool hpp_b_selectedborder;
	//bool hpp_b_selectedbordercount;
	//bool hpp_b_selectedinside;
	//bool hpp_b_selectedinsidecount;
	//CPoint hpp_p_center;
	CRect hpp_r_region;
	CPoint hpp_p_start;
	int hpp_w_pen;
	int hpp_rgba_red;
	int hpp_rgba_green;
	int hpp_rgba_blue;
	int hpp_rgba_alpha;

protected:
	HyperPlanePolygon() {};
	HyperPlanePolygon(const CPoint& _p_start, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha, int _w_penwidth = 1);
};
// ***********************************
// HyperPlanePolygon : CObject members

// HPLine: HyperPlanePolygon : CObject members
// *******************************************
class HPLine : public HyperPlanePolygon
{
public:
	virtual ~HPLine(void) {};
	virtual void Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList = nullptr) override; // Function to display a line

	HPLine(const CPoint& _p_start, const CPoint& _p_end, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha);

public:
	//HPLine& operator = (const HPLine &_other); // array of operator
	//HPLine* operator = (const HPLine *_other); // adress of operator

protected:
	CPoint hpp_p_end;

protected:
	HPLine() {};
};
// *******************************************
// HPLine: HyperPlanePolygon : CObject members

// HPRectangle: HyperPlanePolygon : CObject members
// ************************************************
class HPRectangle : public HyperPlanePolygon
{
public:
	virtual ~HPRectangle() {};
	virtual void Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList = nullptr) override; // Function to display a rectangle

	HPRectangle(const CPoint& _p_start, const CPoint& _p_end, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha);

public:
	//HPLine& operator = (const HPLine &_other); // array of operator
	//HPLine* operator = (const HPLine *_other); // adress of operator

protected:
	CPoint hpp_p_bottomright;	// Bottom-right point for the rectangle;
	HPRectangle() {};				// Default constructor - should not be used 
};
// ************************************************
// HPRectangle: HyperPlanePolygon : CObject members

// HPCircle: HyperPlanePolygon : CObject members
// *********************************************
class HPCircle : public HyperPlanePolygon
{
public:
	virtual ~HPCircle() {};
	virtual void Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList = nullptr) override; // Function to display a circle

	HPCircle(const CPoint& _p_start, const CPoint& _p_end, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha);

public:
	//HPLine& operator = (const HPLine &_other); // array of operator
	//HPLine* operator = (const HPLine *_other); // adress of operator

protected:
	CPoint hpp_p_bottomright;	// Bottom-right point for the rectangle;
	HPCircle() {};				// Default constructor - should not be used 
};
// *********************************************
// HPCircle: HyperPlanePolygon : CObject members

// HPCurve: HyperPlanePolygon : CObject members
// ********************************************
class HPCurve : public HyperPlanePolygon
{
public:
	virtual ~HPCurve() {};
	virtual void Draw(CDC* pDC, std::shared_ptr<HyperPlanePolygon> _posObjList = nullptr) override; // Function to display a curve

	HPCurve(const CPoint& _p_first, const CPoint& _p_second, int _rgba_red, int _rgba_green, int _rgba_blue, int _rgba_alpha);
	void AddPointSegment(const CPoint& _p_point);	// Add a segment to the curve


public:
	//HPLine& operator = (const HPLine &_other); // array of operator
	//HPLine* operator = (const HPLine *_other); // adress of operator

protected:
	std::vector<CPoint> hpp_p_points;           // Points defining the curve 
	HPCurve() {};				// Default constructor - should not be used 
};
// ********************************************
// HPCurve: HyperPlanePolygon : CObject members
