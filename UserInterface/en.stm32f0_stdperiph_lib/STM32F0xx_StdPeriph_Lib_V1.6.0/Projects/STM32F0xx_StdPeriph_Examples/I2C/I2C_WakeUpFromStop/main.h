/**
  ******************************************************************************
  * @file    I2C/I2C_WakeUpFromStop/main.h 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Header for main.c module
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
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_i2c_cpal.h"
#ifdef USE_STM320518_EVAL
  #include "stm320518_eval.h"
  #include "stm320518_eval_lcd.h"
#else 
  #include "stm32072b_eval.h"
  #include "stm32072b_eval_lcd.h"
#endif /* USE_STM320518_EVAL */


/* Exported types ------------------------------------------------------------*/
typedef enum {FAILED = 1, PASSED = !FAILED} TestStatus;

/* Exported constants --------------------------------------------------------*/

/* Uncomment the line below if you will use the I2C peripheral as a Master*/
#define I2C_MASTER  
/* Uncomment the line below if you will use the I2C peripheral as a Slave*/
//#define I2C_SLAVE

/* Configure I2C TIMING by defining the value of TIMINGR Register */
#define MASTER_I2C_TIMING                      0x10420F13
#define SLAVE_I2C_TIMING                       0x10420F13

/* Define the used Devices */
#define MASTERSTRUCTURE           I2C1_DevStructure  
#define SLAVESTRUCTURE            I2C1_DevStructure

/* Configure the OA1 address of the slave device */
#define OWNADDRESS                      ((uint8_t)0xCD)


#define BUFFSIZE                       (countof(BufferTX)-1)

#define MEASSAGE_EMPTY                  (uint8_t*)"                    "
#define MESSAGE1                        (uint8_t*)"---STM32 CPAL Lib---"
#define MESSAGE2                        (uint8_t*)"I2C WakeUp From Stop"
#define MESSAGE3                        (uint8_t*)"-------READY--------"
#define MESSAGE4                        (uint8_t*)" Press SEL to start "
#define MESSAGE5                        (uint8_t*)"       Tansfer      "
#define MESSAGE6                        (uint8_t*)" Transfer Complete  "
#define MESSAGE7                        (uint8_t*)" Entering Stop Mode "
#define MESSAGE8                        (uint8_t*)" Device in Stop Mode"  
#define MESSAGE9                        (uint8_t*)"  WakeUp From Stop  "
#define MESSAGE10                       (uint8_t*)" Slave Not yet Ready"
#define MESSAGE11                       (uint8_t*)"   Error occurred   "
#define MESSAGE12                       (uint8_t*)"  Timeout occurred  "

/* Exported macro ------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#endif /* __MAIN_H */

