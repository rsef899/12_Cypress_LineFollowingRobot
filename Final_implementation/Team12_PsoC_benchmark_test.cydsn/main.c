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
    int front_sensor = 0;
    int dontCalibrate = 0;
    
    for(;;){ 
        controlWheels(64, 65);
        //stop all
        if (Q1_Read() && Q2_Read() && Q3_Read() && Q4_Read() && Q5_Read() && Q6_Read() && Q7_Read()){
            controlWheels(STOP, STOP);
        }
   
        else if ((Q1_Read() && Q2_Read() && Q3_Read())){
            LED_Write(0);
            dontCalibrate = 1;
            
            front_sensor = 0;
                   
            //If a left turn is detected
            if (!Q5_Read()){
                while(TRUE){
                    //if (!Q3_Read() || (!Q5_Read() && Q6_Read() && !Q2_Read())){
                    if (!Q2_Read()){
                        controlWheels(STOP, STOP);
                        dontCalibrate = 0;
                        break;
                    }
                    controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
                   
                }
                controlWheels(64, MEDIUM_FORWARD);
                //controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
            }
            //If a right turn is detected
            else if (!Q4_Read()){
                while(TRUE){
                    controlWheels(64, MEDIUM_REVERSE);
                    if (!Q2_Read()){
                    //if (!Q1_Read() || ((!Q4_Read()) && Q6_Read() && !Q2_Read())){
                        controlWheels(STOP, STOP);
                        dontCalibrate = 0;
                        break;
                    }
                    
                }
                controlWheels(64, MEDIUM_FORWARD);
                
                //controlWheels(MEDIUM_FORWARD, MEDIUM_REVERSE);
            }
        }
        // If the top middle sensor is on the line, set the front sensor flag and drive the wheels.
        else if (!Q2_Read()){
            front_sensor = 1;
            controlWheels(64, MEDIUM_FORWARD);
        }
        else if((((Q1_Read() && Q2_Read()) || (Q2_Read() && Q3_Read())) && dontCalibrate == 0)){
            LED_Write(1);
            // While the line is not in between the four surrounding sensors
            // run correction code
            if (((Q1_Read() && Q2_Read()) || (Q2_Read() && Q3_Read()))){
                
                // right correction
                while (!Q3_Read()){
                        controlWheels(MEDIUM_FORWARD, SLOW_FORWARD);                       
                }
                // left correction
                while (!Q1_Read()){
                    controlWheels(SLOW_FORWARD, MEDIUM_FORWARD);  
                    
                }
                LED_Write(0);
                
                
            }
            controlWheels(MEDIUM_FORWARD, MEDIUM_FORWARD);  
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
