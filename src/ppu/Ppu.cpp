#include<algorithm>

#include "Ppu.hpp"

namespace sneslite
{
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

    Ppu::address_register::address_register() :
        ar { {0}, false }
    {}
}