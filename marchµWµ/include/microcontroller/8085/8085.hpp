#pragma once
#include <memory>

#include "timingAndControl.hpp"
#include "dataAddressBus.hpp"
//#include "alu.hpp"
//#include "decoder.hpp"
//#include "interruptControl.hpp"
//#include "registerManager.hpp"

#include <iostream>
#include <string>

namespace atat5
{
	struct internalComponents 
	{
		//std::unique_ptr<atat5::registerMan> m_registers;

		internalComponents()	
		{
		}
	};

	class processor
	{
	public:
		processor(uint16_t programCounter = 0);
	
		void dataAddressBus(uint16_t twoBytes, bool addressLatchEnable);
	
		//temporary main loop
		//will be merged to the main game loop after completion 
		void Run();
	private:

		std::string m_inputProgram;
		std::shared_ptr<atat5::internalComponents> m_components;
		//timing and control is special because it is 
		//a component that controls other components
		//so can't put it in m_components due to recursion
		//that arises when it tries to access m_components
		std::unique_ptr<atat5::timingAndControl> m_timingAndControl;
		
		//same goes for the bus

	};
}
