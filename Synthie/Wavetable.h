#pragma once
#include "SineWave.h"
#include <vector>
#include <string>
#include "StdAfx.h"
#include "Organ.h"
#include "Notes.h"

#include "audio/wave.h"
#include "audio/DirSoundStream.h"
#include "audio/DirSoundSource.h"
#include "audio/WaveformBuffer.h"

using namespace std;
class CWavetable :
	public CInstrument
{
public:
	CWavetable(void);
	CWavetable(double);
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) {_freq = f;}
	void SetDuration(double d) {_duration = d;}
	void SetToneWheels(WCHAR * setting);
	virtual void SetNote(CNote *note);
	~CWavetable(void);
private:
	double _bpm;
	double _duration;
	double _freq;
	double _time;
	CDirSoundSource   _wave;
	double _waveSampleRate1;
	double _waveNumChannels1;
	double _waveNumFrames1;
	double _waveSampleRate2;
	double _waveNumChannels2;
	double _waveNumFrames2;
	vector<short> _waveFrames1L;
	vector<short> _waveFrames1R;
	vector<short> _waveFrames2L;
	vector<short> _waveFrames2R;
	int _currFrame;
	bool _file2;
	bool _sustain;
	bool _sustainStarted;
};

