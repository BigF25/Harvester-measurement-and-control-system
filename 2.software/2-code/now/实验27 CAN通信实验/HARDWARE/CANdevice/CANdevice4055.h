#ifndef __CANdevice4055_H
#define __CANdevice4055_H	
#include "sys.h" 
	 

//��ʼ������
void Init_4055(uint32_t id);

//���������
//д��1����͵�ƽ��д��0���������������Ϊ�ߵ�ƽ
u8 Set_4055_Switchoutput(uint32_t id, u8 digital_output);

//����ģ���D0��ȫֵ���
typedef uint8_t type_DO;
//�趨Ϊ 0 ʱ��ʾ��ʹ�ܰ�ȫ������ܡ�ͨ��������������Զ�������ÿ�� DO ͨ���Ŀ��أ���ͨ���ر�ʱ�����԰�ȫֵ�����
//��ȫʱ��Ͱ�ȫ���ֵ��ָ��ģ�������������趨�İ�ȫʱ��δ�ɹ�ͨ��ʱ��ģ���
//DO�����趨�İ�ȫ���ֵ����Ա��������豸�İ�ȫ������ģ���״̬�ָ�Ϊδ����״̬��
#define TYPE_DO0 0x01
#define TYPE_DO1 0x02
#define TYPE_DO2 0x04
#define TYPE_DO3 0x08
#define TYPE_DO4 0x10
#define TYPE_DO5 0x20
#define TYPE_DO6 0x40
#define TYPE_DO7 0x80
u8 Set_4055_SaftyOutput_Ena(uint32_t id, u8 type_DO);
                              
#endif
