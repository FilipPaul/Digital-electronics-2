//Structure
#include <Arduino.h>
#include <stdlib.h>        // C library. Needed for conversion function
#include <stdio.h>        // C library. Needed for printf and etc
#include <avr/io.h>        // AVR device-specific IO definitions
#include <avr/interrupt.h> // Interrupts standard C library for AVR-GCC

uint16_t int16bit = 0;
uint8_t int8bit = 0;
uint8_t num = 0;
uint8_t num_point = 0;
uint8_t *p = &int8bit;
int inc(uint8_t num)
{
   num ++;
}

int incpoint(uint8_t *nump)
{
   *nump = (*nump) + 1;
}

int main(void) {

//Serial.begin(9600);
// -------------------------------------------pin deffinicions--------------
//DDRC = DDRC | (1<<pin_number); // set pin C2 as output (sett DDRx port)

/*
DDRD = DDRD | (1<<3);
PORTD = PORTD | (1<<3);
*/

//--------------------------------------------------timer settings
/*
#define TIM1_stop()             TCCR1B &= ~((1<<CS12) | (1<<CS11) | (1<<CS10));  //000 stop
#define TIM1_overflow_4ms()     TCCR1B &= ~((1<<CS12) | (1<<CS11)); TCCR1B |= (1<<CS10); 
#define TIM1_overflow_33ms()    TCCR1B &= ~((1<<CS12) | (1<<CS10)); TCCR1B |= (1<<CS11);
#define TIM1_overflow_262ms()   TCCR1B &= ~(1<<CS12); TCCR1B |= (1<<CS11) | (1<<CS10);
#define TIM1_overflow_1s()      TCCR1B &= ~((1<<CS11) | (1<<CS10)); TCCR1B |= (1<<CS12);
#define TIM1_overflow_4s()      TCCR1B &= ~(1<<CS11); TCCR1B |= (1<<CS12) | (1<<CS10);

#define TIM1_overflow_interrupt_enable()    TIMSK1 |= (1<<TOIE1); // wirte 1 in TIMSK1 reg on possition 0
#define TIM1_overflow_interrupt_disable()   TIMSK1 &= ~(1<<TOIE1); // wirte 0 in TIMSK1 reg on possition 0
*/

//set TIM1 to 4ms and enable it
//TCCR1B &= ~((1<<CS12) | (1<<CS11)); TCCR1B |= (1<<CS10);// 001 1:1 --> 2^16/16MHz = cca 4ms
//TCCR1B &= ~((1<<CS11) | (1<<CS10)); TCCR1B |= (1<<CS12);
//TIMSK1 |= (1<<TOIE1); //1
//_delay_ms(100);
//sei(); //set all interrupts
//----------------------------------------------------------------------------------------

pinMode(9,OUTPUT);

   //-------------- pointers --------------------
//int variable = 10; // variable with value of 10
//int *p ; // pointer 
//p = &variable; //

/*
    Memmory
   |       variable = 10      | <-- memmory adress of &variable for ex: adress = 204
   |                          |
   |                          |
   | p = &variable; value 204 | <-- memmory adress &p for ex: 101
*/
   //print p --> adress of "variable" 204
   //print *p --> 10 value of variable from adress 204
   // variable = 50; print *p --> 50, print p --> adress of variable
   // print &p --> adress of p, 101


  while(1)
  {
   //endles loop
   PORTB = 0x2;
   PORTC = 0b00100000;
   PORTC = 0b00000000;
   PORTB = 0x0;

  }
  //never reach this
  return 0;
}

// ISR for TIM 1 overflow
/*
ISR(TIMER1_OVF_vect)
{
   if (num_point == 255){
      num_point = 0;      
   }
   inc(num);
   incpoint(&num_point);
   Serial.println(num_point);
   Serial.println(num);
}
*/