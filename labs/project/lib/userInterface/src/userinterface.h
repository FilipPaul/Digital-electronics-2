#ifndef userinterface_H
#define userinterface_
#endif

#include <inttypes.h> //include int data types like uint8_t
#include <avr/pgmspace.h>

void updateDisplay(uint8_t frequency,const char* waveform, bool shift, const char* type);
void homePage(uint8_t frequency,const char* waveform,bool shift);

