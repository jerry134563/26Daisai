#include "key.h"
#include "Emm_V5.h"
uint8_t KEY1_Push_flag=0;
uint8_t KEY2_Push_flag=0;
uint8_t KEY4_Push_flag=0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin==Key1_Pin)//pin4
   {
		// Emm_V5_Pos_Control(3, 0, 1000, 0, 10, 0, 0);//@param:addr,dir(0/1),vel,acc,clk,raF,snF
		 KEY1_Push_flag=1;
   }
   else if(GPIO_Pin==Key2_Pin || GPIO_Pin==Key3_Pin)//pin5,6
   {
		//Emm_V5_Pos_Control(3, 1, 1000, 0, 10, 0, 0);
    KEY2_Push_flag=1;
   }
   else if(GPIO_Pin==Key4_Pin)//pin13
   {
		// Emm_V5_Pos_Control(3, 0, 1000, 0, 10, 0, 0);
		 KEY4_Push_flag=1;
   }
}

uint8_t* get_KEY1_Push_flag(void)
{
  return &KEY1_Push_flag;
}
uint8_t* get_KEY2_Push_flag(void)
{
  return &KEY2_Push_flag;
}
uint8_t* get_KEY4_Push_flag(void)
{
  return &KEY4_Push_flag;
}

void test_key(void)
{
  if(KEY1_Push_flag==1)
	{
		Emm_V5_Pos_Control(3, 0, 1000, 0, 1, 0, 0);//@param:addr,dir(0/1),vel,acc,clk,raF,snF
    KEY1_Push_flag=0;
	}
	  if(KEY2_Push_flag==1)
	{
		Emm_V5_Pos_Control(3, 1, 1000, 0, 1, 0, 0);
    KEY2_Push_flag=0;
	}
	  if(KEY4_Push_flag==1)
	{
		Emm_V5_Pos_Control(3, 0, 1000, 0, 1, 0, 0);
    KEY4_Push_flag=0;
	}

}


