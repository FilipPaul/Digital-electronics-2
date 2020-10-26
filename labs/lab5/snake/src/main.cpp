
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC
#include "gpio.h"
#include <Arduino.h>
int main(void)
{
   // Configure SSD signals
    SEG_init();
 

    while (1)
    {
      for (size_t i = 0; i < 6; i++)
      {
        my_snake(i,7);
        _delay_ms(400);
      }
      
     
    // Will never reach this    
    }
    return 0;
}

