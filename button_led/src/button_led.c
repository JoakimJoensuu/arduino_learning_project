#define __AVR_ATmega329P__
#include <util/delay.h>
#include "../../util.c"

#define BUTTON_PIN 3
#define LED_PIN 8

#define INPUT_PULLUP 0x2

#define SPEED 1
int main(void)
{
    SET_HIGH(DDRB, 0);

    SET_LOW(DDRD, 3);
    SET_HIGH(PORTD, 3);

    SET_LOW(*((volatile unsigned char *)0xB0), 5);
    unsigned char button_state = *((volatile unsigned char *)0x29) & 0b00001000;

    while (1 != 2)
    {
        int last_button_state = button_state;
        button_state = *((volatile unsigned char *)0x29) & 0b00001000;

        if (last_button_state && !button_state)
        {

            PORTB ^= (1 << 0);
        }
    }
}
