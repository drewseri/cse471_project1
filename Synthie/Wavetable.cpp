#include "StdAfx.h"
#include "Wavetable.h"


CWavetable::CWavetable(void) {
	_duration=0.1;
	_bpm=120;
}
CWavetable::CWavetable(double bpm) {
	_duration=0.1;
	_time=0;
	_bpm=bpm;
	_file2=false;
	_sustain=false;
	_sustainStarted=false;
	_waveSampleRate1=0;
	_waveNumChannels1=0;
	_waveNumFrames1=0;
	_waveSampleRate2=0;
	_waveNumChannels2=0;
	_waveNumFrames2=0;
}

CWavetable::~CWavetable(void)
{
}
bool CWavetable::Generate() {
	if (_file2) {
		
		if (!_sustain) {
			//cross-fading
			m_frame[0] = _waveFrames1L[_currFrame]*((_duration-_time)/_duration);
			m_frame[0] += _waveFrames2L[_currFrame]*(_time/_duration);
			m_frame[1] = _waveFrames1R[_currFrame]*((_duration-_time)/_duration);
			m_frame[1] += _waveFrames2R[_currFrame]*(_time/_duration);
		} else {
			//loop points;
			if (!_sustainStarted) {
				if (_currFrame<_waveFrames1L.size()-1) {
					m_frame[0] = _waveFrames1L[_currFrame];
					m_frame[1] = _waveFrames1R[_currFrame];
				} else if  (_currFrame>=_waveFrames1L.size()-1)  {
			
					m_frame[0] = _waveFrames1L[_currFrame];
					m_frame[1] = _waveFrames1R[_currFrame];
					_sustainStarted=true;
					_currFrame=0;
				}
			} else {
				m_frame[0] = _waveFrames2L[_currFrame];
				m_frame[1] = _waveFrames2R[_currFrame];
			}
		}
	} else {
		
		m_frame[0] = _waveFrames1L[_currFrame];
		m_frame[1] = _waveFrames1R[_currFrame];
	}
	//Envelope generation
	if (_time>=_duration-_duration*0.05) {
		m_frame[0]*=(_duration-_time)/(_duration*0.05);
		m_frame[1]*=(_duration-_time)/(_duration*0.05);
	}
	_currFrame++;
	if (_sustainStarted) {
		if (_currFrame >= _waveFrames2L.size())
			_currFrame=0;
	}
	_time+= GetSamplePeriod();
	bool result=_time<_duration;
	if (!_sustain) {
		result &= _currFrame<min(_waveNumFrames1,_waveNumFrames2);
	}
	m_frame[0] = (double)m_frame[0]/32676;
	m_frame[1] = (double)m_frame[1]/32676;
	return result;
}

void CWavetable::Start() {
	_currFrame=0;
}


void CWavetable::SetNote(CNote *note) {
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);
	short frame[2];
	for (int i=0;i<len;i++) {
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);
	  
		if (name=="file") {
			_wave.Open(value.bstrVal);
			_waveSampleRate1 = _wave.SampleRate();
			_waveNumChannels1 = _wave.NumChannels();
			_waveNumFrames1   = _wave.NumSampleFrames();
			for (int i=0;i<_waveNumFrames1;i++) {
				_wave.ReadFrame(frame);
				_waveFrames1L.push_back(frame[0]);
				_waveFrames1R.push_back(frame[1]);
			}
			_wave.Close();
		} else if (name=="file2") {
			_file2=true;
			_wave.Open(value.bstrVal);
			_waveSampleRate2 = _wave.SampleRate();
			_waveNumChannels2 = _wave.NumChannels();
			_waveNumFrames2   = _wave.NumSampleFrames();
			for (int i=0;i<_waveNumFrames2;i++) {
				_wave.ReadFrame(frame);
				_waveFrames2L.push_back(frame[0]);
				_waveFrames2R.push_back(frame[1]);
			}
			_wave.Close();
		} else if (name=="sustain") {
			_sustain=true;
		}else if (name=="duration") {
			value.ChangeType(VT_R8);
			_duration=value.dblVal;
		}
	}
}