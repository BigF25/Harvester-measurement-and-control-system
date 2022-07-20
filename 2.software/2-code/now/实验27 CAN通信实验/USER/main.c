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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    				//��ʼ����ʱ����
	uart_init(115200);					//��ʼ�����ڲ�����Ϊ115200
	My_RTC_Init();							//RTC��ʼ��

	//////////////���ݶ��г�ʼ��/////////////////////////////////////////////////////////////////////////////////////
	queue_Init();
	queue2_Init();
	
	////////////��������ʼ��///////////////////////////////////////////////////////////////////////////////////////////
	COMscreen_Init();
	
	////////////4GDTU��ʼ��///////////////////////////////////////////////////////////////////////////////////////////
	atkm_Init();
	
	/////////////SD���ļ�ϵͳ��ʼ��/////////////////////////////////////////////////////////////////////////////////////////
	SDCardFile_Init();
	
	//////////////CANͨ��/////////////////////////////////////////////////////////////////////////////////////////////
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);
	
	//////////////CAN�豸ͨ��/////////////////////////////////////////////////////////////////////////////////////////////
	Init_3402(ADDRESS_3402);
	Init_4055(ADDRESS_4055);
	Init_5801(ADDRESS_5801_1);
	Init_5801(ADDRESS_5801_2);
	Init_7017(ADDRESS_7017);

	delay_ms(100);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@InitFinsh@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\r\n");
	extern uint8_t ReceiveBuff_USART3[30];	//�������ݻ�����
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
