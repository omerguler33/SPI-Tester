/**
  @page USART_WakeUpFromStop USART WakeUp from Stop mode Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    USART/USART_WakeUpFromStop/readme.txt 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    13-October-2021
  * @brief   Description of the USART WakeUp from Stop mode Example.
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

This example provides a description of how to use the WakeUp from STOP mode capability
of the USART via the hyperterminal.

First, the USART1(STM32F051R8T6 devices) or USART2(STM32F072VBT6 devices) is configured 
to WakeUp from STOP with StartBitMethod(when any data is received on RX line).
After configuration, the MCU enters STOP mode and waits to be waken.
When a string is sent to USART via the hyperterminal, the MCU WakeUp from stop,
restore the system clock configuration and configures the systick to toggle LED's.
The LED's toggling is used to indicate that the MCU is Waken Up from stop.

The USART is configured as follow:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits 
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled


@par Directory contents 

  - USART/USART_WakeUpFromStop/stm32f0xx_conf.h    Library Configuration file
  - USART/USART_WakeUpFromStop/stm32f0xx_it.c      Interrupt handlers
  - USART/USART_WakeUpFromStop/stm32f0xx_it.h      Interrupt handlers header file
  - USART/USART_WakeUpFromStop/main.c              Main program   
  - USART/USART_WakeUpFromStop/main.h              Main program header file 
  - USART/USART_WakeUpFromStop/system_stm32f0xx.c  STM32F0xx system source file
  
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
      - Connect a null-modem female/female RS232 cable between the DB9 connector 
        CN7 and PC serial port.
      - Make sure that JP3 is in position 5<->6  
      
  - STM32072B-EVAL Set-up  
      - Connect a null-modem female/female RS232 cable between the DB9 connector 
        CN10 and PC serial port.
      - Make sure that JP17 is in position 5<->6 

  - Hyperterminal configuration:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - flow control: None 


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
