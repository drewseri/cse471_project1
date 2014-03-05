#include "StdAfx.h"
#include "Organ.h"
#include "Notes.h"

COrgan::COrgan(void)
{
	m_duration = 0.1;
	m_bpm = 120;
}
COrgan::COrgan(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
}

COrgan::~COrgan(void)
{
}

void COrgan::Start()
{
    m_time = 0;
    m_duration = m_duration * (1 / (m_bpm/60));
}


bool COrgan::Generate()
{
	m_frame[0] = 0;
	m_frame[1] = 0;
	double SOUNDSPEED = 343;

	double bar_freq = 0;

	for(int i=0; i<m_tonewheels.size(); i++)
	{
		if(i ==0)
		{
			bar_freq = m_freq*1;
		}
		else if(i ==1)
		{
			bar_freq = m_freq*3;
		}
		else if(i ==2)
		{
			bar_freq = m_freq*2;
		}
		else if(i ==3)
		{
			bar_freq = m_freq*4;
		}
		else if(i ==4)
		{
			bar_freq = m_freq*6;
		}
		else if(i ==5)
		{
			bar_freq = m_freq*8;
		}
		else if(i ==6)
		{
			bar_freq = m_freq*10;
		}
		else if(i ==7)
		{
			bar_freq = m_freq*12;
		}
		else if(i ==8)
		{
			bar_freq = m_freq*16;
		}

		// Adjust for drawbar setting
		if(m_tonewheels[i] == '8')
		{
			m_amp = 0.1;
		}
		else if(m_tonewheels[i] == '7')
		{
			m_amp = 0.0708;
		}
		else if(m_tonewheels[i] == '6')
		{
			m_amp = 0.0501;
		}
		else if(m_tonewheels[i] == '5')
		{
			m_amp = 0.0355;
		}
		else if(m_tonewheels[i] == '4')
		{
			m_amp = 0.0251;
		}
		else if(m_tonewheels[i] == '3')
		{
			m_amp = 0.0178;
		}
		else if(m_tonewheels[i] == '2')
		{
			m_amp = 0.0126;
		}
		else if(m_tonewheels[i] == '1')
		{
			m_amp = 0.0089;
		}
		else if(m_tonewheels[i] == '0')
		{
			m_amp = 0;
		}

		// generate wave and add to the current wave
		m_frame[0] += m_amp * sin(m_rad1[i]);
		m_frame[1] = m_frame[0];

		// calculate diff for vibrato
		double diff = bar_freq * (0.2 *sin(m_rad2[i]));

		// increment phases
		m_rad1[i] += (2 * PI * (bar_freq + diff)) / GetSampleRate();
		m_rad2[i] += (2 * PI * bar_freq) / GetSampleRate();
	}

	// Envelope
	AR(m_frame);

    // Update time
    m_time += GetSamplePeriod();

    // We return true until the time reaches the duration.
    return m_time < m_duration;
}

void COrgan::AR(double * frame)
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

void COrgan::SetToneWheels(WCHAR * setting)
{
	m_tonewheels.resize(9);
	m_rad1.resize(9);
	m_rad2.resize(9);
	int count = 0;
	int num = wcslen(setting);

	for(int i=0;i<num;i++)
	{
		m_tonewheels[count] = setting[i];
		//m_rad1[count] = 0;
		//m_rad2[count] = 0;
		count++;
	}
}

void COrgan::SetNote(CNote *note)
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
		else if(name == "drawbar")
		{
			SetToneWheels(value.bstrVal);
		}

   }

}