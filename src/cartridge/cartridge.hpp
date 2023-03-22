#pragma once

#include "../debug/logger.hpp"

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
             * @return true, if file loaded 
             * @return false, if unable to load file
             * 
             * @warning PAL cartridges are currently not supported
             */
            bool load_dump_file(std::string path);
            
            /**
             * @brief Get program ROM
             * 
             * @return vector<uint8_t> PRG_ROM
             */
            std::vector<uint8_t>& get_prg_rom();

            /**
             * @brief Get the start position for program ROM
             * 
             * @return uint16_t PRG_ROM_START
             */
            uint16_t get_prg_rom_start();

            /**
             * @brief Get character tileset ROM
             * 
             * @return vector<uint8_t> CHAR_ROM
             */
            std::vector<uint8_t>& get_char_rom();

            /**
             * @brief Get mapper number
             * 
             * @return uint8_t MAPPER_NUMBER
             */
            uint8_t get_mapper_number();

            /**
             * @brief Get mirror type
             * 
             * @return const uint8_t MIRROR_TYPE
             */
            uint8_t get_mirror_type();

            /**
             * @brief Three options for NES mirroring.
             * 
             * @warning Currently does not support single-screen mirroring, which is available
             * on certain cartridge chipsets.
             */
            enum mirroring
            {
                FOUR_SCREEN = 0,
                VERTICAL = 1,
                HORIZONTAL = 2
            };

        private:
            /**
             * @brief String representation of the iNES file header.
             */
            const std::string NES_HEADER = "NES\x1A";
        
            /**
             * @brief Holds program ROM data.
             */
            std::vector<uint8_t> PRG_ROM;

            /**
             * @brief Points to the start position for PRG_ROM.
             */
            uint16_t PRG_ROM_START;

            /**
             * @brief Holds character ROM data.
             */
            std::vector<uint8_t> CHAR_ROM;

            /**
             * @brief Holds mapper type.
             */
            uint8_t MAPPER_NUMBER;

            /**
             * @brief Identifies if ROM uses additional RAM banks
             */
            bool EXTENDED_RAM;

            /**
             * @brief Holds mirror type.
             */
            mirroring MIRROR_TYPE;
    };
}