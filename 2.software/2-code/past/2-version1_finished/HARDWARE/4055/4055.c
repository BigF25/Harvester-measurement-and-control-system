#include "4055.h"
#include "can.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"

void Init_4055(uint32_t id)
{
	Set_4055_Safety_output(id, 0xFF);
	enable_TPDO(id, TPDO1, TPDOCOMMAND_NO);
	enable_TPDO(id, TPDO2, TPDOCOMMAND_NO);
	enable_TPDO(id, TPDO3, TPDOCOMMAND_NO);
	enable_TPDO(id, TPDO4, TPDOCOMMAND_NO);
}

u8 Set_4055_Switchoutput(uint32_t id, u8 digital_output)
{
	u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x200+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x200+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=1;
  TxMessage.Data[0] = digital_output;      
  mbox= CAN_Transmit(CAN1, &TxMessage);
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;
}

u8 Set_4055_Safety_output(uint32_t id, u8 type_DO)
{
	u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2F;
  TxMessage.Data[1]=0x01;
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=type_DO;
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
  mbox= CAN_Transmit(CAN1, &TxMessage);
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;
}
