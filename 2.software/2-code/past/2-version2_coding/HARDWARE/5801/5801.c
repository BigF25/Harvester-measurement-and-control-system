#include "5801.h"
#include "can.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"

void Init_5801(u8 address, u8 value)
{
	Set_5801_Frequency_Type(address, value);delay_ms(100);//0xFF����ͨ����Ϊ��Ƶ��ģʽ
	Set_5801_Filter_Time(address, Passageway_CF0, Filtertime_10);delay_ms(100);//����ͨ��0 1�˲�ʱ��
	Set_5801_Filter_Time(address, Passageway_CF1, Filtertime_10);delay_ms(100);//����ͨ��0 1�˲�ʱ��
	Set_5801_Filter_Time(address, Passageway_CF2, Filtertime_10);delay_ms(100);//����ͨ��0 1�˲�ʱ��
	Set_5801_Filter_Time(address, Passageway_CF3, Filtertime_10);delay_ms(100);//����ͨ��0 1�˲�ʱ��
	Set_5801_Filter_Time(address, Passageway_CF4, Filtertime_10);delay_ms(100);//����ͨ��0 1�˲�ʱ��
	Set_5801_Filter_Time(address, Passageway_CF5, Filtertime_10);delay_ms(100);//����ͨ��0 1�˲�ʱ��
	Set_5801_Filter_Time(address, Passageway_CF6, Filtertime_10);delay_ms(100);//����ͨ��0 1�˲�ʱ��
	Set_5801_Filter_Time(address, Passageway_CF7, Filtertime_10);delay_ms(100);//����ͨ��0 1�˲�ʱ��
	Set_5801_Excessive_Time(address, Passageway_CF0, 0x32);delay_ms(100);
	Set_5801_Excessive_Time(address, Passageway_CF1, 0x32);delay_ms(100);
	Set_5801_Excessive_Time(address, Passageway_CF2, 0x32);delay_ms(100);
	Set_5801_Excessive_Time(address, Passageway_CF3, 0x32);delay_ms(100);
	Set_5801_Excessive_Time(address, Passageway_CF4, 0x32);delay_ms(100);
	Set_5801_Excessive_Time(address, Passageway_CF5, 0x32);delay_ms(100);
	Set_5801_Excessive_Time(address, Passageway_CF6, 0x32);delay_ms(100);
	Set_5801_Excessive_Time(address, Passageway_CF7, 0x32);delay_ms(100);
	lapsetime_TPDO(address, _TPDO1, 10);delay_ms(100);
	lapsetime_TPDO(address, _TPDO2, 10);delay_ms(100);
	lapsetime_TPDO(address, _TPDO3, 10);delay_ms(100);
	lapsetime_TPDO(address, _TPDO4, 10);delay_ms(100);
	event_TPDO(address, _TPDO1, 50);delay_ms(100);
	event_TPDO(address, _TPDO2, 50);delay_ms(100);
	event_TPDO(address, _TPDO3, 50);delay_ms(100);//100
	event_TPDO(address, _TPDO4, 50);delay_ms(100);
}

u8 rec_5801_ImpulseValue(uint32_t ID, u32 *resut_int)//��ȡƵ��ֵ
{
	u8 buf[8];
	CanRxMsg RxMessage;
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0) return 0;		//û�н��յ�����,ֱ���˳� 
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
  for(u32 i=0;i<RxMessage.DLC;i++)
		buf[i]=RxMessage.Data[i];  
	uint32_t id = RxMessage.StdId;
	static int count = 0;
	count+=50;
	LCD_ShowxNum(count,70,id,4,16,0);//delay_ms(1000);
	if(count > 800)count = 0;
	if(id == 0x180+ID)
	{	
		resut_int[0] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//ͨ��0
		resut_int[1] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//ͨ��1
		static int i = 0;i++;
		LCD_ShowxNum(10,100,i,4,16,0);//delay_ms(1000);
	}
	else if(id == 0x280+ID)
	{	
		resut_int[2] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//ͨ��2
		resut_int[3] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//ͨ��3
		static int i = 0;i++;
		LCD_ShowxNum(10,120,i,4,16,0);//delay_ms(1000);
	}
	else if(id == 0x380+ID)
	{	
		resut_int[4] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//ͨ��4
		resut_int[5] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//ͨ��5
		static int i = 0;i++;
		LCD_ShowxNum(10,140,i,4,16,0);//delay_ms(1000);
	}
	else if(id == 0x480+ID)
	{	
		resut_int[6] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//ͨ��6
		resut_int[7] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//ͨ��7
		static int i = 0;i++;
		LCD_ShowxNum(10,160,i,4,16,0);//delay_ms(1000);
	}
	return RxMessage.DLC;	
}

u8 rec_5801_CountValue(uint32_t ID, u32 resut_int[8])//��ȡ����ֵ
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
		resut_int[0] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//ͨ��0
		resut_int[1] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//ͨ��1
	}
	else if(id == 0x280+ID)
	{	
		resut_int[2] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//ͨ��2
		resut_int[3] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//ͨ��3
	}
	else if(id == 0x380+ID)
	{	
		resut_int[4] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//ͨ��4
		resut_int[5] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//ͨ��5
	}
	else if(id == 0x480+ID)
	{	
		resut_int[6] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//ͨ��6
		resut_int[7] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//ͨ��7
	}
	return RxMessage.DLC;	
}

u8 Set_5801_Frequency_Type(uint32_t id, uint8_t type)//����ģ��Ϊ��Ƶ�����ģʽ��0Ϊ����ģʽ��1Ϊ��Ƶģʽ                                                     
{                                                    //��type��ֵȷ������ͨ���ľ���ģʽ 
	u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=0x00; 
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

u8 Set_5801_ClearCount(uint32_t id, u8 count_clear[8])//�������ͨ��
{
	u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x200+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x200+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=count_clear[0];//0x01//����      
  TxMessage.Data[1]=count_clear[1];//0x00//������ 
  TxMessage.Data[2]=count_clear[2];//0x01//����
  TxMessage.Data[3]=count_clear[3];//0x01//����
  TxMessage.Data[4]=count_clear[4];//0x00//������ 
  TxMessage.Data[5]=count_clear[5];//0x01//����
  TxMessage.Data[6]=count_clear[6];//0x01//����
	TxMessage.Data[7]=count_clear[7];//0x00//������
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;	
}

u8 Set_5801_Filter_Time(uint32_t id, EMPPassageway Passageway, EMPFiltertime Filtertime)//����ģ���Ƶͨ���˲�ʱ��
{
	u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x580+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x580+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=0x07; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=Passageway;//���������ĸ�ͨ��
  TxMessage.Data[4]=Filtertime;//�˲�ʱ�� 
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;	
}

u8 Set_5801_Excessive_Time(uint32_t id, EMPPassageway Passageway, uint8_t Excessivetime)//����ģ���Ƶ��ʱʱ�䣨����Ϊ��СƵ�ʵ����ڣ�
{                                                                                       //0x32=50��50*100ms=5s����ʱ5s
	u8 mbox;                                                                              //0x0A=10��10*100ms=5s����ʱ1s
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=8;	
  TxMessage.Data[0]=0x2B;      
  TxMessage.Data[1]=0x08; 
  TxMessage.Data[2]=0x20;
  TxMessage.Data[3]=Passageway;
  TxMessage.Data[4]=Excessivetime;//���õĲ�Ƶ����ʱ�䣨��λ 100ms�����Ը���ʱ���� Excessivetime*100ms
  TxMessage.Data[5]=0x00;
  TxMessage.Data[6]=0x00;
	TxMessage.Data[7]=0x00;
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;	
}