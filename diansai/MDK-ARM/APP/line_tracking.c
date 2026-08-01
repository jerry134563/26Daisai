#include "line_tracking.h"
int16_t tracking_weights[8] = {-140, -120, -60, -30, +30, +60, +120, +140};  
int8_t tracking_number_of_circle = 1;       
int8_t tracking_enable_flag = 0;            
int8_t A_stop_flag = 0;                               
int16_t tracking_turn_error = 0;		    
int16_t tracking_turn_speed = 0;		  
int16_t tracking_led_num = 0;              
int8_t crossing_num = 0;                  
int16_t tracking_speed = 2200;		        //循迹期望速度1650; only xunji:2550; xunji & ball:?
int16_t last_turn_speed = 0;		        
uint8_t complete_half_flag=0;
float kp_l=11;
float kd_l= 0 ;//-1
float k_turn = 0.01;
uint8_t cnt= 0;
uint8_t complete_line_track_flag=0;
uint8_t tracking_line(void)
{
	        read_Line_state();
      	uint8_t*read_Line=get_g_Line_state_addr();
        last_turn_speed= tracking_turn_speed;
            if(read_Line[track_left1]  == black) tracking_turn_error += 140,  tracking_led_num++;
            if(read_Line[track_left2]  == black) tracking_turn_error += 120,  tracking_led_num++;
            if(read_Line[track_left3]  == black) tracking_turn_error += 70,   tracking_led_num++;
            if(read_Line[track_left4]  == black) tracking_turn_error += 22,   tracking_led_num++;   

            if(read_Line[track_right4] == black) tracking_turn_error -= 22,   tracking_led_num++;
            if(read_Line[track_right3] == black) tracking_turn_error -= 70,   tracking_led_num++;
            if(read_Line[track_right2] == black) tracking_turn_error -= 120,  tracking_led_num++;
            if(read_Line[track_right1] == black) tracking_turn_error -= 140,  tracking_led_num++;
	
	         if(tracking_led_num>=3)
					 {
					   tracking_turn_speed=0;
						 if(complete_half_flag)
						 {
						   if(get_yaw_atk901()<20&&get_yaw_atk901()>-20)
							 {
							     if(tracking_led_num<6)
									 {
										 dc_motorL_brake();
										 dc_motorR_brake();
										 dc_motor_on(0,0);
										 
										 complete_line_track_flag=1;
										 HAL_Delay(1000);
										 return 1;
									 }
							 }
						 
						 }
					 }
					 else
					 {
						 tracking_turn_speed = tracking_turn_error / tracking_led_num;   //返回转向速度

	         }
					 if(get_yaw_atk901()>170||get_yaw_atk901()<-170)
           {
					   complete_half_flag=1;
					 }					 
					 
          tracking_turn_error = 0;    //清空，等待下次识别
          tracking_led_num = 0;       //清空，等待下次识别
					int16_t motor_L_out=tracking_speed-tracking_turn_speed*kp_l+kd_l*get_yaw_speed();
					int16_t motor_R_out=tracking_speed+tracking_turn_speed*kp_l+kd_l*get_yaw_speed();
					dc_motor_on(motor_L_out,motor_R_out);
			return 0;
}

uint8_t get_complete_line_track_flag(void)
{

return complete_line_track_flag;
}	

			
