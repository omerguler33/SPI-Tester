/**
  ******************************************************************************
  * @file    stm32f0xx_ip_dbg.c 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   This file provides all STM32F0xx peripherals pointers initialization.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_ip_dbg.h"

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup Lib_DEBUG_Example
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
NVIC_Type * NVIC_DBG;
SCB_Type * SCB_DBG;
SysTick_Type * SysTick_DBG;
ADC_TypeDef * ADC1_DBG;
ADC_Common_TypeDef * ADC_DBG;
CEC_TypeDef * CEC_DBG;
CRC_TypeDef * CRC_DBG;
COMP_TypeDef * COMP_DBG;
DAC_TypeDef * DAC_DBG;
DBGMCU_TypeDef * DBGMCU_DBG;
DMA_TypeDef * DMA1_DBG;
DMA_Channel_TypeDef * DMA1_Channel1_DBG;
DMA_Channel_TypeDef * DMA1_Channel2_DBG;
DMA_Channel_TypeDef * DMA1_Channel3_DBG;
DMA_Channel_TypeDef * DMA1_Channel4_DBG;
DMA_Channel_TypeDef * DMA1_Channel5_DBG;
EXTI_TypeDef * EXTI_DBG;
FLASH_TypeDef * FLASH_DBG;
OB_TypeDef * OB_DBG; 
GPIO_TypeDef * GPIOA_DBG;
GPIO_TypeDef * GPIOB_DBG;
GPIO_TypeDef * GPIOC_DBG;
GPIO_TypeDef * GPIOD_DBG;
GPIO_TypeDef * GPIOF_DBG;
I2C_TypeDef * I2C1_DBG;
I2C_TypeDef * I2C2_DBG;
IWDG_TypeDef * IWDG_DBG;
PWR_TypeDef * PWR_DBG;
RCC_TypeDef * RCC_DBG;
RTC_TypeDef * RTC_DBG;
SPI_TypeDef * SPI1_DBG;
SPI_TypeDef * SPI2_DBG;
SYSCFG_TypeDef * SYSCFG_DBG;
TIM_TypeDef * TIM1_DBG;
TIM_TypeDef * TIM2_DBG;
TIM_TypeDef * TIM3_DBG;
TIM_TypeDef * TIM6_DBG;
TIM_TypeDef * TIM14_DBG;
TIM_TypeDef * TIM15_DBG;
TIM_TypeDef * TIM16_DBG;
TIM_TypeDef * TIM17_DBG;
USART_TypeDef * USART1_DBG;
USART_TypeDef * USART2_DBG;
WWDG_TypeDef * WWDG_DBG; 

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function initialize peripherals pointers.
  * @param  None
  * @retval None
  */
void IP_Debug(void)
{
/*************************************CORE CM0 ********************************/
  NVIC_DBG  = (NVIC_Type *)  NVIC_BASE;
  SCB_DBG = (SCB_Type *)  SCB_BASE;
  SysTick_DBG = (SysTick_Type *)  SysTick_BASE;
  
/************************************* ADC ************************************/
  ADC_DBG  = (ADC_Common_TypeDef *)  ADC_BASE;
  ADC1_DBG = (ADC_TypeDef *)  ADC1_BASE;

/************************************* CEC ************************************/
  CEC_DBG  = (CEC_TypeDef *)  CEC_BASE;
   
/************************************* CRC ************************************/  
  CRC_DBG = (CRC_TypeDef *)  CRC_BASE;

/************************************* COMP ***********************************/  
  COMP_DBG = (COMP_TypeDef *)  COMP_BASE;
  
/************************************* DAC ************************************/
  DAC_DBG = (DAC_TypeDef *)  DAC_BASE;

/************************************* DBGMCU *********************************/
  DBGMCU_DBG = (DBGMCU_TypeDef *)  DBGMCU_BASE;

/************************************* DMA ************************************/
  DMA1_DBG = (DMA_TypeDef *) DMA1_BASE;
  DMA1_Channel1_DBG = (DMA_Channel_TypeDef *) DMA1_Channel1_BASE;
  DMA1_Channel2_DBG = (DMA_Channel_TypeDef *) DMA1_Channel2_BASE;
  DMA1_Channel3_DBG = (DMA_Channel_TypeDef *) DMA1_Channel3_BASE;
  DMA1_Channel4_DBG = (DMA_Channel_TypeDef *) DMA1_Channel4_BASE;
  DMA1_Channel5_DBG = (DMA_Channel_TypeDef *) DMA1_Channel5_BASE;
  
/************************************* EXTI ***********************************/
  EXTI_DBG = (EXTI_TypeDef *)  EXTI_BASE;
 
/************************************* FLASH **********************************/
  FLASH_DBG = (FLASH_TypeDef *)  FLASH_R_BASE;
  OB_DBG = (OB_TypeDef *)  OB_BASE;
      
/************************************* GPIO ***********************************/
  GPIOA_DBG = (GPIO_TypeDef *)  GPIOA_BASE;
  GPIOB_DBG = (GPIO_TypeDef *)  GPIOB_BASE;
  GPIOC_DBG = (GPIO_TypeDef *)  GPIOC_BASE;
  GPIOD_DBG = (GPIO_TypeDef *)  GPIOD_BASE;
  GPIOF_DBG = (GPIO_TypeDef *)  GPIOF_BASE;
  
/************************************* I2C ************************************/
  I2C1_DBG = (I2C_TypeDef *)  I2C1_BASE;
  I2C2_DBG = (I2C_TypeDef *)  I2C2_BASE;

/************************************* IWDG ***********************************/
  IWDG_DBG = (IWDG_TypeDef *)  IWDG_BASE;
   
/************************************* PWR ************************************/
  PWR_DBG = (PWR_TypeDef *)  PWR_BASE;

/************************************* RCC ************************************/
  RCC_DBG = (RCC_TypeDef *)  RCC_BASE;
  
/************************************* RTC ************************************/
  RTC_DBG = (RTC_TypeDef *)  RTC_BASE;
   
/************************************* SPI ************************************/
  SPI1_DBG = (SPI_TypeDef *)  SPI1_BASE;
  SPI2_DBG = (SPI_TypeDef *)  SPI2_BASE;

/************************************* SYSCFG *********************************/
  SYSCFG_DBG = (SYSCFG_TypeDef *)  SYSCFG_BASE;

/************************************* TIM ************************************/
  TIM1_DBG  = (TIM_TypeDef *)  TIM1_BASE;
  TIM2_DBG  = (TIM_TypeDef *)  TIM2_BASE;
  TIM3_DBG  = (TIM_TypeDef *)  TIM3_BASE;
  TIM6_DBG  = (TIM_TypeDef *)  TIM6_BASE;
  TIM14_DBG  = (TIM_TypeDef *)  TIM14_BASE;
  TIM15_DBG = (TIM_TypeDef *)  TIM15_BASE;
  TIM16_DBG = (TIM_TypeDef *)  TIM16_BASE;
  TIM17_DBG = (TIM_TypeDef *)  TIM17_BASE;  

/************************************* USART **********************************/
  USART1_DBG = (USART_TypeDef *)  USART1_BASE;
  USART2_DBG = (USART_TypeDef *)  USART2_BASE;
  
/************************************* WWDG************************************/
  WWDG_DBG = (WWDG_TypeDef *)  WWDG_BASE;
}

/**
  * @}
  */

/**
  * @}
  */
  
