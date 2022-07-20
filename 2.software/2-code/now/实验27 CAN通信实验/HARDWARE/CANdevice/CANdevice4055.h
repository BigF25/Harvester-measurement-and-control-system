#ifndef __CANdevice4055_H
#define __CANdevice4055_H	
#include "sys.h" 
	 

//初始化函数
void Init_4055(uint32_t id);

//数字量输出
//写入1输出低电平，写入0输出由上拉电阻拉为高电平
u8 Set_4055_Switchoutput(uint32_t id, u8 digital_output);

//设置模块的D0安全值输出
typedef uint8_t type_DO;
//设定为 0 时表示不使能安全输出功能。通过配置软件还可以独立控制每个 DO 通道的开关，当通道关闭时，将以安全值输出。
//安全时间和安全输出值是指当模块与主机超过设定的安全时间未成功通信时，模块的
//DO将以设定的安全输出值输出以保护控制设备的安全，并将模块的状态恢复为未连接状态。
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
