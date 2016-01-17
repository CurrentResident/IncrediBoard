#include "PlatformTeensy.h"

#include <avr/interrupt.h>

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

        // Configure Port E to be inputs.
        DDRF  = 0x00;   
        PORTF = 0x00;   // Normal inputs.  This keyboard's rows are wired with pull-down resistors.

        // Configure timer to generate 1msec interrupts.
        cli();
        TCCR0A = (1 << WGM01) | (1 << WGM00);       //WGM00 thru WGM02 set: Fast PWM mode with TOP == OCR0A
        TCCR0B = (1 << WGM02) |                     // See above.
                 (1 << CS01)  | (1 << CS00);        // Source from clock with 64 divisor.
        OCR0A  = 249;                               // 0 based.  249 counts of 64 ticks at 16 MHz == 1 msec.

        TIMSK0 = (1 << TOIE0);
        sei();
    }
/*
    void ReadInputs(InputValuesType& o_inputs)
    {
        o_inputs.row[0] = (PINF & (1 << PF2));
        o_inputs.row[1] = (PINF & (1 << PF3));
        o_inputs.row[2] = (PINF & (1 << PF4));
        o_inputs.row[3] = (PINF & (1 << PF5));
        o_inputs.row[4] = (PINF & (1 << PF6));
        o_inputs.row[5] = (PINF & (1 << PF7));
    }
*/
    unsigned long GetMsec()
    {
        unsigned long result;

        cli();
        result = s_msec;
        sei();

        return result;
    }

}
