#include "cartridge.hpp"

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
        // Attempt to open file
        std::ifstream rom_dump(path, std::ios_base::binary | std::ios_base::in);
        if(!rom_dump)
        {
            std::cerr << "Unable to open ROM dump from path: " << path << std::endl;
            return false;
        }

        // Check if dump has header
        std::vector<uint8_t> header;
        std::cout << "Reading ROM dump from path: " << path << std::endl;
    
        // Standard iNES file has a header of 16 bytes
        header.resize(0x10);

        if(std::string{&header[0], &header[4]} != NES_HEADER)
        {
            std::cerr << "File is not in a valid iNES format." << std::endl;
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