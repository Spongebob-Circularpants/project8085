#include "timingAndControl.hpp"

namespace atat5
{
	
	timingAndControl::timingAndControl()
	:
		m_clockCycleCounter(0)
	{
	}
	
	timingAndControl::~timingAndControl()
	{
	}

	void timingAndControl::opcodeFetch()
	{
	}

	void timingAndControl::memoryRead()
	{
	}

	void timingAndControl::memoryWrite()
	{
	}

	void timingAndControl::ioRead()
	{
	}

	void timingAndControl::ioWrite()
	{
	}

	void timingAndControl::addressLatchEnable()
	{
		if(!m_clockCycleCounter) 
		{
			systemBus::controlBus::ALE = HIGH;
		}
		else
		{
			systemBus::controlBus::ALE = LOW;
		}
	}

	//clock 
	void timingAndControl::clockLow()
	{
		systemBus::controlBus::clock = LOW;
	}

	void timingAndControl::clockRisingEdge()
	{
		systemBus::controlBus::clock = RISING;
	}

	void timingAndControl::clockHigh()
	{
		systemBus::controlBus::clock = HIGH;
	}

	void timingAndControl::clockFallingEdge()
	{
		systemBus::controlBus::clock = FALLING;  
		//if opcode fetch
		if(
			systemBus::controlBus::S1 &&
			systemBus::controlBus::S0 &&
			!systemBus::controlBus::read_0 &&
			systemBus::controlBus::write_0 &&
			!systemBus::controlBus::IO_M
		)
		{
			m_clockCycleCounter = (m_clockCycleCounter+1)%4;
		}
		else
		{
			m_clockCycleCounter = (m_clockCycleCounter+1)%4;
		}

	}
	
	
	
	

}
