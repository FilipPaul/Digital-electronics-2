#include <Arduino.h>        // delay definitions
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include <myMatrix.h>       // library for matrix scanning
#include <gpio.h>
#include "lcd.h"            // Peter Fleury's LCD library

uint8_t columns[4] = {Col_1,Col_2,Col_3,Col_4};
uint8_t rows[3] = {row_3,row_2,row_1};
const char* buttons_look_up[13]= {"1","2","3","4","5","6","7","8","9","shift","0","enter","none"};
const char* shift_buttons_look_up[13]= {"freq","sine","ramp","Hz","kHz","MHz","7","8","9","shift","0","enter","none"};
bool shift = 0; // to store shift button


void initMatrix(){
    // set collumn pins as inputs with internal pullups
    for (size_t i = 0; i < 4; i++)
    {
     GPIO_config_input_pullup(&MATRIX_MODE_PORT, columns[i]); 
    }
    

    // set rows as outputs HIGH
    for (size_t i = 0; i < 3; i++)
    {
       GPIO_config_output(&MATRIX_MODE_PORT, rows[i]);
       GPIO_write_high(&MATRIX_PORT, rows[i]);
    }    
}


uint8_t scanMatrix(){ //returns int like 14 --> row 1, column 4
   static uint8_t pos_row;
   static uint8_t pos_column;
   static uint8_t pre_pos = 0;  
   static uint8_t pos = 0;  //row x column 
   static uint8_t n =0; //variable to check if nothing was pressed
    for (size_t i = 0; i < 3; i++)
    {   
        //set row to LOW and scan through collumns
        GPIO_toggle(&MATRIX_PORT, rows[i]); // set row pin LOW
        for (size_t k = 0; k < 4; k++) // scan through all columns
        { _delay_us(20); // needed for its functionality
            if (GPIO_read(&PINC, columns[k]) == 0)
            {
                pos_row = i+1;
                pos_column = k+1;
                pos = 10*pos_row+pos_column;
                
            }//if  
            else
            {
                n++;
            }
                 
        }//for
    GPIO_toggle(&MATRIX_PORT, rows[i]);  // set row pin HIGH
    }//for 
    if (n == 12){ // nothing was pressed
        pos = 0;
    }
    if ((pos == 14) && (pos != pre_pos)){ // shift position
        shift = !shift;
    }
    /*else if ((pos != 14) && (shift == 1)&&(pos != 0))
    {
        shift = 0;
    }*/
    
    n = 0;
    pre_pos = pos;   
    return pos;  
     
}//void


const char* posToConstChar(uint8_t pos){
    const char* button_name;
    switch (pos)
    {
    case 11:
    button_name = shiftFun(0); //1 or freq
        break;
    case 21:
        button_name = shiftFun(1); //2 or sine
        break;
    case 31:
        button_name = shiftFun(2);//3 or ramp
        break; 
    case 12:
        button_name = shiftFun(3);// 4 or Hz 
        break; 
    case 22:
        button_name = shiftFun(4);// 5 or kHz
        break; 
    case 32:
        button_name = shiftFun(5);// 6 or MHz
        break;         
    case 13:
        button_name = shiftFun(6);
        break; 
    case 23:
        button_name = shiftFun(7);
        break; 
    case 33:
        button_name = shiftFun(8);
        break; 
    case 14:
        button_name = shiftFun(9);//shift
        break;
    case 24:
        button_name = shiftFun(10);//0
        break; 
    case 34:
        button_name = shiftFun(11);//enter/decimal
        break;  
    case 0:
        button_name = shiftFun(12);
        break;         

    default:
        button_name = "Init";
        break;
    }
    return button_name;
}


const char* shiftFun(uint8_t number){
    const char* button_name;
    if (shift == 0)
    {
        button_name = buttons_look_up[number];
    }
    else
    {
        button_name = shift_buttons_look_up[number];

    }   
    return button_name;
}

/*uint16_t freqSetting(){
    char lcdString[2] = "";
    static uint8_t pos;
    const char* inputNumber;
    
    lcd_gotoxy(1, 0); lcd_puts("Freq settings");
    lcd_gotoxy(1, 1); lcd_puts("Freq:");
    pos = scanMatrix();
    inputNumber = posToConstChar(pos);
    
    lcd_gotoxy(8, 1); lcd_puts("sine");    // Put ADC value in decimal
}*/