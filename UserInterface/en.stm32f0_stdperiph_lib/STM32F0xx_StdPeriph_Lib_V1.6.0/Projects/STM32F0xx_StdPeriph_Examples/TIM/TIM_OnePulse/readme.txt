/**
  @page TIM_One_Pulse TIM One Pulse example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    TIM/TIM_OnePulse/readme.txt 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Description of the TIM One Pulse example.
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

This example shows how to use the TIM peripheral to generate a One pulse Mode 
after a Rising edge of an external signal is received in Timer Input pin.

TIM2CLK = SystemCoreClock, we want to get TIM2 counter clock at 24 MHz:
  - Prescaler = (TIM2CLK / TIM2 counter clock) - 1

SystemCoreClock is set to 48 MHz.

The Autoreload value is 65535 (TIM2->ARR), so the maximum frequency value to 
trigger the TIM2 input is 24000000/65535 = 366.2 Hz.

The TIM2 is configured as follows: 
The One Pulse mode is used, the external signal is connected to TIM2 CH2 pin (PA.01), 
the rising edge is used as active edge, the One Pulse signal is output 
on TIM2_CH1 (PA.05).

The TIM_Pulse defines the delay value, the delay value is fixed to:
delay =  CCR1/TIM2 counter clock = 16383 / 24000000 = 682.6 us. 
The (TIM_Period - TIM_Pulse) defines the One Pulse value, the pulse value is fixed to:
One Pulse value = (TIM_Period - TIM_Pulse)/TIM2 counter clock 
                = (65535 - 16383) / 24000000 = 2.04 ms.
 

@par Directory contents 

  - TIM/TIM_OnePulse/stm32f0xx_conf.h    Library Configuration file
  - TIM/TIM_OnePulse/stm32f0xx_it.c      Interrupt handlers
  - TIM/TIM_OnePulse/stm32f0xx_it.h      Interrupt handlers header file
  - TIM/TIM_OnePulse/main.c              Main program
  - TIM/TIM_OnePulse/main.h              Header for main.c module
  - TIM/TIM_OnePulse/system_stm32f0xx.c  STM32F0xx system source file
  
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
    - Connect the external signal to the TIM2_CH2 pin (PA.01)
    - Connect the TIM2_CH1 (PA.05) pin to an oscilloscope to monitor the waveform.
  - STM32072B-EVAL Set-up
    - Connect the external signal to the TIM2_CH2 pin (PA.01)
    - Connect the TIM2_CH1 (PA.05) pin to an oscilloscope to monitor the waveform.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\STM32F0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - Select the appropriate workspace 
 - Rebuild all files and load your image into target memory
 - Run the example

 */
