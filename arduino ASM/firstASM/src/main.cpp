#include <stdio.h>         
#include <stdlib.h>        // C library. Needed for conversion function
#include <avr/io.h>        // AVR device-specific IO definitions
#include "toggle.h"
#include "myDelay.h"
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC

int main(void) {

  TCCR1B &= ~((1<<CS11) | (1<<CS10)); TCCR1B |= (1<<CS12);
  TIMSK1 |= (1<<TOIE1);

  DDRC =  0b00110000;
  DDRB  = 0b11111111;
  PORTB = 0b01111111;
  sei();
 
while(1) 
{
}
return 0;

}

ISR(TIMER1_OVF_vect){
  static uint8_t k = 0;
  if (k == 0){ //print 8 on 1st disp
    PORTC = 0b00100000;
    PORTB =  0b11111111;
    k++;
  }
  else if ( k ==  1)
  {
    PORTC = 0b00010000;
    PORTB =  0b01101101;
    k = 0;
  }
  
}