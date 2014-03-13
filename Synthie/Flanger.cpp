#include "StdAfx.h"
#include "Flanger.h"

CFlanger::CFlanger(void)
{
	phaseAngle = 0;
}


CFlanger::~CFlanger(void)
{
}

void CFlanger::ProcessWet(double * frame){
	for (int i = 0; i < 2; i++){
		inQueue[(wrloc+i)%QUEUESIZE] = frame[i];
	}
	int delaySize = int(88.2*(6 + 4 * sin(phaseAngle)));
	int otherDelaySize = int(88.2*(10 + 8 * cos(phaseAngle)));
	phaseAngle += 2*M_PI*1/44100;
	for (int i = 0; i < 2; i++){
		frame[i] += inQueue[(wrloc+i+delaySize)%QUEUESIZE]*(0.75+0.25*sin(phaseAngle*2));
		frame[i] += inQueue[(wrloc+i+otherDelaySize)%QUEUESIZE]*(0.75+0.25*sin(2*phaseAngle*2));
		frame[i] /= 3;
	}
	for (int i = 0; i < 2; i++){
		outQueue[(wrloc+i)/QUEUESIZE] = frame[i];
	}
	wrloc += 2;
	wrloc %= QUEUESIZE;
}