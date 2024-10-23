#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdint.h> 
#include "operations.h"

char get_button(int16_t x, int16_t y){
    char button_pressed;

    if( x<80 && x > 11){
        if(y > 43 && y < 90){
            button_pressed = '7'; 
        }
        else if(y > 96 && y < 145){
            button_pressed = '4';  
        }
        else if(y > 148 && y < 196){
            button_pressed = '1';  
        }
        else if(y > 200 && y < 240){
            button_pressed = '0';  
        }
        else 
            button_pressed = ' '; 
    } 
       
    else if(x<156 && x > 85 ){
         if(y > 43 && y < 90){
            button_pressed = '8'; 
        }
        else if(y > 96 && y < 145){
            button_pressed = '5';  
        }
        else if(y > 148 && y < 196){
            button_pressed = '2';  
        }
        else if(y > 200 && y < 240){
            button_pressed = 'C';  
        }
        else 
            button_pressed = ' '; 

    }

    else if(x<230 && x > 161 ){
         if(y > 43 && y < 90){
            button_pressed = '9'; 
        }
        else if(y > 96 && y < 145){
            button_pressed = '6';  
        }
        else if(y > 148 && y < 196){
            button_pressed = '3';  
        }
        else if(y > 200 && y < 240){
            button_pressed = '=';  
        }
        else 
            button_pressed = ' '; 

    }

    else if(x<308 && x > 236 ){
         if(y > 43 && y < 90){
            button_pressed = '+'; 
        }
        else if(y > 96 && y < 145){
            button_pressed = '-';  
        }
        else if(y > 148 && y < 196){
            button_pressed = 'x';  
        }
        else if(y > 200 && y < 240){
            button_pressed = '/';  
        }
        else 
            button_pressed = ' '; 

    }
    else
         button_pressed = ' '; 



    return button_pressed; 
}


void calculator_fsm(){
    switch (INIT)
    {
    case /* constant-expression */:
        /* code */
        break;
    
    default:
        break;
    }
}


