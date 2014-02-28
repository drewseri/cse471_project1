#pragma once
#include "instrument.h"
#include "SineWave.h"
#include <string>
#include <vector>

class COrgan :
public CInstrument
{
	public:
		COrgan(void);
		COrgan(double);
		virtual ~COrgan(void);

		virtual void Start();
		virtual bool Generate();

		void SetFreq(double f) {m_sinewave.SetFreq(f);}
	    void SetAmplitude(double a) {m_sinewave.SetAmplitude(a);}
	    void SetDuration(double d) {m_duration = d;}
		void SetDrawBar(WCHAR * setting);
		virtual void SetNote(CNote *note);

	private:
	   CSineWave   m_sinewave;
	   void AR(double*);
	   double m_duration;
	   double m_time;
	   double m_bpm;
	   double m_freq;
	   std::vector<char> m_drawbar;
};