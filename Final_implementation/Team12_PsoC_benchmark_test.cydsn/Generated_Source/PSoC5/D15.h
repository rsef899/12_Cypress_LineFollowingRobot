/*******************************************************************************
* File Name: D15.h  
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

#if !defined(CY_PINS_D15_H) /* Pins D15_H */
#define CY_PINS_D15_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "D15_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 D15__PORT == 15 && ((D15__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    D15_Write(uint8 value);
void    D15_SetDriveMode(uint8 mode);
uint8   D15_ReadDataReg(void);
uint8   D15_Read(void);
void    D15_SetInterruptMode(uint16 position, uint16 mode);
uint8   D15_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the D15_SetDriveMode() function.
     *  @{
     */
        #define D15_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define D15_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define D15_DM_RES_UP          PIN_DM_RES_UP
        #define D15_DM_RES_DWN         PIN_DM_RES_DWN
        #define D15_DM_OD_LO           PIN_DM_OD_LO
        #define D15_DM_OD_HI           PIN_DM_OD_HI
        #define D15_DM_STRONG          PIN_DM_STRONG
        #define D15_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define D15_MASK               D15__MASK
#define D15_SHIFT              D15__SHIFT
#define D15_WIDTH              1u

/* Interrupt constants */
#if defined(D15__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in D15_SetInterruptMode() function.
     *  @{
     */
        #define D15_INTR_NONE      (uint16)(0x0000u)
        #define D15_INTR_RISING    (uint16)(0x0001u)
        #define D15_INTR_FALLING   (uint16)(0x0002u)
        #define D15_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define D15_INTR_MASK      (0x01u) 
#endif /* (D15__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define D15_PS                     (* (reg8 *) D15__PS)
/* Data Register */
#define D15_DR                     (* (reg8 *) D15__DR)
/* Port Number */
#define D15_PRT_NUM                (* (reg8 *) D15__PRT) 
/* Connect to Analog Globals */                                                  
#define D15_AG                     (* (reg8 *) D15__AG)                       
/* Analog MUX bux enable */
#define D15_AMUX                   (* (reg8 *) D15__AMUX) 
/* Bidirectional Enable */                                                        
#define D15_BIE                    (* (reg8 *) D15__BIE)
/* Bit-mask for Aliased Register Access */
#define D15_BIT_MASK               (* (reg8 *) D15__BIT_MASK)
/* Bypass Enable */
#define D15_BYP                    (* (reg8 *) D15__BYP)
/* Port wide control signals */                                                   
#define D15_CTL                    (* (reg8 *) D15__CTL)
/* Drive Modes */
#define D15_DM0                    (* (reg8 *) D15__DM0) 
#define D15_DM1                    (* (reg8 *) D15__DM1)
#define D15_DM2                    (* (reg8 *) D15__DM2) 
/* Input Buffer Disable Override */
#define D15_INP_DIS                (* (reg8 *) D15__INP_DIS)
/* LCD Common or Segment Drive */
#define D15_LCD_COM_SEG            (* (reg8 *) D15__LCD_COM_SEG)
/* Enable Segment LCD */
#define D15_LCD_EN                 (* (reg8 *) D15__LCD_EN)
/* Slew Rate Control */
#define D15_SLW                    (* (reg8 *) D15__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define D15_PRTDSI__CAPS_SEL       (* (reg8 *) D15__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define D15_PRTDSI__DBL_SYNC_IN    (* (reg8 *) D15__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define D15_PRTDSI__OE_SEL0        (* (reg8 *) D15__PRTDSI__OE_SEL0) 
#define D15_PRTDSI__OE_SEL1        (* (reg8 *) D15__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define D15_PRTDSI__OUT_SEL0       (* (reg8 *) D15__PRTDSI__OUT_SEL0) 
#define D15_PRTDSI__OUT_SEL1       (* (reg8 *) D15__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define D15_PRTDSI__SYNC_OUT       (* (reg8 *) D15__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(D15__SIO_CFG)
    #define D15_SIO_HYST_EN        (* (reg8 *) D15__SIO_HYST_EN)
    #define D15_SIO_REG_HIFREQ     (* (reg8 *) D15__SIO_REG_HIFREQ)
    #define D15_SIO_CFG            (* (reg8 *) D15__SIO_CFG)
    #define D15_SIO_DIFF           (* (reg8 *) D15__SIO_DIFF)
#endif /* (D15__SIO_CFG) */

/* Interrupt Registers */
#if defined(D15__INTSTAT)
    #define D15_INTSTAT            (* (reg8 *) D15__INTSTAT)
    #define D15_SNAP               (* (reg8 *) D15__SNAP)
    
	#define D15_0_INTTYPE_REG 		(* (reg8 *) D15__0__INTTYPE)
#endif /* (D15__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_D15_H */


/* [] END OF FILE */
