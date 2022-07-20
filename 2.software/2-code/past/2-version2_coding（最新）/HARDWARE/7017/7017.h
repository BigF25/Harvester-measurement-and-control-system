#ifndef __7017_H
#define __7017_H	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ADC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

void Init_7017(uint32_t ID);

u8 rec_7017_AiValue(uint32_t ID, u16 resut_char[8]);//读取 AI 模拟量输入
u8 rec_7017_msg(uint32_t *id, u8 *buf);
u8 send_7017_msg(uint32_t id);

u8 set_7017_DOBit(uint32_t id, u8 bit);//设置 DO 开关量输出

typedef uint8_t AiType;
u8 Set_7017_AiType(uint32_t id, AiType type);//设置模块的 AIN 采集类型 
#define  AiType_10V 	0	//±10V输入
#define  AiType_5V 		1	//±5V输入
#define  AiType_20MA 	2	//0~20ma输入

typedef uint8_t AiChannel;
u8 Set_7017_AiEnable(uint32_t id, AiChannel channel);//设置模块的 AI 采集通道使能
#define  AiChannel_0 		0x01	//通道0
#define  AiChannel_1 		0x02	//通道1
#define  AiChannel_2 		0x04	//通道2
#define  AiChannel_3 		0x08	//通道3
#define  AiChannel_4 		0x10	//通道4
#define  AiChannel_5 		0x20	//通道5
#define  AiChannel_6 		0x40	//通道6
#define  AiChannel_7 		0x80	//通道7
#define  AiChannel_ALL 	0xFF	//通道7


typedef uint8_t AiDataType;
u8 Set_7017_AiDataType(uint32_t id, AiDataType datatype);//设置模块 AI 的数据格式 
#define  ADCVALUE 			1	//ADC 数据类型
#define  COMPLEMENT 		2 //补码
#define  ANALOG_VALUE 	3	//模拟量数据
#define  PRECENTAGE 		4	//百分比数据

typedef uint8_t AiNum;
u8 Set_7017_AiNumberOfFilters(uint32_t id, AiNum Ainum);//设置模块的采集滤波次数 
#define AiNumOfFilters(x) x

#endif 















