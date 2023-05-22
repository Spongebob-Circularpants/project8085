#pragma once

namespace microcontroller 
{
	class component
	{
	public:
		component(){};
		virtual ~component(){};

		//a component of the architecture does things during the following events
		virtual void clockLow() {};
		virtual void clockRisingEdge() {};
		virtual void clockHigh() {};
		virtual void clockFallingEdge() {};
		//they are not virtual because some component do nothing during a clock cycle
	};
}
