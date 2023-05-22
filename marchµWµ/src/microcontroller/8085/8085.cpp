#include "8085.hpp"

namespace atat5
{

	processor::processor(uint16_t programCounter) 
	:
		m_components(std::make_shared<atat5::components>()),
	m_timingAndControl(std::make_unique<atat5::timingAndControl>())
	{
		std::cout<<"The program counter is "<<programCounter<<"\n";
	}

	

	void processor::Run()
	{
		std::cin.unsetf(std::ios::dec);
		std::cin.unsetf(std::ios::hex);
		std::cin.unsetf(std::ios::oct);
		//while(true)
		{
			//just in case the any of the flags are set
			m_timingAndControl->clockFallingEdge();
		}
	}

	


}
