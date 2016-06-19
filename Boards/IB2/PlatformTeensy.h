#ifndef PLATFORM_TEENSY_H_
#define PLATFORM_TEENSY_H_

#include <avr/io.h>
#include <util/delay.h>

#include "Platform.h"

namespace Platform
{
    template<uint32_t usec>
    void DelayMicrosecs()
    {
        _delay_us(usec);
    }

    // Needed by Board.
    typedef uint8_t InputElementType;

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 21>(uint8_t (& o_inputs)[21])
    {
        #define READ_COLUMN_PIN(columnIndex, pinRegister, pinNumber) \
        o_inputs[columnIndex] = ((~pinRegister) & (1 << pinNumber));

        // Every thing up to the numpad.
        READ_COLUMN_PIN(0,  PIND, 0);
        READ_COLUMN_PIN(1,  PIND, 1);
        READ_COLUMN_PIN(2,  PIND, 2);
        READ_COLUMN_PIN(3,  PIND, 3);
        READ_COLUMN_PIN(4,  PIND, 4);

        READ_COLUMN_PIN(5,  PIND, 5);
        READ_COLUMN_PIN(6,  PIND, 7);
        READ_COLUMN_PIN(7,  PINE, 0);
        READ_COLUMN_PIN(8,  PINE, 1);
        READ_COLUMN_PIN(9,  PINB, 6);
        READ_COLUMN_PIN(10, PINB, 5);
        READ_COLUMN_PIN(11, PINB, 4);
        READ_COLUMN_PIN(12, PINB, 3);
        READ_COLUMN_PIN(13, PINB, 2);
        READ_COLUMN_PIN(14, PINB, 1);
        READ_COLUMN_PIN(15, PINB, 0);
        READ_COLUMN_PIN(16, PINE, 7);

        // Numpad.
        READ_COLUMN_PIN(17, PINE, 6);
        READ_COLUMN_PIN(18, PINF, 0);
        READ_COLUMN_PIN(19, PINF, 3);
        READ_COLUMN_PIN(20, PINF, 7);
    }

    #define MAKE_ROW_PIN(rowIndex, ddRegister, pinNumber) \
    template <> inline void SetRow  <rowIndex>() { ddRegister |=  (1 << pinNumber); } \
    template <> inline void ClearRow<rowIndex>() { ddRegister &= ~(1 << pinNumber); }

    MAKE_ROW_PIN(0, DDRB, 7)
    MAKE_ROW_PIN(1, DDRF, 1)
    MAKE_ROW_PIN(2, DDRF, 2)
    MAKE_ROW_PIN(3, DDRF, 5)
    MAKE_ROW_PIN(4, DDRF, 4)
    MAKE_ROW_PIN(5, DDRF, 6)
}


#endif
