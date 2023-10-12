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

/* [] END OF FILE */

#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <project.h>
#include "movement.h"

#define GEAR_RATIO 19
#define PULSES_PER_ROT (GEAR_RATIO * 3 * QuadDec_M1_COUNTER_RESOLUTION)
#define RADIUS (3.25f)
#define MOTORSPEED_PER_SECOND ((float) 50/1000.0f) // 50ms is the period we want to be changing the motor speed

void motorControl(float m1speed, float m2speed);
void setupMotor();
CY_ISR(QuadDecoderIsr);
void usbPutString1(char *s);