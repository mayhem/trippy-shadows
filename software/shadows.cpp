#include <avr/io.h>
#include <util/delay.h>

// LED0 -> PC0
// LED1 -> PC1
// LED2 -> PC2
// LED3 -> PC3
// LED4 -> PD3
// LED5 -> PD4

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 3
#define LED5 4

// Bit manipulation macros
#define sbi(a, b) ((a) |= 1 << (b))       //sets bit B in variable A
#define cbi(a, b) ((a) &= ~(1 << (b)))    //clears bit B in variable A
#define tbi(a, b) ((a) ^= 1 << (b))       //toggles bit B in variable A

int main(void)
{
    uint8_t i;
    
    DDRC = _BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3);
    DDRD = _BV(LED4) | _BV(LED5);
    for(;;)
        for(i = 0; i < 6; i++)
        {
            if (i < 4)
                sbi(PORTC, i);
            else
                sbi(PORTD, i - 1);

            _delay_ms(1000);

            if (i < 4)
                cbi(PORTC, i);
            else
                cbi(PORTD, i - 1);
        }
    
    return 0;
}

