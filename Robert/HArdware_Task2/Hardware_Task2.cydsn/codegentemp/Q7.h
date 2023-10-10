/*******************************************************************************
* File Name: Q7.h  
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

#if !defined(CY_PINS_Q7_H) /* Pins Q7_H */
#define CY_PINS_Q7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Q7_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Q7__PORT == 15 && ((Q7__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Q7_Write(uint8 value);
void    Q7_SetDriveMode(uint8 mode);
uint8   Q7_ReadDataReg(void);
uint8   Q7_Read(void);
void    Q7_SetInterruptMode(uint16 position, uint16 mode);
uint8   Q7_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Q7_SetDriveMode() function.
     *  @{
     */
        #define Q7_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Q7_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Q7_DM_RES_UP          PIN_DM_RES_UP
        #define Q7_DM_RES_DWN         PIN_DM_RES_DWN
        #define Q7_DM_OD_LO           PIN_DM_OD_LO
        #define Q7_DM_OD_HI           PIN_DM_OD_HI
        #define Q7_DM_STRONG          PIN_DM_STRONG
        #define Q7_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Q7_MASK               Q7__MASK
#define Q7_SHIFT              Q7__SHIFT
#define Q7_WIDTH              1u

/* Interrupt constants */
#if defined(Q7__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Q7_SetInterruptMode() function.
     *  @{
     */
        #define Q7_INTR_NONE      (uint16)(0x0000u)
        #define Q7_INTR_RISING    (uint16)(0x0001u)
        #define Q7_INTR_FALLING   (uint16)(0x0002u)
        #define Q7_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Q7_INTR_MASK      (0x01u) 
#endif /* (Q7__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Q7_PS                     (* (reg8 *) Q7__PS)
/* Data Register */
#define Q7_DR                     (* (reg8 *) Q7__DR)
/* Port Number */
#define Q7_PRT_NUM                (* (reg8 *) Q7__PRT) 
/* Connect to Analog Globals */                                                  
#define Q7_AG                     (* (reg8 *) Q7__AG)                       
/* Analog MUX bux enable */
#define Q7_AMUX                   (* (reg8 *) Q7__AMUX) 
/* Bidirectional Enable */                                                        
#define Q7_BIE                    (* (reg8 *) Q7__BIE)
/* Bit-mask for Aliased Register Access */
#define Q7_BIT_MASK               (* (reg8 *) Q7__BIT_MASK)
/* Bypass Enable */
#define Q7_BYP                    (* (reg8 *) Q7__BYP)
/* Port wide control signals */                                                   
#define Q7_CTL                    (* (reg8 *) Q7__CTL)
/* Drive Modes */
#define Q7_DM0                    (* (reg8 *) Q7__DM0) 
#define Q7_DM1                    (* (reg8 *) Q7__DM1)
#define Q7_DM2                    (* (reg8 *) Q7__DM2) 
/* Input Buffer Disable Override */
#define Q7_INP_DIS                (* (reg8 *) Q7__INP_DIS)
/* LCD Common or Segment Drive */
#define Q7_LCD_COM_SEG            (* (reg8 *) Q7__LCD_COM_SEG)
/* Enable Segment LCD */
#define Q7_LCD_EN                 (* (reg8 *) Q7__LCD_EN)
/* Slew Rate Control */
#define Q7_SLW                    (* (reg8 *) Q7__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Q7_PRTDSI__CAPS_SEL       (* (reg8 *) Q7__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Q7_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Q7__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Q7_PRTDSI__OE_SEL0        (* (reg8 *) Q7__PRTDSI__OE_SEL0) 
#define Q7_PRTDSI__OE_SEL1        (* (reg8 *) Q7__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Q7_PRTDSI__OUT_SEL0       (* (reg8 *) Q7__PRTDSI__OUT_SEL0) 
#define Q7_PRTDSI__OUT_SEL1       (* (reg8 *) Q7__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Q7_PRTDSI__SYNC_OUT       (* (reg8 *) Q7__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Q7__SIO_CFG)
    #define Q7_SIO_HYST_EN        (* (reg8 *) Q7__SIO_HYST_EN)
    #define Q7_SIO_REG_HIFREQ     (* (reg8 *) Q7__SIO_REG_HIFREQ)
    #define Q7_SIO_CFG            (* (reg8 *) Q7__SIO_CFG)
    #define Q7_SIO_DIFF           (* (reg8 *) Q7__SIO_DIFF)
#endif /* (Q7__SIO_CFG) */

/* Interrupt Registers */
#if defined(Q7__INTSTAT)
    #define Q7_INTSTAT            (* (reg8 *) Q7__INTSTAT)
    #define Q7_SNAP               (* (reg8 *) Q7__SNAP)
    
	#define Q7_0_INTTYPE_REG 		(* (reg8 *) Q7__0__INTTYPE)
#endif /* (Q7__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Q7_H */


/* [] END OF FILE */
