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
void checkPWMCommand(const char *input);
void setPWMDuty(int duty);
void setPWMFreq(int peri);
//* ========================================


int main()
{
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;

// ------USB SETUP ----------------    
#ifdef USE_USB    
    USBUART_Start(0,USBUART_5V_OPERATION);
#endif        
        
    RF_BT_SELECT_Write(0);
    usbPutString(displaystring);
    
    PWM_1_Start();
    PWM_2_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        handle_usb();
        if (flag_KB_string == 1 && line[0] != '\0')
        {
            char msg[BUF_SIZE];
            char textpt[14] = "You entered: \"";
            strcpy(msg, textpt);
            strcat(msg, line);
            strcat(msg, "\"\n\r");
            usbPutString(msg);
            checkPWMCommand(line);
            flag_KB_string = 0;
        }        
    }   
}

void checkPWMCommand(const char *input){
    char *duty_command_found = strstr(input, "d");
    char *period_command_found = strstr(input, "p");
    
    if (duty_command_found) {
        int count = 1;
        char currentchar = 'a';
        while (currentchar != '\0') {
            currentchar = input[count];
            if (!isdigit(currentchar)) {
                return;
            }
            count++;
            usbPutChar(currentchar);                                //**//
        }
        usbPutString("END LOOP\n\r");                               //**//
        
        if (count > 3){
            usbPutString("Number too large!\n\r");
            return;            
        }
        
        char char_nums[count-1];
        strncpy(char_nums, input+1, count-1);
        usbPutString(char_nums);                                    //**//
    }
    return; // Pattern not found
}

void setPWMDuty(int duty){
    PWM_1_WriteCompare(PWM_1_ReadPeriod() * (float)duty/100.00);
    PWM_2_WriteCompare(PWM_2_ReadPeriod() * (float)duty/100.00);
    usbPutString("Updated duty cycle!\n\r");
    return;
}

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
//* ========================================
void handle_usb()
{
    // handles input at terminal, echos it back to the terminal
    // turn echo OFF, key emulation: only CR
    // entered string is made available in 'line' and 'flag_KB_string' is set
    
    static uint8 usbStarted = FALSE;
    static uint16 usbBufCount = 0;
    uint8 c; 
    

    if (!usbStarted)
    {
        if (USBUART_GetConfiguration())
        {
            USBUART_CDC_Init();
            usbStarted = TRUE;
        }
    }
    else
    {
        if (USBUART_DataIsReady() != 0)
        {  
            c = USBUART_GetChar();

            if ((c == 13) || (c == 10))
            {
//                if (usbBufCount > 0)
                {
                    entry[usbBufCount]= '\0';
                    strcpy(line,entry);
                    usbBufCount = 0;
                    flag_KB_string = 1;
                }
            }
            else 
            {
                if (((c == CHAR_BACKSP) || (c == CHAR_DEL) ) && (usbBufCount > 0) )
                    usbBufCount--;
                else
                {
                    if (usbBufCount > (BUF_SIZE-2) ) // one less else strtok triggers a crash
                    {
                       USBUART_PutChar('!');        
                    }
                    else
                        entry[usbBufCount++] = c;  
                }  
            }
        }
    }    
}


/* [] END OF FILE */
