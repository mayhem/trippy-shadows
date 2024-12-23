#include <avr/io.h>
#include <util/delay.h>

#define LED0 2
#define LED1 3
#define LED2 4
#define LED3 5

int main(void)
{
    uint8_t i;
    
    DDRB = _BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3);

    for(;;)
        for(i = 0; i < 4; i++)
        {
            PORTB = (1 << (i+2));
            _delay_ms(100);
            PORTB = 0;
        }
    
    return 0;
}

