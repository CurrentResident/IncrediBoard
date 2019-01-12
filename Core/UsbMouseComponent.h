#ifndef USB_MOUSE_COMPONENT_H_
#define USB_MOUSE_COMPONENT_H_

#include "BoardState.h"
#include "KeyCodes.h"
#include "MouseState.h"
#include "Platform.h"
#include "UsbInterface.h"

class UsbMouseComponent
{
    public:

        UsbMouseComponent() :
            m_mouseFrontStatePtr (&m_mouseState1),
            m_mouseBackStatePtr  (&m_mouseState2),
            m_mouseMode       (MOUSE_OFF)
        {
            UsbInterface::UpdateMouseState(*m_mouseBackStatePtr);
        }

        void Process(BoardState& io_state)
        {
            // Mouse emulation
            switch (m_mouseMode)
            {
                case MOUSE_ON:
                    io_state.m_keyReportArray.clear();

                    if (UsbInterface::GetTimeOfMostRecentMouseReport() != m_mouseFrontStatePtr->reportTime)
                    {
                        using std::swap;
                        swap(m_mouseFrontStatePtr, m_mouseBackStatePtr);
                    }

                    MouseStateType::MouseMotion(*m_mouseFrontStatePtr,
                                *m_mouseBackStatePtr,
                                io_state.m_activeKeyTable[IB_KEY_W] != 0,
                                io_state.m_activeKeyTable[IB_KEY_S] != 0,
                                io_state.m_activeKeyTable[IB_KEY_A] != 0,
                                io_state.m_activeKeyTable[IB_KEY_D] != 0,
                                ((io_state.m_activeKeyTable[IB_KEY_COMMA]  or io_state.m_activeKeyTable[IB_KEY_DELETE])    ? 1 : 0) |
                                ((io_state.m_activeKeyTable[IB_KEY_SLASH]  or io_state.m_activeKeyTable[IB_KEY_PAGE_DOWN]) ? 2 : 0) |
                                ((io_state.m_activeKeyTable[IB_KEY_PERIOD] or io_state.m_activeKeyTable[IB_KEY_END])       ? 4 : 0));

                    UsbInterface::UpdateMouseState(*m_mouseBackStatePtr);

                    if (not io_state.m_functionKey)
                    {
                        m_mouseMode = MOUSE_TURNING_OFF;
                    }
                    break;

                case MOUSE_TURNING_OFF:

                    m_mouseMode = MOUSE_OFF;

                    m_mouseState1 = MouseStateType();
                    m_mouseState2 = m_mouseState1;
                    m_mouseBackStatePtr->reportIsRequired = true;

                    UsbInterface::UpdateMouseState(*m_mouseBackStatePtr);
                    break;

                default:                // fall-thru
                case MOUSE_OFF:

                    if (io_state.m_functionKey)
                    {
                        m_mouseMode      = MOUSE_ON;
                        //m_mouseState1    = MouseStateType();
                        //m_mouseState2    = m_mouseState1;
                        m_mouseFrontStatePtr->reportTime = UsbInterface::GetTimeOfMostRecentMouseReport();
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

        MouseStateType  m_mouseState1;
        MouseStateType  m_mouseState2;
        MouseStateType* m_mouseFrontStatePtr;
        MouseStateType* m_mouseBackStatePtr;
        MouseModeEnum   m_mouseMode;
};

#endif
