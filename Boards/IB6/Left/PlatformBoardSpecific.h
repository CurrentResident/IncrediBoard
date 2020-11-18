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

        PORTB = BOOST_BINARY(1000 1001);
        PORTC = BOOST_BINARY(0000 0000);
        PORTD = BOOST_BINARY(0000 0011);
        PORTE = BOOST_BINARY(0000 0000);
        PORTF = BOOST_BINARY(0110 0000);
    }

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 7>(uint8_t (& o_inputs)[7])
    {
        #define READ_COLUMN_PIN(columnIndex, pinRegister, pinNumber) \
        o_inputs[columnIndex] = ((~pinRegister) & (1 << pinNumber));

        // Every thing up to the numpad.
        READ_COLUMN_PIN(0,  PINB, 3);
        READ_COLUMN_PIN(1,  PINB, 7);
        READ_COLUMN_PIN(2,  PIND, 0);
        READ_COLUMN_PIN(3,  PIND, 1);
        READ_COLUMN_PIN(4,  PINB, 0);
        READ_COLUMN_PIN(5,  PINF, 5);
        READ_COLUMN_PIN(6,  PINF, 6);
    }

    #define MAKE_ROW_PIN(rowIndex, ddRegister, pinNumber) \
    template <> inline void SetRow  <rowIndex>() { ddRegister |=  (1 << pinNumber); } \
    template <> inline void ClearRow<rowIndex>() { ddRegister &= ~(1 << pinNumber); }

    MAKE_ROW_PIN(0, DDRB, 1)
    MAKE_ROW_PIN(1, DDRB, 5)
    MAKE_ROW_PIN(2, DDRF, 7)
    MAKE_ROW_PIN(3, DDRB, 4)
    MAKE_ROW_PIN(4, DDRB, 6)
    MAKE_ROW_PIN(5, DDRD, 4)
}
