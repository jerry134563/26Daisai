#include "mpu6050.h" 


/*=========================================================

					  START:MPU6050

=========================================================*/

float Pitch;
float Roll;
float Yaw;
int16_t acc_x, acc_y, acc_z;
int16_t gyr_x, gyr_y, gyr_z;
int16_t temperature;

/**
  * 函    数：MPU6050初始化函数
  * 参    数：无
  * 返 回 值：无
  * 说    明：无		
  */
void MPU6050_Init(void)
{
	/* 初始化ATK-MS6050 */
	uint8_t ret;
    ret = atk_ms6050_init();
    if (ret != 0)
    {
        while (1)
        {
            HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN,GPIO_PIN_SET);
        }
    }
	/* 初始化ATK-MS6050 DMP */
    ret = atk_ms6050_dmp_init();
	if(ret != 0)
	{
		while(ret)
		{
			HAL_Delay(1000);
			ret = atk_ms6050_dmp_init();
			HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN);
		} 
		HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN,GPIO_PIN_RESET);

	}else
	{
		HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN,GPIO_PIN_RESET);
	}
}

/**
  * 函    数：MPU6050数据读取函数
  * 参    数：无
  * 返 回 值：无
  * 说    明：放MPU6050_INT引脚触发的EXTI中断里面	。三角度是不管怎么样都需要读取的，否则fifo会溢出，前面几个用不到的可以注释不读取。
  */
void Get_MPU6050_Data(void)
{
	/* 获取ATK-MS6050加速度值 */
	atk_ms6050_get_accelerometer(&acc_x, &acc_y, &acc_z);
	
	/* 获取ATK-MS6050陀螺仪值 */
	atk_ms6050_get_gyroscope(&gyr_x, &gyr_y, &gyr_z);
	 
	/* 获取ATK-MS6050温度值 */
//	atk_ms6050_get_temperature(&temperature);
		
	/* 获取ATK-MS6050 DMP处理后的数据 */
	atk_ms6050_dmp_get_data(&Pitch, &Roll, &Yaw);
}

/*=========================================================

						END:MPU6050

=========================================================*/


/**
  * 函    数：外部中断回调函数
  * 参    数：无
  * 返 回 值：无
  * 说    明：无
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//MPU6050数据读取引脚	
	if(GPIO_Pin == MPU6050_EXTI_GPIO_PIN)
	{
		Get_MPU6050_Data();
		__HAL_GPIO_EXTI_CLEAR_IT(MPU6050_EXTI_GPIO_PIN);
	}
	
//	if(GPIO_Pin == MEDICINE_EXTI_GPIO_PIN)//双边沿
//	{
//		rectangle_right_flag = 1;
//		__HAL_GPIO_EXTI_CLEAR_IT(MEDICINE_EXTI_GPIO_PIN);//释放中断信号
//	}		
}
float get_yaw(void)
{
  return Yaw;
}

int16_t get_gyr_z(void)
{
  return gyr_z;
}






