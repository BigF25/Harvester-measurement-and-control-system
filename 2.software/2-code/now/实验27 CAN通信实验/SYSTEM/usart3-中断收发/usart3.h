#ifndef __USART3_H
#define __USART3_H			 
#include "sys.h"	 								  

//模式控制
#define USART3_TX_EN		PGout(8)	//485模式控制.0,接收;1,发送.
//如果想串口中断接收，设置EN_USART2_RX为1，否则设置为0
#define EN_USART3_RX 	1			//0,不接收;1,接收.

//extern u8 USART3_RX_BUF[64];  	//接收缓冲,最大64个字节
//extern u8 USART3_RX_CNT;			//接收到的数据长度	
													 
void USART3_Init(u32 bound);
void USART3_Send_Data(u8 *buf,u8 len);
#endif	   
















