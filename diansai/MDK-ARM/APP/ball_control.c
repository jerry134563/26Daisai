#include "ball_control.h"
PidController_t ball_control;
uint16_t zore_x=110;
uint16_t g__5cm_x=65;
uint16_t g_5cm_x=152;
int16_t total_move=0,out = 0;
float kp_b=2;
float ki_b=0;
float kd_b=0;
int16_t err=0,last_err = 0,err_sum = 0;
uint8_t stable_cnt = 0;
uint32_t count=0;
uint32_t count2=0;

void ball_control_init(void){
	pid_init(&ball_control,1.3,0,0,150);//1.3,0,0,150
}

#define max_err_sum 32
void ball_position(void){
  err=g__5cm_x-get_ball_x();
	err_sum+= err;
	if(err>max_err_sum){err = max_err_sum;}if(err<-max_err_sum){err = -max_err_sum;}
	out=kp_b*err+ki_b*err_sum+kd_b*(err-last_err);
	if(out>30)
	{
	  out=30;
	}
	 if(out<-30)
	{
	  out=-30;
	}
	bsp_usart8_printf("%d\n",out);
		if(out>0){
			if(out>150)
			{
				out = 150;
			}
	Emm_V5_Pos_Control(3, 1, 1500, 0, out, 1, 0);
	} 
	  if(out<0){
       	if(out<-150)
				{
					out = -150;
				}
	Emm_V5_Pos_Control(3, 0, 1500, 0, -out, 1, 0);
	}
	if(out==0){
		Emm_V5_Pos_Control(3, 1, 0, 0, 0, 1, 0);
	}
	last_err = err;
}

//void ball_stay_in_5(){
//	out=pid_calculate(&ball_control,g__5cm_x,get_ball_x(),0,0);
//	total_move = out;
//	Step_abs_pos(total_move);
//}

void open_control(void)
{
	 HAL_StatusTypeDef ret;
   if(get_ball_x()<=g__5cm_x)
	 {
	   	 HAL_StatusTypeDef ret=Emm_V5_Pos_Control(3, 1, 800, 0, 20, 1, 0);
		   if(ret!=HAL_OK)
			 {
			   count++;
			 }
			 			 else
			 {
			 count2++;
			 }
	 }	
   else if(get_ball_x()>g__5cm_x){
	 HAL_StatusTypeDef ret=	Emm_V5_Pos_Control(3, 0, 800, 0, 20, 1, 0);
		 		   if(ret!=HAL_OK)
			 {
			   count++;
			 }
			 else
			 {
			 count2++;
			 }
	 }	 

}

void ball_first_step(void)
{
  HAL_Delay(1000);//µÈ´ýÌ§Æð
	
	Step_abs_pos(122);
	HAL_Delay(400);
	
	Step_abs_pos(-80);
	HAL_Delay(400);
	Step_abs_pos(-72);
	HAL_Delay(300);
	Step_abs_pos(-50);
	HAL_Delay(260);
	
	Step_abs_pos(4);
	HAL_Delay(1460);

}




















