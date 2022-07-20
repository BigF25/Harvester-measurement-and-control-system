#ifndef __TRANSLATE_H
#define __TRANSLATE_H	 
#include "sys.h"
#define TEMPCHAR_MAX 50
#define WRITE_ALREADY 0xFF
typedef struct
{
	uint32_t temp_rec_5801_num_channel[16];
	uint32_t temp_rec_7017_num_channel[8];
	char temp_rec_5801_char_channel[16][TEMPCHAR_MAX];
	char temp_rec_7017_char_channel[8][TEMPCHAR_MAX];
	uint32_t temp_rec_idnum;	//临时缓存结构体中最近一次刷新数据的id号
	RTC_DateTypeDef temp_rec_rtc_data;
	RTC_TimeTypeDef temp_rec_rtc_time;
}TEMP_REC_MSG;
extern TEMP_REC_MSG my_temp_rec_msg;

void Translate_CANMsg2Num(uint32_t can_device_id);
void Translate_Num2AscllChar(uint32_t can_device_id);
void Translate_CANMsg2TempStruct(void);
#define ONETAB 	"\t"
#define TWOTAB 	"\t\t"
#define FOURTAB "\t\t\t\t"
#define ENTER 	"\n"
void Translate_AscllChar2SDData(uint32_t can_device_id, char *SDDataMsg);
int Translate_AscllChar2ComScreenCMD(u8 *ComScreenCmd, u8 screenID);
void Translate_AscllChar2DTUMsg(char *DTUData);

#endif
