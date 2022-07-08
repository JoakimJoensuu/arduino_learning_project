#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
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

unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    /* Put data into buffer, sends the data */
    UDR0 = data;
}

int main(void)
{

    /*Set to one the fifth bit of DDRB to one
    **Set digital pin 13 to output mode */
    DDRB |= _BV(DDB5);

    UART_init(F_CPU / 16 / 9600 - 1);

    while (1)
    {
        unsigned char x;
        if (UCSR0A & (1 << RXC0)) //it is eqavilant to if(Serial.available)
        {
            x = USART_Receive();
            switch (x)
            {
            case 'A':
                PORTB |= _BV(PORTB5);
                USART_Transmit(x);
                //_delay_ms(400);
                PORTB &= ~_BV(PORTB5);
                break;
            case 'S':
                PORTB |= _BV(PORTB5);
                USART_Transmit(x);
                //_delay_ms(100);
                PORTB &= ~_BV(PORTB5);
                break;
            default:
                USART_Transmit(x);
                for (int i = 0; i < 10; i++)
                {
                    PORTB |= _BV(PORTB5);
                    //_delay_ms(20);
                    PORTB &= ~_BV(PORTB5);
                    //_delay_ms(20);
                }
                break;
            }
        }
        //_delay_ms(200);
    }
}
