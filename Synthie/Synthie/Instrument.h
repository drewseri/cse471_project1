#pragma once
#include "AudioNode.h"
#include "Note.h"

class CSynthesizer;

class CInstrument :
	public CAudioNode
{
public:
	CInstrument(void);
	virtual ~CInstrument(void);
	virtual void SetNote(CNote *note) = 0;
};

