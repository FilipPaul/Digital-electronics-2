#include <Arduino.h>        // delay definitions
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include <myMatrix.h>       // library for matrix scanning
#include <gpio.h>
#include "lcd.h"            // Peter Fleury's LCD library

const char* style[12]= {"homePage","2","3","4","5","6","7","8","9","shift","0","enter"};

void homePage(uint8_t frequency,const char* waveform,bool shift){
    char lcdString[2] = ""; // string for updading LCD
    lcd_gotoxy(1,0);
    lcd_puts("wave:");
    lcd_gotoxy(8,0);
    lcd_puts("     ");
    lcd_gotoxy(8,0);
    lcd_puts(waveform);

    lcd_gotoxy(1,1);
    lcd_puts("Freq:");
    lcd_gotoxy(8,1);
    itoa(frequency,lcdString,10);
    lcd_puts(lcdString);  
    if (shift == 0){  
        lcd_gotoxy(15,1);
        lcd_puts(" ");         
    }
    else
    {
        lcd_gotoxy(15,1);
        lcd_puts("S");
    }
}


void updateDisplay(uint8_t frequency, const char* waveform,bool shift, const char* type){
    if (type == style[0])
    {
        homePage(frequency,waveform,shift);
    }
}