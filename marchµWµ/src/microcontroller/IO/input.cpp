#include "input.hpp"

namespace io
{
	input::input()
	{
	}

	input::~input()
	{
	}

	void input::consoleRead()
	{
		std::cin>>m_inputBuffertem;
	}
}
