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


uint8_t timeIndex = 0;
uint8_t timeArray[2];
uint8_t printSpeed = 0;


//Interupts
CY_ISR(QuadDecoderIsr){
    if (timeIndex == 0){
        timeArray[0] = QuadDec_M2_GetCounter();
        timeIndex = 1;
    } else {
        timeArray[1] = QuadDec_M2_GetCounter();
        timeIndex = 0;
        printSpeed = 1;      
    }
}



int main(){
    
// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;   
    
    M1_INV_Write(1);
    
    //PWM1
    PWM_1_Start();
    //PWM2
    PWM_2_Start();   
    
    //QuadEncoder initialisation
    isr_quad_timer_StartEx(QuadDecoderIsr);
    Quad_TImer_Start();
    
    
    // control signals
    uint8_t currentState = 0;
    volatile uint8_t mode = FREERUNNING;
    volatile uint8_t cal = 0;   
    
    for(;;)
    {
        
        //StateMachine
        switch (currentState){
            case (MODESELECT):
                switch (mode){
                    case (FREERUNNING):
                       currentState = FREERUNNING;
                    break;
                    case (SHORTESTMODE):
                        currentState = SHORTESTMODE;
                    break;
            break;
                }
            case (FREERUNNING):
                //TODO:  code to see if calibration is needed
                switch (cal){
                    case (1):
                        currentState = CALIBRATING;
                    break;
                    case(0):
                        currentState = DRIVING;
                    break;   
                }
             break;
            case (DRIVING):
                //drive
                controlWheels(FULL_FORWARD, FULL_FORWARD);
               
                
                if (!Q5_Read() || !Q4_Read()){
                    currentState = STOP;
                }
                if (Q2_Read() && !Q6_Read()){
                    currentState = CALIBRATING;
                }
                if (Q1_Read() && Q2_Read() && Q3_Read() && !Q4_Read()){
                    currentState = STOPCAR;
                }
                    
            break;
            case (STOP):
                controlWheels(STOP, STOP);
                if (!Q5_Read() || !Q4_Read()){
                    currentState = TURNING;
                }
                       
            break;
            case (TURNING):
                switch (mode){
                    case(FREERUNNING):
                        if (!Q5_Read()){
                            turn(TURN_LEFT);
                        }
                        if (!Q4_Read()){
                            turn(TURN_RIGHT);
                        }
                        if (!Q2_Read() && (Q3_Read() && Q1_Read())){
                            currentState = STOP;
                        }
                    break;
                }
            break;
        }
        
        
        //QuadEncoder icode
        if (printSpeed == 1){
            uint16_t speed = timeArray[0] - timeArray[1];
            speed =  (float)speed / 1.31;
            
            //char buffer [64];
            //itoa(speed, buffer, 10);
           // USBUART_PutString(buffer);
            printSpeed = 0; 
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
