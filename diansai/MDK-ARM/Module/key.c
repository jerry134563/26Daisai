#include "key.h"
#include "Emm_V5.h"
uint8_t KEY1_Push_flag=0;
uint8_t KEY3_Push_flag=0;
uint8_t KEY4_Push_flag=0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin==Key1_Pin)//pin4//任务二
   {
		 KEY1_Push_flag=1;
   }
   else if(GPIO_Pin==Key3_Pin)//pin5,6//任务三
   {
    KEY3_Push_flag=1;
   }
   else if(GPIO_Pin==Key4_Pin)//pin13//任务四
   {
		 KEY4_Push_flag=1;
   }
}

uint8_t* get_KEY1_Push_flag(void)
{
  return &KEY1_Push_flag;
}
uint8_t* get_KEY3_Push_flag(void)
{
  return &KEY3_Push_flag;
}
uint8_t* get_KEY4_Push_flag(void)
{
  return &KEY4_Push_flag;
}

void test_key(void)
{
  if(KEY1_Push_flag==1)
	{
    KEY1_Push_flag=0;
	}
	  if(KEY3_Push_flag==1)
	{
    KEY3_Push_flag=0;
	}
	  if(KEY4_Push_flag==1)
	{
    KEY4_Push_flag=0;
	}

}


