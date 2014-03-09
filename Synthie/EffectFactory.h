#pragma once
#include<vector>
#include<map>
#include"Note.h"
#include"Instrument.h"
class EffectFactory
{
public:
	EffectFactory(void);
	virtual ~EffectFactory(void);
	void fitEffects(CInstrument * instrument, const std::wstring & instrumentName);
	void addEffectNode(CNote & note) { m_effectNotes.push_back(note); }
	void nextEffect();
	void start();
	void clear();
private:
	std::vector<CNote> m_effectNotes;
	std::map<const std::wstring, CNote> m_activeEffects;
	int currentEffect;
};

