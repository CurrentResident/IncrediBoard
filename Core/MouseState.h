#ifndef MOUSE_STATE_H_
#define MOUSE_STATE_H_

#include <algorithm>
#include <cmath>
#include <stdint.h>

#include "FixedPoint.h"
#include "Platform.h"
#include "Vector2.h"

struct MouseStateType
{
    //typedef FixedPoint<int16_t, int16_t, 4> SignedFixedType;     // 12.4
    //typedef FixedPoint<int32_t, int32_t, 8> SignedFixedType;      // 24.8
    //typedef FixedPoint<int32_t, int64_t, 16> SignedFixedType;      // 16.16

    // 22.10 fixed point.  When multiplied, this leaves 12 bits for the integer part of the result, or
    // for the numerator when divided, but it gives enough precision for the fractional part to represent
    // thousandths of a second.
    typedef FixedPoint<int32_t, int32_t, 10> SignedFixedType;      // 22.10

    typedef Vector2<SignedFixedType> VectorType;

    unsigned long   reportTime;
    VectorType      position;
    SignedFixedType velocity;
    int8_t          reportDeltaX;    ///< The motion X component reported on USB.
    int8_t          reportDeltaY;    ///< The motion Y component reported on USB.
    uint8_t         buttons;
    bool            reportIsRequired;

    MouseStateType() :
        reportTime(0),        // 0?
        reportDeltaX(0),
        reportDeltaY(0),
        buttons(0),
        reportIsRequired(false)
    {
    }

    static const VectorType s_mouseUnitVectors[3][3];           // [row][col]

    static void MouseMotion(const MouseStateType& i_lastState,
                            MouseStateType&       o_newState,
                            bool                  i_upIsActive,
                            bool                  i_downIsActive,
                            bool                  i_leftIsActive,
                            bool                  i_rightIsActive,
                            uint8_t               i_buttons)
    {
        const unsigned long   now            = Platform::GetMsec();
        const SignedFixedType deltaMsec      = now - i_lastState.reportTime;
        const SignedFixedType deltaTSeconds  = deltaMsec / 1000l;

        const SignedFixedType MAX_VELOCITY = 1000l;          // In units per second.
        const SignedFixedType ACCELERATION = 1000l;

        const int row = 1 + (i_upIsActive   *  1) + (i_downIsActive  * -1);
        const int col = 1 + (i_leftIsActive * -1) + (i_rightIsActive *  1);

        o_newState.reportIsRequired = false;

        if (row == 1 and col == 1)
        {
            // If we're stopping the mouse, we report the 0, 0 motion.
            if (i_lastState.velocity.GetRaw() != 0)
            {
                o_newState.reportIsRequired = true;
            }

            o_newState.velocity = 0l;
        }
        else
        {
            o_newState.velocity = std::min(MAX_VELOCITY, i_lastState.velocity + ACCELERATION * deltaTSeconds);
        }

        o_newState.position = i_lastState.position + s_mouseUnitVectors[row][col] * (o_newState.velocity * deltaTSeconds);

        o_newState.position.x.Round(o_newState.reportDeltaX);
        o_newState.position.y.Round(o_newState.reportDeltaY);

        //deltaMsec.Round(m_mouseState.reportDeltaX);

        //Platform::DelayMillisecs<3>();

        if (o_newState.reportDeltaX != 0)
        {
            o_newState.reportIsRequired = true;
            o_newState.position.x -= o_newState.reportDeltaX;
        }

        if (o_newState.reportDeltaY != 0)
        {
            o_newState.reportIsRequired = true;
            o_newState.position.y -= o_newState.reportDeltaY;
        }

        if (i_lastState.buttons != i_buttons)
        {
            o_newState.reportIsRequired = true;
            o_newState.buttons = i_buttons;
        }

        //m_lastUpdateTime = now;
    }
};

#endif
