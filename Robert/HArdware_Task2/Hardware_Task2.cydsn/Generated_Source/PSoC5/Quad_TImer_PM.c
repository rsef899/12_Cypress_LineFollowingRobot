/*******************************************************************************
* File Name: Quad_TImer_PM.c
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

#include "Quad_TImer.h"

static Quad_TImer_backupStruct Quad_TImer_backup;


/*******************************************************************************
* Function Name: Quad_TImer_SaveConfig
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
*  Quad_TImer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Quad_TImer_SaveConfig(void) 
{
    #if (!Quad_TImer_UsingFixedFunction)
        Quad_TImer_backup.TimerUdb = Quad_TImer_ReadCounter();
        Quad_TImer_backup.InterruptMaskValue = Quad_TImer_STATUS_MASK;
        #if (Quad_TImer_UsingHWCaptureCounter)
            Quad_TImer_backup.TimerCaptureCounter = Quad_TImer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Quad_TImer_UDB_CONTROL_REG_REMOVED)
            Quad_TImer_backup.TimerControlRegister = Quad_TImer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Quad_TImer_RestoreConfig
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
*  Quad_TImer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Quad_TImer_RestoreConfig(void) 
{   
    #if (!Quad_TImer_UsingFixedFunction)

        Quad_TImer_WriteCounter(Quad_TImer_backup.TimerUdb);
        Quad_TImer_STATUS_MASK =Quad_TImer_backup.InterruptMaskValue;
        #if (Quad_TImer_UsingHWCaptureCounter)
            Quad_TImer_SetCaptureCount(Quad_TImer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Quad_TImer_UDB_CONTROL_REG_REMOVED)
            Quad_TImer_WriteControlRegister(Quad_TImer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Quad_TImer_Sleep
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
*  Quad_TImer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Quad_TImer_Sleep(void) 
{
    #if(!Quad_TImer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Quad_TImer_CTRL_ENABLE == (Quad_TImer_CONTROL & Quad_TImer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Quad_TImer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Quad_TImer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Quad_TImer_Stop();
    Quad_TImer_SaveConfig();
}


/*******************************************************************************
* Function Name: Quad_TImer_Wakeup
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
*  Quad_TImer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Quad_TImer_Wakeup(void) 
{
    Quad_TImer_RestoreConfig();
    #if(!Quad_TImer_UDB_CONTROL_REG_REMOVED)
        if(Quad_TImer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Quad_TImer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
