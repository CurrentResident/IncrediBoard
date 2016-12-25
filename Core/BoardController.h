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

        // TODO: NKRO.  Until then, keep things really simple...

    public:

        BoardController() :
            m_mouseX                  (0),
            m_mouseY                  (0),
            m_mouseState              (MOUSE_OFF),
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
        }
};

#endif
