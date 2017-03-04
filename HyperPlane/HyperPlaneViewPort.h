#pragma once

// HyperPlaneViewPort command target

class HyperPlaneViewPort : public CObject
{
public:
	HyperPlaneViewPort();
	HyperPlaneViewPort(CRect &_r);
	virtual ~HyperPlaneViewPort();
	virtual void Draw(CDC* pDC);
	void PortInitialize(CRect _viewrectangle);
	void PortOn(BOOL _PortOnValue);

public:
	COLORREF PortColor;
	CRect SquareSurfacePort;
	CRect SquareViewPort;
	CRect SquareWidhtPort;
	CRect SquareHeightPort;
	CRect SquareRadiusPort;
	CRect SquareLenghtPort;
	CRect SquareAreaPort;
	CRect SquareVolumePort;
	CRect SquareCenterRectangle;
	CPoint SquareCenterPoint;
	int MinInPort;
	int MinOutPort;
	BOOL PortOnValue;
	BOOL PortOutValue; //Server viewport out connection close.
};


