// HyperPlaneViewAngle.cpp : implementation file
//

#include "stdafx.h"
#include "HyperPlane.h"
#include "HyperPlaneViewAngle.h"


// HyperPlaneViewAngle
//**********************
// ! ! ! ATTENTION UNDER CONSTRUCTION ! ! ! 
//**********************
// x^3/3 + y^3/3 = r^3/3 possible 1 unit partial angle of circle
// so in +1 point in plane system does not shown right with this equation
// so 1 unit partial angle goes point +1 in plane system does not drawable real point with this equation
// this point must be angular diferential, not pointable
//**********************
// x^2 + y^2 = r^2 measure the angle of view port.
// x + y = ar draw angular plane to view port 
// when ar_series before serialized and strecthed for view port.
//**********************
// Plane does not shown its hidden pillar so 
// (+x,+y) -> give positive angular max period,
// (-x,-y) -> give negative angular min period,
// (+x,-y) or (-x, +y) -> give left and right shift of angular period,
// (-x, -y) + (+x, +y) -> give non period,
//**********************
// (+0, +0) (+1, +0) to (+0,+0) (+1, +1) -> (UL1P) UpLeft1Period
// (+0, +0) (+0, +1) to (+0,+0) (+1, +1) -> (RD1P) RightDown1Period
// (+0, +0) (+0, +1) to (+0,+0) (-1, +1) -> (LD1P) LeftDown1Period
// (+0, +0) (-1, +0) to (+0,+0) (-1, +1) -> (UR1P) UpRight1Period
// (+0, +0) (-1, +0) to (+0, +0) (-1,-1) -> (DR1P) DownRight1Period
// (+0, +0) (+0, -1) to (+0, +0) (-1,-1) -> (LU1P) LeftUp1Period
// (+0, +0) (+0, -1) to (+0, +0) (+1, -1) ->(RU1P) RightUp1Period
// (+0, +0) (+1, +0) to (+0, +0) (+1, -1) ->(DL1P) DownLeft1Period
//**********************
// Basic Square Control Points
//**********************
//
//   ROT             ROT
//      W     U     WH
//        ---------|
//        |        |
//      L | Center | R
//        |        |
//        |---------
//      HW    D     H
//   ROT             ROT
//**********************
// Basic Circle Control Points
//**********************
//        
//          ROT                       ROT
//                       RU       
//        
//                       *
//                     *   *
//                   *       *
//              *      *   *      *
//            *   *      *      *   *
//          *       *  Center *       *  
//            *   *      *      *   *
//              *      *   *      *
//                   *       *
//                     *   *
//                       *
//        
//                      RD      
//          ROT                       ROT


HyperPlaneViewAngle::HyperPlaneViewAngle()
{
	//Special Series
	//**************
	Series_OddPrime		= 1.35711;		// continue...
	Series_NotNumber	= 2;			// continue...
	Series_OddNotPrime	= 9.15212527;	// continue...
	Series_EvenNumber	= 4.681012;		// continue...
	Series_OddNotNumber = 1.4737184;	// continue...
	// Series_NotNumber / Series_OddNotNumber = Series_OddPrime
	//**************
	//Special Series
}

HyperPlaneViewAngle::HyperPlaneViewAngle(CPoint _r0, CPoint _r1, CPoint _r2, CPoint _r3, CPoint _ar0, CPoint _ar1, CPoint _ar2, CPoint _ar3, CPoint _br0, CPoint _br1, CPoint _br2, CPoint _br3)
{
	r0 = _r0;
	r1 = _r1;
	r2 = _r2;
	r3 = _r3;
	ar0 = _ar0;
	ar1 = _ar1;
	ar2 = _ar2;
	ar3 = _ar3;
	br0 = _br0;
	br1 = _br1;
	br2 = _br2;
	br3 = _br3;
}

HyperPlaneViewAngle::~HyperPlaneViewAngle()
{
}

HyperPlaneViewAngle & HyperPlaneViewAngle::operator=(const HyperPlaneViewAngle & _other)
{
	// TODO: insert return statement here

	r0 = _other.r0;
	r1 = _other.r1;
	r2 = _other.r2;
	r3 = _other.r3;
	ar0 = _other.ar0;
	ar1 = _other.ar1;
	ar2 = _other.ar2;
	ar3 = _other.ar3;
	br0 = _other.br0;
	br1 = _other.br1;
	br2 = _other.br2;
	br3 = _other.br3;
	
	HyperPlaneViewAngle(_other.r0, _other.r1, _other.r2, _other.r3, _other.ar0, _other.ar1, _other.ar2, _other.ar3, _other.br0, _other.br1, _other.br2, _other.br3);

	return *this;
}

void HyperPlaneViewAngle::ChangeCenter(CPoint _r)
{
	CPoint _centeralchange = (_r - r0);

	r0 += _centeralchange;
	r1 += _centeralchange;
	r2 += _centeralchange;
	r3 += _centeralchange;
	ar0 += _centeralchange;
	ar1 += _centeralchange;
	ar2 += _centeralchange;
	ar3 += _centeralchange;
	br0 += _centeralchange;
	br1 += _centeralchange;
	br2 += _centeralchange;
	br3 += _centeralchange;
}

void HyperPlaneViewAngle::HyperPlaneViewAngular2(CDC* pDC, int line = 1)
{
	double singular = 6.0; // -Series_OddPrime - Series_EvenNumber; // -6.01; //-4.68101214161820;
	double doubler = -6.0; // -Series_OddPrime - Series_EvenNumber; // -6.01; // -4.68101214161820;
	double singularmultiplier = 1;
	double doublemultiplier = 2;

	if (r0.x < r1.x)
	{
		if (ar2.y > ar1.y)
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - int ( doublemultiplier * (r1.y - ar1.y - doubler)), r1.x, r1.y + int ( doublemultiplier * (r1.y - ar1.y - doubler)), ar1.x, ar1.y, r1.x, r1.y);
			pDC->MoveTo(r1);
			pDC->LineTo(r0);
		}
		else
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x, r0.y - int(1 * (r1.y - ar1.y - singular)), r1.x, r1.y + int(1 * (r1.y - ar1.y - singular)), r0.x, r0.y, r1.x, r1.y);
			pDC->LineTo(r1);
			pDC->LineTo(r0);
		}

		if (ar2.y > ar1.y)
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y + int ( doublemultiplier * (br1.y - r1.y - doubler)), r1.x, r1.y - int ( doublemultiplier * (br1.y - r1.y - doubler)), r1.x, r1.y, br1.x, br1.y);
			pDC->LineTo(r0);
		}
		else
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x, r0.y + int(1 * (br1.y - r1.y - singular)), r1.x, r1.y - int(1 * (br1.y - r1.y - singular)), r1.x, r1.y, r0.x, r0.y);
			pDC->LineTo(r0);
		}

		pDC->MoveTo(ar2);
		pDC->LineTo(ar1);
		if (ar2.y > ar1.y)
		{
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - int(doublemultiplier * (r1.y - ar1.y - doubler)), r1.x, r1.y + int(doublemultiplier * (r1.y - ar1.y - doubler)), ar1.x, ar1.y, r1.x, r1.y);
		}
		else
		{
			pDC->ArcTo(r0.x, r0.y - int(1 * (r1.y - ar1.y - singular)), r1.x, r1.y + int(1 * (r1.y - ar1.y - singular)), (r0.x + r1.x) / 2, ar1.y, r1.x, r1.y);
		}
		pDC->LineTo(r1);
		pDC->MoveTo(ar2);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - int(doublemultiplier * (r2.y - ar2.y - doubler)), r2.x, r2.y + int(doublemultiplier * (r2.y - ar2.y - doubler)), ar2.x, ar2.y, r2.x, r2.y);
		pDC->LineTo(r2);
		pDC->LineTo(r1);

		pDC->MoveTo(r2);
		if (ar2.y > ar1.y)
		{
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y + int(doublemultiplier * (br1.y - r1.y - doubler)), r1.x, r1.y - int(doublemultiplier * (br1.y - r1.y - doubler)), r1.x, r1.y, br1.x, br1.y);
			pDC->LineTo(br1);
		}
		else
		{
			pDC->ArcTo(r0.x, r0.y + int(1 * (br1.y - r1.y - singular)), r1.x, r1.y - int(1 * (br1.y - r1.y - singular)), r1.x, r1.y, (r0.x + r1.x) / 2, br1.y);
			pDC->LineTo(br1);
		}
		pDC->MoveTo(r2);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y + int(doublemultiplier * (br2.y - r2.y - doubler)), r2.x, r2.y - int(doublemultiplier * (br2.y - r2.y - doubler)), r2.x, r2.y, br2.x, br2.y);
		pDC->LineTo(br2);
		pDC->LineTo(br1);

		pDC->MoveTo(ar3);
		pDC->ArcTo(r0.x - (r3.x - r0.x), r0.y - int(doublemultiplier * (r3.y - ar3.y - doubler)), r3.x, r3.y + int(doublemultiplier * (r3.y - ar3.y - doubler)), ar3.x, ar3.y, r3.x, r3.y);
		pDC->LineTo(r3);
		pDC->LineTo(r2);
		pDC->MoveTo(ar3);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - int(doublemultiplier * (r2.y - ar2.y - doubler)), r2.x, r2.y + int(doublemultiplier * (r2.y - ar2.y - doubler)), ar2.x, ar2.y, r2.x, r2.y);
		pDC->LineTo(r2);

		pDC->MoveTo(r3);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y + int(doublemultiplier * (br2.y - r2.y - doubler)), r2.x, r2.y - int(doublemultiplier * (br2.y - r2.y - doubler)), r2.x, r2.y, br2.x, br2.y);
		pDC->LineTo(br3);
		pDC->MoveTo(r3);
		pDC->ArcTo(r0.x - (r3.x - r0.x), r0.y + int(doublemultiplier * (br3.y - r3.y - doubler)), r3.x, r3.y - int(doublemultiplier * (br3.y - r3.y - doubler)), r3.x, r3.y, br3.x, br3.y);
		pDC->LineTo(br3);
	}
	else
	{
		if (r0.y > r1.y)
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - int(1 * (r1.y - ar1.y)), r1.x, r1.y + int(1 * (r1.y - ar1.y)), r1.x, r1.y, ar1.x, ar1.y);
			pDC->LineTo(r0);
		}
		else
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x, r0.y - int(1 * (r1.y - ar1.y)), r1.x, r1.y + int(1 * (r1.y - ar1.y)), r1.x, r1.y, r0.x, r0.y);
			pDC->LineTo(r0);
		}

		if (r0.y > r1.y)
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - int(1 * (br1.y - r1.y)), r1.x, r1.y + int(1 * (br1.y - r1.y)), br1.x, br1.y, r1.x, r1.y);
			pDC->LineTo(r1);
			pDC->LineTo(r0);
		}
		else
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x, r0.y - int(1 * (br1.y - r1.y)), r1.x, r1.y + int(1 * (br1.y - r1.y)), r0.x, r0.y, r1.x, r1.y);
			pDC->LineTo(r1);
			pDC->LineTo(r0);
		}

		pDC->MoveTo(r1);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - int(doublemultiplier * (r2.y - ar2.y - doubler)), r2.x, r2.y + int(doublemultiplier * (r2.y - ar2.y - doubler)), r2.x, r2.y, ar2.x, ar2.y);
		pDC->LineTo(ar2);
		pDC->LineTo(ar1);
		pDC->MoveTo(r1);
		if (r0.y > r1.y)
		{
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - int(1 * (r1.y - ar1.y)), r1.x, r1.y + int(1 * (r1.y - ar1.y)), r1.x, r1.y, ar1.x, ar1.y);
		}
		else
		{
			pDC->ArcTo(r0.x, r0.y - int(1 * (r1.y - ar1.y)), r1.x, r1.y + int(1 * (r1.y - ar1.y)), r1.x, r1.y, ar1.x, ar1.y);

		}
		pDC->LineTo(ar1);

		pDC->MoveTo(br1);
		pDC->LineTo(br2);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - int(doublemultiplier * (br2.y - r1.y - doubler)), r2.x, r2.y + int(doublemultiplier * (br2.y - r1.y - doubler)), br2.x, br2.y, r2.x, r2.y);
		pDC->LineTo(r2);
		pDC->LineTo(r1);
		pDC->MoveTo(br1);
		if (r0.y > r1.y)
		{
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - int(1 * (br1.y - r1.y)), r1.x, r1.y + int(1 * (br1.y - r1.y)), br1.x, br1.y, r1.x, r1.y);
		}
		else
		{
			pDC->ArcTo(r0.x, r0.y - int(1 * (br1.y - r1.y)), r1.x, r1.y + int(1 * (br1.y - r1.y)), br1.x, br1.y, r1.x, r1.y);
		}
		pDC->LineTo(r1);

		pDC->MoveTo(r3);
		pDC->ArcTo(r0.x - (r3.x - r0.x), r0.y - int(doublemultiplier * (r2.y - ar3.y - doubler)), r3.x, r3.y + int(doublemultiplier * (r2.y - ar3.y - doubler)), r3.x, r3.y, ar3.x, ar3.y);
		pDC->LineTo(ar2);
		pDC->MoveTo(r3);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - int(doublemultiplier * (r1.y - ar2.y - doubler)), r2.x, r2.y + int(doublemultiplier * (r1.y - ar2.y - doubler)), r2.x, r2.y, ar2.x, ar2.y);
		pDC->LineTo(ar2);

		pDC->MoveTo(br2);
		pDC->ArcTo(r0.x - (r3.x - r0.x), r0.y - int(doublemultiplier * (br3.y - r2.y - doubler)), r3.x, r3.y + int(doublemultiplier * (br3.y - r2.y - doubler)), br3.x, br3.y, r3.x, r3.y);
		pDC->LineTo(r3);
		pDC->MoveTo(br2);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - int(doublemultiplier * (br2.y - r1.y - doubler)), r2.x, r2.y + int(doublemultiplier * (br2.y - r1.y - doubler)), br2.x, br2.y, r2.x, r2.y);
		pDC->LineTo(r2);
		pDC->LineTo(r3);
	}
}

void HyperPlaneViewAngle::HyperPlaneViewAngular(CDC* pDC, int volume=1)
{
	CBrush brush(RGB(0, 0, 0));
	CBrush * oldBrush;
	CBrush * tmpBrush;

	oldBrush = pDC->SelectObject(&brush);
	tmpBrush = oldBrush;

	if (r0.x < r1.x)
	{
		CBrush 	brush1(RGB(75, 75, 75));
		tmpBrush = pDC->SelectObject(&brush1);
		pDC->BeginPath();
		pDC->MoveTo(r0);
		pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - 2*(r1.y - ar1.y - 6), r1.x, r1.y + 2*(r1.y - ar1.y - 6), ar1.x, ar1.y, r1.x, r1.y);
		pDC->MoveTo(r1);
		pDC->LineTo(r0);
		pDC->EndPath();
		pDC->FillPath();
		
		CBrush 	brush2(RGB(125, 125, 125));
		tmpBrush = pDC->SelectObject(&brush2);
		pDC->BeginPath();
		pDC->MoveTo(r0);
		pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y + 2*(br1.y - r1.y - 6), r1.x, r1.y - 2*(br1.y - r1.y - 6),  r1.x, r1.y, br1.x, br1.y);
		pDC->LineTo(r0);
		pDC->EndPath();
		pDC->FillPath();

		CBrush brush3(RGB(37, 37, 37));
		tmpBrush = pDC->SelectObject(&brush3);
		pDC->BeginPath();
		pDC->MoveTo(ar1);
		pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - 2*(r1.y - ar1.y - 6), r1.x, r1.y + 2*(r1.y - ar1.y - 6), ar1.x, ar1.y, r1.x, r1.y);
		pDC->LineTo(r1);
		pDC->MoveTo(ar1);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - 2*(r2.y - ar2.y - 6), r2.x, r2.y + 2*(r2.y - ar2.y - 6), ar2.x, ar2.y, r2.x, r2.y);
		pDC->LineTo(r2);
		pDC->LineTo(r1);
		pDC->EndPath();
		pDC->FillPath();

		CBrush brush4(RGB(188, 188, 188));
		tmpBrush = pDC->SelectObject(&brush4);
		pDC->BeginPath();
		pDC->MoveTo(r1);
		pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y + 2 * (br1.y - r1.y - 6), r1.x, r1.y - 2 * (br1.y - r1.y - 6), r1.x, r1.y, br1.x, br1.y);
		pDC->MoveTo(r1);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y + 2 * (br2.y - r2.y - 6), r2.x, r2.y - 2 * (br2.y - r2.y - 6), r2.x, r2.y, br2.x, br2.y);
		pDC->LineTo(br1);
		pDC->EndPath();
		pDC->FillPath();
		
		CBrush brush5(RGB(19, 19, 19));
		tmpBrush = pDC->SelectObject(&brush5);
		pDC->BeginPath();
		pDC->MoveTo(ar3);
		pDC->ArcTo(r0.x - (r3.x - r0.x), r0.y - 2 * (r3.y - ar3.y - 6), r3.x, r3.y + 2 * (r3.y - ar3.y - 6), ar3.x, ar3.y, r3.x, r3.y);
		pDC->LineTo(r2);
		pDC->MoveTo(ar3);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - 2 * (r2.y - ar2.y - 6), r2.x, r2.y + 2 * (r2.y - ar2.y - 6), ar2.x, ar2.y, r2.x, r2.y);
		pDC->LineTo(r2);
		pDC->EndPath();
		pDC->FillPath();
		
		CBrush brush6(RGB(220, 220, 220));
		tmpBrush = pDC->SelectObject(&brush6);
		pDC->BeginPath();
		pDC->MoveTo(r3);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y + 2 * (br2.y - r2.y - 6), r2.x, r2.y - 2 * (br2.y - r2.y - 6), r2.x, r2.y, br2.x, br2.y);
		pDC->LineTo(br3);
		pDC->MoveTo(r3);
		pDC->ArcTo(r0.x - (r3.x - r0.x), r0.y + 2 * (br3.y - r3.y - 6), r3.x, r3.y - 2 * (br3.y - r3.y - 6), r3.x, r3.y, br3.x, br3.y);
		pDC->LineTo(br3);
		pDC->EndPath();
		pDC->FillPath();
	}
	else
	{
		CBrush 	brush1(RGB(75, 75, 75));
		tmpBrush = pDC->SelectObject(&brush1);
		pDC->BeginPath();
		if (r0.y > r1.y)
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - 1 * (r1.y - ar1.y), r1.x, r1.y + 1 * (r1.y - ar1.y), r1.x, r1.y, ar1.x, ar1.y);
			pDC->LineTo(r0);
		}
		else
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x, r0.y - 1 * (r1.y - ar1.y), r1.x, r1.y + 1 * (r1.y - ar1.y), r1.x, r1.y, r0.x, r0.y);
			pDC->LineTo(r0);
		}
		pDC->EndPath();
		pDC->FillPath();

		CBrush 	brush2(RGB(125, 125, 125));
		tmpBrush = pDC->SelectObject(&brush2);
		pDC->BeginPath();

		if (r0.y > r1.y)
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - 1 * (br1.y - r1.y), r1.x, r1.y + 1 * (br1.y - r1.y), br1.x, br1.y, r1.x, r1.y);
			pDC->LineTo(r1);
			pDC->LineTo(r0);
		}
		else
		{
			pDC->MoveTo(r0);
			pDC->ArcTo(r0.x, r0.y - 1 * (br1.y - r1.y), r1.x, r1.y + 1 * (br1.y - r1.y), r0.x, r0.y, r1.x, r1.y);
			pDC->LineTo(r1);
			pDC->LineTo(r0);
		}
		pDC->EndPath();
		pDC->FillPath();

		CBrush 	brush3(RGB(37, 37, 37));
		tmpBrush = pDC->SelectObject(&brush3);
		pDC->BeginPath();
		pDC->MoveTo(r1);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - 2 * (r2.y - ar2.y - 6), r2.x, r2.y + 2 * (r2.y - ar2.y - 6), r2.x, r2.y, ar2.x, ar2.y);
		pDC->LineTo(ar2);
		pDC->LineTo(ar1);
		pDC->MoveTo(r1);
		if (r0.y > r1.y)
		{
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - 1 * (r1.y - ar1.y), r1.x, r1.y + 1 * (r1.y - ar1.y), r1.x, r1.y, ar1.x, ar1.y);
		}
		else
		{
			pDC->ArcTo(r0.x, r0.y - 1 * (r1.y - ar1.y), r1.x, r1.y + 1 * (r1.y - ar1.y), r1.x, r1.y, ar1.x, ar1.y);
		}
		pDC->LineTo(ar1);
		pDC->EndPath();
		pDC->FillPath();
		
		CBrush brush4(RGB(188, 188, 188));
		tmpBrush = pDC->SelectObject(&brush4);
		pDC->BeginPath();
		pDC->MoveTo(br1);
		pDC->LineTo(br2);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - 2*(br2.y - r1.y - 6), r2.x, r2.y + 2*(br2.y - r1.y - 6), br2.x, br2.y, r2.x, r2.y);
		pDC->LineTo(r2);
		pDC->LineTo(r1);
		pDC->MoveTo(br1);
		if (r0.y > r1.y)
		{
			pDC->ArcTo(r0.x - (r1.x - r0.x), r0.y - 1 * (br1.y - r1.y), r1.x, r1.y + 1 * (br1.y - r1.y), br1.x, br1.y, r1.x, r1.y);
		}
		else
		{
			pDC->ArcTo(r0.x, r0.y - 1 * (br1.y - r1.y), r1.x, r1.y + 1 * (br1.y - r1.y), br1.x, br1.y, r1.x, r1.y);
		}
		pDC->LineTo(r1);
		pDC->EndPath();
		pDC->FillPath();

		CBrush 	brush5(RGB(19, 19, 19));
		tmpBrush = pDC->SelectObject(&brush5);
		pDC->BeginPath();
		pDC->MoveTo(r3);
		pDC->ArcTo(r0.x - (r3.x - r0.x), r0.y - 2 * (r2.y - ar3.y - 6), r3.x, r3.y + 2 * (r2.y - ar3.y - 6), r3.x, r3.y, ar3.x, ar3.y);
		pDC->LineTo(ar2);
		pDC->MoveTo(r3);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - 2 * (r1.y - ar2.y - 6), r2.x, r2.y + 2 * (r1.y - ar2.y - 6), r2.x, r2.y, ar2.x, ar2.y);
		pDC->LineTo(ar2);
		pDC->EndPath();
		pDC->FillPath();
		
		CBrush 	brush6(RGB(220, 220, 220));
		tmpBrush = pDC->SelectObject(&brush6);
		pDC->BeginPath();
		pDC->MoveTo(br2);
		pDC->ArcTo(r0.x - (r3.x - r0.x), r0.y - 2 * (br3.y - r2.y - 6), r3.x, r3.y + 2 * (br3.y - r2.y - 6), br3.x, br3.y, r3.x, r3.y);
		pDC->LineTo(r3);
		pDC->MoveTo(br2);
		pDC->ArcTo(r0.x - (r2.x - r0.x), r0.y - 2 * (br2.y - r1.y - 6), r2.x, r2.y + 2 * (br2.y - r1.y - 6), br2.x, br2.y, r2.x, r2.y);
		pDC->LineTo(r2);
		pDC->LineTo(r3);
		pDC->EndPath();
		pDC->FillPath();
	}
	pDC->SelectObject(oldBrush);
}

void HyperPlaneViewAngle::HyperPlaneViewLinear(CDC* pDC)
{
	CBrush brush(RGB(0, 0, 0));
	CBrush * oldBrush;
	CBrush * tmpBrush;

	oldBrush = pDC->SelectObject(&brush);
	tmpBrush = oldBrush;

	CBrush brush1 (RGB(75, 75, 75));
	tmpBrush = pDC->SelectObject(&brush1);
	pDC->BeginPath();
	pDC->MoveTo(r0);
	pDC->LineTo(r1);
	pDC->LineTo(ar1);
	pDC->LineTo(r0);
	pDC->EndPath(); 
	pDC->FillPath();
	
	CBrush brush2(RGB(125, 125, 125));
	tmpBrush = pDC->SelectObject(&brush2);
	pDC->BeginPath();
	pDC->MoveTo(r0);
	pDC->LineTo(br1);
	pDC->LineTo(r1);
	pDC->EndPath(); 
	pDC->FillPath();
	
	CBrush brush3(RGB(37, 37, 37));
	tmpBrush = pDC->SelectObject(&brush3);
	pDC->BeginPath();
	pDC->MoveTo(r1);
	pDC->LineTo(r2);
	pDC->LineTo(ar2);
	pDC->LineTo(ar1);
	pDC->LineTo(r1);
	pDC->EndPath();
	pDC->FillPath();

	CBrush brush4(RGB(188, 188, 188));
	tmpBrush = pDC->SelectObject(&brush4);
	pDC->BeginPath();
	pDC->MoveTo(r1);
	pDC->LineTo(br1);
	pDC->LineTo(br2);
	pDC->LineTo(r2);
	pDC->LineTo(r1);
	pDC->EndPath();
	pDC->FillPath();
	
	CBrush brush5(RGB(19, 19, 19));
	tmpBrush = pDC->SelectObject(&brush5);
	pDC->BeginPath();
	pDC->MoveTo(r2);
	pDC->LineTo(r3);
	pDC->LineTo(ar3);
	pDC->LineTo(ar2);
	pDC->LineTo(r2);
	pDC->EndPath();
	pDC->FillPath();
	
	CBrush brush6(RGB(220, 220, 220));
	tmpBrush = pDC->SelectObject(&brush6);
	pDC->BeginPath();
	pDC->MoveTo(r2);
	pDC->LineTo(br2);
	pDC->LineTo(br3);
	pDC->LineTo(r3);
	pDC->LineTo(r2);
	pDC->EndPath();
	pDC->FillPath();

	pDC->SelectObject(oldBrush);
}

void HyperPlaneViewAngle::HyperPlaneViewLinear2(CDC* pDC, int line=1)
{
	pDC->MoveTo(r0);
	pDC->LineTo(r1);
	pDC->LineTo(ar1);
	pDC->LineTo(r0);

	pDC->MoveTo(r0);
	pDC->LineTo(br1);
	pDC->LineTo(r1);

	pDC->MoveTo(r1);
	pDC->LineTo(r2);
	pDC->LineTo(ar2);
	pDC->LineTo(ar1);
	pDC->LineTo(r1);

	pDC->MoveTo(r1);
	pDC->LineTo(br1);
	pDC->LineTo(br2);
	pDC->LineTo(r2);
	pDC->LineTo(r1);

	pDC->MoveTo(r2);
	pDC->LineTo(r3);
	pDC->LineTo(ar3);
	pDC->LineTo(ar2);
	pDC->LineTo(r2);

	pDC->MoveTo(r2);
	pDC->LineTo(br2);
	pDC->LineTo(br3);
	pDC->LineTo(r3);
	pDC->LineTo(r2);
}

void HyperPlaneViewAngle::HyperPlaneViewArc(CDC* pDC, CPoint _r0, CPoint _r1, CPoint _ar0)
{
	double radius1, aradius0;
	radius1 = sqrt((_r1.x - _r0.x) ^ 2 + (_r1.y - _r0.y) ^ 2);
	aradius0 = sqrt((_ar0.x - _r0.x) ^ 2 + (_ar0.y - _r0.y) ^ 2);

}

void HyperPlaneViewAngle::SetHyperPlaneViewLinear(CPoint _r0, CPoint _r1, CPoint _r2, CPoint _r3, CPoint _ar0, CPoint _ar1, CPoint _ar2, CPoint _ar3)
{
	r0 = _r0;
	r1 = _r0 + _r1;
	r2 = _r0 + _r2;
	r3 = _r0 + _r3;
	ar0 = br0 = _ar0;
	ar1 = br1 = _ar0 + _ar1;
	ar2 = br2 = _ar0 + _ar2;
	ar3 = br3 = _ar0 + _ar3;
	br1.y -= 2 *_ar1.y;
	br2.y -= 2 * _ar2.y;
	br3.y -= 2 * _ar3.y;
}

//**********************
// HyperPlaneViewAngle
