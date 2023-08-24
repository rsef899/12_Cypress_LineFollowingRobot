/*******************************************************************************
* File Name: SENS1.h  
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

#if !defined(CY_PINS_SENS1_H) /* Pins SENS1_H */
#define CY_PINS_SENS1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SENS1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SENS1__PORT == 15 && ((SENS1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SENS1_Write(uint8 value);
void    SENS1_SetDriveMode(uint8 mode);
uint8   SENS1_ReadDataReg(void);
uint8   SENS1_Read(void);
void    SENS1_SetInterruptMode(uint16 position, uint16 mode);
uint8   SENS1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SENS1_SetDriveMode() function.
     *  @{
     */
        #define SENS1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SENS1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SENS1_DM_RES_UP          PIN_DM_RES_UP
        #define SENS1_DM_RES_DWN         PIN_DM_RES_DWN
        #define SENS1_DM_OD_LO           PIN_DM_OD_LO
        #define SENS1_DM_OD_HI           PIN_DM_OD_HI
        #define SENS1_DM_STRONG          PIN_DM_STRONG
        #define SENS1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SENS1_MASK               SENS1__MASK
#define SENS1_SHIFT              SENS1__SHIFT
#define SENS1_WIDTH              1u

/* Interrupt constants */
#if defined(SENS1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SENS1_SetInterruptMode() function.
     *  @{
     */
        #define SENS1_INTR_NONE      (uint16)(0x0000u)
        #define SENS1_INTR_RISING    (uint16)(0x0001u)
        #define SENS1_INTR_FALLING   (uint16)(0x0002u)
        #define SENS1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SENS1_INTR_MASK      (0x01u) 
#endif /* (SENS1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SENS1_PS                     (* (reg8 *) SENS1__PS)
/* Data Register */
#define SENS1_DR                     (* (reg8 *) SENS1__DR)
/* Port Number */
#define SENS1_PRT_NUM                (* (reg8 *) SENS1__PRT) 
/* Connect to Analog Globals */                                                  
#define SENS1_AG                     (* (reg8 *) SENS1__AG)                       
/* Analog MUX bux enable */
#define SENS1_AMUX                   (* (reg8 *) SENS1__AMUX) 
/* Bidirectional Enable */                                                        
#define SENS1_BIE                    (* (reg8 *) SENS1__BIE)
/* Bit-mask for Aliased Register Access */
#define SENS1_BIT_MASK               (* (reg8 *) SENS1__BIT_MASK)
/* Bypass Enable */
#define SENS1_BYP                    (* (reg8 *) SENS1__BYP)
/* Port wide control signals */                                                   
#define SENS1_CTL                    (* (reg8 *) SENS1__CTL)
/* Drive Modes */
#define SENS1_DM0                    (* (reg8 *) SENS1__DM0) 
#define SENS1_DM1                    (* (reg8 *) SENS1__DM1)
#define SENS1_DM2                    (* (reg8 *) SENS1__DM2) 
/* Input Buffer Disable Override */
#define SENS1_INP_DIS                (* (reg8 *) SENS1__INP_DIS)
/* LCD Common or Segment Drive */
#define SENS1_LCD_COM_SEG            (* (reg8 *) SENS1__LCD_COM_SEG)
/* Enable Segment LCD */
#define SENS1_LCD_EN                 (* (reg8 *) SENS1__LCD_EN)
/* Slew Rate Control */
#define SENS1_SLW                    (* (reg8 *) SENS1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SENS1_PRTDSI__CAPS_SEL       (* (reg8 *) SENS1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SENS1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SENS1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SENS1_PRTDSI__OE_SEL0        (* (reg8 *) SENS1__PRTDSI__OE_SEL0) 
#define SENS1_PRTDSI__OE_SEL1        (* (reg8 *) SENS1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SENS1_PRTDSI__OUT_SEL0       (* (reg8 *) SENS1__PRTDSI__OUT_SEL0) 
#define SENS1_PRTDSI__OUT_SEL1       (* (reg8 *) SENS1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SENS1_PRTDSI__SYNC_OUT       (* (reg8 *) SENS1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SENS1__SIO_CFG)
    #define SENS1_SIO_HYST_EN        (* (reg8 *) SENS1__SIO_HYST_EN)
    #define SENS1_SIO_REG_HIFREQ     (* (reg8 *) SENS1__SIO_REG_HIFREQ)
    #define SENS1_SIO_CFG            (* (reg8 *) SENS1__SIO_CFG)
    #define SENS1_SIO_DIFF           (* (reg8 *) SENS1__SIO_DIFF)
#endif /* (SENS1__SIO_CFG) */

/* Interrupt Registers */
#if defined(SENS1__INTSTAT)
    #define SENS1_INTSTAT            (* (reg8 *) SENS1__INTSTAT)
    #define SENS1_SNAP               (* (reg8 *) SENS1__SNAP)
    
	#define SENS1_0_INTTYPE_REG 		(* (reg8 *) SENS1__0__INTTYPE)
#endif /* (SENS1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SENS1_H */


/* [] END OF FILE */
