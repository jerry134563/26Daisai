#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

#include "main.h"
#include "tim.h"
typedef struct
{
  volatile uint32_t t_1_ms_count;
  volatile uint8_t t_1_ms_flag;
  volatile uint8_t t_10_ms_flag;
  volatile uint8_t t_5_ms_flag;

}cnt_flag_t;


void bsp_timer_init(void);
void bsp_set_timer_compare(uint8_t channel,uint16_t COMPARE);
void bsp_timer_set_counter(TIM_HandleTypeDef*tim,uint16_t counter);
cnt_flag_t*get_g_time_flag_addr(void);

#endif
