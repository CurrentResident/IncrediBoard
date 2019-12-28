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

        PORTB = BOOST_BINARY(0001 0000);
        PORTC = BOOST_BINARY(0000 0000);
        PORTD = BOOST_BINARY(0000 0000);
        PORTE = BOOST_BINARY(0000 0000);
        PORTF = BOOST_BINARY(1000 0011);
    }

    // Template specializations
    //
    template <> inline void ReadInputs<uint8_t, 4>(uint8_t (& o_inputs)[4])
    {
        #define READ_COLUMN_PIN(columnIndex, pinRegister, pinNumber) \
        o_inputs[columnIndex] = ((~pinRegister) & (1 << pinNumber));

        // Every thing up to the numpad.
        READ_COLUMN_PIN(0,  PINF, 0);
        READ_COLUMN_PIN(1,  PINF, 1);
        READ_COLUMN_PIN(2,  PINF, 7);
        READ_COLUMN_PIN(3,  PINB, 4);
    }

    #define MAKE_ROW_PIN(rowIndex, ddRegister, pinNumber) \
    template <> inline void SetRow  <rowIndex>() { ddRegister |=  (1 << pinNumber); } \
    template <> inline void ClearRow<rowIndex>() { ddRegister &= ~(1 << pinNumber); }

    MAKE_ROW_PIN(0, DDRB, 5)
    MAKE_ROW_PIN(1, DDRB, 6)
    MAKE_ROW_PIN(2, DDRF, 6)
    MAKE_ROW_PIN(3, DDRF, 4)
    MAKE_ROW_PIN(4, DDRF, 5)
}
