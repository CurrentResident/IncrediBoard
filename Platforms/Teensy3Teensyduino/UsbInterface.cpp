
#include "UsbInterface.h"

namespace
{
    // Keyboard bookkeeping
    const uint8_t   s_keycodesRollOverError[6] = {1, 1, 1, 1, 1, 1};
    const uint8_t*  s_keycodesPointer;
    uint8_t         s_keycodesCount;
    uint8_t         s_modifiers;

    // Mouse bookkeeping
    uint8_t s_mouseButtons;
    uint8_t s_mouseX;
    uint8_t s_mouseY;
}

namespace UsbInterface
{
    void Init()
    {
    }

    void MouseSetButtons(uint8_t i_buttonBitset)
    {
        s_mouseButtons = i_buttonBitset;
    }

    void MouseMove(uint8_t i_mouseX, uint8_t i_mouseY)
    {
        s_mouseX = i_mouseX;
        s_mouseY = i_mouseY;
    }

    void Process(const uint8_t* i_keycodes, uint8_t i_keycodeCount, uint8_t i_modifiers)
    {
        s_keycodesPointer = i_keycodes;
        s_keycodesCount   = i_keycodeCount;
        s_modifiers       = i_modifiers;
    }
}
