#include "StdAfx.h"
#include "Instrument.h"


CInstrument::CInstrument(void)
{
	for (int i = 0; i <= NUM_EFFECTS_BUILD; i++){
		sends[i] = (i == 0) ? 1.0 : 0.0; //Default dry channel to full and all effects channels to mute
	}
}


CInstrument::~CInstrument(void)
{
}

void CInstrument::SetSend(int send, double value){
	if (send > NUM_EFFECTS_BUILD) {
		//index out of range. TODO: Should throw exception if time permits.
		return;
	}
	sends[send] = value;
}
double CInstrument::GetSend(int send){
	if (send > NUM_EFFECTS_BUILD) {
		//index out of range. TODO: Should throw exception if time permits.
		return 0.0;
	}
	return sends[send];
}