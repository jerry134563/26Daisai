#include "bsp_timer.h"
#define Tim_Period_Callback()  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
cnt_flag_t g_time_flag;
void bsp_timer_init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL); 
}
//channel 1  Îª×ó±ßµç»ú
void bsp_set_timer_compare(uint8_t channel,uint16_t COMPARE)
{
	if(channel==1)
    {
	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, COMPARE);
	}
	else if(channel==2)
	{
	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, COMPARE);
	}
}
void bsp_timer_set_counter(TIM_HandleTypeDef*tim,uint16_t counter)
{
    __HAL_TIM_SET_COUNTER(tim, counter);
}
    Tim_Period_Callback()
{	
	if(htim==&htim6)
	{
		g_time_flag.t_1_ms_count++;
		g_time_flag.t_1_ms_flag=1;
		if(g_time_flag.t_1_ms_count%10==0)
		{
		  g_time_flag.t_10_ms_flag=1;
		}
		else if(g_time_flag.t_1_ms_count%5==0)
		{
		  g_time_flag.t_5_ms_flag=1;
		}
	}	
}

cnt_flag_t*get_g_time_flag_addr(void)
{
   return &g_time_flag;
}


