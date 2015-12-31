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

    #define MAKE_COLUMN_PIN(columnIndex, portRegister, pinNumber) \
    template <> inline void SetColumn  <columnIndex>::operator()() { portRegister |=  (1 << pinNumber); } \
    template <> inline void ResetColumn<columnIndex>::operator()() { portRegister &= ~(1 << pinNumber); }

    MAKE_COLUMN_PIN(0,  PORTB, 7)
    MAKE_COLUMN_PIN(1,  PORTD, 0)
    MAKE_COLUMN_PIN(2,  PORTD, 1)
    MAKE_COLUMN_PIN(3,  PORTD, 2)
    MAKE_COLUMN_PIN(4,  PORTD, 3)
    MAKE_COLUMN_PIN(5,  PORTD, 4)
    MAKE_COLUMN_PIN(6,  PORTD, 5)
    MAKE_COLUMN_PIN(7,  PORTD, 7)   // Note skipping 6, because the Teensy has an LED there.
    MAKE_COLUMN_PIN(8,  PORTE, 0)
    MAKE_COLUMN_PIN(9,  PORTE, 1)
    MAKE_COLUMN_PIN(10, PORTC, 0)
    MAKE_COLUMN_PIN(11, PORTC, 1)
    MAKE_COLUMN_PIN(12, PORTC, 2)
    MAKE_COLUMN_PIN(13, PORTC, 3)
    MAKE_COLUMN_PIN(14, PORTC, 4)
    MAKE_COLUMN_PIN(15, PORTC, 5)
    MAKE_COLUMN_PIN(16, PORTC, 6)

    // Keypad
    MAKE_COLUMN_PIN(17, PORTB, 1)
    MAKE_COLUMN_PIN(18, PORTB, 0)
    MAKE_COLUMN_PIN(19, PORTE, 7)
    MAKE_COLUMN_PIN(20, PORTE, 6)
}


#endif
