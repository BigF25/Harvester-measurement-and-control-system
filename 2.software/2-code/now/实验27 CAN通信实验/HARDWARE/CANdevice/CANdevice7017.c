//��ͬ�ͺ�CANģ��ĸ��ԵĲ���ָ��
#include "CANdevice7017.h"
#include "CANdevice.h"

void Init_7017(uint32_t id)
{
	Set_7017_AiType(id, AiType_10V);
	Set_7017_AiEnable(id, AiChannel_ALL);
	Set_7017_AiDataType(id, ANALOG_VALUE);
	Set_7017_AiNumberOfFilters(id, AiNumOfFilters(5));
	set_lapsetime_TPDO(id, TPDO_CH1, microsecond(999));
	set_lapsetime_TPDO(id, TPDO_CH2, microsecond(999));
	event_TPDO(id, TPDO_CH1, microsecond(1000));
	event_TPDO(id, TPDO_CH2, microsecond(1000));
	enable_TPDO(id, TPDO_CH1, TPDOCOMMAND_YES);
	enable_TPDO(id, TPDO_CH2, TPDOCOMMAND_YES);
}
//1�� ��ȡ AI ģ��������
u8 rec_7017_AiValue(uint32_t id, u16 resut_char[8])
{
	u8 buf[8];
	CanRxMsg RxMessage;
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0) return 0;		//û�н��յ�����,ֱ���˳� 
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
  for(u32 i=0;i<RxMessage.DLC;i++)
		buf[i]=RxMessage.Data[i];  
	uint32_t id_intact = RxMessage.StdId; 
	if(id_intact == 0x180+id)
	{
		resut_char[0] = (u16)(buf[0]+buf[1]*256);
		resut_char[1] = (u16)(buf[2]+buf[3]*256);
		resut_char[2] = (u16)(buf[4]+buf[5]*256);
		resut_char[3] = (u16)(buf[6]+buf[7]*256);
		static int m = 0;m++;
	}
	else if(id_intact == 0x280+id)
	{
		resut_char[4] = (u16)(buf[0]+buf[1]*256);
		resut_char[5] = (u16)(buf[2]+buf[3]*256);
		resut_char[6] = (u16)(buf[4]+buf[5]*256);
		resut_char[7] = (u16)(buf[6]+buf[7]*256);
		static int i = 0;i++;
	}
	return RxMessage.DLC;	
}
//3������ģ��� AIN �ɼ�����
u8 Set_7017_AiType(uint32_t id, AiType type)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2F;      
  TxMessage.Data[1]=0x04; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=type; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
//5������ģ��� AI �ɼ�ͨ��ʹ��
u8 Set_7017_AiEnable(uint32_t id, AiChannel channel)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2F;      
  TxMessage.Data[1]=0x03; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=channel; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
//7������ģ�� AI �����ݸ�ʽ
u8 Set_7017_AiDataType(uint32_t id, AiDataType datatype)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2F;      
  TxMessage.Data[1]=0x08; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=datatype; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
//15������ģ��Ĳɼ��˲�����
u8 Set_7017_AiNumberOfFilters(uint32_t id, AiNum Ainum) 
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=0x09; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=Ainum; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
