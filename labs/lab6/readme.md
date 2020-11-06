<h1> Lab 6 </h1>
<h2> Preparation Task</h2>

   | **LCD signal(s)** | **AVR pin(s)** | **Description** |
   | :-: | :-: | :-- |
   | RS | PB0 | Register selection signal. Selection between Instruction register (RS=0) and Data register (RS=1) |
   | R/W | GND | LOW - WRITE to the display, HIGH READ - read from display|
   | E | PB1 | enable. This loads the data into the HD44780 on the falling edge |
   | D[3:0] | PD3 - PD0 | data pins for custom characters |
   | D[7:4] | PD7 - PD4 | Upper nibble used in 4-bit mode |

What is the ASCII table? What are the values for uppercase letters `A` to `Z`, lowercase letters `a` to `z`, and numbers `0` to `9` in this table?

ASCII table is a way how to describe characters with numbers in DEC, BIN, HEX etc. Each special charracter or letter is assigned to a number. For example 'A' is represented by: DEC 65, HEX 41 and bin 100 0001.
<br>
<h3>ASCII table </h3>

<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab6/pictures/ASCII.PNG">


<h2> Lab results</h2>
<h3> Table of functions from LCD library</h3>

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `lcd_init` | `LCD_DISP_OFF`<br>`LCD_DISP_ON`<br>`LCD_DISP_ON_CURSOR`<br>`LCD_DISP_ON_CURSOR_BLINK` | Display off &nbsp;<br>Display on, cursor off &nbsp;<br> Display on, cursor on &nbsp;<br>Display on, cursor on, blink char &nbsp;| `lcd_init(LCD_DISP_OFF);` |
   | `lcd_clrscr` | none| Clear display and set cursor to home position. | `lcd_clrscr();` |
   | `lcd_gotoxy` | uint8_t x, uint8_t y | set cursor's position | `lcd_gotoxy(x,y);` |
   | `lcd_putc` | char c | Display character at current cursor position. | `lcd_putc(c);` |
   | `lcd_puts` | string s | Display string without auto linefeed. | `lcd_puts(s);` |
   | `lcd_command` |uint8_t cmd	instruction to send to LCD controller | Send LCD controller instruction command. | `lcd_command(cmd)`|
   | `lcd_data` | uint8_t data | Send data byte to LCD controller. | `lcd_data(data);`|

<h3> HD44780 communication, message: DE2</h3>
<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab6/pictures/message.jpg">

<h3> Simulation </h3>
<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab6/pictures/simulation.png">

<h3> main.cpp</h3>
<br>

```cpp

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

```


