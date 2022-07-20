#include "sys.h"
#include "stdio.h"
#include "string.h"
#include "log.h"

#include "delay.h"
#include "usart.h"
#include "rtc.h"

#include "translate.h"

#include "queue.h"	   
#include "SDCardFile.h"  
#include "can.h"
#include "CANdevice.h"

#include "queue2.h"	   
#include "COMscreen.h"

#include "atk_m750.h"

int main(void)
{ 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    				//初始化延时函数
	uart_init(115200);					//初始化串口波特率为115200
	My_RTC_Init();							//RTC初始化

	//////////////数据队列初始化/////////////////////////////////////////////////////////////////////////////////////
	queue_Init();
	queue2_Init();
	
	////////////串口屏初始化///////////////////////////////////////////////////////////////////////////////////////////
	COMscreen_Init();
	
	////////////4GDTU初始化///////////////////////////////////////////////////////////////////////////////////////////
	atkm_Init();
	
	/////////////SD卡文件系统初始化/////////////////////////////////////////////////////////////////////////////////////////
	SDCardFile_Init();
	
	//////////////CAN通信/////////////////////////////////////////////////////////////////////////////////////////////
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);
	
	//////////////CAN设备通信/////////////////////////////////////////////////////////////////////////////////////////////
	Init_3402(ADDRESS_3402);
	Init_4055(ADDRESS_4055);
	Init_5801(ADDRESS_5801_1);
	Init_5801(ADDRESS_5801_2);
	Init_7017(ADDRESS_7017);

	delay_ms(100);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@InitFinsh@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\r\n");
	extern uint8_t ReceiveBuff_USART3[30];	//接收数据缓冲区
	while(1)
	{
//	  printf("ReceiveBuff:");
//	  for(uint8_t i=0; i<14; i++)
//			printf("%02x ", ReceiveBuff_USART3[i]);
//	  printf("\n\r");
		static uint32_t i = 0;
		i++;
		Translate_CANMsg2TempStruct();
		WriteDataToSDCard();
		COMscreen_REV_Cmd();
		delay_ms(1);
		if(i%300==0)
		{	
			UpdateComScreen_ALL();
		}
		if(i%1000==0)
		{	
			send_atkm750_data();
		}
	}	
}
