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

    // Needed by Board.
    typedef uint8_t InputElementType;

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 21>(uint8_t (& o_inputs)[21])
    {
        #define READ_COLUMN_PIN(columnIndex, pinRegister, pinNumber) \
        o_inputs[columnIndex] = ~(pinRegister & (1 << pinNumber));

        // Every thing up to the numpad.
        READ_COLUMN_PIN(0,  PINB, 6);
        READ_COLUMN_PIN(1,  PINB, 5);
        READ_COLUMN_PIN(2,  PINB, 4);
        READ_COLUMN_PIN(3,  PINB, 3);
        READ_COLUMN_PIN(4,  PINB, 2);
        READ_COLUMN_PIN(5,  PINB, 1);
        READ_COLUMN_PIN(6,  PINB, 0);
        READ_COLUMN_PIN(7,  PINE, 7);
        READ_COLUMN_PIN(8,  PINE, 6);
        READ_COLUMN_PIN(9,  PINF, 0);
        READ_COLUMN_PIN(10, PINF, 1);
        READ_COLUMN_PIN(11, PINF, 2);
        READ_COLUMN_PIN(12, PINF, 3);
        READ_COLUMN_PIN(13, PINF, 4);
        READ_COLUMN_PIN(14, PINF, 5);
        READ_COLUMN_PIN(15, PINF, 6);
        READ_COLUMN_PIN(16, PINF, 7);

        // Numpad.
        READ_COLUMN_PIN(17, PIND, 1);
        READ_COLUMN_PIN(18, PIND, 4);
        READ_COLUMN_PIN(19, PINC, 0);
        READ_COLUMN_PIN(20, PINC, 2);
    }

    #define MAKE_ROW_PIN(rowIndex, ddRegister, pinNumber) \
    template <> inline void SetRow  <rowIndex>() { ddRegister |=  (1 << pinNumber); } \
    template <> inline void ClearRow<rowIndex>() { ddRegister &= ~(1 << pinNumber); }

    MAKE_ROW_PIN(0, DDRB, 7)
    MAKE_ROW_PIN(1, DDRD, 2)
    MAKE_ROW_PIN(2, DDRD, 5)
    MAKE_ROW_PIN(3, DDRE, 0)
    MAKE_ROW_PIN(4, DDRC, 4)
    MAKE_ROW_PIN(5, DDRC, 7)
}


#endif
