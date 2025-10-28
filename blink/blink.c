#include <avr/io.h> // provides macros and definitions for accessing registers and hardware-specific functions of AVR microcontrollers

#define F_CPU 16000000UL

#include <util/delay.h> // provides delay functions, including _delay_ms() for millisecond delays

#define BLINK_DELAY_MS 100

int main (void)
{
    // Arduino digital pin 13 (pin 5 of PORTB) for output
    DDRD |= (1 << DDD4); // PORTB5

    while(1) {
        // turn LED on
        PORTD |= (1 << PORTD4); // PORTB5
        _delay_ms(BLINK_DELAY_MS);

        // turn LED off
        PORTD &= ~(1 << PORTD4); // PORTB5
        _delay_ms(BLINK_DELAY_MS);
    }
}
