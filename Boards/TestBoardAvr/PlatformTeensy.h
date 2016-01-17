#ifndef PLATFORM_TEENSY_H_
#define PLATFORM_TEENSY_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "Platform.h"

namespace Platform
{
    void Init();

    template<uint32_t usec>
    void DelayMicrosecs()
    {
        _delay_us(usec);
    }

    // Required by Board.
    typedef uint8_t InputElementType;

    template <> inline void ReadInputs<uint8_t, 5>(uint8_t (& o_inputs)[5])
    {
        // Bitwise not due to inverted signals on pulled-up inputs.
        o_inputs[0] = ~(PINF & (1 << PF2));
        o_inputs[1] = ~(PINF & (1 << PF3));
        o_inputs[2] = ~(PINF & (1 << PF4));
        o_inputs[3] = ~(PINF & (1 << PF5));
        o_inputs[4] = ~(PINF & (1 << PF6));
    }

    // Template specializations for Rows
    //

    template <> inline void SetRow  <0>() { DDRD |=  0x01; }
    template <> inline void ClearRow<0>() { DDRD &= ~0x01; }
    template <> inline void SetRow  <1>() { DDRD |=  0x02; }
    template <> inline void ClearRow<1>() { DDRD &= ~0x02; }
    template <> inline void SetRow  <2>() { DDRD |=  0x04; }
    template <> inline void ClearRow<2>() { DDRD &= ~0x04; }
    template <> inline void SetRow  <3>() { DDRD |=  0x08; }
    template <> inline void ClearRow<3>() { DDRD &= ~0x08; }
    template <> inline void SetRow  <4>() { DDRD |=  0x10; }
    template <> inline void ClearRow<4>() { DDRD &= ~0x10; }
}


#endif
