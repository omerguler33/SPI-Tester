/**
  ******************************************************************************
  * @file    stm320518_eval_i2c_tsensor_cpal.h
  * @author  MCD Application Team
  * @version V1.1.2
  * @date    13-October-2021
  * @brief   This file contains all the functions prototypes for the 
  *          stm320518_eval_i2c_tsensor_cpal.c firmware driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM320518_EVAL_I2C_TSENSOR_CPAL_H
#define __STM320518_EVAL_I2C_TSENSOR_CPAL_H

#ifdef __cplusplus
 extern "C" {
#endif
   
   
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_i2c_cpal.h"
   
/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  TSENSOR Status  
  */ 
typedef enum
{
  LM75_OK = 0,
  LM75_FAIL
}LM75_Status_TypDef;

/* Exported constants --------------------------------------------------------*/
    
/*====================== CPAL Structure configuration ========================*/ 
/* Select I2C device (uncomment relative define) */

//#define LM75_DevStructure                I2C1_DevStructure   
#define LM75_DevStructure                I2C2_DevStructure  

   
/*============== TIMING Configuration ==========================*/
#define LM75_I2C_TIMING 0x1045061D


/*=================== Programming model Configuration ========================*/
/* Select interrupt programming model : By default DMA programming model is selected.
 To select interrupt programming model uncomment this define */
//#define LM75_IT


/* Maximum Timeout values for waiting until device is ready for communication.*/
   
#define LM75_TIMEOUT        ((uint32_t)0x3FFFF)

/**
  * @brief  Internal register Memory
  */
#define LM75_REG_TEMP       0x00  /* Temperature Register of LM75 */
#define LM75_REG_CONF       0x01  /* Configuration Register of LM75 */
#define LM75_REG_THYS       0x02  /* Temperature Register of LM75 */
#define LM75_REG_TOS        0x03  /* Over-temp Shutdown threshold Register of LM75 */
#define LM75_ADDR           0x90   /* LM75 address */
   

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

void LM75_DeInit(void);
void LM75_Config(void);
ErrorStatus LM75_GetStatus(void);
uint16_t LM75_ReadTemp(void);
uint16_t LM75_ReadReg(uint8_t RegName);
uint8_t LM75_WriteReg(uint8_t RegName, uint16_t RegValue);
uint8_t LM75_ReadConfReg(void);
uint8_t LM75_WriteConfReg(uint8_t RegValue);
uint8_t LM75_ShutDown(FunctionalState NewState);


 
#ifdef __cplusplus
}
#endif

#endif /* __STM320518_EVAL_I2C_TSENSOR_CPAL_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */

