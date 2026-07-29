#include "bsp_usart.h"
#define UART_RX_BUF_SIZE  64    /* 串口 DMA 接收缓冲区大小 */
#define usart_idle_call_back() void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)

/* === 各串口 DMA 接收缓冲区 === */
uint8_t s_rx_buf_u8[UART_RX_BUF_SIZE] = {0};
uint8_t s_rx_buf_u7[UART_RX_BUF_SIZE] = {0};
volatile float Yaw_atk901=0;
volatile float Yaw_speed=0;

/* 格式化输出缓冲区 */
static unsigned char s_uart_tx_buf[300];


void bsp_usart_init(void)
{
   HAL_UARTEx_ReceiveToIdle_DMA(&huart8, s_rx_buf_u8, UART_RX_BUF_SIZE);
	 HAL_UARTEx_ReceiveToIdle_DMA(&huart7, s_rx_buf_u7, UART_RX_BUF_SIZE);

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
	   else if(huart==&huart7)
	if(huart== &huart7)
  {
    // 处理数据    	
	  uint8_t sum=0;			  	  	  

    		  if(s_rx_buf_u7[0]==0x55&&s_rx_buf_u7[1]==0x53)
	  {    
			 sum=0x55+0x53;
		   for(uint8_t i = 6; i < 10; i++)
			 {
			    sum+=s_rx_buf_u7[i];
			 }
			 if(sum==s_rx_buf_u7[10])
			 {	    
           if(s_rx_buf_u7[7]!=0||s_rx_buf_u7[6]!=0)				 
		       {
						 Yaw_atk901=(float)((int16_t)(s_rx_buf_u7[7]<<8)|s_rx_buf_u7[6])/32768*180;
					 }
				
			 } 
		 }
      else if(s_rx_buf_u7[0]==0x55&&s_rx_buf_u7[1]==0x52)
			{
			  sum=0x55+0x52;
				 for(uint8_t i = 4; i < 10; i++)
			 {
			    sum+=s_rx_buf_u7[i];
			 }
			 if(sum==s_rx_buf_u7[10])
			 {	    
        
						 Yaw_speed=(float)((int16_t)(s_rx_buf_u7[7]<<8)|s_rx_buf_u7[6])/32768*180;			
			 } 						
			}
	  // 重新开启DMA	  
	  HAL_UARTEx_ReceiveToIdle_DMA(&huart7,s_rx_buf_u7, 11);     
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

	__HAL_UART_CLEAR_OREFLAG(huart); 
	__HAL_UART_CLEAR_FEFLAG(huart);
	__HAL_UART_CLEAR_NEFLAG(huart);
}












