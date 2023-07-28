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
volatile uint16_t ADCVoltage;
//define teh TImer Interuprt
CY_ISR(ADCInterupt){
    uint16_t ADCReturn = ADC_GetResult16((uint16_t)0);  
    ADCVoltage = ADC_CountsTo_mVolts(ADCReturn);
    printFlag = 1;
}


int main(){
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;

    USBUART_Start(0,USBUART_5V_OPERATION);
    //Default message to see if terminal connection is working
    usbPutString("*--- ROBERT IS GAY ----*");
    
    //Start the timer and initialise its interupt
    Timer_TS_Start();
    //initialise the ADC timer
    isr_eoc_StartEx(ADCInterupt);
    
    ADC_Start();
    
    for(;;)
    {
        
        if (printFlag == 1){
            char str[20];
            sprintf(str, "%d", ADCVoltage);
            usbPutString(str);
            usbPutString("\n");
            usbPutString("\r");
            printFlag = 0;
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
