#pragma once

#include "component.hpp"
#include <stdint.h>
#include "dataAddressBus.hpp"

namespace microcontroller 
{

/*choices; 
array, 
hashmap, 
fileHandling
-array and hashmap should behave identically 
since we know the "key"/address but if i use 
a hashmap, i'll only need to allocate memory 
when required using insert

-fileHandling - manually looking up and poking
the memory is easier i guess i should use the 
file handling method because this is an emulator
and i'm trying to recreate all of the hardware 
conditions
*/
	
	//just for testing purposes 
	class memory : public component
	{
	public:
		//the size has to be unsigned and not 
		//uint16_t since 65536 can't fit in it
		memory(unsigned size = 65536);
		~memory();
	
		//void clockFallingEdge();
		void readBus(bool address_data);
		void dataToBus();
		void store();

		uint8_t dmaOutput(uint16_t address);
		void dmaInput(uint16_t address, uint8_t data);

	private:
		uint16_t m_addressFromBus;
		uint8_t m_dataFromBus;
		unsigned m_size;
		uint8_t *m_ram;
	};

	/*using file handling
	class memoryFile
	{
	public:
		memoryFile();
		~memoryFile();
	};*/

}
