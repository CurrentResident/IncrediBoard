#ifndef PLATFORM_TEENSY_H_
#define PLATFORM_TEENSY_H_

#include <avr/io.h>
#include <util/delay.h>

#include "Platform.h"

namespace Platform
{
    void Init();

    template<uint32_t usec>
    void DelayMicrosecs()
    {
        _delay_us(usec);
    }

    // Template specializations for Columns
    //
    template <> inline void SetColumn  <0>::operator()() { PORTD |=  0x1; }
    template <> inline void ResetColumn<0>::operator()() { PORTD &= ~0x1; }
    template <> inline void SetColumn  <1>::operator()() { PORTD |=  0x2; }
    template <> inline void ResetColumn<1>::operator()() { PORTD &= ~0x2; }
}


#endif
