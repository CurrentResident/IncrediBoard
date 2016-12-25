#ifndef INSIDE_PLATFORM_H_
#error "Do not include this file directly!!!"
#endif

#include <avr/io.h>
#include <util/delay.h>

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
        READ_COLUMN_PIN(0,  PINB, 7);
        READ_COLUMN_PIN(1,  PIND, 0);
        READ_COLUMN_PIN(2,  PIND, 1);
        READ_COLUMN_PIN(3,  PIND, 2);
        READ_COLUMN_PIN(4,  PIND, 3);

        READ_COLUMN_PIN(5,  PIND, 4);
        READ_COLUMN_PIN(6,  PIND, 5);
        READ_COLUMN_PIN(7,  PIND, 7);
        READ_COLUMN_PIN(8,  PINE, 0);
        READ_COLUMN_PIN(9,  PINE, 1);
        READ_COLUMN_PIN(10, PINC, 0);
        READ_COLUMN_PIN(11, PINC, 1);
        READ_COLUMN_PIN(12, PINC, 2);
        READ_COLUMN_PIN(13, PINC, 3);
        READ_COLUMN_PIN(14, PINC, 4);
        READ_COLUMN_PIN(15, PINC, 5);
        READ_COLUMN_PIN(16, PINC, 6);

        // Numpad.
        READ_COLUMN_PIN(17, PINB, 0);
        READ_COLUMN_PIN(18, PINF, 1);
        READ_COLUMN_PIN(19, PINF, 5);
        READ_COLUMN_PIN(20, PINC, 7);
    }

    #define MAKE_ROW_PIN(rowIndex, ddRegister, pinNumber) \
    template <> inline void SetRow  <rowIndex>() { ddRegister |=  (1 << pinNumber); } \
    template <> inline void ClearRow<rowIndex>() { ddRegister &= ~(1 << pinNumber); }

    MAKE_ROW_PIN(0, DDRB, 3)
    MAKE_ROW_PIN(1, DDRF, 7)
    MAKE_ROW_PIN(2, DDRF, 6)
    MAKE_ROW_PIN(3, DDRF, 0)
    MAKE_ROW_PIN(4, DDRB, 2)
    MAKE_ROW_PIN(5, DDRB, 1)
}
