#define PORTB *((volatile unsigned char *)0x25)
#define DDRB *((volatile unsigned char *)0x24)

#define PORTD *((volatile unsigned char *)0x2B)
#define DDRD *((volatile unsigned char *)0x2A)

#define USART_IO_DATA_REGISTER *((volatile unsigned char *)0xC6) // UDR0
#define UCSR0A *((volatile unsigned char *)0xC0)

#define SET_HIGH(target, pin) (target) |= (1 << (pin))
#define SET_LOW(target, pin) (target) &= ~(1 << (pin))

void USART_send_string(unsigned char string[])
{
    uint8_t len = 0;
    for (uint8_t i = 0; string[i] != '\0'; ++i)
    {
        len++;
    }

    for (uint8_t i = 0; i <= len; ++i)
    {
        while (!(UCSR0A & (1 << 5)))
            SET_HIGH(PORTB, 5);
        USART_IO_DATA_REGISTER = string[i];
    }
}