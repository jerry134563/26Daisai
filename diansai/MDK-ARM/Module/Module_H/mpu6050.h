#ifndef __MPU6050_H
#define __MPU6050_H

#include "main.h"  
#include "atk_ms6050.h"
#include "inv_mpu.h"

#define MPU6050_EXTI_GPIO_PORT             GPIOB
#define MPU6050_EXTI_GPIO_PIN              GPIO_PIN_12  

#define MEDICINE_EXTI_GPIO_PORT            GPIOC
#define MEDICINE_EXTI_GPIO_PIN             GPIO_PIN_3  

#define LED0_GPIO_PORT            	GPIOA
#define LED0_GPIO_PIN             	GPIO_PIN_15

extern float Pitch;
extern float Roll;
extern float Yaw;
extern int16_t acc_x, acc_y, acc_z;
extern int16_t gyr_x, gyr_y, gyr_z;
extern int16_t temperature;


void MPU6050_Init(void);
void Get_MPU6050_Data(void);
float get_yaw(void);
int16_t get_gyr_z(void);


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif

