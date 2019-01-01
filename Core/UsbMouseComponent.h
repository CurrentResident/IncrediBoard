#ifndef USB_MOUSE_COMPONENT_H_
#define USB_MOUSE_COMPONENT_H_

#include <stdint.h>

#include "BoardState.h"
#include "KeyCodes.h"
#include "Platform.h"
#include "UsbInterface.h"

class UsbMouseComponent
{
    public:

        UsbMouseComponent() :
            m_lastUpdateTime(Platform::GetMsec()),
            m_mouseX        (0),
            m_mouseY        (0),
            m_mouseState    (MOUSE_OFF)
        {
        }

        void MouseMotion(bool   i_upIsActive,
                         bool   i_downIsActive,
                         bool   i_leftIsActive,
                         bool   i_rightIsActive,
                         int8_t o_mouseX,
                         int8_t o_mouseY)
        {
            const unsigned long now = Platform::GetMsec();

            m_lastUpdateTime = now;
        }

        void Process(BoardState& io_state)
        {
            // Mouse emulation
            switch (m_mouseState)
            {
                case MOUSE_ON:
                    io_state.m_keyReportArray.clear();

                    m_mouseY = (io_state.m_activeKeyTable[IB_KEY_W] ? -2 :
                               (io_state.m_activeKeyTable[IB_KEY_S] ?  2 : 0));
                    m_mouseX = (io_state.m_activeKeyTable[IB_KEY_A] ? -2 :
                               (io_state.m_activeKeyTable[IB_KEY_D] ?  2 : 0));

                    UsbInterface::MouseMove(m_mouseX, m_mouseY);

                    UsbInterface::MouseSetButtons(((io_state.m_activeKeyTable[IB_KEY_COMMA]  or io_state.m_activeKeyTable[IB_KEY_DELETE])    ? 1 : 0) |
                                                  ((io_state.m_activeKeyTable[IB_KEY_SLASH]  or io_state.m_activeKeyTable[IB_KEY_PAGE_DOWN]) ? 2 : 0) |
                                                  ((io_state.m_activeKeyTable[IB_KEY_PERIOD] or io_state.m_activeKeyTable[IB_KEY_END])       ? 4 : 0));

                    if (not io_state.m_functionKey)
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

                default:                // fall-thru
                case MOUSE_OFF:

                    if (io_state.m_functionKey)
                    {
                        m_mouseState     = MOUSE_ON;
                        m_lastUpdateTime = Platform::GetMsec();
                    }
                    break;
            }
        }

    private:

        // Mouse state
        // ------------------------------------------------------------------------------
        enum MouseStateEnum
        {
            MOUSE_OFF,
            MOUSE_ON,
            MOUSE_TURNING_OFF
        };

        unsigned long   m_lastUpdateTime;
        uint8_t         m_mouseX;
        uint8_t         m_mouseY;
        MouseStateEnum  m_mouseState;

};

#endif
