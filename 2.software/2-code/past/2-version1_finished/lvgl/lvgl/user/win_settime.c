#include "win_settime.h" 
#include "mylvgl.h"

void show_win_settime(void)
{
	/**************win界面***********************/
	my_lv_obj.win_settime = lv_win_create(my_lv_obj.scr, NULL);//创建MENU界面
	gettime(my_lv_obj.win_flag,my_lv_obj.time);//显示时间和界面名称
	lv_win_set_title(my_lv_obj.win_settime, my_lv_obj.time);
//	lv_obj_set_event_cb(my_lv_obj.win_set, win_set_title_handler);//设置回调函数
//	
	
	/**************滚动条***********************/
	u16 i = 0;
	char buf[12] = { 0 };
	const char year[] = "2019\n2020\n2021\n2022\n2023\n2024\n2025\n2026\n2027";
	const char month[] = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12";
	char date[100] = { 0 };
	const char days[] = "Mon\nTue\nWed\nThur\nFri\nSat\nSun";
	char hour[100] = { 0 };
	char min[200] = { 0 };	
	for (i = 1; i <= 31; i++) {
		if (i < 31)
			sprintf(buf, "%d\n", i);
		else
			sprintf(buf, "%d", i);
		strcat(date, buf);
	}
	for (i = 0; i <= 23; i++) {
		if (i < 23)
			sprintf(buf, "%d\n", i);
		else
			sprintf(buf, "%d", i);
		strcat(hour, buf);
	}
	for (i = 0; i <= 58; i+=2) {
		if (i < 58)
			sprintf(buf, "%d\n", i);
		else
			sprintf(buf, "%d", i);
		strcat(min, buf);
	}
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	RTC_GetDate(RTC_Format_BIN,&RTC_DateStruct);
	my_lv_obj.timeset.year = RTC_DateStruct.RTC_Year;
	my_lv_obj.timeset.month = RTC_DateStruct.RTC_Month;
	my_lv_obj.timeset.date = RTC_DateStruct.RTC_Date;
	my_lv_obj.timeset.weekday = RTC_DateStruct.RTC_WeekDay;
	my_lv_obj.timeset.hour = RTC_TimeStruct.RTC_Hours;
	my_lv_obj.timeset.min = RTC_TimeStruct.RTC_Minutes;
	my_lv_obj.win_settime_roller_year = lv_roller_create(my_lv_obj.win_settime, NULL);
	lv_obj_set_pos(my_lv_obj.win_settime_roller_year, 50, 50);//设置坐标
	lv_roller_set_options(my_lv_obj.win_settime_roller_year, year, LV_ROLLER_MODE_INIFINITE);// 添加内容
	lv_obj_set_width(my_lv_obj.win_settime_roller_year, 100);//设置宽度
	lv_roller_set_visible_row_count(my_lv_obj.win_settime_roller_year, 9);//设置显示的行数
	lv_obj_set_event_cb(my_lv_obj.win_settime_roller_year, win_settime_roller_handler);//设置事件回调函数
	lv_roller_set_selected(my_lv_obj.win_settime_roller_year, my_lv_obj.timeset.year-19, true);//手动设置选择项
	
	my_lv_obj.win_settime_roller_month = lv_roller_create(my_lv_obj.win_settime, NULL);
	lv_obj_set_pos(my_lv_obj.win_settime_roller_month, 170, 50);
	lv_roller_set_options(my_lv_obj.win_settime_roller_month, month, LV_ROLLER_MODE_INIFINITE);
	lv_obj_set_width(my_lv_obj.win_settime_roller_month, 50);
	lv_roller_set_visible_row_count(my_lv_obj.win_settime_roller_month, 9);
	lv_obj_set_event_cb(my_lv_obj.win_settime_roller_month, win_settime_roller_handler);
	lv_roller_set_selected(my_lv_obj.win_settime_roller_month, my_lv_obj.timeset.month - 1, true);
	
	my_lv_obj.win_settime_roller_date = lv_roller_create(my_lv_obj.win_settime, NULL);
	lv_obj_set_pos(my_lv_obj.win_settime_roller_date, 340, 50);
	lv_roller_set_options(my_lv_obj.win_settime_roller_date, date, LV_ROLLER_MODE_INIFINITE);
	lv_obj_set_width(my_lv_obj.win_settime_roller_date, 50);
	lv_roller_set_visible_row_count(my_lv_obj.win_settime_roller_date,9);
	lv_obj_set_event_cb(my_lv_obj.win_settime_roller_date, win_settime_roller_handler);
	lv_roller_set_selected(my_lv_obj.win_settime_roller_date, my_lv_obj.timeset.date - 1, true);
	
	my_lv_obj.win_settime_roller_weekday = lv_roller_create(my_lv_obj.win_settime, NULL);
	lv_obj_set_pos(my_lv_obj.win_settime_roller_weekday, 460, 50);
	lv_roller_set_options(my_lv_obj.win_settime_roller_weekday, days, LV_ROLLER_MODE_INIFINITE);
	lv_obj_set_width(my_lv_obj.win_settime_roller_weekday, 100);
	lv_roller_set_visible_row_count(my_lv_obj.win_settime_roller_weekday, 9);
	lv_obj_set_event_cb(my_lv_obj.win_settime_roller_date, win_settime_roller_handler);
	lv_roller_set_selected(my_lv_obj.win_settime_roller_weekday, my_lv_obj.timeset.weekday - 1, true);
	
	my_lv_obj.win_settime_roller_hour = lv_roller_create(my_lv_obj.win_settime, NULL);
	lv_obj_set_pos(my_lv_obj.win_settime_roller_hour, 580, 50);
	lv_roller_set_options(my_lv_obj.win_settime_roller_hour, hour, LV_ROLLER_MODE_INIFINITE);
	lv_obj_set_width(my_lv_obj.win_settime_roller_hour, 50);
	lv_roller_set_visible_row_count(my_lv_obj.win_settime_roller_hour, 9);
	lv_obj_set_event_cb(my_lv_obj.win_settime_roller_hour, win_settime_roller_handler);
	lv_roller_set_selected(my_lv_obj.win_settime_roller_hour, my_lv_obj.timeset.hour, true);
	
	my_lv_obj.win_settime_roller_min = lv_roller_create(my_lv_obj.win_settime, NULL);
	lv_obj_set_pos(my_lv_obj.win_settime_roller_min, 670, 50);
	lv_roller_set_options(my_lv_obj.win_settime_roller_min, min, LV_ROLLER_MODE_INIFINITE);
	lv_obj_set_width(my_lv_obj.win_settime_roller_min, 50);
	lv_roller_set_visible_row_count(my_lv_obj.win_settime_roller_min, 9);
	lv_obj_set_event_cb(my_lv_obj.win_settime_roller_min, win_settime_roller_handler);
	lv_roller_set_selected(my_lv_obj.win_settime_roller_min, my_lv_obj.timeset.min/2, true);

	/**************按钮***********************/
	my_lv_obj.win_settime_close_btn = lv_win_add_btn(my_lv_obj.win_settime, LV_SYMBOL_CLOSE);
	my_lv_obj.win_settime_ok_btn = lv_win_add_btn(my_lv_obj.win_settime, LV_SYMBOL_OK);
//	my_lv_obj.win_set_forward_btn = lv_win_add_btn(my_lv_obj.win_set, LV_SYMBOL_RIGHT);
//	my_lv_obj.win_set_back_btn = lv_win_add_btn(my_lv_obj.win_set, LV_SYMBOL_LEFT);
//	
	lv_obj_set_event_cb(my_lv_obj.win_settime_ok_btn, win_settime_ok_btn_handler);//设置回调函数
	lv_obj_set_event_cb(my_lv_obj.win_settime_close_btn, win_settime_close_btn_handler);//设置回调函数
//	
//	lv_obj_t * label;
//	//按钮一
//  my_lv_obj.win_set_settime_btn = lv_btn_create(my_lv_obj.win_set , NULL);//创建按钮
//	lv_style_set_radius(&my_lv_obj.style, LV_STATE_DEFAULT, 10);//输入风格
//	lv_obj_add_style(my_lv_obj.win_set_settime_btn, LV_BTN_PART_MAIN, &my_lv_obj.style);
//  lv_obj_set_size(my_lv_obj.win_set_settime_btn, 150, 100);//设置按钮大小
//  label = lv_label_create(my_lv_obj.win_set_settime_btn, NULL);
//  lv_label_set_text(label, "Set Time");
//	//按钮二
//  my_lv_obj.win_set_sys2_btn = lv_btn_create(my_lv_obj.win_set, my_lv_obj.win_set_settime_btn);
//  label = lv_label_create(my_lv_obj.win_set_sys2_btn, NULL);
//   lv_label_set_text(label, "system2");
//	//按钮三
//  my_lv_obj.win_set_sys3_btn = lv_btn_create(my_lv_obj.win_set, my_lv_obj.win_set_settime_btn);
//  label = lv_label_create(my_lv_obj.win_set_sys3_btn, NULL);
//  lv_label_set_text(label, "system3");
//	//按钮四
//  my_lv_obj.win_set_sys4_btn = lv_btn_create(my_lv_obj.win_set, my_lv_obj.win_set_settime_btn);
//  label = lv_label_create(my_lv_obj.win_set_sys4_btn, NULL);
//  lv_label_set_text(label, "system4");	

//	//设置位置
//	lv_obj_align(my_lv_obj.win_set_settime_btn, NULL, LV_ALIGN_CENTER, -300, 20);
//  lv_obj_align(my_lv_obj.win_set_sys2_btn, NULL, LV_ALIGN_CENTER, -100, 20);
//  lv_obj_align(my_lv_obj.win_set_sys3_btn, NULL, LV_ALIGN_CENTER, 100, 20);
//  lv_obj_align(my_lv_obj.win_set_sys4_btn, NULL, LV_ALIGN_CENTER, 300, 20);
//	//设置回调函数
//	lv_obj_set_event_cb(my_lv_obj.win_set_settime_btn, win_set_settime_btn_handler);
//  lv_obj_set_event_cb(my_lv_obj.win_set_sys2_btn, win_set_sys2_btn_handler);
//  lv_obj_set_event_cb(my_lv_obj.win_set_sys3_btn, win_set_sys3_btn_handler);
//  lv_obj_set_event_cb(my_lv_obj.win_set_sys4_btn, win_set_sys4_btn_handler);
//	
}
void win_settime_roller_handler(lv_obj_t * obj, lv_event_t event) 
{
	if (event == LV_EVENT_VALUE_CHANGED) {
		
		my_lv_obj.timeset.year = lv_roller_get_selected(my_lv_obj.win_settime_roller_year)+19;
		my_lv_obj.timeset.month = lv_roller_get_selected(my_lv_obj.win_settime_roller_month)+1;
		my_lv_obj.timeset.date = lv_roller_get_selected(my_lv_obj.win_settime_roller_date)+1;
		my_lv_obj.timeset.weekday = lv_roller_get_selected(my_lv_obj.win_settime_roller_weekday)+1;		
		my_lv_obj.timeset.hour = lv_roller_get_selected(my_lv_obj.win_settime_roller_hour);
		my_lv_obj.timeset.min = lv_roller_get_selected(my_lv_obj.win_settime_roller_min)*2;
		
		char temp[100];
		memset(temp, 0, sizeof(temp));
		lv_roller_get_selected_str(my_lv_obj.win_settime_roller_year, temp, sizeof(temp));
		strcpy(my_lv_obj.time, "Set Time ");
		strcat(my_lv_obj.time, temp);
		strcat(my_lv_obj.time, "-");
		lv_roller_get_selected_str(my_lv_obj.win_settime_roller_month, temp, sizeof(temp));
		strcat(my_lv_obj.time, temp);
		strcat(my_lv_obj.time, "-");
		lv_roller_get_selected_str(my_lv_obj.win_settime_roller_date, temp, sizeof(temp));
		strcat(my_lv_obj.time, temp);
		strcat(my_lv_obj.time, " ");
		lv_roller_get_selected_str(my_lv_obj.win_settime_roller_weekday, temp, sizeof(temp));
		strcat(my_lv_obj.time, temp);
		strcat(my_lv_obj.time, " ");
		sprintf(temp, "%02d", lv_roller_get_selected(my_lv_obj.win_settime_roller_hour));
		strcat(my_lv_obj.time, temp);
		strcat(my_lv_obj.time, ":");
		sprintf(temp, "%02d", lv_roller_get_selected(my_lv_obj.win_settime_roller_min)*2);
		strcat(my_lv_obj.time, temp);
		strcat(my_lv_obj.time, ":");
		strcat(my_lv_obj.time, "00");
		
		lv_win_set_title(my_lv_obj.win_settime, my_lv_obj.time);
	
	}
}
void win_settime_ok_btn_handler(lv_obj_t * obj, lv_event_t event) 
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		RTC_Set_Time(my_lv_obj.timeset.hour,my_lv_obj.timeset.min,0,RTC_H12_PM);
		RTC_Set_Date(my_lv_obj.timeset.year,my_lv_obj.timeset.month,my_lv_obj.timeset.date,my_lv_obj.timeset.weekday);
	}
}
void win_settime_close_btn_handler(lv_obj_t * obj, lv_event_t event) 
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_SET;
		lv_obj_del(my_lv_obj.win_settime);
	}
}
