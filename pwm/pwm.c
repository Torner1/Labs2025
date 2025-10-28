#include <avr/io.h>
#include <util/delay.h>

void PWM_Init()
{
    // Set PD6 (OC0A) as output
    DDRD |= (1 << PD6); // PWM pin 6

    // Set Timer0 to Fast PWM mode with non-inverting output on OC0A
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);

    // Set the prescaler to 64 for Timer0
    TCCR0B = (1 << CS01) | (1 << CS00);

    // Initialize with 0% duty cycle
    OCR0A = 0;
}

int main()
{
    PWM_Init(); // Initialize PWM on PD6

    while (1) {
        // Adjust OCR0A as needed for duty cycle from 0 to 255
        OCR0A = 127; // Example: 50% duty cycle
    }
}
