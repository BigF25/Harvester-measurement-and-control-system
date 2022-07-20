#ifndef __COMSCREEN_H
#define __COMSCREEN_H	
#include "COMscreen_drive.h"
#include "sys.h"


#define SCR_MAIN_ID 						0
#define SCR_5801_1_ID 					1
#define SCR_5801_1_BACK_BUT_ID 	10
#define SCR_5801_1_UP_BUT_ID 		11
#define SCR_5801_1_DOWN_BUT_ID 	12
#define SCR_5801_1_SD_BUT_ID 		13
#define SCR_5801_1_CAN_BUT_ID 	14
#define SCR_5801_2_ID 					2
#define SCR_5801_2_BACK_BUT_ID 	20
#define SCR_5801_2_UP_BUT_ID 		21
#define SCR_5801_2_DOWN_BUT_ID 	22
#define SCR_5801_3_ID 					3
#define SCR_5801_3_BACK_BUT_ID 	30
#define SCR_5801_3_UP_BUT_ID 		3
#define SCR_5801_3_DOWN_BUT_ID 	32
#define SCR_7017_1_ID						4
#define SCR_7017_1_BACK_BUT_ID 	40
#define SCR_7017_1_UP_BUT_ID 		41
#define SCR_7017_1_DOWN_BUT_ID 	42
#define SCR_7017_2_ID						8
#define SCR_7017_2_BACK_BUT_ID 	80
#define SCR_7017_2_UP_BUT_ID 		81
#define SCR_7017_2_DOWN_BUT_ID 	82
#define SCR_4055_ID 								5
#define SCR_4055_BACK_BUT_ID 				50
#define SCR_4055_MOTOR1_BUT_ENA_ID 	51
#define SCR_4055_MOTOR1_BUT_DIR_ID 	52
#define SCR_4055_MOTOR1_SLIDER_ID 	53
#define SCR_4055_MOTOR2_BUT_ENA_ID 	54
#define SCR_4055_MOTOR2_BUT_DIR_ID 	55
#define SCR_4055_MOTOR2_SLIDER_ID 	56
#define SCR_3402_ID 					6
#define SCR_3402_SLIDER1_ID 	61
#define SCR_3402_SLIDER2_ID 	62
#define SCR_SET_ID 					7
#define SCR_SET_SD_BUT_ID 	71

#define CMD_MAX_SIZE 25           // 单条指令大小，根据需要调整，尽量设置大一些
typedef struct
{
	u8 sys_init_ready;
	u8 sd_ready_flag;
	u8 scr_can_but_flag;
	u8 scr_sd_but_flag;	
	u32 scr_5801_result_int[16];//ADC显示的数值
	char scr_5801_result_char[16][25];//ADC显示的字符串
	
	u16 scr_7017_result_int[8];//ADC显示的数值	
	char scr_7017_result_char[8][25];//ADC显示的字符串
	
	u8 scr_4055_motor1_but_ena_flag;
	u8 scr_4055_motor1_but_dir_flag;	
	u8 scr_4055_motor2_but_ena_flag;
	u8 scr_4055_motor3_but_dir_flag;
	u8 scr_4055_motor1_slider_value;
	u8 scr_4055_motor2_slider_value;
	u8 scr_4055_motor_can_send_msg;
}ComScreenMsg;
extern ComScreenMsg my_comscreen_msg;

void COMscreen_Init(void);
void COMscreen_value_init(void);
void COMscreen_REV_Cmd(void);
void MCU_Reaction_ReferToCmd(uint8* cmd_buffer);
void UpdateComScreen(u8 screenID);
void UpdateComScreen_ALL(void);

#endif 
