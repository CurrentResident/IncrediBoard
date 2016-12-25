#ifndef BOARD_CONTROLLER_H_
#define BOARD_CONTROLLER_H_

#include <stdint.h>

#include "FixedArray.h"
#include "KeyCodes.h"
#include "Platform.h"

class BoardController
{
    private:

        // Mouse state
        // ------------------------------------------------------------------------------
        enum MouseStateEnum
        {
            MOUSE_OFF,
            MOUSE_ON,
            MOUSE_TURNING_OFF
        };
        uint8_t         m_mouseX;
        uint8_t         m_mouseY;
        MouseStateEnum  m_mouseState;

        // Reboot state
        // ------------------------------------------------------------------------------
        bool          m_isRebootingToBootloader;    ///< Indicates we're going to the bootloader shortly.
        unsigned long m_bootLoaderJumpTime;         ///< The time in msec that we'll make the actual jump.

        // TODO: NKRO.  Until then, keep things really simple...

    public:

        BoardController() :
            m_mouseX                  (0),
            m_mouseY                  (0),
            m_mouseState              (MOUSE_OFF),
            m_isRebootingToBootloader (false),
            m_bootLoaderJumpTime      (0)
        {
        }

        void Process()
        {
            //TODO:  Fancy features?
            //

            // TODO: Carve features off into a generic fusion collection defined in board-specific area.

            // Mouse emulation
            switch (m_mouseState)
            {
                case MOUSE_ON:
                    m_keyReportArray.clear();

                    m_mouseY = (m_activeKeyTable[KEY_W] ? -2 :
                               (m_activeKeyTable[KEY_S] ?  2 : 0));
                    m_mouseX = (m_activeKeyTable[KEY_A] ? -2 :
                               (m_activeKeyTable[KEY_D] ?  2 : 0));

                    UsbInterface::MouseMove(m_mouseX, m_mouseY);

                    UsbInterface::MouseSetButtons(((m_activeKeyTable[KEY_COMMA]  or m_activeKeyTable[KEY_DELETE])    ? 1 : 0) |
                                                  ((m_activeKeyTable[KEY_SLASH]  or m_activeKeyTable[KEY_PAGE_DOWN]) ? 2 : 0) |
                                                  ((m_activeKeyTable[KEY_PERIOD] or m_activeKeyTable[KEY_END])       ? 4 : 0));

                    if (not m_functionKey)
                    {
                        m_mouseState = MOUSE_TURNING_OFF;
                    }
                    break;

                case MOUSE_TURNING_OFF:
                    m_mouseState = MOUSE_OFF;
                    m_mouseX     = 0;
                    m_mouseY     = 0;
                    UsbInterface::MouseMove(m_mouseX, m_mouseY);
                    UsbInterface::MouseSetButtons(0);
                    break;

                default:
                case MOUSE_OFF:

                    if (m_functionKey)
                    {
                        m_mouseState = MOUSE_ON;
                    }
                    break;
            }

            // Four-finger salute to put the keyboard into the bootloader.  Not concerned about latching this.
            // Once all four keys are down, the keyboard reports all keys cleared/reset, and the reboot happens
            // some amount time after the keys are physically released, much like a proper reset button's behavior.
            if (m_activeKeyTable[KEY_LEFT_CTRL]  and
                m_activeKeyTable[KEY_LEFT_SHIFT] and
                m_activeKeyTable[KEY_TAB]        and
                m_activeKeyTable[KEY_BACKSPACE])
            {
                // Don't jump immediately.  Allow a second to pass so that we can reset the key reports.
                // Otherwise the OS thinks the board is just holding down the keys when really it's in the
                // bootloader.
                m_isRebootingToBootloader = true;
                m_bootLoaderJumpTime      = Platform::GetMsec() + 1000;
            }

            if (m_isRebootingToBootloader)
            {
                m_keyReportArray.clear();
                m_modifiers = 0;

                if (Platform::GetMsec() > m_bootLoaderJumpTime)
                {
                    // No return!
                    Platform::JumpToBootloader();
                }
            }

        }
};

#endif
