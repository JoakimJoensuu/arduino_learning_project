#define PORTD *((volatile unsigned char *)0x2B)
#define DDRD *((volatile unsigned char *)0x2A)

#define PORTB *((volatile unsigned char*) 0x25)
#define DDRB *((volatile unsigned char*) 0x24)
#define USART_IO_DATA_REGISTER *((volatile unsigned char*) 0xC6) // UDR0
#define UCSR0A *((volatile unsigned char*) 0xC0)

#define SET_HIGH(target, bit) (target) |= (1 << (bit))
#define SET_LOW(target, bit) (target) &= ~(1 << (bit))
#define TOGGLE_BIT(target, bit) (target) ^= (1 << (bit))

void USART_send_string(unsigned char string[])
{
    uint8_t len = 0;
    for (uint8_t i = 0; string[i] != '\0'; ++i)
    {
        len++;
    }

    for (uint8_t i=0; i<=len; ++i)
    {
        while (!(UCSR0A & (1 << 5)));
        USART_IO_DATA_REGISTER = string[i];
    }
}

void USART_read_line(unsigned char* buf, uint8_t buffer_size)
{
    uint8_t index = 0;
    for (; index < buffer_size; ++index) 
    { 
        while (!(UCSR0A & (1 << 5))); 
        unsigned char ch = USART_IO_DATA_REGISTER;
        if (ch == '\r')
        {
            buf[index] = '\0';
            return;
        }
        buf[index] = ch;
    }
    buf[index] = 0;
}

