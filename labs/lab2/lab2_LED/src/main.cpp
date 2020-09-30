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
/**
 
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)

{
    Serial.begin(9600);
    /*PUSHTBUTTON*/
    DDRD = DDRD & ~(0<<SWITCH); // null DDRD
    //  setting pull up
    PORTD = PORTD |(1<<SWITCH); //

    /* GREEN LED */
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_GREEN);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_GREEN);

    /* BLUE LED */
    // Set pin as output in Data Direction Register...
    DDRC = DDRC | (1<<LED_BLUE);
    // ...and turn LED off in Data Register
    PORTC = PORTC & ~(1<<LED_BLUE);

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
