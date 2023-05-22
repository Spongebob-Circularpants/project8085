#pragma once

#include <stdint.h>
#include "rom.hpp"
//buses are by their nature, shared 
//so making their methods and data members 
//inline static is the way to go
//inline makes it such that initialization
//is not required outside the struct and 
//the use of static should be obvious


//the control bus is under direct control
//of the control unit/timingAndControl
namespace systemBus 
{
	struct controlBus
	{
		//the clock out from the muP
		//0 = low
		//1 = rising
		//2 = high
		//3 = falling
		inline static signal clock = LOW;

		//reset signals
		inline static signal resetIN_0 = HIGH, resetOUT = LOW;

		//ready signal; idk what to do with this
		inline static signal ready = HIGH;

		//io/memory operation 
		inline static signal IO_M;

		//_0 = complement i.e. active low
		inline static signal read_0;
		inline static signal write_0;

		//input/output operation
		inline static signal S1, S0;

		//address latch enable
		inline static signal ALE;

		//interrupt signals
		inline static signal INTR = LOW, INTA_0 = LOW;
		inline static signal TRAP = LOW;
		inline static signal RST7_5 = LOW, RST6_5 = LOW, RST5_5 = LOW;

		//dma
		inline static signal HOLD = LOW, HLDA = LOW;
	};		

}
