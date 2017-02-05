#include "Platform.h"

#include <avr/interrupt.h>

#include "PlatformBoardSpecific.h"

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

        EnablePullupInputs();

        // Configure push-pull outputs.
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

    template<uint32_t usec>
    void DelayMicrosecs()
    {
        _delay_us(usec);
    }

    unsigned long GetMsec()
    {
        unsigned long result;

        cli();
        result = s_msec;
        sei();

        return result;
    }

    void JumpToBootloader()
    {
        cli();
        // disable watchdog, if enabled
        // disable all peripherals
        UDCON = 1;
        USBCON = (1<<FRZCLK);  // disable USB
        UCSR1B = 0;
        _delay_ms(5);
        #if defined(__AVR_AT90USB162__)                // Teensy 1.0
            EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0;
            TIMSK0 = 0; TIMSK1 = 0; UCSR1B = 0;
            DDRB = 0; DDRC = 0; DDRD = 0;
            PORTB = 0; PORTC = 0; PORTD = 0;
            asm volatile("jmp 0x3E00");
        #elif defined(__AVR_ATmega32U4__)              // Teensy 2.0
            EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
            TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
            DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
            PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
            asm volatile("jmp 0x7E00");
        #elif defined(__AVR_AT90USB646__)              // Teensy++ 1.0
            EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
            TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
            DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
            PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
            asm volatile("jmp 0xFC00");
        #elif defined(__AVR_AT90USB1286__)             // Teensy++ 2.0
            EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
            TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
            DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
            PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
            asm volatile("jmp 0x1FC00");
        #endif 
    }
}
