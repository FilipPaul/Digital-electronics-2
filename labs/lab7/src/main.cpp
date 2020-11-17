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

/* Function definitions ----------------------------------------------*/
// returns 1 if odd (1,3.) and 0 if even(0,2...)
    bool myParity(uint16_t message){
    bool parity = 0;
    while (message) //while message == 1
    {
        parity =   ~parity;
        message =  message & (message -1);
    }
    return parity;    
    }

int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(1, 0); lcd_puts("value:");
    lcd_gotoxy(3, 1); lcd_puts("key:");
    lcd_gotoxy(8, 0); lcd_puts("a");    // Put ADC value in decimal
    lcd_gotoxy(13,0); lcd_puts("b");    // Put ADC value in hexadecimal
    lcd_gotoxy(8, 1); lcd_puts("c");    // Put button name here

    // Configure ADC to convert PC0[A0] analog value
    // Set ADC reference to AVcc
    //ADMUX = 010-0000
    //ADCSRA = 1000 1111
    ADMUX |= (1<<REFS0);
    ADMUX &=  ~(1<<REFS1);
    // Set input channel to ADC0
    ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3));
    // Enable ADC module
    ADCSRA |= (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA |= (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)| (1<<ADPS2));

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Enable interrupt and set the overflow prescaler to 262 ms
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600,F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        _delay_ms(100);

    if( myParity(ADC)){
        lcd_gotoxy(12,1);
        lcd_puts(" ");
        lcd_gotoxy(13,1);
        lcd_puts("odd");
        uart_puts(" parity: odd");
        uart_puts("\n");
    }
    else
    {
        lcd_gotoxy(12,1);
        lcd_puts("even");
        uart_puts(" parity: even");
        uart_puts("\n");
    }
    }
    

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter1 overflows. Use single conversion mode
 * and start conversion four times per second.
 */
ISR(TIMER1_OVF_vect)
{
    // Start ADC conversion
    ADCSRA |= (1<<ADSC);

}

/* -------------------------------------------------------------------*/
/**
 * ISR starts when ADC completes the conversion. Display value on LCD
 * and send it to UART.
 */
ISR(ADC_vect)
{

    // print ADC value
    static uint16_t value = 0;
    static uint16_t pre_value = 0; // to avoid flashing display
    char lcd_string[2] = "";
    value = ADC;    // Copy ADC result to 16-bit variable
    if(value !=  pre_value){   //clear display whenever value change
    lcd_gotoxy(8,0);
    lcd_puts("    ");
    lcd_gotoxy(13,0);
    lcd_puts("    ");
    itoa(value, lcd_string, 10);    // Convert decimal value to string
    lcd_gotoxy(8,0);
    lcd_puts(lcd_string);
    itoa(value, lcd_string, 16);
    lcd_gotoxy(13,0);
    lcd_puts(lcd_string);
    //print data to serial in HEX monitor via UART
    uart_puts("button pressed: ");
    uart_puts(lcd_string); 
    uart_puts("\n");

    }
    pre_value = value;
}
