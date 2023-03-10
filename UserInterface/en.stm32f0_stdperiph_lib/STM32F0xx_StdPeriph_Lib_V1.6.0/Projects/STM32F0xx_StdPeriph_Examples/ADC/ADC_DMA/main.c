/**
  ******************************************************************************
  * @file    ADC/ADC_DMA/main.c 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Main program body
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
#include "main.h"

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_DMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MESSAGE1   "STM32F0xx CortexM0  " 
#ifdef USE_STM320518_EVAL
  #define MESSAGE2   "   STM320518-EVAL   "
  #define MESSAGE3   "  Turn RV3(PC.01)    "
#else 
  #define MESSAGE2   "   STM32072B-EVAL   " 
  #define MESSAGE3   "  Turn RV3(PC.00)    "
#endif /* USE_STM320518_EVAL */
#define ADC1_DR_Address    0x40012440

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
__IO uint16_t RegularConvData_Tab[4];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Display_Init(void);
static void Display(void);
static void ADC_Config(void);
static void DMA_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */ 

  /* LCD Display init  */
  Display_Init();
   
  /* ADC1 configuration */
  ADC_Config();
  
  /* DMA configuration */
  DMA_Config();

  /* Infinite loop */
  while (1)
  {
    /* Test DMA1 TC flag */
    while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET ); 
    
    /* Clear DMA TC flag */
    DMA_ClearFlag(DMA1_FLAG_TC1);
    
    /* Display converted data on the LCD */
    Display();
  }
}

/**
  * @brief  ADC1 channel configuration
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
  ADC_InitTypeDef     ADC_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
  
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
   /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* Configure ADC Channel11 and channel10 as analog input */
#ifdef USE_STM320518_EVAL
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
#else
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
#endif /* USE_STM320518_EVAL */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continuous mode withe a resolution equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;
  ADC_Init(ADC1, &ADC_InitStructure); 

  /* Convert the ADC1 Channel11 and channel10 with 55.5 Cycles as sampling time */ 
#ifdef USE_STM320518_EVAL
  ADC_ChannelConfig(ADC1, ADC_Channel_11 , ADC_SampleTime_55_5Cycles); 
#else
  ADC_ChannelConfig(ADC1, ADC_Channel_10 , ADC_SampleTime_55_5Cycles); 
#endif /* USE_STM320518_EVAL */  
  
  
  /* Convert the ADC1 temperature sensor  with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_TempSensor , ADC_SampleTime_55_5Cycles);  
  ADC_TempSensorCmd(ENABLE);
  
  /* Convert the ADC1 Vref  with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_Vrefint , ADC_SampleTime_55_5Cycles); 
  ADC_VrefintCmd(ENABLE);
  
  /* Convert the ADC1 Vbat with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_Vbat , ADC_SampleTime_55_5Cycles);  
  ADC_VbatCmd(ENABLE);
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* ADC DMA request in circular mode */
  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  
  /* Enable ADC_DMA */
  ADC_DMACmd(ADC1, ENABLE);  
  
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY flag */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}

/**
  * @brief  DMA channel1 configuration
  * @param  None
  * @retval None
  */
static void DMA_Config(void)
{
  DMA_InitTypeDef   DMA_InitStructure;
  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
  
  /* DMA1 Channel1 Config */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  /* DMA1 Channel1 enable */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
}

/**
  * @brief  Display ADC converted value on LCD
  * @param  None
  * @retval None
  */
static void Display(void)
{
  uint32_t v=0,mv=0;
  uint8_t text[50],index;
  
  /* Set the LCD Back Color and Text Color*/
  LCD_SetBackColor(White);
  LCD_SetTextColor(Green);
  for(index=0;index<4;index++)
  {
    if (index == 0)
    {
      v=((2* RegularConvData_Tab[index]* 3300) / 0xFFF) / 1000;
      mv = (((2* RegularConvData_Tab[index]* 3300) / 0xFFF)%1000)/100;
    }
    else
    {
      v=((RegularConvData_Tab[index]* 3300) / 0xFFF) / 1000;
      mv = (((RegularConvData_Tab[index]* 3300) / 0xFFF)%1000)/100;
    } 
    
    if (index == 3)
    {
      sprintf((char*)text," Pot (RV3)   = %d,%d V   ",v,mv);
    }
    else if (index == 2)
    {
      sprintf((char*)text," V(sense)    = %d,%d V   ",v,mv);
    }
     else if (index == 1)
    {
      sprintf((char*)text," V(ref int)  = %d,%d V   ",v,mv);
    }
     else
    {
      sprintf((char*)text," V(Battery)  = %d,%d V",v,mv);
    }
    
    LCD_DisplayStringLine(LINE(5+index),text);
  } 
}

/**
  * @brief  Display Init (LCD)
  * @param  None
  * @retval None
  */
static void Display_Init(void)
{
  /* Initialize the LCD */
#ifdef USE_STM320518_EVAL
  STM320518_LCD_Init();
#else
  STM32072B_LCD_Init();
#endif /* USE_STM320518_EVAL */

  /* Clear the LCD */ 
  LCD_Clear(White);

  /* Set the LCD Text size */
  LCD_SetFont(&Font8x12);

  /* Set the LCD Back Color and Text Color*/
  LCD_SetBackColor(Blue);
  LCD_SetTextColor(White);

  /* Display */
  LCD_DisplayStringLine(LINE(0x13), "         ADC DMA conversion example         ");

  /* Set the LCD Text size */
  LCD_SetFont(&Font16x24);

  LCD_DisplayStringLine(LINE(0), MESSAGE1);
  LCD_DisplayStringLine(LINE(1), MESSAGE2);
  
  /* Set the LCD Back Color and Text Color*/
  LCD_SetBackColor(White);
  LCD_SetTextColor(Blue);

  /* Display */
  LCD_DisplayStringLine(LINE(3), MESSAGE3);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

