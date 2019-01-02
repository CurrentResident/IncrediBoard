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
                                { { -1l,  0l }, { 0l,  0l }, {  1l,  0l } },
                                { { std::cos(M_PI * 1.25), std::sin(M_PI * 1.25) }, {  0l, -1l }, { std::cos(M_PI * 1.75), std::sin(M_PI * 1.75) } } },
            m_mouseMode       (MOUSE_OFF)
        {
            //m_mouseUnitVectors = ;

                /*
            m_mouseUnitVectors[DEG_0]   = {  1l,  0l };
            m_mouseUnitVectors[DEG_90]  = {  0l,  1l };
            m_mouseUnitVectors[DEG_180] = { -1l,  0l };
            m_mouseUnitVectors[DEG_270] = {  0l, -1l };

            m_mouseUnitVectors[DEG_45]  = { std::cos(M_PI * 0.25), std::sin(M_PI * 0.25) };
            m_mouseUnitVectors[DEG_135] = { std::cos(M_PI * 0.75), std::sin(M_PI * 0.75) };
            m_mouseUnitVectors[DEG_225] = { std::cos(M_PI * 1.25), std::sin(M_PI * 1.25) };
            m_mouseUnitVectors[DEG_315] = { std::cos(M_PI * 1.75), std::sin(M_PI * 1.75) };
            */
        }

        void MouseMotion(bool i_upIsActive,
                         bool i_downIsActive,
                         bool i_leftIsActive,
                         bool i_rightIsActive)
        {
            const unsigned long   now            = Platform::GetMsec();
            const SignedFixedType deltaMsec      = now - m_lastUpdateTime;
            const SignedFixedType deltaTSeconds  = deltaMsec / 1000l;

            const SignedFixedType MAX_VELOCITY = 1000l;          // In units per second.

            const SignedFixedType actualVelocity = MAX_VELOCITY * deltaTSeconds;

            const int row = 1 + (i_upIsActive * 1) + (i_downIsActive * -1);
            const int col = 1 + (i_leftIsActive * -1) + (i_rightIsActive * 1);

            m_mouseState.velocity = m_mouseUnitVectors[row][col];

            /*
            m_mouseState.velocity.x  = i_rightIsActive ? actualVelocity : 0l;
            m_mouseState.velocity.x -= i_leftIsActive  ? actualVelocity : 0l;

            m_mouseState.velocity.y  = i_downIsActive ? actualVelocity : 0l;
            m_mouseState.velocity.y -= i_upIsActive   ? actualVelocity : 0l;
            */

            m_mouseState.position += m_mouseState.velocity;

            const VectorType deltaSinceReport = m_mouseState.position;

            deltaSinceReport.x.Round(m_mouseState.reportDeltaX);
            deltaSinceReport.y.Round(m_mouseState.reportDeltaY);

            if (m_mouseState.reportDeltaX != 0)
            {
                m_mouseState.position.x = SignedFixedType();
            }

            if (m_mouseState.reportDeltaY != 0)
            {
                m_mouseState.position.y = SignedFixedType();
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

        enum DirectionCommandEnum
        {
            DEG_NONE,
            DEG_0,
            DEG_45,
            DEG_90,
            DEG_135,
            DEG_180,
            DEG_225,
            DEG_270,
            DEG_315,
            DEG_COUNT
        };

        //typedef FixedPoint<int16_t, int16_t, 4> SignedFixedType;     // 12.4
        //typedef FixedPoint<int32_t, int32_t, 8> SignedFixedType;      // 24.8
        //typedef FixedPoint<int32_t, int64_t, 16> SignedFixedType;      // 16.16
        typedef FixedPoint<int32_t, int32_t, 10> SignedFixedType;      // 22.10

        typedef Vector2<SignedFixedType> VectorType;

        struct MouseStateType
        {
            VectorType  position;
            VectorType  velocity;
            int8_t      reportDeltaX;    ///< The motion X component reported on USB.
            int8_t      reportDeltaY;    ///< The motion Y component reported on USB.

            MouseStateType() :
                reportDeltaX(0),
                reportDeltaY(0)
            {
            }
        };

        unsigned long   m_lastUpdateTime;
        MouseStateType  m_mouseState;
        //VectorType      m_mouseUnitVectors[DEG_COUNT];
        VectorType      m_mouseUnitVectors[3][3];           // [row][col]
        MouseModeEnum   m_mouseMode;
};

#endif
