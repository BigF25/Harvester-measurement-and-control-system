#ifndef __USART3_H
#define __USART3_H			 
#include "sys.h"	 								  	
														 
void USART3_Init(uint32_t bound);
void USART3_Send_Data(u8 *buf,u8 len);
		 
#endif	   

