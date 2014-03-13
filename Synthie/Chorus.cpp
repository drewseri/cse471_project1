#include "StdAfx.h"
#include "Chorus.h"


CChorus::CChorus(void)
{
	phaseAngle = 0;
}


CChorus::~CChorus(void)
{
}

void CChorus::ProcessWet(double * frame){
	for (int i = 0; i < 2; i++){
		inQueue[(wrloc+i)%QUEUESIZE] = frame[i];
	}
	int delaySize = int(88.2*(25 + 2 * sin(phaseAngle)));
	phaseAngle += 2*M_PI*2/44100;
	for (int i = 0; i < 2; i++){
		frame[i] += inQueue[(wrloc+i+delaySize)%QUEUESIZE];
		frame[i] /= 2;
	}
	for (int i = 0; i < 2; i++){
		outQueue[(wrloc+i)/QUEUESIZE] = frame[i];
	}
	wrloc += 2;
	wrloc %= QUEUESIZE;
}