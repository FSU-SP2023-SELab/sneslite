#include<algorithm>

#include "Bus.h"
#include "ppu.hpp"

namespace sneslite
{
    // As cart is defined in bus, attempt to locate
    extern cartridge cart;

    ppu::ppu() :
        pd
        {
            cart.get_char_rom(),
            static_cast<cartridge::mirroring>( cart.get_mirror_type() ),
            {0}, {0}, {0}
        }
    {}

    ppu::address_register::address_register() :
        ar { {0}, false }
    {}
}