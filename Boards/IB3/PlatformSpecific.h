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
    template <> inline void ReadInputs<uint8_t, 17>(uint8_t (& o_inputs)[17])
    {
        #define READ_COLUMN_PIN(columnIndex, pinRegister, pinNumber) \
        o_inputs[columnIndex] = ((~pinRegister) & (1 << pinNumber));

        // Every thing up to the numpad.
        READ_COLUMN_PIN(0,  PINB, 0);
        READ_COLUMN_PIN(1,  PINB, 1);
        READ_COLUMN_PIN(2,  PINB, 2);
        READ_COLUMN_PIN(3,  PINB, 3);
        READ_COLUMN_PIN(4,  PINE, 6);

        READ_COLUMN_PIN(5,  PINB, 7);
        READ_COLUMN_PIN(6,  PINF, 0);
        READ_COLUMN_PIN(7,  PIND, 5);
        READ_COLUMN_PIN(8,  PINF, 4);
        READ_COLUMN_PIN(9,  PINF, 5);
        READ_COLUMN_PIN(10, PINF, 6);
        READ_COLUMN_PIN(11, PINF, 7);
        READ_COLUMN_PIN(12, PINB, 6);
        READ_COLUMN_PIN(13, PINB, 5);
        READ_COLUMN_PIN(14, PIND, 0);
        READ_COLUMN_PIN(15, PIND, 1);
        READ_COLUMN_PIN(16, PIND, 2);
    }

    #define MAKE_ROW_PIN(rowIndex, ddRegister, pinNumber) \
    template <> inline void SetRow  <rowIndex>() { ddRegister |=  (1 << pinNumber); } \
    template <> inline void ClearRow<rowIndex>() { ddRegister &= ~(1 << pinNumber); }

    MAKE_ROW_PIN(0, DDRC, 7)
    MAKE_ROW_PIN(1, DDRC, 6)
    MAKE_ROW_PIN(2, DDRD, 3)
    MAKE_ROW_PIN(3, DDRB, 4)
    MAKE_ROW_PIN(4, DDRD, 7)
    MAKE_ROW_PIN(5, DDRD, 4)
}
