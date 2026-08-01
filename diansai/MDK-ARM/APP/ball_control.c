#include "ball_control.h"
PidController_t ball_control;
uint16_t zore_x=110;
uint16_t g__1cm_x=98;
uint16_t g_1cm_x=122;
uint16_t g__5cm_x=51;
uint16_t g_5cm_x=170;
int16_t total_move=0,out = 0;
float kp_b=0.1;
float ki_b=0.01;
float kd_b=0;
int16_t err=0,last_err = 0,err_sum = 0;
uint8_t stable_cnt = 0;
uint32_t count=0;
uint32_t count2=0;
uint8_t up_flag=0;
uint8_t down_flag=0;

void ball_control_init(void){
	pid_init(&ball_control,1.3,0,0,150);//1.3,0,0,150
}

#define max_err_sum 32
void ball_position(void){
//  err=g_5cm_x-get_ball_x();
//	err_sum+= err;
//	if(err>max_err_sum){err = max_err_sum;}if(err<-max_err_sum){err = -max_err_sum;}
//	out=kp_b*err+ki_b*err_sum+kd_b*(err-last_err);
//	if(out>100)
//	{
//	  out=100;
//	}
//	 if(out<-100)
//	{
//	  out=-100;
//	}
	out=pid_calculate(&ball_control,g_5cm_x,get_ball_x(),10,40,10);
		if(out>30)
	{
	  out=30;
	}
	 if(out<-30)
	{
	  out=-30;
	}
	bsp_usart8_printf("%d\n",out);
  Step_abs_pos(out);
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
	  count++;
   if(1)//(get_ball_x()<=g__5cm_x)
	 {
		   if(down_flag!=1)
			 {
				HAL_StatusTypeDef ret=Emm_V5_Pos_Control(3, 1, 800, 0, 10, 1, 0);
				 count=0;
		   if(ret!=HAL_OK)
			 {
				 
			 }
			 			 else
			 {
			 count2++;
				up_flag=1;
			 }
		 }
	 }	
   else if(get_ball_x()>g__5cm_x){
		 if(1)//(up_flag!=1||count>8)
		 {   HAL_StatusTypeDef ret=	Emm_V5_Pos_Control(3, 0, 800, 0, 10, 1, 0);
			 				 count=0;
		 		   if(ret!=HAL_OK)
			 {
				 
			 }
			 else
			 {
			 count2++;
			 down_flag=1;
			 }
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
	Step_abs_pos(-48);
	HAL_Delay(200);
		Step_abs_pos(0);
	HAL_Delay(1120);

}




















