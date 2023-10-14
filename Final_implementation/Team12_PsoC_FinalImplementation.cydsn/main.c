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
#include "motor.h"
//* ========================================
//* ==== Our functionsality Includes =======
#include "movement.h"
#include "states.h"
//*=========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
//* ========================================
# define MAX_PATH_SIZE 128
typedef struct Point {
    uint8_t x,y,direction,node,finalTurn,foodPoint,steps  ;
} Point;

#define FORWARD    1
#define BACKWARD  2
#define LEFT  3
#define RIGHT 4

#define go_speed 15.0

static Point pathArray[MAX_PATH_SIZE] = {{1,1,FORWARD,1,0,0,0},{1,1,FORWARD,1,0,0,0},{1,3,LEFT,1,0,0,0}, {1,3,LEFT,1,0,0,0},{1,3,RIGHT,1,0,0,0},{1,3,LEFT,1,0,0,0},{1,3,LEFT,1,0,0,0},{1,3,RIGHT,1,1,0,4},{1,3,LEFT,1,0,1,0}};
uint8_t currentState = DRIVING;
uint8_t firstEntry = 0;
volatile int noSensor = 0;

CY_ISR(Sensor_Timer_Isr){
    noSensor = 0;
    Timer_Sensor_Stop();
    LED_GREEN_Write(0);
    LED_BLUE_Write(0);
    LED_Write(1);
}

int main(){
    
// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;   
    M2_INV_Write(1);
    //controlWheels(STOP, STOP);
    
    
    uint8_t intersect = 0;
    //#ifdef USE_USB
    //    USBUART_Start(0, USBUART_5V_OPERATION);
    //#endif
    // instuction index
    uint8_t instructions = 0;
    // current instuction
    Point currentInstruction = pathArray[instructions++];
    
    Sensor_isr_StartEx(Sensor_Timer_Isr);
    
    int edgeFlag = 0;
    
    setupMotor();
    CyDelay(1000);
    currentState = DRIVING;
    
    for(;;){
        switch(currentState){
            case (DRIVING):
            
                controlWheels(MEDIUM_FORWARD_L, MEDIUM_FORWARD);

                if ((!Q5_Read() || !Q4_Read()) && !noSensor) {
                    currentState = PREPARETURN;
                    firstEntry = 1;
                    currentInstruction = pathArray[instructions++];
                }
                // if all the front sensors are not off the line
                // if either side of the sensor is off the line
                else if (!(Q1_Read() && Q2_Read() && Q3_Read()) && ((Q1_Read() && Q2_Read()) || (Q2_Read() && Q3_Read()))) {
                    currentState = CALIBRATING;
                }

                break;   
                
            case (DISTANCEDRIVING):
                LED_GREEN_Write(1);
                LED_BLUE_Write(1);
                LED_Write(1);
                if(motorControl(go_speed, go_speed, 10.00, Q1_Read(), Q2_Read())){
                    currentState = STOPCAR;
                }
                              
                break;           
            case (CALIBRATING):
                LED_GREEN_Write(0);
                LED_BLUE_Write(1);
                LED_Write(0);
                //controlWheels(MEDIUM_FORWARD_L, MEDIUM_FORWARD);
                               
                    // if the front wheels are all of the line, we must drive before turning
                    /*
                    if (Q1_Read() && Q2_Read() && Q3_Read()){
                        currentState = DRIVING;
                    }
                    if (!Q1_Read() && !Q3_Read()){
                        currentState = DRIVING;
                    }
                    */
                    /*
                    if ((!Q5_Read() || !Q4_Read()) && !noSensor) {
                        controlWheels(STOP, STOP);
                        currentState = PREPARETURN;
                        firstEntry = 1;
                        currentInstruction = pathArray[instructions++];
                    }
                    */
                    // right correction
                    if (!Q3_Read()){
                        controlWheels(MEDIUM_FORWARD, SLOW_FORWARD);
                    }
                    // left correction
                    if (!Q1_Read()){
                        controlWheels(SLOW_FORWARD, MEDIUM_FORWARD); 
                    }
                    currentState = DRIVING;
                break;       
            case(PREPARETURN):
                LED_GREEN_Write(0);
                LED_BLUE_Write(0);
                LED_Write(1);
                if(!currentInstruction.foodPoint) {
                    switch(currentInstruction.direction) {
                    case(LEFT):
                        controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
                         //Working Mostly
                        if ((firstEntry == 1 && Q2_Read() && Q1_Read() && Q3_Read())) { // i.e nothing in front -- wdc ab intersect then
                            intersect = 1;
                            controlWheels(STOP,STOP);
                            currentState = TURNING;
                        }
                        firstEntry = 0;
                        
                        
                        
                        if (!Q3_Read()) {
                            edgeFlag = 1;   
                            
                        }
                        if(Q2_Read() && Q3_Read() && edgeFlag == 1){
                            intersect = 1;
                            edgeFlag = 0;
                            controlWheels(STOP,STOP);
                            currentState = TURNING;
                        }
                      
                        
                        break;   
                    case(FORWARD):
                        controlWheels(MEDIUM_FORWARD_L, MEDIUM_FORWARD);
                        CyDelay(400);    // REVIEW MAYBE //
                        if (Q5_Read() && Q4_Read()){
                            controlWheels(MEDIUM_FORWARD_L, MEDIUM_FORWARD);
                            
                            
                            if (currentInstruction.steps){
                                currentState = DISTANCEDRIVING;
                            
                            } else{                                
                                currentState = DRIVING;
                            }
                            
                        }
                        firstEntry = 0;
                    
                        break;
                    case(RIGHT):
                        controlWheels(MEDIUM_FORWARD, MEDIUM_REVERSE);
                         //Working Mostly
                        if ((firstEntry == 1 && Q2_Read() && Q1_Read() && Q3_Read())) { // i.e nothing in front -- wdc ab intersect then
                            intersect = 1;
                            controlWheels(STOP,STOP);
                            currentState = TURNING;
                        }
                        firstEntry = 0;
                        
                        
                        
                        if (!Q1_Read()) {
                            edgeFlag = 1;   
                            
                        }
                        if(Q2_Read() && Q1_Read() && edgeFlag == 1){
                            intersect = 1;
                            edgeFlag = 0;
                            controlWheels(STOP,STOP);
                            currentState = TURNING;
                        }
                        break;
                    case(BACKWARD):
                        
                        break;
                    }
                } else {
                    controlWheels(STOP,STOP);
                    currentState = STOPCAR;
                }
                
                    break;
            case (TURNING):
                             
                switch(currentInstruction.direction){
                    LED_GREEN_Write(0);
                    LED_BLUE_Write(0);
                    LED_Write(1);
                    case(LEFT):
                       controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
                        
                        if (!Q1_Read() && !intersect){
                            controlWheels(STOP, STOP);
                            noSensor = 1;
                            Timer_Sensor_Start();
                                                    
                            if (currentInstruction.steps){
                                currentState = DISTANCEDRIVING;
                                CyDelay(500);
                            
                            } else{                                
                                currentState = DRIVING;
                            }
                        
                        }
                        
                        if (Q2_Read()){                            
                            intersect = 0;
                        }

                        break; 
                    case(RIGHT):
                        controlWheels(MEDIUM_FORWARD, MEDIUM_REVERSE);
                        
                        if (!Q3_Read() && !intersect){
                            controlWheels(STOP, STOP);
                            noSensor = 1;
                            Timer_Sensor_Start();
                                                     
                            if (currentInstruction.steps){
                                CyDelay(500);
                                currentState = DISTANCEDRIVING;
                                
                            
                            } else{                                
                                currentState = DRIVING;
                            }
                        
                        }
                        
                        if (Q2_Read()){                            
                            intersect = 0;
                        }

                        break; 
                }
               
                break;
            case (STOPCAR):
                controlWheels(STOP,STOP);
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
