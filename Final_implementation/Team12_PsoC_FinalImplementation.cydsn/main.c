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
#include "algo.h"
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


#define FORWARD    1
#define BACKWARD  2
#define LEFT  3
#define RIGHT 4

#define go_speed 15.0
#define COUNT_OF(x)\
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))
//* ===========================================
// MAP and FOOD

static uint8_t map[15][19] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
{1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1},
{1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1},
{1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1},
{1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1},
{1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1},
{1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
{1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

static Point food_list[]= {
{1,9},
{5,5},
{7,1},
{13,5},
{9,9}
};

/*static Point food_list[] = {
    
    {15,5},{13,5},{11,1},{9,7},{7,13}   
};*/
//* ===========================================

static const Point start = (Point){.x = 1, .y = 1};
 
static Point pathArray[MAX_PATH_SIZE];
//static Point pathArray[MAX_PATH_SIZE] = {{1,1,FORWARD,1,0,0,0},{1,1,FORWARD,1,0,0,0},{1,3,LEFT,1,0,0,0}, {1,3,LEFT,1,0,0,0},{1,3,RIGHT,1,0,0,0},{1,3,LEFT,1,0,0,0},{1,3,LEFT,1,0,0,0},{1,3,RIGHT,1,1,0,4},{1,3,BACKWARD,1,0,0,0},{1,3,LEFT,1,0,1,0}};
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
     // Find the quickest path to the first piece of food
    size_t result = run_algo(map, start, food_list, COUNT_OF(food_list), pathArray);
    
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
    float targetDistance = 0;
    
    setupMotor();
    CyDelay(1000);
    currentState = DRIVING;
    
    for(;;){
        LED_GREEN_Write(pathArray[instructions].direction == LEFT);
        LED_BLUE_Write(pathArray[instructions].direction == RIGHT);
        LED_Write(pathArray[instructions].direction == FORWARD);
        switch(currentState){
            case (DRIVING):
                if (pathArray[instructions].foodPoint){
                    currentState = STOPCAR;
                    break;
                }
                controlWheels(MEDIUM_FORWARD_L, MEDIUM_FORWARD);
                
                if((pathArray[instructions].direction == BACKWARD) && !noSensor && !pathArray[instructions].foodPoint){
                    currentState = PREPARETURN;
                    currentInstruction = pathArray[instructions++];
                    break;
                }

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
                if (currentInstruction.xOrY){
                    targetDistance = currentInstruction.steps * y_block;
                }else{
                    targetDistance = currentInstruction.steps * x_block;
                }
                if(motorControl(go_speed, go_speed, targetDistance, Q1_Read(), Q3_Read())){
                    currentState = DRIVING;
                    noSensor = 1;
                    Timer_Sensor_Start();
                }              
                break;           
            case (CALIBRATING):
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
                    //CyDelay(400);    // REVIEW MAYBE //
                    
                    if (Q5_Read() && Q4_Read()){
                        controlWheels(MEDIUM_FORWARD_L, MEDIUM_FORWARD);
                        Timer_Sensor_Start();
                        noSensor = 1;
                        
                        if (currentInstruction.steps && !(pathArray[instructions].node && (pathArray[instructions].direction == FORWARD))){
                            currentState = DISTANCEDRIVING;
                        } else if (!pathArray[instructions].node && (pathArray[instructions].direction == FORWARD)){
                            currentInstruction = pathArray[instructions++];
                            currentState = DRIVING;
                        }else{                                
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
                        if(motorControl(-go_speed, go_speed, 0, Q2_Read(), 0)){
                            if (currentInstruction.steps && !pathArray[instructions].node && pathArray[instructions].direction != FORWARD){
                                currentState = DISTANCEDRIVING;
                                CyDelay(500);
                            } else if (!pathArray[instructions].node && (pathArray[instructions].direction == FORWARD)){
                                currentInstruction = pathArray[instructions++];
                                currentState = DRIVING;
                            }else{                                
                                currentState = DRIVING;
                            }
                        };
                    break;
                }
                
                    break;
            case (TURNING):
                             
                switch(currentInstruction.direction){
                    case(LEFT):
                       controlWheels(MEDIUM_REVERSE, MEDIUM_FORWARD);
                        
                        if (!Q1_Read() && !intersect){
                            controlWheels(STOP, STOP);
                            noSensor = 1;
                            Timer_Sensor_Start();
                                                    
                            if (currentInstruction.steps && !pathArray[instructions].node && pathArray[instructions].direction != FORWARD){
                                currentState = DISTANCEDRIVING;
                                CyDelay(500);
                            } else if (!pathArray[instructions].node && (pathArray[instructions].direction == FORWARD)){
                                currentInstruction = pathArray[instructions++];
                                currentState = DRIVING;
                            }else{                                
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
                                                     
                            if (currentInstruction.steps && !pathArray[instructions].node && pathArray[instructions].direction != FORWARD){
                                currentState = DISTANCEDRIVING;
                                CyDelay(500);
                            } else if (!pathArray[instructions].node && (pathArray[instructions].direction == FORWARD)){
                                currentInstruction = pathArray[instructions++];
                                currentState = DRIVING;
                            }else{                                
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
