#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Generates a Blocking Delay

#define USART_BAUDRATE 9600 // Desired Baud Rate (USBRR)

#define BAUD_PRESCALER (((16000000UL / (USART_BAUDRATE * 16UL))) - 1) // 103

// Can have Synchronous or Asynchronous
#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection, synchronous = 1

// USART parity mode (UPM)
#define DISABLED    (0<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection, EVEN = 2, ODD = 3

// USART stop bit  (USB)
#define ONE_BIT (0<<USBS0) // Two bit = 1
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

// USART character size (UCS) buts select the number of data bits in the frame
#define EIGHT_BIT (3<<UCSZ00) // 5 Bits = 0, 6 Bits = 1, 7 Bits = 2
#define DATA_BIT EIGHT_BIT  // USART Data Bit Selection

char name[] = {'H','e','l','l','o',' ','w','o','r','l','d','!','\n'};

void USART_Init()
{
        // Set Baud Rate register (H)igh and (L)ow
        UBRR0H = BAUD_PRESCALER >> 8; // shift right by 8 bits so 103 would be 0
        UBRR0L = BAUD_PRESCALER; // here would 1101010

        // Set Frame Format ((U)SART (C)ontrol and (S)tatus (R)egister C) selects async or sync
        UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;

        // Enable Receiver and Transmitter RX/TXEN Enable... (U)SART (C)ontrol and (S)tatus (R)egister B
        UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

void USART_Transmit(uint8_t DataByte)
{
        // (U)SART (D)ata (R)egister (E)mpty if 0 empty, 1 has data
        while (( UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
        
        UDR0 = DataByte; // Where your byte of data goes
}

int main()
{
        USART_Init();
        while (1)
        {
                for(int i = 0; i < 13;i++){
                        USART_Transmit(name[i]);
                }
                _delay_ms(1000);
        }
        return 0;
}
