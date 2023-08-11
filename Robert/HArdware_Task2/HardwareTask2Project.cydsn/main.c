
/* ========================================
 * Laboratory Exercise 1
 *
 * Build and download project
 * Push SW1 to light led
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
#include <project.h>

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    IN1A_Write(0);
    IN2A_Write(1);
    IN1B_Write(0);
    IN2B_Write(1);
    for(;;)
    {
        /* Place your application code here. */
        
        
    }
}

/* [] END OF FILE */
