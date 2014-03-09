#include "StdAfx.h"
#include "EffectFactory.h"
#include <algorithm>


EffectFactory::EffectFactory(void)
{
	currentEffect = 0;
}


EffectFactory::~EffectFactory(void)
{
}

void EffectFactory::nextEffect() {
	if (m_effectNotes.size() > 0) {
		m_activeEffects[m_effectNotes[currentEffect].Instrument()] = m_effectNotes[currentEffect];
	}
}

void EffectFactory::fitEffects(CInstrument * instrument, const std::wstring & instrumentName) {
	if (m_activeEffects.find(instrumentName)==m_activeEffects.end()) {
		return;
	}
	CNote effectNote = m_activeEffects[instrumentName];
	for (int i = 0; i <= NUM_EFFECTS_BUILD; i++) {
		instrument->SetSend(i,effectNote.GetSend(i));
	}
}

void EffectFactory::start() {
	std::sort(m_effectNotes.begin(), m_effectNotes.end());
}

void EffectFactory::clear() {
	m_effectNotes.clear();
	m_activeEffects.clear();
	currentEffect = 0;
}