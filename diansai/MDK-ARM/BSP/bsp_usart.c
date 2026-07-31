#include "bsp_usart.h"
#define UART_RX_BUF_SIZE  64    /* 串口 DMA 接收缓冲区大小 */
#define usart_idle_call_back() void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)

/* === 各串口 DMA 接收缓冲区 === */
uint8_t s_rx_buf_u8[UART_RX_BUF_SIZE] = {0};
uint8_t s_rx_buf_u7[UART_RX_BUF_SIZE] = {0};
uint8_t s_rx_buf_u2[UART_RX_BUF_SIZE] = {0};

volatile float Yaw_atk901=0;
volatile float Yaw_speed=0;
volatile float ACC_x=0;
volatile float ACC_y=0;
volatile float ACC_z=0;
volatile uint16_t ball_x=0;
volatile uint16_t ball_y=0;

/* 格式化输出缓冲区 */
static unsigned char s_uart_tx_buf[300];


void bsp_usart_init(void)
{
   HAL_UARTEx_ReceiveToIdle_DMA(&huart8, s_rx_buf_u8, UART_RX_BUF_SIZE);
	 HAL_UARTEx_ReceiveToIdle_DMA(&huart7, s_rx_buf_u7, UART_RX_BUF_SIZE);
	 HAL_UARTEx_ReceiveToIdle_DMA(&huart2, s_rx_buf_u2, UART_RX_BUF_SIZE);  

	__HAL_UART_CLEAR_IDLEFLAG(&huart5); 											// 清除IDLE标志
	__HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE); 							// 使能串UART1 IDLE中断
  HAL_UART_Receive_DMA(&huart5, (uint8_t *)rxCmd, CMD_LEN); // 开启DMA接收模式
}


void bsp_usart8_printf(const char *format, ...)
{
    uint16_t len;
    va_list args;
    va_start(args, format);
    len = vsnprintf((char *)s_uart_tx_buf, sizeof(s_uart_tx_buf), (char *)format, args);
    va_end(args);
    HAL_UART_Transmit_DMA(&huart8, s_uart_tx_buf, len);
}

void bsp_usart_send(UART_HandleTypeDef*usart,uint8_t *data, uint16_t len)
{
    HAL_UART_Transmit_DMA(usart, data, len);
}

 
/* === 缓冲区指针访问（供 DMA 和模块层使用） === */

uint8_t *bsp_usart_get_rx_buf_u8(void) { return s_rx_buf_u8; }

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
	{
   if(huart==&huart8)
   {
      HAL_UARTEx_ReceiveToIdle_DMA(&huart8, s_rx_buf_u8, UART_RX_BUF_SIZE);
   }
	if(huart== &huart7)     // 处理数据    	
   {		 
	  uint8_t sum=0;			  	  	  
	   if(s_rx_buf_u7[0]==0x55&&s_rx_buf_u7[1]==0x55)
	  {
	     if(s_rx_buf_u7[2]==1)
		 {
		   for(uint8_t i = 0; i < 10; i++)
			 {
			    sum+=s_rx_buf_u7[i];
			 }
			 if(sum==s_rx_buf_u7[10])
			 {	       
		       Yaw_atk901=(float)((int16_t)(s_rx_buf_u7[9]<<8)|s_rx_buf_u7[8])/32768*180;				
			 }		   
		 }		
       if(s_rx_buf_u7[13]==3)
		 {
		    for(uint8_t j = 0; j < 15; j++)
			 {
			      sum+=s_rx_buf_u7[j+13];
           if(sum==s_rx_buf_u7[28])
			 {	       
		       ACC_x=(float)((int16_t)(s_rx_buf_u7[16]<<8)|s_rx_buf_u7[15])/32768*4;				
			 }				 
			 }
		 }
	 }
      HAL_UARTEx_ReceiveToIdle_DMA(&huart7, s_rx_buf_u7, UART_RX_BUF_SIZE);  
   }
	if(huart== &huart2)
	 {
	   
		 if(s_rx_buf_u2[0]==0xfe&&s_rx_buf_u2[5]==0xff)
		 {
		   ball_x=((uint16_t)s_rx_buf_u2[2]<<8)|s_rx_buf_u2[1];
			 ball_y=((uint16_t)s_rx_buf_u2[4]<<8)|s_rx_buf_u2[3];
		 }
		 
		 HAL_UARTEx_ReceiveToIdle_DMA(&huart2, s_rx_buf_u2, UART_RX_BUF_SIZE);  
	 }	 
  }

 

float get_yaw_atk901(void)
{
 return Yaw_atk901;
}
float get_yaw_speed(void)
{
 return Yaw_speed;
}
float get_Acc_x(void)
{
 return ACC_x;
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

	 if(huart== &huart7)
	{	  
     HAL_UARTEx_ReceiveToIdle_DMA(&huart7, s_rx_buf_u7, UART_RX_BUF_SIZE);
	}
	else if(huart== &huart8)
	{
     HAL_UARTEx_ReceiveToIdle_DMA(&huart8, s_rx_buf_u8, UART_RX_BUF_SIZE);
	}
		else if(huart== &huart2)
	{
     HAL_UARTEx_ReceiveToIdle_DMA(&huart2, s_rx_buf_u2, UART_RX_BUF_SIZE);
	}

	__HAL_UART_CLEAR_OREFLAG(huart); 
	__HAL_UART_CLEAR_FEFLAG(huart);
	__HAL_UART_CLEAR_NEFLAG(huart);
}

uint8_t*get_s_rx_buf_u8(void)
{
  return s_rx_buf_u8;
}
uint8_t get_ball_x(void)
{
  return ball_x;
}









