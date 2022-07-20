#ifndef __COMSCREEN_H
#define __COMSCREEN_H	
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "stdio.h"
#include "hw_config.h"
#include "ulitity.h"
#include "string.h"
#include "usart2.h"
#include "usart3.h"

#include "3402.h"
#include "4055.h"
#include "5801.h"
#include "7017.h"

#define TIME_100MS 10										 //100毫秒(10个单位)
 
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
}COMSCREEN;
extern COMSCREEN my_comscreen;

typedef struct 
{
	uint32  timer_tick_count;				//定时器节拍
	uint8 cmd_buffer[CMD_MAX_SIZE];	//指令缓存
	uint16 current_screen_id;				//当前画面ID
	int32 progress_value;						//进度条测试值
	int32 test_value;								//测试值
	uint8 update_en;								//更新标记
	int32 meter_flag;								//仪表指针往返标志位
	int32 num;											//曲线采样点计数
	int sec;												//时间秒
	int32 curves_type;							//曲线标志位  0为正弦波，1为锯齿波
	int32 second_flag;							//时间标志位
	int32 icon_flag;								//图标标志位
	uint8 Select_H;									//滑动选择小时
	uint8 Select_M;									//滑动选择分钟
	uint8 Last_H;										//上一个选择小时
	uint8 Last_M;										//上一个选择分钟
	int32 Progress_Value;						//进度条的值
}COMSCREEN_VAL;

extern COMSCREEN_VAL my_comscreen_value;

void screen_ID_case(void);
void control_ID_case(void);

void comscreen_value_init(void);

void ProcessMessage( PCTRL_MSG msg, uint16 size ) ;
void NOTIFYHandShake(void) ;
void NotifyScreen(uint16 screen_id) ;
void NotifyTouchXY(uint8 press,uint16 x,uint16 y) ;
void UpdateUI(void) ;
void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state) ;
void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str) ;
void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value) ;
void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value) ;
void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value) ;
void NotifyMenu(uint16 screen_id, uint16 control_id, uint8 item, uint8 state) ;
void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item) ;
void NotifyTimer(uint16 screen_id, uint16 control_id) ;
void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length) ;
void NotifyWriteFlash(uint8 status) ;
void NotifyReadRTC(uint8 year,uint8 month,uint8 week,uint8 day,uint8 hour,uint8 minute,uint8 second) ;


#endif 
