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
    int front_sensor = 1;
    
    for(;;){ 
        
        //stop all
        if (Q1_Read() && Q2_Read() && Q3_Read() && Q4_Read() && Q5_Read() && Q6_Read() && Q7_Read()){
            controlWheels(STOP, STOP);
        }
        else if (!Q7_Read() && Q1_Read()&& Q2_Read() && Q3_Read()){
            front_sensor = 0;
            controlWheels(MEDIUM_FORWARD, MEDIUM_FORWARD);
            //turn left
            if (!Q5_Read() && !Q7_Read() && !Q6_Read()){
                controlWheels(STOP, STOP);
                //controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
            }
            else if (!Q4_Read() && !Q7_Read() && !Q6_Read()){
                controlWheels(STOP, STOP);
                //controlWheels(MEDIUM_FORWARD, MEDIUM_REVERSE);
            }
        }
        else if (!Q2_Read()){
            front_sensor = 1;
            controlWheels(MEDIUM_FORWARD, MEDIUM_FORWARD);  
        }
        else {
            while (!(Q1_Read() && Q3_Read() & Q5_Read() & Q4_Read())){
                if (front_sensor == 1){
                    if (!Q3_Read()){
                        controlWheels(MEDIUM_FORWARD, SLOW_FORWARD);
                    }
                    if (!Q1_Read()){
                        controlWheels(SLOW_FORWARD, MEDIUM_FORWARD);
                    }
                }
                else if (front_sensor == 0) {
                    if (!Q4_Read()){
                        controlWheels(MEDIUM_FORWARD, SLOW_FORWARD);
                    }
                    if (!Q5_Read()){
                        controlWheels(SLOW_FORWARD, MEDIUM_FORWARD);
                    }
                }
            }
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