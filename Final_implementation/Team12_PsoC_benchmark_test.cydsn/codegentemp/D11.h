/*******************************************************************************
* File Name: D11.h  
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

#if !defined(CY_PINS_D11_H) /* Pins D11_H */
#define CY_PINS_D11_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "D11_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 D11__PORT == 15 && ((D11__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    D11_Write(uint8 value);
void    D11_SetDriveMode(uint8 mode);
uint8   D11_ReadDataReg(void);
uint8   D11_Read(void);
void    D11_SetInterruptMode(uint16 position, uint16 mode);
uint8   D11_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the D11_SetDriveMode() function.
     *  @{
     */
        #define D11_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define D11_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define D11_DM_RES_UP          PIN_DM_RES_UP
        #define D11_DM_RES_DWN         PIN_DM_RES_DWN
        #define D11_DM_OD_LO           PIN_DM_OD_LO
        #define D11_DM_OD_HI           PIN_DM_OD_HI
        #define D11_DM_STRONG          PIN_DM_STRONG
        #define D11_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define D11_MASK               D11__MASK
#define D11_SHIFT              D11__SHIFT
#define D11_WIDTH              1u

/* Interrupt constants */
#if defined(D11__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in D11_SetInterruptMode() function.
     *  @{
     */
        #define D11_INTR_NONE      (uint16)(0x0000u)
        #define D11_INTR_RISING    (uint16)(0x0001u)
        #define D11_INTR_FALLING   (uint16)(0x0002u)
        #define D11_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define D11_INTR_MASK      (0x01u) 
#endif /* (D11__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define D11_PS                     (* (reg8 *) D11__PS)
/* Data Register */
#define D11_DR                     (* (reg8 *) D11__DR)
/* Port Number */
#define D11_PRT_NUM                (* (reg8 *) D11__PRT) 
/* Connect to Analog Globals */                                                  
#define D11_AG                     (* (reg8 *) D11__AG)                       
/* Analog MUX bux enable */
#define D11_AMUX                   (* (reg8 *) D11__AMUX) 
/* Bidirectional Enable */                                                        
#define D11_BIE                    (* (reg8 *) D11__BIE)
/* Bit-mask for Aliased Register Access */
#define D11_BIT_MASK               (* (reg8 *) D11__BIT_MASK)
/* Bypass Enable */
#define D11_BYP                    (* (reg8 *) D11__BYP)
/* Port wide control signals */                                                   
#define D11_CTL                    (* (reg8 *) D11__CTL)
/* Drive Modes */
#define D11_DM0                    (* (reg8 *) D11__DM0) 
#define D11_DM1                    (* (reg8 *) D11__DM1)
#define D11_DM2                    (* (reg8 *) D11__DM2) 
/* Input Buffer Disable Override */
#define D11_INP_DIS                (* (reg8 *) D11__INP_DIS)
/* LCD Common or Segment Drive */
#define D11_LCD_COM_SEG            (* (reg8 *) D11__LCD_COM_SEG)
/* Enable Segment LCD */
#define D11_LCD_EN                 (* (reg8 *) D11__LCD_EN)
/* Slew Rate Control */
#define D11_SLW                    (* (reg8 *) D11__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define D11_PRTDSI__CAPS_SEL       (* (reg8 *) D11__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define D11_PRTDSI__DBL_SYNC_IN    (* (reg8 *) D11__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define D11_PRTDSI__OE_SEL0        (* (reg8 *) D11__PRTDSI__OE_SEL0) 
#define D11_PRTDSI__OE_SEL1        (* (reg8 *) D11__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define D11_PRTDSI__OUT_SEL0       (* (reg8 *) D11__PRTDSI__OUT_SEL0) 
#define D11_PRTDSI__OUT_SEL1       (* (reg8 *) D11__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define D11_PRTDSI__SYNC_OUT       (* (reg8 *) D11__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(D11__SIO_CFG)
    #define D11_SIO_HYST_EN        (* (reg8 *) D11__SIO_HYST_EN)
    #define D11_SIO_REG_HIFREQ     (* (reg8 *) D11__SIO_REG_HIFREQ)
    #define D11_SIO_CFG            (* (reg8 *) D11__SIO_CFG)
    #define D11_SIO_DIFF           (* (reg8 *) D11__SIO_DIFF)
#endif /* (D11__SIO_CFG) */

/* Interrupt Registers */
#if defined(D11__INTSTAT)
    #define D11_INTSTAT            (* (reg8 *) D11__INTSTAT)
    #define D11_SNAP               (* (reg8 *) D11__SNAP)
    
	#define D11_0_INTTYPE_REG 		(* (reg8 *) D11__0__INTTYPE)
#endif /* (D11__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_D11_H */


/* [] END OF FILE */
