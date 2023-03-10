/**
  @page COMP_AnalogWatchdog COMP Analog Watchdog example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    COMP/COMP_AnalogWatchdog/readme.txt  
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Description of the COMP Analog Watchdog Example.
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

This example shows how to make an analog watchdog using the STM32F0xx COMPs 
peripherals in window mode:
  - The upper threshold is set to VREFINT = 1.22V
  - The lower threshold is set to VREFINT / 4 = 1.22/4 = 0.305V
  - The input voltage is configured to be connected to PA.01 (On STM320518-EVAL 
    RV3 (PC.01) is used to simulate an input voltage)
  - The input voltage is configured to be connected to PA.01 (On STM32072B-EVAL 
    RV3 (PC.00) is used to simulate an input voltage)

If the input voltage is above the higher threshold, LD3 and LD1 are turned On.
If the input voltage is under the lower threshold, LD2 and LD4 are turned On.
If the input voltage is within the thresholds, the MCU remains in STOP mode

@par Directory contents 

  - COMP/COMP_AnalogWatchdog/stm32f0xx_conf.h    Library Configuration file
  - COMP/COMP_AnalogWatchdog/stm32f0xx_it.c      Interrupt handlers
  - COMP/COMP_AnalogWatchdog/stm32f0xx_it.h      Interrupt handlers header file
  - COMP/COMP_AnalogWatchdog/main.c              Main program
  - COMP/COMP_AnalogWatchdog/main.h              Main Header file
  - COMP/COMP_AnalogWatchdog/system_stm32f0xx.c  STM32F0xx system source file
  
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
    - Use LED1, LED2, LED3 and LED4 connected respectively to PC.10, PC.11 ,PC.12
      and PD.02 pins
      @note This example run in stand alone mode.
    - Use a wire to connect Potentiometer RV3 (PC.01 pin) to COMP2 non inverting input (PA.01)
    
  - STM32072B-EVAL Set-up
    - Use LED1, LED2, LED3 and LED4 connected respectively to PD.08, PD.09 ,PD.10
      and PD.11 pins
      @note This example run in stand alone mode.
    - Use a wire to connect Potentiometer RV3 (PC.00 pin) to COMP2 non inverting input (PA.01)


@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\STM32F0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is STM32F051R8T6 choose STM32F051 project
    - Add the following files to the project source list
       - Utilities\STM32_EVAL\STM320518_EVAL\stm320518_eval.c
 - If the used device is STM32F072VBT6 choose STM32F072 project
    - Add the following files to the project source list
       - Utilities\STM32_EVAL\STM32072B_EVAL\stm32072b_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example

 */
