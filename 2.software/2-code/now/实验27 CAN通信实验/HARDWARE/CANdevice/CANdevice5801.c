//不同型号CAN模块的各自的操作指令

#include "CANdevice5801.h"
#include "CANdevice.h"


void Init_5801(uint32_t id)
{
	Set_5801_Frequency_Type(id, 0xFF);//0xFF所有通道设为测频率模式
	Set_5801_Filter_Time(id, Passageway_CF0, Filtertime_10);//设置通道0 1滤波时间
	Set_5801_Filter_Time(id, Passageway_CF1, Filtertime_10);//设置通道0 1滤波时间
	Set_5801_Filter_Time(id, Passageway_CF2, Filtertime_10);//设置通道0 1滤波时间
	Set_5801_Filter_Time(id, Passageway_CF3, Filtertime_10);//设置通道0 1滤波时间
	Set_5801_Filter_Time(id, Passageway_CF4, Filtertime_10);//设置通道0 1滤波时间
	Set_5801_Filter_Time(id, Passageway_CF5, Filtertime_10);//设置通道0 1滤波时间
	Set_5801_Filter_Time(id, Passageway_CF6, Filtertime_10);//设置通道0 1滤波时间
	Set_5801_Filter_Time(id, Passageway_CF7, Filtertime_10);//设置通道0 1滤波时间
	Set_5801_Excessive_Time(id, Passageway_CF0, 0x32);
	Set_5801_Excessive_Time(id, Passageway_CF1, 0x32);
	Set_5801_Excessive_Time(id, Passageway_CF2, 0x32);
	Set_5801_Excessive_Time(id, Passageway_CF3, 0x32);
	Set_5801_Excessive_Time(id, Passageway_CF4, 0x32);
	Set_5801_Excessive_Time(id, Passageway_CF5, 0x32);
	Set_5801_Excessive_Time(id, Passageway_CF6, 0x32);
	Set_5801_Excessive_Time(id, Passageway_CF7, 0x32);
	set_lapsetime_TPDO(id, TPDO_CH1, microsecond(999));
	set_lapsetime_TPDO(id, TPDO_CH2, microsecond(999));
	set_lapsetime_TPDO(id, TPDO_CH3, microsecond(999));
	set_lapsetime_TPDO(id, TPDO_CH4, microsecond(999));
	event_TPDO(id, TPDO_CH1, microsecond(1000));
	event_TPDO(id, TPDO_CH2, microsecond(1000));
	event_TPDO(id, TPDO_CH3, microsecond(1000));
	event_TPDO(id, TPDO_CH4, microsecond(1000));
	enable_TPDO(id, TPDO_CH1, TPDOCOMMAND_YES);
	enable_TPDO(id, TPDO_CH2, TPDOCOMMAND_YES);
	enable_TPDO(id, TPDO_CH3, TPDOCOMMAND_YES);
	enable_TPDO(id, TPDO_CH4, TPDOCOMMAND_YES);
}

u8 rec_5801_Frequency_Value(uint32_t id, u32 *resut_int)//读取频率值
{
	u8 buf[8];
	CanRxMsg RxMessage;
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0) return 0;		//没有接收到数据,直接退出 
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//读取数据	
  for(u32 i=0;i<RxMessage.DLC;i++)
	buf[i]=RxMessage.Data[i];  
	uint32_t id_intact = RxMessage.StdId;
	if(id_intact == 0x180+id)
	{	
		resut_int[0] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道0
		resut_int[1] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道1
		static int i = 0;i++;
	}
	else if(id_intact == 0x280+id)
	{	
		resut_int[2] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道2
		resut_int[3] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道3
		static int i = 0;i++;
	}
	else if(id_intact == 0x380+id)
	{	
		resut_int[4] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道4
		resut_int[5] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道5
		static int i = 0;i++;
	}
	else if(id_intact == 0x480+id)
	{	
		resut_int[6] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道6
		resut_int[7] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道7
		static int i = 0;i++;
	}
	return RxMessage.DLC;	
}

u8 rec_5801_Count_Value(uint32_t id, u32 resut_int[8])//读取计数值
{
	u8 buf[8];
	CanRxMsg RxMessage;
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0) return 0;		//没有接收到数据,直接退出 
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//读取数据	
  for(u32 i=0;i<RxMessage.DLC;i++)
		buf[i]=RxMessage.Data[i];  
	uint32_t id_intact = RxMessage.StdId;
	if(id_intact == 0x180+id)
	{	
		resut_int[0] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道0
		resut_int[1] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道1
	}
	else if(id_intact == 0x280+id)
	{	
		resut_int[2] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道2
		resut_int[3] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道3
	}
	else if(id_intact == 0x380+id)
	{	
		resut_int[4] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道4
		resut_int[5] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道5
	}
	else if(id_intact == 0x480+id)
	{	
		resut_int[6] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道6
		resut_int[7] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道7
	}
	return RxMessage.DLC;	
}
//设置模块为测频或计数模式，0为计数模式，1为测频模式
//由type的值确定各个通道的具体模式 
u8 Set_5801_Frequency_Type(uint32_t id, uint8_t type)                                                   
{                                                    
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // 标准标识符为0
  TxMessage.ExtId=0x600+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=0x00; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=type; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;		
}
//清零计数通道
u8 Set_5801_ClearCount(uint32_t id, u8 count_clear[8])
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x200+id;	 // 标准标识符为0
  TxMessage.ExtId=0x200+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=count_clear[0];//0x01//清零      
  TxMessage.Data[1]=count_clear[1];//0x00//不清零 
  TxMessage.Data[2]=count_clear[2];//0x01//清零
  TxMessage.Data[3]=count_clear[3];//0x01//清零
  TxMessage.Data[4]=count_clear[4];//0x00//不清零 
  TxMessage.Data[5]=count_clear[5];//0x01//清零
  TxMessage.Data[6]=count_clear[6];//0x01//清零
	TxMessage.Data[7]=count_clear[7];//0x00//不清零
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;		
}
//设置模块测频通道滤波时间
u8 Set_5801_Filter_Time(uint32_t id, EMPPassageway Passageway, EMPFiltertime Filtertime)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x580+id;	 // 标准标识符为0
  TxMessage.ExtId=0x580+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=0x07; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=Passageway;//具体配置哪个通道
  TxMessage.Data[4]=Filtertime;//滤波时间 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;		
}
//设置模块测频超时时间（设置为最小频率的周期）
 //0x32=50，50*100ms=5s，定时5s
 //0x0A=10，10*100ms=5s，定时1s
u8 Set_5801_Excessive_Time(uint32_t id, EMPPassageway Passageway, uint8_t Excessivetime)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // 标准标识符为0
  TxMessage.ExtId=0x600+id;	 // 设置扩展标示符（29位）
  TxMessage.IDE=0;		  // 使用扩展标识符
  TxMessage.RTR=0;		  // 消息类型为数据帧，一帧8位
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=0x08; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=Passageway;
  TxMessage.Data[4]=Excessivetime;//设置的测频更新时间（单位 100ms）所以更新时间是 Excessivetime*100ms
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;		
}
