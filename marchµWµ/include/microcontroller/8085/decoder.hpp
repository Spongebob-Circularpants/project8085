#pragma once
#include <cstdint>

typedef uint8_t oneByte;

namespace atat5
{
	class instructionDecoder
	{
	public:
		instructionDecoder(oneByte instructionRegister);
		~instructionDecoder();
		
		void decode();


	private:
		oneByte m_instructionRegister;
	};
}
