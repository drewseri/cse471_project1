#include "StdAfx.h"
#include "FrameWrapper.h"


CFrameWrapper::CFrameWrapper()
{
	m_frame[0] = 0;
	m_frame[1] = 0;
}

CFrameWrapper::~CFrameWrapper(void)
{
}

void CFrameWrapper::setFrame(double * frameIn){
	m_frame[0] = frameIn[0];
	m_frame[1] = frameIn[1];
}