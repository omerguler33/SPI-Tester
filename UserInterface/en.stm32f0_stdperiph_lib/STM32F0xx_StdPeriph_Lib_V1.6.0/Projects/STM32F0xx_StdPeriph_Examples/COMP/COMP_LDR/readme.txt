/**
  @page COMP_LDR Comparator With LDR example.
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    COMP/COMP_LDR/readme.txt 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Description of Comparator With LDR example.
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

The STM32F0xx microcontroller has an embedded comparator which can be used
in combination with DAC peripheral for more application like the measure of light
intensity (using the LDR sensor).

In this example when the luminosity changes the progress bar displayed on the color
LCD changes according to light intensity level detected on comparator.


@par Directory contents 

  - COMP/COMP_LDR/stm32f0xx_conf.h    Library Configuration file
  - COMP/COMP_LDR/stm32f0xx_it.c      Interrupt handlers
  - COMP/COMP_LDR/stm32f0xx_it.h      Interrupt handlers header file
  - COMP/COMP_LDR/main.c              Main program
  - COMP/COMP_LDR/main.h              Main program  header file
  - COMP/COMP_LDR/system_stm32f0xx.c  STM32F0xx system source file
  
@note The "system_stm32f0xx.c" is generated by an automatic clock configuration 
      tool and can be easily customized to meet user application requirements. 
      To select different clock setup, use the "STM32F0xx_Clock_Configuration_VX.Y.Z.xls" 
      provided with the AN4055 package available on <a href="http://www.st.com/internet/mcu/class/1734.jsp">  ST Microcontrollers </a>

         
@par Hardware and Software environment

  - This example runs on STM32F0xx Devices.
  
  - This example has been tested with STMicroelectronics STM320518-EVAL and
    STM32072B-EVAL including respectively STM32F051R8T6 and STM32F072VBT6 devices
    and can be easily tailored to any other supported device and development board.

  - STM320518-EVAL Set-up
    - Make sure that jumper JP13 is not fitted to avoid noise from the speaker.
    
  - STM32072B-EVAL Set-up
    - Make sure that jumper JP18 is not fitted to avoid noise from the speaker.


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
