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

    VectorType      position;
    SignedFixedType velocity;
    int8_t          reportDeltaX;    ///< The motion X component reported on USB.
    int8_t          reportDeltaY;    ///< The motion Y component reported on USB.
    uint8_t         buttons;
    bool            reportIsRequired;

    MouseStateType() :
        reportDeltaX(0),
        reportDeltaY(0),
        buttons(0),
        reportIsRequired(false)
    {
    }

    static const VectorType s_mouseUnitVectors[3][3];           // [row][col]

    void MouseMotion(unsigned long         i_deltaMsec,
                     bool                  i_upIsActive,
                     bool                  i_downIsActive,
                     bool                  i_leftIsActive,
                     bool                  i_rightIsActive,
                     uint8_t               i_buttons)
    {
        const SignedFixedType deltaMsec      = i_deltaMsec;
        const SignedFixedType deltaTSeconds  = deltaMsec / 1000l;

        const SignedFixedType MAX_VELOCITY = 1000l;          // In units per second.
        const SignedFixedType ACCELERATION = 1000l;

        const int row = 1 + (i_upIsActive   *  1) + (i_downIsActive  * -1);
        const int col = 1 + (i_leftIsActive * -1) + (i_rightIsActive *  1);

        reportIsRequired = false;

        if (row == 1 and col == 1)
        {
            // If we're stopping the mouse, we report the 0, 0 motion.
            if (velocity.GetRaw() != 0)
            {
                reportIsRequired = true;
            }

            velocity = 0l;
        }
        else
        {
            velocity = std::min(MAX_VELOCITY, velocity + ACCELERATION * deltaTSeconds);
        }

        position += s_mouseUnitVectors[row][col] * (velocity * deltaTSeconds);

        position.x.Round(reportDeltaX);
        position.y.Round(reportDeltaY);

        if (reportDeltaX != 0)
        {
            reportIsRequired = true;
            position.x -= reportDeltaX;
        }

        if (reportDeltaY != 0)
        {
            reportIsRequired = true;
            position.y -= reportDeltaY;
        }

        if (buttons != i_buttons)
        {
            reportIsRequired = true;
            buttons = i_buttons;
        }
    }
};

#endif
