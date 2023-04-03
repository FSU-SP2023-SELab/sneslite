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
        
        // Connect PPU to bus
        ppu.connect_bus(this);
    }

    Bus::~Bus()
    {

    }

    void Bus::write(uint16_t addr, uint8_t data)
    {
		ram[addr] = data;
    }

    uint8_t Bus::read(uint16_t addr, bool bReadOnly)
    {
		return ram[addr];
    }

    void Bus::SetSampleFrequency(uint32_t sample_rate)
    {
        AudioTimeSample = 1.0 / (double)sample_rate;
        AudioTimeNESClock = 1.0 / 5369318.0;
    }

    void Bus::reset()
    {
        cpu.reset();
        Clockcount = 0;
    }

    bool Bus::clock()
    {
        //Used for when PPU is introduced
        if (Clockcount % 3 == 0)
        {
            cpu.clock();
        }
        Clockcount++;
    }

}