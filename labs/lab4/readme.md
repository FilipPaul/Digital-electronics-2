<h1> Lab 4 </h1>
<h2> Preparation tasks </h2>

| **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Timer/Counter0 | 8  | 16us | 128us | -- |1.024ms | -- | 4.096ms | 16.384ms |
| Timer/Counter1 | 16 | 4.096ms | 32.768ms | -- | 262.144ms | -- | 1.048576s | 4.194304s |
| Timer/Counter2 | 8  | 16us | 128us | 512us | 1.024ms | 2.048ms | 4.096ms | 16.384ms |


| **Module** | **Operation** | **I/O register(s)** | **Bit(s)** |
| :-: | :-- | :-: | :-- |
| Timer/Counter0 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR0B<br><br>TCNT0<br>TIMSK0 | CS02, CS01, CS00<br>(000: stopped, 001:1, 010:8, 011:64, 100:256, 101:1024<br>TCNT0[7:0] <br> TOIE0(1:enable, 0:disable)|
| Timer/Counter1 | Prescaler<br><br>16-bit data value<br>Overflow interrupt enable | TCCR1B<br><br>TCNT1H, TCNT1L<br>TIMSK1 | CS12, CS11, CS10<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)<br>TCNT1[15:0]<br>TOIE1 (1: enable, 0: disable) |
| Timer/Counter2 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR2B<br><br>TCNT2<br>TIMSK2 | CS22, CS21, CS20<br>(000: stopped, 001: 1, 010: 8, 011: 32, 100: 64, 101: 128, 110: 256, 111: 1024)<br>TCNT2[7:0]<br>TOIE2 (1: enable, 0: disable) |



| **Program address** | **Source** | **Vector name** | **Description** |
| :-: | :-- | :-- | :-- |
| 0x0000 | RESET | -- | Reset of the system |
| 0x0002 | INT0  | External Interrupt 0 |
| 0x0004 | INT1 | INT1_vect | External Interrupt Request 1 |
| 0x0006 | PCINT0 | PCINT0_vect | Pin Change Interrupt Request 0 |
| 0x0008 | PCINT1 | PCINT1_vect | Pin Change Interrupt Request 1 |
| 0x000A | PCINT2 | PCINT2_vect | Pin Change Interrupt Request 2 |
| 0x0012 | TIMER2_OVF | TIMER2_OVF_vect | Timer/Counter2 Overflow |
| 0x001A | TIMER1_OVF | TIMER1_OVF_vect | Timer/Counter1 Overflow |
| 0x0020 | TIMER0_OVF | TIMER0_OVF_vect | Timer/Counter0 Overflow |
| 0x002A | ADC | ADC_vect | ADC Conversion Complete |
| 0x0030 | TWI | TWI_vect | 2-wire Serial Interface |

| **Module** | **Description** | **MCU pin** | **Arduino pin** |
| :-: | :-: | :-: | :-: |
| Timer/Counter0 | OC0A | PD6 | 6 |
|                | OC0B | PB5 | 5 |
| Timer/Counter1 | OC1A | PB1 | 9 |
|                | OC1B | PB2 | 10 |
| Timer/Counter2 | OC2A | PB3 | 11 |
|                | OC2B | PD3 | 3 |

<h2> Source code</h2>
<h3> Timer.h </h3>

```c
#ifndef TIMER_H
#define TIMER_H

/***********************************************************************
 * 
 * Timer library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2019-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/*
 * @file  timer.h
 * @brief Timer library for AVR-GCC.
 *
 * @details
 * The library contains macros for controlling the timer modules.
 *
 * @note
 * Based on Microchip Atmel ATmega328P manual and no source file is 
 * needed for the library.
 * 
 * @copyright (c) 2019-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
//---------------------Timer 1 ------------------------------------------------------------
/* Defines -----------------------------------------------------------*/
/*
 * @brief Defines prescaler CPU frequency values for Timer/Counter1.
 * @note  F_CPU = 16 MHz
 */

#define TIM1_stop()             TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));
#define TIM1_overflow_4ms()     TCCR1B &= ~((1<<CS12) | (1<<CS11)); TCCR1B |= (1<<CS10);
#define TIM1_overflow_33ms()    TCCR1B &= ~((1<<CS12) | (1<<CS10)); TCCR1B |= (1<<CS11);
#define TIM1_overflow_262ms()   TCCR1B &= ~(1<<CS12); TCCR1B |= (1<<CS11) | (1<<CS10);
#define TIM1_overflow_1s()      TCCR1B &= ~((1<<CS11) | (1<<CS10)); TCCR1B |= (1<<CS12);
#define TIM1_overflow_4s()      TCCR1B &= ~(1<<CS11); TCCR1B |= (1<<CS12) | (1<<CS10);

/*
 * @brief Defines interrupt enable/disable modes for Timer/Counter1.
 */
#define TIM1_overflow_interrupt_enable()    TIMSK1 |= (1<<TOIE1);
#define TIM1_overflow_interrupt_disable()   TIMSK1 &= ~(1<<TOIE1);

//---------------------Timer 0 ------------------------------------------------------------
/* Defines -----------------------------------------------------------*/
/*
 * @brief Defines prescaler CPU frequency values for Timer/Counter0.
 * @note  F_CPU = 16 MHz
 */

#define TIM0_stop()             TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));//000
#define TIM0_overflow_16us()     TCCR0B &= ~((1<<CS02) | (1<<CS01)); TCCR0B |= (1<<CS00);//001
#define TIM0_overflow_128us()    TCCR0B &= ~((1<<CS02) | (1<<CS00)); TCCR0B |= (1<<CS01);//010
#define TIM0_overflow_1024us()   TCCR0B &= ~(1<<CS02); TCCR0B |= (1<<CS01) | (1<<CS00);//011
#define TIM0_overflow_4096us()      TCCR0B &= ~((1<<CS01) | (1<<CS00)); TCCR0B |= (1<<CS02);//100
#define TIM0_overflow_16384us()      TCCR0B &= ~(1<<CS01); TCCR0B |= (1<<CS02) | (1<<CS00);//101

/*
 * @brief Defines interrupt enable/disable modes for Timer/Counter0.
 */
#define TIM0_overflow_interrupt_enable()    TIMSK0 |= (1<<TOIE0);
#define TIM0_overflow_interrupt_disable()   TIMSK0 &= ~(1<<TOIE0);

//---------------------Timer 2 ------------------------------------------------------------
/* Defines -----------------------------------------------------------*/
/*
 * @brief Defines prescaler CPU frequency values for Timer/Counter2.
 * @note  F_CPU = 16 MHz
 */

#define TIM2_stop()                 TCCR2B &= ~((1<<CS22) | (1<<CS21) | (1<<CS20));//000
#define TIM2_overflow_16us()        TCCR2B &= ~((1<<CS22) | (1<<CS21)); TCCR2B |= (1<<CS20);//001
#define TIM2_overflow_128us()       TCCR2B &= ~((1<<CS22) | (1<<CS20)); TCCR2B |= (1<<CS21);//010
#define TIM2_overflow_512us()       TCCR2B &= ~(1<<CS22); TCCR2B |= (1<<CS21) | (1<<CS20);//011
#define TIM2_overflow_1024us()      TCCR2B &= ~((1<<CS21) | (1<<CS20)); TCCR2B |= (1<<CS22);//100
#define TIM2_overflow_2048us()      TCCR2B &= ~(1<<CS21); TCCR2B |= (1<<CS22) | (1<<CS20);//101
#define TIM2_overflow_4096us()      TCCR2B &= ~(1<<CS20); TCCR2B |= (1<<CS22)|(1<<CS21); //110
#define TIM2_overflow_16384us()     TCCR2B |= (1<<CS22)|(1<<CS21) | (1<<CS20);           //111


/*
 * @brief Defines interrupt enable/disable modes for Timer/Counter2.
 */
#define TIM2_overflow_interrupt_enable()    TIMSK2 |= (1<<TOIE2);
#define TIM2_overflow_interrupt_disable()   TIMSK2 &= ~(1<<TOIE2);

#endif

```

<h3> main.cpp </h3>

```c
#include <Arduino.h>
/***********************************************************************
 * 
 * Control LEDs using functions from GPIO and Timer libraries. Do not 
 * use delay library any more.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_D1  PB5
#define LED_D2  PB4
#define LED_D3  PB3

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC


/* Function definitions ----------------------------------------------*/
/*
 * Main function where the program execution begins. Toggle three LEDs
 * on Multi-function shield with internal 8- and 16-bit timer modules.
 */
int main(void)
{
    /* Configuration of three LEDs */
    GPIO_config_output(&DDRB, LED_D2);
    GPIO_write_low(&PORTB, LED_D2);

    GPIO_config_output(&DDRB, LED_D1);
    GPIO_write_low(&PORTB, LED_D1);

    GPIO_config_output(&DDRB, LED_D3);
    GPIO_write_low(&PORTB, LED_D3);
    // WRITE YOUR CODE HERE

    /* Configuration of 8-bit Timer/Counter0 */
    TIM0_overflow_4096us();
    TIM0_overflow_interrupt_enable();

    /* Configuration of 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    /* Configuration of 8-bit Timer/Counter2 */
    TIM2_overflow_16384us();
    TIM2_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter1 overflows. Toggle LED D2 on 
 * Multi-function shield. */
ISR(TIMER1_OVF_vect)
{
    GPIO_toggle(&PORTB,LED_D1);
}
ISR(TIMER2_OVF_vect)
{
   GPIO_toggle(&PORTB,LED_D2); 
}
ISR(TIMER0_OVF_vect)
{
   GPIO_toggle(&PORTB,LED_D3); 
}

```
<h3> Simulation </h3>
<img src = "https://github.com/FilipPaul/Digital-Electronics-2/blob/master/labs/lab4/pictures/simulation.gif">
<h3> Answers to questions </h3>
ISR() is function, that is called whenever specific condition meets interupts condition, input of this function is predefined vector, that defines type of interupt. For EX: ISR(TIMER0_OVF_vect) execute its code whenever Timer 1 overflow. This function is called asynchronously. <br>
Common C function is called from source code from line, where the function is called. This function is called synchronously.<br>
Clear Timer on Compare - this method counts into given number of Timer, if the number of counts is equal to our given number ,it resets counter value and start again from 0. We can define what should be executed in ISR function.<br>
Fast PWM modes, uses Timers for changing automaticaly logical levels at GPIOs without calling ISR function from script.

