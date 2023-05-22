#include "output.hpp"

namespace io
{
	output::output()
	{
	}

	output::~output()
	{
	}

	void output::consoleWrite(std::string message)
	{
		std::cout<<message<<"\n";
		//std::cout<<std::hex<<"Address: "<<unsigned(m_homAddress)<<unsigned(m_lomAddress)<<"\n"<<"data: "<<unsigned(m_data)<<"\n";
	}
}
