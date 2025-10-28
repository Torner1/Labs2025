#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // For itoa()

#define USART_BAUDRATE 9600
#define BAUD_PRESCALER (((16000000UL / (USART_BAUDRATE * 16UL))) - 1)

// Constants based on typical values
#define ADC_AT_25C 352        // ADC value at +25°C (0x0160)
#define TEMPERATURE_SENSITIVITY 1  // 1 LSB/°C

void USART_Init() {
    UBRR0H = (BAUD_PRESCALER >> 8);
    UBRR0L = BAUD_PRESCALER;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit, no parity
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Enable RX and TX
}

void USART_Transmit(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait until the data register is empty
    UDR0 = data;
}

void USART_SendString(char* str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

void ADC_Init() {
    // Set the reference voltage to internal 1.1V and select the temperature sensor
    ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);
    // Enable the ADC and set the prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read() {
    ADCSRA |= (1 << ADSC); // Start conversion
    while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
    return ADC; // Return the ADC value
}

int main() {
    char buffer[10]; // Buffer to store temperature as a string

    USART_Init(); // Initialize USART
    ADC_Init(); // Initialize ADC

    while (1) {
        // Read the ADC value from the temperature sensor
        uint16_t adcValue = ADC_Read();
        
        // Calculate the temperature based on typical values
        // Using a simple linear conversion with 1 LSB/°C sensitivity
        int16_t temperature = adcValue - ADC_AT_25C; // Offset from 25°C
        temperature += 25; // Adjust to get the temperature in °C

        // Convert temperature to string and send it via USART
        itoa(temperature, buffer, 10); // Convert temperature to string (base 10)
        USART_SendString("Temperature: ");
        USART_SendString(buffer);
        USART_SendString(" C\n");
        _delay_ms(1000); // Delay for demonstration
    }
}
