/***********************************************************************
 * 
 * Analog-to-digital conversion with displaying result on LCD and 
 * transmitting via UART.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <Arduino.h>
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#include <myMatrix.h>       // library for matrix scanning
#include "userinterface.h" // for updating display

/* Function definitions ----------------------------------------------*/
// returns 1 if odd (1,3.) and 0 if even(0,2...)

uint8_t frequency =  100;
const char* waveform = "sine";

int main(void)
{
    // init matrix
    initMatrix();
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600,F_CPU));
    // set timer for scanning
    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();



    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
    }
    

    // Will never reach this
    return 0;
}


ISR(TIMER1_OVF_vect)
{   
    static uint8_t pos ;            // position of pressed button
    static uint8_t pre_pos;         // previous position
    static bool shift = 0;
    static const char* button_name= ""; // button Name
    static const char* type = "homePage"; // button Name
    char StringToUpadate[2]="";
    pos = scanMatrix();               // get position in form of int ex:23 row 2, column 3
    button_name = posToConstChar(pos);

    if ((pos == 0) || (pos == pre_pos)){
    } // do nothing 
    else {
      if (pos == 14){ // shift position
          shift = !shift;
        }
      else if ((pos != 14) && (shift ==1))
      {
        shift = 0;
      }
         
        itoa(pos,StringToUpadate,10);
        uart_puts(StringToUpadate);
        updateDisplay(frequency,button_name, shift, type);// function to update display
    }
    pre_pos = pos;
}//ISR

