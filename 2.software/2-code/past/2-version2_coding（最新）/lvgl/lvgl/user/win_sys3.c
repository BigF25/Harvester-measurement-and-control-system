#include "win_sys3.h" 
#include "mylvgl.h"
#include "beep.h"
#include "rtc.h"

void show_win_sys3(void)
{
	/**************winΩÁ√Ê***********************/
	my_lv_obj.win_sys3 = lv_win_create(my_lv_obj.scr, NULL);
	gettime(my_lv_obj.win_flag,my_lv_obj.time);
	lv_win_set_title(my_lv_obj.win_sys3, my_lv_obj.time);
	/*****************∞¥≈•********************/
	my_lv_obj.win_sys3_close_btn = lv_win_add_btn(my_lv_obj.win_sys3, LV_SYMBOL_CLOSE);
	my_lv_obj.win_sys3_msg_btn = lv_win_add_btn(my_lv_obj.win_sys3, LV_SYMBOL_WARNING);
  lv_obj_set_event_cb(my_lv_obj.win_sys3_close_btn, win_sys3_close_btn_handler);					//…Ë÷√ªÿµ˜∫Ø ˝
  lv_obj_set_event_cb(my_lv_obj.win_sys3_msg_btn, win_sys3_msg_btn_handler);							//…Ë÷√ªÿµ˜∫Ø ˝
	/**************ª¨∂Øø™πÿ***********************/
	my_lv_obj.win_sys3_motor1_ena_switch = lv_switch_create(my_lv_obj.win_sys3, NULL);
	my_lv_obj.win_sys3_motor1_dir_switch = lv_switch_create(my_lv_obj.win_sys3, NULL);
	my_lv_obj.win_sys3_motor2_ena_switch = lv_switch_create(my_lv_obj.win_sys3, NULL);
	my_lv_obj.win_sys3_motor2_dir_switch = lv_switch_create(my_lv_obj.win_sys3, NULL);
	lv_obj_align(my_lv_obj.win_sys3_motor1_ena_switch, my_lv_obj.win_sys3, LV_ALIGN_CENTER, -80, -100);
	lv_obj_align(my_lv_obj.win_sys3_motor1_dir_switch, my_lv_obj.win_sys3, LV_ALIGN_CENTER, 80, -100);
	lv_obj_align(my_lv_obj.win_sys3_motor2_ena_switch, my_lv_obj.win_sys3, LV_ALIGN_CENTER, -80, 80);
	lv_obj_align(my_lv_obj.win_sys3_motor2_dir_switch, my_lv_obj.win_sys3, LV_ALIGN_CENTER, 80, 80);
	lv_switch_set_anim_time(my_lv_obj.win_sys3_motor1_ena_switch, 0);//πÿ±’∂Øª≠
	lv_switch_set_anim_time(my_lv_obj.win_sys3_motor1_dir_switch, 0);//πÿ±’∂Øª≠
	lv_switch_set_anim_time(my_lv_obj.win_sys3_motor2_ena_switch, 0);//πÿ±’∂Øª≠
	lv_switch_set_anim_time(my_lv_obj.win_sys3_motor2_dir_switch, 0);//πÿ±’∂Øª≠
	lv_obj_set_event_cb(my_lv_obj.win_sys3_motor1_ena_switch, win_sys3_motor1_ena_switch_handler);	//…Ë÷√ªÿµ˜∫Ø ˝
	lv_obj_set_event_cb(my_lv_obj.win_sys3_motor1_dir_switch, win_sys3_motor1_dir_switch_handler);	//…Ë÷√ªÿµ˜∫Ø ˝
	lv_obj_set_event_cb(my_lv_obj.win_sys3_motor2_ena_switch, win_sys3_motor2_ena_switch_handler);	//…Ë÷√ªÿµ˜∫Ø ˝
	lv_obj_set_event_cb(my_lv_obj.win_sys3_motor2_dir_switch, win_sys3_motor2_dir_switch_handler);	//…Ë÷√ªÿµ˜∫Ø ˝
	/**************ª¨∂Øø™πÿµƒ±Í«©*****************/
	lv_obj_t * win_sys3_switch_temp_label1;
	lv_obj_t * win_sys3_switch_temp_label2;
	lv_obj_t * win_sys3_switch_temp_label3;
	lv_obj_t * win_sys3_switch_temp_label4;
	win_sys3_switch_temp_label1 = lv_label_create(my_lv_obj.win_sys3, NULL);
	win_sys3_switch_temp_label2 = lv_label_create(my_lv_obj.win_sys3, NULL);
	win_sys3_switch_temp_label3 = lv_label_create(my_lv_obj.win_sys3, NULL);
	win_sys3_switch_temp_label4 = lv_label_create(my_lv_obj.win_sys3, NULL);
	lv_obj_add_style(win_sys3_switch_temp_label1, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(win_sys3_switch_temp_label2, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(win_sys3_switch_temp_label3, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(win_sys3_switch_temp_label4, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
  lv_label_set_text(win_sys3_switch_temp_label1, "È±ºÈ≥ûÁîµÂä®Áº∏ \n   ÂêØÂÅú ");
  lv_label_set_text(win_sys3_switch_temp_label2, "È±ºÈ≥ûÁîµÂä®Áº∏ \n   Ê≠£Âèç ");
  lv_label_set_text(win_sys3_switch_temp_label3, "ÂâçËøõÈÄüÂ∫¶Ê≠•ËøõÁîµÊú∫  \n      ÂêØÂÅú ");
  lv_label_set_text(win_sys3_switch_temp_label4, "ÂâçËøõÈÄüÂ∫¶Ê≠•ËøõÁîµÊú∫  \n      Ê≠£Âèç ");
	lv_obj_align(win_sys3_switch_temp_label1, my_lv_obj.win_sys3_motor1_ena_switch, LV_ALIGN_CENTER, 0, -40);
	lv_obj_align(win_sys3_switch_temp_label2, my_lv_obj.win_sys3_motor1_dir_switch, LV_ALIGN_CENTER, 0, -40);
	lv_obj_align(win_sys3_switch_temp_label3, my_lv_obj.win_sys3_motor2_ena_switch, LV_ALIGN_CENTER, 0, -40);
	lv_obj_align(win_sys3_switch_temp_label4, my_lv_obj.win_sys3_motor2_dir_switch, LV_ALIGN_CENTER, 0, -40);
	my_lv_obj.win_sys3_motor1_ena_switch_state_label = lv_label_create(my_lv_obj.win_sys3, NULL);
	my_lv_obj.win_sys3_motor1_dir_switch_state_label = lv_label_create(my_lv_obj.win_sys3, NULL);
	my_lv_obj.win_sys3_motor2_ena_switch_state_label = lv_label_create(my_lv_obj.win_sys3, NULL);
	my_lv_obj.win_sys3_motor2_dir_switch_state_label = lv_label_create(my_lv_obj.win_sys3, NULL);
	lv_obj_add_style(my_lv_obj.win_sys3_motor1_ena_switch_state_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(my_lv_obj.win_sys3_motor1_dir_switch_state_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(my_lv_obj.win_sys3_motor2_ena_switch_state_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(my_lv_obj.win_sys3_motor2_dir_switch_state_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_align(my_lv_obj.win_sys3_motor1_ena_switch_state_label, my_lv_obj.win_sys3_motor1_ena_switch, LV_ALIGN_CENTER, 0, 25);
	lv_obj_align(my_lv_obj.win_sys3_motor1_dir_switch_state_label, my_lv_obj.win_sys3_motor1_dir_switch, LV_ALIGN_CENTER, 0, 25);
	lv_obj_align(my_lv_obj.win_sys3_motor2_ena_switch_state_label, my_lv_obj.win_sys3_motor2_ena_switch, LV_ALIGN_CENTER, 0, 25);
	lv_obj_align(my_lv_obj.win_sys3_motor2_dir_switch_state_label, my_lv_obj.win_sys3_motor2_dir_switch, LV_ALIGN_CENTER, 0, 25);
	/**************slider*****************/
	my_lv_obj.win_sys3_motor1_speed_slider = lv_slider_create(my_lv_obj.win_sys3, NULL);
	my_lv_obj.win_sys3_motor2_speed_slider = lv_slider_create(my_lv_obj.win_sys3, NULL);
	lv_obj_set_width(my_lv_obj.win_sys3_motor1_speed_slider, 400);
	lv_obj_set_width(my_lv_obj.win_sys3_motor2_speed_slider, 400);
	lv_obj_align(my_lv_obj.win_sys3_motor1_speed_slider, my_lv_obj.win_sys3, LV_ALIGN_CENTER, 0, -20);
	lv_obj_align(my_lv_obj.win_sys3_motor2_speed_slider, my_lv_obj.win_sys3, LV_ALIGN_CENTER, 0, 160);
	lv_slider_set_anim_time(my_lv_obj.win_sys3_motor1_speed_slider, 0);//πÿ±’∂Øª≠
	lv_slider_set_anim_time(my_lv_obj.win_sys3_motor2_speed_slider, 0);//πÿ±’∂Øª≠
	lv_slider_set_range(my_lv_obj.win_sys3_motor1_speed_slider, 1, 10);
	lv_slider_set_range(my_lv_obj.win_sys3_motor2_speed_slider, 1, 10);
	lv_obj_set_event_cb(my_lv_obj.win_sys3_motor1_speed_slider, win_sys3_motor1_speed_slider_handler);		//…Ë÷√ªÿµ˜∫Ø ˝
	lv_obj_set_event_cb(my_lv_obj.win_sys3_motor2_speed_slider, win_sys3_motor2_speed_slider_handler);		//…Ë÷√ªÿµ˜∫Ø ˝
	/**************sliderµƒ±Í«©*****************/
	my_lv_obj.win_sys3_motor1_speed_slider_label = lv_label_create(my_lv_obj.win_sys3, NULL);
	my_lv_obj.win_sys3_motor2_speed_slider_label = lv_label_create(my_lv_obj.win_sys3, NULL);
	lv_obj_add_style(my_lv_obj.win_sys3_motor1_speed_slider_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(my_lv_obj.win_sys3_motor2_speed_slider_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_align(my_lv_obj.win_sys3_motor1_speed_slider_label, my_lv_obj.win_sys3_motor1_speed_slider, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
	lv_obj_align(my_lv_obj.win_sys3_motor2_speed_slider_label, my_lv_obj.win_sys3_motor2_speed_slider, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
	win_sys3_state_show();//À¢–¬sys3◊¥Ã¨∫Õ±Í«©◊¥Ã¨
	my_lv_obj.win_sys3_finish_loading_flag = WIN_SYS3_FINISHED;
}
void win_sys3_close_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_MENU;
		my_lv_obj.win_sys3_finish_loading_flag = WIN_SYS3_LOADING;
		lv_obj_del(my_lv_obj.win_sys3);
	}
}
void win_sys3_msg_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys3_msgbox_msg=lv_msgbox_create(my_lv_obj.win_sys3, NULL);
		static const char * btns[] ={"CLOSE", "OPEN", ""};
		lv_msgbox_add_btns(my_lv_obj.win_sys3_msgbox_msg, btns);
		lv_msgbox_set_anim_time(my_lv_obj.win_sys3_msgbox_msg, 0);//πÿ±’∂Øª≠
	}
}
void win_sys3_motor1_ena_switch_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys3_motor1_ena_switch_flag = lv_switch_get_state(my_lv_obj.win_sys3_motor1_ena_switch);
		if(my_lv_obj.win_sys3_motor1_ena_switch_flag == WIN_SYS3_SWITCH_CLOSE) 
			my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value & 0xFE;//11111110
		else if(my_lv_obj.win_sys3_motor1_ena_switch_flag == WIN_SYS3_SWITCH_OPEN)
			my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value | 0x01;//00000001
		Set_4055_Switchoutput(ADDRESS_4055, my_lv_obj.win_sys3_motor_value);
		win_sys3_state_show();
	}
}
void win_sys3_motor1_dir_switch_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys3_motor1_dir_switch_flag = lv_switch_get_state(my_lv_obj.win_sys3_motor1_dir_switch);
		if(my_lv_obj.win_sys3_motor1_dir_switch_flag == WIN_SYS3_SWITCH_CLOSE) 
			my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value & 0xFD;//11111101
		else if(my_lv_obj.win_sys3_motor1_dir_switch_flag == WIN_SYS3_SWITCH_OPEN)
			my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value | 0x02;//00000010
		Set_4055_Switchoutput(ADDRESS_4055, my_lv_obj.win_sys3_motor_value);
		win_sys3_state_show();
	}
}
void win_sys3_motor2_ena_switch_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys3_motor2_ena_switch_flag = lv_switch_get_state(my_lv_obj.win_sys3_motor2_ena_switch);
		if(my_lv_obj.win_sys3_motor2_ena_switch_flag == WIN_SYS3_SWITCH_CLOSE) 
			my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value & 0xDF;//11011111
		else if(my_lv_obj.win_sys3_motor2_ena_switch_flag == WIN_SYS3_SWITCH_OPEN)
			my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value | 0x20;//00100000
		Set_4055_Switchoutput(ADDRESS_4055, my_lv_obj.win_sys3_motor_value);
		win_sys3_state_show();
	}
}
void win_sys3_motor2_dir_switch_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys3_motor2_dir_switch_flag = lv_switch_get_state(my_lv_obj.win_sys3_motor2_dir_switch);
		if(my_lv_obj.win_sys3_motor2_dir_switch_flag == WIN_SYS3_SWITCH_CLOSE) 
			my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value & 0xBF;//10111111
		else if(my_lv_obj.win_sys3_motor2_dir_switch_flag == WIN_SYS3_SWITCH_OPEN)
			my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value | 0x40;//01000000
		Set_4055_Switchoutput(ADDRESS_4055, my_lv_obj.win_sys3_motor_value);
		win_sys3_state_show();
	}
}
void win_sys3_motor1_speed_slider_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_VALUE_CHANGED) 
	{
		my_lv_obj.win_sys3_motor1_speed_slider_value = lv_slider_get_value(my_lv_obj.win_sys3_motor1_speed_slider);
		win_sys3_state_show();
	}
}
void win_sys3_motor2_speed_slider_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_VALUE_CHANGED) 
	{
		my_lv_obj.win_sys3_motor2_speed_slider_value = lv_slider_get_value(my_lv_obj.win_sys3_motor2_speed_slider);
		win_sys3_state_show();
	}
}
void win_sys3_state_show(void)
{
	char temp[10];
	sprintf(temp, "ÈÄüÂ∫¶Ôºö %d", my_lv_obj.win_sys3_motor1_speed_slider_value);
	lv_label_set_text(my_lv_obj.win_sys3_motor1_speed_slider_label, temp);
	sprintf(temp, "ÈÄüÂ∫¶Ôºö %d", my_lv_obj.win_sys3_motor2_speed_slider_value);
	lv_label_set_text(my_lv_obj.win_sys3_motor2_speed_slider_label, temp);
	lv_slider_set_value(my_lv_obj.win_sys3_motor1_speed_slider, my_lv_obj.win_sys3_motor1_speed_slider_value, LV_ANIM_OFF);
	lv_slider_set_value(my_lv_obj.win_sys3_motor2_speed_slider, my_lv_obj.win_sys3_motor2_speed_slider_value, LV_ANIM_OFF);
	if(my_lv_obj.win_sys3_motor1_ena_switch_flag == WIN_SYS3_SWITCH_OPEN)
	{
		lv_switch_on(my_lv_obj.win_sys3_motor1_ena_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys3_motor1_ena_switch_state_label, "ÂêØÂä® ");
	}
	else if(my_lv_obj.win_sys3_motor1_ena_switch_flag == WIN_SYS3_SWITCH_CLOSE)
	{
		lv_switch_off(my_lv_obj.win_sys3_motor1_ena_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys3_motor1_ena_switch_state_label, "ÂÅúÊ≠¢ ");
	}
	if(my_lv_obj.win_sys3_motor1_dir_switch_flag == WIN_SYS3_SWITCH_OPEN)
	{
		lv_switch_on(my_lv_obj.win_sys3_motor1_dir_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys3_motor1_dir_switch_state_label, "Ê≠£ËΩ¨ ");
	}
	else if(my_lv_obj.win_sys3_motor1_dir_switch_flag == WIN_SYS3_SWITCH_CLOSE)
	{
		lv_switch_off(my_lv_obj.win_sys3_motor1_dir_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys3_motor1_dir_switch_state_label, "ÂèçËΩ¨ ");
	}	
		if(my_lv_obj.win_sys3_motor2_ena_switch_flag == WIN_SYS3_SWITCH_OPEN)
	{
		lv_switch_on(my_lv_obj.win_sys3_motor2_ena_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys3_motor2_ena_switch_state_label, "ÂêØÂä® ");
	}
	else if(my_lv_obj.win_sys3_motor2_ena_switch_flag == WIN_SYS3_SWITCH_CLOSE)
	{
		lv_switch_off(my_lv_obj.win_sys3_motor2_ena_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys3_motor2_ena_switch_state_label, "ÂÅúÊ≠¢ ");
	}	
	if(my_lv_obj.win_sys3_motor2_dir_switch_flag == WIN_SYS3_SWITCH_OPEN)
	{
		lv_switch_on(my_lv_obj.win_sys3_motor2_dir_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys3_motor2_dir_switch_state_label, "Ê≠£ËΩ¨ ");
	}
	else if(my_lv_obj.win_sys3_motor2_dir_switch_flag == WIN_SYS3_SWITCH_CLOSE)
	{
		lv_switch_off(my_lv_obj.win_sys3_motor2_dir_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys3_motor2_dir_switch_state_label, "ÂèçËΩ¨ ");
	}	
}


