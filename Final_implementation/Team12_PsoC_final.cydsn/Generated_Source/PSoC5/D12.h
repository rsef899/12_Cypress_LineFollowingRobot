/*******************************************************************************
* File Name: D12.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_D12_H) /* Pins D12_H */
#define CY_PINS_D12_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "D12_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 D12__PORT == 15 && ((D12__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    D12_Write(uint8 value);
void    D12_SetDriveMode(uint8 mode);
uint8   D12_ReadDataReg(void);
uint8   D12_Read(void);
void    D12_SetInterruptMode(uint16 position, uint16 mode);
uint8   D12_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the D12_SetDriveMode() function.
     *  @{
     */
        #define D12_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define D12_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define D12_DM_RES_UP          PIN_DM_RES_UP
        #define D12_DM_RES_DWN         PIN_DM_RES_DWN
        #define D12_DM_OD_LO           PIN_DM_OD_LO
        #define D12_DM_OD_HI           PIN_DM_OD_HI
        #define D12_DM_STRONG          PIN_DM_STRONG
        #define D12_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define D12_MASK               D12__MASK
#define D12_SHIFT              D12__SHIFT
#define D12_WIDTH              1u

/* Interrupt constants */
#if defined(D12__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in D12_SetInterruptMode() function.
     *  @{
     */
        #define D12_INTR_NONE      (uint16)(0x0000u)
        #define D12_INTR_RISING    (uint16)(0x0001u)
        #define D12_INTR_FALLING   (uint16)(0x0002u)
        #define D12_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define D12_INTR_MASK      (0x01u) 
#endif /* (D12__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define D12_PS                     (* (reg8 *) D12__PS)
/* Data Register */
#define D12_DR                     (* (reg8 *) D12__DR)
/* Port Number */
#define D12_PRT_NUM                (* (reg8 *) D12__PRT) 
/* Connect to Analog Globals */                                                  
#define D12_AG                     (* (reg8 *) D12__AG)                       
/* Analog MUX bux enable */
#define D12_AMUX                   (* (reg8 *) D12__AMUX) 
/* Bidirectional Enable */                                                        
#define D12_BIE                    (* (reg8 *) D12__BIE)
/* Bit-mask for Aliased Register Access */
#define D12_BIT_MASK               (* (reg8 *) D12__BIT_MASK)
/* Bypass Enable */
#define D12_BYP                    (* (reg8 *) D12__BYP)
/* Port wide control signals */                                                   
#define D12_CTL                    (* (reg8 *) D12__CTL)
/* Drive Modes */
#define D12_DM0                    (* (reg8 *) D12__DM0) 
#define D12_DM1                    (* (reg8 *) D12__DM1)
#define D12_DM2                    (* (reg8 *) D12__DM2) 
/* Input Buffer Disable Override */
#define D12_INP_DIS                (* (reg8 *) D12__INP_DIS)
/* LCD Common or Segment Drive */
#define D12_LCD_COM_SEG            (* (reg8 *) D12__LCD_COM_SEG)
/* Enable Segment LCD */
#define D12_LCD_EN                 (* (reg8 *) D12__LCD_EN)
/* Slew Rate Control */
#define D12_SLW                    (* (reg8 *) D12__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define D12_PRTDSI__CAPS_SEL       (* (reg8 *) D12__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define D12_PRTDSI__DBL_SYNC_IN    (* (reg8 *) D12__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define D12_PRTDSI__OE_SEL0        (* (reg8 *) D12__PRTDSI__OE_SEL0) 
#define D12_PRTDSI__OE_SEL1        (* (reg8 *) D12__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define D12_PRTDSI__OUT_SEL0       (* (reg8 *) D12__PRTDSI__OUT_SEL0) 
#define D12_PRTDSI__OUT_SEL1       (* (reg8 *) D12__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define D12_PRTDSI__SYNC_OUT       (* (reg8 *) D12__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(D12__SIO_CFG)
    #define D12_SIO_HYST_EN        (* (reg8 *) D12__SIO_HYST_EN)
    #define D12_SIO_REG_HIFREQ     (* (reg8 *) D12__SIO_REG_HIFREQ)
    #define D12_SIO_CFG            (* (reg8 *) D12__SIO_CFG)
    #define D12_SIO_DIFF           (* (reg8 *) D12__SIO_DIFF)
#endif /* (D12__SIO_CFG) */

/* Interrupt Registers */
#if defined(D12__INTSTAT)
    #define D12_INTSTAT            (* (reg8 *) D12__INTSTAT)
    #define D12_SNAP               (* (reg8 *) D12__SNAP)
    
	#define D12_0_INTTYPE_REG 		(* (reg8 *) D12__0__INTTYPE)
#endif /* (D12__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_D12_H */


/* [] END OF FILE */
