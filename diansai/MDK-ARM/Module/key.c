#include "key.h"
#include "Emm_V5.h"

struct keys key[KEY_NUMBER] = {0};

float abc = 1500;
int32_t ttt = 900;

/* 按键控制函数 */
void key_scan(void)
{
	/* 按键一 */
	if(key[0].short_flag == 1)
	{
		Emm_V5_Pos_Control(3, 0, 1000, 0, 100, 0, 0);
		key[0].short_flag = 0;
	}
	if(key[0].double_flag == 1)
	{		
		key[0].double_flag = 0;
	}
	if(key[0].long_flag == 1)
	{
		key[0].long_flag = 0;
	}
	
	/* 按键二 */
	if(key[1].short_flag == 1)
	{		
		
		key[1].short_flag = 0;
	}	
	if(key[1].double_flag == 1)
	{
		key[1].double_flag = 0;
	}
	if(key[1].long_flag == 1)
	{
		key[1].long_flag = 0;
	}
	
	/* 按键三 */
	if(key[2].short_flag == 1)
	{		
		key[2].short_flag = 0;
	}	
	if(key[2].double_flag == 1)
	{
        
		key[2].double_flag = 0;
	}
	if(key[2].long_flag == 1)
	{
		
		key[2].long_flag = 0;
	}
	
	/* 按键四 */
	if(key[3].short_flag == 1)
	{		
		key[3].short_flag = 0;
	}	
	if(key[3].double_flag == 1)
	{
		key[3].double_flag = 0;
	}
	if(key[3].long_flag == 1)
	{
		key[3].long_flag = 0;
	}
}



/*定时器7扫描按键：周期10ms */
void KEY_Interupt_10ms_Scan(void)
{
		key[0].key_flag = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
		key[1].key_flag = HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin);
		key[2].key_flag = HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin);
		key[3].key_flag = HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin);
		for(int i = 1;i < KEY_NUMBER;i++)
		{
				switch(key[i].key_judge)
				{
						case 0:
								if(key[i].key_flag == 0)
								{
										key[i].key_judge=1;
								}
								break;
						case 1:
								if(key[i].key_flag == 0)
								{
										key[i].key_judge = 2;
										key[i].key_time  = 0;
								}
								else{
										key[i].key_judge=0;
								}						
								break;
						case 2:
								if(key[i].key_flag == 0)
								{
										key[i].key_time++;
								}
								else if(key[i].key_time > 70 && key[i].key_flag == 1)
								{
										key[i].long_flag = 1;
										key[i].key_judge = 0;
								}
								else if(key[i].key_flag == 1 && key[i].key_time < 70)
								{
										switch(key[i].double_judge)
										{
												case 0:
														key[i].double_judge=1;
														key[i].double_time =0;
														break;
												case 1:
														key[i].double_judge=0;
														key[i].double_flag =1;
														break;
										}
										key[i].key_judge =0;
								}
								break;				
				}
				if(key[i].double_judge ==1)
				{
						key[i].double_time++;
						if(key[i].double_time >= 35)
						{
								key[i].short_flag = 1;
								key[i].double_judge =0;
						}
				}
		} 
}

