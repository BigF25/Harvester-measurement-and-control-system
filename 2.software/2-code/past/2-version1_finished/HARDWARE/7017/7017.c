#include "7017.h"
#include "can.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"

void Init_7017(uint32_t ID)
{
	Set_7017_AiType(ID, AiType_5V);
	Set_7017_AiEnable(ID, AiChannel_ALL);
	Set_7017_AiDataType(ID, ANALOG_VALUE);
	Set_7017_AiNumberOfFilters(ID, AiNumOfFilters(5));
	lapsetime_TPDO(ID, _TPDO1, 999);delay_ms(100);
	lapsetime_TPDO(ID, _TPDO2, 999);delay_ms(100);
	event_TPDO(ID, _TPDO1, 1000);delay_ms(100);
	event_TPDO(ID, _TPDO2, 1000);delay_ms(100);
}
 
u8 rec_7017_AiValue(uint32_t ID, u16 resut_char[8])//��ȡ AI ģ��������
{
	u8 buf[8];
	CanRxMsg RxMessage;
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0) return 0;		//û�н��յ�����,ֱ���˳� 
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
  for(u32 i=0;i<RxMessage.DLC;i++)
		buf[i]=RxMessage.Data[i];  
	uint32_t id = RxMessage.StdId; 
	if(id == 0x180+ID)
	{
		resut_char[0] = (u16)(buf[0]+buf[1]*256);
		resut_char[1] = (u16)(buf[2]+buf[3]*256);
		resut_char[2] = (u16)(buf[4]+buf[5]*256);
		resut_char[3] = (u16)(buf[6]+buf[7]*256);
		static int m = 0;m++;
		LCD_ShowxNum(70,100,m,4,16,0);//delay_ms(1000);
	}
	else if(id == 0x280+ID)
	{
		resut_char[4] = (u16)(buf[0]+buf[1]*256);
		resut_char[5] = (u16)(buf[2]+buf[3]*256);
		resut_char[6] = (u16)(buf[4]+buf[5]*256);
		resut_char[7] = (u16)(buf[6]+buf[7]*256);
		static int i = 0;i++;
		LCD_ShowxNum(70,120,i,4,16,0);//delay_ms(1000);
	}
	return RxMessage.DLC;	
}
u8 set_7017_DOBit(uint32_t id, u8 a)//���� DO ���������
{
	u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x200+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x200+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=1;	
	if(a == 0)
		TxMessage.Data[0]=0x00;     
	else if(a == 1)
		TxMessage.Data[0]=0x01;
  mbox= CAN_Transmit(CAN1, &TxMessage); 
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;
}
u8 rec_7017_msg(uint32_t *id, u8 *buf)
{
	CanRxMsg RxMessage;
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0) return 0;		//û�н��յ�����,ֱ���˳� 
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
  for(u32 i=0;i<RxMessage.DLC;i++)
		buf[i]=RxMessage.Data[i];  
	*id = RxMessage.StdId; 
	return RxMessage.DLC;	
}

u8 send_7017_msg(uint32_t id)
{
	u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x40;      
  TxMessage.Data[1]=0x09; 
  TxMessage.Data[2]=0x20; 
  TxMessage.Data[3]=0x01; 
  TxMessage.Data[4]=0x00; 
  TxMessage.Data[5]=0x00; 
  TxMessage.Data[6]=0x00; 
	TxMessage.Data[7]=0x00; 
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;	
}

u8 Set_7017_AiType(uint32_t id, AiType type)//����ģ��� AIN �ɼ����� 
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
  TxMessage.Data[1]=0x04; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=type; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;		
}

u8 Set_7017_AiEnable(uint32_t id, AiChannel channel)//����ģ��� AI �ɼ�ͨ��ʹ��
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
  TxMessage.Data[1]=0x03; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=channel; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;	
}

u8 Set_7017_AiDataType(uint32_t id, AiDataType datatype)//����ģ�� AI �����ݸ�ʽ 
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
  TxMessage.Data[1]=0x08; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=0x01;
  TxMessage.Data[4]=datatype; 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;	
}

u8 Set_7017_AiNumberOfFilters(uint32_t id, AiNum Ainum)//����ģ��Ĳɼ��˲����� 
{
	u8 mbox;
  u16 i=0;
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
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;	
}
