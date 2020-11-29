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

uint16_t frequency =  100;
const char* waveform = "sine";
uint8_t input_counter = 0;
uint8_t digits[3] = {0,0,0};
const char* my_exponent = "Hz";

int main(void)
{
    // init matrix
    initMatrix();
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    lcd_gotoxy(0,0);
    lcd_puts("               ");
    lcd_gotoxy(0,1);
    lcd_puts("               ");

    lcd_gotoxy(1,0);
    lcd_puts("wave:");
    lcd_gotoxy(8,0);
    lcd_puts("sine");

    lcd_gotoxy(1,1);
    lcd_puts("Freq:");
    lcd_gotoxy(8,1);
    lcd_puts("100 Hz"); 
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
    char StringToUpadate[2]="";
    pos = scanMatrix();               // get position in form of int ex:23 row 2, column 3
    button_name = posToConstChar(pos,shift);
    static bool im_in_freq = 0;
   

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

      if (button_name == "freq") // freq is pressed
      {
        im_in_freq = 1;
      }
      
      if (im_in_freq == 1)
      {
        if (input_counter == 0)
        {
          lcd_gotoxy(8,1);
          lcd_puts("        ");
          lcd_gotoxy(8,1);
          lcd_puts(button_name);
          _delay_us(2);
          input_counter++;
        }
        else if (input_counter == 1)
        {
          lcd_gotoxy(8,1);
          lcd_puts("        ");
          lcd_gotoxy(8,1);
          lcd_puts(button_name);
          digits[0] = atoi(button_name);
          uart_puts("digit 0: ");
          itoa(digits[0],StringToUpadate,10);
          uart_puts(StringToUpadate);
          uart_puts("\n");
          input_counter++;
          
        }
        

        else if (input_counter < 4) // input counter == 2 and 3
        {
          lcd_gotoxy(7+input_counter,1);
          lcd_puts(button_name);
          digits[input_counter-1] = atoi(button_name);
          
          uart_puts("digit");
          itoa((input_counter-1),StringToUpadate,10);
          uart_puts(StringToUpadate);
          uart_puts(":");
          itoa(digits[input_counter-1],StringToUpadate,10);
          uart_puts(StringToUpadate);
          uart_puts("\n");
          input_counter++;
        }
        
        else if (input_counter == 4)
        {
          switch (pos)
          {
          case 12:
            my_exponent = "Hz";
            frequency =  100*digits[0]+10*digits[1]+digits[2];
            uart_puts("frequency: ");
            itoa(frequency,StringToUpadate,10);
            uart_puts(StringToUpadate);
            uart_puts(" ");
            uart_puts(my_exponent);
            uart_puts("\n");
            break;

          case 22:
            my_exponent = "kHz";
            frequency =  100*digits[0] + 10*digits[1] + digits[2];
            lcd_gotoxy(7+input_counter,1);
            lcd_puts("kHz");
            input_counter = 0;
            im_in_freq = 0;

            uart_puts("frequency: ");
            itoa(frequency,StringToUpadate,10);
            uart_puts(StringToUpadate);
            uart_puts(" ");
            uart_puts(my_exponent);
            uart_puts("\n");
            break;

          case 32:
            my_exponent = "MHz";
            frequency =  100*digits[0] +10*digits[1]+digits[2];
            lcd_gotoxy(7+input_counter,1);
            lcd_puts("MHz");
            input_counter = 0;
            im_in_freq = 0;

            uart_puts("frequency: ");
            itoa(frequency,StringToUpadate,10);
            uart_puts(StringToUpadate);
            uart_puts(" ");
            uart_puts(my_exponent);
            uart_puts("\n");
            break;    
          
          default:
            break;
          }//switch
       }//else if
      }//if
      else
      {
        uart_puts("position:");
        itoa(pos,StringToUpadate,10);
        uart_puts(StringToUpadate);
        uart_puts("\n");

        uart_puts("frequency: ");
        itoa(frequency,StringToUpadate,10);
        uart_puts(StringToUpadate);
        uart_puts(" ");
        uart_puts(my_exponent);
        uart_puts("\n");

      }//else
      
    }
    pre_pos = pos;
}//ISR

