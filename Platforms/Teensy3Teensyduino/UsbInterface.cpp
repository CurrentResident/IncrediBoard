
#include "UsbInterface.h"

#include <algorithm>
#include <cstring>

#include "Platform.h"

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
    unsigned long s_timeOfLastMouseReport;
    unsigned long s_mouseReportDeltaMsec;
    bool          s_mouseIsUpdated;
}

namespace UsbInterface
{
    void Init()
    {
        // usb_init() is called by the core _init_Teensyduino_internal_ in pins_teensy.c,
        // so there's no need to do it here.
    }

    void Process(const uint8_t*  i_keycodes,
                 uint8_t         i_keycodeCount,
                 uint8_t         i_modifiers,
                 MouseStateType& io_mouseState)
    {
        const bool isCurrentlyRolledover    = s_keycodesCount > 6;
        const bool keyboardReportIsRequired = s_keycodesCount != i_keycodeCount or
                                              s_modifiers     != i_modifiers    or
                                              not (isCurrentlyRolledover or
                                                    std::equal(i_keycodes, i_keycodes + i_keycodeCount,
                                                               keyboard_keys));

        if (keyboardReportIsRequired)
        {
            s_keycodesCount   =  i_keycodeCount;
            s_keycodesPointer = (i_keycodeCount > 6 ? s_keycodesRollOverError : i_keycodes);
            s_modifiers       =  i_modifiers;

            // Set the TD usb_keyboard data interfaces.
            std::copy_n(s_keycodesPointer, 6, keyboard_keys);
            keyboard_modifier_keys = s_modifiers;

            usb_keyboard_send();
        }

        if (io_mouseState.reportIsRequired)
        {
            io_mouseState.reportIsRequired = false;

            usb_mouse_buttons_state = io_mouseState.buttons;
            usb_mouse_move(io_mouseState.reportDeltaX, io_mouseState.reportDeltaY, 0, 0);
        }

        const unsigned long now = Platform::GetMsec();
        s_mouseReportDeltaMsec  = now - s_timeOfLastMouseReport;
        s_timeOfLastMouseReport = now;

        s_mouseIsUpdated = true;
    }


    bool UpdateMouseState()
    {
        if (s_mouseIsUpdated)
        {
            s_mouseIsUpdated = false;
            return true;
        }

        return false;
    }

    unsigned long GetMouseReportDeltaMsec()
    {
        return s_mouseReportDeltaMsec;
    }

}
