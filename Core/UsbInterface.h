#ifndef USB_INTERFACE_H_
#define USB_INTERFACE_H_

#include <stdint.h>

namespace UsbInterface
{
    void Init();

    void Process(const uint8_t* i_keycodes, uint8_t i_keycodeCount, uint8_t i_modifiers);
}

#endif
