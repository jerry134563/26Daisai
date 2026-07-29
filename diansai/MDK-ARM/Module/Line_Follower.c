#include "Line_Follower.h"
uint8_t g_Line_state[8]={0};

uint8_t*read_Line_state(void)
{
  g_Line_state[0]=bsp_read_gpio(RED1_GPIO_Port,RED1_Pin);
	g_Line_state[1]=bsp_read_gpio(RED2_GPIO_Port,RED2_Pin);
	g_Line_state[2]=bsp_read_gpio(RED3_GPIO_Port,RED3_Pin);
	g_Line_state[3]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);
	g_Line_state[4]=bsp_read_gpio(RED5_GPIO_Port,RED5_Pin);
	g_Line_state[5]=bsp_read_gpio(RED6_GPIO_Port,RED6_Pin);
	g_Line_state[6]=bsp_read_gpio(RED7_GPIO_Port,RED7_Pin);
	g_Line_state[7]=bsp_read_gpio(RED8_GPIO_Port,RED8_Pin);
  return g_Line_state;
}
