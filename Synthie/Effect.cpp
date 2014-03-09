#include "StdAfx.h"
#include "Effect.h"


CEffect::CEffect(void)
{
	wet = 1.0;
	dry = 0.0;
}


CEffect::~CEffect(void)
{
}

void CEffect::Process(double * frame) {
	double * dryFrame = new double[2];
	double * wetFrame = new double[2];
	dryFrame[0] = frame[0];
	wetFrame[0] = frame[0];
	dryFrame[1] = frame[1];
	wetFrame[1] = frame[1];
	ProcessWet(wetFrame);
	frame[0] = dry*dryFrame[0] + wet*wetFrame[0];
	frame[1] = dry*dryFrame[1] + wet*wetFrame[1];
	delete dryFrame;
	delete wetFrame;
}