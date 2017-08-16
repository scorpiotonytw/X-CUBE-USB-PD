/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    24-Apr-2017
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
#include "usbpd_cad.h"
#include "usbpd_prl.h"
/** @addtogroup STM32F0xx_HAL_Examples
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}



/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
#ifndef DBG_STUSB1602
  if (uxTaskGetNumberOfTasks() != 0)
  {
    osSystickHandler();
  }

  //USBPD_CAD_TimerCounter(0);
  USBPD_PE_TimerCounter(0);
  USBPD_PRL_TimerCounter(0);
#if (USBPD_PORT_COUNT == 2)
  //USBPD_CAD_TimerCounter(1);
  USBPD_PE_TimerCounter(1);
  USBPD_PRL_TimerCounter(1);
#endif //USBPD_PORT_COUNT == 2
#endif //DBG_STUSB1602
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

#ifdef MB1303

/**
  * @brief  This function handles EXTI line 4_15 interrupts.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(ALERT_GPIO_PIN(0));
}

/**
  * @brief  This function handles EXTI line 2 to 3 interrupts.
  * @param  None
  * @retval None
  */
void EXTI2_3_IRQHandler(void)
{  
  HAL_GPIO_EXTI_IRQHandler(ALERT_GPIO_PIN(1));
  
}

#endif

/**
  * @brief  This function handles EXTI line 4_15 interrupts.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_PIN);
  
#ifndef MB1303
  HAL_GPIO_EXTI_IRQHandler(ALERT_GPIO_PIN(0));
#endif
  
  HAL_GPIO_EXTI_IRQHandler(SPI_NSS_PIN(0));
  
  HAL_GPIO_EXTI_IRQHandler(SPI_NSS_PIN(1));

}


#if defined (MB1303) && (USBPD_PORT_COUNT == 2)

/**
  * @brief  This function handles DMA Channel 2 and 3 interrupts.
  * @param  None
  * @retval None
  */
void DMA1_Channel2_3_IRQHandler(void)
{
  USBPD_DMA_PORT1_IRQHandler();
}
#endif

/**
  * @brief  This function handles DMA Channel 4 to 7 interrupts.
  * @param  None
  * @retval None
  */
void DMA1_Channel4_5_6_7_IRQHandler(void)
{
  USBPD_DMA_PORT0_IRQHandler();
}

/**
  * @brief  This function handles TIM1 CC interrupt..
  * @param  None
  * @retval None
  */
//void TIM1_CC_IRQHandler(void)
//{
//  USBPD_RX_PORT1_Interrupt_IRQHandler();
//}

/**
  * @brief  This function handles TIM3 interrupt.
  * @param  None
  * @retval None
  */
//void TIM3_IRQHandler(void)
//{
//  USBPD_RX_PORT0_Interrupt_IRQHandler();
//}

/**
  * @brief  This function handles TIM6 interrupt.
  * @param  None
  * @retval None
  */
void TIM16_IRQHandler(void)
{
  USBPD_RX_PORT0_COUNTTIM_IRQHandler();
}

#if defined (MB1303) && (USBPD_PORT_COUNT == 2)
/**
  * @brief  This function handles TIM7 interrupt.
  * @param  None
  * @retval None
  */
void TIM17_IRQHandler(void)
{
  USBPD_RX_PORT1_COUNTTIM_IRQHandler();
}
#endif

///**
//  * @brief  This function handles TIM2 interrupt.
//  * @param  None
//  * @retval None
//  */
//void TIM2_IRQHandler(void)
//{
//  USBPD_PE_PRL_TIMER_IRQHandler();
//}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/