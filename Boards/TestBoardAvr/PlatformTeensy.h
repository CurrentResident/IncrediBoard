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

    // Template specializations for Rows
    //

    template <> inline void SetRow  <0>() { PORTD |=  0x01; }
    template <> inline void ClearRow<0>() { PORTD &= ~0x01; }
    template <> inline void SetRow  <1>() { PORTD |=  0x02; }
    template <> inline void ClearRow<1>() { PORTD &= ~0x02; }
    template <> inline void SetRow  <2>() { PORTD |=  0x04; }
    template <> inline void ClearRow<2>() { PORTD &= ~0x04; }
    template <> inline void SetRow  <3>() { PORTD |=  0x08; }
    template <> inline void ClearRow<3>() { PORTD &= ~0x08; }
    template <> inline void SetRow  <4>() { PORTD |=  0x10; }
    template <> inline void ClearRow<4>() { PORTD &= ~0x10; }
/*
    template <> inline void SetRow  <0>::operator()() { PORTD |=  0x01; }
    template <> inline void ResetRow<0>::operator()() { PORTD &= ~0x01; }
    template <> inline void SetRow  <1>::operator()() { PORTD |=  0x02; }
    template <> inline void ResetRow<1>::operator()() { PORTD &= ~0x02; }
    template <> inline void SetRow  <2>::operator()() { PORTD |=  0x04; }
    template <> inline void ResetRow<2>::operator()() { PORTD &= ~0x04; }
    template <> inline void SetRow  <3>::operator()() { PORTD |=  0x08; }
    template <> inline void ResetRow<3>::operator()() { PORTD &= ~0x08; }
    template <> inline void SetRow  <4>::operator()() { PORTD |=  0x10; }
    template <> inline void ResetRow<4>::operator()() { PORTD &= ~0x10; }
*/
}


#endif
