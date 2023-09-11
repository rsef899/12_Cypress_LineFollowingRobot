/* ========================================
 *
 * Team 12: Movement file
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

#ifndef Movements_H
#define Movements_H

#define STOP 50 //stopping duty cycle
#define FULL_FORWARD 100
#define FULL_REVERSE 0
#define MEDIUM_FORWARD 75
#define MEDIUM_REVSERSE 25
   
    
uint8_t controlWheels(uint8_t wheel1Duty, uint8_t wheel2Duty);
    
   
    
    
#endif

/* [] END OF FILE */


