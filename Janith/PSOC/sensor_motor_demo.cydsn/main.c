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

void setPWMDuty(int duty);
//* ========================================

int main()
{
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;

    PWM_1_Start();
    PWM_2_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        setPWMDuty(170);
    }   
}

void setPWMDuty(int duty){
    PWM_1_WriteCompare(PWM_1_ReadPeriod() * (float)duty/100.00);
    PWM_2_WriteCompare(PWM_2_ReadPeriod() * (float)duty/100.00);
    return;
}
/* [] END OF FILE */
