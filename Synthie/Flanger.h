#pragma once
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "circularqueueeffect.h"

/*
Flanger effect as described in exam part B problem 1
*/

class CFlanger :
	public CCircularQueueEffect
{
public:
	CFlanger(void);
	virtual ~CFlanger(void);
	virtual void ProcessWet(double * frame);
private:
	double phaseAngle;
};

