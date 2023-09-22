/*******************************************************************************
* File Name: D14.h  
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

#if !defined(CY_PINS_D14_H) /* Pins D14_H */
#define CY_PINS_D14_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "D14_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 D14__PORT == 15 && ((D14__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    D14_Write(uint8 value);
void    D14_SetDriveMode(uint8 mode);
uint8   D14_ReadDataReg(void);
uint8   D14_Read(void);
void    D14_SetInterruptMode(uint16 position, uint16 mode);
uint8   D14_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the D14_SetDriveMode() function.
     *  @{
     */
        #define D14_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define D14_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define D14_DM_RES_UP          PIN_DM_RES_UP
        #define D14_DM_RES_DWN         PIN_DM_RES_DWN
        #define D14_DM_OD_LO           PIN_DM_OD_LO
        #define D14_DM_OD_HI           PIN_DM_OD_HI
        #define D14_DM_STRONG          PIN_DM_STRONG
        #define D14_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define D14_MASK               D14__MASK
#define D14_SHIFT              D14__SHIFT
#define D14_WIDTH              1u

/* Interrupt constants */
#if defined(D14__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in D14_SetInterruptMode() function.
     *  @{
     */
        #define D14_INTR_NONE      (uint16)(0x0000u)
        #define D14_INTR_RISING    (uint16)(0x0001u)
        #define D14_INTR_FALLING   (uint16)(0x0002u)
        #define D14_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define D14_INTR_MASK      (0x01u) 
#endif /* (D14__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define D14_PS                     (* (reg8 *) D14__PS)
/* Data Register */
#define D14_DR                     (* (reg8 *) D14__DR)
/* Port Number */
#define D14_PRT_NUM                (* (reg8 *) D14__PRT) 
/* Connect to Analog Globals */                                                  
#define D14_AG                     (* (reg8 *) D14__AG)                       
/* Analog MUX bux enable */
#define D14_AMUX                   (* (reg8 *) D14__AMUX) 
/* Bidirectional Enable */                                                        
#define D14_BIE                    (* (reg8 *) D14__BIE)
/* Bit-mask for Aliased Register Access */
#define D14_BIT_MASK               (* (reg8 *) D14__BIT_MASK)
/* Bypass Enable */
#define D14_BYP                    (* (reg8 *) D14__BYP)
/* Port wide control signals */                                                   
#define D14_CTL                    (* (reg8 *) D14__CTL)
/* Drive Modes */
#define D14_DM0                    (* (reg8 *) D14__DM0) 
#define D14_DM1                    (* (reg8 *) D14__DM1)
#define D14_DM2                    (* (reg8 *) D14__DM2) 
/* Input Buffer Disable Override */
#define D14_INP_DIS                (* (reg8 *) D14__INP_DIS)
/* LCD Common or Segment Drive */
#define D14_LCD_COM_SEG            (* (reg8 *) D14__LCD_COM_SEG)
/* Enable Segment LCD */
#define D14_LCD_EN                 (* (reg8 *) D14__LCD_EN)
/* Slew Rate Control */
#define D14_SLW                    (* (reg8 *) D14__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define D14_PRTDSI__CAPS_SEL       (* (reg8 *) D14__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define D14_PRTDSI__DBL_SYNC_IN    (* (reg8 *) D14__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define D14_PRTDSI__OE_SEL0        (* (reg8 *) D14__PRTDSI__OE_SEL0) 
#define D14_PRTDSI__OE_SEL1        (* (reg8 *) D14__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define D14_PRTDSI__OUT_SEL0       (* (reg8 *) D14__PRTDSI__OUT_SEL0) 
#define D14_PRTDSI__OUT_SEL1       (* (reg8 *) D14__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define D14_PRTDSI__SYNC_OUT       (* (reg8 *) D14__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(D14__SIO_CFG)
    #define D14_SIO_HYST_EN        (* (reg8 *) D14__SIO_HYST_EN)
    #define D14_SIO_REG_HIFREQ     (* (reg8 *) D14__SIO_REG_HIFREQ)
    #define D14_SIO_CFG            (* (reg8 *) D14__SIO_CFG)
    #define D14_SIO_DIFF           (* (reg8 *) D14__SIO_DIFF)
#endif /* (D14__SIO_CFG) */

/* Interrupt Registers */
#if defined(D14__INTSTAT)
    #define D14_INTSTAT            (* (reg8 *) D14__INTSTAT)
    #define D14_SNAP               (* (reg8 *) D14__SNAP)
    
	#define D14_0_INTTYPE_REG 		(* (reg8 *) D14__0__INTTYPE)
#endif /* (D14__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_D14_H */


/* [] END OF FILE */
