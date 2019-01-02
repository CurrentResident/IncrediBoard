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
            m_mouseMode     (MOUSE_OFF)
        {
        }

        void MouseMotion(bool    i_upIsActive,
                         bool    i_downIsActive,
                         bool    i_leftIsActive,
                         bool    i_rightIsActive)
        {
            const unsigned long now       = Platform::GetMsec();
            const int64_t       deltaMsec = static_cast<int64_t>(now - m_lastUpdateTime) << 16;

            const int64_t deltaTSeconds  = (deltaMsec << 16) / (1000 << 16);    // The numerator needs another half-shift for FP-divide.

            const int64_t MAX_VELOCITY = 1000 << 16;          // In units per second.

            const int32_t actualVelocity = static_cast<int32_t>((MAX_VELOCITY * deltaTSeconds) >> 16);

            m_mouseState.velocityX  = i_rightIsActive ? actualVelocity : 0;
            m_mouseState.velocityX -= i_leftIsActive  ? actualVelocity : 0;

            m_mouseState.velocityY  = i_downIsActive ? actualVelocity : 0;
            m_mouseState.velocityY -= i_upIsActive   ? actualVelocity : 0;

            m_mouseState.positionX += m_mouseState.velocityX;
            m_mouseState.positionY += m_mouseState.velocityY;

            const int32_t POINT_FIVE = 1 << 15;

            m_mouseState.reportDeltaX = static_cast<int8_t>((m_mouseState.positionX - m_mouseState.positionXAtPreviousReport + POINT_FIVE) >> 16);
            m_mouseState.reportDeltaY = static_cast<int8_t>((m_mouseState.positionY - m_mouseState.positionYAtPreviousReport + POINT_FIVE) >> 16);

            if (m_mouseState.reportDeltaX != 0)
            {
                m_mouseState.positionXAtPreviousReport = m_mouseState.positionX;
            }

            if (m_mouseState.reportDeltaY != 0)
            {
                m_mouseState.positionYAtPreviousReport = m_mouseState.positionY;
            }

            m_lastUpdateTime = now;
        }

        void Process(BoardState& io_state)
        {
            // Mouse emulation
            switch (m_mouseMode)
            {
                case MOUSE_ON:
                    io_state.m_keyReportArray.clear();

                    MouseMotion(io_state.m_activeKeyTable[IB_KEY_W] != 0,
                                io_state.m_activeKeyTable[IB_KEY_S] != 0,
                                io_state.m_activeKeyTable[IB_KEY_A] != 0,
                                io_state.m_activeKeyTable[IB_KEY_D] != 0);

                    UsbInterface::MouseMove(m_mouseState.reportDeltaX,
                                            m_mouseState.reportDeltaY);

                    UsbInterface::MouseSetButtons(((io_state.m_activeKeyTable[IB_KEY_COMMA]  or io_state.m_activeKeyTable[IB_KEY_DELETE])    ? 1 : 0) |
                                                  ((io_state.m_activeKeyTable[IB_KEY_SLASH]  or io_state.m_activeKeyTable[IB_KEY_PAGE_DOWN]) ? 2 : 0) |
                                                  ((io_state.m_activeKeyTable[IB_KEY_PERIOD] or io_state.m_activeKeyTable[IB_KEY_END])       ? 4 : 0));

                    if (not io_state.m_functionKey)
                    {
                        m_mouseMode = MOUSE_TURNING_OFF;
                    }
                    break;

                case MOUSE_TURNING_OFF:

                    m_mouseMode = MOUSE_OFF;

                    UsbInterface::MouseMove(0, 0);
                    UsbInterface::MouseSetButtons(0);
                    break;

                default:                // fall-thru
                case MOUSE_OFF:

                    if (io_state.m_functionKey)
                    {
                        m_mouseState     = MouseStateType();
                        m_mouseMode      = MOUSE_ON;
                        m_lastUpdateTime = Platform::GetMsec();
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

        struct MouseStateType
        {
            int32_t positionX;      ///< Signed 16.16 fixed point.
            int32_t positionY;      ///< Signed 16.16 fixed point.
            int32_t velocityX;      ///< Signed 16.16 fixed point.
            int32_t velocityY;      ///< Signed 16.16 fixed point.

            int32_t positionXAtPreviousReport;
            int32_t positionYAtPreviousReport;

            int8_t reportDeltaX;    ///< The motion X component reported on USB.
            int8_t reportDeltaY;    ///< The motion Y component reported on USB.

            MouseStateType() :
                positionX                (0),
                positionY                (0),
                velocityX                (0),
                velocityY                (0),
                positionXAtPreviousReport(0),
                positionYAtPreviousReport(0),
                reportDeltaX             (0),
                reportDeltaY             (0)
            {
            }
        };

        unsigned long   m_lastUpdateTime;
        MouseStateType  m_mouseState;
        MouseModeEnum   m_mouseMode;
};

#endif
