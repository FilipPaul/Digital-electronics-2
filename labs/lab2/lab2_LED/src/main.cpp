#include <Arduino.h>

/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5     //arduino 13 AVR pin where green LED is connected
#define LED_BLUE    PC0     // arduino 6
#define SWITCH      PD5     // arduino 5
#define BLINK_DELAY 250
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif
bool toggle_state = 1;

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/

void toggle(){
toggle_state = !toggle_state;
_delay_ms(BLINK_DELAY);

}

int main(void){
// Set pin as output in Data Direction Register...
for (int i = 1; i < 6; i++)
{
      // Set pin as output in Data Direction Register...
    DDRD = DDRD | (1<<i);
    // ...and turn LED off in Data Register
    PORTD = PORTD | (1<<i);
  
}


    Serial.begin(9600);


    // Infinite loop
    while (1)
    {
       if (bit_is_clear(PIND,SWITCH)){

        PORTB = PORTB^(1<<LED_GREEN);
        PORTC = PORTC^(1<<LED_BLUE);
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);

        }
        


        // WRITE YOUR CODE HERE
    }

    // Will never reach this
    return 0;
}
