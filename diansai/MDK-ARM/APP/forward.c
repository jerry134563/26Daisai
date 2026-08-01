#include "forward.h"
int8_t f_A_stop_flag = 0;                               
int16_t f_tracking_turn_error = 0;		    
int16_t f_tracking_turn_speed = 0;		  
int16_t f_tracking_led_num = 0;              
int16_t f_tracking_speed = 2600;		        //循迹期望速度1650; only xunji:2550; xunji & ball:?
int16_t f_last_turn_speed = 0;		        
uint8_t f_complete_half_flag=0;
float f_kp_l=11;
float f_kd_l= 0 ;//-1
float f_k_turn = 0.01;
uint8_t f_cnt= 0;
uint8_t f_complete_line_track_flag=0;
uint8_t A_to_B_tracking_line(void)
{
	        read_Line_state();
      	uint8_t*read_Line=get_g_Line_state_addr();
        f_last_turn_speed= f_tracking_turn_speed;
            if(read_Line[track_left1]  == black) f_tracking_turn_error += 140,  f_tracking_led_num++;
            if(read_Line[track_left2]  == black) f_tracking_turn_error += 120,  f_tracking_led_num++;
            if(read_Line[track_left3]  == black) f_tracking_turn_error += 70,   f_tracking_led_num++;
            if(read_Line[track_left4]  == black) f_tracking_turn_error += 22,   f_tracking_led_num++;   

            if(read_Line[track_right4] == black) f_tracking_turn_error -= 22,   f_tracking_led_num++;
            if(read_Line[track_right3] == black) f_tracking_turn_error -= 70,   f_tracking_led_num++;
            if(read_Line[track_right2] == black) f_tracking_turn_error -= 120,  f_tracking_led_num++;
            if(read_Line[track_right1] == black) f_tracking_turn_error -= 140,  f_tracking_led_num++;
	
	         
					f_tracking_turn_speed = f_tracking_turn_error / f_tracking_led_num;   //返回转向速度
										 
          f_tracking_turn_error = 0;    //清空，等待下次识别
          f_tracking_led_num = 0;       //清空，等待下次识别
					int16_t motor_L_out=f_tracking_speed-f_tracking_turn_speed*f_kp_l+f_kd_l*get_yaw_speed();
					int16_t motor_R_out=f_tracking_speed+f_tracking_turn_speed*f_kp_l+f_kd_l*get_yaw_speed();
					dc_motor_on(motor_L_out,motor_R_out);
			return 0;
}



