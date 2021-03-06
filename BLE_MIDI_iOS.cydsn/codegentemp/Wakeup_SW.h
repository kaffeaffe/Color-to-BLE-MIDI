/*******************************************************************************
* File Name: Wakeup_SW.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Wakeup_SW_H) /* Pins Wakeup_SW_H */
#define CY_PINS_Wakeup_SW_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Wakeup_SW_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Wakeup_SW_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Wakeup_SW_Read(void);
void    Wakeup_SW_Write(uint8 value);
uint8   Wakeup_SW_ReadDataReg(void);
#if defined(Wakeup_SW__PC) || (CY_PSOC4_4200L) 
    void    Wakeup_SW_SetDriveMode(uint8 mode);
#endif
void    Wakeup_SW_SetInterruptMode(uint16 position, uint16 mode);
uint8   Wakeup_SW_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Wakeup_SW_Sleep(void); 
void Wakeup_SW_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Wakeup_SW__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Wakeup_SW_DRIVE_MODE_BITS        (3)
    #define Wakeup_SW_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Wakeup_SW_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Wakeup_SW_SetDriveMode() function.
         *  @{
         */
        #define Wakeup_SW_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Wakeup_SW_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Wakeup_SW_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Wakeup_SW_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Wakeup_SW_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Wakeup_SW_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Wakeup_SW_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Wakeup_SW_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Wakeup_SW_MASK               Wakeup_SW__MASK
#define Wakeup_SW_SHIFT              Wakeup_SW__SHIFT
#define Wakeup_SW_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Wakeup_SW_SetInterruptMode() function.
     *  @{
     */
        #define Wakeup_SW_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Wakeup_SW_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Wakeup_SW_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Wakeup_SW_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Wakeup_SW__SIO)
    #define Wakeup_SW_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Wakeup_SW__PC) && (CY_PSOC4_4200L)
    #define Wakeup_SW_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Wakeup_SW_USBIO_DISABLE              ((uint32)(~Wakeup_SW_USBIO_ENABLE))
    #define Wakeup_SW_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Wakeup_SW_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Wakeup_SW_USBIO_ENTER_SLEEP          ((uint32)((1u << Wakeup_SW_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Wakeup_SW_USBIO_SUSPEND_DEL_SHIFT)))
    #define Wakeup_SW_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Wakeup_SW_USBIO_SUSPEND_SHIFT)))
    #define Wakeup_SW_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Wakeup_SW_USBIO_SUSPEND_DEL_SHIFT)))
    #define Wakeup_SW_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Wakeup_SW__PC)
    /* Port Configuration */
    #define Wakeup_SW_PC                 (* (reg32 *) Wakeup_SW__PC)
#endif
/* Pin State */
#define Wakeup_SW_PS                     (* (reg32 *) Wakeup_SW__PS)
/* Data Register */
#define Wakeup_SW_DR                     (* (reg32 *) Wakeup_SW__DR)
/* Input Buffer Disable Override */
#define Wakeup_SW_INP_DIS                (* (reg32 *) Wakeup_SW__PC2)

/* Interrupt configuration Registers */
#define Wakeup_SW_INTCFG                 (* (reg32 *) Wakeup_SW__INTCFG)
#define Wakeup_SW_INTSTAT                (* (reg32 *) Wakeup_SW__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Wakeup_SW_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Wakeup_SW__SIO)
    #define Wakeup_SW_SIO_REG            (* (reg32 *) Wakeup_SW__SIO)
#endif /* (Wakeup_SW__SIO_CFG) */

/* USBIO registers */
#if !defined(Wakeup_SW__PC) && (CY_PSOC4_4200L)
    #define Wakeup_SW_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Wakeup_SW_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Wakeup_SW_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Wakeup_SW_DRIVE_MODE_SHIFT       (0x00u)
#define Wakeup_SW_DRIVE_MODE_MASK        (0x07u << Wakeup_SW_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Wakeup_SW_H */


/* [] END OF FILE */
