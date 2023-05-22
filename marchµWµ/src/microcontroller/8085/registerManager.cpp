#include "registerManager.hpp"

namespace atat5
{
	registerManager::registerManager() :
	A(0), B(0), C(0), D(0), E(0), H(0), L(0),
	m_stackPointer(0), m_programCounter(0)
	{
	}

	registerManager::~registerManager()
	{
	}

	void registerManager::dataAddressBus(uint16_t twoBytes, bool addressLatchEnable)
	{
		//the address latch
		if(addressLatchEnable)
		{
			m_programCounter = twoBytes;

			//mask with 255 to get just the loma 
			m_lomAddress = twoBytes & 255;

			//bitwise right shift 8 times then mask again
			twoBytes = (twoBytes>>8);
			m_homAddress = twoBytes & 255;
		}
		else 
		{
			m_data = twoBytes & 255;
		}
	}
}
