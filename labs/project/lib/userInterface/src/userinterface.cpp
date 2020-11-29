#include <Arduino.h>        // delay definitions
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include <myMatrix.h>       // library for matrix scanning
#include <gpio.h>
#include "lcd.h"            // Peter Fleury's LCD library

const char* style[12]= {"homePage","freq","3","4","5","6","7","8","9","shift","0","enter"};

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

void freqPage(uint8_t LCD_Xposition, const char* button){
    if (LCD_Xposition < 2)
    {
        lcd_gotoxy(8,1);
        lcd_puts("      ");
    }
    else{
    lcd_gotoxy(LCD_Xposition+7,1);
    lcd_puts(button);
    }
}


void updateDisplay(uint8_t frequency, const char* waveform,bool shift, const char* type,const char* button_name){
    static uint8_t LCD_Xposition = 0;
    if (type == style[0])
    {
        homePage(frequency,waveform,shift);
    }
        if (type == style[1]) //freq
    {
        freqPage(LCD_Xposition, button_name);
        LCD_Xposition ++;
        if (LCD_Xposition == 4)
        {
            LCD_Xposition = 0;
        }
        
    }
}