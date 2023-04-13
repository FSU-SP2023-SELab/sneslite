#include<algorithm>
#include<csignal>

#include "Ppu.hpp"
#include "../cpu/Bus.h"
#include "../debug/Logger.hpp"

namespace sneslite
{
    //
    // PPU initialization
    //

    Ppu::Ppu() :
        pd
        {
            p_bus->cartridge.get_char_rom(),
            p_bus->cartridge.get_mirror_type(),
            {0}, {0}, {0}
        }
    {}
    
    uint8_t Ppu::read_data() {
        uint16_t addr = p_ar->get_addr_value();

        increment_vram_addr();

        if (addr <= 0x1fff)
        {
            uint8_t result = pd.internal_data_buffer;
            pd.internal_data_buffer = pd.char_rom[addr];
            return result;
        }
        else if (addr >= 0x2000 && addr <= 0x2fff)
        {
            uint8_t result = pd.internal_data_buffer;
            pd.internal_data_buffer = pd.vram[mirror_vram_addr(addr)];
            return result;
        }
        else if (addr >= 0x3000 && addr <= 0x3eff)
        {
            LOG(Info) << "Address " + std::to_string(addr) + " shouldn't be used";
        }
        else if (addr == 0x3f10 || addr == 0x3f14 || addr == 0x3f18 || addr == 0x3f1c)
        {
            uint16_t add_mirror = addr - 0x10;
            return pd.palette_table[(add_mirror - 0x3f00)];
        }
        else if (addr >= 0x3f00 && addr <= 0x3fff)
        {
            return pd.palette_table[(addr - 0x3f00)];
        }
        else
        {
            LOG(Error) << "Unexpected access to mirrored space " + std::to_string(addr);
            raise(SIGTERM);
        }
    }
    
    void Ppu::write_to_ar(uint8_t data)
    {
        p_ar->update_addr(data);
    }
    
    void Ppu::write_to_control(uint8_t data)
    {
        p_cr->update_vram_addr(data);
    }
    
    void Ppu::increment_vram_addr()
    {
        p_cr->increment_vram_addr();
    }

    // TODO: Check for proper mapping
    uint16_t Ppu::mirror_vram_addr(uint16_t addr)
    {
        uint16_t mirrored_vram = addr & 0b10111111111111;
        uint16_t vram_index = mirrored_vram - 0x2000;
        uint8_t name_table = vram_index / 0x400;

        if ((pd.mirror_type == Cartridge::mirroring::VERTICAL && name_table == 2) ||
            (pd.mirror_type == Cartridge::mirroring::VERTICAL && name_table == 3))
        {
            return vram_index - 0x800;
        }
        else if ((pd.mirror_type == Cartridge::mirroring::HORIZONTAL && name_table == 2) ||
                 (pd.mirror_type == Cartridge::mirroring::HORIZONTAL && name_table == 1))
        {
            return vram_index - 0x400;
        }
        else if (pd.mirror_type == Cartridge::mirroring::HORIZONTAL && name_table == 3)
        {
            return vram_index - 0x800;
        }
        else
        {
            return vram_index;
        }
    }

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
        return (static_cast<uint16_t>(ar.value[0]) << 8) |
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