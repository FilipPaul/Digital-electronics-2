
/* Includes ----------------------------------------------------------*/
#include <Arduino.h>
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */
//custom character
uint8_t customChar[8*8] = { //adress 0
	0b01000,0b10100,0b11100,0b00000,0b00111,0b00101,0b00111,0b10000,
//adress 1
    0b00010,0b00101,0b00111,0b00000,0b11100,0b10100,0b11100,0b00001,
//adress 2
    0b00001,0b00001,0b00000,0b00111,0b00001,0b00001,0b00010,0b00100,
// adress 3
	0b10000,0b10000,0b00000,0b11100,0b10000,0b10000,0b01000,0b00100,
// adress 4
	0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,
// adress 5
    0b11000,0b11000,0b11000,0b11000,0b11000,0b11000,0b11000,0b11000,    
// adress 6
    0b11100,0b11100,0b11100,0b11100,0b11100,0b11100,0b11100,0b11100,
// adress 7
    0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110
};

int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(4-1,0);
    lcd_puts(":");
    lcd_gotoxy(7-1,0);
    lcd_puts(".");
    lcd_gotoxy(10-1,0);
    lcd_puts("a");

// display custom character
 lcd_command(1 << LCD_CGRAM);
    for (uint8_t i = 0; i < 8*8; i++)
    {
        // Store all new chars to memory line by line
        lcd_data(customChar[i]);
    }
    // Set DDRAM address
    lcd_command(1 << LCD_DDRAM);
    
    // Display first custom character
    lcd_gotoxy(10-1,0);
    lcd_putc(0);
    lcd_gotoxy(11-1,0);
    lcd_putc(1); 
    lcd_gotoxy(10-1,1);
    lcd_putc(2);
    lcd_gotoxy(11-1,1);
    lcd_putc(3);  
    lcd_gotoxy(2-1,1);
  
    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms
    TIM2_overflow_16384us();
    TIM2_overflow_interrupt_enable();
    //timer for "progress bar"
    TIM0_overflow_1024us();
    TIM0_overflow_interrupt_enable();
    
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
    }
    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
ISR(TIMER0_OVF_vect)
// progress bar
{
    static uint16_t n = 0;
    static uint8_t c = 0; //character to display
    static uint8_t pos = 0; //character to display
    n++;
    if (n >= 28) //1024 us *28 = 28.7ms --> aprox 35 times per second (display 8x5 chars per second)
    {
        c++;
        if (c > 4){ // c = 5, move cursor and reset C
            c = 0; 
            pos++;
            if (pos >7-1){ // pos = 7 reset position and delete content
                pos = 0;
                lcd_gotoxy(1,1);
                lcd_puts("        "); // delete progress bar
            }
            lcd_gotoxy(pos+1,1);
            lcd_putc(c+4); // offset to correct character      
        }
        else if (c == 4 ){ //this symbol was already defined
            lcd_gotoxy(pos+1,1);
            lcd_putc(0xff); // all black 
        }
        else{ // c = 0,1,2
            lcd_gotoxy(pos+1,1);
            lcd_putc(c+4); // offset to correct character  
        } 
      n = 0;
    }

}


/**
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16384us = cca 100 ms).
 */
ISR(TIMER2_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
    static uint8_t tens = 0;
    static uint8_t secs = 0;
    static uint8_t secs10 = 0;
    static uint8_t min = 0;
    static uint8_t min10 = 0;
    char lcd_string[2]  = " ";
    number_of_overflows++;
    
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = cca 100 ms
        number_of_overflows = 0;
        tens++;
        if (tens > 9) 
        {
            secs++;
            tens = 0;
        }
        if (secs > 9){
            secs = 0;
            tens = 0;
            secs10++;
        }
        if (secs10 > 5){
            secs = 0;
            tens = 0;
            secs10 = 0;
            min++;
            lcd_gotoxy(13-1,0);
            lcd_puts("    "); //4 blank characters to reset
        }
        if (min > 9){
            secs = 0;
            tens = 0;
            secs10=0;
            min = 0;
            min10++;
        }
            if (min10 > 5){
            secs = 0;
            tens = 0;
            secs10=0;
            min = 0;
            min10 = 0;
        }

// display values
        itoa(tens,lcd_string,10);
        lcd_gotoxy(8-1,0);
        lcd_puts(lcd_string);

        itoa(secs,lcd_string,10);
        lcd_gotoxy(6-1,0);
        lcd_puts(lcd_string);

        itoa(secs10,lcd_string,10);
        lcd_gotoxy(5-1,0);
        lcd_puts(lcd_string);

        itoa(min,lcd_string,10);
        lcd_gotoxy(3-1,0);
        lcd_puts(lcd_string);

        itoa(min10,lcd_string,10);
        lcd_gotoxy(2-1,0);
        lcd_puts(lcd_string);
        //squared sec
        itoa((secs+secs10*10)*(secs+secs10*10),lcd_string,10);
        lcd_gotoxy(13-1,0);
        lcd_puts(lcd_string);
        number_of_overflows = 0;
    }
}