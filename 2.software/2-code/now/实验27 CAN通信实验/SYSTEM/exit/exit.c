//管理所有中断函数的文件
#include "exit.h"	
#include "stdio.h"
#include "malloc.h"

#include "can.h"
#include "queue.h"

#include "usart3.h"
#include "queue2.h"

#if CAN1_RX0_INT_ENABLE	//使能RX0中断	    
void CAN1_RX0_IRQHandler(void)
{
	extern queue *myqueue;
	insert_queue(myqueue);
	CAN_Receive(CAN1, CAN_FIFO0, &myqueue->rear->data);//queue中加入数据
	RTC_GetDate(RTC_Format_BIN, &myqueue->rear->RTC_DateStruct);//queue加入时间戳
	RTC_GetTime(RTC_Format_BIN, &myqueue->rear->RTC_TimeStruct);
//	printf("\r\nThe queue length is :%d\r\n", get_queue_length(myqueue));//////////////////////////////////////////////////////
//	queue_print(myqueue);////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif

#if EN_USART3_RX   		//如果使能了接收   	  
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
	{
		u8 res = USART_ReceiveData(USART3);		//读取接收到的数据USART2->DR
		extern queue2 *myqueue2;
		insert_queue2(myqueue2);
		myqueue2->rear->buf = res;
	}
} 
#endif

