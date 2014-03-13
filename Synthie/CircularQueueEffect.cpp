#include "StdAfx.h"
#include "CircularQueueEffect.h"
#include "resource.h"


CCircularQueueEffect::CCircularQueueEffect(void)
{
	inQueue.resize(QUEUESIZE);
	outQueue.resize(QUEUESIZE);
	wrloc = 0;
}


CCircularQueueEffect::~CCircularQueueEffect(void)
{
}
