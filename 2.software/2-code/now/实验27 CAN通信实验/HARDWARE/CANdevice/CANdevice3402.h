#ifndef __CANdevice3402_H
#define __CANdevice3402_H	
#include "sys.h" 


//初始化函数
void Init_3402(uint32_t id);

//AO模拟量输出
u8 Set_3402_Analogoutput(uint32_t id, u16 ao_0, u16 ao_1);

//设置模块的AO输出类型
typedef uint8_t Output_type;
typedef uint8_t Output_pin;
#define type_V 0x02 //电压输出0-10V
#define type_I0 0x00 //电流输出0-20mA
#define type_I1 0x01 //电流输出4-40mA
#define Output_pin_AO0 0x01
#define Output_pin_AO1 0x02
u8 Set_3402_AOoutput_type(uint32_t id, Output_pin pin, Output_type type);

//设置AI使能
u8 Set_3402_AI_Ena(uint32_t id);


#endif 
