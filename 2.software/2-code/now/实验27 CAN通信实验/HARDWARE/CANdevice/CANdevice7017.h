#ifndef __CANdevice7017_H
#define __CANdevice7017_H	
#include "sys.h" 

//��ʼ������
void Init_7017(uint32_t id);

//��ȡ AI ģ��������
u8 rec_7017_AiValue(uint32_t id, u16 resut_char[8]);

//���� DO ���������
u8 set_7017_DOBit(uint32_t id, u8 bit);

//����ģ��� AIN �ɼ����� 
typedef uint8_t AiType;
#define  AiType_10V 	0	//��10V����
#define  AiType_5V 		1	//��5V����
#define  AiType_20MA 	2	//0~20ma����
u8 Set_7017_AiType(uint32_t id, AiType type);

//����ģ��� AI �ɼ�ͨ��ʹ��
typedef uint8_t AiChannel;
#define  AiChannel_0 		0x01	//ͨ��0
#define  AiChannel_1 		0x02	//ͨ��1
#define  AiChannel_2 		0x04	//ͨ��2
#define  AiChannel_3 		0x08	//ͨ��3
#define  AiChannel_4 		0x10	//ͨ��4
#define  AiChannel_5 		0x20	//ͨ��5
#define  AiChannel_6 		0x40	//ͨ��6
#define  AiChannel_7 		0x80	//ͨ��7
#define  AiChannel_ALL 	0xFF	//ͨ��7
u8 Set_7017_AiEnable(uint32_t id, AiChannel channel);

//����ģ�� AI �����ݸ�ʽ 
typedef uint8_t AiDataType;
#define  ADCVALUE 			1	//ADC ��������
#define  COMPLEMENT 		2 //����
#define  ANALOG_VALUE 	3	//ģ��������
#define  PRECENTAGE 		4	//�ٷֱ�����
u8 Set_7017_AiDataType(uint32_t id, AiDataType datatype);

//����ģ��Ĳɼ��˲�����
typedef uint8_t AiNum;
#define AiNumOfFilters(x) x
u8 Set_7017_AiNumberOfFilters(uint32_t id, AiNum Ainum); 

#endif 















