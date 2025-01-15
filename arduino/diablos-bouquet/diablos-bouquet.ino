#include <Arduino.h>

const uint8_t NUM_LEDS = 6;
const int LED0 = 4;
const int LED1 = 3;
const int LED2 = 17;
const int LED3 = 16;
const int LED4 = 15;
const int LED5 = 14;
const int POT = A4;

uint8_t leds[NUM_LEDS] = { LED0, LED1, LED2, LED3, LED4, LED5 };

uint16_t min_delay = 50;
uint16_t max_delay = 300;
int _delay = 0;

// pass in unscaled pot reading
int calculate_delay(float pot_value)
{
    float percent = pot_value / 10.23;
    return min_delay + (int)(max_delay - min_delay) * percent / 100.0;
}

void setup() 
{
    Serial.begin(9600);
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    _delay = 100; //calculate_delay(analogRead(POT));
}


void loop() 
{
    static int current_led = 0;
    static int pot_cumulator = 0;
    static int pot_count = 0;

    digitalWrite(leds[current_led], HIGH);
    delay(_delay);
    digitalWrite(leds[current_led], LOW);

    pot_cumulator = 0;
    for(int i = 0; i < 10; i++)
        pot_cumulator += analogRead(POT);
    //Serial.println(pot_cumulator / 10);
    _delay = calculate_delay(pot_cumulator / 10);
    Serial.println(_delay);

    current_led = (current_led+1) % NUM_LEDS;
}
