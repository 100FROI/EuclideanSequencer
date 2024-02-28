/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ROTA_T2_Pin GPIO_PIN_13
#define ROTA_T2_GPIO_Port GPIOC
#define ROTA_T2_EXTI_IRQn EXTI15_10_IRQn
#define ROTB_T2_Pin GPIO_PIN_14
#define ROTB_T2_GPIO_Port GPIOC
#define SW_CVSEQ2_Pin GPIO_PIN_15
#define SW_CVSEQ2_GPIO_Port GPIOC
#define SW_CVSEQ2_EXTI_IRQn EXTI15_10_IRQn
#define RCLK_T3_Pin GPIO_PIN_0
#define RCLK_T3_GPIO_Port GPIOH
#define SRCLK_T3_Pin GPIO_PIN_1
#define SRCLK_T3_GPIO_Port GPIOH
#define RCLK_T2_Pin GPIO_PIN_0
#define RCLK_T2_GPIO_Port GPIOC
#define CV1_CVSEQ2_Pin GPIO_PIN_1
#define CV1_CVSEQ2_GPIO_Port GPIOC
#define SER_T3_Pin GPIO_PIN_3
#define SER_T3_GPIO_Port GPIOC
#define SRCLK_T2_Pin GPIO_PIN_0
#define SRCLK_T2_GPIO_Port GPIOA
#define SER_T2_Pin GPIO_PIN_1
#define SER_T2_GPIO_Port GPIOA
#define TEMPO_CVSEQ2_Pin GPIO_PIN_2
#define TEMPO_CVSEQ2_GPIO_Port GPIOA
#define TEMPO_CVSEQ2_EXTI_IRQn EXTI2_IRQn
#define TEMPO_CVSEQ1_Pin GPIO_PIN_3
#define TEMPO_CVSEQ1_GPIO_Port GPIOA
#define TEMPO_CVSEQ1_EXTI_IRQn EXTI3_IRQn
#define CVSEQ2_OUT_Pin GPIO_PIN_4
#define CVSEQ2_OUT_GPIO_Port GPIOA
#define CVSEQ1_OUT_Pin GPIO_PIN_5
#define CVSEQ1_OUT_GPIO_Port GPIOA
#define CV2_CVSEQ1_Pin GPIO_PIN_6
#define CV2_CVSEQ1_GPIO_Port GPIOA
#define CV1_CVSEQ1_Pin GPIO_PIN_7
#define CV1_CVSEQ1_GPIO_Port GPIOA
#define ROTA_T3_Pin GPIO_PIN_4
#define ROTA_T3_GPIO_Port GPIOC
#define ROTA_T3_EXTI_IRQn EXTI4_IRQn
#define ROTB_T1_Pin GPIO_PIN_5
#define ROTB_T1_GPIO_Port GPIOC
#define CV2_CVSEQ2_Pin GPIO_PIN_0
#define CV2_CVSEQ2_GPIO_Port GPIOB
#define ROTB_T3_Pin GPIO_PIN_1
#define ROTB_T3_GPIO_Port GPIOB
#define DISP_MODE_Pin GPIO_PIN_2
#define DISP_MODE_GPIO_Port GPIOB
#define CCLR_T1_Pin GPIO_PIN_10
#define CCLR_T1_GPIO_Port GPIOB
#define ROTB_BPM_Pin GPIO_PIN_11
#define ROTB_BPM_GPIO_Port GPIOB
#define ROTA_BPM_Pin GPIO_PIN_12
#define ROTA_BPM_GPIO_Port GPIOB
#define ROTA_BPM_EXTI_IRQn EXTI15_10_IRQn
#define SER_T1_Pin GPIO_PIN_13
#define SER_T1_GPIO_Port GPIOB
#define SRCLK_T1_Pin GPIO_PIN_14
#define SRCLK_T1_GPIO_Port GPIOB
#define RCLK_T1_Pin GPIO_PIN_15
#define RCLK_T1_GPIO_Port GPIOB
#define ROTA_T1_Pin GPIO_PIN_6
#define ROTA_T1_GPIO_Port GPIOC
#define ROTA_T1_EXTI_IRQn EXTI9_5_IRQn
#define TRIG_T1_Pin GPIO_PIN_8
#define TRIG_T1_GPIO_Port GPIOC
#define TRIG_BPM_Pin GPIO_PIN_9
#define TRIG_BPM_GPIO_Port GPIOC
#define CCLK_T1_Pin GPIO_PIN_8
#define CCLK_T1_GPIO_Port GPIOA
#define DISPLAY_CLR_Pin GPIO_PIN_9
#define DISPLAY_CLR_GPIO_Port GPIOA
#define CCLR_T3_Pin GPIO_PIN_10
#define CCLR_T3_GPIO_Port GPIOA
#define DISP_BPM_Pin GPIO_PIN_11
#define DISP_BPM_GPIO_Port GPIOA
#define SW_T123_Pin GPIO_PIN_10
#define SW_T123_GPIO_Port GPIOC
#define SW_T123_EXTI_IRQn EXTI15_10_IRQn
#define DISP_CVSEQ1_Pin GPIO_PIN_11
#define DISP_CVSEQ1_GPIO_Port GPIOC
#define DISP_CVSEQ2_Pin GPIO_PIN_2
#define DISP_CVSEQ2_GPIO_Port GPIOD
#define CCLK_T3_Pin GPIO_PIN_3
#define CCLK_T3_GPIO_Port GPIOB
#define CCLK_T2_Pin GPIO_PIN_4
#define CCLK_T2_GPIO_Port GPIOB
#define CCLR_T2_Pin GPIO_PIN_5
#define CCLR_T2_GPIO_Port GPIOB
#define SW_CVSEQ1_Pin GPIO_PIN_7
#define SW_CVSEQ1_GPIO_Port GPIOB
#define SW_CVSEQ1_EXTI_IRQn EXTI9_5_IRQn
#define TRIG_T3_Pin GPIO_PIN_8
#define TRIG_T3_GPIO_Port GPIOB
#define TRIG_T2_Pin GPIO_PIN_9
#define TRIG_T2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
