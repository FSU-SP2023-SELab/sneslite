#include "Bus.h"
#include "Cpu.h"

namespace sneslite
{

    Bus::Bus()
    {
	    //Clear RAM contents
	    for (auto& i : ram) i = 0x00;

	    //Connect CPU to communication bus
	    cpu.ConnectBus(this);
    }

    Bus::~Bus()
    {

    }

    void Bus::write(uint16_t addr, uint8_t data)
    {
	    if (addr >= 0x0000 && addr <= 0xFFFF)
		    ram[addr] = data;
    }

    uint8_t Bus::read(uint16_t addr, bool bReadOnly)
    {
	    if (addr >= 0x0000 && addr <= 0xFFFF)
		    return ram[addr];

	    return 0x00;
    }

    void Bus::SetSampleFrequency(uint32_t sample_rate)
    {
        AudioTimeSample = 1.0 / (double)sample_rate;
        AudioTimeNESClock = 1.0 / 5369318.0;
    }
}