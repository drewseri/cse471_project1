#include "StdAfx.h"
#include "OctaveUp.h"


COctaveUp::COctaveUp(void)
{
}


COctaveUp::~COctaveUp(void)
{
}

void COctaveUp::ProcessWet(double * frame){
	for (int i = 0; i < 2; i++){
		frame[i] = (frame[i] < 0) ? -1*frame[i] : frame[i];
	}
}