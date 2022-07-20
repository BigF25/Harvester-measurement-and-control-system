#ifndef __3402_H
#define __3402_H	
#include "sys.h" 
	 


void Init_3402(uint32_t id);

u8 Set_3402_Analogoutput(uint32_t id, u16 ao_0, u16 ao_1);//AOģ�������

typedef uint8_t Output_type;
typedef uint8_t Output_pin;
u8 Set_3402_AOoutput_type(uint32_t id, Output_pin pin, Output_type type);//����ģ���AO�������
#define type_V 0x02 //��ѹ���0-10V
#define type_I0 0x00 //�������0-20mA
#define type_I1 0x01 //�������4-40mA
#define Output_pin_AO0 0x01
#define Output_pin_AO1 0x02

#endif 
