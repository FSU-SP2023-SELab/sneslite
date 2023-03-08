#pragma once

#include<vector>
#include<cstdint>

#include "../cpu/Bus.h"

namespace sneslite
{
    /**
     * @brief PPU rendering
     * 
     * TODO 
     * 
     * Source: https://www.nesdev.org/wiki/PPU
     */
    class ppu
    {
        class address_register;

        public:
            /**
            * @brief Data storage for PPU
            * 
            * @warning This struct is for internal use only!
            */
            struct _data
            {
                /**
                * @brief Character ROM, as read from cartridge
                */
                std::vector<uint8_t> char_rom;

                /**
                * @brief Mirror type, as read from cartridge
                */
                cartridge::mirroring mirror_type;

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
            };

            /**
            * @brief Construct a new ppu object
            */
            ppu();

        private:
            /**
            * @brief Pointer to address_register object for cross-referencing
            */
            address_register *p_ar;

            /**
             * @brief PPU data
             */
            _data pd;
    };

    class ppu::address_register : public ppu
    {
        public:
            /**
            * @brief Address registers on PPU
            * 
            * @warning This struct is for internal use only!
            */
            struct _data
            {
                /**
                * @brief TODO
                */
                uint8_t value[2];

                /**
                * @brief TODO
                */
                bool hi_ptr;
            };

            /**
            * @brief Construct a new address register object
            */
            address_register();
            
            /**
            * @brief Set the address_register object
            * 
            * @param data 
            */
            void set_addr(uint16_t data);

            /**
            * @brief Update the address register
            * 
            * @param data 
            */
            void update_addr(uint8_t data);

            /**
            * @brief Increment the register
            * 
            * @param inc 
            */
            void increment_addr(uint8_t inc);

            /**
            * @brief Set hi_ptr to true
            */
            void reset_latch();

            /**
            * @brief Get the address_register value
            */
            void get_addr_value();

        private:
            /**
            * @brief Pointer to ppu object for cross-referencing
            */
            ppu *p_ppu;

            /**
            * @brief Address register data
            */
            _data ar;
    };
}