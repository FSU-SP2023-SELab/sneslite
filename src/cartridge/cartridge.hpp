#pragma once

#include<vector>
#include<iostream>
#include<string>
#include<cstdint>

namespace sneslite
{
    /**
     * Cartridge memory allocation.
     * 
     * A typical NES cartridge contains two ROM banks.
     * A character ROM which contains a game's tilesets, and a program ROM which contains the game's binary.
     * Some cartridges come with additional RAM, such as battery-backed work RAM (used for saving), or character RAM (used for bank switching tilesets).
     * 
     * Source: https://en.wikibooks.org/wiki/NES_Programming/Memory_Map
     */
    class cartridge
    {
        public:
            /**
             * @brief Construct a new cartridge object
             */
            cartridge();
            
            /**
             * @brief Attempt to load a cartridge dump given some path.
             * 
             * @param path 
             * @return true 
             * @return false 
             */
            bool load_dump_file(std::string path);
            
            /**
             * @brief Get program ROM
             * 
             * @return const std::vector<uint8_t>& 
             */
            const std::vector<uint8_t>& get_prg_rom();

            /**
             * @brief Get character tileset ROM
             * 
             * @return const std::vector<uint8_t>& 
             */
            const std::vector<uint8_t>& get_char_rom();

        private:
            /**
             * @brief Holds program ROM data.
             */
            const std::vector<uint8_t>& PRG_ROM;

            /**
             * @brief Holds character ROM data.
             */
            const std::vector<uint8_t> CHAR_ROM;
    };
}