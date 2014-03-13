#pragma once
#include "effect.h"
#include "AR.h"
#include "FrameWrapper.h"

class CNoiseGate :
	public CEffect
{
public:
	CNoiseGate(void);
	virtual ~CNoiseGate(void);
	virtual void ProcessWet(double * frame);
private:
	double threshold;
	int hold;
	int window;
	CAR attackRelease;
	CFrameWrapper wrapper;
};

