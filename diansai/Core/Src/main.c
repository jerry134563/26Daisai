/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BSP_H.h"
#include "Module_H.h"
#include "pid.h"
#include "line_tracking.h"
#include "ball_control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
float R_rpm=0;
float L_rpm=0;
float Wish_angle = 0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  MX_UART8_Init();
  MX_UART7_Init();
  MX_UART5_Init();
  MX_TIM7_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	bsp_timer_init();
	bsp_usart_init();
	bsp_set_gpio_high(power_en_GPIO_Port,power_en_Pin);
	bsp_set_gpio_high(PWM_EN_GPIO_Port,PWM_EN_Pin);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  cnt_flag_t*p_time_flag=get_g_time_flag_addr();
  PidController_t*pid_forward=pid_get_speed_controller();
  pid_init(pid_forward,85,1.1,0,1500);// pid_init(pid_forward,35,0.95,0.5,4500);5mspid����
	ball_control_init();
	uint8_t*u8_array=get_s_rx_buf_u8();
  while (1)
  {
//		//大头步进电机:地址3, 方向0, 速度1000, 0直接启动, 脉冲�?100, 0, 0(3200为一�?)
//		Emm_V5_Pos_Control(3, 0, 1000, 0, 100, 0, 0);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(p_time_flag->t_0_5_ms_flag){
			p_time_flag->t_0_5_ms_flag=0;
			
		}
	 if(p_time_flag->t_5_ms_flag)
	 {
			p_time_flag->t_5_ms_flag=0;
			tracking_line();
			int16_t turn_speed = pid_calculate(pid_forward,Wish_angle,get_yaw_atk901(),0,0);

	 }
	 if(p_time_flag->t_16_ms_flag){
		 p_time_flag->t_16_ms_flag=0;
		 ball_position();
		 
	 }
	 if(p_time_flag->t_30_ms_flag){
	 }
	 if(p_time_flag->t_500_ms_flag){
		 p_time_flag->t_500_ms_flag = 0;
		 
//		 uint8_t*read_Line=get_g_Line_state_addr();
		 
//		bsp_usart8_printf("%d,%d,%d,%d,%d,%d,%d,%d\n",read_Line[track_left1],read_Line[track_left2],read_Line[track_left3],read_Line[track_left4],\
//		 read_Line[track_right4],read_Line[track_right3],read_Line[track_right2],read_Line[track_right1]);
		 
//		 bsp_usart8_printf("%f\n",get_yaw_speed());
	 }
	 test_key();
   if(u8_array[0]=='1')
	 {
	   		Emm_V5_Pos_Control(3, 0, 1000, 0, 10, 0, 0);//@param:addr,dir(0/1),vel,acc,clk,raF,snF
		 u8_array[0]=0;
	 }
	    if(u8_array[0]=='2')
	 {
		Emm_V5_Pos_Control(3, 1, 1000, 0, 10, 0, 0);
		 		 u8_array[0]=0;

	 }
	    if(u8_array[0]=='4')
	 {
		Emm_V5_Pos_Control(3, 0, 1000, 0, 10, 0, 0);
		 		 u8_array[0]=0;
	 }

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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 10;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
