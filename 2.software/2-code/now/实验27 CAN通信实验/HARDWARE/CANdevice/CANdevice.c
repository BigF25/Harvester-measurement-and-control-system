//��ͬ�ͺ�CANģ�����ͬ�Ĳ���ָ��
#include "CANdevice.h"
u8 enable_TPDO(uint32_t id, TPDOChannel channel, TPDOCommand command)
{

  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
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
//���ü��ʱ��
//���ʱ���ڲ�Ҫ��������
u8 set_lapsetime_TPDO(uint32_t id, TPDOChannel channel, u16 time)
{
	u8 low,high;
	time = time*10; //��λ0.1us
	low = time & 0x00ff; 	//�Ͱ�λ
	high = time >> 8;    	//�߰�λ
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
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
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
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
//�����¼�ʱ��
//���ʱ�����������ݷ����仯�����Ϸ������ݣ������¼�ʱ����������ݡ�
u8 event_TPDO(uint32_t id, TPDOChannel channel, u16 time)
{
	u8 low,high;
	low = time & 0x00ff; 	//�Ͱ�λ
	high = time >> 8;    	//�߰�λ
  CanTxMsg TxMessage;
  TxMessage.StdId=0x600+id;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=0x600+id;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
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
//��ʹǿ�Ƴɹ�������Ҫ���͵ı��ĵ���������
//���ǳ���0xFFF�˺� ��ֹ��ѭ���˳�
u8 CANdevice_sendmsg_force(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{
	u8 mbox;
	u8 state=SendMsg_Force_NO;
	u16 i=0;
	while(1){
		mbox = CAN_Transmit(CAN1, TxMessage);
		//printf("mbox=%d\t%x\r\n",mbox,TxMessage->StdId);
		//�����Ų���NoMailBox����˵�����ͳɹ�
		
		if(mbox!=CAN_TxStatus_NoMailBox) 
		{
			state = SendMsg_Force_OK;
			break;
		}
		//�������·��ͣ����Ǳ�����ѭ�����ڳ��Է���0xFFF�κ�ǿ���˳������ط��ʹ���״̬
		else if(mbox==CAN_TxStatus_NoMailBox && i<0xFFF)
		{
			state = SendMsg_Force_NO;
			i++;
		}
	}
	return state;
}
