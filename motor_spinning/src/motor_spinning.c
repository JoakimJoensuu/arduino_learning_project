#define __AVR_ATmega329P__
#include <util/delay.h>
#include <avr/io.h>
#include "../../util.c"
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <avr/interrupt.h>

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
    SET_HIGH(DDRD, 2); //SET PIN PB1 (2) MODE TO OUTPUT
    SET_HIGH(DDRD, 3); //SET PIN PB1 (3) MODE TO OUTPUT
    SET_HIGH(PORTD, 2);
    SET_LOW(*((volatile unsigned char *)0xB0), 5); // timer pin3 off
    SET_LOW(PORTD, 3);

    SET_HIGH(DDRB, 1); //SET PIN PB1 (9) MODE TO OUTPUT

    TCCR1A |= _BV(COM1A1) | _BV(WGM10);
    TCCR1B |= _BV(CS10) | _BV(WGM12);

    UART_init(103);
    setupADC();
    sei();

    while (1)
    {
    }
}

void setupADC()
{
    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS0) | (1 << ADPS1);
    DIDR0 = (1 << ADC5D);

    startConversion();
}

void startConversion()
{
    ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect)
{
    unsigned char string[20];

    unsigned char speed = ADC / 1023.0f * 255.0f / 255.0f * (255.0f - 130.0f) + 130.0f;
    sprintf(string, "%d\n\n", speed);
    USART_send_string(string);

    OCR1A = speed;

    startConversion();
}
