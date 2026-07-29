#include "dc_motor.h"
#define max_pwm_speed 6400
#define min_pwm_speed 185
void set_forward_gpio(void)
{
      bsp_set_gpio_high(BIN2_GPIO_Port,BIN2_Pin);
	  bsp_set_gpio_high(AIN1_GPIO_Port,AIN1_Pin);
      bsp_set_gpio_low(BIN1_GPIO_Port,BIN1_Pin);
	  bsp_set_gpio_low(AIN2_GPIO_Port,AIN2_Pin);
}
void set_back_gpio(void)
{
   bsp_set_gpio_high(BIN1_GPIO_Port,BIN1_Pin);
   bsp_set_gpio_high(AIN2_GPIO_Port,AIN2_Pin);
   bsp_set_gpio_low(BIN2_GPIO_Port,BIN2_Pin);
   bsp_set_gpio_low(AIN1_GPIO_Port,AIN1_Pin);
}

void dc_motor_on(int16_t speedL,int16_t speedR)
{     
	  if(speedL>=0||speedR>=0)
      {
		set_forward_gpio();
	  }
	  else{
	    set_back_gpio();
		  speedL=-speedL;
		  speedR=-speedR;
	  }
	  /* оч╥Ы */
    if(speedL > max_pwm_speed)
        speedL = max_pwm_speed;

    if(speedR > max_pwm_speed)
        speedR = max_pwm_speed;

    if(speedL < min_pwm_speed)
        speedL = min_pwm_speed;

    if(speedR < min_pwm_speed)
        speedR = min_pwm_speed;
	  bsp_set_timer_compare(1,speedL);
	  bsp_set_timer_compare(2,speedR);	
}

void dc_motorL_brake(void)
{
   bsp_set_gpio_high(BIN1_GPIO_Port,BIN1_Pin);
   bsp_set_gpio_high(BIN2_GPIO_Port,BIN2_Pin);
   bsp_set_timer_compare(1,0);
}

void dc_motorR_brake(void)
{
   bsp_set_gpio_high(AIN2_GPIO_Port,AIN2_Pin);
   bsp_set_gpio_high(AIN1_GPIO_Port,AIN1_Pin);
   bsp_set_timer_compare(2,0);
}
