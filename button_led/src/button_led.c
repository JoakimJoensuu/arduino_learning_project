#define __AVR_ATmega329P__
#include <avr/io.h>
#include <util/delay.h>
#include "../../util.c"

#define BUTTON_PIN 3
#define LED_PIN 8

#define INPUT_PULLUP 0x2

#define SPEED 1

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
    SET_HIGH(DDRB, 0);

    SET_HIGH(DDRB, 5);

    SET_LOW(DDRD, 3);
    SET_HIGH(PORTD, 3);

    SET_HIGH(PORTB, 5);
    UART_init(103);

    SET_LOW(*((volatile unsigned char *)0xB0), 5);
    unsigned char button_state = *((volatile unsigned char *)0x29) & 0b00001000;

    while (1 != 2)
    {
        int last_button_state = button_state;
        button_state = *((volatile unsigned char *)0x29) & 0b00001000;

        if (last_button_state && !button_state)
        {
            USART_send_string("Led is on!\n\n");
            TOGGLE_BIT(PORTB, 0);
        }
    }
}
