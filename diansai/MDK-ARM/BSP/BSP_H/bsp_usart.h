#ifndef __BSP_USART__H
#define __BSP_USART__H

#include "main.h"
#include "usart.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>	
void bsp_usart_init(void);
void bsp_usart8_printf(const char *format, ...);
float get_yaw_atk901(void);

#endif
