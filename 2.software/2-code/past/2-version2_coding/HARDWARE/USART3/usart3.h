#ifndef __USART3_H
#define __USART3_H			 
#include "sys.h"	 								  
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//USART3���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
	  	
extern u8 USART3_RX_BUF[64]; 		//���ջ���,���64���ֽ�
extern u8 USART3_RX_CNT;   			//���յ������ݳ���

//ģʽ����
#define USART3_TX_EN		PGout(8)	//485ģʽ����.0,����;1,����.
//����봮���жϽ��գ�����EN_USART2_RXΪ1����������Ϊ0
#define EN_USART3_RX 	1			//0,������;1,����.

														 
void USART3_Init(u32 bound);
void USART3_Send_Data(u8 *buf,u8 len);
void USART3_Receive_Data(u8 *buf,u8 *len);		 
#endif	   
















