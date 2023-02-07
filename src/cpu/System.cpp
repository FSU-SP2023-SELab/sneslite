/**
 * @file System.cpp
 * @brief System definitions
 */

#include "System.h"

System::System()
{
    cpu.ConnectSystem(this);

    for (auto &i : ram) i = 0x00;
}

System::~System() {}

uint8_t System::read_ram(uint32_t addr)
{
    if (addr >= 0x0000 && addr <= 0x1FFF ) {
        return ram[addr];
    }
    return UINT8_MAX;
}

void System::write_ram(uint32_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0x1FFF) {
        ram[addr] = data;
    }
}