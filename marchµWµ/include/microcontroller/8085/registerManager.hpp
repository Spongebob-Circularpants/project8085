#pragma once
#include <cstdint>

//full disclaimer, even though we generally work 
//with hex in these muPs, I'm purposely gonna
//work with decimals because I don't know of a 
//system to change the base-system of in-built
//data bytes

typedef uint8_t oneByte;
typedef uint16_t twoBytes;

namespace atat5
{
	class registerManager
	{
	public:
		registerManager();
		~registerManager();
		
		oneByte multiplexer(oneByte registerAddress);
		void dataAddressBus(uint16_t twoBytes, bool addressLatchEnable);

			
	private:
		oneByte A, W, Z, B, C, D, E, H, L;
		twoBytes m_stackPointer, m_programCounter;
		//as it stands, homa and loma are completely useless 
		//in this emulation as the program counter does 
		//everything but i'm gonna include them for 
		//completeness' sake as you look into this 
		//emulator more, you're gonna realise this 
		//theme is more prevelant than not
		oneByte m_homAddress;
		oneByte m_lomAddress;
		oneByte m_data;
	};
}
