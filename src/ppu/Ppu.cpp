#include<algorithm>
#include<csignal>
#include<cassert>

#include "Ppu.hpp"
#include "../cpu/Bus.h"
#include "../debug/Logger.hpp"

namespace sneslite
{
    const std::array<std::tuple<uint8_t, uint8_t, uint8_t>, 64> SYSTEM_PALLETE =
    {{
        {0x80, 0x80, 0x80}, {0x00, 0x3D, 0xA6}, {0x00, 0x12, 0xB0}, {0x44, 0x00, 0x96}, {0xA1, 0x00, 0x5E},
        {0xC7, 0x00, 0x28}, {0xBA, 0x06, 0x00}, {0x8C, 0x17, 0x00}, {0x5C, 0x2F, 0x00}, {0x10, 0x45, 0x00},
        {0x05, 0x4A, 0x00}, {0x00, 0x47, 0x2E}, {0x00, 0x41, 0x66}, {0x00, 0x00, 0x00}, {0x05, 0x05, 0x05},
        {0x05, 0x05, 0x05}, {0xC7, 0xC7, 0xC7}, {0x00, 0x77, 0xFF}, {0x21, 0x55, 0xFF}, {0x82, 0x37, 0xFA},
        {0xEB, 0x2F, 0xB5}, {0xFF, 0x29, 0x50}, {0xFF, 0x22, 0x00}, {0xD6, 0x32, 0x00}, {0xC4, 0x62, 0x00},
        {0x35, 0x80, 0x00}, {0x05, 0x8F, 0x00}, {0x00, 0x8A, 0x55}, {0x00, 0x99, 0xCC}, {0x21, 0x21, 0x21},
        {0x09, 0x09, 0x09}, {0x09, 0x09, 0x09}, {0xFF, 0xFF, 0xFF}, {0x0F, 0xD7, 0xFF}, {0x69, 0xA2, 0xFF},
        {0xD4, 0x80, 0xFF}, {0xFF, 0x45, 0xF3}, {0xFF, 0x61, 0x8B}, {0xFF, 0x88, 0x33}, {0xFF, 0x9C, 0x12},
        {0xFA, 0xBC, 0x20}, {0x9F, 0xE3, 0x0E}, {0x2B, 0xF0, 0x35}, {0x0C, 0xF0, 0xA4}, {0x05, 0xFB, 0xFF},
        {0x5E, 0x5E, 0x5E}, {0x0D, 0x0D, 0x0D}, {0xFF, 0xFF, 0xFF}, {0xA6, 0xFC, 0xFF}, {0xB3, 0xEC, 0xFF},
        {0xDA, 0xAB, 0xEB}, {0xFF, 0xA8, 0xF9}, {0xFF, 0xAB, 0xB3}, {0xFF, 0xD2, 0xB0}, {0xFF, 0xEF, 0xA6},
        {0xFF, 0xF7, 0x9C}, {0xD7, 0xE8, 0x95}, {0xA6, 0xED, 0xAF}, {0xA2, 0xF2, 0xDA}, {0x99, 0xFF, 0xFC},
        {0xDD, 0xDD, 0xDD}, {0x11, 0x11, 0x11}, {0x11, 0x11, 0x11}
    }};

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

    bool Ppu::tick(uint8_t cycles)
    {
        pd.cycles += cycles;

        if(pd.cycles >= 341)
        {
            pd.cycles = pd.cycles - 341;
            pd.scanline += 1;

            if(pd.scanline == 241)
            {
                if(p_cr->generate_vblank_nmi())
                {
                    p_sr->set_vblank_status(true);
                    LOG(Info) << "Pending NMI interrupt...";
                }
            }

            if(pd.scanline >= 262)
            {
                pd.scanline = 0;
                p_sr->reset_vblank_status();
                return true;
            }
        }

        return false;
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

    bool Ppu::controller_register::_contains(uint8_t flag) const {
        return (cr.value & flag) != 0;
    }

    uint8_t Ppu::controller_register::increment_vram_addr()
    {
        return (cr.value & cr.VRAM_ADD_INCREMENT) ? 32 : 1;
    }

    void Ppu::controller_register::update_vram_addr(uint8_t data)
    {
        cr.value = data;
    }

    uint16_t Ppu::controller_register::sprt_pattern_addr() const 
    {
        return _contains(cr.SPRITE_PATTERN_ADDR) ? 0x1000 : 0;
    }

    uint16_t Ppu::controller_register::bknd_pattern_addr() const 
    {
        return _contains(cr.BACKROUND_PATTERN_ADDR) ? 0x1000 : 0;
    }

    uint8_t Ppu::controller_register::sprite_size() const 
    {
        return _contains(cr.SPRITE_SIZE) ? 16 : 8;
    }

    uint8_t Ppu::controller_register::master_slave_select() const 
    {
        return _contains(cr.MASTER_SLAVE_SELECT) ? 1 : 0;
    }

    bool Ppu::controller_register::generate_vblank_nmi() const 
    {
        return _contains(cr.GENERATE_NMI);
    }

    //
    // Status register emulation
    //
    Ppu::status_register::status_register() :
        sr
        {
            0b00000000
        }
    {}

    void Ppu::status_register::_set(uint8_t flag, bool status)
    {
        if (status) {
            sr.value |= flag;
        } else {
            sr.value &= ~flag;
        }
    }

    void Ppu::status_register::_remove(uint8_t flag)
    {
        sr.value &= ~flag;
    }

    bool Ppu::status_register::_contains(uint8_t flag) const
    {
        return (sr.value & flag) != 0;
    }

    void Ppu::status_register::set_vblank_status(bool status)
    {
        _set(sr.VBLANK_STARTED, status);
    }

    void Ppu::status_register::set_sprite_zero_hit(bool status)
    {
        _set(sr.SPRITE_ZERO_HIT, status);
    }

    void Ppu::status_register::set_sprite_overflow(bool status)
    {
        _set(sr.SPRITE_OVERFLOW, status);
    }

    void Ppu::status_register::reset_vblank_status()
    {
        _remove(sr.VBLANK_STARTED);
    }

    bool Ppu::status_register::is_in_vblank() const
    {
        return _contains(sr.VBLANK_STARTED);
    }

    uint8_t Ppu::status_register::snapshot() const
    {
        return sr.value;
    }

    //
    // Frame rendering abstraction
    //
    Ppu::frame::frame()
    {
        fd.value.push_back(fd.WIDTH * fd.HEIGHT * 3);
        fd.value.push_back(0);
    }

    void Ppu::frame::set_pixel(size_t x, size_t y, std::tuple<uint8_t, uint8_t, uint8_t> rgb)
    {
        auto base = y * 3 * fd.WIDTH + x * 3;

        if(base + 2 < fd.value.size())
        {
            fd.value[base]     = std::get<0>(rgb);
            fd.value[base + 1] = std::get<1>(rgb);
            fd.value[base + 2] = std::get<2>(rgb);
        }
    }

    std::vector<uint8_t> Ppu::frame::show_tile(std::vector<uint8_t> &char_rom, size_t bank, size_t tile_n)
    {
        assert(bank <= 1);

        frame ppu_frame;
        size_t bank_offset = bank * 0x1000;

        const uint8_t *tile = &char_rom[bank_offset + tile_n * 16];

        for (size_t y = 0; y <= 7; ++y) {
            uint8_t upper = tile[y];
            uint8_t lower = tile[y + 8];

            for (int x = 7; x >= 0; --x) {
                uint8_t value = (1 & upper) << 1 | (1 & lower);
                upper = upper >> 1;
                lower = lower >> 1;
                std::tuple<uint8_t, uint8_t, uint8_t> rgb;
                switch (value) {
                    case 0:
                        rgb = SYSTEM_PALLETE[0x01];
                        break;
                    case 1:
                        rgb = SYSTEM_PALLETE[0x23];
                        break;
                    case 2:
                        rgb = SYSTEM_PALLETE[0x27];
                        break;
                    case 3:
                        rgb = SYSTEM_PALLETE[0x30];
                        break;
                    default:
                        LOG(Error) << "Invalid pallete: " << value;
                        raise(SIGTERM);
                        break;
                }
            
                ppu_frame.set_pixel(x, y, rgb);
            }
        }

        return ppu_frame.fd.value;
    }

    std::vector<uint8_t> Ppu::frame::get_frame_data()
    {
        return fd.value;
    }
}