#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

u8 rec_can_value(u32 *resut_int_5801, u16 *resut_char_7017);
void my_USART_Send_Data(u8 *buf,u8 len);
void TIM3_Int_Init(u16 arr,u16 psc);
void getsendmsg_5801(u8* temp, u8 num,u8 screenID, u8*need);
void getsendmsg_7017(u8* temp, u8 num,u8 screenID, u8*need);
void TIM3_IRQHandler(void);


#endif
