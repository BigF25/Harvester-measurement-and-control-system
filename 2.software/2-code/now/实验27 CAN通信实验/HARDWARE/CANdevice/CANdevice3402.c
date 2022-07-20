//��ͬ�ͺ�CANģ��ĸ��ԵĲ���ָ��
#include "CANdevice3402.h"
#include "CANdevice.h"
#include "stdio.h"

void Init_3402(uint32_t id)
{
	enable_TPDO(id, TPDO_CH1, TPDOCOMMAND_NO);
	enable_TPDO(id, TPDO_CH2, TPDOCOMMAND_NO);
	enable_TPDO(id, TPDO_CH3, TPDOCOMMAND_NO);
	enable_TPDO(id, TPDO_CH4, TPDOCOMMAND_NO);
	Set_3402_AOoutput_type(id, Output_pin_AO0, type_V);
	Set_3402_AOoutput_type(id, Output_pin_AO1, type_V);
}
u8 Set_3402_Analogoutput(uint32_t id, u16 ao_0, u16 ao_1)
{
	u8 ao_00, ao_01, ao_10, ao_11;
	ao_00 = ao_0 & 0x00ff; 	//�Ͱ�λ
	ao_01 = ao_0 >> 8;    	//�߰�λ
	ao_10 = ao_1 & 0x00ff; 	//�Ͱ�λ
	ao_11 = ao_1 >> 8;     	//�߰�λ
  CanTxMsg TxMessage;
  TxMessage.StdId=0x200+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x200+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=5;	
  TxMessage.Data[0]=0x03;      
  TxMessage.Data[1]=ao_00; 
  TxMessage.Data[2]=ao_01;
  TxMessage.Data[3]=ao_10;
  TxMessage.Data[4]=ao_11; 
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}

u8 Set_3402_AOoutput_type(uint32_t id, Output_pin pin, Output_type type)
{
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2F;      
  TxMessage.Data[1]=0x09; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=pin;
  TxMessage.Data[4]=type; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
	u8 state = CANdevice_sendmsg_force(CAN1, &TxMessage);
  return state;	
}
