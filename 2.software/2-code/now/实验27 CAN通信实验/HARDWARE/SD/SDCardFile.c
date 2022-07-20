//SD���ļ��Ĳ���
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
	if(SD_Init())								//��ʼ��SD��
		;//SD Card Error!
	else 
		f_mount(&SDFatFS,"0:",1);	//����SD��
}
void WriteDataToSDCard(void)
{
	extern TEMP_REC_MSG my_temp_rec_msg;
	u8 open_state;	//�ļ��Ĵ�״̬
	int resID;			//f_xx�Ĺ���״̬
	FIL SDFile;       /* File object for SD */
	UINT bww;
	char temp_title[50];
	char temp[200];
	char SDDataMsg[200];
	//SD������δ�� ֱ�ӷ���
	
	//SD��״̬�쳣 ֱ�ӷ���
	
	//��ȡ��ʱ����ṹ�������һ��ˢ�����ݵ�id��
	uint32_t idnum = my_temp_rec_msg.temp_rec_idnum;
	//������һ��ˢ�µ������Ѿ�д���ˣ�ֱ�����������ظ���sd��д������
	if(idnum == WRITE_ALREADY) 
	{
		error("no new message");
		return;
	}
	//�������Ķ�Ӧ���ļ�����
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
			sprintf(temp_title, "0:/5801_20%02d-%02d-%02d %02dh.xls", //�½��ļ�����
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Year,
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Month,
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Date,
										my_temp_rec_msg.temp_rec_rtc_time.RTC_Hours
										);
			open_state = f_open(&SDFile,temp_title,FA_CREATE_NEW | FA_WRITE);
//			printf("f_openCREATE5801:%d\r\n",open_state);////////////////////////////////////////////////////////////////////////////////////
//			printf("%s\t",temp_title);////////////////////////////////////////////////////////////////////////////////////
//			printf("%x\r\n",myqueue->front->data.StdId);////////////////////////////////////////////////////////////////////////////////////
			if(open_state==FR_OK)//�ļ������� �½�һ��	
			{
				sprintf(temp, "Data\tTime\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\t14\t15\n");//������ͷ
				resID = f_write(&SDFile,temp,strlen(temp), &bww);
//				printf("f_write%d\r\n",resID);////////////////////////////////////////////////////////////////////////////////////////////////
			}
			break;
			
		case ADDRESS_7017+0x180:
		case ADDRESS_7017+0x280:
			sprintf(temp_title, "0:/7017_20%02d-%02d-%02d %02dh.xls", //�½��ļ�����
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Year,
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Month,
										my_temp_rec_msg.temp_rec_rtc_data.RTC_Date,
										my_temp_rec_msg.temp_rec_rtc_time.RTC_Hours
										);
			open_state = f_open(&SDFile,temp_title,FA_CREATE_NEW | FA_WRITE);
//			printf("f_openCREATE7017:%d\r\n",open_state);////////////////////////////////////////////////////////////////////////
//			printf("%s\t",temp_title);////////////////////////////////////////////////////////////////////////////////////
//			printf("%x\r\n",myqueue->front->data.StdId);////////////////////////////////////////////////////////////////////////////////////
			if(open_state==FR_OK)//�ļ������� �½�һ��	
			{
				sprintf(temp, "Data\tTime\t1\t2\t3\t4\t5\t6\t7\t8\n");//������ͷ
				resID = f_write(&SDFile,temp,strlen(temp), &bww);
//				printf("f_write%d\r\n",resID);////////////////////////////////////////////////////////////////////////////////////////////////
			}
			break;
		
		default:
			break;
	}
	//���ļ�
	if(open_state==FR_EXIST)
	{
		resID = f_open(&SDFile,temp_title,FA_OPEN_EXISTING | FA_WRITE);
//		printf("f_openEXIS:%d\r\n",resID);//////////////////////////////////////////////////////////////////////////////////
		resID = f_lseek(&SDFile,f_size(&SDFile));//�ҵ��ļ���β��
//		printf("f_lseek:%d\r\n",resID);//////////////////////////////////////////////////////////////////////////////////
	}
	//����ʱ���
	sprintf(SDDataMsg, "20%d-%02d-%02d\t%02d:%02d:%02d\t",
					my_temp_rec_msg.temp_rec_rtc_data.RTC_Year, 
					my_temp_rec_msg.temp_rec_rtc_data.RTC_Month, 
					my_temp_rec_msg.temp_rec_rtc_data.RTC_Date,
					my_temp_rec_msg.temp_rec_rtc_time.RTC_Hours,
					my_temp_rec_msg.temp_rec_rtc_time.RTC_Minutes,
					my_temp_rec_msg.temp_rec_rtc_time.RTC_Seconds
					);
	//��������
	Translate_AscllChar2SDData(idnum,SDDataMsg);
	//������д���ļ�
	resID = f_write(&SDFile,SDDataMsg,strlen(SDDataMsg),&bww);
//	printf("f_write:%d\r\n",resID);/////////////////////////////////////////////////////////////////////////////////
	//����
	resID = f_close(&SDFile);
//	printf("f_close:%d\r\n\r\n",resID);///////////////////////////////////////////////////////////////////////////////
	my_temp_rec_msg.temp_rec_idnum = WRITE_ALREADY;
	success();
}



