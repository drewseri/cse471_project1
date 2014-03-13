#pragma once
#include "circularqueueeffect.h"
class CReverb :
	public CCircularQueueEffect
{
public:
	CReverb(void);
	virtual ~CReverb(void);
	virtual void ProcessWet(double * frame);
};

