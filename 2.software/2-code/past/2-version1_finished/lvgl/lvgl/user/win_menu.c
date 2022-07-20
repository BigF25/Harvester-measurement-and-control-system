#include "win_menu.h" 
#include "mylvgl.h"

void show_win_menu(void)
{
	lv_obj_t * label;
	/**************winΩÁ√Ê***********************/
	my_lv_obj.win_menu = lv_win_create(my_lv_obj.scr, NULL);//¥¥Ω®MENUΩÁ√Ê
	lv_style_set_text_font(&my_lv_obj.win_font1_style, LV_STATE_DEFAULT, &my_font1); 			// ‰»Î∑Á∏Ò …Ë÷√◊÷ÃÂ
	gettime(my_lv_obj.win_flag,my_lv_obj.time);//œ‘ æ ±º‰∫ÕΩÁ√Ê√˚≥∆
	lv_win_set_title(my_lv_obj.win_menu, my_lv_obj.time);
	/**************∞¥≈•***********************/
	//Õ∑≤ø∞¥≈•
	my_lv_obj.win_menu_set_btn = lv_win_add_btn(my_lv_obj.win_menu, LV_SYMBOL_SETTINGS);
	
	//∞¥≈•“ª
  my_lv_obj.win_menu_sys1_btn = lv_btn_create(my_lv_obj.win_menu , NULL);//¥¥Ω®∞¥≈•
	lv_style_set_radius(&my_lv_obj.win_menu_btn_style, LV_STATE_DEFAULT, 0);													// ‰»Î∑Á∏Ò ‘≤Ω«∞Îæ∂
	lv_style_set_text_font(&my_lv_obj.win_menu_btn_style, LV_STATE_DEFAULT, &my_font); 								// ‰»Î∑Á∏Ò ◊÷ÃÂ
	lv_style_set_bg_color(&my_lv_obj.win_menu_btn_style, LV_STATE_DEFAULT, LV_COLOR_WHITE); 					// ‰»Î∑Á∏Ò ±≥æ∞—’…´
	lv_obj_add_style(my_lv_obj.win_menu_sys1_btn, LV_BTN_PART_MAIN, &my_lv_obj.win_menu_btn_style);		// ‰»Î∑Á∏Ò
  lv_obj_set_size(my_lv_obj.win_menu_sys1_btn, 200, 120);//…Ë÷√∞¥≈•¥Û–°
  label = lv_label_create(my_lv_obj.win_menu_sys1_btn, NULL);
  lv_label_set_text(label, "5801\nÊï∞Â≠óÈáèËæìÂÖ• ");
	//∞¥≈•∂˛
  my_lv_obj.win_menu_sys2_btn = lv_btn_create(my_lv_obj.win_menu, my_lv_obj.win_menu_sys1_btn);
  label = lv_label_create(my_lv_obj.win_menu_sys2_btn, NULL);
  lv_label_set_text(label, "7017\nÊ®°ÊãüÈáèËæìÂÖ• ");
	//∞¥≈•»˝
  my_lv_obj.win_menu_sys3_btn = lv_btn_create(my_lv_obj.win_menu, my_lv_obj.win_menu_sys1_btn);
  label = lv_label_create(my_lv_obj.win_menu_sys3_btn, NULL);
  lv_label_set_text(label, "4055\nÊï∞Â≠óÈáèËæìÂá∫ ");
	//∞¥≈•Àƒ
  my_lv_obj.win_menu_sys4_btn = lv_btn_create(my_lv_obj.win_menu, my_lv_obj.win_menu_sys1_btn);
  label = lv_label_create(my_lv_obj.win_menu_sys4_btn, NULL);
  lv_label_set_text(label, "3402\nÊ®°ÊãüÈáèËæìÂá∫ ");	
	//…Ë÷√Œª÷√
	lv_obj_align(my_lv_obj.win_menu_sys1_btn, NULL, LV_ALIGN_CENTER, -150, -80);
  lv_obj_align(my_lv_obj.win_menu_sys2_btn, NULL, LV_ALIGN_CENTER, 150, -80);
  lv_obj_align(my_lv_obj.win_menu_sys3_btn, NULL, LV_ALIGN_CENTER, -150, 80);
  lv_obj_align(my_lv_obj.win_menu_sys4_btn, NULL, LV_ALIGN_CENTER, 150, 80);
	//…Ë÷√ªÿµ˜∫Ø ˝
	lv_obj_set_event_cb(my_lv_obj.win_menu_set_btn, win_menu_set_btn_handler);
	lv_obj_set_event_cb(my_lv_obj.win_menu_sys1_btn, win_menu_sys1_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_menu_sys2_btn, win_menu_sys2_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_menu_sys3_btn, win_menu_sys3_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_menu_sys4_btn, win_menu_sys4_btn_handler);	
}
//∞¥≈•ªÿµ˜∫Ø ˝
void win_menu_set_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_SET;
		show_win_set();
	}
}
void win_menu_sys1_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_SYS1;
		show_win_sys1();
	}
}
void win_menu_sys2_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		show_win_sys2();
		my_lv_obj.win_flag = WIN_SYS2;
	}
}
void win_menu_sys3_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		show_win_sys3();
		my_lv_obj.win_flag = WIN_SYS3;
	}
}
void win_menu_sys4_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		show_win_sys4();
		my_lv_obj.win_flag = WIN_SYS4;
	}
}


