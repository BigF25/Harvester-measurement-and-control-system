#include "win_set.h" 
#include "mylvgl.h"

void show_win_set(void)
{		
	lv_obj_t * label; 
	/**************win界面***********************/
	my_lv_obj.win_set = lv_win_create(my_lv_obj.scr, NULL);//创建MENU界面
	gettime(my_lv_obj.win_flag,my_lv_obj.time);//显示时间和界面名称
	lv_win_set_title(my_lv_obj.win_set, my_lv_obj.time);
	
	
	/**************按钮***********************/
	//头部按钮
	my_lv_obj.win_set_close_btn = lv_win_add_btn(my_lv_obj.win_set, LV_SYMBOL_CLOSE);
	lv_obj_set_event_cb(my_lv_obj.win_set_close_btn, win_set_close_btn_handler);//设置回调函数
       
	//按钮一
  my_lv_obj.win_set_settime_btn = lv_btn_create(my_lv_obj.win_set , NULL);//创建按钮
	lv_obj_add_style(my_lv_obj.win_set_settime_btn, LV_BTN_PART_MAIN, &my_lv_obj.win_menu_btn_style);		//输入风格
  lv_obj_set_size(my_lv_obj.win_set_settime_btn, 200, 120);//设置按钮大小
  label = lv_label_create(my_lv_obj.win_set_settime_btn, NULL);
  lv_label_set_text(label, "璁剧疆鏃堕棿 ");
	//按钮二
  my_lv_obj.win_set_sys2_btn = lv_btn_create(my_lv_obj.win_set, my_lv_obj.win_set_settime_btn);
  label = lv_label_create(my_lv_obj.win_set_sys2_btn, NULL);
   lv_label_set_text(label, "璁剧疆SD鍗? ");
	//按钮三
  my_lv_obj.win_set_sys3_btn = lv_btn_create(my_lv_obj.win_set, my_lv_obj.win_set_settime_btn);
  label = lv_label_create(my_lv_obj.win_set_sys3_btn, NULL);
  lv_label_set_text(label, "绯荤粺閲嶇疆 ");
	//按钮四
  my_lv_obj.win_set_sys4_btn = lv_btn_create(my_lv_obj.win_set, my_lv_obj.win_set_settime_btn);
  label = lv_label_create(my_lv_obj.win_set_sys4_btn, NULL);
  lv_label_set_text(label, "鐩稿叧淇℃伅 ");	

	//设置位置
	lv_obj_align(my_lv_obj.win_set_settime_btn, NULL, LV_ALIGN_CENTER, -150, -80);
  lv_obj_align(my_lv_obj.win_set_sys2_btn, NULL, LV_ALIGN_CENTER, 150, -80);
  lv_obj_align(my_lv_obj.win_set_sys3_btn, NULL, LV_ALIGN_CENTER, -150, 80);
  lv_obj_align(my_lv_obj.win_set_sys4_btn, NULL, LV_ALIGN_CENTER, 150, 80);
	//设置回调函数
	lv_obj_set_event_cb(my_lv_obj.win_set_settime_btn, win_set_settime_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_set_sys2_btn, win_set_sys2_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_set_sys3_btn, win_set_sys3_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_set_sys4_btn, win_set_sys4_btn_handler);
	
}
void win_set_close_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_MENU;
		lv_obj_del(my_lv_obj.win_set);
	}
}
void win_set_settime_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_SETTIME;
		show_win_settime();
	}
}
void win_set_sys2_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_SDCard;
		show_win_setSDCard();
	}
}void win_set_sys3_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
	}
}
void win_set_sys4_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
	}
}


