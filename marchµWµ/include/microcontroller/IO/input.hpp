#pragma once
#include <iostream>

//api of sorts to connect to sfml

namespace io
{

	class input
	{
	public:
		input();
		~input();

		void consoleRead();
	private:
		uint16_t m_inputBuffertem;
	};
}
