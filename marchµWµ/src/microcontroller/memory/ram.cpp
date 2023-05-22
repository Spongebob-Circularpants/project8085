#include "ram.hpp"

namespace microcontroller 
{
	memory::memory(unsigned size) 
	:
		m_size(size),
 		m_ram(new uint8_t [m_size])
	{
		for(unsigned i = 0; i<m_size; i++)
		{
			//default value is 0
			m_ram[i] = 0;
		}
	}

	memory::~memory()
	{
		delete [] m_ram; 	
	}

	void memory::readBus(bool address_data)
	{
		if(address_data) 
		{
			m_addressFromBus = systemBus::dataAddressBus::data_address; 
		}
		else 
		{
			//8 bit         //16 bit
			m_dataFromBus = systemBus::dataAddressBus::data_address;
		}
	}

	void memory::dataToBus()
	{
		systemBus::dataAddressBus::data_address = m_ram[m_addressFromBus];
	}

	void memory::store()
	{
		*(m_ram+m_addressFromBus) = m_dataFromBus;
	}

	uint8_t memory::dmaOutput(uint16_t address)
	{
		return *(m_ram+address);
	}


	void memory::dmaInput(uint16_t address, uint8_t data)
	{
		*(m_ram+address) = data;
	}
}
