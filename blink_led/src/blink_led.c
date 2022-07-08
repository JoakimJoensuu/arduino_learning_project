#define __AVR_ATmega329P__
#include <avr/io.h>
#include <util/delay.h>

#define MS_DELAY 1000
#define MESSAGE "SOS"

static char *message = MESSAGE;

static char morse[][7] =
    {
        ['A'] = ".-",
        ['B'] = "-...",
        ['C'] = "-.-.",
        ['D'] = "-..",
        ['E'] = ".",
        ['F'] = "..-.",
        ['G'] = "--.",
        ['H'] = "....",
        ['I'] = "..",
        ['J'] = ".---",
        ['K'] = "-.-",
        ['L'] = ".-..",
        ['M'] = "--",
        ['N'] = "-.",
        ['O'] = "---",
        ['P'] = ".--.",
        ['Q'] = "--.-",
        ['R'] = ".-.",
        ['S'] = "...",
        ['T'] = "-",
        ['U'] = "..-",
        ['V'] = "...-",
        ['W'] = ".--",
        ['X'] = "-..-",
        ['Y'] = "-.--",
        ['Z'] = "--..",

        ['0'] = "-----",
        ['1'] = ".----",
        ['2'] = "..---",
        ['3'] = "...--",
        ['4'] = "....-",
        ['5'] = ".....",
        ['6'] = "-....",
        ['7'] = "--...",
        ['8'] = "---..",
        ['9'] = "----.",

        ['.'] = ".-.-.-",
        [','] = "--..--",
        ['?'] = "..--..",
        ['\''] = ".----.",
        ['!'] = "-.-.--",
        ['/'] = "-..-.",
        ['('] = "-.--.",
        [')'] = "-.--.-",
        ['&'] = ".-...",
        [':'] = "---...",
        [';'] = "-.-.-.",
        ['='] = "-...-",
        ['+'] = ".-.-.",
        ['-'] = "-....-",
        ['_'] = "..--.-",
        ['\\'] = ".-..-.",
        ['$'] = "...-..-",
        ['@'] = ".--.-.",
        [' '] = "----",

};

int main(void)
{
    /*Set to one the fifth bit of DDRB to one
    **Set digital pin 13 to output mode */
    DDRB |= _BV(DDB5);

    while (1)
    {
        _delay_ms(1000);

        char *message_reader = message;
        for (char character = *message_reader; message_reader - message < sizeof(MESSAGE); character = *(++message_reader))
        {
            char *morse_reader = morse[character];
            for (char morse_char = *morse_reader; morse_char != '\0'; morse_char = *(++morse_reader))
            {
                switch (morse_char)
                {
                case '-':
                    PORTB |= _BV(PORTB5);
                    _delay_ms(400);
                    break;
                case '.':
                    PORTB |= _BV(PORTB5);
                    _delay_ms(100);
                    break;
                default:
                    for (int i = 0; i < 10; i++)
                    {
                        PORTB |= _BV(PORTB5);
                        _delay_ms(20);
                        PORTB &= ~_BV(PORTB5);
                        _delay_ms(20);
                    }
                    break;
                }
                PORTB &= ~_BV(PORTB5);
                _delay_ms(200);
            }

            _delay_ms(700);
        }

        _delay_ms(1000);
    }
}
