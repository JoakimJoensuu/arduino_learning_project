#define __AVR_ATmega329P__
#include <avr/io.h>
#include <util/delay.h>

void UART_init(uint16_t ubrr)
{
    // set baudrate in UBRR
    UBRR0L = (uint8_t)(ubrr & 0xFF);
    UBRR0H = (uint8_t)(ubrr >> 8);

    // enable the transmitter and receiver
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

int main(void)
{

    /*Set to one the fifth bit of DDRB to one
    **Set digital pin 13 to output mode */
    DDRB |= _BV(DDB5);

    UART_init(103);

    while (1)
    {

        PORTB |= _BV(PORTB5);

        while (!(UCSR0A & (1 << UDRE0)))
            ;

        // load data into transmit register
        UDR0 = 'F';

        PORTB &= ~_BV(PORTB5);
    }
}
