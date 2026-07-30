#include "bsp_gpio.h"
uint8_t bsp_read_gpio(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  return HAL_GPIO_ReadPin(GPIOx,GPIO_Pin);
}

void bsp_set_gpio_high(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_SET);
}

void bsp_set_gpio_low(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_RESET);
}

