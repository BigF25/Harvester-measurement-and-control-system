#ifndef __4055_H
#define __4055_H	
#include "sys.h" 
	 


void Init_4055(uint32_t id);

u8 Set_4055_Switchoutput(uint32_t id, u8 digital_output);//���������
                                                         //д��1����͵�ƽ��д��0���������������Ϊ�ߵ�ƽ
typedef uint8_t type_DO;
u8 Set_4055_Safety_output(uint32_t id, u8 type_DO);//����ģ���D0��ȫֵ���
#define TYPE_DO0 0x01
#define TYPE_DO1 0x02
#define TYPE_DO2 0x04
#define TYPE_DO3 0x08
#define TYPE_DO4 0x10
#define TYPE_DO5 0x20
#define TYPE_DO6 0x40
#define TYPE_DO7 0x80
                                    //�趨Ϊ0ʱ��ʾ��ʹ�ܰ�ȫ�������
#endif
