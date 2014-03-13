#pragma once
#include "effect.h"
#include <vector>
#include "resource.h"
class CCircularQueueEffect :
	public CEffect
{
public:
	CCircularQueueEffect(void);
	virtual ~CCircularQueueEffect(void);
	//virtual void ProcessWet(double * frame)=0;
protected:
	std::vector<double> inQueue;
	std::vector<double> outQueue;
	int wrloc;
};