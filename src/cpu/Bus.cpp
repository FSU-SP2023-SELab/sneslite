#include "Bus.h"
#include "Cpu.h"
#include "../debug/Logger.hpp"

namespace sneslite
{

    Bus::Bus()
    {
	    //Clear RAM contents
	    for (auto& i : ram) i = 0x00;
        LOG(Info) << "RAM cleared";

	    //Connect CPU to communication bus
	    cpu.ConnectBus(this);
        LOG(Info) << "CPU connected to bus";
        
        // Connect PPU to bus
        ppu.connect_bus(this);
        LOG(Info) << "PPU connected to bus";
    }

    Bus::~Bus()
    {

    }

    void Bus::initialize(std::string path)
    {
        if (path == "") {
            LOG(Info) << "Must provide path";
            return;
        }

        if (!cartridge.load_dump_file(path)) {
            LOG(Info) << "Unable to open file at path";  
            return;
        }
        LOG(Info) << "Cartridge loaded";

        ppu.initialize_ppu();
        LOG(Info) << "PPU Initialized";
    }

    void Bus::write(uint16_t addr, uint8_t data)
    {
        LOG(Info) << "Writing data to bus";
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
        else if (addr == 0x4016 || addr == 0x4017)
        {
            joypad.write(data);
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
        else if (addr == 0x4016 || addr == 0x4017)
        {
            data = joypad.read();
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
        ppu.tick(Clockcount);
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