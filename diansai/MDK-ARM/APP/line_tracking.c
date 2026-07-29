#include "line_tracking.h"
int16_t tracking_weights[8] = {-140, -120, -60, -30, +30, +60, +120, +140};  
int8_t tracking_number_of_circle = 1;       
int8_t tracking_enable_flag = 0;            
int8_t Left_turn_flag = 0;                  
int8_t Right_turn_flag = 0;                 
int16_t tracking_turn_error = 0;		    
int16_t tracking_turn_speed = 0;		  
int16_t tracking_led_num = 0;              
int8_t crossing_num = 0;                  
int16_t tracking_speed = 1500;		        //循迹期望速度1650
int16_t last_turn_speed = 0;		        //循迹期望速度1650

float kp_l=16;
float kd_l=0;//-1


void tracking_line(void)
{
	
      	uint8_t*read_Line=read_Line_state();
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
					 }
					 else
					 {
						 tracking_turn_speed = tracking_turn_error / tracking_led_num;   //返回转向速度
	         }
          memset(read_Line,0,8);    //清除状态数组
          tracking_turn_error = 0;    //清空，等待下次识别
          tracking_led_num = 0;       //清空，等待下次识别
					int16_t motor_L_out=tracking_speed-tracking_turn_speed*kp_l+kd_l*get_yaw_atk901();
					int16_t motor_R_out=tracking_speed+tracking_turn_speed*kp_l+kd_l*get_yaw_atk901();
					dc_motor_on(motor_L_out,motor_R_out);
					


			}	

