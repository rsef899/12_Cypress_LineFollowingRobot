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

#include <project.h>

#ifndef STATES_H
#define STATES_H
    
    extern uint8_t currentState;
 
    #define MODESELECT 0
    #define FREERUNNING 1
    #define SHORTESTMODE 2
    #define CALIBRATING 3
    #define DRIVING 4
    #define DISTANCEDRIVING 5
    #define PREPARETURN 6
    #define TURNING 7
    #define STOPCAR 10
    
    
#endif

/* [] END OF FILE */
