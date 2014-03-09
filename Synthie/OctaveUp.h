#pragma once
#include "effect.h"
class COctaveUp :
	public CEffect
{
public:
	COctaveUp(void);
	virtual ~COctaveUp(void);
	virtual void ProcessWet(double * frame);
};

