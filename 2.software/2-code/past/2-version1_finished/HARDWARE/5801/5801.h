#ifndef __5801_H
#define __5801_H	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


void Init_5801(u8 address, u8 value);

u8 rec_5801_ImpulseValue(uint32_t ID, u32 resut_int[8]);//��ȡ��ȡƵ��ֵ

u8 rec_5801_CountValue(uint32_t ID, u32 resut_int[8]);//��ȡ��ȡƵ��ֵ

u8 Set_5801_Frequency_Type(uint32_t id, uint8_t type);//����ģ��Ϊ��Ƶ�����ģʽ��
                                                      //��type��ֵȷ��ͨ���ľ���ģʽ
u8 Set_5801_ClearCount(uint32_t id, u8 count_clear[8]);//�������ͨ��

typedef uint8_t EMPPassageway;
typedef uint8_t EMPFiltertime;
u8 Set_5801_Filter_Time(uint32_t id, EMPPassageway Passageway, EMPFiltertime Filtertime);//����ģ���Ƶͨ���˲�ʱ��
#define Passageway_CF0 0x01 //CF0 
#define Passageway_CF1 0x02 //CF1 
#define Passageway_CF2 0x03 //CF2 
#define Passageway_CF3 0x04 //CF3 
#define Passageway_CF4 0x05 //CF4 
#define Passageway_CF5 0x06 //CF5 
#define Passageway_CF6 0x07 //CF6 
#define Passageway_CF7 0x08 //CF7 

#define Filtertime_0  0x00  //0us
#define Filtertime_1  0x01  //0.024us
#define Filtertime_2  0x02  //0.048us
#define Filtertime_3  0x03  //0.096us
#define Filtertime_4  0x04  //0.14us
#define Filtertime_5  0x05  //0.19us
#define Filtertime_6  0x06  //0.28us
#define Filtertime_7  0x07  //0.38us
#define Filtertime_8  0x08  //0.57us
#define Filtertime_9  0x09  //0.76us
#define Filtertime_10 0x0A  //0.95us
#define Filtertime_11 0x0B  //1.14us
#define Filtertime_12 0x0C  //1.52us
#define Filtertime_13 0x0D  //1.90us
#define Filtertime_14 0x0E  //2.28us
#define Filtertime_15 0x0F  //3.04us

typedef uint8_t EMPPassageway;
u8 Set_5801_Excessive_Time(uint32_t id, EMPPassageway Passageway, uint8_t Excessivetime);//����ģ���Ƶ��ʱʱ�䣨����Ϊ��СƵ�ʵ����ڣ�
#define Passageway_CF0 0x01 //CF0 
#define Passageway_CF1 0x02 //CF1 
#define Passageway_CF2 0x03 //CF2 
#define Passageway_CF3 0x04 //CF3 
#define Passageway_CF4 0x05 //CF4 
#define Passageway_CF5 0x06 //CF5 
#define Passageway_CF6 0x07 //CF6 
#define Passageway_CF7 0x08 //CF7 

#endif 