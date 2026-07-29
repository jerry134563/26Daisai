#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "main.h"
uint8_t bsp_read_gpio(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void bsp_set_gpio_high(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void bsp_set_gpio_low(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif
