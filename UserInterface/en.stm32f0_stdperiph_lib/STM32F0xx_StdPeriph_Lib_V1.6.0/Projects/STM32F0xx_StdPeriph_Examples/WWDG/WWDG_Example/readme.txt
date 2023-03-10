/**
  @page WWDG_Example  WWDG Example decription
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    WWDG/WWDG_Example/readme.txt 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Description of the WWDG Example
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

@par  Example Description 

This example shows how to update at regular period the WWDG counter and how to
simulate a software fault generating an MCU WWDG reset on expiry of a programmed 
time period.

The WWDG timeout is set to 43.7 ms and the refresh window is set to 80. 
The WWDG counter is refreshed each 33 ms in the main program infinite loop to 
prevent a WWDG reset.
LED2 is also toggled each 33 ms indicating that the program is running.

An EXTI Line is connected to a GPIO pin, and configured to generate an interrupt
on the rising edge of the signal.

The EXTI Line is used to simulate a software failure: once the EXTI Line event 
occurs, by pressing the Tamper push-button, the corresponding interrupt is served.
In the ISR, a write to invalid address generates a Hardfault exception containing
an infinite loop and preventing to return to main program (the WWDG counter is 
not refreshed).
As a result, when the WWDG counter falls to 63, the WWDG reset occurs.
If the WWDG reset is generated, after the system resumes from reset, LED1 turns on.

If the EXTI Line event does not occur, the WWDG counter is indefinitely refreshed
in the main program infinite loop, and there is no WWDG reset. 


@par Directory contents 

  - WWDG/WWDG_Example/stm32f0xx_conf.h     Library Configuration file
  - WWDG/WWDG_Example/stm32f0xx_it.c       Interrupt handlers
  - WWDG/WWDG_Example/stm32f0xx_it.h       Interrupt handlers header file
  - WWDG/WWDG_Example/main.c               Main program 
  - WWDG/WWDG_Example/main.h               Header file for Main program
  - WWDG/WWDG_Example/system_stm32f0xx.c   STM32F0xx system source file

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
    - Use the Tamper push-button connected to PC13 pin  
    
  - STM32072B-EVAL Set-up  
    - Use the Tamper push-button connected to PC13 pin


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
