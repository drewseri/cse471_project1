#include "StdAfx.h"
#include "NoiseGate.h"


CNoiseGate::CNoiseGate(void)
{
	attackRelease.SetSource(wrapper);
	attackRelease.Start();
	threshold = 0.05;
	hold = 441;
	window = 0;
}


CNoiseGate::~CNoiseGate(void)
{
}

void CNoiseGate::ProcessWet(double * frame){
	for (int i = 0; i < 2; i++){
		if (frame[i] > 0.0 && frame[i] < threshold) {
			window++;
			if (window > hold) {
				frame[i] = 0;
			}
		} else if (frame[i] < 0.0 && frame[i] > (-1.0*threshold)) {
			if (window > hold) {
				frame[i] = 0;
			}
		} else {
			window = 0;
		}
		//frame[i] = (frame[i] > threshold || (-1.0*frame[i]) > threshold) ? frame[i] : 0;
	}
	wrapper.setFrame(frame);
	if (attackRelease.Generate()){
		frame[0] = attackRelease.Frame()[0];
		frame[1] = attackRelease.Frame()[1];
	}
}