#pragma once

// HyperPlaneViewAngle command target

class HyperPlaneViewAngle : public CObject
{
public:
	HyperPlaneViewAngle();
	virtual ~HyperPlaneViewAngle();
	virtual void HyperPlaneViewAngular(CDC* pDC, int volume);
	virtual void HyperPlaneViewAngular2(CDC* pDC, int line);
	virtual void HyperPlaneViewLinear(CDC* pDC);
	virtual void HyperPlaneViewLinear2(CDC* pDC, int line);
	void SetHyperPlaneViewLinear(CPoint _r0, CPoint _r1, CPoint _r2, CPoint _r3, CPoint _ar0, CPoint _ar1, CPoint _ar2, CPoint _ar3);
public:
	CPoint r0, r1, r2, r3;
	CPoint ar0, ar1, ar2, ar3;
	CPoint br0, br1, br2, br3;
};


