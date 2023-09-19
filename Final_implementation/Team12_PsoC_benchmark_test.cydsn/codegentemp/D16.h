/*******************************************************************************
* File Name: D16.h  
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

#if !defined(CY_PINS_D16_H) /* Pins D16_H */
#define CY_PINS_D16_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "D16_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 D16__PORT == 15 && ((D16__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    D16_Write(uint8 value);
void    D16_SetDriveMode(uint8 mode);
uint8   D16_ReadDataReg(void);
uint8   D16_Read(void);
void    D16_SetInterruptMode(uint16 position, uint16 mode);
uint8   D16_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the D16_SetDriveMode() function.
     *  @{
     */
        #define D16_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define D16_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define D16_DM_RES_UP          PIN_DM_RES_UP
        #define D16_DM_RES_DWN         PIN_DM_RES_DWN
        #define D16_DM_OD_LO           PIN_DM_OD_LO
        #define D16_DM_OD_HI           PIN_DM_OD_HI
        #define D16_DM_STRONG          PIN_DM_STRONG
        #define D16_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define D16_MASK               D16__MASK
#define D16_SHIFT              D16__SHIFT
#define D16_WIDTH              1u

/* Interrupt constants */
#if defined(D16__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in D16_SetInterruptMode() function.
     *  @{
     */
        #define D16_INTR_NONE      (uint16)(0x0000u)
        #define D16_INTR_RISING    (uint16)(0x0001u)
        #define D16_INTR_FALLING   (uint16)(0x0002u)
        #define D16_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define D16_INTR_MASK      (0x01u) 
#endif /* (D16__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define D16_PS                     (* (reg8 *) D16__PS)
/* Data Register */
#define D16_DR                     (* (reg8 *) D16__DR)
/* Port Number */
#define D16_PRT_NUM                (* (reg8 *) D16__PRT) 
/* Connect to Analog Globals */                                                  
#define D16_AG                     (* (reg8 *) D16__AG)                       
/* Analog MUX bux enable */
#define D16_AMUX                   (* (reg8 *) D16__AMUX) 
/* Bidirectional Enable */                                                        
#define D16_BIE                    (* (reg8 *) D16__BIE)
/* Bit-mask for Aliased Register Access */
#define D16_BIT_MASK               (* (reg8 *) D16__BIT_MASK)
/* Bypass Enable */
#define D16_BYP                    (* (reg8 *) D16__BYP)
/* Port wide control signals */                                                   
#define D16_CTL                    (* (reg8 *) D16__CTL)
/* Drive Modes */
#define D16_DM0                    (* (reg8 *) D16__DM0) 
#define D16_DM1                    (* (reg8 *) D16__DM1)
#define D16_DM2                    (* (reg8 *) D16__DM2) 
/* Input Buffer Disable Override */
#define D16_INP_DIS                (* (reg8 *) D16__INP_DIS)
/* LCD Common or Segment Drive */
#define D16_LCD_COM_SEG            (* (reg8 *) D16__LCD_COM_SEG)
/* Enable Segment LCD */
#define D16_LCD_EN                 (* (reg8 *) D16__LCD_EN)
/* Slew Rate Control */
#define D16_SLW                    (* (reg8 *) D16__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define D16_PRTDSI__CAPS_SEL       (* (reg8 *) D16__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define D16_PRTDSI__DBL_SYNC_IN    (* (reg8 *) D16__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define D16_PRTDSI__OE_SEL0        (* (reg8 *) D16__PRTDSI__OE_SEL0) 
#define D16_PRTDSI__OE_SEL1        (* (reg8 *) D16__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define D16_PRTDSI__OUT_SEL0       (* (reg8 *) D16__PRTDSI__OUT_SEL0) 
#define D16_PRTDSI__OUT_SEL1       (* (reg8 *) D16__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define D16_PRTDSI__SYNC_OUT       (* (reg8 *) D16__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(D16__SIO_CFG)
    #define D16_SIO_HYST_EN        (* (reg8 *) D16__SIO_HYST_EN)
    #define D16_SIO_REG_HIFREQ     (* (reg8 *) D16__SIO_REG_HIFREQ)
    #define D16_SIO_CFG            (* (reg8 *) D16__SIO_CFG)
    #define D16_SIO_DIFF           (* (reg8 *) D16__SIO_DIFF)
#endif /* (D16__SIO_CFG) */

/* Interrupt Registers */
#if defined(D16__INTSTAT)
    #define D16_INTSTAT            (* (reg8 *) D16__INTSTAT)
    #define D16_SNAP               (* (reg8 *) D16__SNAP)
    
	#define D16_0_INTTYPE_REG 		(* (reg8 *) D16__0__INTTYPE)
#endif /* (D16__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_D16_H */


/* [] END OF FILE */
