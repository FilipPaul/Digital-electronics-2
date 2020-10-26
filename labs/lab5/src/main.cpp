
/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC
#include "gpio.h"
#include <Arduino.h>
uint8_t segment[] = {0,0,0,0,0,0,0,0}; // initial value
uint8_t muxflag = 1; // variable for multiplexing digits

int main(void)
{
    // timer for multiplexing
    TIM2_overflow_512us(); // 512us for each digit
    TIM2_overflow_interrupt_enable();

    // Configure SSD signals
    SEG_init();
    TIM1_overflow_262ms() ;
    TIM1_overflow_interrupt_enable();
    sei();
    // Infinite loop
    while (1)
    {

    // Will never reach this    
    }
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
ISR(TIMER1_OVF_vect)
{

    if(segment[7] == 9){
      segment[6] = segment[6] + 1;
      segment[7] = 0;
    }

    else
    {
        segment[7] = segment[7] + 1;
    }

    if(segment[6] == 6){  
        segment[6] = 0;  
        segment[7] = 0;      
    } 
}
ISR(TIMER2_OVF_vect){
    if (muxflag == 1){
    SEG_update_shift_regs(segment[7], 7);
    }
    else
    {
     SEG_update_shift_regs(segment[6], 6); 
    }
    muxflag = !muxflag;
    
}