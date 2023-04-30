#include <cstdint>
#include "joypad.hpp"

namespace sneslite
{
    JoyPad::JoyPad() : strobe(false), button_index(0), button_status(static_cast<JoyPadButton>(0)) {}

    void JoyPad::write(uint8_t data) {
        strobe = (data & 1) == 1;
        if (strobe) {
            button_index = 0;
        }
    }

    uint8_t JoyPad::read() {
        if (button_index > 7) {
            return 1;
        }
        uint8_t response = (button_status & (1 << button_index)) >> button_index;
        if (!strobe && button_index <= 7) {
            button_index += 1;
        }
        return response;
    }

    void JoyPad::set_button_status(JoyPadButton button, bool pressed) {
        if (pressed) {
            button_status = static_cast<JoyPadButton>(button_status | button);
        } else {
            button_status = static_cast<JoyPadButton>(button_status & ~button);
        }
    }
}