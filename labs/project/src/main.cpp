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
#include <avr/io.h>        // AVR device-specific IO definitions
#include <avr/interrupt.h> // Interrupts standard C library for AVR-GCC
#include "timer.h"         // Timer library for AVR-GCC
#include "lcd.h"           // Peter Fleury's LCD library
#include <stdlib.h>        // C library. Needed for conversion function
#include "uart.h"          // Peter Fleury's UART library
#include <myMatrix.h>      // library for matrix scanning

/* Function definitions ----------------------------------------------*/
// returns 1 if odd (1,3.) and 0 if even(0,2...)

uint16_t frequency = 100;
const char *waveform = "sine";
uint8_t digits[4] = {0, 0, 0, 0};
const char *my_exponent = "Hz";
bool status = 0;      //status on/off
uint8_t shiftChar[8] = { //adress 0
    0b11011,
    0b10001,
    0b00000,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011};

int main(void)
{
  // init matrix
  initMatrix();
  // Initialize LCD display
  lcd_init(LCD_DISP_ON);

  lcd_gotoxy(0, 0);
  lcd_puts("               ");
  lcd_gotoxy(0, 1);
  lcd_puts("               ");

  lcd_gotoxy(1, 0);
  lcd_puts("wave:");
  lcd_gotoxy(8, 0);
  lcd_puts("sine");
  lcd_gotoxy(13, 0);
  lcd_puts("off");

  lcd_gotoxy(1, 1);
  lcd_puts("Freq:");
  lcd_gotoxy(8, 1);
  lcd_puts("100 Hz");

  //custom character
  lcd_command(1 << LCD_CGRAM);
  for (uint8_t i = 0; i < 8; i++)
  {
    // Store all new chars to memory line by line
    lcd_data(shiftChar[i]);
  }
  // Set DDRAM address
  lcd_command(1 << LCD_DDRAM);

  // Initialize UART to asynchronous, 8N1, 9600
  uart_init(UART_BAUD_SELECT(9600, F_CPU));
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

// timer 1 is used to handle user interface (input matrix, display and UART)
ISR(TIMER1_OVF_vect)
{
  static uint8_t pos;     // position of pressed button
  static uint8_t pre_pos; // previous position
  static bool shift = 0;
  static const char *button_name = ""; // button Name
  static uint8_t input_counter = 0;
  char StringToUpadate[2] = ""; //string to update UART
  static bool im_in_freq = 0;

  pos = scanMatrix();                       // get position in form of int ex:23 row 2, column 3
  button_name = posToConstChar(pos, shift); //grt name of button in form of const char* from position


  if ((pos == 0) || (pos == pre_pos))
  { 
  } // do nothing
  else
  {
    // if change is detected:
    if (pos == 14)
    { //if shift was pressed
      shift = !shift;
      if (shift == 1)
      {
        lcd_gotoxy(0, 1);
        lcd_putc(0);
      }
      if (shift == 0)
      {
        lcd_gotoxy(0, 1);
        lcd_puts(" ");
      }
    }
    else if ((pos != 14) && (shift == 1)) // switch off  shift after shift + button combination
    {
      shift = 0;
      lcd_gotoxy(0, 1);
      lcd_puts(" ");
    }

    if (button_name == "freq") // freq is pressed
    {
      im_in_freq = 1; // variable to detect, that frequency isn't already selected
    }
    else if(button_name == "onoff")
    {
      status = !status;
      if (status == 1)
      {
        lcd_gotoxy(13, 0);
        lcd_puts("   ");
        lcd_gotoxy(13, 0);
        lcd_puts("on");
      }
      if (status == 0)
      {
        lcd_gotoxy(13, 0);
        lcd_puts("off");
      }
      
    }

    else if((button_name == "sine") || (button_name == "ramp")){
      waveform = button_name;
        lcd_gotoxy(8, 0);
        lcd_puts(waveform);
    }
    


    if (im_in_freq == 1)
    {
      if (input_counter == 0) // wait for input ("freq" on display)
      {
        lcd_gotoxy(8, 1);
        lcd_puts("        ");
        lcd_gotoxy(8, 1);
        lcd_puts(button_name);
        _delay_us(2);
        input_counter++;
      }
      else if (input_counter == 1) // first digit (MSB)
      {
        lcd_gotoxy(8, 1);
        lcd_puts("        ");
        lcd_gotoxy(8, 1);
        lcd_puts(button_name);
        digits[0] = atoi(button_name);
        input_counter++;
      }

      else if (input_counter < 5) // 2nd - 4th(LSB) digit of frequency
      {
        lcd_gotoxy(7 + input_counter, 1);
        lcd_puts(button_name);
        digits[input_counter - 1] = atoi(button_name);
        input_counter++;
      }

      else if (input_counter == 5) // wait for enter frequency with exponent (Hz, kHz, MHz)
      {
        switch (pos)
        {
        case 12:
          my_exponent = " Hz";
          frequency = 1000 * digits[0] + 100 * digits[1] + 10 * digits[2] + digits[3];
          lcd_gotoxy(7 + input_counter, 1);
          lcd_puts(" Hz");
          uart_puts("frequency: ");
          input_counter = 0;
          im_in_freq = 0;
          break;

        case 22:
          my_exponent = "kHz";
          frequency = 1000 * digits[0] + 100 * digits[1] + 10 * digits[2] + digits[3];
          lcd_gotoxy(7 + input_counter, 1);
          lcd_puts(" kHz");
          input_counter = 0;
          im_in_freq = 0;
          break;

        case 32:
          my_exponent = "MHz";
          frequency = 1000 * digits[0] + 100 * digits[1] + 10 * digits[2] + digits[3];
          lcd_gotoxy(7 + input_counter, 1);
          lcd_puts(" MHz");
          input_counter = 0;
          im_in_freq = 0;
          break;

        default: // do nothing untill Hz, kHz or MHz is pressed
          break;
        } //switch
      }   //else if
    }     //if
    else  //send position of matrix input, frequency and exponent to UART
    {
    } //else
  }
  pre_pos = pos; // to avoid multiple press
} //ISR
