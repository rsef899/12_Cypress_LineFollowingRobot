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
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
//* ========================================


uint8_t changeDutyCycle(uint8_t dutyValue){
    //PWM_1_WriteCompare((uint8_t)(255 * dutyValue)/(float)100);
    //PWM_2_WriteCompare((uint8_t)(255 * dutyValue)/(float)100);
    uint8_t val = (uint8_t)((float)PWM_1_ReadPeriod() * (dutyValue/100));
    PWM_1_WriteCompare(val);
    PWM_2_WriteCompare(val);
    return val;
}

int main(){
    
    //PWM1
    PWM_1_Start();
    //PWM2
    PWM_2_Start();
    
    uint8_t testnum;
    char buffer [64];
    uint8_t duty = 50;
    testnum = changeDutyCycle(duty);
    
    itoa(testnum, buffer, 10);
    
    USBUART_PutString(buffer);
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;


    
    for(;;)
    {
       
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
