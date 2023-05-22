#pragma once

#include <stdint.h>

namespace systemBus 
{
	//using only one bus to transmit data and address
	struct dataAddressBus
	{
		inline static uint16_t data_address;

		//idk how sid and sod work
		//but my intuition says they
		//transmit data at 1 bit per 
		//clock falling edge so I'm 
		//making them bools
		static bool SID, SOD;
	};

	//I can't believe I was creating a class for 
	//wrapping a single 16 bit data. I guess I've 
	//fallen deep into the oop rabbit hole
}
