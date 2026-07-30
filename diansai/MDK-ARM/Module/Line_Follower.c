#include "Line_Follower.h"
uint8_t g_Line_state[8]={0};

uint8_t read_step = 0;
void read_Line_state(void)
{
	switch(read_step){
		case 0:
	g_Line_state[0]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//000
	bsp_set_gpio_high(W1_GPIO_Port,W1_Pin);	
	read_step++;
		break;
		case 1:
	g_Line_state[1]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//001
	bsp_set_gpio_high(W2_GPIO_Port,W2_Pin);	
	read_step++;
		break;
		case 2:
	g_Line_state[3]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//011
	bsp_set_gpio_low(W1_GPIO_Port,W1_Pin);	
	read_step++;
		break;
		case 3:
	g_Line_state[2]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//010
	bsp_set_gpio_high(W3_GPIO_Port,W3_Pin);	
	read_step++;
		break;
		case 4:
	g_Line_state[6]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//110
	bsp_set_gpio_high(W1_GPIO_Port,W1_Pin);	
	read_step++;
		break;
		case 5:
	g_Line_state[7]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//111
	bsp_set_gpio_low(W2_GPIO_Port,W2_Pin);	
	read_step++;
		break;
		case 6:
	g_Line_state[5]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//101
	bsp_set_gpio_low(W1_GPIO_Port,W1_Pin);	
	read_step++;
		break;
		case 7:
	g_Line_state[4]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//100
	bsp_set_gpio_low(W3_GPIO_Port,W3_Pin);
	read_step=0;
		break;
		default:
			read_step=0;
	} 
}
uint8_t*get_g_Line_state_addr(void)
{
  return g_Line_state;
}
