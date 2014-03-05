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

		void SetFreq(double f) {m_freq = f;}
	    void SetDuration(double d) {m_duration = d;}
		void SetToneWheels(WCHAR * setting);
		virtual void SetNote(CNote *note);

	private:
	   void AR(double*);
	   double m_duration;
	   double m_time;
	   double m_bpm;
	   double m_freq;
	   double m_amp;
	   std::vector<char> m_tonewheels;
	   std::vector<double> m_rad1;
	   std::vector<double> m_rad2;
};