#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB = DDRB | (1 << DDB4);
    while (1)
    {
        _delay_ms(1000);
        PORTB ^= (1 << PORTB4);
    }
}