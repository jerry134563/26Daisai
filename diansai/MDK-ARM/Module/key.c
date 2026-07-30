#include "key.h"
#include "Emm_V5.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin==Key1_Pin)//pin4
   {
		 Emm_V5_Pos_Control(3, 0, 1000, 0, 50, 0, 0);//@param:addr,dir(0/1),vel,acc,clk,raF,snF
   }
   else if(GPIO_Pin==Key2_Pin || GPIO_Pin==Key3_Pin)//pin5,6
   {
		Emm_V5_Pos_Control(3, 1, 1000, 0, 50, 0, 0);
   }
   else if(GPIO_Pin==Key4_Pin)//pin13
   {
		 Emm_V5_Pos_Control(3, 0, 1000, 0, 50, 0, 0);
   }
}

