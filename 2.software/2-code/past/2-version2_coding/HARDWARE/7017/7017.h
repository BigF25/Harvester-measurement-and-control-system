#ifndef __7017_H
#define __7017_H	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

void Init_7017(uint32_t ID);

u8 rec_7017_AiValue(uint32_t ID, u16 resut_char[8]);//��ȡ AI ģ��������
u8 rec_7017_msg(uint32_t *id, u8 *buf);
u8 send_7017_msg(uint32_t id);

u8 set_7017_DOBit(uint32_t id, u8 bit);//���� DO ���������

typedef uint8_t AiType;
u8 Set_7017_AiType(uint32_t id, AiType type);//����ģ��� AIN �ɼ����� 
#define  AiType_10V 	0	//��10V����
#define  AiType_5V 		1	//��5V����
#define  AiType_20MA 	2	//0~20ma����

typedef uint8_t AiChannel;
u8 Set_7017_AiEnable(uint32_t id, AiChannel channel);//����ģ��� AI �ɼ�ͨ��ʹ��
#define  AiChannel_0 		0x01	//ͨ��0
#define  AiChannel_1 		0x02	//ͨ��1
#define  AiChannel_2 		0x04	//ͨ��2
#define  AiChannel_3 		0x08	//ͨ��3
#define  AiChannel_4 		0x10	//ͨ��4
#define  AiChannel_5 		0x20	//ͨ��5
#define  AiChannel_6 		0x40	//ͨ��6
#define  AiChannel_7 		0x80	//ͨ��7
#define  AiChannel_ALL 	0xFF	//ͨ��7


typedef uint8_t AiDataType;
u8 Set_7017_AiDataType(uint32_t id, AiDataType datatype);//����ģ�� AI �����ݸ�ʽ 
#define  ADCVALUE 			1	//ADC ��������
#define  COMPLEMENT 		2 //����
#define  ANALOG_VALUE 	3	//ģ��������
#define  PRECENTAGE 		4	//�ٷֱ�����

typedef uint8_t AiNum;
u8 Set_7017_AiNumberOfFilters(uint32_t id, AiNum Ainum);//����ģ��Ĳɼ��˲����� 
#define AiNumOfFilters(x) x

#endif 















