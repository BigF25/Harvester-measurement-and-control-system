#include "mylvgl.h"


//lgvl功能初始化
extern MY_LV_OBJ my_lv_obj;

void gettime(u8 flag,char resut_char[50])
{
	const char days[7][5] = {"Mon","Tue","Wed","Thur","Fri","Sat","Sun"};
	char temp[50];
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
	switch(flag)
	{
		case WIN_MENU:		strcpy(resut_char,"Menu     ");break;
		case WIN_SYS1:		strcpy(resut_char,"5801			");break;
		case WIN_SYS2:		strcpy(resut_char,"7017			");break;
		case WIN_SYS3:		strcpy(resut_char,"4055			");break;
		case WIN_SYS4:		strcpy(resut_char,"3402			");break;
		case WIN_SET:			strcpy(resut_char,"Setting  ");break;
		case WIN_SETTIME:	strcpy(resut_char,"Set Time ");break;
		case WIN_SDCard:	strcpy(resut_char,"SD Card  ");break;
	}
	sprintf(temp, "20%d-%02d-%02d %s ", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date, days[RTC_DateStruct.RTC_WeekDay-1]);
	strcat(resut_char,temp);
	sprintf(temp, "%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes, RTC_TimeStruct.RTC_Seconds);
	strcat(resut_char,temp);
	if(my_lv_obj.SDCard_flag == SD_ERROR)
		strcat(resut_char," SD Card Error");
	else
		strcat(resut_char," SD Card Ready");
}
void lvgl_init(void) 
{
  lv_init();
  lv_port_disp_init();        // 显示器初始化
  lv_port_indev_init();       // 输入设备初始化
  // lv_port_fs_init();          // 文件系统设备初始化
	
	my_lv_obj.scr = lv_scr_act();
	my_lv_obj.win_flag = WIN_MENU;
	my_lv_obj.btn_beep_sound_time = 0;
	my_lv_obj.time_timer_count = 0;
	my_lv_obj.win_sys1_can_rec_switch_flag = WIN_SYS1_SWITCH_CLOSE;
	my_lv_obj.win_sys1_sd_rec_switch_flag = WIN_SYS1_SWITCH_CLOSE;	
	my_lv_obj.win_sys1_finish_loading_flag = WIN_SYS1_LOADING;
	my_lv_obj.SDCard_flag = SD_ERROR;	
	my_lv_obj.win_sys1_table_count = 0;
	my_lv_obj.win_title_refresh_task = lv_task_create(win_title_refresh, 100, LV_TASK_PRIO_HIGHEST, NULL);//title 刷新任务
	my_lv_obj.win_SD_monitor_task = lv_task_create(win_SD_monitor, 20, LV_TASK_PRIO_HIGH, NULL);//SD监视器
	my_lv_obj.win_function_monitor_task = lv_task_create(win_function_monitor, 10, LV_TASK_PRIO_MID, NULL);//任务监视器
	my_lv_obj.win_sys3_motor1_speed_slider_value = 1;
	my_lv_obj.win_sys3_motor2_speed_slider_value = 1;
}
static void win_title_refresh(lv_task_t * task)
{
	gettime(my_lv_obj.win_flag,my_lv_obj.time);
	switch(my_lv_obj.win_flag)
	{
		case WIN_MENU:lv_win_set_title(my_lv_obj.win_menu, my_lv_obj.time);break;
		case WIN_SYS1:lv_win_set_title(my_lv_obj.win_sys1, my_lv_obj.time);break;
		case WIN_SYS2:lv_win_set_title(my_lv_obj.win_sys2, my_lv_obj.time);break;
		case WIN_SYS3:lv_win_set_title(my_lv_obj.win_sys3, my_lv_obj.time);break;
		case WIN_SYS4:lv_win_set_title(my_lv_obj.win_sys4, my_lv_obj.time);break;
		case WIN_SET:lv_win_set_title(my_lv_obj.win_set, my_lv_obj.time);break;
		case WIN_SDCard:lv_win_set_title(my_lv_obj.win_setSDCard, my_lv_obj.time);break;
	}
}
static void win_SD_monitor(lv_task_t * task)
{
	if(SD_GetState() == 0xFF)
	{
		my_lv_obj.SDCard_flag = SD_ERROR;
		my_lv_obj.win_sys1_sd_rec_switch_flag = WIN_SYS1_SWITCH_CLOSE;
	}
}
void win_sys1_function()
{
	//CAN接收数据
	if(my_lv_obj.win_sys1_can_rec_switch_flag)
	{
		rec_5801_ImpulseValue(ADDRESS_5801_1, my_lv_obj.win_sys1_5801_result_int_1);
		rec_5801_ImpulseValue(ADDRESS_5801_2, my_lv_obj.win_sys1_5801_result_int_2);
		for(int i=0; i<8; i++)
		{
			sprintf(my_lv_obj.win_sys1_5801_result_char_1[i], "%.2f", my_lv_obj.win_sys1_5801_result_int_1[i]*0.6);
		}
		sprintf(my_lv_obj.win_sys1_5801_result_char_2[0], "%.2f", my_lv_obj.win_sys1_5801_result_int_2[0]*0.6);
		sprintf(my_lv_obj.win_sys1_5801_result_char_2[1], "%.2f", my_lv_obj.win_sys1_5801_result_int_2[1]*0.6);
		sprintf(my_lv_obj.win_sys1_5801_result_char_2[6], "%d", my_lv_obj.win_sys1_5801_result_int_2[6]);
		sprintf(my_lv_obj.win_sys1_5801_result_char_2[7], "%d", my_lv_obj.win_sys1_5801_result_int_2[7]);
	}
	//界面刷新
	if(my_lv_obj.win_sys1_finish_loading_flag == WIN_SYS1_FINISHED && my_lv_obj.win_sys1_can_rec_switch_flag == WIN_SYS1_SWITCH_OPEN)
	{
		win_sys1_table_handler_event_send();
	}
	//SD卡写入
	if(my_lv_obj.SDCard_flag == SD_READY && my_lv_obj.win_sys1_sd_rec_switch_flag == WIN_SYS1_SWITCH_OPEN)
	{
		FIL fil;
		UINT bww;
		u8 res;
		char temp[200];
		RTC_TimeTypeDef RTC_TimeStruct;
		RTC_DateTypeDef RTC_DateStruct;
		RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
		RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
		sprintf(temp, "0:/5801_20%d-%02d-%02d.xls", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date);
		res=f_open(&fil,temp,FA_CREATE_NEW | FA_WRITE);
		if(res)
		{
			f_open(&fil,temp,FA_OPEN_EXISTING | FA_WRITE);
			res=f_lseek(&fil,f_size(&fil));
			sprintf(temp, "20%d-%02d-%02d\t%02d:%02d:%02d\t", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date,RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds);
			for(int i=0; i<8; i++)
			{
				char tempp[20];
				sprintf(tempp, "%s\t", my_lv_obj.win_sys1_5801_result_char_1[i]);
				strcat(temp,tempp);
			}
			for(int i=0; i<4; i++)
			{
				char tempp[20];
				if(i==2) i=6;
				if(i==3) i=7;
				sprintf(tempp, "%s\t", my_lv_obj.win_sys1_5801_result_char_2[i]);
				if(i==6) i=2;
				if(i==7) i=3;
				strcat(temp,tempp);
			}
			strcat(temp,"\n");
			f_write(&fil,temp,strlen(temp), &bww);
			f_close(&fil);
		}
		else
		{
			sprintf(temp, "日期\t时间\t前进速度\t拨禾轮转速\t输送槽转速\t割台搅龙转速\t滚筒转速\t风机转速\t冗余绞龙转速\t籽粒绞龙转速\t碎草装置转速\t发动机转速\t籽粒夹带损失\t籽粒清选损失\n");
			f_write(&fil,temp,strlen(temp), &bww);
			f_close(&fil);
		}
	}
}
void win_sys2_function()
{
	//CAN接收数据
	if(my_lv_obj.win_sys2_can_rec_switch_flag)
	{
		rec_7017_AiValue(ADDRESS_7017, my_lv_obj.win_sys2_7017_result_int);
		for(int i=0; i<8; i++)
		{
			sprintf(my_lv_obj.win_sys2_7017_result_char[i], "%d", my_lv_obj.win_sys2_7017_result_int[i]);
		}
	}
	//界面刷新
	if(my_lv_obj.win_sys2_finish_loading_flag == WIN_SYS2_FINISHED && my_lv_obj.win_sys2_can_rec_switch_flag == WIN_SYS2_SWITCH_OPEN)
	{
		win_sys2_table_handler_event_send();
	}
	//SD卡写入
	if(my_lv_obj.SDCard_flag == SD_READY && my_lv_obj.win_sys2_sd_rec_switch_flag == WIN_SYS2_SWITCH_OPEN)
	{
		FIL fil;
		UINT bww;
		u8 res;
		char temp[200];
		RTC_TimeTypeDef RTC_TimeStruct;
		RTC_DateTypeDef RTC_DateStruct;
		RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
		RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
		sprintf(temp, "0:/7017_20%d-%02d-%02d.xls", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date);
		res=f_open(&fil,temp,FA_CREATE_NEW | FA_WRITE);
		if(res)
		{
			f_open(&fil,temp,FA_OPEN_EXISTING | FA_WRITE);
			res=f_lseek(&fil,f_size(&fil));
			sprintf(temp, "20%d-%02d-%02d\t%02d:%02d:%02d\t", RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date,RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds);
			for(int i=0; i<5; i++)
			{
				char tempp[20];
				sprintf(tempp, "%s\t", my_lv_obj.win_sys2_7017_result_char[i]);
				strcat(temp,tempp);
			}
			strcat(temp,"\n");
			f_write(&fil,temp,strlen(temp), &bww);
			f_close(&fil);
		}
		else
		{
			sprintf(temp, "日期\t时间\t拨禾轮高度\t割台高度\t鱼鳞筛开度\t仿形板1角度\t仿形板2角度\n");
			f_write(&fil,temp,strlen(temp), &bww);
			f_close(&fil);
		}
	}
}
void win_function_monitor(lv_task_t * task)
{
	if(SD_GetState() == 0xFF)
	{
		my_lv_obj.SDCard_flag = SD_ERROR;
		my_lv_obj.win_sys1_sd_rec_switch_flag = WIN_SYS1_SWITCH_CLOSE;
		my_lv_obj.win_sys2_sd_rec_switch_flag = WIN_SYS2_SWITCH_CLOSE;
	}
	win_sys1_function();
	win_sys2_function();
}

