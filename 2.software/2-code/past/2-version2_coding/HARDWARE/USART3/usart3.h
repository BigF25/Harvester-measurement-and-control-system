#ifndef __USART3_H
#define __USART3_H			 
#include "sys.h"	 								  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//USART3驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
	  	
extern u8 USART3_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern u8 USART3_RX_CNT;   			//接收到的数据长度

//模式控制
#define USART3_TX_EN		PGout(8)	//485模式控制.0,接收;1,发送.
//如果想串口中断接收，设置EN_USART2_RX为1，否则设置为0
#define EN_USART3_RX 	1			//0,不接收;1,接收.

														 
void USART3_Init(u32 bound);
void USART3_Send_Data(u8 *buf,u8 len);
void USART3_Receive_Data(u8 *buf,u8 *len);		 
#endif	   
















