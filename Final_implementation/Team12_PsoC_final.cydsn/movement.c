/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <project.h>

#include "movement.h"


void controlWheels(uint8_t wheel1Duty, uint8_t wheel2Duty){
    
    //find the compare value, i.e count number of each PWM
    uint8_t compareValue1 = ((float)PWM_1_ReadPeriod() * (wheel1Duty/100.0));
    uint8_t compareValue2 = ((float)PWM_2_ReadPeriod() * (wheel2Duty/100.0));
    //set the PWM to the found value
    PWM_1_WriteCompare(compareValue1);
    PWM_2_WriteCompare(compareValue2);
    LED_Write(1);
 
}

void turn(uint8_t dierection){
    switch (dierection){
        case(TURN_RIGHT):
        controlWheels(MEDIUM_FORWARD, STOP);
        break;
        
        case(TURN_LEFT):
        controlWheels(STOP, MEDIUM_FORWARD);
        break;
        
    }
}



/* [] END OF FILE */
