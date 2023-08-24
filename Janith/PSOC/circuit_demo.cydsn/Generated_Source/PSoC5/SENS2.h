/*******************************************************************************
* File Name: SENS2.h  
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

#if !defined(CY_PINS_SENS2_H) /* Pins SENS2_H */
#define CY_PINS_SENS2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SENS2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SENS2__PORT == 15 && ((SENS2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SENS2_Write(uint8 value);
void    SENS2_SetDriveMode(uint8 mode);
uint8   SENS2_ReadDataReg(void);
uint8   SENS2_Read(void);
void    SENS2_SetInterruptMode(uint16 position, uint16 mode);
uint8   SENS2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SENS2_SetDriveMode() function.
     *  @{
     */
        #define SENS2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SENS2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SENS2_DM_RES_UP          PIN_DM_RES_UP
        #define SENS2_DM_RES_DWN         PIN_DM_RES_DWN
        #define SENS2_DM_OD_LO           PIN_DM_OD_LO
        #define SENS2_DM_OD_HI           PIN_DM_OD_HI
        #define SENS2_DM_STRONG          PIN_DM_STRONG
        #define SENS2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SENS2_MASK               SENS2__MASK
#define SENS2_SHIFT              SENS2__SHIFT
#define SENS2_WIDTH              1u

/* Interrupt constants */
#if defined(SENS2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SENS2_SetInterruptMode() function.
     *  @{
     */
        #define SENS2_INTR_NONE      (uint16)(0x0000u)
        #define SENS2_INTR_RISING    (uint16)(0x0001u)
        #define SENS2_INTR_FALLING   (uint16)(0x0002u)
        #define SENS2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SENS2_INTR_MASK      (0x01u) 
#endif /* (SENS2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SENS2_PS                     (* (reg8 *) SENS2__PS)
/* Data Register */
#define SENS2_DR                     (* (reg8 *) SENS2__DR)
/* Port Number */
#define SENS2_PRT_NUM                (* (reg8 *) SENS2__PRT) 
/* Connect to Analog Globals */                                                  
#define SENS2_AG                     (* (reg8 *) SENS2__AG)                       
/* Analog MUX bux enable */
#define SENS2_AMUX                   (* (reg8 *) SENS2__AMUX) 
/* Bidirectional Enable */                                                        
#define SENS2_BIE                    (* (reg8 *) SENS2__BIE)
/* Bit-mask for Aliased Register Access */
#define SENS2_BIT_MASK               (* (reg8 *) SENS2__BIT_MASK)
/* Bypass Enable */
#define SENS2_BYP                    (* (reg8 *) SENS2__BYP)
/* Port wide control signals */                                                   
#define SENS2_CTL                    (* (reg8 *) SENS2__CTL)
/* Drive Modes */
#define SENS2_DM0                    (* (reg8 *) SENS2__DM0) 
#define SENS2_DM1                    (* (reg8 *) SENS2__DM1)
#define SENS2_DM2                    (* (reg8 *) SENS2__DM2) 
/* Input Buffer Disable Override */
#define SENS2_INP_DIS                (* (reg8 *) SENS2__INP_DIS)
/* LCD Common or Segment Drive */
#define SENS2_LCD_COM_SEG            (* (reg8 *) SENS2__LCD_COM_SEG)
/* Enable Segment LCD */
#define SENS2_LCD_EN                 (* (reg8 *) SENS2__LCD_EN)
/* Slew Rate Control */
#define SENS2_SLW                    (* (reg8 *) SENS2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SENS2_PRTDSI__CAPS_SEL       (* (reg8 *) SENS2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SENS2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SENS2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SENS2_PRTDSI__OE_SEL0        (* (reg8 *) SENS2__PRTDSI__OE_SEL0) 
#define SENS2_PRTDSI__OE_SEL1        (* (reg8 *) SENS2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SENS2_PRTDSI__OUT_SEL0       (* (reg8 *) SENS2__PRTDSI__OUT_SEL0) 
#define SENS2_PRTDSI__OUT_SEL1       (* (reg8 *) SENS2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SENS2_PRTDSI__SYNC_OUT       (* (reg8 *) SENS2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SENS2__SIO_CFG)
    #define SENS2_SIO_HYST_EN        (* (reg8 *) SENS2__SIO_HYST_EN)
    #define SENS2_SIO_REG_HIFREQ     (* (reg8 *) SENS2__SIO_REG_HIFREQ)
    #define SENS2_SIO_CFG            (* (reg8 *) SENS2__SIO_CFG)
    #define SENS2_SIO_DIFF           (* (reg8 *) SENS2__SIO_DIFF)
#endif /* (SENS2__SIO_CFG) */

/* Interrupt Registers */
#if defined(SENS2__INTSTAT)
    #define SENS2_INTSTAT            (* (reg8 *) SENS2__INTSTAT)
    #define SENS2_SNAP               (* (reg8 *) SENS2__SNAP)
    
	#define SENS2_0_INTTYPE_REG 		(* (reg8 *) SENS2__0__INTTYPE)
#endif /* (SENS2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SENS2_H */


/* [] END OF FILE */
