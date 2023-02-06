#include <cstdint>

#include "Cpu.h"

class System
{
public:
    System();
    ~System();

    //Devices in system
    Cpu cpu;
    uint8_t ram[128 * 1024];

    //WRAM Access
    uint8_t read_ram(uint32_t addr);
    void write_ram(uint32_t addr, uint8_t data);
};