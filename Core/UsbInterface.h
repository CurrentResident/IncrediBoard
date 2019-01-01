#ifndef USB_INTERFACE_H_
#define USB_INTERFACE_H_

#include <stdint.h>

namespace UsbInterface
{
    void Init();

    void Process(const uint8_t* i_keycodes, uint8_t i_keycodeCount, uint8_t i_modifiers);

    void MouseSetButtons(uint8_t i_buttonBitset);
    void MouseMove(int8_t i_mouseX, int8_t i_mouseY);
}

#endif
