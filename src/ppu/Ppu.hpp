#pragma once

#include<vector>
#include<cstdint>
#include<memory>

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
            * @brief Pointer to frame object
            */
            frame *p_f;

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
                uint8_t mirror_type = 0;

                /**
                * @brief Delimited array of sprites and textures as stored in the ROM
                */
                uint8_t palette_table[32] = {0};

                /**
                * @brief Current VRAM data
                */
                uint8_t vram[2048] = {0};

                /**
                * @brief Current status of on-screen sprites
                */
                uint8_t oam_data[256] = {0};

                /**
                * @brief Temporary data buffer
                */
                uint8_t internal_data_buffer = 0;

                /**
                * @brief Scanline to draw
                */
                uint16_t scanline = 0;

                /**
                * @brief Cycle tracking
                */
                size_t cycles = 0;
            };

            Ppu();

            ~Ppu();

            /**
            * @brief Called by the bus when prior modules have been loaded
            */
            void initialize_ppu();

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
            * @brief Check if bit contains flag
            * 
            * @internal
            */
            bool _contains(uint8_t flag) const;

            /**
            * @brief Return sprite pattern address
            */
            uint16_t sprt_pattern_addr() const;
            
            /**
            * @brief Return background pattern address
            */
            uint16_t bknd_pattern_addr() const;
            
            /**
            * @brief Return sprite size
            */
            uint8_t sprite_size() const;
            
            /**
            * @brief Return master/slave bitflag
            */
            uint8_t master_slave_select() const;
            
            /**
            * @brief Set vblank bitflag for next frame
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
                * @brief Status register value
                */
                uint8_t value;

                /**
                * @brief Unused bit
                */
                static const uint8_t NOTUSED          = 0b00000001;
                
                /**
                * @brief Unused bit
                */
                static const uint8_t NOTUSED2         = 0b00000010;
                
                /**
                * @brief Unused bit
                */
                static const uint8_t NOTUSED3         = 0b00000100;
                
                /**
                * @brief Unused bit
                */
                static const uint8_t NOTUSED4         = 0b00001000;
                
                /**
                * @brief Unused bit
                */
                static const uint8_t NOTUSED5         = 0b00010000;
                
                /**
                * @brief Bitflag for sprite overflow
                */
                static const uint8_t SPRITE_OVERFLOW  = 0b00100000;
                
                /**
                * @brief Bitflag for zero hit
                */
                static const uint8_t SPRITE_ZERO_HIT  = 0b01000000;
                
                /**
                * @brief Bitflag for vblank
                */
                static const uint8_t VBLANK_STARTED   = 0b10000000;
            };

            /**
            * @brief Construct a new status register object
            */
            status_register();

            /**
            * @brief Set status register
            * 
            * @param flag 
            * @param status 
            */
            void _set(uint8_t flag, bool status);

            /**
            * @brief Remove bitflag
            * 
            * @param flag 
            */
            void _remove(uint8_t flag);

            /**
            * @brief Check if bitflag contains other bit
            * 
            * @param flag 
            * @return true 
            * @return false 
            */
            bool _contains(uint8_t flag) const;

            /**
            * @brief Set vblank bitflag
            * 
            * @param status
            */
            void set_vblank_status(bool status);
            
            /**
            * @brief Set zero hit bitflag
            * 
            * @param status
            */
            void set_sprite_zero_hit(bool status);
            
            /**
            * @brief Set sprite overflow bitflag
            * 
            * @param status
            */
            void set_sprite_overflow(bool status);
            
            /**
            * @brief Set vblank to zero
            */
            void reset_vblank_status();
            
            /**
            * @brief Check if PPU is in vblank
            * 
            * @return true, if in vblank
            */
            bool is_in_vblank() const;

            /**
            * @brief Return status register value
            * 
            * @return uint8_t sr.value
            */
            uint8_t snapshot() const;

        private:
            /**
            * @brief TODO
            */
            _data sr;
    };

    class Ppu::frame : public Ppu
    {
        public:

            struct _data
            {
                /**
                * @brief Container for all pixels on frame
                */
                std::vector<uint8_t> value;
                
                /**
                * @brief Width of frame
                */
                const uint16_t WIDTH  = 256;
                
                /**
                * @brief Height of frame
                */
                const uint16_t HEIGHT = 240;
            };

            /**
            * @brief Frame object constructor 
            */
            frame();

            /**
            * @brief Setter for frame data value
            * 
            * @param x x position
            * @param y y position
            * @param rgb Color data for pixel
            */
            void set_pixel(size_t x, size_t y, std::tuple<uint8_t, uint8_t, uint8_t> rgb);

            /**
            * @brief Getter for frame data value, sequentially
            * 
            * @param char_rom Cartridge character ROM
            * @param bank Memory bank location
            * @param tile_n Tile number to fetch
            * 
            * @return _data.value vector
            */
            std::vector<uint8_t> show_tile(std::vector<uint8_t> &char_rom, size_t bank, size_t tile_n);

            /**
            * @brief TODO
            */
            void render();

            /**
            * @brief Getter for frame data value, without returning whole tile
            */
            std::vector<uint8_t> get_frame_data();
        
        private:
            /**
            * @brief TODO
            */
            _data fd;
    };
}