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
#include <math.h>

//* ========================================
#include "defines.h"
#include "vars.h"
#define GEAR_RATIO 19
#define PULSES_PER_ROT (GEAR_RATIO * 3 * QuadDec_M1_COUNTER_RESOLUTION)
#define RADIUS (3.25f)
#define MOTORSPEED_PER_SECOND ((float) 50/1000.0f) // 100ms is the period we want to be changing the motor speed
//* ========================================
void usbPutString(char *s);
uint8_t changeDutyCycle(uint8_t dutyValue);
void usbPutChar(char c);
void handle_usb();
//* ========================================
uint8_t timeIndex = 0;
float m1motorSpeed =0;
float m2motorSpeed =0;

uint8_t printSpeed = 0;
volatile uint8_t changeVal = 0;
uint16_t m1Count = 0;
uint16_t m2Count = 0;
uint8_t stop = 0;

float m1Comp,m2Comp;

//Interupts
CY_ISR(outputUartIsr) {
    //LED_Write(!LED_Read());
    printSpeed = 1; // Print the speed every like 200ms
    stop = 1;
    Timer_TS_ReadStatusRegister();   
}
CY_ISR(QuadDecoderIsr){
    //usbPutString("test");
    m2Count = QuadDec_M2_GetCounter();
    m1Count = QuadDec_M1_GetCounter();
    //get_speed();
    QuadDec_M1_SetCounter(0);
    QuadDec_M2_SetCounter(0);
    changeVal = 1;
    Quad_TImer_ReadStatusRegister();
}
void motorControl(float m1speed, float m2speed) {
    
    if(changeVal == 0) {
        
        return;
    } else if (stop ==1) {
        changeDutyCycle(50);
        return;
    }
    //PWM_1_WriteCompare(250);
    changeVal = 0;
    m1motorSpeed =  (float) m1Count / (float) PULSES_PER_ROT;
    m2motorSpeed = (float) m2Count / (float) PULSES_PER_ROT;
    m1motorSpeed = 2 * CY_M_PI * m1motorSpeed / MOTORSPEED_PER_SECOND; // 2 * pi * rotations / (m/s)
    m1motorSpeed = m1motorSpeed * RADIUS;
    m2motorSpeed = 2 * CY_M_PI * m2motorSpeed / MOTORSPEED_PER_SECOND;
    m2motorSpeed = m2motorSpeed * RADIUS;
    
    float m1error = m1speed - m1motorSpeed;
    float m2error = m2speed - m2motorSpeed;
    
    //m1error = (m1speed * 228.0f * (float) MOTORSPEED_PER_SECOND) / ((float) 7.5f * CY_M_PI);
    //m2error = (m2speed * 228.0f * (float) MOTORSPEED_PER_SECOND) / ((float) 7.5f * CY_M_PI);
    m1Comp = PWM_1_ReadCompare();
    m2Comp = PWM_2_ReadCompare();
    float m1Target = m1Comp + m1error;
    float m2Target = m2Comp + m2error;
    
    //float m1Target = m2Target - 5;
    
    //PWM_1_WriteCompare((uint8_t) m1Target);
    //PWM_2_WriteCompare((uint8_t) m2Target);
    
    
    if (m1Target > 255) {
        PWM_1_WriteCompare(255);   
    } else if (m1Target < 0) {
        PWM_1_WriteCompare(0);      
    } else {
        PWM_1_WriteCompare((uint8_t) m1Target);
    }
    if (m2Target > 255) {
        PWM_2_WriteCompare(255);   
    } else if (m2Target < 0) {
        PWM_2_WriteCompare(0);      
    } else {
        PWM_2_WriteCompare((uint8_t) m2Target);
    }
   
    
    
}


//------------------------------------------------------


uint8_t changeDutyCycle(uint8_t dutyValue){

    uint8_t val = ((float)PWM_1_ReadPeriod() * (dutyValue/100.0));
    PWM_1_WriteCompare(val);
    PWM_2_WriteCompare(val);
    return val;
}

void controlWheels(uint8_t wheel1Duty, uint8_t wheel2Duty){
    
    //find the compare value, i.e count number of each PWM
    uint8_t compareValue1 = ((float)PWM_1_ReadPeriod() * (wheel1Duty/100.0));
    uint8_t compareValue2 = ((float)PWM_2_ReadPeriod() * (wheel2Duty/100.0));
    //set the PWM to the found value
    PWM_1_WriteCompare(compareValue1);
    PWM_2_WriteCompare(compareValue2);
 
}
void setupMotor() {
    PWM_1_WritePeriod(255);
    PWM_1_Start();
    PWM_1_WriteCompare(170);
    
    PWM_2_WritePeriod(255);
    PWM_2_Start();
    PWM_2_WriteCompare(170);
    
    QuadDec_M1_Start();
    QuadDec_M2_Start();
    Quad_TImer_Start();
    
    isr_quad_timer_StartEx(QuadDecoderIsr);
    Quad_TImer_WritePeriod(49); // 100ms
    QuadDec_M1_SetCounter(0);
    QuadDec_M2_SetCounter(0);
    
    
}


int main(){
    M2_INV_Write(1);
    setupMotor();
    float m1speed = 75.0;
    float m2speed = 75.0;
    float timer =  100.0/abs(m1speed);
    isr_TS_StartEx(outputUartIsr);
    Timer_TS_Start();
    Timer_TS_WritePeriod(timer * 1000.0f);
    Timer_TS_WriteCounter(0);

    #ifdef USE_USB
        USBUART_Start(0,USBUART_5V_OPERATION);
    #endif

    
    
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;    
    for(;;)
    {
        
        motorControl(m1speed,m2speed);
        char buffer [64];
        while (!(Q1_Read() && Q3_Read())) {
            if (!Q3_Read()) {
                motorControl(m1speed,m2speed-5);
            }
            if (!Q1_Read()) {
                motorControl(m1speed-5,m2speed);
            }
        }
        
       
        
        /*if (printSpeed == 1) {
            usbPutString("\r\n M1:");
            //itoa((float) m1motorSpeed, buffer, 10);
            itoa((float) m1Comp, buffer, 10);
            usbPutString(buffer);
            usbPutString("-");
            itoa((float) m1motorSpeed, buffer, 10);
            //itoa((float) speedL, buffer, 10);
            usbPutString(buffer);
            usbPutString("\r\n");
            usbPutString("\r\n M2:");
            //itoa((float) m2motorSpeed, buffer, 10);
            itoa((float) m2Comp, buffer, 10);
            //itoa((float) speedR, buffer, 10);
            usbPutString(buffer);
            usbPutString("-");
            itoa((float) m2motorSpeed, buffer, 10);
            usbPutString(buffer);
            usbPutString("\r\n end \r\n");
            printSpeed = 0;
        } */

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
