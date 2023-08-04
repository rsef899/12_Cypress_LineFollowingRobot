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
void changeDutyCycle(char* dutyValue);

volatile uint8_t printFlag = 0;
volatile uint16_t buffer[1024];
volatile uint16_t bufferIndex = 0;

//define teh TImer Interuprt
CY_ISR(ADCInterupt){
    //if we are printing pdmt store ADC values
    if(printFlag == 1) return;
    uint16_t ADCReturn = ADC_GetResult16((uint16_t)0);
    //add the result to the buffer
    buffer[bufferIndex++] = ADC_CountsTo_mVolts(ADCReturn);
    //when the buffer is full set the prin flag, start the buffer aggain
    if(bufferIndex == 1024) {
        printFlag = 1;
        bufferIndex = 0;
    }
}


int main(){
    

    IN1A_Write(1);
    IN1B_Write(1);
    IN2A_Write(0);
    IN2B_Write(0);
    
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
