#pragma once
#include "instrument.h"
#include <vector>
#include "SineWave.h"

class CAdditive :
	public CInstrument
{
public:
	CAdditive(void);
	CAdditive(double bpm);
	~CAdditive(void);

	virtual void Start();
	virtual bool Generate();

	//virtual void SetNote(CNote *note);

	void AR(double * frame);

	void SetNote(CNote *note);

	void AddHarmonic1(double har) {m_harmonics1.push_back(har);}
	void AddHarmonic2(double har) {m_harmonics2.push_back(har);}

	void SetFreq(double freq) {m_freq = freq;}

	void SetBPM(double bpm) {m_bpm = bpm;}
	double GetBPM() {return m_bpm;}

	void SetDuration(double dur) {m_duration = dur;}
	double GetDuration() {return m_duration;}

	void SetTime(double time) {m_time = time;}
	double GetTime() {return m_time;}

	void SetHarmonic(WCHAR *harms, std::vector<double> &harmonics);
	


private:

	CSineWave   m_sinewave;
	CSineWave	m_sinewave2;

    double m_duration;
    double m_time;
	double m_bpm;
	double m_freq;

	double m_depth;

	std::vector<double> m_harmonics1;
	std::vector<double> m_harmonics2;

	std::vector<double> m_rad1;
	std::vector<double> m_rad2;

	
};

