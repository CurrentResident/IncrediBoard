#ifndef INSIDE_PLATFORM_SPECIFIC_H_
#error "Do not include this file directly!!!"
#endif

#include <avr/io.h>

#include <boost/utility/binary.hpp>

namespace Platform
{
    // Needed by Board.
    typedef uint8_t InputElementType;

    inline void ConfigurePins()
    {
        // In the common Teensy2 platform, we've already configured outputs.
        //
        // Now enable pull-ups on column inputs.  Remember to keep this in synch with ReadInputs!
        //                   7654 3210

        PORTB = BOOST_BINARY(1111 1110);
        PORTC = BOOST_BINARY(1100 0001);
        PORTD = BOOST_BINARY(1011 1111);
        PORTE = BOOST_BINARY(0000 0011);
        PORTF = BOOST_BINARY(1100 0000);
    }

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 21>(uint8_t (& o_inputs)[21])
    {
        #define READ_COLUMN_PIN(columnIndex, pinRegister, pinNumber) \
        o_inputs[columnIndex] = ((~pinRegister) & (1 << pinNumber));

        // Every thing up to the numpad.
        READ_COLUMN_PIN(0,  PINB, 6);
        READ_COLUMN_PIN(1,  PINB, 5);
        READ_COLUMN_PIN(2,  PINB, 4);
        READ_COLUMN_PIN(3,  PINB, 3);
        READ_COLUMN_PIN(4,  PINB, 2);

        READ_COLUMN_PIN(5,  PINB, 1);
        READ_COLUMN_PIN(6,  PINB, 7);
        READ_COLUMN_PIN(7,  PIND, 0);
        READ_COLUMN_PIN(8,  PIND, 1);
        READ_COLUMN_PIN(9,  PIND, 2);
        READ_COLUMN_PIN(10, PIND, 3);
        READ_COLUMN_PIN(11, PIND, 4);
        READ_COLUMN_PIN(12, PIND, 5);
        READ_COLUMN_PIN(13, PIND, 7);
        READ_COLUMN_PIN(14, PINE, 0);
        READ_COLUMN_PIN(15, PINE, 1);
        READ_COLUMN_PIN(16, PINC, 0);

        // Numpad.
        READ_COLUMN_PIN(17, PINF, 6);
        READ_COLUMN_PIN(18, PINC, 6);
        READ_COLUMN_PIN(19, PINF, 7);
        READ_COLUMN_PIN(20, PINC, 7);
    }

    #define MAKE_ROW_PIN(rowIndex, ddRegister, pinNumber) \
    template <> inline void SetRow  <rowIndex>() { ddRegister |=  (1 << pinNumber); } \
    template <> inline void ClearRow<rowIndex>() { ddRegister &= ~(1 << pinNumber); }

    MAKE_ROW_PIN(0, DDRC, 1)
    MAKE_ROW_PIN(1, DDRC, 3)
    MAKE_ROW_PIN(2, DDRC, 2)
    MAKE_ROW_PIN(3, DDRF, 0)
    MAKE_ROW_PIN(4, DDRF, 1)
    MAKE_ROW_PIN(5, DDRF, 3)
}
