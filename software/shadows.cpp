#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define TRIGPOINT 128

#define BAUD             9600
#define UBBR             (F_CPU / 16 / BAUD - 1)

void serial_init(void)
{
    /*Set baud rate */ 
    UBRR0H = (unsigned char)(UBBR>>8); 
    UBRR0L = (unsigned char)UBBR; 
    /* Enable transmitter */ 
    UCSR0B = (1<<TXEN0) | (1<<RXEN0); 
    /* Set frame format: 8data, 1stop bit */ 
    UCSR0C = (0<<USBS0)|(3<<UCSZ00); 
}

void serial_tx(uint8_t ch)
{
    while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = ch;
}

void dprint(const char *ptr)
{
    for(; *ptr; ptr++)
    {
        if (*ptr == '\n') serial_tx('\r');
        serial_tx(*ptr);
    }
}

void adc_config(uint8_t ch){
    // Set ADC configuration registers as follows:
    // ADMUX - ADC multiplexer selection register: 
        // REFS0 = 1        - AVcc reference with external capacitor at AREF pin
        // ADLAR = 1        - ADC presentation of ADC result (left adjusted)
    // ADCSRA - ADC control and status register A
        // ADATE = 1        - Enable auto triggering of the ADC
        // ADPS0, ADPS1, ADPS2 = 1 - Set the division factor between the system clock frequency and the input clock to the ADC (/128 - 62.5kHz)
//    ADMUX |= (1 << REFS0) | (1 << ADLAR);
    ADMUX |= (1 << ADLAR);
    switch(ch){
        case 6:
            // MUX1, MUX2 = 1   - Choose the ADC channel 6
            ADMUX |= (1<< MUX2) | (1 << MUX1);
            break;
        case 7:
            // MUX0, MUX1, MUX2 = 1   - Choose the ADC channel 7
            ADMUX |= (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
            break;
    }
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADATE);

    // enabled the adc
    ADCSRA |= (1 << ADEN);
}

int main(void)
{
    serial_init();
    adc_config(7);

    dprint("Hello!\n");

	// Main program loop
    while (1) 
    {
		// Start an ADC conversion by setting ADSC bit (bit 6)
		ADCSRA = ADCSRA | (1 << ADSC);
		
		// Wait until the ADSC bit has been cleared
		while(ADCSRA & (1 << ADSC));

        int h = ADCH;
        int l = ADCL;
        char text[32];
        sprintf(text, "%d,%d\n", l, h);
        dprint(text);
	}
}


#if 0

#include <avr/io.h>
#include <util/delay.h>

// For Version 2024-12-23 of this board
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

int _main(void)
{
    uint8_t i;
    
    DDRC = _BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3);
    DDRD = _BV(LED4) | _BV(LED5);

    cbi(PORTC, 0);
    cbi(PORTC, 1);
    cbi(PORTC, 2);
    cbi(PORTC, 3);
    cbi(PORTD, 3);
    cbi(PORTD, 4);
    for(;;)
        for(i = 0; i < 6; i++)
        {
            if (i < 4)
                sbi(PORTC, i);
            else
                sbi(PORTD, i - 1);

            _delay_ms(50);

            if (i < 4)
                cbi(PORTC, i);
            else
                cbi(PORTD, i - 1);
        }
    
    return 0;
}
#endif
