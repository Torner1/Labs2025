#include <avr/io.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALER (((16000000UL / (USART_BAUDRATE * 16UL))) - 1)

void USART_Init() {
    UBRR0H = (BAUD_PRESCALER >> 8);
    UBRR0L = BAUD_PRESCALER;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit, no parity
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Enable RX and TX
}

void USART_Transmit(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait until the data register is empty
    UDR0 = data; // Load data into the register to send
}

uint8_t USART_Receive() {
    while (!(UCSR0A & (1 << RXC0))); // Wait until data is received
    return UDR0; // Return the received data from the register
}

int main() {
    USART_Init(); // Initialize USART

    while (1) {
        uint8_t receivedData = USART_Receive(); // Wait for data
        // Transmit an acknowledgment message
        USART_Transmit(receivedData); // 
    }
}
