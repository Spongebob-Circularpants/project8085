#pragma once
//#include "8085.hpp"

#include "ram.hpp"
#include "rom.hpp"

#include "controlBus.hpp"
#include "dataAddressBus.hpp"

#include "input.hpp"
#include "output.hpp"

#include <memory>

//8085 connected to sfml
//this should be the first time this has happened
namespace microcontroller
{
	//I'm calling it a system, one could call it a computer 
	struct components
	{
		//cpu, memory, io
		std::unique_ptr<microcontroller::memory> m_ram; 
		std::unique_ptr<io::input> m_input; 
		std::unique_ptr<io::output> m_output; 

		components() 
		:
			m_ram(std::make_unique<microcontroller::memory>()),
			m_input(std::make_unique<io::input>()),
			m_output(std::make_unique<io::output>())
		{
		}
	};
}
