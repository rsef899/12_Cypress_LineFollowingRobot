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
//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
//* ========================================
uint8_t timeIndex = 0;
uint16_t timeArrayM1[2];
uint16_t timeArrayM2[2];
uint8_t printSpeed = 0;
uint8_t changeVal = 0;


//Interupts
CY_ISR(outputUartIsr) {
    printSpeed = 1; // Print the speed every like 200ms
    
    Timer_TS_ReadStatusRegister();   
}
CY_ISR(QuadDecoderIsr){
    if (timeIndex == 0){
        timeArrayM1[0] = QuadDec_M1_GetCounter();
        timeArrayM2[0] = QuadDec_M2_GetCounter();
        timeIndex = 1;
    } else {
        timeArrayM1[1] = QuadDec_M1_GetCounter();
        timeArrayM2[1] = QuadDec_M2_GetCounter();
        timeIndex = 0;
        changeVal = 1;   
        Quad_TImer_Start();
       
    }
    Quad_TImer_ReadStatusRegister();
}


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


int main(){
    M2_INV_Write(1);
    // Count = 
    uint16_t reqCount = (float) SPEED_WANTED * (float) 0.03 * (float) 114.0 * (float) CY_M_PI * (float) 3.5;
    //PWM1
    PWM_1_Start();
    //PWM2
    PWM_2_Start();   
    uint8_t duty = 100;
    changeDutyCycle(duty);
    #ifdef USE_USB
        USBUART_Start(0,USBUART_5V_OPERATION);
    #endif
    uint16_t m1counts = 0;
    uint16_t m2counts = 0;
    float speed = 0;
    float distance = 0;
    QuadDec_M1_Start();
    QuadDec_M2_Start();
    
    //QuadEncoder initialisation
    isr_quad_timer_StartEx(QuadDecoderIsr);
    isr_TS_StartEx(outputUartIsr);
    Timer_TS_Start();
    Quad_TImer_Start();
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;    
    for(;;)
    {
        
        char buffer [64];
        //QuadEncoder icode
        if (changeVal == 1){
            m1counts = timeArrayM1[1] - timeArrayM1[0]; // Tells us how many counts occured in 30ms
            m2counts = timeArrayM2[1] - timeArrayM2[0];
            // Gears are 19:1, therefore 19 * 3 counts means one full rotation, we only have speed counts
            // Therefore = counts/19 of a wheel rotation: counts/57 * 2pi * r = circumference moved in that time. circumeferenceMoved/30ms gives us the value in cm/s
            distance = (float)m1counts/(float)((float)(57.0 * 2.0) *(float)((float) CY_M_PI * 3.5));  //CY_M_PI = pi, 3.5cm is the radius (might actually be wrong)
            speed =  (float)distance / (float) 0.03;
            if (speed > SPEED_WANTED) { // If we are currently going faster than needed, reduce the speed on PWM (cannot be 50 since that is 'stopped')
                
                
                // INSTEAD OF DOING BY DUTY CYCLE WE COULD TRY ADD THE ERROR TO THE COMPARE VALUE ITSELF
                uint16_t error = speed - SPEED_WANTED; // (m/s to count = error * 0.03 * 114.0 * pi * 3.5)
                //uint16_t errorCount = error * 0.03 * 114.0 * CY_M_PI * 3.5;
               
                //PWM_1_WriteCompare(PWM_1_ReadCompare() -errorCount);
                //PWM_2_WriteCompare(PWM_1_ReadCompare() -errorCount);
                if (error > 10) {
                   duty = duty - 10;
                    
                } else {
                   duty = duty - 5;   
                }
                if (duty <= 50) {
                    duty = 55;
                }
                changeDutyCycle(duty);

                
            } else if (speed < SPEED_WANTED) {
                uint16_t error = SPEED_WANTED - speed;
                //uint16_t errorCount = error * 0.03 * 114.0 * CY_M_PI * 3.5;
                //PWM_1_WriteCompare(PWM_1_ReadCompare() +errorCount);
                //PWM_2_WriteCompare(PWM_1_ReadCompare() +errorCount);
                if (error > 10) {
                    duty = duty + 10;
                    
                } else {
                   duty = duty + 5;   
                }
                if (duty >= 100) {
                        duty = 95;
                }
                changeDutyCycle(duty);
            }
            
            
            
            changeVal = 0; 
            
        }
        if (printSpeed == 1) {
            itoa(speed, buffer, 10);
            usbPutString(buffer);
            //usbPutString("\r\n");
            //itoa(m2counts, buffer, 10);
            //usbPutString(buffer);
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
