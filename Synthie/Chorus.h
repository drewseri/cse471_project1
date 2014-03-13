#pragma once
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "circularqueueeffect.h"

/*
A modified version of chorus as described in exam part B, problem 1.
*/

class CChorus :
	public CCircularQueueEffect
{
public:
	CChorus(void);
	virtual ~CChorus(void);
	virtual void ProcessWet(double * frame);
private:
	double phaseAngle;
};

