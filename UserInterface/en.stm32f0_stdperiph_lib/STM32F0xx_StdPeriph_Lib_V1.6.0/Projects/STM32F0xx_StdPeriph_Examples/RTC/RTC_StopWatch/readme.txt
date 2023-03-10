/**
  @page RTC_StopWatch RTC StopWatch example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    RTC/RTC_StopWatch/readme.txt 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Description of the RTC StopWatch example
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

  This example illustrates how to use the STM32F0xx new RTC's sub-seconds and
  Tamper feature (Filter, sampling) features. It simulates a precise chronometer
  with 2 record times possibilities stored in the Backup registers (2 registers
  for time (second, minutes and hours) and 2 registers for subsecond).
  
  For this example an interactive human interface is developed using
   LCD and Push Buttons to allow user to use StopWatch with real time display.

  After startup, a default 00:00:00:000 chronometer counter is displayed on the 
  LCD, it corresponds to [Hours]:[minutes]:[seconds]:[milliseconds].
  User can manipulate the chronometer features using Joystick LEFT, RIGHT and Tamper buttons:
    - press Joystick LEFT  button to start counter.
    - press Joystick RIGHT button to save trials in the backup registers (max 5 actions).
    - press and hold Tamper button for 1 sec to reset all the backup registers.
 

@par Directory contents 

  - RTC/RTC_StopWatch/stm32f0xx_conf.h    Library Configuration file
  - RTC/RTC_StopWatch/stm32f0xx_it.c      Interrupt handlers
  - RTC/RTC_StopWatch/stm32f0xx_it.h      Interrupt handlers header file
  - RTC/RTC_StopWatch/main.c              Main program
  - RTC/RTC_StopWatch/main.h              Main program header file
  - RTC/RTC_StopWatch/system_stm32f0xx.c  STM32F0xx system source file
  
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
    - Use Joystick LEFT and RIGHT button
    - Use Tamper button
    
  - STM32072B-EVAL Set-up
    - Use Joystick LEFT and RIGHT button
    - Use Tamper button

@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\STM32F0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is STM32F051R8T6 choose STM32F051 project
    - Add the following files to the project source list
      - Utilities/STM32_EVAL/STM320518_EVAL/stm320518_eval.c
      - Utilities/STM32_EVAL/STM320518_EVAL/stm320518_eval_lcd.c 
 - If the used device is STM32F072VBT6 choose STM32F072 project
    - Add the following files to the project source list
      - Utilities/STM32_EVAL/STM32072B_EVAL/stm32072b_eval.c
      - Utilities/STM32_EVAL/STM320518_EVAL/stm32072b_eval_lcd.c   
 - Rebuild all files and load your image into target memory
 - Run the example

 */
