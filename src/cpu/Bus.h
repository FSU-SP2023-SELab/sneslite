#pragma once
#include "Cpu.h"
#include <cstdint>
#include <array>

namespace sneslite
{

    class Bus
    {
    public:
	    Bus();
	    ~Bus();

	    //Devices on the Bus
        Cpu cpu;

	    //Temp fake RAM
	    std::array<uint8_t, 64 * 1024> ram;

	    //Bus Read/Write
	    void write(uint16_t addr, uint8_t data);
	    uint8_t read(uint16_t addr, bool bReadOnly = false);

    };
}
