
/* ========================================
 * Laboratory Exercise 3
 *
 * Program timer to flash LED at 1Hz, use interrupts
 *
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include "project.h"


//Define the ISR, CY_ISR is used tod efine the function
CY_ISR(TC_Interrupt) {
    //Toggle the LED, Write to it the opposite of its curent value
    LED_Write(~LED_Read());
    //reset the TIMER value
    Timer_1_ReadStatusRegister();   
}

int main()
{
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    
    //Start the Define ISR, pass the ISR to the isr start
    isr_TC_StartEx(TC_Interrupt);
    
    
    //Start the TIemr
    Timer_1_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        
        
    }
}

/* [] END OF FILE */
