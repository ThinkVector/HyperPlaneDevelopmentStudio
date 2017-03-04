// HyperPlaneViewPort.cpp : implementation file
//

#include "stdafx.h"
#include "HyperPlane.h"
#include "HyperPlaneViewPort.h"


// HyperPlaneViewPort member functions
//************************************
HyperPlaneViewPort::HyperPlaneViewPort()
{
	MinInPort = 20;
	MinOutPort = 2;
	PortColor = RGB(20, 20, 20);
	PortOnValue = false;
	PortOutValue = false;
	SquareViewPort = CRect(MinOutPort, MinOutPort, MinInPort + MinOutPort, MinInPort + MinOutPort);
	SquareWidhtPort = SquareSurfacePort = SquareHeightPort = SquareRadiusPort = SquareLenghtPort = SquareAreaPort = SquareVolumePort = SquareCenterRectangle = SquareViewPort;
	SquareCenterPoint = SquareViewPort.CenterPoint();
}

HyperPlaneViewPort::HyperPlaneViewPort(CRect &_r)
{
	MinInPort = 20;
	MinOutPort = 2;
	PortColor = RGB(20, 20, 20);
	PortOnValue = false;
	PortOutValue = false;
}

HyperPlaneViewPort::~HyperPlaneViewPort()
{
}

void HyperPlaneViewPort::PortInitialize(CRect _viewrectangle)
{
	int _MinOutPort = MinOutPort + 1;
	SquareViewPort = SquareSurfacePort = _viewrectangle;
	SquareViewPort.DeflateRect(MinOutPort, MinOutPort);
	SquareCenterPoint = _viewrectangle.CenterPoint();
	SquareCenterRectangle.MoveToXY(SquareCenterPoint);

	SquareWidhtPort = CRect(SquareViewPort.TopLeft().x + _MinOutPort, SquareCenterRectangle.TopLeft().y, SquareCenterRectangle.TopLeft().x - MinOutPort, SquareCenterRectangle.BottomRight().y);
	SquareRadiusPort = CRect(SquareViewPort.BottomRight().x - _MinOutPort, SquareCenterRectangle.BottomRight().y, SquareCenterRectangle.BottomRight().x + MinOutPort, SquareCenterRectangle.TopLeft().y);
	SquareLenghtPort = CRect(SquareCenterRectangle.TopLeft().x, SquareViewPort.TopLeft().y + _MinOutPort, SquareCenterRectangle.BottomRight().x, SquareCenterRectangle.TopLeft().y - MinOutPort);
	SquareHeightPort = CRect(SquareCenterRectangle.TopLeft().x, SquareCenterRectangle.BottomRight().y + MinOutPort, SquareCenterRectangle.BottomRight().x, SquareViewPort.BottomRight().y - _MinOutPort);

	SquareAreaPort = SquareVolumePort = SquareViewPort;
	SquareSurfacePort.DeflateRect(-1, -1);
	SquareAreaPort.DeflateRect(1, 1);
	SquareVolumePort.DeflateRect(2, 2);

}

void HyperPlaneViewPort::Draw(CDC* pDC)
{
	if (PortOnValue)
	{
		pDC->Rectangle(SquareSurfacePort);
		pDC->Rectangle(SquareViewPort);
		pDC->Rectangle(SquareAreaPort);
		pDC->Rectangle(SquareVolumePort);
		pDC->Rectangle(SquareCenterRectangle);
		pDC->Rectangle(SquareWidhtPort);
		pDC->Rectangle(SquareRadiusPort);
		pDC->Rectangle(SquareLenghtPort);
		pDC->Rectangle(SquareHeightPort);
	}
}

void HyperPlaneViewPort::PortOn(BOOL _PortOn)
{
	if (_PortOn)
	{
		PortOnValue = true;
	}
	else
	{
		PortOnValue = false;
	}
}

//************************************
// HyperPlaneViewPort member functions