#pragma once

// HyperPlaneViewAngle command target

class HyperPlaneViewAngle : public CObject
{
public:
	HyperPlaneViewAngle();
	HyperPlaneViewAngle(CPoint _r0, CPoint _r1, CPoint _r2, CPoint _r3, CPoint _ar0, CPoint _ar1, CPoint _ar2, CPoint _ar3, CPoint _br0, CPoint _br1, CPoint _br2, CPoint _br3);
	HyperPlaneViewAngle& operator= (const HyperPlaneViewAngle& _other); // copy-assignment
	HyperPlaneViewAngle(CPoint _single) : r0(_single), r1(_single), r2(_single), r3(_single),
		ar0(_single), ar1(_single), ar2(_single), ar3(_single),
		br0(_single), br1(_single), br2(_single), br3(_single) {}

	virtual ~HyperPlaneViewAngle();
	virtual void HyperPlaneViewAngular(CDC* pDC, int volume);
	virtual void HyperPlaneViewAngular2(CDC* pDC, int line);
	virtual void HyperPlaneViewLinear(CDC* pDC);
	virtual void HyperPlaneViewLinear2(CDC* pDC, int line);
	virtual void HyperPlaneViewArc(CDC* pDC, CPoint _r0, CPoint _r1, CPoint _ar0);
	void SetHyperPlaneViewLinear(CPoint _r0, CPoint _r1, CPoint _r2, CPoint _r3, CPoint _ar0, CPoint _ar1, CPoint _ar2, CPoint _ar3);
	void ChangeCenter(CPoint _r);
	
	
	
public:
	CPoint r0, r1, r2, r3;
	CPoint ar0, ar1, ar2, ar3;
	CPoint br0, br1, br2, br3;

//operators
public:
	//HyperPlaneViewAngle& operator= (const HyperPlaneViewAngle& other); // copy-assignment
	//HyperPlaneViewAngle& operator= (HyperPlaneViewAngle&&);  // move-assignment
	//HyperPlaneViewAngle(const HyperPlaneViewAngle& other) = delete;
};


