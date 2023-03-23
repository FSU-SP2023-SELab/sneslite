#include<algorithm>

#include "Ppu.hpp"

namespace sneslite
{
    //
    // PPU initialization
    //

    // As cart is defined in bus, attempt to locate
    extern Cartridge cart;

    Ppu::Ppu() :
        pd
        {
            cart.get_char_rom(),
            static_cast<Cartridge::mirroring>( cart.get_mirror_type() ),
            {0}, {0}, {0}
        }
    {}

    //
    // Address register emulation
    //

    Ppu::address_register::address_register() :
        ar { {0}, false }
    {}

    void Ppu::address_register::set_addr(uint16_t data)
    {
        ar.value[0] = static_cast<uint8_t>(data >> 8);
        ar.value[1] = static_cast<uint8_t>(data & 0xff);
    }

    void Ppu::address_register::update_addr(uint8_t data)
    {
        ar.hi_ptr ? ar.value[0] = data : ar.value[1] = data;

        // Check if addr value is greater than 16383, which is the end of
        // the mirror memory region
        // If it is, mirror the address down
        if(Ppu::address_register::get_addr_value() > 0x3fff)
        {
            Ppu::address_register::set_addr
            (
                Ppu::address_register::get_addr_value() & 0xFFB
            );
        }
    }

    void Ppu::address_register::increment_addr(uint8_t inc)
    {
        uint8_t lo = ar.value[1];

        uint32_t sum = lo + inc;

        ar.value[1] = (sum + ((sum < lo) | (sum < inc)));

        if(Ppu::address_register::get_addr_value() > 0x3fff)
        {
            Ppu::address_register::set_addr
            (
                Ppu::address_register::get_addr_value() & 0xFFB
            );
        }
    }

    void Ppu::address_register::reset_latch()
    {
        ar.hi_ptr = true;
    }

    uint16_t Ppu::address_register::get_addr_value()
    {
        (static_cast<uint16_t>(ar.value[0]) << 8) |
        (static_cast<uint16_t>(ar.value[1]));
    }

    //
    // Controller register emulation
    //
    
    Ppu::controller_register::controller_register() :
        cr { 0 }
    {}

    uint8_t Ppu::controller_register::increment_vram_addr()
    {
        return (cr.value & cr.VRAM_ADD_INCREMENT) ? 32 : 1;
    }

    void Ppu::controller_register::update_vram_addr(uint8_t data)
    {
        cr.value = data;
    }
}