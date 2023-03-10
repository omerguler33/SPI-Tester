/**
  @page TIM_ADC_Trigger TIM ADC Trigger Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    TIM/TIM_ADCTrigger/readme.txt 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   TIM ADC Trigger Example Description
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
   @endverbatim

@par Example Description 

This example describes how to configure the TIM to trigger the ADC conversion.

In this example the TIM1 is configured in PWM mode, the TIM1 CC4 event is used
to trigger the ADC.

The ADC is configured to convert continuously the ADC_Channel_11 (connected to
potentiometer RV3 on the STM320518-EVAL Board) or ADC_Channel_10 (connected to
potentiometer RV3 on the STM32072B-EVAL Board).
Each time the TIM1 CC4 event occurs, the ADC convert the variable voltage. 
 
User can display continuously the ADC_Channel_11 or ADC_Channel_10 voltage on 
the EVAL Board LCD 


@par Directory contents 

  - TIM/TIM_ADCTrigger/stm32f0xx_conf.h    Library Configuration file
  - TIM/TIM_ADCTrigger/stm32f0xx_it.c      Interrupt handlers
  - TIM/TIM_ADCTrigger/stm32f0xx_it.h      Interrupt handlers header file
  - TIM/TIM_ADCTrigger/main.c              Main program
  - TIM/TIM_ADCTrigger/main.h              Header for main.c module
  - TIM/TIM_ADCTrigger/system_stm32f0xx.c  STM32F0xx system source file
  
@note The "system_stm32f0xx.c" is generated by an automatic clock configuration 
      tool and can be easily customized to meet user application requirements. 
      To select different clock setup, use the "STM32F0xx_Clock_Configuration_VX.Y.Z.xls" 
      provided with the AN4055 package available on <a href="http://www.st.com/internet/mcu/class/1734.jsp">  ST Microcontrollers </a>

         
@par Hardware and Software environment

  - This example runs on STM32F0xx devices.
  
  - This example has been tested with STMicroelectronics STM320518-EVAL and
    STM32072B-EVAL including respectively STM32F051R8T6 and STM32F072VBT6 devices
    and can be easily tailored to any other supported device and development board

 - STM320518-EVAL Set-up
    - Use the potentiometer RV3 to change the ADC_Channel_11 voltage.
    
 - STM32072B-EVAL Set-up
    - Use the potentiometer RV3 to change the ADC_Channel_10 voltage.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\STM32F0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is STM32F051R8T6 choose STM32F051 project
    - Add the following files to the project source list
       - Utilities\STM32_EVAL\STM320518_EVAL\stm320518_eval.c
       - Utilities\STM32_EVAL\STM320518_EVAL\stm320518_eval_lcd.c
 - If the used device is STM32F072VBT6 choose STM32F072 project
    - Add the following files to the project source list
       - Utilities\STM32_EVAL\STM32072B_EVAL\stm32072b_eval.c
       - Utilities\STM32_EVAL\STM32072B_EVAL\stm32072b_eval_lcd.c 
 - Rebuild all files and load your image into target memory
 - Run the example

 */
