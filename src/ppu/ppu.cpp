#include "ppu.hpp"

namespace sneslite
{
    ppu::ppu() :
        char_rom( cart.get_char_rom() ),
        mirror_type(cartridge.get_mirror_type())
    {}

}