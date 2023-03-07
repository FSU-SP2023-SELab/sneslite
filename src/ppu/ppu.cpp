#include "ppu.hpp"

namespace sneslite
{
    ppu::ppu() :
        char_rom( cartridge.get_char_rom() ),
        mirror_type(cartridge.get_mirror_type())
    {}

    void ppu::insertCart(const std::shared_ptr<cartridge>& newcart)
    {
        this->cart = newcart;
    }
}