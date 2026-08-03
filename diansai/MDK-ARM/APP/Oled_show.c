#include "Oled_show.h"
#include "Emm_V5.h"
uint32_t tick_cnt = 0;

int8_t oled_show_choose = 0;
int8_t* get_oled_show_choose_addr(void){
	return &oled_show_choose;
}

uint8_t tick_mode = 0;
uint8_t* tick_mode_addr(void){
	return &tick_mode;
}
uint8_t tick_mode_start = 0;

uint8_t task_choose_num = 0;
uint8_t task_num = 0;
uint8_t* task_num_addr(void){
	return &task_num;
}

void oled_show(void)
{
	if(*get_KEY1_Push_flag()){//!!!!!!!确认键
		task_num = task_choose_num;
		tick_mode = 1;
	}
	if(*get_KEY3_Push_flag()){		//递减键
		if(task_choose_num==0){task_choose_num = 6;}
		else{task_choose_num -=1;}
	}
	if(*get_KEY4_Push_flag()){		//递增键
		if(task_choose_num==6){task_choose_num=0;}
		else{task_choose_num +=1;}
	}
	test_key();
	
	
		switch(task_num){
			case 2: if(get_complete_line_track_flag()){tick_mode = 0;task_num = 0;}break;
			case 3:break;
			case 4:break;
			default:break;
		}
	
	
	if(tick_mode){
		if(tick_mode_start==0){
			tick_mode_start = 1;
			oled_show_choose = 1;
			tick_cnt = 0;
		}
		tick_cnt++;
	}else{
		if(tick_mode_start==1){
			tick_mode_start = 0;
		}
	}
	
	switch(oled_show_choose)
	{
		case 0:
			OLED_Clear();
		
		OLED_ShowString(0,0,"task_choose:",OLED_8X16);
		
		OLED_ShowNum(16,16,task_choose_num,1,OLED_8X16);
		
			OLED_Update();
			
			break;
		case 1: ///秒数计时与显示
			/* 识别 */
			OLED_Clear();
			OLED_ShowString(0,0,"time_seconds",OLED_8X16);
		
		switch(task_choose_num){
			case 2:if(tick_cnt>40){tick_cnt = 40;}break;
			case 3:if(tick_cnt>10){
				tick_cnt = 10;tick_mode = 0;task_num = 0;
				back_to_zero();

				
			}break;
			case 4:if(tick_cnt>16){tick_cnt = 16;tick_mode = 0;task_num = 0;}break;
			default :break;
		}
		
			OLED_ShowNum(16,16,tick_cnt/2,3,OLED_8X16);
		
		OLED_ShowString(0,40,"task:",OLED_8X16);
		OLED_ShowNum(40,40,task_choose_num,3,OLED_8X16);
		
		OLED_UpdateArea(0,0,56,56);
			OLED_Update();	
			
			break;
			
		case 2:
			/* 电源显示 */
			OLED_Clear();
			OLED_Update();	
			break;	
	}
}

