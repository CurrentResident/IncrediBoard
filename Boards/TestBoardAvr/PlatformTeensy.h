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
    template <> inline void SetColumn  <0>::operator()() { PORTD |=  0x01; }
    template <> inline void ResetColumn<0>::operator()() { PORTD &= ~0x01; }
    template <> inline void SetColumn  <1>::operator()() { PORTD |=  0x02; }
    template <> inline void ResetColumn<1>::operator()() { PORTD &= ~0x02; }
    template <> inline void SetColumn  <2>::operator()() { PORTD |=  0x04; }
    template <> inline void ResetColumn<2>::operator()() { PORTD &= ~0x04; }
    template <> inline void SetColumn  <3>::operator()() { PORTD |=  0x08; }
    template <> inline void ResetColumn<3>::operator()() { PORTD &= ~0x08; }
    template <> inline void SetColumn  <4>::operator()() { PORTD |=  0x10; }
    template <> inline void ResetColumn<4>::operator()() { PORTD &= ~0x10; }
}


#endif
