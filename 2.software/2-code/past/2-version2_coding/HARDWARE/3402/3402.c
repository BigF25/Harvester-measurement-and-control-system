#include "3402.h"
#include "can.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"

void Init_3402(uint32_t id)
{
	Set_3402_AOoutput_type(id, Output_pin_AO0, type_V);delay_ms(100);
	Set_3402_AOoutput_type(id, Output_pin_AO1, type_V);delay_ms(100);
//	enable_TPDO(id, _TPDO1, TPDOCOMMAND_NO);delay_ms(100);
//	enable_TPDO(id, _TPDO2, TPDOCOMMAND_NO);delay_ms(100);
//	enable_TPDO(id, _TPDO3, TPDOCOMMAND_NO);delay_ms(100);
//	enable_TPDO(id, _TPDO4, TPDOCOMMAND_NO);delay_ms(100);
}
u8 Set_3402_Analogoutput(uint32_t id, u16 ao_0, u16 ao_1)
{
	u8 mbox;
	u8 ao_00, ao_01, ao_10, ao_11;
	ao_00 = ao_0 & 0x00ff; 	//低八位
	ao_01 = ao_0 >> 8;    	//高八位
	ao_10 = ao_1 & 0x00ff; 	//低八位
	ao_11 = ao_1 >> 8;     	//高八位
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x200+id;	 // 标准标识符为0
  TxMessage.ExtId=0x200+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=5;	
  TxMessage.Data[0]=0x03;      
  TxMessage.Data[1]=ao_00; 
  TxMessage.Data[2]=ao_01;
  TxMessage.Data[3]=ao_10;
  TxMessage.Data[4]=ao_11; 
  mbox= CAN_Transmit(CAN1, &TxMessage);
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
  if(i>=0XFFF)return 1;
  return 0;
}

u8 Set_3402_AOoutput_type(uint32_t id, Output_pin pin, Output_type type)
{
	u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // 标准标识符为0
  TxMessage.ExtId=0x600+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2F;      
  TxMessage.Data[1]=0x09; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=pin;
  TxMessage.Data[4]=type; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
  mbox= CAN_Transmit(CAN1, &TxMessage);
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
  if(i>=0XFFF)return 1;
  return 0;
}
