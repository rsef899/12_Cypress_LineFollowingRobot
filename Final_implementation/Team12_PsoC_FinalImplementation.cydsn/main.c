/* ========================================
 * Fully working code: 
 * PWM      : 
 * Encoder  : 
 * ADC      :
 * USB      : port displays speed and position.
 * CMD: "PW xx"
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <project.h>
//* ========================================
#include "defines.h"
#include "vars.h"
//* ========================================
//* ==== Our functionsality Includes =======
#include "movement.h"
#include "states.h"

//*=========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
//* ========================================

uint8_t currentState = DRIVING;

int main(){
    
// --------------------------------    
// ----- INITIALIZATIONS ----------
        CYGlobalIntEnable;   
    
    M2_INV_Write(1);
    
    //PWM1
    PWM_1_Start();
    //PWM2
    PWM_2_Start();   
    
    controlWheels(STOP, STOP);
    currentState = DRIVING;
    
    for(;;){

        
        
        switch(currentState){
            case (DRIVING):
            LED_GREEN_Write(1);
            LED_BLUE_Write(0);
                
                controlWheels(64, MEDIUM_FORWARD);
                
                if (!(Q1_Read() && Q2_Read() && Q3_Read()) && ((Q1_Read() && Q2_Read()) || (Q2_Read() && Q3_Read()))) {
                    currentState = CALIBRATING;
                }
               
                break;
                
            case (CALIBRATING):
                LED_GREEN_Write(0);
                LED_BLUE_Write(1);
                controlWheels(64, MEDIUM_FORWARD);
                
                    if (Q1_Read() && Q2_Read() && Q3_Read()){
                        currentState = DRIVING;
                    }
                    // right correction
                    if (!Q3_Read()){
                            controlWheels(MEDIUM_FORWARD, SLOW_FORWARD);
                    }
                    // left correction
                    if (!Q1_Read()){
                        controlWheels(SLOW_FORWARD, MEDIUM_FORWARD);  
                    }
                 
                break;
        }
           
    }
            
        
    
}//End main



//* ========================================
void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')

#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    s[63]='\0';
    s[62]='!';
    USBUART_PutData((uint8*)s,strlen(s));
#endif
}
//* ========================================
void usbPutChar(char c)
{
#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    USBUART_PutChar(c);
#endif    
}
/* [] END OF FILE */
