#ifndef userinterface_H
#define userinterface_
#endif

#include <inttypes.h> //include int data types like uint8_t
#include <avr/pgmspace.h>

void updateDisplay(uint8_t frequency,const char* waveform, bool shift, const char* type,const char* button_name);
void homePage(uint8_t frequency,const char* waveform,bool shift);
void freqPage(uint8_t LCD_Xposition, const char* button);

