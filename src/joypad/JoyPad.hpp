#include <cstdint>

namespace sneslite
{
    enum JoyPadButton : uint8_t {
        RIGHT   = 0b10000000,
        LEFT    = 0b01000000,
        DOWN    = 0b00100000,
        UP      = 0b00010000,
        START   = 0b00001000,
        SELECT  = 0b00000100,
        BUTTON_B= 0b00000010,
        BUTTON_A= 0b00000001
    };

    class JoyPad
    {
        public:
            JoyPad();
            ~JoyPad();

            uint8_t read();
            void write(uint8_t data);
            void set_button_status(JoyPadButton button, bool pressed);

        private:
            bool strobe;
            uint8_t button_index;
            JoyPadButton button_status;
    };
} 
