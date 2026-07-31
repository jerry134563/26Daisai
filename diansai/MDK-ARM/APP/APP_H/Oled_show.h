#ifndef __OLED_SHOW__H
#define __OLED_SHOW__H
#include "OLED_Data.h"
#include "OLED.h"
#include "main.h"
#include "line_tracking.h"

int8_t* get_oled_show_choose_addr(void);
uint8_t* tick_mode_addr(void);
uint8_t* task_num_addr(void);

void oled_show(void);




#endif
