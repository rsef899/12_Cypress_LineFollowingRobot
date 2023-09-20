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
uint16_t timeArrayM1[2];
uint16_t timeArrayM2[2];
uint8_t printSpeed = 0;
volatile uint8_t changeVal = 0;
uint16_t m1Count = 0;
uint16_t m2Count = 0;
uint8_t stop = 0;
uint16_t speedL, speedR;
uint16_t posL, posR;
float m1Comp,m2Comp;
void get_speed()
{
    int16 pl, pr;
    
    // get current position.
    pl = QuadDec_M1_GetCounter();
    pr = QuadDec_M2_GetCounter();
    
    speedL = pl - posL;
    speedR = pr - posR;
    posL = pl;
    posR = pr;
    
    
    // Speed of Motor 1
    uint8_t state = QuadDec_M1_GetEvents();
    uint8_t speed = pl - posL;
    if ((state & QuadDec_M1_COUNTER_OVERFLOW) != 0x00)
        speed += 32767;
    
    if ((state & QuadDec_M1_COUNTER_UNDERFLOW) != 0x00)
        speed += -32768;
    speedL = speed;
    posL = pl;
    
    // Speed of Motor 2
    state = QuadDec_M2_GetEvents();
    speed = pr - posR;
    if ((state & QuadDec_M2_COUNTER_OVERFLOW) != 0x00)
        speed += 32767;
    
    if ((state & QuadDec_M2_COUNTER_UNDERFLOW) != 0x00)
        speed += -32768;
    speedR = speed;    
    posR = pr;
}
void motorControl(float m1speed, float m2speed) {
    
    if(changeVal == 0) {
        
        return;
    } else if (stop ==1) {
        changeDutyCycle(50);
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
    } else if (m1Target < 122) {
        PWM_1_WriteCompare(125);      
    } else {
        PWM_1_WriteCompare((uint8_t) m1Target);
    }
    if (m2Target > 255) {
        PWM_2_WriteCompare(255);   
    } else if (m2Target < 122) {
        PWM_2_WriteCompare(125);      
    } else {
        PWM_2_WriteCompare((uint8_t) m2Target);
    }
   
    
    
}
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
void get_pos()
{
    int pl, pr;

    pl = QuadDec_M1_GetCounter();
    pr = QuadDec_M2_GetCounter();

    posL = pl;
    posR = pr;
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
    float m1speed = 55.0;
    float m2speed = 55.0;
    // Count = 
    //uint16_t reqCount = (float) SPEED_WANTED * (float) 0.03 * (float) 114.0 * (float) CY_M_PI * (float) 3.5;
    
    uint8_t duty = 100;
    //changeDutyCycle(duty);
    #ifdef USE_USB
        USBUART_Start(0,USBUART_5V_OPERATION);
    #endif
    //uint16_t m1counts = 0;
    //uint16_t m2counts = 0;
    //float speed = 0;
    //float distance = 0;

    isr_TS_StartEx(outputUartIsr);
    Timer_TS_Start();
    
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;    
    for(;;)
    {
        
        motorControl(25.0,25.0);
        char buffer [64];
        
        //QuadEncoder icode
        //if (changeVal == 1){
            //m1counts = timeArrayM1[1] - timeArrayM1[0]; // Tells us how many counts occured in 30ms
            //m2counts = timeArrayM2[1] - timeArrayM2[0];
            // Gears are 19:1, therefore 19 * 3 counts means one full rotation, we only have speed counts
            // Therefore = counts/19 of a wheel rotation: counts/57 * 2pi * r = circumference moved in that time. circumeferenceMoved/30ms gives us the value in cm/s
            //distance = (float)m1counts/(float)((float)(57.0 * 2.0) *(float)((float) CY_M_PI * 3.5));  //CY_M_PI = pi, 3.5cm is the radius (might actually be wrong)
            //speed =  (float)distance / (float) 0.03;
            //if (speed > SPEED_WANTED) { // If we are currently going faster than needed, reduce the speed on PWM (cannot be 50 since that is 'stopped')
                
                
                // INSTEAD OF DOING BY DUTY CYCLE WE COULD TRY ADD THE ERROR TO THE COMPARE VALUE ITSELF
                //uint16_t error = speed - SPEED_WANTED; // (m/s to count = error * 0.03 * 114.0 * pi * 3.5)
                //uint16_t errorCount = error * 0.03 * 114.0 * CY_M_PI * 3.5;
               
                //PWM_1_WriteCompare(PWM_1_ReadCompare() -e rrorCount);
                //PWM_2_WriteCompare(PWM_1_ReadCompare() -errorCount);
                //if (error > 10) {
                   //duty = duty - 10;
                    
                //} else {
                   //duty = duty - 5;   
                //}
                //if (duty <= 50) {
                    //duty = 55;
                //}
                //changeDutyCycle(duty);

                
            //} else if (speed < SPEED_WANTED) {
                //uint16_t error = SPEED_WANTED - speed;
                //uint16_t errorCount = error * 0.03 * 114.0 * CY_M_PI * 3.5;
                //PWM_1_WriteCompare(PWM_1_ReadCompare() +errorCount);
                //PWM_2_WriteCompare(PWM_1_ReadCompare() +errorCount);
                //if (error > 10) {
                    //duty = duty + 10;
                    
                //} else {
                   //duty = duty + 5;   
                //}
                //if (duty >= 100) {
                        //duty = 95;
                //}
                //changeDutyCycle(duty);
            //}
            
            
            
            //changeVal = 0; 
            
        //}
        
        if (printSpeed == 1) {
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
