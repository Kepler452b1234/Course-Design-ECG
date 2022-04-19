/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
float pwmVal=0.36;		//定义占空比
__IO uint32_t TIM2_TIMEOUT_COUNT = 0;			///< 定时器2定时溢出计数
uint32_t TIM2_CAPTURE_BUF[3]   = {0, 0, 0};		///< 分别存储上升沿计数、下降沿计数、下个上升沿计数
__IO uint8_t TIM2_CAPTURE_STA = 0;			///< 状态标记


/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 8;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}
/* TIM3 init function */
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 499;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);		//新增
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal*500);
  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PA2     ------> TIM2_CH3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspPostInit 0 */

  /* USER CODE END TIM3_MspPostInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PB1     ------> TIM3_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM3_MspPostInit 1 */

  /* USER CODE END TIM3_MspPostInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /**TIM2 GPIO Configuration
    PA2     ------> TIM2_CH3
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void Sampling_time(int num)
{
	HAL_TIM_Base_Stop(&htim3);
	__HAL_TIM_SET_AUTORELOAD(&htim3,4*2*1000000/num-1); 
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal*(4*2*1000/num-1)+0.5); 
	HAL_TIM_Base_Start(&htim3);
}

/**
 * 设置TIM2输入捕获极性
 * @param TIM_ICPolarity：
 *        TIM_INPUTCHANNELPOLARITY_RISING  ：上升沿捕获
 *        TIM_INPUTCHANNELPOLARITY_FALLING ：下降沿捕获
 *        TIM_INPUTCHANNELPOLARITY_BOTHEDGE：上升沿和下降沿都捕获
 */
void TIM2_SetCapturePolarity(uint32_t TIM_ICPolarity)
{
    htim2.Instance->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
    htim2.Instance->CCER |= (TIM_ICPolarity & (TIM_CCER_CC1P | TIM_CCER_CC1NP));
}

/// 定时器2时间溢出回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim2.Instance)
    {
        TIM2_TIMEOUT_COUNT++;										// 溢出次数计数
    }
}

///< 输入捕获回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim2.Instance)
    {
        switch (TIM2_CAPTURE_STA)
        {
        case 1:
        {
            //printf("准备捕获下降沿...\r\n");
            TIM2_CAPTURE_BUF[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3) + TIM2_TIMEOUT_COUNT * 0xFFFF;
            TIM2_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_FALLING);					// 设置为下降沿触发
            TIM2_CAPTURE_STA++;
            break;
        }
        case 2:
        {
           // printf("准备捕获下个上升沿...\r\n");
            TIM2_CAPTURE_BUF[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3) + TIM2_TIMEOUT_COUNT * 0xFFFF;
            TIM2_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_RISING);					// 设置为上升沿触发
            TIM2_CAPTURE_STA++;
            break;
        }
        case 3:
        {
            //printf("捕获结束...\r\n");
            //printf("# end ----------------------------------------------------\r\n");
            TIM2_CAPTURE_BUF[2] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3) + TIM2_TIMEOUT_COUNT * 0xFFFF;
            HAL_TIM_IC_Stop_IT(htim, TIM_CHANNEL_3);									// 停止捕获
            HAL_TIM_Base_Stop_IT(&htim2);												// 停止定时器更新中断
            TIM2_CAPTURE_STA++;
            break;
        }
        default:
            break;
        }
    }
}

///< TIM2轮训状态切换
float TIM2_Poll(void)
{
	 
    switch (TIM2_CAPTURE_STA)
    {
    case 0:
    {
        //printf("# start ----------------------------------------------------\r\n");
       // printf("准备捕获上升沿...\r\n");
        TIM2_TIMEOUT_COUNT = 0;
        __HAL_TIM_SET_COUNTER(&htim2, 0);											// 清除定时器2现有计数
        memset(TIM2_CAPTURE_BUF, 0, sizeof(TIM2_CAPTURE_BUF));						// 清除捕获计数
        TIM2_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_RISING);					// 设置为上升沿触发
        HAL_TIM_Base_Start_IT(&htim2);												// 启动定时器更新中断
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);									// 启动捕获中断
        TIM2_CAPTURE_STA++;
        break;
    }

    case 4:
    {
			  float frq;
        uint32_t high  = TIM2_CAPTURE_BUF[1] - TIM2_CAPTURE_BUF[0];
        uint32_t cycle = TIM2_CAPTURE_BUF[2] - TIM2_CAPTURE_BUF[0];
        frq = 1.0 / (((float)cycle) / 2000000.0);
        TIM2_CAPTURE_STA++;

        //printf("\r\n\r\n");
       // printf("################################# START #########################################\r\n");
       // printf("高电平持续时间：%dms\r\n", high / 1000);
        //printf("周期          ：%dms\r\n", cycle / 1000);
       // printf("频率          ：%fHz\r\n", frq);
			  TIM2_CAPTURE_STA = 0;
       // printf("################################## END ##########################################\r\n\r\n");
        return frq;
			break;
    }

    default:
        break;
    }
		
}















/* USER CODE END 1 */
