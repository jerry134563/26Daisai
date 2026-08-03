#include "five.h"
#include "ball_control.h"
#include "line_tracking.h"
int16_t A_tracking_turn_error = 0;		    
int16_t A_tracking_turn_speed = 0;		  
int16_t A_tracking_led_num = 0;              
int16_t A_tracking_speed = 0;		        //循迹期望速度1650; only xunji:2550; xunji & ball:?
int16_t A_last_turn_speed = 0;		        
uint8_t A_complete_half_flag=0;
float A_kp_l=11;
float A_kd_l= 0 ;//-1
float A_k_turn = 0.01;
uint8_t A_cnt= 0;
uint8_t A_complete_line_track_flag=0;
uint8_t A_tracking_line(void)
{
	        read_Line_state();
	      A_tracking_speed+=2;
	        if(A_tracking_speed>1800)
					{
            A_tracking_speed=1800;
					}						
      	uint8_t*read_Line=get_g_Line_state_addr();
        A_last_turn_speed= A_tracking_turn_speed;
            if(read_Line[track_left1]  == black) A_tracking_turn_speed += 140,  A_tracking_led_num++;
            if(read_Line[track_left2]  == black) A_tracking_turn_speed += 120,  A_tracking_led_num++;
            if(read_Line[track_left3]  == black) A_tracking_turn_speed += 70,   A_tracking_led_num++;
            if(read_Line[track_left4]  == black) A_tracking_turn_speed += 22,   A_tracking_led_num++;   

            if(read_Line[track_right4] == black) A_tracking_turn_speed -= 22,   A_tracking_led_num++;
            if(read_Line[track_right3] == black) A_tracking_turn_speed -= 70,   A_tracking_led_num++;
            if(read_Line[track_right2] == black) A_tracking_turn_speed -= 120,  A_tracking_led_num++;
            if(read_Line[track_right1] == black) A_tracking_turn_speed -= 140,  A_tracking_led_num++;
	
	         if(A_tracking_led_num>=3)
					 {
					   A_tracking_turn_speed=0;
						 if(A_complete_half_flag)
						 {
						   if(get_yaw_atk901()<20&&get_yaw_atk901()>-20)
							 {
							     if(A_tracking_led_num<6)
									 {
										 dc_motorL_brake();
										 dc_motorR_brake();
										 dc_motor_on(0,0);
										 
										 A_complete_line_track_flag=1;
										 HAL_Delay(1000);
										 return 1;
									 }
							 }
						 
						 }
					 }
					 else
					 {
						 A_tracking_turn_speed = A_tracking_turn_error / A_tracking_led_num;   //返回转向速度

	         }
					 if(get_yaw_atk901()>170||get_yaw_atk901()<-170)
           {
					   A_complete_half_flag=1;
					 }					 
					 
          A_tracking_turn_error = 0;    //清空，等待下次识别
          A_tracking_led_num = 0;       //清空，等待下次识别
					int16_t motor_L_out=A_tracking_speed-A_tracking_turn_speed*A_kp_l+A_kd_l*get_yaw_speed();
					int16_t motor_R_out=A_tracking_speed+A_tracking_turn_speed*A_kp_l+A_kd_l*get_yaw_speed();
					dc_motor_on(motor_L_out+310,motor_R_out+380);
					 forward_open_control();

			return 0;
}

uint8_t A_get_complete_line_track_flag(void)
{

return A_complete_line_track_flag;
}	

			



