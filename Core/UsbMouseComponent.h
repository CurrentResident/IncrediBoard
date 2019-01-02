#ifndef USB_MOUSE_COMPONENT_H_
#define USB_MOUSE_COMPONENT_H_

#include <stdint.h>

#include "BoardState.h"
#include "FixedPoint.h"
#include "KeyCodes.h"
#include "Platform.h"
#include "UsbInterface.h"
#include "Vector2.h"

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
            const SignedFixedType deltaMsec = now - m_lastUpdateTime;

            const SignedFixedType deltaTSeconds  = deltaMsec / 1000;

            const SignedFixedType MAX_VELOCITY = 1000;          // In units per second.

            const SignedFixedType actualVelocity = MAX_VELOCITY * deltaTSeconds;

            m_mouseState.velocity.x  = i_rightIsActive ? actualVelocity : 0;
            m_mouseState.velocity.x -= i_leftIsActive  ? actualVelocity : 0;

            m_mouseState.velocity.y  = i_downIsActive ? actualVelocity : 0;
            m_mouseState.velocity.y -= i_upIsActive   ? actualVelocity : 0;

            m_mouseState.position += m_mouseState.velocity;

            const VectorType deltaSinceReport = m_mouseState.position;// - m_mouseState.positionAtPreviousReport;

            //m_mouseState.reportDeltaX = static_cast<int8_t>(deltaSinceReport.x);
            //m_mouseState.reportDeltaY = static_cast<int8_t>(deltaSinceReport.y);

            deltaSinceReport.x.Round(m_mouseState.reportDeltaX);
            deltaSinceReport.y.Round(m_mouseState.reportDeltaY);

            if (m_mouseState.reportDeltaX != 0)
            {
                m_mouseState.position.x = SignedFixedType();
                //m_mouseState.positionXAtPreviousReport = m_mouseState.positionX;
            }

            if (m_mouseState.reportDeltaY != 0)
            {
                m_mouseState.position.y = SignedFixedType();
                //m_mouseState.positionYAtPreviousReport = m_mouseState.positionY;
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

        //typedef FixedPoint<int16_t, int16_t, 4> SignedFixedType;     // 12.4
        //typedef FixedPoint<int32_t, int32_t, 8> SignedFixedType;      // 24.8
        typedef FixedPoint<int32_t, int64_t, 16> SignedFixedType;      // 16.16

        typedef Vector2<SignedFixedType> VectorType;

        struct MouseStateType
        {
            VectorType  position;
            VectorType  velocity;
            //VectorType positionAtPreviousReport;
            /*
            int32_t positionX;      ///< Signed 16.16 fixed point.
            int32_t positionY;      ///< Signed 16.16 fixed point.
            int32_t velocityX;      ///< Signed 16.16 fixed point.
            int32_t velocityY;      ///< Signed 16.16 fixed point.

            int32_t positionXAtPreviousReport;
            int32_t positionYAtPreviousReport;
*/
            int8_t reportDeltaX;    ///< The motion X component reported on USB.
            int8_t reportDeltaY;    ///< The motion Y component reported on USB.

            MouseStateType() :
                /*
                positionX                (0),
                positionY                (0),
                velocityX                (0),
                velocityY                (0),
                positionXAtPreviousReport(0),
                positionYAtPreviousReport(0),
                */
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
