//SD卡文件的操作
#include "SDCardFile.h"
#include "stdio.h"
#include "string.h"	
#include "log.h"	

#include "translate.h"
#include "sdio_sdcard.h"
#include "ff.h"
#include "CANdevice.h"

FATFS SDFatFS;    /* File system object for SD logical drive */

void SDCardFile_Init(void)
{
	if(SD_Init())								//初始化SD卡
		;//SD Card Error!
	else 
		f_mount(&SDFatFS,"0:",1);	//挂载SD卡
}
void WriteDataToSDCard(void)
{
	extern TEMP_REC_MSG my_temp_rec_msg;
	u8 open_state;	//文件的打开状态
	int resID;			//f_xx的工作状态
	FIL SDFile;       /* File object for SD */
	UINT bww;
	char temp_title[50];
	char temp[200];
	char SDDataMsg[200];
	//SD卡开关未打开 直接返回
	
	//SD卡状态异常 直接返回
	
	//获取临时缓存结构体中最近一次刷新数据的id号
	uint32_t idnum = my_temp_rec_msg.temp_rec_idnum;
	//如果最近一次刷新的数据已经写过了，直接跳过不再重复往sd卡写入数据
	if(idnum == WRITE_ALREADY) 
	{
		error("no new message");
		return;
	}
	//创建报文对应的文件名称
	switch(idnum)
	{
		case ADDRESS_5801_1+0x180:
		case ADDRESS_5801_1+0x280:
		case ADDRESS_5801_1+0x380:
		case ADDRESS_5801_1+0x480:
		case ADDRESS_5801_2+0x180:
		case ADDRESS_5801_2+0x280:
		case ADDRESS_5801_2+0x380:
		case ADDRESS_5801_2+0x480:
			sprintf(temp_title, "0:/5801_20%02d-%02d-%02d %02dh.xls", //新建文件名称
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Year,
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Month,
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Date,
										my_temp_rec_msg.temp_rec_rtc_time.RTC_Hours
										);
			open_state = f_open(&SDFile,temp_title,FA_CREATE_NEW | FA_WRITE);
//			printf("f_openCREATE5801:%d\r\n",open_state);////////////////////////////////////////////////////////////////////////////////////
//			printf("%s\t",temp_title);////////////////////////////////////////////////////////////////////////////////////
//			printf("%x\r\n",myqueue->front->data.StdId);////////////////////////////////////////////////////////////////////////////////////
			if(open_state==FR_OK)//文件不存在 新建一个	
			{
				sprintf(temp, "Data\tTime\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\t14\t15\n");//创建表头
				resID = f_write(&SDFile,temp,strlen(temp), &bww);
//				printf("f_write%d\r\n",resID);////////////////////////////////////////////////////////////////////////////////////////////////
			}
			break;
			
		case ADDRESS_7017+0x180:
		case ADDRESS_7017+0x280:
			sprintf(temp_title, "0:/7017_20%02d-%02d-%02d %02dh.xls", //新建文件名称
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Year,
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Month,
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Date,
										my_temp_rec_msg.temp_rec_rtc_time.RTC_Hours
										);
			open_state = f_open(&SDFile,temp_title,FA_CREATE_NEW | FA_WRITE);
//			printf("f_openCREATE7017:%d\r\n",open_state);////////////////////////////////////////////////////////////////////////
//			printf("%s\t",temp_title);////////////////////////////////////////////////////////////////////////////////////
//			printf("%x\r\n",myqueue->front->data.StdId);////////////////////////////////////////////////////////////////////////////////////
			if(open_state==FR_OK)//文件不存在 新建一个	
			{
				sprintf(temp, "Data\tTime\t1\t2\t3\t4\t5\t6\t7\t8\n");//创建表头
				resID = f_write(&SDFile,temp,strlen(temp), &bww);
//				printf("f_write%d\r\n",resID);////////////////////////////////////////////////////////////////////////////////////////////////
			}
			break;
		
		default:
			break;
	}
	//打开文件
	if(open_state==FR_EXIST)
	{
		resID = f_open(&SDFile,temp_title,FA_OPEN_EXISTING | FA_WRITE);
//		printf("f_openEXIS:%d\r\n",resID);//////////////////////////////////////////////////////////////////////////////////
		resID = f_lseek(&SDFile,f_size(&SDFile));//找到文件的尾巴
//		printf("f_lseek:%d\r\n",resID);//////////////////////////////////////////////////////////////////////////////////
	}
	//加入时间戳
	sprintf(SDDataMsg, "20%d-%02d-%02d\t%02d:%02d:%02d\t",
					my_temp_rec_msg.temp_rec_rtc_data.RTC_Year, 
					my_temp_rec_msg.temp_rec_rtc_data.RTC_Month, 
					my_temp_rec_msg.temp_rec_rtc_data.RTC_Date,
					my_temp_rec_msg.temp_rec_rtc_time.RTC_Hours,
					my_temp_rec_msg.temp_rec_rtc_time.RTC_Minutes,
					my_temp_rec_msg.temp_rec_rtc_time.RTC_Seconds
					);
	//加入数据
	Translate_AscllChar2SDData(idnum,SDDataMsg);
	//将数据写入文件
	resID = f_write(&SDFile,SDDataMsg,strlen(SDDataMsg),&bww);
//	printf("f_write:%d\r\n",resID);/////////////////////////////////////////////////////////////////////////////////
	//结束
	resID = f_close(&SDFile);
//	printf("f_close:%d\r\n\r\n",resID);///////////////////////////////////////////////////////////////////////////////
	my_temp_rec_msg.temp_rec_idnum = WRITE_ALREADY;
	success();
}



