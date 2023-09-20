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
    int error_flag = 0;
    
    for(;;){
        //stop all
        if (Q1_Read() && Q2_Read() && Q3_Read() && Q4_Read() && Q5_Read() && Q6_Read() && Q7_Read()){
            controlWheels(STOP, STOP);
        }
        // If the top middle sensor is on the line, set the front sensor flag and drive the wheels.
        else if (!Q2_Read() || !Q7_Read()){
            controlWheels(63, MEDIUM_FORWARD);
                
            if (Q1_Read()&& Q2_Read() && Q3_Read()){
                controlWheels(63, MEDIUM_FORWARD);
                
                //If a left turn is detected
                if (!Q5_Read()){
                    error_flag = 0;
                    while(TRUE){
                        if (!Q3_Read() || (!Q5_Read() && Q6_Read() && !Q2_Read())){
                            break;
                        }
                        controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
                        if (Q6_Read()){
                            error_flag = 1;
                        }
                        if (!Q6_Read() && error_flag && Q5_Read()){
                            while(TRUE){
                                controlWheels(MEDIUM_FORWARD, MEDIUM_REVERSE);
                                if (!Q3_Read()){
                                    break;
                                }
                            }
                        }
                    }
                    controlWheels(63, MEDIUM_FORWARD);
                    //controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
                }
                //If a right turn is detected
                else if (!Q4_Read()){
                    error_flag = 0;
                    while(TRUE){
                        if (!Q1_Read() || ((!Q4_Read()) && Q6_Read() && !Q2_Read())){
                            break;
                        }
                        controlWheels(MEDIUM_FORWARD, MEDIUM_REVERSE);
                        if (Q6_Read()){
                            error_flag = 1;
                        }
                        if (!Q6_Read() && error_flag && Q4_Read()){
                            while(TRUE){
                                controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
                                if (!Q1_Read()){
                                    break;
                                }
                            }
                        }
                    }
                    controlWheels(63, MEDIUM_FORWARD);
                    //controlWheels(MEDIUM_FORWARD, MEDIUM_REVERSE);
                }
            }
            
            // While the line is not in between the four surrounding sensors
            // run correction code
            while (!(Q1_Read() && Q3_Read() & Q5_Read() & Q4_Read())){

                // right correction
                if (!Q3_Read()){
                    controlWheels(MEDIUM_FORWARD, SLOW_FORWARD);
                }
                // left correction
                if (!Q1_Read()){
                    controlWheels(SLOW_FORWARD, MEDIUM_FORWARD);  
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