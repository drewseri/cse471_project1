#include "StdAfx.h"
#include "Reverb.h"


CReverb::CReverb(void)
{
	inQueue.resize(88200);
	outQueue.resize(88200);
}


CReverb::~CReverb(void)
{
}

void CReverb::ProcessWet(double * frame){
	for (int i = 0; i < 2; i++){
		inQueue[(wrloc+i)%88200] = frame[i];
	}
	for (int i = 0; i < 2; i++){
		frame[i] += 1*inQueue[(wrloc+i+int(88.2 * 100))%88200] + 0.5*inQueue[(wrloc+i+int(88.2 * 200))%88200] + 0.25*inQueue[(wrloc+i+int(88.2 * 400))%88200] + 0.125*inQueue[(wrloc+i+int(88.2 * 800))%88200];
		frame[i] /= 2.75;
	}
	for (int i = 0; i < 2; i++){
		outQueue[(wrloc+i)/88200] = frame[i];
	}
	wrloc += 2;
	wrloc %= 88200;
}
