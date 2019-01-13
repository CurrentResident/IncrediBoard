#ifndef USB_MOUSE_COMPONENT_H_
#define USB_MOUSE_COMPONENT_H_

#include "BoardState.h"
#include "KeyCodes.h"
#include "Platform.h"
#include "UsbInterface.h"

class UsbMouseComponent
{
    public:

        UsbMouseComponent() :
            m_mouseMode (MOUSE_OFF)
        {
        }

        void Process(BoardState& io_state)
        {
            // Mouse emulation
            switch (m_mouseMode)
            {
                case MOUSE_ON:
                    io_state.m_keyReportArray.clear();

                    if (UsbInterface::UpdateMouseState())
                    {
                        io_state.m_mouseState.MouseMotion(UsbInterface::GetMouseReportDeltaMsec(),
                                                          io_state.m_activeKeyTable[IB_KEY_W] != 0,
                                                          io_state.m_activeKeyTable[IB_KEY_S] != 0,
                                                          io_state.m_activeKeyTable[IB_KEY_A] != 0,
                                                          io_state.m_activeKeyTable[IB_KEY_D] != 0,
                                                          ((io_state.m_activeKeyTable[IB_KEY_COMMA]  or io_state.m_activeKeyTable[IB_KEY_DELETE])    ? 1 : 0) |
                                                          ((io_state.m_activeKeyTable[IB_KEY_SLASH]  or io_state.m_activeKeyTable[IB_KEY_PAGE_DOWN]) ? 2 : 0) |
                                                          ((io_state.m_activeKeyTable[IB_KEY_PERIOD] or io_state.m_activeKeyTable[IB_KEY_END])       ? 4 : 0));
                    }

                    if (not io_state.m_functionKey)
                    {
                        m_mouseMode = MOUSE_TURNING_OFF;
                    }
                    break;

                case MOUSE_TURNING_OFF:

                    m_mouseMode           = MOUSE_OFF;
                    io_state.m_mouseState = MouseStateType();
                    io_state.m_mouseState.reportIsRequired = true;

                    UsbInterface::UpdateMouseState();

                    break;

                default:                // fall-thru
                case MOUSE_OFF:

                    if (io_state.m_functionKey)
                    {
                        m_mouseMode           = MOUSE_ON;
                        io_state.m_mouseState = MouseStateType();
                        io_state.m_mouseState.reportIsRequired = true;

                        UsbInterface::UpdateMouseState();
                    }
                    break;
            }
        }

    private:

        // Mouse mode
        // ------------------------------------------------------------------------------
        enum MouseModeEnum
        {
            MOUSE_OFF,
            MOUSE_ON,
            MOUSE_TURNING_OFF
        };

        MouseModeEnum m_mouseMode;
};

#endif
