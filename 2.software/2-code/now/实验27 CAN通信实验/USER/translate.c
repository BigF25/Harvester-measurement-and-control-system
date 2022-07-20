#include "translate.h"
#include "stdio.h"
#include "string.h"	
#include "sys.h"
#include "log.h"

#include "queue.h"
#include "CANdevice.h"
#include "COMscreen.h"
#include "math.h"
#define degree(x) (3.88017*pow(10,-10)*pow(x,3)) - 1.24686*(pow(10,-5)*x*x) + (0.138173*x) - (446.93)
TEMP_REC_MSG my_temp_rec_msg;

/*! 
*  \brief  	��CAN���ķ����������ʽ��д����ʱ����ṹ����
*  \param  	can_device_id ���ĵ�id��
*  \return  ��
*/
void Translate_CANMsg2Num(uint32_t can_device_id)
{
	switch(can_device_id)
	{
		case ADDRESS_5801_1+0x180:
			my_temp_rec_msg.temp_rec_5801_num_channel[0] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//ͨ��0
			my_temp_rec_msg.temp_rec_5801_num_channel[1] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//ͨ��1
			break;
		case ADDRESS_5801_1+0x280:
			my_temp_rec_msg.temp_rec_5801_num_channel[2] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//ͨ��2
			my_temp_rec_msg.temp_rec_5801_num_channel[3] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//ͨ��3
			break;
		case ADDRESS_5801_1+0x380:
			my_temp_rec_msg.temp_rec_5801_num_channel[4] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//ͨ��4
			my_temp_rec_msg.temp_rec_5801_num_channel[5] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//ͨ��5
			break;
		case ADDRESS_5801_1+0x480:
			my_temp_rec_msg.temp_rec_5801_num_channel[6] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//ͨ��6
			my_temp_rec_msg.temp_rec_5801_num_channel[7] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//ͨ��7
			break;
		case ADDRESS_5801_2+0x180:
			my_temp_rec_msg.temp_rec_5801_num_channel[8] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//ͨ��0
			my_temp_rec_msg.temp_rec_5801_num_channel[9] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//ͨ��1
			break;
		case ADDRESS_5801_2+0x280:
			my_temp_rec_msg.temp_rec_5801_num_channel[10] = myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//ͨ��2
			my_temp_rec_msg.temp_rec_5801_num_channel[11] = myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//ͨ��3
			break;
		case ADDRESS_5801_2+0x380:
			my_temp_rec_msg.temp_rec_5801_num_channel[12] = myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//ͨ��4
			my_temp_rec_msg.temp_rec_5801_num_channel[13] = myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//ͨ��5
			break;
		case ADDRESS_5801_2+0x480:
			my_temp_rec_msg.temp_rec_5801_num_channel[14] = myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//ͨ��6
			my_temp_rec_msg.temp_rec_5801_num_channel[15] = myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//ͨ��7
			break;
		case ADDRESS_7017+0x180:
			my_temp_rec_msg.temp_rec_7017_num_channel[0] = myqueue->front->data.Data[0]+myqueue->front->data.Data[1]*256;//ͨ��0
			my_temp_rec_msg.temp_rec_7017_num_channel[1] = myqueue->front->data.Data[2]+myqueue->front->data.Data[3]*256;//ͨ��1
			my_temp_rec_msg.temp_rec_7017_num_channel[2] = myqueue->front->data.Data[4]+myqueue->front->data.Data[5]*256;//ͨ��2
			my_temp_rec_msg.temp_rec_7017_num_channel[3] = myqueue->front->data.Data[6]+myqueue->front->data.Data[7]*256;//ͨ��3
			break;
		case ADDRESS_7017+0x280:
			my_temp_rec_msg.temp_rec_7017_num_channel[4] = myqueue->front->data.Data[0]+myqueue->front->data.Data[1]*256;//ͨ��4
			my_temp_rec_msg.temp_rec_7017_num_channel[5] = myqueue->front->data.Data[2]+myqueue->front->data.Data[3]*256;//ͨ��5
			my_temp_rec_msg.temp_rec_7017_num_channel[6] = myqueue->front->data.Data[4]+myqueue->front->data.Data[5]*256;//ͨ��6
			my_temp_rec_msg.temp_rec_7017_num_channel[7] = myqueue->front->data.Data[6]+myqueue->front->data.Data[7]*256;//ͨ��7
			break;
		default:
			break;
	}	
}
/*! 
*  \brief  	��������ʽ�����ݷ����Ascll���ַ�����д����ʱ����ṹ����
*  \param  	can_device_id ���ĵ�id�� 
*  \return  ��
*/
void Translate_Num2AscllChar(uint32_t can_device_id)
{
		switch(can_device_id)
	{
		case ADDRESS_5801_1+0x180:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[0], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[0]*0.6);//ͨ��0
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[1], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[1]*0.6);//ͨ��1
			break;
		case ADDRESS_5801_1+0x280:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[2], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[2]*0.6);//ͨ��2
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[3], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[3]*0.6);//ͨ��3
			break;
		case ADDRESS_5801_1+0x380:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[4], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[4]*0.6);//ͨ��4
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[5], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[5]*0.6);//ͨ��5
			break;
		case ADDRESS_5801_1+0x480:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[6], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[6]*0.6);//ͨ��6
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[7], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[7]*0.6);//ͨ��7
			break;
		case ADDRESS_5801_2+0x180:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[8], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[8]*0.6);//ͨ��8
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[9], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[9]*0.6);//ͨ��9
			break;
		case ADDRESS_5801_2+0x280:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[10], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[10]*0.6);//ͨ��10
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[11], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[11]*0.6);//ͨ��11
			break;
		case ADDRESS_5801_2+0x380:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[12], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[12]*0.6);//ͨ��12
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[13], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[13]*0.6);//ͨ��13
			break;
		case ADDRESS_5801_2+0x480:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[14], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[14]*0.6);//ͨ��14
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[15], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[15]*0.6);//ͨ��15
			break;
		case ADDRESS_7017+0x180:
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[0], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[0]);//ͨ��0
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[1], "%.2f", degree(my_temp_rec_msg.temp_rec_7017_num_channel[1]));//ͨ��1
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[2], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[2]);//ͨ��2
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[3], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[3]);//ͨ��3
//			for(uint8_t i=0; i<4; i++)
//			printf("7017channel_%d:%s\n\r", i, my_temp_rec_msg.temp_rec_7017_char_channel[i]);
			break;
		case ADDRESS_7017+0x280:
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[4], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[4]);//ͨ��4
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[5], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[5]);//ͨ��5
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[6], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[6]);//ͨ��6
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[7], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[7]);//ͨ��7
//			for(uint8_t i=4; i<8; i++)
//			printf("7017channel_i:%s\n\r", my_temp_rec_msg.temp_rec_7017_char_channel[i]);
			break;
		default:
			break;
	}	
}
/*! 
*  \brief  	ִ�г��淭�룬�����ĵ�����һ֡������ʱ����ṹ����
*						���а��������ķ����������ʽ�ͽ�������ʽ������ַ���
*  \param  	��
*  \return  ��
*/
void Translate_CANMsg2TempStruct(void)
{
	extern queue *myqueue;
	//��������ǿյ�ֱ�ӷ���
	if(get_queue_length(myqueue)==0) 
	{
		error("empty_queue");
		return;
	}
	//�������ȷid  ɾ���ýڵ� ���ҷ���
	uint32_t idnum = myqueue->front->data.StdId;
	if(
			myqueue->front->data.StdId != ADDRESS_5801_1+0x180 &&
			myqueue->front->data.StdId != ADDRESS_5801_1+0x280 &&
			myqueue->front->data.StdId != ADDRESS_5801_1+0x380 &&
			myqueue->front->data.StdId != ADDRESS_5801_1+0x480 &&
			myqueue->front->data.StdId != ADDRESS_5801_2+0x180 &&
			myqueue->front->data.StdId != ADDRESS_5801_2+0x280 &&
			myqueue->front->data.StdId != ADDRESS_5801_2+0x380 &&
			myqueue->front->data.StdId != ADDRESS_5801_2+0x480 &&
			myqueue->front->data.StdId != ADDRESS_7017+0x180 &&
			myqueue->front->data.StdId != ADDRESS_7017+0x280
			) 
	{
		delete_queue(myqueue);
		error("PASS! WrongID:%d",idnum);
		return;
	}
	//����id��
	my_temp_rec_msg.temp_rec_idnum=  idnum;
	//����ʱ���
	my_temp_rec_msg.temp_rec_rtc_data.RTC_Year = myqueue->front->RTC_DateStruct.RTC_Year;
	my_temp_rec_msg.temp_rec_rtc_data.RTC_Month = myqueue->front->RTC_DateStruct.RTC_Month;
	my_temp_rec_msg.temp_rec_rtc_data.RTC_Date = myqueue->front->RTC_DateStruct.RTC_Date;
	my_temp_rec_msg.temp_rec_rtc_time.RTC_Hours = myqueue->front->RTC_TimeStruct.RTC_Hours;
	my_temp_rec_msg.temp_rec_rtc_time.RTC_Minutes = myqueue->front->RTC_TimeStruct.RTC_Minutes;
	my_temp_rec_msg.temp_rec_rtc_time.RTC_Seconds = myqueue->front->RTC_TimeStruct.RTC_Seconds;
	//����1
	Translate_CANMsg2Num(idnum);
	//����2�����������ﴦ��λ��
	Translate_Num2AscllChar(idnum);
	//���½�������� ɾ���ڵ�
	delete_queue(myqueue);
	success();
}

/*! 
*  \brief  	����һ��SD����д������
*  \param  	can_device_id ���ĵ�id��
*  \param  	SDDataMsg Ҫ���͵ı���������׵�ַ
*  \return  ��
*/
void Translate_AscllChar2SDData(uint32_t can_device_id, char *SDDataMsg)
{
	switch(can_device_id)
	{
		case ADDRESS_5801_1+0x180:
			for(int i =0; i<0; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[0]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[1]);strcat(SDDataMsg,ONETAB);
			for(int i =1; i<8; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_5801_1+0x280:
			for(int i =0; i<1; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[2]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[3]);strcat(SDDataMsg,ONETAB);
			for(int i =2; i<8; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_5801_1+0x380:
			for(int i =0; i<2; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[4]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[5]);strcat(SDDataMsg,ONETAB);
			for(int i =3; i<8; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_5801_1+0x480:
			for(int i =0; i<3; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[6]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[7]);strcat(SDDataMsg,ONETAB);
			for(int i =4; i<8; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_5801_2+0x180:
			for(int i =0; i<4; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[8]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[9]);strcat(SDDataMsg,ONETAB);
			for(int i =5; i<8; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_5801_2+0x280:
			for(int i =0; i<5; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[10]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[11]);strcat(SDDataMsg,ONETAB);
			for(int i =6; i<8; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_5801_2+0x380:
			for(int i =0; i<6; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[12]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[13]);strcat(SDDataMsg,ONETAB);
			for(int i =7; i<8; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_5801_2+0x480:
			for(int i =0; i<7; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[14]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_5801_char_channel[15]);strcat(SDDataMsg,ONETAB);
			for(int i =8; i<8; i++) strcat(SDDataMsg,TWOTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_7017+0x180:
			for(int i =0; i<0; i++) strcat(SDDataMsg,FOURTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_7017_char_channel[0]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_7017_char_channel[1]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_7017_char_channel[2]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_7017_char_channel[3]);strcat(SDDataMsg,ONETAB);
			for(int i =1; i<2; i++) strcat(SDDataMsg,FOURTAB);
			strcat(SDDataMsg,ENTER);
			break;
		case ADDRESS_7017+0x280:
			for(int i =0; i<1; i++) strcat(SDDataMsg,FOURTAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_7017_char_channel[4]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_7017_char_channel[5]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_7017_char_channel[6]);strcat(SDDataMsg,ONETAB);
			strcat(SDDataMsg,my_temp_rec_msg.temp_rec_7017_char_channel[7]);strcat(SDDataMsg,ONETAB);
			for(int i =2; i<2; i++) strcat(SDDataMsg,FOURTAB);
			strcat(SDDataMsg,ENTER);
			break;
	}
}
/*! 
*  \brief  	����һ��������ˢ�����ݵ�д��ָ��
*  \param  	can_device_id ���ĵ�id��
*  \param  	ComScreenCmd Ҫ���͵�ָ��������׵�ַ
*  \return  ����ָ���
*/
int Translate_AscllChar2ComScreenCMD(u8 *ComScreenCmd, u8 screenID)
{
	int num;
	int select[5];
	char (*pp)[50];
	switch(screenID)
	{
		case SCR_5801_1_ID:
			num = 5;																												//��ǰid��Ҫ���µ�����
			select[0]=0;select[1]=1;select[2]=2;select[3]=3;select[4]=4;		//����ʱ����ṹ����ѡ����Ҫ��������Ҫ������
			pp = my_temp_rec_msg.temp_rec_5801_char_channel;								//ָ��ָ����ʱ����ṹ���ж�Ӧ���ַ�����Ա
			break;
		case SCR_5801_2_ID:
			num = 5;
			select[0]=5;select[1]=6;select[2]=7;select[3]=8;select[4]=9;
			pp = my_temp_rec_msg.temp_rec_5801_char_channel;
			break;
		case SCR_5801_3_ID:
			num = 2;
			select[0]=10;select[1]=11;
			pp = my_temp_rec_msg.temp_rec_5801_char_channel;
			break;
		case SCR_7017_1_ID:
			num = 5;
			select[0]=0;select[1]=1;select[2]=2;select[3]=3;select[4]=4;
			pp = my_temp_rec_msg.temp_rec_7017_char_channel;
			break;
		case SCR_7017_2_ID:
			num = 2;
			select[0]=5;select[1]=6;
			pp = my_temp_rec_msg.temp_rec_7017_char_channel;
			break;
	}
	int p = -1;
	//�������ͷ
	ComScreenCmd[++p] = HEAD0;
	ComScreenCmd[++p] = HEAD1;
	ComScreenCmd[++p] = HEAD2;
	//�����Ļid
	ComScreenCmd[++p] = 0x00;
	ComScreenCmd[++p] = screenID;
	for(u8 i=0; i<num; i++)
	{
		//��ӿؼ�id
		ComScreenCmd[++p] = 0x00;
		ComScreenCmd[++p] = i+1;
		//��Ӹÿؼ�id���յĸ������ݵĳ���
		ComScreenCmd[++p] = 0x00;
		int len = strlen(pp[select[i]]);	
		ComScreenCmd[++p] = len;
		//��Ӹÿؼ�id���ܵĸ��µ�����
		for(int j=0; j<len; j++)
		{
			ComScreenCmd[++p] = pp[i][j];
		}
	}
	ComScreenCmd[++p] = TAIL0;
	ComScreenCmd[++p] = TAIL1;
	ComScreenCmd[++p] = TAIL2;
	ComScreenCmd[++p] = TAIL3;
	return p;
}
/*! 
*  \brief  	����һ��DTUˢ�µ�д��ָ��
*  \param  	DTUMsg Ҫ���͵���Ϣ�������׵�ַ
*  \return  ��
*/
void Translate_AscllChar2DTUMsg(char *DTUData)
{
	const char atk_key[21][6] = {{"\"fv\":"}, //forward velocity               ǰ���ٶ�
															 {"\"rs\":"}, //Reel speed                     ������ת��
															 {"\"cs\":"}, //Conveying speed                ���Ͳ�ת�� 
															 {"\"fd\":"}, //Feed into dragon speed         ι�����ת�� 
															 {"\"ts\":"}, //Threshing speed                ������Ͳת��
															 {"\"fs\":"}, //Fan speed                      ���ת��
															 {"\"ds\":"}, //Dragon tails up speed          �������ת��
															 {"\"gd\":"}, //Grain dragon speed up          ��������ת��                      
															 {"\"bs\":"}, //Broken grass device speed      ���װ��ת�� 
															 {"\"es\":"}, //engine speed                   ������ת�� 
															 {"\"ge\":"}, //Grain loss of entrainment      �����д���ʧ 
															 {"\"lc\":"}, //Loss of grain cleaning         ������ѡ��ʧ
															 {"\"rh\":"}, //Reel height                    �����ָ߶�
															 {"\"ss\":"}, //Screen opening of fish scales  ����ɸ���� 
															 {"\"ch\":"}, //Cutting height                 ��̨�߶� 
															 {"\"a1\":"}, //Angle profile panel 1          ���ΰ�1�Ƕ�												
															 {"\"a2\":"}, //Angle profile panel 2          ���ΰ�2�Ƕ� 
															 {"\"u1\":"}, //Ultrasonic level 1             ������1�߶� 
															 {"\"u2\":"}, //Ultrasonic level 2             ������2�߶� 
															 {"\"la\":"}, //latitude                       γ�� 
															 {"\"lo\":"}}; //longitude                     ����
	strcat(DTUData,"{");
	for(int i=0;i<21;i++)
	{
		strcat(DTUData,atk_key[i]);
		strcat(DTUData,"\"");
		strcat(DTUData, i<16 ? my_temp_rec_msg.temp_rec_5801_char_channel[i] : my_temp_rec_msg.temp_rec_7017_char_channel[i-16]);
		strcat(DTUData,"\"");
		if(i<20)strcat(DTUData,",");		
	}
	strcat(DTUData,"}");
}
