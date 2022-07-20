//不同型号CAN模块的相同的操作指令
#include "CANdevice.h"
u8 enable_TPDO(uint32_t id, TPDOChannel channel, TPDOCommand command)
{

  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // 标准标识符为0
  TxMessage.ExtId=0x600+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2F;      
  TxMessage.Data[1]=channel; 
  TxMessage.Data[2]=0x18; 
  TxMessage.Data[3]=0x02; 
  TxMessage.Data[4]=command; 
  TxMessage.Data[5]=0x00; 
  TxMessage.Data[6]=0x00; 
	TxMessage.Data[7]=0x00; 
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
//设置间隔时间
//间隔时间内不要发送数据
u8 set_lapsetime_TPDO(uint32_t id, TPDOChannel channel, u16 time)
{
	u8 low,high;
	time = time*10; //单位0.1us
	low = time & 0x00ff; 	//低八位
	high = time >> 8;    	//高八位
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // 标准标识符为0
  TxMessage.ExtId=0x600+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=channel; 
  TxMessage.Data[2]=0x18; 
  TxMessage.Data[3]=0x03; 
  TxMessage.Data[4]=low; 
  TxMessage.Data[5]=high; 
  TxMessage.Data[6]=0x00; 
	TxMessage.Data[7]=0x00; 
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
u8 read_lapsetime_TPDO(uint32_t id, TPDOChannel channel)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // 标准标识符为0
  TxMessage.ExtId=0x600+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x40;      
  TxMessage.Data[1]=channel; 
  TxMessage.Data[2]=0x18; 
  TxMessage.Data[3]=0x03; 
  TxMessage.Data[4]=0x00; 
  TxMessage.Data[5]=0x00; 
  TxMessage.Data[6]=0x00; 
	TxMessage.Data[7]=0x00; 
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
//设置事件时间
//间隔时间过后，如果数据发生变化，马上发送数据；否则事件时间过后发送数据。
u8 event_TPDO(uint32_t id, TPDOChannel channel, u16 time)
{
	u8 low,high;
	low = time & 0x00ff; 	//低八位
	high = time >> 8;    	//高八位
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // 标准标识符为0
  TxMessage.ExtId=0x600+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=channel; 
  TxMessage.Data[2]=0x18; 
  TxMessage.Data[3]=0x05; 
  TxMessage.Data[4]=low; 
  TxMessage.Data[5]=high; 
  TxMessage.Data[6]=0x00; 
	TxMessage.Data[7]=0x00; 
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
//迫使强制成功发送需要发送的报文到发送邮箱
//但是尝试0xFFF此后 防止死循环退出
u8 CANdevice_sendmsg_force(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{
	u8 mbox;
	u8 state=SendMsg_Force_NO;
	u16 i=0;
	while(1){
		mbox = CAN_Transmit(CAN1, TxMessage);
		//printf("mbox=%d\t%x\r\n",mbox,TxMessage->StdId);
		//邮箱编号不是NoMailBox，则说明发送成功
		
		if(mbox!=CAN_TxStatus_NoMailBox) 
		{
			state = SendMsg_Force_OK;
			break;
		}
		//否则，重新发送，但是避免死循环，在尝试发送0xFFF次后，强制退出，返回发送错误状态
		else if(mbox==CAN_TxStatus_NoMailBox && i<0xFFF)
		{
			state = SendMsg_Force_NO;
			i++;
		}
	}
	return state;
}
