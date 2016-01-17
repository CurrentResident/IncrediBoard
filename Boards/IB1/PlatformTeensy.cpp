#include "PlatformTeensy.h"

#include <avr/interrupt.h>
#include <boost/utility/binary.hpp>

namespace
{
    volatile unsigned long s_msec = 0;
}

ISR(TIMER0_OVF_vect)
{
    s_msec++;
}

namespace Platform
{
    void Init()
    {
        // Set CPU Prescaler to divisor 1 aka 16 MHz
        CLKPR = 0x80;   // Enable writes to this register's bits
        CLKPR = 0x00;   // 4lsbs = 0 == divisor of 1

        // TODO:  Automate the initialization of IOs and tie in with IO functions in header.
        //
        // Initialize input and output pins.
        //  Because we want column output pins to be open/drain style, start as "open" free-floating inputs.
        DDRB  = 0x00;
        PORTB = 0x00;
        DDRC  = 0x00;
        PORTC = 0x00;
        DDRD  = 0x00;
        PORTD = 0x00;
        DDRE  = 0x00;
        PORTE = 0x00;
        DDRF  = 0x00;
        PORTF = 0x00;

        // Now enable pull-ups on column inputs.  Keep this in synch with the header file!
        //                   7654 3210
        PORTB = BOOST_BINARY(0111 1111); //0x7F;
        PORTC = BOOST_BINARY(0000 0101); //0x05;
        PORTD = BOOST_BINARY(0001 0010); //0x12;
        PORTE = BOOST_BINARY(1100 0000); //0xC0;
        PORTF = BOOST_BINARY(1111 1111); //0xFF;

        // Configure outputs.
        // Currently we just want to flash the LED...
        DDRD |= (1 << 6);

        // Configure timer to generate 1msec interrupts.
        cli();
        TCCR0A = (1 << WGM01) | (1 << WGM00);       //WGM00 thru WGM02 set: Fast PWM mode with TOP == OCR0A
        TCCR0B = (1 << WGM02) |                     // See above.
                 (1 << CS01)  | (1 << CS00);        // Source from clock with 64 divisor.
        OCR0A  = 249;                               // 0 based.  249 counts of 64 ticks at 16 MHz == 1 msec.

        TIMSK0 = (1 << TOIE0);
        sei();
    }

    unsigned long GetMsec()
    {
        unsigned long result;

        cli();
        result = s_msec;
        sei();

        return result;
    }

}
