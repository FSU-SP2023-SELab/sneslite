#pragma once

#include<vector>
#include<cstdint>

#include "../cpu/Cpu.h"
#include "../cartridge/Cartridge.hpp"

namespace sneslite
{
    /**
    * @brief PPU rendering
    * 
    * TODO 
    * 
    * Source: https://www.nesdev.org/wiki/PPU
    */
    class Ppu
    {
        class address_register;

        class controller_register;

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
                Cartridge::mirroring mirror_type;

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
            * @brief Construct a new Ppu object
            */
            Ppu();

        private:
            /**
            * @brief Pointer to address_register object for cross-referencing
            */
            address_register *p_ar;

            /**
            * @brief Pointer to controller_register object for cross-referencing
            */
            controller_register *p_cr;

            /**
            * @brief PPU data
            */
            _data pd;
    };

    class Ppu::address_register : public Ppu
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
                * @brief Address register data
                */
                uint8_t value[2];

                /**
                * @brief Bool to indicate which set of bits to access
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
            * 
            * @return uint16_t ar.value
            */
            uint16_t get_addr_value();

        private:
            /**
            * @brief Pointer to Ppu object for cross-referencing
            */
            Ppu *p_ppu;

            /**
             * @brief Pointer to controller_register object for cross-referencing
             */
            controller_register *p_cr;

            /**
            * @brief Address register data
            */
            _data ar;
    };

    class Ppu::controller_register : public Ppu
    {
        public:
            /**
            * @brief Controller registers on PPU
            * 
            * @warning This struct is for internal use only!
            */
            struct _data
            {
                /**
                * @brief Data on register
                */
                uint8_t value;

                /**
                * @brief Base nametable address
                */
                static const uint8_t NAMETABLE1              = 0b00000001;

                /**
                * @brief Base nametable address
                */
                static const uint8_t NAMETABLE2              = 0b00000010;

                /**
                * @brief VRAM increment after CPU read/write of PPU _data
                */
                static const uint8_t VRAM_ADD_INCREMENT      = 0b00000100;

                /**
                * @brief Sprite pattern address
                */
                static const uint8_t SPRITE_PATTERN_ADDR     = 0b00001000;

                /**
                * @brief Background pattern address
                */
                static const uint8_t BACKROUND_PATTERN_ADDR  = 0b00010000;
                
                /**
                * @brief Size of sprite (0: 8x8, 1: 16x16)
                */
                static const uint8_t SPRITE_SIZE             = 0b00100000;

                /**
                * @brief Master/slave select
                */
                static const uint8_t MASTER_SLAVE_SELECT     = 0b01000000;

                /**
                * @brief Generate non-maskable interrupt (0: off, 1: on)
                */
                static const uint8_t GENERATE_NMI            = 0b10000000;
            };

            /**
            * @brief Construct a new controller register object
            */
            controller_register();

            /**
            * @brief Increments VRAM address depending on VRAM_ADD_INCREMENT
            * 
            * @return 1 or 32
            */
            uint8_t increment_vram_addr();

            /**
            * @brief 
            */
           void update_vram_addr(uint8_t data);

        private:
            /**
            * @brief Pointer to Ppu object for cross-referencing
            */
            Ppu *p_ppu;

            /**
            * @brief Pointer to address_register object for cross-referencing
            */
            address_register *p_ar;

            /**
            * @brief Controller register data
            */
            _data cr;
    };
}