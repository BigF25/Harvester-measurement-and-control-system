#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//CAN驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/7
//版本：V1.0 
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

	
//CAN1接收RX0中断使能
#define CAN1_RX0_INT_ENABLE	0		//0,不使能;1,使能.								    
										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
 
u8 CAN1_Send_Msg(u8* msg,u8 len);						//发送数据

u8 CAN1_Receive_Msg(u8 *buf);							//接收数据

void CAN1_send_adc_msg(u8 channel);
typedef u8 TPDOCommand;
typedef u8 TPDOChannel;
u8 enable_TPDO(uint32_t id, TPDOChannel channel, TPDOCommand command);
#define TPDOCOMMAND_YES 0xFF
#define TPDOCOMMAND_NO 	0x01
#define TPDO1 	0x01
#define TPDO2 	0x02
#define TPDO3 	0x03
#define TPDO4 	0x04
u8 lapsetime_TPDO(uint32_t id, TPDOChannel channel, u16 command);
#define _TPDO1 	0x00
#define _TPDO2 	0x01
#define _TPDO3 	0x02
#define _TPDO4 	0x03
u8 event_TPDO(uint32_t id, TPDOChannel channel, u16 command);


#endif

















