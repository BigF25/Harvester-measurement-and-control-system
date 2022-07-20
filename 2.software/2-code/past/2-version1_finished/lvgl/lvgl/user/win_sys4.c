#include "win_sys4.h" 
#include "mylvgl.h"
#include "beep.h"
#include "rtc.h"

void show_win_sys4(void)
{
	/**************winΩÁ√Ê***********************/
	my_lv_obj.win_sys4 = lv_win_create(my_lv_obj.scr, NULL);
	gettime(my_lv_obj.win_flag,my_lv_obj.time);
	lv_win_set_title(my_lv_obj.win_sys4, my_lv_obj.time);
	/*****************∞¥≈•********************/
	my_lv_obj.win_sys4_close_btn = lv_win_add_btn(my_lv_obj.win_sys4, LV_SYMBOL_CLOSE);
	my_lv_obj.win_sys4_msg_btn = lv_win_add_btn(my_lv_obj.win_sys4, LV_SYMBOL_WARNING);
  lv_obj_set_event_cb(my_lv_obj.win_sys4_close_btn, win_sys4_close_btn_handler);					//…Ë÷√ªÿµ˜∫Ø ˝
  lv_obj_set_event_cb(my_lv_obj.win_sys4_msg_btn, win_sys4_msg_btn_handler);							//…Ë÷√ªÿµ˜∫Ø ˝
	/**************slider*****************/
	my_lv_obj.win_sys4_slider_1  =lv_slider_create(my_lv_obj.win_sys4, NULL);
	my_lv_obj.win_sys4_slider_2  =lv_slider_create(my_lv_obj.win_sys4, NULL);
	lv_obj_set_width(my_lv_obj.win_sys4_slider_1, 400);
	lv_obj_set_width(my_lv_obj.win_sys4_slider_2, 400);
	lv_obj_align(my_lv_obj.win_sys4_slider_1, my_lv_obj.win_sys4, LV_ALIGN_CENTER, 0, -80);
	lv_obj_align(my_lv_obj.win_sys4_slider_2, my_lv_obj.win_sys4, LV_ALIGN_CENTER, 0, 100);
	lv_slider_set_anim_time(my_lv_obj.win_sys4_slider_1, 0);//πÿ±’∂Øª≠
	lv_slider_set_anim_time(my_lv_obj.win_sys4_slider_2, 0);//πÿ±’∂Øª≠
	lv_slider_set_range(my_lv_obj.win_sys4_slider_1, 0, 4095);
	lv_slider_set_range(my_lv_obj.win_sys4_slider_2, 0, 4095);
	lv_obj_set_event_cb(my_lv_obj.win_sys4_slider_1, win_sys4_slider_1_handler);		//…Ë÷√ªÿµ˜∫Ø ˝
	lv_obj_set_event_cb(my_lv_obj.win_sys4_slider_2, win_sys4_slider_2_handler);		//…Ë÷√ªÿµ˜∫Ø ˝
	/**************sliderµƒ±Í«©*****************/
	lv_obj_t * win_sys4_slider_temp_label1;
	lv_obj_t * win_sys4_slider_temp_label2;
	win_sys4_slider_temp_label1 = lv_label_create(my_lv_obj.win_sys4, NULL);
	win_sys4_slider_temp_label2 = lv_label_create(my_lv_obj.win_sys4, NULL);
	lv_obj_add_style(win_sys4_slider_temp_label1, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(win_sys4_slider_temp_label2, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
  lv_label_set_text(win_sys4_slider_temp_label1, "Ââ≤Âè∞È´òÂ∫¶ÁîµÂ≠êÈòÄÂºÄÂ∫¶ ");
  lv_label_set_text(win_sys4_slider_temp_label2, "Êã®Á¶æËΩÆËΩ¨ÈÄüÊ∂≤ÂéãÈòÄÂºÄÂ∫¶ ");
	lv_obj_align(win_sys4_slider_temp_label1, my_lv_obj.win_sys4_slider_1, LV_ALIGN_CENTER, 0, -40);
	lv_obj_align(win_sys4_slider_temp_label2, my_lv_obj.win_sys4_slider_2, LV_ALIGN_CENTER, 0, -40);
	my_lv_obj.win_sys4_slider_1_label = lv_label_create(my_lv_obj.win_sys4, NULL);
	my_lv_obj.win_sys4_slider_2_label = lv_label_create(my_lv_obj.win_sys4, NULL);
	lv_obj_add_style(my_lv_obj.win_sys4_slider_1_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_add_style(my_lv_obj.win_sys4_slider_2_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		// ‰»Î∑Á∏Ò
	lv_obj_align(my_lv_obj.win_sys4_slider_1_label, my_lv_obj.win_sys4_slider_1, LV_ALIGN_CENTER, 0, 40);
	lv_obj_align(my_lv_obj.win_sys4_slider_2_label, my_lv_obj.win_sys4_slider_2, LV_ALIGN_CENTER, 0, 40);
	win_sys4_state_show();
	my_lv_obj.win_sys4_finish_loading_flag = WIN_SYS4_FINISHED;
}
void win_sys4_close_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_MENU;
		my_lv_obj.win_sys4_finish_loading_flag = WIN_SYS3_LOADING;
		lv_obj_del(my_lv_obj.win_sys4);
	}
}
void win_sys4_msg_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys4_msgbox_msg=lv_msgbox_create(my_lv_obj.win_sys4, NULL);
		static const char * btns[] ={"CLOSE", "OPEN", ""};
		lv_msgbox_add_btns(my_lv_obj.win_sys4_msgbox_msg, btns);
		lv_msgbox_set_anim_time(my_lv_obj.win_sys4_msgbox_msg, 0);//πÿ±’∂Øª≠
	}
}
void win_sys4_slider_1_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_VALUE_CHANGED) 
	{
		my_lv_obj.win_sys4_slider_1_value = lv_slider_get_value(my_lv_obj.win_sys4_slider_1);
		Set_3402_Analogoutput(ADDRESS_3402, my_lv_obj.win_sys4_slider_1_value, my_lv_obj.win_sys4_slider_2_value);
		char temp[20];
		sprintf(temp, "Â§ßÂ∞è: %d", my_lv_obj.win_sys4_slider_1_value);
		lv_label_set_text(my_lv_obj.win_sys4_slider_1_label, temp);
	}
}
void win_sys4_slider_2_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_VALUE_CHANGED) 
	{
		my_lv_obj.win_sys4_slider_2_value = lv_slider_get_value(my_lv_obj.win_sys4_slider_2);
		Set_3402_Analogoutput(ADDRESS_3402, my_lv_obj.win_sys4_slider_1_value, my_lv_obj.win_sys4_slider_2_value);
		char temp[20];
		sprintf(temp, "Â§ßÂ∞è: %d", my_lv_obj.win_sys4_slider_2_value);
		lv_label_set_text(my_lv_obj.win_sys4_slider_2_label, temp);
	}
}
void win_sys4_state_show(void)
{
	char temp[20];
	sprintf(temp, "Â§ßÂ∞è: %d", my_lv_obj.win_sys4_slider_1_value);
	lv_label_set_text(my_lv_obj.win_sys4_slider_1_label, temp);
	sprintf(temp, "Â§ßÂ∞è: %d", my_lv_obj.win_sys4_slider_2_value);
	lv_label_set_text(my_lv_obj.win_sys4_slider_2_label, temp);
	lv_slider_set_value(my_lv_obj.win_sys4_slider_1, my_lv_obj.win_sys4_slider_1_value, LV_ANIM_OFF);
	lv_slider_set_value(my_lv_obj.win_sys4_slider_2, my_lv_obj.win_sys4_slider_2_value, LV_ANIM_OFF);
}
