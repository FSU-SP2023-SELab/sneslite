#pragma once

#include<vector>
#include<cstdint>

#include "../cpu/Bus.h"
#include "../cartridge/cartridge.hpp"

namespace sneslite
{
    class ppu
    {
        public:
            /**
             * @brief Constructor, transfers data from cartridge read as stored on bus and stores it into private members.
             */
            ppu();

        private:

            /**
             * @brief Character ROM, as read from cartridge
             */
            std::vector<uint8_t> char_rom;

            /**
             * @brief Delimited array of sprites and textures as stored in the ROM
             */
            uint8_t palette_table[32];

            /**
             * @brief Current VRAM data
             */
            uint8_t vram[2048];

            /**
             * @brief Current status of on-screen sprites
             */
            uint8_t oam_data[256];

            /**
             * @brief Mirror type, as read from cartridge
             */
            cartridge::mirroring mirror_type;
    };
}