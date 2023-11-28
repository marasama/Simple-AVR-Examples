#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LEDP PORTB4
#define ECHOI PORTB3
#define TRIGO PORTB2

void initalize(void)
{
    // Set LED and trigger pin as output
    DDRB |= (1 << LEDP);
    DDRB |= (1 << TRIGO);
    // Set ECHOI as input
    DDRB &= ~(1 << ECHOI);
    // Set LED and trigger state to low
    PORTB &= ~(1 << TRIGO);
    PORTB &= ~(1 << LEDP);
}

void initUART() {
    // Set baud rate to 9600
    UBRR0H = 0;
    UBRR0L = 47;
    // Enable transmitter and receiver
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    // Set frame format: 8 data, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to transmit a character over UART
void UART_transmit(unsigned char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    // Put data into buffer, sends the data
    UDR0 = data;
}

int get_distance(void)
{
    uint16_t start;
    uint16_t end;
    uint16_t pulse;
    PORTB ^= (1 << TRIGO);
    _delay_us(10);
    PORTB ^= (1 << TRIGO);
    while (!(PINB & (1 << ECHOI)));
    start = TCNT1;
    while (PINB & (1 << ECHOI));
    end = TCNT1;
    pulse = end - start;
    // Sound of speed is 343 m/s, my timer works with micro seconds so im using it as 0.0343 cm/us
    // The division by 2 is because sound waves travels to the target and come back
    return (pulse * 0.0343) / 2;
}

int main()
{
    initalize();
    TCCR1B |= (1 << CS11);
    while (1)
    {
        PORTB ^= (1 << LEDP);
        // Made delay depending on distance because i want it to blink faster as its approaches to target
        _delay_ms(get_distance() * 75);
    }
}