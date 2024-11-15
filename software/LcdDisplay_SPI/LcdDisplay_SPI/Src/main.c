/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define LEN 200
__IO uint16_t ADC_DMA_ConvertValue[LEN];
__IO uint32_t TransDone =1;

uint8_t ADC_Buffer[LEN];


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
double value[LCD_W];
uint8_t c1,c2,c3;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
double Get_ADC(){
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1,1);

	return HAL_ADC_GetValue(&hadc1);   
}

// void write(){
//     value=3.3*Get_ADC()/4096;
//     c1=value;
//     c2=value*10-c1*10;
//     c3=value*100-c2*10-c1*100;
//     ADC_Buffer[0]=c1+0x30;
//     ADC_Buffer[1]=0x2E;
//     ADC_Buffer[2]=c2+0x30;
//     ADC_Buffer[3]=c3+0x30;
//     HAL_UART_Transmit_DMA(&huart1,ADC_Buffer,sizeof(ADC_Buffer));
// }

 void HAL_ADC_ConvClptCallback(ADC_HandleTypeDef *hadc){
   if (TransDone==0){
     HAL_ADC_Stop(&hadc1);
     TransDone=1;
   }
   	LCD_ShowString(30,50,ADC_Buffer,RED,WHITE,32,0);
 }

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
  MX_SPI5_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	delay_init(180);			
  LCD_Init();						
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);	
  HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_Buffer,LEN);
  HAL_TIM_Base_Start(&htim3);
 

 LCD_DrawLine(0,LCD_H*4/5,LCD_W,LCD_H*4/5,BLACK);
 LCD_ShowString(0,LCD_H*6/7,"max(V):",RED,WHITE,16,0);
 LCD_ShowString(LCD_W/2,LCD_H*6/7,"min(V):",RED,WHITE,16,0);

 double max;
 double min;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    double init=3.3*Get_ADC()/4096;
    max=init;
    min=init;

    for(int x=0;x<LCD_W;x++){
      // HAL_Delay(20);
      value[x]=3.3*Get_ADC()/4096;
      HAL_Delay(20);
      LCD_DrawPoint(x,30*(value[x])+LCD_H/2,RED);
      
      if(x>=1){
         LCD_DrawLine(x-1,30*value[x-1]+LCD_H/2,x,value[x]*30+LCD_H/2,RED);
      }
      
      if(value[x]>max){
        max=value[x];
         LCD_ShowFloatNum1(70,LCD_H*6/7,max,3,RED,WHITE,16);
      }
      if(value[x]<=min){
        min=value[x];
        LCD_ShowFloatNum1(LCD_W/2+70,LCD_H*6/7,min,3,RED,WHITE,16);
      }

      // if(x>LCD_W/2){
      //   LCD_ShowFloatNum1(70,LCD_H*6/7,max,3,RED,WHITE,16);
      //   LCD_ShowFloatNum1(LCD_W/2+70,LCD_H*6/7,min,3,RED,WHITE,16);
      // }

      if(x==LCD_W-1){
       	  LCD_Fill(0,0,LCD_W,LCD_H,WHITE);	
          LCD_DrawLine(0,LCD_H*4/5,LCD_W,LCD_H*4/5,BLACK);
          LCD_ShowString(0,LCD_H*6/7,"max(V):",RED,WHITE,16,0);
          LCD_ShowString(LCD_W/2,LCD_H*6/7,"min(V):",RED,WHITE,16,0);
           max=init;
           min=init;
           x=0;
        }
      }
    }  

    
		// }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		LCD_ShowPicture(0,0,240,240,gImage_picture);
		
		// LCD_ShowString(0,0,"  you qing  ",RED,WHITE,32,0);		//�ַ�����ʾ����
		// LCD_ShowString(30,50,"LCD_W:",RED,WHITE,16,0);				
		// LCD_ShowIntNum(80,50,LCD_W,3,RED,WHITE,16);						//������ʾ����
		// LCD_ShowString(130,50,"LCD_H:",RED,WHITE,16,0);
		// LCD_ShowIntNum(160,50,LCD_H,3,RED,WHITE,16);
		 //LCD_ShowString(30,50,ADC_Buffer,RED,WHITE,32,0);
  }
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 108;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
