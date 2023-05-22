#pragma once
#include <iostream>
#include <string>

//api of sorts to connect to sfml
//and also the console

namespace io
{
	class output
	{
	public:
		output();
		~output();
		void consoleWrite(std::string message);
	private:
	};
}
