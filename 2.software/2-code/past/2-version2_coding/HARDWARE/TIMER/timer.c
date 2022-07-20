#include "timer.h"
#include "beep.h"
#include "rtc.h"
#include "can.h"
#include "comscreen.h"
#include "mylvgl.h"
#include "rtc.h"


//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
u8 rec_can_value(u32 *resut_int_5801, u16 *resut_char_7017)
{
	u8 buf[8];
	CanRxMsg RxMessage;
  if( CAN_MessagePending(CAN1,CAN_FIFO0)==0) return 0;		//没有接收到数据,直接退出 
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//读取数据	
  for(u32 i=0;i<RxMessage.DLC;i++)
		buf[i]=RxMessage.Data[i];  
	uint32_t id = RxMessage.StdId;
	u8 ID = id%16 ;

	//////////////////////////can显示//////////////////////////////////
	{	
		static u16 count_1=0,count_2=0,count_3=0,count_4=0,count_5=0,count_6=0,count_7=0,count_8=0,count_9=0,count_10=0;
		switch(id)
		{
			case 0x183:count_1++;break;
			case 0x283:count_2++;break;
			case 0x383:count_3++;break;
			case 0x483:count_4++;break;
			case 0x184:count_5++;break;
			case 0x284:count_6++;break;
			case 0x384:count_7++;break;
			case 0x484:count_8++;break;
			case 0x185:count_9++;break;
			case 0x285:count_10++;break;
		}
		LCD_ShowxNum(650,40,183,4,16,0);
		LCD_ShowxNum(650,60,283,4,16,0);
		LCD_ShowxNum(650,80,383,4,16,0);		
		LCD_ShowxNum(650,100,483,4,16,0);		
		LCD_ShowxNum(650,120,184,4,16,0);
		LCD_ShowxNum(650,140,284,4,16,0);
		LCD_ShowxNum(650,160,384,4,16,0);
		LCD_ShowxNum(650,180,484,4,16,0);
		LCD_ShowxNum(650,200,185,4,16,0);		
		LCD_ShowxNum(650,220,285,4,16,0);		
		
		LCD_ShowxNum(700,40,count_1,4,16,0);
		LCD_ShowxNum(700,60,count_2,4,16,0);
		LCD_ShowxNum(700,80,count_3,4,16,0);
		LCD_ShowxNum(700,100,count_4,4,16,0);
		LCD_ShowxNum(700,120,count_5,4,16,0);
		LCD_ShowxNum(700,140,count_6,4,16,0);
		LCD_ShowxNum(700,160,count_7,4,16,0);
		LCD_ShowxNum(700,180,count_8,4,16,0);
		LCD_ShowxNum(700,200,count_9,4,16,0);
		LCD_ShowxNum(700,220,count_10,4,16,0);
		static u8 count = 1;
		static u8 j = 0;
		u16 tempid = id;
		u16 countweishu = 1;
		u16 output = 0;
		while(tempid!=0)
		{
			output+=tempid%16*countweishu;
			countweishu*=10;
			tempid/=16;
		}
		if(1)
		{
		if(++j>20) j=0;
		count++;
		LCD_ShowxNum(20,40+20*j,count,4,16,0);
		LCD_ShowxNum(20+48,40+20*j,output,4,16,0);

		for(int i=0;i<8;i++)
		{
			LCD_ShowxNum(20+48+48+i*48,40+20*j,0,3,16,0X80);	//刷新
		}
		for(int i=0;i<8;i++)
		{
			LCD_ShowxNum(20+48+48+i*48,40+20*j,buf[i],3,16,0X80);	//显示数据
		}
		}
	}
	////////////////////////can显示////////////////////////////////////

	if(ID == ADDRESS_5801_1)
	{
		if(id == 0x180+ID)
		{	
			resut_int_5801[0] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道0
			resut_int_5801[1] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道1
			static int i = 0;i++;
		}
		else if(id == 0x280+ID)
		{	
			resut_int_5801[2] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道2
			resut_int_5801[3] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道3
			static int i = 0;i++;
		}
		else if(id == 0x380+ID)
		{	
			resut_int_5801[4] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道4
			resut_int_5801[5] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道5
			static int i = 0;i++;
		}
		else if(id == 0x480+ID)
		{	
			resut_int_5801[6] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道6
			resut_int_5801[7] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道7
			static int i = 0;i++;
		}
	}
	else if(ID == ADDRESS_5801_2)
	{
		if(id == 0x180+ID)
		{	
			resut_int_5801[8] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道0
			resut_int_5801[9] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道1
			static int i = 0;i++;
		}
		else if(id == 0x280+ID)
		{	
			resut_int_5801[10] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道2
			resut_int_5801[11] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道3
			static int i = 0;i++;
		}
		else if(id == 0x380+ID)
		{	
			resut_int_5801[12] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道4
			resut_int_5801[13] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道5
			static int i = 0;i++;
		}
		else if(id == 0x480+ID)
		{	
			resut_int_5801[14] = buf[0]+buf[1]*256+buf[2]*65536+buf[3]*16777216;//通道6
			resut_int_5801[15] = buf[4]+buf[5]*256+buf[6]*65536+buf[7]*16777216;//通道7
			static int i = 0;i++;
		}
	}
	else if(ID == ADDRESS_7017)
	{
		if(id == 0x180+ID)
		{
			resut_char_7017[0] = (u16)(buf[0]+buf[1]*256);
			resut_char_7017[1] = (u16)(buf[2]+buf[3]*256);
			resut_char_7017[2] = (u16)(buf[4]+buf[5]*256);
			resut_char_7017[3] = (u16)(buf[6]+buf[7]*256);
			static int m = 0;m++;
		}
		else if(id == 0x280+ID)
		{
			resut_char_7017[4] = (u16)(buf[0]+buf[1]*256);
			resut_char_7017[5] = (u16)(buf[2]+buf[3]*256);
			resut_char_7017[6] = (u16)(buf[4]+buf[5]*256);
			resut_char_7017[7] = (u16)(buf[6]+buf[7]*256);
			static int i = 0;i++;
		}
	}
	return RxMessage.DLC;	
}

void my_USART_Send_Data(u8 *buf,u8 len)
{
		USART3_Send_Data(buf,len);
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void getsendmsg_5801(u8* temp, u8 num,u8 screenID, u8*need)
{ 
	int p = -1;
	char head[3];
	head[0] = 0xEE;
	head[1] = 0xB1;
	head[2] = 0x12;
	temp[++p] = head[0];
	temp[++p] = head[1];
	temp[++p] = head[2];
	
	u8 screenIDchar[2];
	screenIDchar[0] = 0;
	screenIDchar[1] = screenID;
	temp[++p] = screenIDchar[0];
	temp[++p] = screenIDchar[1];
	
	for(u8 i=1; i<=num; i++)
	{
		u8 numID[2];
		numID[0] = 0;
		numID[1] = i;
		temp[++p] = numID[0];
		temp[++p] = numID[1];
		
		u8 valuelong[2];
		valuelong[0] = 0;
		valuelong[1] = strlen(my_comscreen.scr_5801_result_char[need[i-1]]);	
		temp[++p] = valuelong[0];
		temp[++p] = valuelong[1];
		
		for(int j=0; j<valuelong[1]; j++)
		{
			temp[++p] = my_comscreen.scr_5801_result_char[need[i-1]][j];
		}
	}
	
	char tail[4];
	tail[0] = 0xFF;
	tail[1] = 0xFC;
	tail[2] = 0xFF;
	tail[3] = 0xFF;
	temp[++p] = tail[0];
	temp[++p] = tail[1];
	temp[++p] = tail[2];
	temp[++p] = tail[3];
}
void getsendmsg_7017(u8* temp, u8 num,u8 screenID, u8*need)
{ 
	int p = -1;
	char head[3];
	head[0] = 0xEE;
	head[1] = 0xB1;
	head[2] = 0x12;
	temp[++p] = head[0];
	temp[++p] = head[1];
	temp[++p] = head[2];
	
	u8 screenIDchar[2];
	screenIDchar[0] = 0;
	screenIDchar[1] = screenID;
	temp[++p] = screenIDchar[0];
	temp[++p] = screenIDchar[1];
	
	for(u8 i=1; i<=num; i++)
	{
		u8 numID[2];
		numID[0] = 0;
		numID[1] = i;
		temp[++p] = numID[0];
		temp[++p] = numID[1];
		
		u8 valuelong[2];
		valuelong[0] = 0;
		valuelong[1] = strlen(my_comscreen.scr_7017_result_char[need[i-1]]);	
		temp[++p] = valuelong[0];
		temp[++p] = valuelong[1];
		
		for(int j=0; j<valuelong[1]; j++)
		{
			temp[++p] = my_comscreen.scr_7017_result_char[need[i-1]][j];
		}
	}
	
	char tail[4];
	tail[0] = 0xFF;
	tail[1] = 0xFC;
	tail[2] = 0xFF;
	tail[3] = 0xFF;
	temp[++p] = tail[0];
	temp[++p] = tail[1];
	temp[++p] = tail[2];
	temp[++p] = tail[3];
}
//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		static int timer_count = 0;
		timer_count++;

		//sd卡检测
		if(my_comscreen.sys_init_ready==1 && timer_count%1000==0)
		{
			if(SD_GetState() == SD_CARD_ERROR)
			{
				my_comscreen.sd_ready_flag = 0;
				const u8 LEN = 64;
				u8 comscreen_send_msg[LEN] = {0xEE,0xB1,0x10,0x00,0x00,0x00,0x06,0x53,0x44,0xBF,0xA8,0xB4,0xED,0xCE,0xF3,0xFF,0xFC,0xFF,0xFF };
				my_USART_Send_Data(comscreen_send_msg,LEN);
			}
			else
			{
				my_comscreen.sd_ready_flag = 1;
				const u8 LEN = 64;
				u8 comscreen_send_msg[LEN] = {0xEE,0xB1,0x10,0x00,0x00,0x00,0x06,0x53,0x44,0xBF,0xA8,0xD5,0xFD,0xB3,0xA3,0xFF,0xFC,0xFF,0xFF };
				my_USART_Send_Data(comscreen_send_msg,LEN);
			}
		}
		
		//can接收
		if(timer_count%300==0 && my_comscreen.scr_can_but_flag == 1)
		{
			//5801
			static u8 countconscreen = 0;
//			rec_can_value(my_comscreen.scr_5801_result_int, my_comscreen.scr_7017_result_int);
			sprintf(my_comscreen.scr_5801_result_char[0], "%.2f", my_comscreen.scr_5801_result_int[0]*0.6);
			sprintf(my_comscreen.scr_5801_result_char[1], "%.2f", my_comscreen.scr_5801_result_int[1]*0.6);
			sprintf(my_comscreen.scr_5801_result_char[2], "%.2f", my_comscreen.scr_5801_result_int[2]*0.6);
			sprintf(my_comscreen.scr_5801_result_char[3], "%.2f", my_comscreen.scr_5801_result_int[3]*0.6);
			sprintf(my_comscreen.scr_5801_result_char[4], "%.2f", my_comscreen.scr_5801_result_int[4]*0.6);
			sprintf(my_comscreen.scr_5801_result_char[5], "%.2f", my_comscreen.scr_5801_result_int[5]*0.6);
			sprintf(my_comscreen.scr_5801_result_char[6], "%.2f", my_comscreen.scr_5801_result_int[6]*0.6);
			sprintf(my_comscreen.scr_5801_result_char[7], "%.2f", my_comscreen.scr_5801_result_int[7]*0.6);
			
			sprintf(my_comscreen.scr_5801_result_char[8], "%.2f", my_comscreen.scr_5801_result_int[8]*0.6);
			sprintf(my_comscreen.scr_5801_result_char[9], "%.2f", my_comscreen.scr_5801_result_int[9]*0.6);
			
			u32 temp = my_comscreen.scr_5801_result_int[11] + my_comscreen.scr_5801_result_int[12] + my_comscreen.scr_5801_result_int[13] + my_comscreen.scr_5801_result_int[15];
//			sprintf(my_comscreen.scr_5801_result_char[10], "%d", my_comscreen.scr_5801_result_int[10]);
//			sprintf(my_comscreen.scr_5801_result_char[11], "%d", my_comscreen.scr_5801_result_int[11]);
//			sprintf(my_comscreen.scr_5801_result_char[12], "%d", my_comscreen.scr_5801_result_int[12]);
//			sprintf(my_comscreen.scr_5801_result_char[13], "%d", my_comscreen.scr_5801_result_int[13]);
			sprintf(my_comscreen.scr_5801_result_char[14], "%d", my_comscreen.scr_5801_result_int[14]);
			sprintf(my_comscreen.scr_5801_result_char[15], "%d", temp);

			const u8 LEN = 64;
			u8 comscreen_send_msg[LEN];
			u8 need[5];
			need[0]=0;need[1]=1;need[2]=2;need[3]=3;need[4]=4;
			getsendmsg_5801(comscreen_send_msg, 5, 1, need);
			my_USART_Send_Data(comscreen_send_msg,LEN);
			
			need[0]=5;need[1]=6;need[2]=7;need[3]=8;need[4]=9;
			getsendmsg_5801(comscreen_send_msg, 5, 2, need);
			my_USART_Send_Data(comscreen_send_msg,LEN);
			
			need[0]=14;need[1]=15;
			getsendmsg_5801(comscreen_send_msg, 2, 3, need);
			my_USART_Send_Data(comscreen_send_msg,LEN);
			
			//7017
			sprintf(my_comscreen.scr_7017_result_char[0], "%d", my_comscreen.scr_7017_result_int[0]);
			sprintf(my_comscreen.scr_7017_result_char[1], "%d", my_comscreen.scr_7017_result_int[1]);
			sprintf(my_comscreen.scr_7017_result_char[2], "%d", my_comscreen.scr_7017_result_int[2]);
			sprintf(my_comscreen.scr_7017_result_char[3], "%d", my_comscreen.scr_7017_result_int[3]);
			sprintf(my_comscreen.scr_7017_result_char[4], "%d", my_comscreen.scr_7017_result_int[4]);
			sprintf(my_comscreen.scr_7017_result_char[5], "%d", my_comscreen.scr_7017_result_int[5]);
			sprintf(my_comscreen.scr_7017_result_char[6], "%d", my_comscreen.scr_7017_result_int[6]);
//			sprintf(my_comscreen.scr_7017_result_char[7], "%d", my_comscreen.scr_7017_result_int[7]);
			
			need[0]=0;need[1]=1;need[2]=2;need[3]=3;need[4]=4;
			getsendmsg_7017(comscreen_send_msg, 5, 4, need);
			my_USART_Send_Data(comscreen_send_msg,LEN);
			
			need[0]=5;need[1]=6;
			getsendmsg_7017(comscreen_send_msg, 2, 8, need);
			my_USART_Send_Data(comscreen_send_msg,LEN);		
		}

		//sd卡写入	
		if(timer_count%200==0 && my_comscreen.sd_ready_flag == 1 && my_comscreen.scr_sd_but_flag == 1)
		{
			LCD_ShowString(200,200,200,16,16,"sdon");
			{		
				FIL fil;
				UINT bww;
				u8 res;
				char temp[200];
				RTC_TimeTypeDef RTC_TimeStruct;
				RTC_DateTypeDef RTC_DateStruct;
				RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
				RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
				sprintf(temp, "0:/5801_20%d-%02d-%02d %02dh.xls", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date, RTC_TimeStruct.RTC_Hours);
				res=f_open(&fil,temp,FA_CREATE_NEW | FA_WRITE);
				if(res)
				{
					f_open(&fil,temp,FA_OPEN_EXISTING | FA_WRITE);
					res=f_lseek(&fil,f_size(&fil));
					sprintf(temp, "20%d-%02d-%02d\t%02d:%02d:%02d\t", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date,RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds);
					for(int i=0; i<10; i++)
					{
						char tempp[20];
						sprintf(tempp, "%s\t", my_comscreen.scr_5801_result_char[i]);
						strcat(temp,tempp);
					}
					{
						char tempp[20];
						sprintf(tempp, "%s\t", my_comscreen.scr_5801_result_char[15]);
						strcat(temp,tempp);
						sprintf(tempp, "%s\t", my_comscreen.scr_5801_result_char[14]);
						strcat(temp,tempp);
					}
					strcat(temp,"\n");
					f_write(&fil,temp,strlen(temp), &bww);
					f_close(&fil);
				}
				else
				{
					sprintf(temp, "日期\t时间\t前进速度\t拨禾轮转速\t输送槽转速\t割台搅龙转速\t滚筒转速\t风机转速\t杂余搅龙转速\t籽粒搅龙转速\t碎草装置转速\t发动机转速\t籽粒夹带损失\t籽粒清选损失\n");
					f_write(&fil,temp,strlen(temp), &bww);
					f_close(&fil);
				}
			}
			{
				FIL fil;
				UINT bww;
				u8 res;
				char temp[200];
				RTC_TimeTypeDef RTC_TimeStruct;
				RTC_DateTypeDef RTC_DateStruct;
				RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
				RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
				sprintf(temp, "0:/7017_20%d-%02d-%02d %02dh.xls", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date, RTC_TimeStruct.RTC_Hours);
				res=f_open(&fil,temp,FA_CREATE_NEW | FA_WRITE);
				if(res)
				{
					f_open(&fil,temp,FA_OPEN_EXISTING | FA_WRITE);
					res=f_lseek(&fil,f_size(&fil));
					sprintf(temp, "20%d-%02d-%02d\t%02d:%02d:%02d\t", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date,RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds);
					for(int i=0; i<7; i++)
					{
						char tempp[20];
						sprintf(tempp, "%s\t", my_comscreen.scr_7017_result_char[i]);
						strcat(temp,tempp);
					}
					strcat(temp,"\n");
					f_write(&fil,temp,strlen(temp), &bww);
					f_close(&fil);
				}
				else
				{
					sprintf(temp, "日期\t时间\t拨禾轮高度\t割台高度\t鱼鳞筛开度\t仿形板1角度\t仿形板2角度\t超声波1\t超声波2\n");
					f_write(&fil,temp,strlen(temp), &bww);
					f_close(&fil);
				}
			}	
		}

		//电机
		if(my_comscreen.scr_4055_motor1_but_ena_flag == 1 && timer_count % (11-my_comscreen.scr_4055_motor1_slider_value) == 0 )
		{
			static u8 flag = 0;
			if(flag == 0) 
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg & 0xFB;//11111011
			else if(flag == 1)
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg | 0x04;//00000100
			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen.scr_4055_motor_can_send_msg);
			flag = !flag;
		}
		if(my_comscreen.scr_4055_motor2_but_ena_flag == 1 && timer_count % (11-my_comscreen.scr_4055_motor2_slider_value) == 0 )
		{
			static u8 flag = 0;
			if(flag == 0) 
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg & 0x7F;//01111111
			else if(flag == 1)
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg | 0x80;//10000000
			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen.scr_4055_motor_can_send_msg);
			flag = !flag;
		}

		//溢出清零
		if(timer_count == 10000) timer_count = 0;
		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}
