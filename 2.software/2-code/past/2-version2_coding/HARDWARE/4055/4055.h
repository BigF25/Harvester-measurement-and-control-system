#ifndef __4055_H
#define __4055_H	
#include "sys.h" 
	 


void Init_4055(uint32_t id);

u8 Set_4055_Switchoutput(uint32_t id, u8 digital_output);//数字量输出
                                                         //写入1输出低电平，写入0输出由上拉电阻拉为高电平
typedef uint8_t type_DO;
u8 Set_4055_Safety_output(uint32_t id, u8 type_DO);//设置模块的D0安全值输出
#define TYPE_DO0 0x01
#define TYPE_DO1 0x02
#define TYPE_DO2 0x04
#define TYPE_DO3 0x08
#define TYPE_DO4 0x10
#define TYPE_DO5 0x20
#define TYPE_DO6 0x40
#define TYPE_DO7 0x80
                                    //设定为0时表示不使能安全输出功能
#endif
