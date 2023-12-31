/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
//* ========================================
#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <project.h>
#include "movement.h"
#include "motor.h"

uint8_t timeIndex = 0;
float m1motorSpeed =0;
float m2motorSpeed =0;





volatile uint8_t changeVal = 0;
float m1Count = 0;
float m2Count = 0;

uint8_t flag = 0;

float m1Comp,m2Comp;

CY_ISR(QuadDecoderIsr){
    m2Count = QuadDec_M2_GetCounter();
    m1Count = QuadDec_M1_GetCounter();
    QuadDec_M1_SetCounter(0);
    QuadDec_M2_SetCounter(0);
    changeVal = 1;
    tmm_ReadStatusRegister();
}

void motorControl(float m1speed, float m2speed) {
    if(changeVal == 0) {
        return;
    } else if (stopMotor ==1) {
            // ******** THIS IS THE CODE FOR CONTROL WHEELS, EITHER REMOVE FROM MAIN OR MOVE TO THIS FILE **//
            uint8_t compareValue1 = ((float)PWM_1_ReadPeriod() * (50/100.0));
            uint8_t compareValue2 = ((float)PWM_2_ReadPeriod() * (50/100.0));
            //set the PWM to the found value
            PWM_1_WriteCompare(compareValue1);
            PWM_2_WriteCompare(compareValue2);
        return;
    }
    changeVal = 0;
    
    m1motorSpeed =  (float) m1Count / (float) PULSES_PER_ROT;
    m2motorSpeed = (float) m2Count / (float) PULSES_PER_ROT;
    m1motorSpeed = 2 * CY_M_PI * m1motorSpeed / MOTORSPEED_PER_SECOND; // 2 * pi * rotations / (m/s)
    m1motorSpeed = m1motorSpeed * RADIUS;
    m2motorSpeed = 2 * CY_M_PI * m2motorSpeed / MOTORSPEED_PER_SECOND;
    m2motorSpeed = m2motorSpeed * RADIUS; 
    
    
    float m1error = m1speed - m1motorSpeed;
    float m2error = m2speed - m2motorSpeed;
    if (distanceCheck == 1) {
        distanceTravelledM1 = distanceTravelledM1 + m1motorSpeed*MOTORSPEED_PER_SECOND;
        distanceTravelledM2 = distanceTravelledM2 + m2motorSpeed*MOTORSPEED_PER_SECOND;
        distanceTravelled = (distanceTravelledM1 + distanceTravelledM2 ) / 2.0;
        if (distanceTravelled >= distanceRequired) {
            stopMotor = 1;
            uint8_t compareValue1 = ((float)PWM_1_ReadPeriod() * (50/100.0));
            uint8_t compareValue2 = ((float)PWM_2_ReadPeriod() * (50/100.0));
            //set the PWM to the found value
            PWM_1_WriteCompare(compareValue1);
            PWM_2_WriteCompare(compareValue2);
            return;
        }
    }
    m1Comp = PWM_1_ReadCompare();
    m2Comp = PWM_2_ReadCompare();
    float m1Target = m1Comp + m1error;
    float m2Target = m2Comp + m2error;
    
    PWM_1_WriteCompare((uint8_t) m1Target);
    PWM_2_WriteCompare((uint8_t) m2Target);
}

void setupMotor() {
    PWM_1_Start();
    PWM_2_Start();
    
    QuadDec_M1_Start();
    QuadDec_M2_Start();

    tmm_Start();
    
    isr_quad_timer_StartEx(QuadDecoderIsr);
    tmm_WritePeriod(49); // 100ms
    QuadDec_M1_SetCounter(0);
    QuadDec_M2_SetCounter(0);
}
void usbPutString1(char *s)
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
/* [] END OF FILE */