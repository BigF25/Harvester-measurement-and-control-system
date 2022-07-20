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
*  \brief  	将CAN报文翻译成数字形式，写入临时缓存结构体中
*  \param  	can_device_id 报文的id号
*  \return  无
*/
void Translate_CANMsg2Num(uint32_t can_device_id)
{
	switch(can_device_id)
	{
		case ADDRESS_5801_1+0x180:
			my_temp_rec_msg.temp_rec_5801_num_channel[0] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//通道0
			my_temp_rec_msg.temp_rec_5801_num_channel[1] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//通道1
			break;
		case ADDRESS_5801_1+0x280:
			my_temp_rec_msg.temp_rec_5801_num_channel[2] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//通道2
			my_temp_rec_msg.temp_rec_5801_num_channel[3] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//通道3
			break;
		case ADDRESS_5801_1+0x380:
			my_temp_rec_msg.temp_rec_5801_num_channel[4] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//通道4
			my_temp_rec_msg.temp_rec_5801_num_channel[5] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//通道5
			break;
		case ADDRESS_5801_1+0x480:
			my_temp_rec_msg.temp_rec_5801_num_channel[6] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//通道6
			my_temp_rec_msg.temp_rec_5801_num_channel[7] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//通道7
			break;
		case ADDRESS_5801_2+0x180:
			my_temp_rec_msg.temp_rec_5801_num_channel[8] = 	myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//通道0
			my_temp_rec_msg.temp_rec_5801_num_channel[9] = 	myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//通道1
			break;
		case ADDRESS_5801_2+0x280:
			my_temp_rec_msg.temp_rec_5801_num_channel[10] = myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//通道2
			my_temp_rec_msg.temp_rec_5801_num_channel[11] = myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//通道3
			break;
		case ADDRESS_5801_2+0x380:
			my_temp_rec_msg.temp_rec_5801_num_channel[12] = myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//通道4
			my_temp_rec_msg.temp_rec_5801_num_channel[13] = myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//通道5
			break;
		case ADDRESS_5801_2+0x480:
			my_temp_rec_msg.temp_rec_5801_num_channel[14] = myqueue->front->data.Data[0]+
																											myqueue->front->data.Data[1]*256+
																											myqueue->front->data.Data[2]*65536+
																											myqueue->front->data.Data[3]*16777216;//通道6
			my_temp_rec_msg.temp_rec_5801_num_channel[15] = myqueue->front->data.Data[4]+
																											myqueue->front->data.Data[5]*256+
																											myqueue->front->data.Data[6]*65536+
																											myqueue->front->data.Data[7]*16777216;//通道7
			break;
		case ADDRESS_7017+0x180:
			my_temp_rec_msg.temp_rec_7017_num_channel[0] = myqueue->front->data.Data[0]+myqueue->front->data.Data[1]*256;//通道0
			my_temp_rec_msg.temp_rec_7017_num_channel[1] = myqueue->front->data.Data[2]+myqueue->front->data.Data[3]*256;//通道1
			my_temp_rec_msg.temp_rec_7017_num_channel[2] = myqueue->front->data.Data[4]+myqueue->front->data.Data[5]*256;//通道2
			my_temp_rec_msg.temp_rec_7017_num_channel[3] = myqueue->front->data.Data[6]+myqueue->front->data.Data[7]*256;//通道3
			break;
		case ADDRESS_7017+0x280:
			my_temp_rec_msg.temp_rec_7017_num_channel[4] = myqueue->front->data.Data[0]+myqueue->front->data.Data[1]*256;//通道4
			my_temp_rec_msg.temp_rec_7017_num_channel[5] = myqueue->front->data.Data[2]+myqueue->front->data.Data[3]*256;//通道5
			my_temp_rec_msg.temp_rec_7017_num_channel[6] = myqueue->front->data.Data[4]+myqueue->front->data.Data[5]*256;//通道6
			my_temp_rec_msg.temp_rec_7017_num_channel[7] = myqueue->front->data.Data[6]+myqueue->front->data.Data[7]*256;//通道7
			break;
		default:
			break;
	}	
}
/*! 
*  \brief  	将数字形式的数据翻译成Ascll的字符串，写入临时缓存结构体中
*  \param  	can_device_id 报文的id号 
*  \return  无
*/
void Translate_Num2AscllChar(uint32_t can_device_id)
{
		switch(can_device_id)
	{
		case ADDRESS_5801_1+0x180:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[0], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[0]*0.6);//通道0
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[1], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[1]*0.6);//通道1
			break;
		case ADDRESS_5801_1+0x280:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[2], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[2]*0.6);//通道2
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[3], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[3]*0.6);//通道3
			break;
		case ADDRESS_5801_1+0x380:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[4], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[4]*0.6);//通道4
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[5], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[5]*0.6);//通道5
			break;
		case ADDRESS_5801_1+0x480:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[6], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[6]*0.6);//通道6
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[7], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[7]*0.6);//通道7
			break;
		case ADDRESS_5801_2+0x180:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[8], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[8]*0.6);//通道8
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[9], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[9]*0.6);//通道9
			break;
		case ADDRESS_5801_2+0x280:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[10], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[10]*0.6);//通道10
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[11], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[11]*0.6);//通道11
			break;
		case ADDRESS_5801_2+0x380:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[12], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[12]*0.6);//通道12
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[13], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[13]*0.6);//通道13
			break;
		case ADDRESS_5801_2+0x480:
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[14], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[14]*0.6);//通道14
			sprintf(my_temp_rec_msg.temp_rec_5801_char_channel[15], "%.1f", my_temp_rec_msg.temp_rec_5801_num_channel[15]*0.6);//通道15
			break;
		case ADDRESS_7017+0x180:
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[0], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[0]);//通道0
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[1], "%.2f", degree(my_temp_rec_msg.temp_rec_7017_num_channel[1]));//通道1
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[2], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[2]);//通道2
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[3], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[3]);//通道3
//			for(uint8_t i=0; i<4; i++)
//			printf("7017channel_%d:%s\n\r", i, my_temp_rec_msg.temp_rec_7017_char_channel[i]);
			break;
		case ADDRESS_7017+0x280:
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[4], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[4]);//通道4
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[5], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[5]);//通道5
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[6], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[6]);//通道6
			sprintf(my_temp_rec_msg.temp_rec_7017_char_channel[7], "%d", my_temp_rec_msg.temp_rec_7017_num_channel[7]);//通道7
//			for(uint8_t i=4; i<8; i++)
//			printf("7017channel_i:%s\n\r", my_temp_rec_msg.temp_rec_7017_char_channel[i]);
			break;
		default:
			break;
	}	
}
/*! 
*  \brief  	执行常规翻译，将报文的最新一帧存入临时缓冲结构体中
*						其中包含将报文翻译成数字形式和将数字形式翻译成字符串
*  \param  	无
*  \return  无
*/
void Translate_CANMsg2TempStruct(void)
{
	extern queue *myqueue;
	//如果队列是空的直接返回
	if(get_queue_length(myqueue)==0) 
	{
		error("empty_queue");
		return;
	}
	//如果非正确id  删除该节点 并且返回
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
	//翻译id号
	my_temp_rec_msg.temp_rec_idnum=  idnum;
	//翻译时间戳
	my_temp_rec_msg.temp_rec_rtc_data.RTC_Year = myqueue->front->RTC_DateStruct.RTC_Year;
	my_temp_rec_msg.temp_rec_rtc_data.RTC_Month = myqueue->front->RTC_DateStruct.RTC_Month;
	my_temp_rec_msg.temp_rec_rtc_data.RTC_Date = myqueue->front->RTC_DateStruct.RTC_Date;
	my_temp_rec_msg.temp_rec_rtc_time.RTC_Hours = myqueue->front->RTC_TimeStruct.RTC_Hours;
	my_temp_rec_msg.temp_rec_rtc_time.RTC_Minutes = myqueue->front->RTC_TimeStruct.RTC_Minutes;
	my_temp_rec_msg.temp_rec_rtc_time.RTC_Seconds = myqueue->front->RTC_TimeStruct.RTC_Seconds;
	//翻译1
	Translate_CANMsg2Num(idnum);
	//翻译2（可以在这里处理单位）
	Translate_Num2AscllChar(idnum);
	//最新结点存入完成 删除节点
	delete_queue(myqueue);
	success();
}

/*! 
*  \brief  	制作一条SD卡的写入数据
*  \param  	can_device_id 报文的id号
*  \param  	SDDataMsg 要发送的报文数组的首地址
*  \return  无
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
*  \brief  	制作一条串口屏刷新数据的写入指令
*  \param  	can_device_id 报文的id号
*  \param  	ComScreenCmd 要发送的指令数组的首地址
*  \return  返回指令长度
*/
int Translate_AscllChar2ComScreenCMD(u8 *ComScreenCmd, u8 screenID)
{
	int num;
	int select[5];
	char (*pp)[50];
	switch(screenID)
	{
		case SCR_5801_1_ID:
			num = 5;																												//当前id需要更新的数据
			select[0]=0;select[1]=1;select[2]=2;select[3]=3;select[4]=4;		//在临时缓存结构体中选择需要更新所需要的数据
			pp = my_temp_rec_msg.temp_rec_5801_char_channel;								//指针指向临时缓存结构体中对应的字符串成员
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
	//添加数据头
	ComScreenCmd[++p] = HEAD0;
	ComScreenCmd[++p] = HEAD1;
	ComScreenCmd[++p] = HEAD2;
	//添加屏幕id
	ComScreenCmd[++p] = 0x00;
	ComScreenCmd[++p] = screenID;
	for(u8 i=0; i<num; i++)
	{
		//添加控件id
		ComScreenCmd[++p] = 0x00;
		ComScreenCmd[++p] = i+1;
		//添加该控件id接收的更新数据的长度
		ComScreenCmd[++p] = 0x00;
		int len = strlen(pp[select[i]]);	
		ComScreenCmd[++p] = len;
		//添加该控件id接受的更新的数据
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
*  \brief  	制作一条DTU刷新的写入指令
*  \param  	DTUMsg 要发送的信息的数组首地址
*  \return  无
*/
void Translate_AscllChar2DTUMsg(char *DTUData)
{
	const char atk_key[21][6] = {{"\"fv\":"}, //forward velocity               前进速度
															 {"\"rs\":"}, //Reel speed                     拨禾轮转速
															 {"\"cs\":"}, //Conveying speed                输送槽转速 
															 {"\"fd\":"}, //Feed into dragon speed         喂入搅龙转速 
															 {"\"ts\":"}, //Threshing speed                脱粒滚筒转速
															 {"\"fs\":"}, //Fan speed                      风机转速
															 {"\"ds\":"}, //Dragon tails up speed          杂余搅龙转速
															 {"\"gd\":"}, //Grain dragon speed up          籽粒搅龙转速                      
															 {"\"bs\":"}, //Broken grass device speed      碎草装置转速 
															 {"\"es\":"}, //engine speed                   发动机转速 
															 {"\"ge\":"}, //Grain loss of entrainment      籽粒夹带损失 
															 {"\"lc\":"}, //Loss of grain cleaning         籽粒清选损失
															 {"\"rh\":"}, //Reel height                    拨禾轮高度
															 {"\"ss\":"}, //Screen opening of fish scales  鱼鳞筛开度 
															 {"\"ch\":"}, //Cutting height                 割台高度 
															 {"\"a1\":"}, //Angle profile panel 1          仿形板1角度												
															 {"\"a2\":"}, //Angle profile panel 2          仿形板2角度 
															 {"\"u1\":"}, //Ultrasonic level 1             超声波1高度 
															 {"\"u2\":"}, //Ultrasonic level 2             超声波2高度 
															 {"\"la\":"}, //latitude                       纬度 
															 {"\"lo\":"}}; //longitude                     经度
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
