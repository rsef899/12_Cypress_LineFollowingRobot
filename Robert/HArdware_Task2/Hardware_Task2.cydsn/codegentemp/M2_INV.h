/*******************************************************************************
* File Name: M2_INV.h  
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

#if !defined(CY_PINS_M2_INV_H) /* Pins M2_INV_H */
#define CY_PINS_M2_INV_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "M2_INV_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 M2_INV__PORT == 15 && ((M2_INV__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    M2_INV_Write(uint8 value);
void    M2_INV_SetDriveMode(uint8 mode);
uint8   M2_INV_ReadDataReg(void);
uint8   M2_INV_Read(void);
void    M2_INV_SetInterruptMode(uint16 position, uint16 mode);
uint8   M2_INV_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the M2_INV_SetDriveMode() function.
     *  @{
     */
        #define M2_INV_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define M2_INV_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define M2_INV_DM_RES_UP          PIN_DM_RES_UP
        #define M2_INV_DM_RES_DWN         PIN_DM_RES_DWN
        #define M2_INV_DM_OD_LO           PIN_DM_OD_LO
        #define M2_INV_DM_OD_HI           PIN_DM_OD_HI
        #define M2_INV_DM_STRONG          PIN_DM_STRONG
        #define M2_INV_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define M2_INV_MASK               M2_INV__MASK
#define M2_INV_SHIFT              M2_INV__SHIFT
#define M2_INV_WIDTH              1u

/* Interrupt constants */
#if defined(M2_INV__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in M2_INV_SetInterruptMode() function.
     *  @{
     */
        #define M2_INV_INTR_NONE      (uint16)(0x0000u)
        #define M2_INV_INTR_RISING    (uint16)(0x0001u)
        #define M2_INV_INTR_FALLING   (uint16)(0x0002u)
        #define M2_INV_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define M2_INV_INTR_MASK      (0x01u) 
#endif /* (M2_INV__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M2_INV_PS                     (* (reg8 *) M2_INV__PS)
/* Data Register */
#define M2_INV_DR                     (* (reg8 *) M2_INV__DR)
/* Port Number */
#define M2_INV_PRT_NUM                (* (reg8 *) M2_INV__PRT) 
/* Connect to Analog Globals */                                                  
#define M2_INV_AG                     (* (reg8 *) M2_INV__AG)                       
/* Analog MUX bux enable */
#define M2_INV_AMUX                   (* (reg8 *) M2_INV__AMUX) 
/* Bidirectional Enable */                                                        
#define M2_INV_BIE                    (* (reg8 *) M2_INV__BIE)
/* Bit-mask for Aliased Register Access */
#define M2_INV_BIT_MASK               (* (reg8 *) M2_INV__BIT_MASK)
/* Bypass Enable */
#define M2_INV_BYP                    (* (reg8 *) M2_INV__BYP)
/* Port wide control signals */                                                   
#define M2_INV_CTL                    (* (reg8 *) M2_INV__CTL)
/* Drive Modes */
#define M2_INV_DM0                    (* (reg8 *) M2_INV__DM0) 
#define M2_INV_DM1                    (* (reg8 *) M2_INV__DM1)
#define M2_INV_DM2                    (* (reg8 *) M2_INV__DM2) 
/* Input Buffer Disable Override */
#define M2_INV_INP_DIS                (* (reg8 *) M2_INV__INP_DIS)
/* LCD Common or Segment Drive */
#define M2_INV_LCD_COM_SEG            (* (reg8 *) M2_INV__LCD_COM_SEG)
/* Enable Segment LCD */
#define M2_INV_LCD_EN                 (* (reg8 *) M2_INV__LCD_EN)
/* Slew Rate Control */
#define M2_INV_SLW                    (* (reg8 *) M2_INV__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define M2_INV_PRTDSI__CAPS_SEL       (* (reg8 *) M2_INV__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define M2_INV_PRTDSI__DBL_SYNC_IN    (* (reg8 *) M2_INV__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define M2_INV_PRTDSI__OE_SEL0        (* (reg8 *) M2_INV__PRTDSI__OE_SEL0) 
#define M2_INV_PRTDSI__OE_SEL1        (* (reg8 *) M2_INV__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define M2_INV_PRTDSI__OUT_SEL0       (* (reg8 *) M2_INV__PRTDSI__OUT_SEL0) 
#define M2_INV_PRTDSI__OUT_SEL1       (* (reg8 *) M2_INV__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define M2_INV_PRTDSI__SYNC_OUT       (* (reg8 *) M2_INV__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(M2_INV__SIO_CFG)
    #define M2_INV_SIO_HYST_EN        (* (reg8 *) M2_INV__SIO_HYST_EN)
    #define M2_INV_SIO_REG_HIFREQ     (* (reg8 *) M2_INV__SIO_REG_HIFREQ)
    #define M2_INV_SIO_CFG            (* (reg8 *) M2_INV__SIO_CFG)
    #define M2_INV_SIO_DIFF           (* (reg8 *) M2_INV__SIO_DIFF)
#endif /* (M2_INV__SIO_CFG) */

/* Interrupt Registers */
#if defined(M2_INV__INTSTAT)
    #define M2_INV_INTSTAT            (* (reg8 *) M2_INV__INTSTAT)
    #define M2_INV_SNAP               (* (reg8 *) M2_INV__SNAP)
    
	#define M2_INV_0_INTTYPE_REG 		(* (reg8 *) M2_INV__0__INTTYPE)
#endif /* (M2_INV__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_M2_INV_H */


/* [] END OF FILE */
