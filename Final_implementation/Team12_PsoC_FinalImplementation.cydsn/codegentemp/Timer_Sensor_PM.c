/*******************************************************************************
* File Name: Timer_Sensor_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Sensor.h"

static Timer_Sensor_backupStruct Timer_Sensor_backup;


/*******************************************************************************
* Function Name: Timer_Sensor_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Sensor_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Sensor_SaveConfig(void) 
{
    #if (!Timer_Sensor_UsingFixedFunction)
        Timer_Sensor_backup.TimerUdb = Timer_Sensor_ReadCounter();
        Timer_Sensor_backup.InterruptMaskValue = Timer_Sensor_STATUS_MASK;
        #if (Timer_Sensor_UsingHWCaptureCounter)
            Timer_Sensor_backup.TimerCaptureCounter = Timer_Sensor_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Sensor_UDB_CONTROL_REG_REMOVED)
            Timer_Sensor_backup.TimerControlRegister = Timer_Sensor_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Sensor_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Sensor_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Sensor_RestoreConfig(void) 
{   
    #if (!Timer_Sensor_UsingFixedFunction)

        Timer_Sensor_WriteCounter(Timer_Sensor_backup.TimerUdb);
        Timer_Sensor_STATUS_MASK =Timer_Sensor_backup.InterruptMaskValue;
        #if (Timer_Sensor_UsingHWCaptureCounter)
            Timer_Sensor_SetCaptureCount(Timer_Sensor_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Sensor_UDB_CONTROL_REG_REMOVED)
            Timer_Sensor_WriteControlRegister(Timer_Sensor_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Sensor_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Sensor_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Sensor_Sleep(void) 
{
    #if(!Timer_Sensor_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Sensor_CTRL_ENABLE == (Timer_Sensor_CONTROL & Timer_Sensor_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Sensor_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Sensor_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Sensor_Stop();
    Timer_Sensor_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Sensor_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Sensor_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Sensor_Wakeup(void) 
{
    Timer_Sensor_RestoreConfig();
    #if(!Timer_Sensor_UDB_CONTROL_REG_REMOVED)
        if(Timer_Sensor_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Sensor_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
