#pragma once
#include "component.hpp"
#include "controlBus.hpp"
#include "dataAddressBus.hpp"
#include "rom.hpp"	
#include <iostream>
#include <memory>

namespace atat5
{
	class timingAndControl : public microcontroller::component
	{
	public:
		timingAndControl();
		~timingAndControl();

		//timing section
		void clockLow() override;
		void clockRisingEdge() override;
		void clockHigh() override;
		void clockFallingEdge() override; //bing bong ding dong
		
		//control section
		void addressLatchEnable();

		void opcodeFetch();
		void memoryRead();
		void memoryWrite();
		void ioRead();
		void ioWrite();
	private:
		//this counts upto 4 clock cycles
		//because opcodeFetch
		unsigned m_clockCycleCounter;

		//base class pointer to component
		component* bptr;
	};
}
