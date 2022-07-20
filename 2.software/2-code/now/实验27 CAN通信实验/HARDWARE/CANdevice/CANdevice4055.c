//不同型号CAN模块的各自的操作指令
#include "CANdevice4055.h"
#include "CANdevice.h"


void Init_4055(uint32_t id)
{
	enable_TPDO(id, TPDO_CH1, TPDOCOMMAND_NO);
	Set_4055_SaftyOutput_Ena(id, 0x00);
}

u8 Set_4055_Switchoutput(uint32_t id, u8 digital_output)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x200+id;	 // 标准标识符为0
  TxMessage.ExtId=0x200+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=1;
  TxMessage.Data[0] = digital_output;      
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}

u8 Set_4055_SaftyOutput_Ena(uint32_t id, u8 type_DO)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // 标准标识符为0
  TxMessage.ExtId=0x600+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2F;
  TxMessage.Data[1]=0x01;
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=type_DO;
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
