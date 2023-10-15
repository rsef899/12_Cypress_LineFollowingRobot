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
#define MEDIUM_FORWARD 66
#define MEDIUM_FORWARD_L 65

#define TEST_FORWARD 55
#define TEST_FORWARD_L 54
#define MEDIUM_REVERSE 35
#define SLOW_FORWARD 55
#define SLOW_REVERSE 45
    
#define TURN_RIGHT 1
#define TURN_LEFT 2
   
    
void controlWheels(uint8_t wheel1Duty, uint8_t wheel2Duty);

void turn(uint8_t dierection);
    
   
    
    
#endif

/* [] END OF FILE */


