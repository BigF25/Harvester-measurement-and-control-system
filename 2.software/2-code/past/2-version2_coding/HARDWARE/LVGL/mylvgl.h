#ifndef __MYLVGL_H
#define __MYLVGL_H
#include "lvgl.h"
#include "stdio.h"
#include "string.h"

#include "win_menu.h" 
#include "win_sys1.h" 
#include "win_sys2.h" 
#include "win_sys3.h" 
#include "win_sys4.h" 
#include "win_set.h" 
#include "win_settime.h" 
#include "win_setSDCard.h" 


#include "beep.h"
#include "3402.h"
#include "4055.h"
#include "5801.h"
#include "7017.h"
#include "rtc.h"
#include "sram.h"   
#include "malloc.h" 
#include "usmart.h"  
#include "sdio_sdcard.h"    
#include "malloc.h" 
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"  

LV_FONT_DECLARE(my_font);
LV_FONT_DECLARE(my_font1);

#define LVGL_TICK 	1
#define WIN_MENU 			1
#define WIN_SYS1 			2
#define WIN_SYS2 			3
#define WIN_SYS3      4
#define WIN_SYS4 			5
#define WIN_SET  			6
#define WIN_SETTIME  	7
#define WIN_SDCard  	8

#define ADDRESS_3402		1
#define ADDRESS_4055		2
#define ADDRESS_5801_1	3
#define ADDRESS_5801_2	4
#define ADDRESS_7017		5

typedef struct
{
	u8 year;
	u8 month;
	u8 date;
	u8 weekday;
	u8 hour;
	u8 min;
}Time;

typedef struct 
{
	lv_obj_t * scr ;//7��lcd��ַ
	/**************task***********************/
	lv_task_t * win_title_refresh_task;
	lv_task_t * win_function_monitor_task;
	lv_task_t * win_SD_monitor_task;
	lv_task_t * win_motor_task;
	/**************SDka***********************/
	u8 SDCard_flag;//SD����Ӧ��flag
	#define SD_READY 1
	#define SD_ERROR 0	
	////////////////////////////////////////////////////////////
	u8 win_flag;//�����־
	lv_style_t style;//���
	
	/**************���˵�***********************/
	lv_obj_t * win_menu;
	//���
	lv_style_t win_menu_btn_style;
	lv_style_t win_font1_style;
	//���ⰴť
	lv_obj_t * win_menu_forward_btn;
	lv_obj_t * win_menu_back_btn;
	lv_obj_t * win_menu_set_btn;
	//��ť
	lv_obj_t * win_menu_sys1_btn;
	lv_obj_t * win_menu_sys2_btn;
	lv_obj_t * win_menu_sys3_btn;
	lv_obj_t * win_menu_sys4_btn;	
	lv_obj_t * win_menu_sys5_btn;
	/**************ϵͳ1***********************/
	lv_obj_t * win_sys1;
	u8 win_sys1_finish_loading_flag;
	#define WIN_SYS1_FINISHED 1
	#define WIN_SYS1_LOADING 0
	//���ⰴť
	lv_obj_t * win_sys1_close_btn;
	lv_obj_t * win_sys1_table_up_btn;
	lv_obj_t * win_sys1_table_down_btn;
	lv_obj_t * win_sys1_msg_btn;	
	//���
	lv_obj_t * win_sys1_table;
	short win_sys1_table_count;//��һҳ��ť�ļ���
	#define WIN_SYS1_TABLE_PAGE 2
	u32 win_sys1_5801_result_int_1[8];//ADC��ʾ����ֵ
	u32 win_sys1_5801_result_int_2[8];//ADC��ʾ����ֵ	
	char win_sys1_5801_result_char_1[8][25];//ADC��ʾ���ַ���
	char win_sys1_5801_result_char_2[8][25];//ADC��ʾ���ַ���
	//����
	lv_obj_t * win_sys1_msgbox_msg;	//״̬��ʾ��Ϣ��
	//����
	lv_obj_t * win_sys1_can_rec_switch;//����can��Ϣ
	lv_obj_t * win_sys1_sd_rec_switch;//SD��д��
	lv_obj_t * win_sys1_can_rec_switch_state_label;
	lv_obj_t * win_sys1_sd_rec_switch_state_label;
	u8 win_sys1_can_rec_switch_flag;//switch��Ӧ��flag
	u8 win_sys1_sd_rec_switch_flag;//switch��Ӧ��flag
	#define WIN_SYS1_SWITCH_CLOSE 0
	#define WIN_SYS1_SWITCH_OPEN 1
	/**************ϵͳ2***********************/
	lv_obj_t * win_sys2;
	u8 win_sys2_finish_loading_flag;
	#define WIN_SYS2_FINISHED 1
	#define WIN_SYS2_LOADING 0
	//���ⰴť
	lv_obj_t * win_sys2_close_btn;
	lv_obj_t * win_sys2_table_up_btn;
	lv_obj_t * win_sys2_table_down_btn;
	lv_obj_t * win_sys2_msg_btn;	
	//���
	lv_obj_t * win_sys2_table;
	short win_sys2_table_count;//��һҳ��ť�ļ���
	#define WIN_SYS2_TABLE_PAGE 1
	char win_sys2_7017_result_char[8][25];//ADC��ʾ���ַ���
	u16 win_sys2_7017_result_int[8];//ADC��ʾ����ֵ	
	//����
	lv_obj_t * win_sys2_msgbox_msg;	//״̬��ʾ��Ϣ��
	//����
	lv_obj_t * win_sys2_can_rec_switch;//����can��Ϣ
	lv_obj_t * win_sys2_sd_rec_switch;//SD��д��
	lv_obj_t * win_sys2_can_rec_switch_state_label;
	lv_obj_t * win_sys2_sd_rec_switch_state_label;
	u8 win_sys2_can_rec_switch_flag;//switch��Ӧ��flag
	u8 win_sys2_sd_rec_switch_flag;//switch��Ӧ��flag
	#define WIN_SYS2_SWITCH_CLOSE 0
	#define WIN_SYS2_SWITCH_OPEN 1
	/**************ϵͳ3***********************/
	lv_obj_t * win_sys3;
	u8 win_sys3_finish_loading_flag;
	#define WIN_SYS3_FINISHED 1
	#define WIN_SYS3_LOADING 0
	//���ⰴť
	lv_obj_t * win_sys3_close_btn;
	lv_obj_t * win_sys3_msg_btn;	
	//����
	lv_obj_t * win_sys3_msgbox_msg;	//״̬��ʾ��Ϣ��
	//����
	lv_obj_t * win_sys3_motor1_ena_switch;
	lv_obj_t * win_sys3_motor1_dir_switch;
	lv_obj_t * win_sys3_motor2_ena_switch;
	lv_obj_t * win_sys3_motor2_dir_switch;
	lv_obj_t * win_sys3_motor1_ena_switch_state_label;
	lv_obj_t * win_sys3_motor1_dir_switch_state_label;
	lv_obj_t * win_sys3_motor2_ena_switch_state_label;
	lv_obj_t * win_sys3_motor2_dir_switch_state_label;
	u8 win_sys3_motor1_ena_switch_flag;//switch��Ӧ��flag
	u8 win_sys3_motor1_dir_switch_flag;//switch��Ӧ��flag
	u8 win_sys3_motor2_ena_switch_flag;//switch��Ӧ��flag
	u8 win_sys3_motor2_dir_switch_flag;//switch��Ӧ��flag
	u8 win_sys3_motor_value;
	#define WIN_SYS3_SWITCH_CLOSE 0
	#define WIN_SYS3_SWITCH_OPEN 1
	//lv_slider
	lv_obj_t * win_sys3_motor1_speed_slider;//��������ٶ�
	lv_obj_t * win_sys3_motor2_speed_slider;//��������ٶ�
	lv_obj_t * win_sys3_motor1_speed_slider_label;//��������ٶ�
	lv_obj_t * win_sys3_motor2_speed_slider_label;//��������ٶ�
	u16 win_sys3_motor1_speed_slider_value;//��������ٶ�
	u16 win_sys3_motor2_speed_slider_value;//��������ٶ�
	/**************ϵͳ4***********************/
	lv_obj_t * win_sys4;
	u8 win_sys4_finish_loading_flag;
	#define WIN_SYS4_FINISHED 1
	#define WIN_SYS4_LOADING 0
	//���ⰴť
	lv_obj_t * win_sys4_close_btn;
	lv_obj_t * win_sys4_msg_btn;	
	//����
	lv_obj_t * win_sys4_msgbox_msg;	//״̬��ʾ��Ϣ��
	//lv_slider
	lv_obj_t * win_sys4_slider_1;//��������ٶ�
	lv_obj_t * win_sys4_slider_2;//��������ٶ�
	lv_obj_t * win_sys4_slider_1_label;//��������ٶ�
	lv_obj_t * win_sys4_slider_2_label;//��������ٶ�
	u16 win_sys4_slider_1_value;//��������ٶ�
	u16 win_sys4_slider_2_value;//��������ٶ�
	/**************���ý���********************/
	//����
	lv_obj_t * win_set;
	lv_obj_t * win_set_close_btn;
	lv_obj_t * win_set_forward_btn;
	lv_obj_t * win_set_back_btn;
	lv_obj_t * win_set_settime_btn;
	lv_obj_t * win_set_sys2_btn;
	lv_obj_t * win_set_sys3_btn;
	lv_obj_t * win_set_sys4_btn;
	//����ʱ��
	lv_obj_t * win_settime;
	lv_obj_t * win_settime_roller_year;
	lv_obj_t * win_settime_roller_month;
	lv_obj_t * win_settime_roller_date;
	lv_obj_t * win_settime_roller_weekday;	
	lv_obj_t * win_settime_roller_hour;
	lv_obj_t * win_settime_roller_min;
	lv_obj_t * win_settime_roller_second;
	lv_obj_t * win_settime_close_btn;
	lv_obj_t * win_settime_ok_btn;
	//sdCard����
	lv_obj_t * win_setSDCard;
	lv_obj_t * win_setSDCard_close_btn;
	lv_obj_t * win_setSDCard_refresh_btn;	
	lv_obj_t * win_setSDCard_label;
	//��ť
	u16 btn_beep_sound_time;
	u8 btn_beep_sound_flag;
	//RTC
	u16 time_timer_count;
	char time[50];
	Time timeset;
	//SD Card
}MY_LV_OBJ;


extern MY_LV_OBJ my_lv_obj;

void gettime(u8 flag,char resut_char[50]);
void lvgl_init(void);//lgvl���ܳ�ʼ��
static void win_title_refresh(lv_task_t * task);//����ˢ������
static void win_SD_monitor(lv_task_t * task);//SD���ǲ��ǻ����ŵļ�����
void win_sys1_function(void);
void win_sys2_function(void);
static void win_function_monitor(lv_task_t * task);//�ճ�����
static void win_motor_function(lv_task_t * task);



#endif
