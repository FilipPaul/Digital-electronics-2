#include <stdio.h>         
#include <stdlib.h>        // C library. Needed for conversion function
#include <avr/io.h>        // AVR device-specific IO definitions
#include "toggle.h"
#include "myDelay.h"

extern void wait();

int main(void) {
  DDRB = 0b00000010;
  mysDelay(150);
  //toggle();


while(1) 
{
}
return 0;
}