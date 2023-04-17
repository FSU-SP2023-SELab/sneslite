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
        if(addr >= 0x0000 && addr <= 0x1FFF)
        {
            ram[addr & 0x07FF] = data;
        }
        else if(addr >= 0x2000 && addr <= 0x3FFF)
        {
            ppu.write_to_ar(data);
        }
        else if((addr >= 0x4000 && addr <= 0x4013) || addr == 0x4015 || addr == 0x4017)
        {
            apu.Write(addr, data);
        }
        else if (addr == 0x4014)
        {
            dma_page = data;
            dma_addr = 0x00;
            dma_transfer = true;
        }
    }

    uint8_t Bus::read(uint16_t addr, bool bReadOnly)
    {
        uint8_t data = 0x00;

        if(addr >= 0x0000 && addr <= 0x1FFF)
        {
            data = ram[addr & 0x07FF];
        }
        else if(addr >= 0x2000 && addr <= 0x3FFF)
        {
            data = ppu.read_data();
        }
        else if(addr == 0x4015)
        {
            data = apu.Read(addr);
        }

		return data;
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
        apu.clock();
        if (Clockcount % 3 == 0)
        {
            if (dma_transfer)
            {
                if (dma_dummy)
                {
                    if(Clockcount % 2 == 1)
                    {
                        dma_dummy = false;
                    }
                }
                else
                {
                    if (Clockcount % 2 == 0)
                    {
                        dma_data = read(dma_page << 8 | dma_addr);
                    }
                    else
                    {
                        dma_addr++;
                        if (dma_addr == 0x00)
                        {
                            dma_transfer = false;
                            dma_dummy = true;
                        }
                    }
                }
            }
            else
            {
                cpu.clock();
            }
        }

        bool AudioReady = false;
        AudioTime += AudioTimeNESClock;
        if(AudioTime >= AudioTimeSample)
        {
            AudioTime -= AudioTimeSample;
            Sample = apu.GetSample();
            AudioReady = true;
        }

        Clockcount++;

        return AudioReady;

    }

}