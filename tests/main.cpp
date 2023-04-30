#include<iostream>
#include<fstream>
#include<string>

#include "cartridge.h"
#include "cpu.h"
#include "ppu.h"

#include "../src/cpu/Bus.h"
#include "../src/debug/Logger.hpp"
#include "test_rom.hpp"


#define IS_TRUE(func, test) { if (!(func)) std::cout << test << " failed on line " << __LINE__ << std::endl; }

int main()
{

    // Build ROM from embedded source
    std::string rom = "./build/romtest.nes";
    {
        std::ofstream ostrm(rom, std::ios::binary);
        ostrm.write(reinterpret_cast<const char*>(&ROM_TEST), sizeof ROM_TEST);
    }
    
    sneslite::Bus bus;

    IS_TRUE(test_cartridge(rom), "Cartridge");

    LOG(2) << "Cartridge Test Complete" << std::endl;

    bus.begin(rom);

    IS_TRUE(test_cpu(), "CPU");

    IS_TRUE(test_ppu(rom, bus), "PPU");
}