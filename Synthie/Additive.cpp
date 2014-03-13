#include "StdAfx.h"
#include "Additive.h"
#include "Notes.h"


CAdditive::CAdditive(void)
{
	m_freq = 440;
	m_depth = .1;
	m_duration = 0.1;
	m_bpm = 120;
}

CAdditive::CAdditive(double bpm)
{
	m_freq = 440;
	m_depth = .1;
	m_duration = 0.1;
	m_bpm = bpm;
}


CAdditive::~CAdditive(void)
{
}

void CAdditive::Start(void)
{
	m_sinewave.SetSampleRate(GetSampleRate());
    m_sinewave.Start();
	m_sinewave2.SetSampleRate(GetSampleRate());
	m_sinewave2.Start();
    m_time = 0;
	

	// Tell the AR object it gets its samples from 
    // the sine wave object.
   
}

bool CAdditive::Generate(void)
{
	m_sinewave.Generate();
	m_sinewave2.Generate();
	double timeRatio = m_time/m_duration;
	double bRatio = 1-timeRatio;
	double newFreq = m_freq * (1 +(m_depth * sin(2*3.14*m_time)));
	m_frame[0] = 0;
	m_frame[1] = 0;

	for(int i = 0; i < m_harmonics1.size(); i++)
	{
		if(i < m_harmonics2.size())
		{
			
			m_frame[0] += (bRatio*m_harmonics1[i]/(i+1) * sin(m_rad1[i])) + (timeRatio*m_harmonics2[i]/(i+1)*sin(m_rad1[i]));
			m_frame[1] = m_frame[0];
			// calculate diff for vibrato
			double diff = m_freq * (0.2 *sin(m_rad2[i]));

			// increment phases
			m_rad1[i] += (2 * PI * (m_freq + diff)*(i+1)) / GetSampleRate();
			m_rad2[i] += (2 * PI * m_freq*(i+1)) / GetSampleRate();
			
			
		}

		else if( i > m_harmonics2.size())
		{
			m_frame[0] += (m_harmonics1[i]/(i+1) * sin(m_rad1[i]));
			m_frame[1] = m_frame[0];
			// calculate diff for vibrato
			double diff = m_freq * (0.2 *sin(m_rad2[i]));

			// increment phases
			m_rad1[i] += (2 * PI * (m_freq + diff)*(i+1)) / GetSampleRate();
			m_rad2[i] += (2 * PI * m_freq*(i+1)) / GetSampleRate();
		}

		
	}

	
	

	AR(m_frame);

	m_time += GetSamplePeriod();

	//m_frame[0] = m_sinewave.Frame(0);
	//m_frame[1] = m_sinewave.Frame(1);
	return m_time*m_bpm/60 < m_duration;
}

void CAdditive::AR(double * frame)
{
	if(m_time < 0.05)
	{
		frame[0] = frame[0] * (m_time/0.05);
		frame[1] = frame[1] * (m_time/0.05);
	}

	else if( m_duration - m_time < 0.05)
	{
		frame[0] = frame[0] * (m_duration-m_time)/0.05;
		frame[1] = frame[1] * (m_duration-m_time)/0.05;
	}
}

void CAdditive::SetHarmonic(WCHAR *harms, std::vector<double> &harmonics)
{
	//harmonics.resize(8);
	int num = wcslen(harms);
	char prev = ' ';
	for(int i = 0; i < num; i++)
	{
		char a = harms[i];
		if(prev == '.' && isdigit(a))
		{
			double value = atof(&a);
			value = value/10;
			harmonics.push_back(value);
		}
		else if(isdigit(a))
		{
			double value = atof(&a);
			harmonics.push_back(value);
		}
		prev = a;
	}
}

void CAdditive::SetNote(CNote *note)
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
       }
		else if(name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if(name == "harmonic1")
		{
			SetHarmonic(value.bstrVal,m_harmonics1);
			m_rad1.resize(m_harmonics1.size());
			m_rad2.resize(m_harmonics1.size());
		}
		else if(name == "harmonic2")
		{
			SetHarmonic(value.bstrVal, m_harmonics2);
		}
		
		

   }
}