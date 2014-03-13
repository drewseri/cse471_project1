#include "StdAfx.h"
#include "DrumInstrument.h"
#include "Notes.h"
#include <math.h>
#include <random>

CDrumInstrument::CDrumInstrument(double bpm) : m_freq(500)
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0,.02);
	int i = 0;
	m_queue.resize(100000);

	m_sinewave.SetSampleRate(GetSampleRate());
    m_sinewave.Start();
	m_sinewave.SetAmplitude(.3);
	m_attacked = false;

	m_wavein.Open("audio/tom1.wav");
	m_clipSampleRate = m_wavein.SampleRate();
	m_numChannels = m_wavein.NumChannels();
	m_numSampleFrames = m_wavein.NumSampleFrames();
	for(int i = 0; i < m_numSampleFrames/m_numChannels; i++)
	{
		short frame[2];
		
		m_wavein.ReadFrame(frame);
		double doubleFrame = (double)frame[0]/32767;
		m_tom1.push_back(doubleFrame);
	}
	m_wavein.Close();
	while(i<44100)
	{
		double number = distribution(generator);
		if(number<=1.0 && number>=-1.0) 
		{
			m_whiteNoise[i] = number;
			i++;
		}
	}
	m_bpm = bpm;
}

CDrumInstrument::CDrumInstrument(void) : m_freq(500)
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0,.1);
	int i = 0;
	m_queue.resize(100000);
	
	m_sinewave.SetSampleRate(GetSampleRate());
    m_sinewave.Start();
	m_sinewave.SetAmplitude(.3);
	m_attacked=false;



	m_wavein.Open("audio/tom1.wav");
	m_clipSampleRate = m_wavein.SampleRate();
	m_numChannels = m_wavein.NumChannels();
	m_numSampleFrames = m_wavein.NumSampleFrames();
	for(int i = 0; i < m_numSampleFrames/m_numChannels; i++)
	{
		short *frame; 
		m_wavein.ReadFrame(frame);
		double doubleFrame = (double)frame[0]/32767;
		m_tom1.push_back(doubleFrame);
	}

	while(i<44100)
	{
		double number = distribution(generator);
		if(number<=1.0 && number>=-1.0) 
		{
			m_whiteNoise[i] = number;
			i++;
		}
	}
	
}


CDrumInstrument::~CDrumInstrument(void)
{
}

void CDrumInstrument::SetNote(CNote *note) 
{
	// Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for(int i=0;  i<len;  i++)
    {
		// Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);
		
		// Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if(name == "duration")
        {
            value.ChangeType(VT_R8);
            SetDuration(value.dblVal);
        } else if(name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        } else if(name == "type")
		{
			if((char*)value.bstrVal == "electric")
				m_type = electric;
			else if((char*)value.bstrVal == "tom1")
				m_type = tom1;
		}
	}
	return;
}

void CDrumInstrument::Start(void) 
{
	m_time= 0;
	return;
}

bool CDrumInstrument::Generate(void)
{
	//if(m_type = electric)
	//{

		int frame = (int)( m_time*GetSampleRate())%44100;
		double r = .995;
		double cosine = (2*r*cos(2*3.14159*(300))/(1+pow(r,2)));
		double a = (1-pow(r,2))*sin(acos(cosine));
		double amplitude = 1;
		if(m_time<.05) {
			amplitude = 20*m_time;
		}
		

		m_sinewave.Generate();
		if(frame >=2){

			m_frame[0]=amplitude*(a*(m_whiteNoise[frame] + m_sinewave.Frame(0)) + 2*r*cosine*m_queue[(frame-1)%m_queue.size()] - pow(r,2)*m_queue[(frame-2)%m_queue.size()]);
			//m_frame[0]= m_whiteNoise[frame];
			
		}
		else
		{
			m_frame[0]=amplitude*(m_whiteNoise[frame] + m_sinewave.Frame(0));

		}
		m_frame[1]=m_frame[0];
		m_queue[frame] = m_frame[0];

		m_sinewave.SetFreq(m_sinewave.GetFreq() - 1/GetSampleRate()*m_sinewave.GetFreq());
		m_time += 1/GetSampleRate();
		return m_time*m_bpm/60 < m_duration;
	/*}
	else if(m_type = tom1)
	{
		int frame = (int)( m_time*GetSampleRate());
		m_frame[0] = m_tom1[frame];
		m_frame[1] = m_frame[0];
		m_time += 1/GetSampleRate();
		return frame < m_tom1.size() - 2 ;
	}*/
	return false;
}

