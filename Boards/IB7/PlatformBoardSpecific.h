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

        PORTB = BOOST_BINARY(1111 1111);
        PORTC = BOOST_BINARY(1000 0000);
        PORTD = BOOST_BINARY(1011 1111);
        PORTE = BOOST_BINARY(1100 0011);
        PORTF = BOOST_BINARY(0000 0001);
    }

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
        READ_COLUMN_PIN(6,  PINB, 1);
        READ_COLUMN_PIN(7,  PINB, 2);
        READ_COLUMN_PIN(8,  PINE, 0);
        READ_COLUMN_PIN(9,  PINE, 1);
        READ_COLUMN_PIN(10, PINB, 4);
        READ_COLUMN_PIN(11, PINB, 3);
        READ_COLUMN_PIN(12, PINB, 5);
        READ_COLUMN_PIN(13, PINB, 6);
        READ_COLUMN_PIN(14, PIND, 5);
        READ_COLUMN_PIN(15, PIND, 7);
        READ_COLUMN_PIN(16, PINB, 0);

        // Numpad.
        READ_COLUMN_PIN(17, PINE, 7);
        READ_COLUMN_PIN(18, PINE, 6);
        READ_COLUMN_PIN(19, PINF, 0);
        READ_COLUMN_PIN(20, PINC, 7);
    }

    #define MAKE_ROW_PIN(rowIndex, ddRegister, pinNumber) \
    template <> inline void SetRow  <rowIndex>() { ddRegister |=  (1 << pinNumber); } \
    template <> inline void ClearRow<rowIndex>() { ddRegister &= ~(1 << pinNumber); }

    MAKE_ROW_PIN(0, DDRF, 2)
    MAKE_ROW_PIN(1, DDRF, 1)
    MAKE_ROW_PIN(2, DDRF, 3)
    MAKE_ROW_PIN(3, DDRF, 4)
    MAKE_ROW_PIN(4, DDRF, 6)
    MAKE_ROW_PIN(5, DDRF, 5)
}
