#include <Arduino.h>
#define analog_pin = A0
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif
uint8_t analogValue = 100;
int led_detect = 0;
bool flag = 0;
void KnightRider()
{
   if (flag == 0){
      if ( led_detect == 7)
      {
      PORTD = PORTD & ~(1<<(led_detect-1));
      PORTD = PORTD | (1<<led_detect);
      led_detect = led_detect+1;
      flag = 1;
      }
      else if((led_detect < 8) && (led_detect != 0) ){
      PORTD = PORTD & ~(1<<(led_detect-1)); // turn pre led off
      PORTD = PORTD | (1<<led_detect);  // turn next led on
      led_detect = led_detect +1;
      }
      else if(led_detect == 0){
        PORTD = PORTD | (1<<led_detect);
        led_detect = led_detect+1;
      }
    }
  else if (flag == 1) {
      if (led_detect == 1)
      {  
      PORTD = PORTD & ~(1<<led_detect);
      PORTD = PORTD | (1<<(led_detect-1));
      led_detect = led_detect-1;
      flag = 0;
      }
      else if(led_detect == 8){
        PORTD = PORTD | (1<<led_detect);
        led_detect = led_detect-1;
      }
      else{
      PORTD = PORTD & ~(1<<led_detect);
      PORTD = PORTD | (1<<(led_detect-1));
      led_detect = led_detect - 1;
      }
    }
}

int main(void){
  for (int i = 0; i < 7+1; i++){

      // Set pin as output in Data Direction Register...
    DDRD = DDRD | (1<<i);
    // ...and turn LED off in Data Register
    PORTD = PORTD & ~(1<<i);

  }

    while (1)
    {
    //mydelay = analogRead(0)  //default 0-1023ms
      // there can be stored value potentiometer value, delay
  KnightRider();
  _delay_ms(100);
    }

    // Will never reach this
    return 0;
}
