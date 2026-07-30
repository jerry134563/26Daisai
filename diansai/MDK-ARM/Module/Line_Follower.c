#include "Line_Follower.h"
#include <stdlib.h>
uint8_t g_Line_state[8]={0};
uint8_t g_continuous_Line_state[8]={0};
/// g_continuous_Line_state
uint8_t read_step = 0;

/*连续判断算法*/
void line_continuous_filter(void){
    uint8_t max_len = 0;        // 最长连续1长度
    uint8_t best_start = 0;     // 最长段起始位置
    uint8_t best_end = 0;       // 最长段结束位置

    uint8_t cur_start = 0;
    uint8_t cur_len = 0;
    uint8_t in_block = 0;       // 是否正在连续1区间内
	  for(uint8_t i = 0; i < 8; i++)
    {
        if(g_Line_state[i] == black)
        {
            if(!in_block)
            {
                // 进入新一段连续1
                cur_start = i;
                cur_len = 1;
                in_block = 1;
            }
            else
            {
                cur_len++;
            }
        }
        else
        {
            if(in_block)
            {
                // 连续1区间结束，对比是否为最长
                if(cur_len > max_len)
                {
                    max_len = cur_len;
                    best_start = cur_start;
                    best_end = i - 1;
                }else if(cur_len == max_len){
									if(abs(best_start-4)>abs(cur_start-4)){
                    max_len = cur_len;
                    best_start = cur_start;
                    best_end = i - 1;
									}
								}
                in_block = 0;
            }
        }
    }
    // 循环结束后，还要判断最后一段还未闭合的连续1（末尾以1结尾场景）
    if(in_block)
    {
        if(cur_len > max_len)
        {
            max_len = cur_len;
            best_start = cur_start;
            best_end = 8 - 1;
        }
				else if(cur_len == max_len)
        {
            int dist_old = abs((int)best_start - 4);
            int dist_new = abs((int)cur_start - 4);
            if(dist_old > dist_new)
            {
                best_start = cur_start;
                best_end = 7;
            }
        }
    }
    // 将最优区间填充为1,rest is 0
    if(max_len > 0)
    {
        for(uint8_t i = 0; i < best_start; i++)
        {
            g_continuous_Line_state[i] = white;
        }
        for(uint8_t i = best_start; i <= best_end; i++)
        {
            g_continuous_Line_state[i] = black;
        }
        for(uint8_t i = best_end+1; i < 8; i++)
        {
            g_continuous_Line_state[i] = white;
        }
    }else{
				//无黑线，全部置白线
				for(uint8_t i=0;i<8;i++)
					g_continuous_Line_state[i] = white;
		}
}

void read_Line_state(void)
{
  g_Line_state[0]=bsp_read_gpio(RED1_GPIO_Port,RED1_Pin);
	g_Line_state[1]=bsp_read_gpio(RED2_GPIO_Port,RED2_Pin);
	g_Line_state[2]=bsp_read_gpio(RED3_GPIO_Port,RED3_Pin);
	g_Line_state[3]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);
	g_Line_state[4]=bsp_read_gpio(RED5_GPIO_Port,RED5_Pin);
	g_Line_state[5]=bsp_read_gpio(RED6_GPIO_Port,RED6_Pin);
	g_Line_state[6]=bsp_read_gpio(RED7_GPIO_Port,RED7_Pin);
	g_Line_state[7]=bsp_read_gpio(RED8_GPIO_Port,RED8_Pin);
	line_continuous_filter();
}
uint8_t*get_g_Line_state_addr(void)
{
  return g_continuous_Line_state;
}

//void read_Line_state(void)
//{
//	switch(read_step){
//		case 0:
//	g_Line_state[0]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//000
//	bsp_set_gpio_high(W1_GPIO_Port,W1_Pin);	
//	read_step++;
//		break;
//		case 1:
//	g_Line_state[1]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//001
//	bsp_set_gpio_high(W2_GPIO_Port,W2_Pin);	
//	read_step++;
//		break;
//		case 2:
//	g_Line_state[3]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//011
//	bsp_set_gpio_low(W1_GPIO_Port,W1_Pin);	
//	read_step++;
//		break;
//		case 3:
//	g_Line_state[2]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//010
//	bsp_set_gpio_high(W3_GPIO_Port,W3_Pin);	
//	read_step++;
//		break;
//		case 4:
//	g_Line_state[6]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//110
//	bsp_set_gpio_high(W1_GPIO_Port,W1_Pin);	
//	read_step++;
//		break;
//		case 5:
//	g_Line_state[7]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//111
//	bsp_set_gpio_low(W2_GPIO_Port,W2_Pin);	
//	read_step++;
//		break;
//		case 6:
//	g_Line_state[5]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//101
//	bsp_set_gpio_low(W1_GPIO_Port,W1_Pin);	
//	read_step++;
//		break;
//		case 7:
//	g_Line_state[4]=bsp_read_gpio(RED4_GPIO_Port,RED4_Pin);//100
//	bsp_set_gpio_low(W3_GPIO_Port,W3_Pin);
//	read_step++;
//		break;
//		case 8:
//	line_continuous_filter();
//	read_step=0;
//		break;
//		default:
//	read_step=0;
//	} 
//}

//uint8_t*get_g_continuous_Line_state_addr(void)
//{
//  return g_continuous_Line_state;
//}

