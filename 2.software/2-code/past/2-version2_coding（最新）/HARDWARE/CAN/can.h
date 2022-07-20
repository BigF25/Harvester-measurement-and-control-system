#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//CAN���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.0 
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

	
//CAN1����RX0�ж�ʹ��
#define CAN1_RX0_INT_ENABLE	0		//0,��ʹ��;1,ʹ��.								    
										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
u8 CAN1_Send_Msg(u8* msg,u8 len);						//��������

u8 CAN1_Receive_Msg(u8 *buf);							//��������

void CAN1_send_adc_msg(u8 channel);
typedef u8 TPDOCommand;
typedef u8 TPDOChannel;
u8 enable_TPDO(uint32_t id, TPDOChannel channel, TPDOCommand command);
#define TPDOCOMMAND_YES 0xFF
#define TPDOCOMMAND_NO 	0x01
#define TPDO1 	0x01
#define TPDO2 	0x02
#define TPDO3 	0x03
#define TPDO4 	0x04
u8 lapsetime_TPDO(uint32_t id, TPDOChannel channel, u16 command);
#define _TPDO1 	0x00
#define _TPDO2 	0x01
#define _TPDO3 	0x02
#define _TPDO4 	0x03
u8 event_TPDO(uint32_t id, TPDOChannel channel, u16 command);


#endif

















