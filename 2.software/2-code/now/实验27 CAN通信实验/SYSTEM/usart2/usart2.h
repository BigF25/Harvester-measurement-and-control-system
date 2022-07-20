#ifndef __USART2_H
#define __USART2_H			 
#include "sys.h"	 								  	  	
														 
void USART2_Init(uint32_t bound);
void USART2_Send_Data(char *buf,uint16_t len);

#endif	   
