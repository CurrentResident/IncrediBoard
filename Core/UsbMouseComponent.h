#ifndef USB_MOUSE_COMPONENT_H_
#define USB_MOUSE_COMPONENT_H_

#include <cmath>
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
            m_lastUpdateTime  (Platform::GetMsec()),
            m_mouseUnitVectors{ { { std::cos(M_PI * 0.75), std::sin(M_PI * 0.75) }, {  0l,  1l }, { std::cos(M_PI * 0.25), std::sin(M_PI * 0.25) } },
                                { {                   -1l,                    0l }, {  0l,  0l }, {                    1l,                    0l } },
                                { { std::cos(M_PI * 1.25), std::sin(M_PI * 1.25) }, {  0l, -1l }, { std::cos(M_PI * 1.75), std::sin(M_PI * 1.75) } } },
            m_mouseMode       (MOUSE_OFF)
        {
        }

        bool MouseMotion(bool i_upIsActive,
                         bool i_downIsActive,
                         bool i_leftIsActive,
                         bool i_rightIsActive)
        {
            const unsigned long   now            = Platform::GetMsec();
            const SignedFixedType deltaMsec      = now - m_lastUpdateTime;
            const SignedFixedType deltaTSeconds  = deltaMsec / 1000l;

            const SignedFixedType MAX_VELOCITY = 1000l;          // In units per second.
            const SignedFixedType ACCELERATION = 1000l;

            const int row = 1 + (i_upIsActive   *  1) + (i_downIsActive  * -1);
            const int col = 1 + (i_leftIsActive * -1) + (i_rightIsActive *  1);

            bool motionReportIsRequired = false;

            if (row == 1 and col == 1)
            {
                // If we're stopping the mouse, we report the 0, 0 motion.
                if (m_mouseState.velocity.GetRaw() != 0)
                {
                    motionReportIsRequired = true;
                }

                m_mouseState.velocity = 0l;
            }
            else
            {
                m_mouseState.velocity = std::min(MAX_VELOCITY, m_mouseState.velocity + ACCELERATION * deltaTSeconds);
            }

            m_mouseState.position += m_mouseUnitVectors[row][col] * (m_mouseState.velocity * deltaTSeconds);

            m_mouseState.position.x.Round(m_mouseState.reportDeltaX);
            m_mouseState.position.y.Round(m_mouseState.reportDeltaY);

            if (m_mouseState.reportDeltaX != 0)
            {
                motionReportIsRequired = true;
                m_mouseState.position.x -= m_mouseState.reportDeltaX;
            }

            if (m_mouseState.reportDeltaY != 0)
            {
                motionReportIsRequired = true;
                m_mouseState.position.y -= m_mouseState.reportDeltaY;
            }

            m_lastUpdateTime = now;

            return motionReportIsRequired;
        }

        void Process(BoardState& io_state)
        {
            // Mouse emulation
            switch (m_mouseMode)
            {
                case MOUSE_ON:
                    io_state.m_keyReportArray.clear();

                    if (MouseMotion(io_state.m_activeKeyTable[IB_KEY_W] != 0,
                                    io_state.m_activeKeyTable[IB_KEY_S] != 0,
                                    io_state.m_activeKeyTable[IB_KEY_A] != 0,
                                    io_state.m_activeKeyTable[IB_KEY_D] != 0))
                    {
                        UsbInterface::MouseMove(m_mouseState.reportDeltaX,
                                                m_mouseState.reportDeltaY);
                    }

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
        //typedef FixedPoint<int32_t, int64_t, 16> SignedFixedType;      // 16.16

        // 22.10 fixed point.  When multiplied, this leaves 12 bits for the integer part of the result, or
        // for the numerator when divided, but it gives enough precision for the fractional part to represent
        // thousandths of a second.
        typedef FixedPoint<int32_t, int32_t, 10> SignedFixedType;      // 22.10

        typedef Vector2<SignedFixedType> VectorType;

        struct MouseStateType
        {
            VectorType      position;
            SignedFixedType velocity;
            int8_t          reportDeltaX;    ///< The motion X component reported on USB.
            int8_t          reportDeltaY;    ///< The motion Y component reported on USB.

            MouseStateType() :
                reportDeltaX(0),
                reportDeltaY(0)
            {
            }
        };

        unsigned long   m_lastUpdateTime;
        MouseStateType  m_mouseState;
        VectorType      m_mouseUnitVectors[3][3];           // [row][col]
        MouseModeEnum   m_mouseMode;
};

#endif
