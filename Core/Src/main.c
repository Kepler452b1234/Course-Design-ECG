/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "bspOled.h"
#include "draw_api.h"
#include "user_interface.h"
#include "user_calculate.h"
#include "valuepack.h"
#include "key.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint16_t ADC_ConvertedValue[NPT];
uint8_t adc_dma_ok=0;



extern float frq;
extern __IO uint8_t TIM2_CAPTURE_STA;
float ADC_Value[NPT];
float ADC_Value_Buffer[NPT];
unsigned char Send_Buffer[50];

float ECGData1[NPT]={2.77, 2.76, 2.91, 2.82, 2.87, 2.94, 2.83, 2.92, 2.82, 2.77, 2.81, 2.63, 2.7, 2.61, 2.46, 2.46, 2.3, 2.42, 2.38, 2.2, 2.3, 2.21, 2.32, 2.34, 2.17, 2.3, 2.23, 2.25, 2.34, 2.17, 2.28, 2.24, 2.17, 2.32, 2.14, 2.23, 2.19, 2.08, 2.21, 2.07, 2.1, 2.1, 1.97, 2.08, 2.01, 2.02, 2.08, 1.95, 2.12, 2.07, 2.04, 2.15, 2.04, 2.26, 2.19, 2.04, 2.08, 1.93, 2.04, 2.03, 1.93, 2.01, 1.9, 2.2, 2.76, 3.05, 3.25, 2.51, 1.9, 1.8, 1.75, 1.92, 1.92, 1.88, 2.02, 1.88, 2.01, 2.03, 2.01, 2.16, 2.08, 2.17, 2.19, 2.1, 2.25, 2.16, 2.21, 2.29, 2.17, 2.34, 2.32, 2.36, 2.47, 2.37, 2.51, 2.54, 2.46, 2.56, 2.41, 2.5, 2.47, 2.28, 2.32, 2.14, 2.2, 2.26, 2.11, 2.17, 2.08, 2.1, 2.16, 2.07, 2.19, 2.14, 2.11, 2.15, 2.07, 2.16, 2.12, 2.08, 2.14, 2.21, 2.14, 2.26, 2.26, 2.14, 2.25, 2.17, 2.21, 2.26, 2.14, 2.28, 2.21, 2.21, 2.26, 2.14, 2.25, 2.25, 2.19, 2.26, 2.14, 2.25, 2.24, 2.2, 2.32, 2.24, 2.36, 2.5, 2.43, 2.5, 2.34, 2.39, 2.46, 2.34, 2.38, 2.36, 2.7, 3.53, 3.58, 3.68, 2.81, 2.33, 2.38, 2.37, 2.51, 2.55, 2.46, 2.58, 2.47, 2.59, 2.63, 2.51, 2.61, 2.54, 2.6, 2.68, 2.55, 2.69, 2.68, 2.7, 2.85, 2.73, 2.89, 2.89, 2.9, 3.05, 2.92, 3.07, 3.08, 3.05, 3.22, 3.02, 2.98, 2.91, 2.7, 2.82, 2.68, 2.63, 2.69, 2.55, 2.69, 2.65, 2.6, 2.7, 2.59, 2.73, 2.74, 2.67, 2.76, 2.63, 2.65, 2.69, 2.56, 2.65, 2.54, 2.6, 2.68, 2.55, 2.65, 2.58, 2.55, 2.68, 2.52, 2.63, 2.58, 2.52, 2.65, 2.51, 2.6, 2.56, 2.47, 2.7, 2.7, 2.74, 2.83, 2.65, 2.73, 2.68, 2.65, 2.7, 2.51, 2.61, 2.81, 3.31, 3.88, 3.86, 3.31, 2.8, 2.63, 2.8, 2.7, 2.82, 2.86, 2.74, 2.87, 2.78};
float ECGData2[NPT]={2.85, 1.66, 1.81, 1.68, 1.73, 1.8, 1.68, 1.84, 1.72, 1.73, 1.8, 1.72, 1.88, 1.86, 1.85, 1.97, 1.86, 2.01, 2.01, 1.94, 2.14, 2.01, 2.21, 1.94, 1.75, 1.81, 1.62, 1.63, 1.63, 1.46, 1.59, 1.54, 1.55, 1.62, 1.49, 1.62, 1.58, 1.59, 1.68, 1.55, 1.63, 1.66, 1.59, 1.72, 1.59, 1.67, 1.63, 1.53, 1.67, 1.55, 1.59, 1.64, 1.54, 1.72, 1.68, 1.67, 1.77, 1.64, 1.79, 1.75, 1.71, 1.84, 1.76, 1.94, 1.92, 1.75, 1.82, 1.66, 1.8, 1.81, 1.68, 1.75, 1.75, 2.21, 2.87, 3.07, 2.95, 2.1, 1.82, 1.94, 1.89, 2.02, 2.03, 1.97, 2.15, 2.02, 2.12, 2.19, 2.11, 2.32, 2.21, 2.32, 2.39, 2.3, 2.48, 2.47, 2.55, 2.64, 2.52, 2.7, 2.96, 2.77, 2.94, 2.82, 2.94, 2.99, 2.9, 2.98, 2.81, 2.81, 2.8, 2.59, 2.65, 2.51, 2.5, 2.59, 2.46, 2.55, 2.47, 2.5, 2.55, 2.68, 2.54, 2.67, 2.63, 2.59, 2.68, 2.6, 2.67, 2.69, 2.61, 2.73, 2.64, 2.69, 2.72, 2.63, 2.74, 2.68, 2.73, 2.82, 2.65, 2.77, 2.77, 2.78, 2.86, 2.74, 2.87, 2.91, 2.86, 3.03, 2.92, 2.94, 2.91, 2.86, 2.96, 2.85, 2.92, 2.91, 2.82, 3.13, 3.64, 4.13, 4.27, 3.55, 3.11, 2.91, 2.99, 3.13, 3.02, 3.2, 3.2, 3.14, 3.3, 3.17, 3.34, 3.36, 3.27, 3.4, 3.6, 3.48, 3.55, 3.4, 3.53, 3.47, 3.53, 3.61, 3.51, 3.66, 3.66, 3.65, 3.74, 3.64, 3.74, 3.66, 3.58, 3.68, 3.44, 3.42, 3.36, 3.18, 3.3, 3.17, 3.18, 3.2, 3.12, 3.29, 3.18, 3.16, 3.22, 3.07, 3.21, 3.18, 3.09, 3.18, 3.07, 3.17, 3.13, 3.04, 3.12, 2.99, 3.07, 3.16, 3.0, 3.13, 3.04, 3.04, 3.2, 3.04, 3.13, 3.08, 3.11, 3.2, 2.99, 3.07, 3.0, 2.9, 3.04, 2.9, 2.94, 3.03, 3.33, 4.05, 4.17, 3.93, 3.2, 2.8, 3.02, 3.09, 3.05, 3.09, 2.95, 3.04, 2.94, 2.89, 2.95};

	
	
	//struct ECGdata_InitTypeDef ECGdata[5] = {
////    {.second = 3.141590,
////    .third = "method three",
////    .first = -10,
////    .four = 0.25},
////		
//		
//};
	
	

struct ECGdata_InitTypeDef ECGdata_realtime[5];
struct ECGdata_InitTypeDef ECGdata_saved[5];	
struct ECGdata_InitTypeDef ECGdata_exhibit[1];	
	
/****************标志位**************/

//按键标志位
uint8_t key1_state = 0;	//按键1的状态
uint8_t key2_state = 0;	//按键2的状态
uint8_t key3_state = 0;	//按键3的状态
uint8_t key4_state = 0;	//按键4的状态
	
	
//按下Key1发送保存的数据
//按下Key2更新保存到结构体的数据

//数据标志位
uint8_t ecgdataflag_realtime = 0;
uint8_t ecgdataflag_saved = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void main_task(void);
void ADC_Start(void);
void ADC_Stop(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
  Wave_Background();
  Sampling_time(Fs);//单位（HZ）	初始化ADC采样率
	ADC_Start();//初始化ADC开始采样
	
	
	
	

extern float fre;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//查询按键状态
		 GetKeyFlag();
		
		 main_task();
	  
	
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void main_task(void)
{
				
	static int i;
	
	/**********FFT处理以及显示方式等处理************************************/
   if(adc_dma_ok==1)
	 {
		 
		//ADC开始采样
  	ADC_Start();
		 
		//开始计算踩到的电压值，并将波形显示到OLED上
		AD_calcuate(ADC_Value,ADC_ConvertedValue,NPT);//计算采集到的电压值给OLED显示
	  for(i=0;i<NPT;i++)
	   {
		     ECGdata_realtime[ecgdataflag_realtime].EGC_ADCVaule[i]=ADC_Value[i];
				 
	   }
		 
		 
		for(i=0;i<NPT;i++)
	  {
			 if(ecgdataflag_saved>=5)
			 {
				 printf("ecgdataflag_saved:%d\n",ecgdataflag_saved);
				 printf("数据更新结束\n");
				 break;
			 }else {
				 
			 ECGdata_saved[ecgdataflag_saved].EGC_ADCVaule[i]=ADC_Value[i];
			 }
		 
	  }
		
		ecgdataflag_realtime++;	
		ecgdataflag_saved++;
		if(ecgdataflag_realtime>=5) 
		{
			
			ecgdataflag_realtime=0;
			
	
		}
		 
		 
		 
		HeartWave_display(ECGdata_realtime[0].EGC_ADCVaule);//显示心电的波形
		 
	
		
	   //保存计算到的频率
		 float frq = TIM2_Poll();
	 /********判断心率是否计算完成**********************/
     if(TIM2_CAPTURE_STA==0)
		 {
			int bmp = frq *60; 
//		  HeartRate_Display(bmp);//刷新心电的频率
//		  HeartState_Display(frq*60);//刷新心电的状态
		 }
		 

	//printf("******************开始**************************\n\n\n");
		/*将数据打包并发送*/
//		for(i=0;i<NPT;i++)
//		{
//			
//		   // 开始发送
//			startValuePack(Send_Buffer);
//		  
//		  // 将要回传的值放入，注意顺序为 Bool->Byte->Short->Int->Float			
//		  //putInt(bmp)
//			putFloat(ADC_Value[i]*100);

//		  // 通过串口发送，endValuePack返回了数据包的总长度
//			sendBuffer(Send_Buffer,endValuePack()); 
//			HAL_Delay(500);
//			int data = ADC_Value[i]/3.3*255;
//			printf("w%d",data);
//	
//		}
   //printf("--------------------结束----------------------------\n\n\n");
		
		
		
		ADC_Start();
		adc_dma_ok=0;//清除标志位，为下一次转换做准备
		
		
	 }






/***********************按键行为处理*************************************************/	
	 if(key1_state==1)
	 {
		 //按键松开
		 if(KEY1==1)
		 {
			 //清除标志位
			 key1_state = 0;
			 
			 HeartWave_display(ECGData1);//显示心电的波形
			 HeartRate_Display(60);//刷新心电的频率
		   HeartState_Display(60);//刷新心电的状态
			 HeartWave_display(ECGData2);//显示心电的波形
			 HeartRate_Display(60);//刷新心电的频率
		   HeartState_Display(60);//刷新心电的状态
			 printf("Key1SetupOK!\n\n");
		 }
		 
	 }
	  if(key2_state==1)
	 {
		 //按键松开
		 if(KEY2==1)
		 {
			 //清除标志位
			 key2_state = 0;
			 if(ecgdataflag_saved>=5) 
				{
					printf("ecgdataflag_saved:%d\n",ecgdataflag_saved);
					printf("重新更新数据\n");
					ecgdataflag_saved=0;
					printf("ecgdataflag_saved:%d\n",ecgdataflag_saved);
			
				}
			 
			 printf("Key2SetupOK!\n\n");
		 }
		 
	 }
	  if(key3_state==1)
	 {
		 //按键松开
		 if(KEY3==1)
		 {
			 //消抖
			 if(KEY3==1)
			 {
			 //清除标志位
			 key3_state = 0;
			 
			 printf("Key3SetupOK!\n\n");
			 }
		 }
		 
	 }
	  if(key4_state==1)
	 {
		 //按键松开
		 if(KEY4==1)
		 {
			 //清除标志位
			 key4_state = 0;
			 
		
			 printf("Key4SetupOK!\n\n");
		 }
		 
	 }
	 
}



/* 函数名称：void ADC_Start(void)
 * 功能描述：FFT数据采集的启动
 * 参数：无
 * 返回值：无
 */
void ADC_Start(void)
{
	/*启动ADC的DMA传输，配合定时器触发ADC转换*/
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&ADC_ConvertedValue, NPT);
	/*开启定时器，用溢出时间来触发ADC*/
	HAL_TIM_Base_Start(&htim3);
}


/* 函数名称：void FFT_Stop(void)
 * 功能描述：FFT数据采集的停止
 * 参数：无
 * 返回值：无
 */
void ADC_Stop(void)
{
	/*停止ADC的DMA传输*/
	HAL_ADC_Stop_DMA(&hadc1);
	/*停止定时器*/
	HAL_TIM_Base_Stop(&htim3);
}

/* 函数名称：void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
 * 功能描述：ADC的DMA回调函数
 * 参数：hadc --- adc结构体指针
 * 返回值：无
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
//	HAL_ADC_Stop_DMA(&hadc1);	//停止ADC的DMA传输
	ADC_Stop();
	adc_dma_ok = 1;						//标记ADC_DMA传输完成
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

