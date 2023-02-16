#include "cartridge.hpp"
#include "../debug/logger.hpp"

#include<string>
#include<fstream>
#include<vector>

namespace sneslite
{
    cartridge::cartridge() :
        MAPPER_NUMBER(0),
        MIRROR_TYPE(FOUR_SCREEN)
    {}

    bool cartridge::load_dump_file(std::string path)
    {
        std::ifstream rom_dump(path, std::ios_base::binary | std::ios_base::in);
        if(!rom_dump)
        {
            std::cerr << "Unable to open ROM dump from path: " << path << std::endl;
            return false;
        }
    }

    const std::vector<uint8_t>& cartridge::get_prg_rom()
    {
        return PRG_ROM;
    }

    const std::vector<uint8_t>& cartridge::get_char_rom()
    {
        return CHAR_ROM;
    }

    const uint8_t cartridge::get_mapper_number()
    {
        return MAPPER_NUMBER;
    }

    const uint8_t cartridge::get_mirror_type()
    {
        return static_cast<uint8_t>(MIRROR_TYPE);
    }
}