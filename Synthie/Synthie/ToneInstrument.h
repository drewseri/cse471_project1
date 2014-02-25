#pragma once
#include "Instrument.h"
#include "SineWave.h"
class CToneInstrument :
	public CInstrument
{
public:
	CToneInstrument(void);
	virtual ~CToneInstrument(void);

	virtual void Start();
    virtual bool Generate();

    void SetFreq(double f) {m_sinewave.SetFreq(f);}
    void SetAmplitude(double a) {m_sinewave.SetAmplitude(a);}
    void SetDuration(double d) {m_duration = d;}

	void CToneInstrument::SetNote(CNote *note);

private:
    CSineWave   m_sinewave;
    double m_duration;
    double m_time;
};

