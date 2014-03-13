#pragma once
#include "instrument.h"
#include <vector>
#include "AR.h"
#include "SineWave.h"
#include "audio/wave.h"
#include "audio/DirSoundStream.h"
#include "audio/DirSoundSource.h"
#include "audio/WaveformBuffer.h"

enum Types {electric, tom1, tom2, snare, bass, cymbal};

class CDrumInstrument :
	public CInstrument
{
public:
	CDrumInstrument(void);
	CDrumInstrument(double bpm);
	virtual ~CDrumInstrument(void);
	virtual void SetNote(CNote *note);
	virtual void Start();
    virtual bool Generate();
	void SetDuration(double duration) { m_duration = duration; }
	void SetFreq(double f) {m_sinewave.SetFreq(f); m_freq=f;}
private:
	double m_whiteNoise[44100];
	std::vector<double> m_queue;
	Types m_type;
	std::vector<double> m_tom1;
	std::vector<double> m_tom2;
	double m_cymbals[100000];
	double m_bass[100000];
	double m_snare[100000];
    double m_duration;
    double m_time;
	double m_bpm;
	double m_freq;
	bool m_attacked;
	CSineWave   m_sinewave;
	CAR m_ar;
	CDirSoundSource   m_wavein;
	int      m_numChannels;
    int      m_numSampleFrames;
	double m_clipSampleRate;
};

