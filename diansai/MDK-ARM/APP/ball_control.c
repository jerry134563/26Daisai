#include "ball_control.h"
PidController_t ball_control;
uint16_t zore_x=110;
uint16_t g__5cm_x=152;
uint16_t g_5cm_x=66;
int16_t total_move=0,out = 0;
void ball_control_init(void){
	pid_init(&ball_control,1.6,0,30,150);
}

void ball_position(void){
   out=pid_calculate(&ball_control,g__5cm_x,get_ball_x(),0,0);
	total_move = out;
	Step_abs_pos(total_move);
	
}


























