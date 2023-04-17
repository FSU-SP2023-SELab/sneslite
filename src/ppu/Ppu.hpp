#pragma once

#include<vector>
#include<cstdint>

namespace sneslite
{
    class Bus;

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

        class status_register;

        class frame;

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
                uint8_t mirror_type;

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
                * @brief Temporary data buffer
                */
                uint8_t internal_data_buffer;

                /**
                * @brief Scanline to draw
                */
                uint16_t scanline;

                /**
                * @brief Cycle tracking
                */
                size_t cycles;
            };

            /**
            * @brief Construct a new Ppu object
            */
            Ppu();

            /**
            * @brief Set bus pointer variable to bus address
            */
            void connect_bus(Bus* n) { p_bus = n; }
            
            /**
            * @brief Read data into registers
            */
            uint8_t read_data();
            
            /**
            * @brief Expose address register
            *
            * @param data Data to send to the address register
            */
            void write_to_ar(uint8_t data);
            
            /**
            * @brief Expose control bus
            *
            * @param data Data to send to the control bus
            */
            void write_to_control(uint8_t data);
            
            /**
            * @brief Expose increment
            */
            void increment_vram_addr();

            /**
            * @brief Implementation of screenspace mirroring
            * 
            * @param addr Address to mirror
            */
            uint16_t mirror_vram_addr(uint16_t addr);

            /**
            * @brief Ticks through PPU 
            * 
            * @param cycles 
            * @return true, if cycles >= 262
            * @return false, if cycles < 341 
             */
            bool tick(uint8_t cycles);

        private:
            /**
            * @brief Pointer to parent bus
            */
            Bus *p_bus = nullptr;
            
            /**
            * @brief Pointer to address_register object for cross-referencing
            */
            address_register *p_ar;

            /**
            * @brief Pointer to controller_register object for cross-referencing
            */
            controller_register *p_cr;

            /**
            * @brief Pointer to status_register object
            */
            status_register *p_sr;

            /**
            * @brief TODO
            */
            frame *p_f;

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
            * @brief Update VRAM control register data
            */
            void update_vram_addr(uint8_t data);

            /**
            * @brief TODO
            * 
            * @internal
            */
            bool _contains(uint8_t flag) const;

            /**
            * @brief TODO
            */
            uint16_t sprt_pattern_addr() const;
            
            /**
            * @brief TODO
            */
            uint16_t bknd_pattern_addr() const;
            
            /**
            * @brief TODO
            */
            uint8_t sprite_size() const;
            
            /**
            * @brief TODO
            */
            uint8_t master_slave_select() const;
            
            /**
            * @brief TODO
            */
            bool generate_vblank_nmi() const;
            
        private:
            /**
            * @brief Controller register data
            */
            _data cr;
    };

    class Ppu::status_register : public Ppu
    {
        public:
            struct _data {
                /**
                * @brief TODO
                */
                uint8_t value;

                /**
                * @brief TODO
                */
                static const uint8_t NOTUSED          = 0b00000001;
                
                /**
                * @brief TODO
                */
                static const uint8_t NOTUSED2         = 0b00000010;
                
                /**
                * @brief TODO
                */
                static const uint8_t NOTUSED3         = 0b00000100;
                
                /**
                * @brief TODO
                */
                static const uint8_t NOTUSED4         = 0b00001000;
                
                /**
                * @brief TODO
                */
                static const uint8_t NOTUSED5         = 0b00010000;
                
                /**
                * @brief TODO
                */
                static const uint8_t SPRITE_OVERFLOW  = 0b00100000;
                
                /**
                * @brief TODO
                */
                static const uint8_t SPRITE_ZERO_HIT  = 0b01000000;
                
                /**
                * @brief TODO
                */
                static const uint8_t VBLANK_STARTED   = 0b10000000;
            };

            /**
            * @brief Construct a new status register object
            */
            status_register();

            /**
            * @brief TODO
            * 
            * @param flag 
            * @param status 
            */
            void _set(uint8_t flag, bool status);

            /**
            * @brief TODO
            * 
            * @param flag 
            */
            void _remove(uint8_t flag);

            /**
            * @brief TODO
            * 
            * @param flag 
            * @return true 
            * @return false 
            */
            bool _contains(uint8_t flag) const;

            /**
            * @brief TODO
            */
            void set_vblank_status(bool status);
            
            /**
            * @brief TODO
            */
            void set_sprite_zero_hit(bool status);
            
            /**
            * @brief TODO
            */
            void set_sprite_overflow(bool status);
            
            /**
            * @brief TODO
            */
            void reset_vblank_status();
            
            /**
            * @brief TODO
            */
            bool is_in_vblank() const;

            /**
            * @brief TODO
            */
            uint8_t snapshot() const;

        private:
            /**
            * @brief TODO
            */
            _data sr;

            /**
            * @brief Pointer to Ppu object for cross-referencing
            */
            Ppu *p_ppu;

            /**
            * @brief Pointer to address_register object for cross-referencing
            */
            address_register *p_ar;

            /**
            * @brief Pointer to controller_register object for cross-referencing
            */
            controller_register *p_cr;
    };

    class Ppu::frame : public Ppu
    {
        public:

            struct _data
            {
                /**
                * @brief TODO
                */
                std::vector<uint8_t> value;
                
                /**
                * @brief TODO
                */
                const uint8_t WIDTH  = 256;
                
                /**
                * @brief TODO
                */
                const uint8_t HEIGHT = 240;
            };

            frame();

            void set_pixel(size_t x, size_t y, std::tuple<uint8_t, uint8_t, uint8_t> rgb);

            std::vector<uint8_t> show_tile(std::vector<uint8_t> &char_rom, size_t bank, size_t tile_n);
        
        private:
            /**
            * @brief TODO
            */
            _data fd;
    };
}