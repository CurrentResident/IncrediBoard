
#include "UsbInterface.h"

#include <cstring>

#include "usb_dev.h"

#include "usb_serial.h"
#include "usb_seremu.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "usb_joystick.h"
#include "usb_midi.h"
#include "usb_rawhid.h"
#include "usb_flightsim.h"
#include "usb_mtp.h"
#include "usb_audio.h"
#include "usb_touch.h"
#include "usb_undef.h" // do not allow usb_desc.h stuff to leak to user programs

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
        // usb_init() is called by the core _init_Teensyduino_internal_ in pins_teensy.c,
        // so there's no need to do it here.
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
        s_keycodesCount   =  i_keycodeCount;
        s_keycodesPointer = (i_keycodeCount > 6 ? s_keycodesRollOverError : i_keycodes);
        s_modifiers       =  i_modifiers;

        // Set the TD usb_keyboard data interfaces.
        std::memcpy(keyboard_keys, s_keycodesPointer, 6);
        keyboard_modifier_keys = s_modifiers;

        usb_keyboard_send();
    }
}
