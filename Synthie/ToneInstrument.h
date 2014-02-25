#pragma once
#include "instrument.h"
#include "SineWave.h"
#include "AR.h"

class CToneInstrument :
	public CInstrument
{
public:
	CToneInstrument(void);
	CToneInstrument(double bpm);
	virtual ~CToneInstrument(void);
    virtual void Start();
    virtual bool Generate();

    void SetFreq(double f) {m_sinewave.SetFreq(f);}
    void SetAmplitude(double a) {m_sinewave.SetAmplitude(a);}
    void SetDuration(double d) {m_duration = d;}
	virtual void SetNote(CNote *note);

private:
    CSineWave   m_sinewave;
    double m_duration;
    double m_time;
	double m_bpm;
	CAR         m_ar;

};

