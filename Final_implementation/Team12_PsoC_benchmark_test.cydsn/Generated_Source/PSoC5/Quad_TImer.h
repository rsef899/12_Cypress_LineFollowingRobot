/*******************************************************************************
* File Name: Quad_TImer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_Quad_TImer_H)
#define CY_TIMER_Quad_TImer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Quad_TImer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define Quad_TImer_Resolution                 8u
#define Quad_TImer_UsingFixedFunction         1u
#define Quad_TImer_UsingHWCaptureCounter      0u
#define Quad_TImer_SoftwareCaptureMode        0u
#define Quad_TImer_SoftwareTriggerMode        0u
#define Quad_TImer_UsingHWEnable              0u
#define Quad_TImer_EnableTriggerMode          0u
#define Quad_TImer_InterruptOnCaptureCount    0u
#define Quad_TImer_RunModeUsed                0u
#define Quad_TImer_ControlRegRemoved          0u

#if defined(Quad_TImer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define Quad_TImer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (Quad_TImer_UsingFixedFunction)
    #define Quad_TImer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define Quad_TImer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End Quad_TImer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!Quad_TImer_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (Quad_TImer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!Quad_TImer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}Quad_TImer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    Quad_TImer_Start(void) ;
void    Quad_TImer_Stop(void) ;

void    Quad_TImer_SetInterruptMode(uint8 interruptMode) ;
uint8   Quad_TImer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define Quad_TImer_GetInterruptSource() Quad_TImer_ReadStatusRegister()

#if(!Quad_TImer_UDB_CONTROL_REG_REMOVED)
    uint8   Quad_TImer_ReadControlRegister(void) ;
    void    Quad_TImer_WriteControlRegister(uint8 control) ;
#endif /* (!Quad_TImer_UDB_CONTROL_REG_REMOVED) */

uint8  Quad_TImer_ReadPeriod(void) ;
void    Quad_TImer_WritePeriod(uint8 period) ;
uint8  Quad_TImer_ReadCounter(void) ;
void    Quad_TImer_WriteCounter(uint8 counter) ;
uint8  Quad_TImer_ReadCapture(void) ;
void    Quad_TImer_SoftwareCapture(void) ;

#if(!Quad_TImer_UsingFixedFunction) /* UDB Prototypes */
    #if (Quad_TImer_SoftwareCaptureMode)
        void    Quad_TImer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!Quad_TImer_UsingFixedFunction) */

    #if (Quad_TImer_SoftwareTriggerMode)
        void    Quad_TImer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (Quad_TImer_SoftwareTriggerMode) */

    #if (Quad_TImer_EnableTriggerMode)
        void    Quad_TImer_EnableTrigger(void) ;
        void    Quad_TImer_DisableTrigger(void) ;
    #endif /* (Quad_TImer_EnableTriggerMode) */


    #if(Quad_TImer_InterruptOnCaptureCount)
        void    Quad_TImer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (Quad_TImer_InterruptOnCaptureCount) */

    #if (Quad_TImer_UsingHWCaptureCounter)
        void    Quad_TImer_SetCaptureCount(uint8 captureCount) ;
        uint8   Quad_TImer_ReadCaptureCount(void) ;
    #endif /* (Quad_TImer_UsingHWCaptureCounter) */

    void Quad_TImer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void Quad_TImer_Init(void)          ;
void Quad_TImer_Enable(void)        ;
void Quad_TImer_SaveConfig(void)    ;
void Quad_TImer_RestoreConfig(void) ;
void Quad_TImer_Sleep(void)         ;
void Quad_TImer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define Quad_TImer__B_TIMER__CM_NONE 0
#define Quad_TImer__B_TIMER__CM_RISINGEDGE 1
#define Quad_TImer__B_TIMER__CM_FALLINGEDGE 2
#define Quad_TImer__B_TIMER__CM_EITHEREDGE 3
#define Quad_TImer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define Quad_TImer__B_TIMER__TM_NONE 0x00u
#define Quad_TImer__B_TIMER__TM_RISINGEDGE 0x04u
#define Quad_TImer__B_TIMER__TM_FALLINGEDGE 0x08u
#define Quad_TImer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define Quad_TImer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define Quad_TImer_INIT_PERIOD             1u
#define Quad_TImer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << Quad_TImer_CTRL_CAP_MODE_SHIFT))
#define Quad_TImer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << Quad_TImer_CTRL_TRIG_MODE_SHIFT))
#if (Quad_TImer_UsingFixedFunction)
    #define Quad_TImer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << Quad_TImer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << Quad_TImer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define Quad_TImer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << Quad_TImer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Quad_TImer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Quad_TImer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (Quad_TImer_UsingFixedFunction) */
#define Quad_TImer_INIT_CAPTURE_COUNT      (2u)
#define Quad_TImer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << Quad_TImer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (Quad_TImer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define Quad_TImer_STATUS         (*(reg8 *) Quad_TImer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define Quad_TImer_STATUS_MASK    (*(reg8 *) Quad_TImer_TimerHW__SR0 )
    #define Quad_TImer_CONTROL        (*(reg8 *) Quad_TImer_TimerHW__CFG0)
    #define Quad_TImer_CONTROL2       (*(reg8 *) Quad_TImer_TimerHW__CFG1)
    #define Quad_TImer_CONTROL2_PTR   ( (reg8 *) Quad_TImer_TimerHW__CFG1)
    #define Quad_TImer_RT1            (*(reg8 *) Quad_TImer_TimerHW__RT1)
    #define Quad_TImer_RT1_PTR        ( (reg8 *) Quad_TImer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define Quad_TImer_CONTROL3       (*(reg8 *) Quad_TImer_TimerHW__CFG2)
        #define Quad_TImer_CONTROL3_PTR   ( (reg8 *) Quad_TImer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define Quad_TImer_GLOBAL_ENABLE  (*(reg8 *) Quad_TImer_TimerHW__PM_ACT_CFG)
    #define Quad_TImer_GLOBAL_STBY_ENABLE  (*(reg8 *) Quad_TImer_TimerHW__PM_STBY_CFG)

    #define Quad_TImer_CAPTURE_LSB         (* (reg16 *) Quad_TImer_TimerHW__CAP0 )
    #define Quad_TImer_CAPTURE_LSB_PTR       ((reg16 *) Quad_TImer_TimerHW__CAP0 )
    #define Quad_TImer_PERIOD_LSB          (* (reg16 *) Quad_TImer_TimerHW__PER0 )
    #define Quad_TImer_PERIOD_LSB_PTR        ((reg16 *) Quad_TImer_TimerHW__PER0 )
    #define Quad_TImer_COUNTER_LSB         (* (reg16 *) Quad_TImer_TimerHW__CNT_CMP0 )
    #define Quad_TImer_COUNTER_LSB_PTR       ((reg16 *) Quad_TImer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define Quad_TImer_BLOCK_EN_MASK                     Quad_TImer_TimerHW__PM_ACT_MSK
    #define Quad_TImer_BLOCK_STBY_EN_MASK                Quad_TImer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define Quad_TImer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define Quad_TImer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define Quad_TImer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define Quad_TImer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define Quad_TImer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define Quad_TImer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << Quad_TImer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Quad_TImer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define Quad_TImer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << Quad_TImer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define Quad_TImer_CTRL_MODE_SHIFT                 0x01u
        #define Quad_TImer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << Quad_TImer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define Quad_TImer_CTRL_RCOD_SHIFT        0x02u
        #define Quad_TImer_CTRL_ENBL_SHIFT        0x00u
        #define Quad_TImer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define Quad_TImer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << Quad_TImer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define Quad_TImer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << Quad_TImer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define Quad_TImer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << Quad_TImer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define Quad_TImer_CTRL_RCOD       ((uint8)((uint8)0x03u << Quad_TImer_CTRL_RCOD_SHIFT))
        #define Quad_TImer_CTRL_ENBL       ((uint8)((uint8)0x80u << Quad_TImer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define Quad_TImer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define Quad_TImer_RT1_MASK                        ((uint8)((uint8)0x03u << Quad_TImer_RT1_SHIFT))
    #define Quad_TImer_SYNC                            ((uint8)((uint8)0x03u << Quad_TImer_RT1_SHIFT))
    #define Quad_TImer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define Quad_TImer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << Quad_TImer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define Quad_TImer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << Quad_TImer_SYNCDSI_SHIFT))

    #define Quad_TImer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << Quad_TImer_CTRL_MODE_SHIFT))
    #define Quad_TImer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << Quad_TImer_CTRL_MODE_SHIFT))
    #define Quad_TImer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << Quad_TImer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Quad_TImer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Quad_TImer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Quad_TImer_STATUS_TC_INT_MASK_SHIFT        (Quad_TImer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Quad_TImer_STATUS_CAPTURE_INT_MASK_SHIFT   (Quad_TImer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define Quad_TImer_STATUS_TC                       ((uint8)((uint8)0x01u << Quad_TImer_STATUS_TC_SHIFT))
    #define Quad_TImer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << Quad_TImer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define Quad_TImer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << Quad_TImer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define Quad_TImer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << Quad_TImer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define Quad_TImer_STATUS              (* (reg8 *) Quad_TImer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define Quad_TImer_STATUS_MASK         (* (reg8 *) Quad_TImer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define Quad_TImer_STATUS_AUX_CTRL     (* (reg8 *) Quad_TImer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define Quad_TImer_CONTROL             (* (reg8 *) Quad_TImer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(Quad_TImer_Resolution <= 8u) /* 8-bit Timer */
        #define Quad_TImer_CAPTURE_LSB         (* (reg8 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define Quad_TImer_CAPTURE_LSB_PTR       ((reg8 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define Quad_TImer_PERIOD_LSB          (* (reg8 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define Quad_TImer_PERIOD_LSB_PTR        ((reg8 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define Quad_TImer_COUNTER_LSB         (* (reg8 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define Quad_TImer_COUNTER_LSB_PTR       ((reg8 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(Quad_TImer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define Quad_TImer_CAPTURE_LSB         (* (reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define Quad_TImer_CAPTURE_LSB_PTR       ((reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define Quad_TImer_PERIOD_LSB          (* (reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define Quad_TImer_PERIOD_LSB_PTR        ((reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define Quad_TImer_COUNTER_LSB         (* (reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define Quad_TImer_COUNTER_LSB_PTR       ((reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define Quad_TImer_CAPTURE_LSB         (* (reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define Quad_TImer_CAPTURE_LSB_PTR       ((reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define Quad_TImer_PERIOD_LSB          (* (reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define Quad_TImer_PERIOD_LSB_PTR        ((reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define Quad_TImer_COUNTER_LSB         (* (reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define Quad_TImer_COUNTER_LSB_PTR       ((reg16 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(Quad_TImer_Resolution <= 24u)/* 24-bit Timer */
        #define Quad_TImer_CAPTURE_LSB         (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define Quad_TImer_CAPTURE_LSB_PTR       ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define Quad_TImer_PERIOD_LSB          (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define Quad_TImer_PERIOD_LSB_PTR        ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define Quad_TImer_COUNTER_LSB         (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define Quad_TImer_COUNTER_LSB_PTR       ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define Quad_TImer_CAPTURE_LSB         (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define Quad_TImer_CAPTURE_LSB_PTR       ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define Quad_TImer_PERIOD_LSB          (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define Quad_TImer_PERIOD_LSB_PTR        ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define Quad_TImer_COUNTER_LSB         (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define Quad_TImer_COUNTER_LSB_PTR       ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define Quad_TImer_CAPTURE_LSB         (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define Quad_TImer_CAPTURE_LSB_PTR       ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define Quad_TImer_PERIOD_LSB          (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define Quad_TImer_PERIOD_LSB_PTR        ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define Quad_TImer_COUNTER_LSB         (* (reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define Quad_TImer_COUNTER_LSB_PTR       ((reg32 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define Quad_TImer_COUNTER_LSB_PTR_8BIT       ((reg8 *) Quad_TImer_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (Quad_TImer_UsingHWCaptureCounter)
        #define Quad_TImer_CAP_COUNT              (*(reg8 *) Quad_TImer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Quad_TImer_CAP_COUNT_PTR          ( (reg8 *) Quad_TImer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Quad_TImer_CAPTURE_COUNT_CTRL     (*(reg8 *) Quad_TImer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define Quad_TImer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) Quad_TImer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (Quad_TImer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define Quad_TImer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define Quad_TImer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define Quad_TImer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define Quad_TImer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define Quad_TImer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define Quad_TImer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << Quad_TImer_CTRL_INTCNT_SHIFT))
    #define Quad_TImer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << Quad_TImer_CTRL_TRIG_MODE_SHIFT))
    #define Quad_TImer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << Quad_TImer_CTRL_TRIG_EN_SHIFT))
    #define Quad_TImer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << Quad_TImer_CTRL_CAP_MODE_SHIFT))
    #define Quad_TImer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << Quad_TImer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define Quad_TImer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define Quad_TImer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define Quad_TImer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define Quad_TImer_STATUS_TC_INT_MASK_SHIFT       Quad_TImer_STATUS_TC_SHIFT
    #define Quad_TImer_STATUS_CAPTURE_INT_MASK_SHIFT  Quad_TImer_STATUS_CAPTURE_SHIFT
    #define Quad_TImer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define Quad_TImer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define Quad_TImer_STATUS_FIFOFULL_INT_MASK_SHIFT Quad_TImer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define Quad_TImer_STATUS_TC                      ((uint8)((uint8)0x01u << Quad_TImer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define Quad_TImer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << Quad_TImer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Quad_TImer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << Quad_TImer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Quad_TImer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << Quad_TImer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define Quad_TImer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << Quad_TImer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define Quad_TImer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << Quad_TImer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Quad_TImer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << Quad_TImer_STATUS_FIFOFULL_SHIFT))

    #define Quad_TImer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define Quad_TImer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define Quad_TImer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define Quad_TImer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define Quad_TImer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define Quad_TImer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_Quad_TImer_H */


/* [] END OF FILE */
