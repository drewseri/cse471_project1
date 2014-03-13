#pragma once
#include "audionode.h"
class CFrameWrapper :
	public CAudioNode
{
public:
	CFrameWrapper();
	virtual ~CFrameWrapper(void);
	virtual void Start() { }
	virtual bool Generate() { return true; }
	void setFrame(double * frameIn);
};

