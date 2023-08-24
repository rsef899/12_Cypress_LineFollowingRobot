
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
#include <project.h>

CY_ISR(SENSOR1){
    LED1_Write(~LED1_Read());
}

CY_ISR(SENSOR2){
    LED1_Write(~LED2_Read());
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_sens1_StartEx(SENSOR1);
    isr_sens2_StartEx(SENSOR2);

    for(;;)
    {
        /* Place your application code here. */
        
        
    }
}

/* [] END OF FILE */
