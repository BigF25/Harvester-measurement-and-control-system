#include "win_menu.h" 
#include "mylvgl.h"

void show_win_menu(void)
{
	lv_obj_t * label;
	/**************win界面***********************/
	my_lv_obj.win_menu = lv_win_create(my_lv_obj.scr, NULL);//创建MENU界面
	lv_style_set_text_font(&my_lv_obj.win_font1_style, LV_STATE_DEFAULT, &my_font1); 			//输入风格 设置字体
	gettime(my_lv_obj.win_flag,my_lv_obj.time);//显示时间和界面名称
	lv_win_set_title(my_lv_obj.win_menu, my_lv_obj.time);
	/**************按钮***********************/
	//头部按钮
	my_lv_obj.win_menu_set_btn = lv_win_add_btn(my_lv_obj.win_menu, LV_SYMBOL_SETTINGS);
	
	//按钮一
  my_lv_obj.win_menu_sys1_btn = lv_btn_create(my_lv_obj.win_menu , NULL);//创建按钮
	lv_style_set_radius(&my_lv_obj.win_menu_btn_style, LV_STATE_DEFAULT, 0);													//输入风格 圆角半径
	lv_style_set_text_font(&my_lv_obj.win_menu_btn_style, LV_STATE_DEFAULT, &my_font); 								//输入风格 字体
	lv_style_set_bg_color(&my_lv_obj.win_menu_btn_style, LV_STATE_DEFAULT, LV_COLOR_WHITE); 					//输入风格 背景颜色
	lv_obj_add_style(my_lv_obj.win_menu_sys1_btn, LV_BTN_PART_MAIN, &my_lv_obj.win_menu_btn_style);		//输入风格
  lv_obj_set_size(my_lv_obj.win_menu_sys1_btn, 200, 120);//设置按钮大小
  label = lv_label_create(my_lv_obj.win_menu_sys1_btn, NULL);
  lv_label_set_text(label, "5801\n鏁板瓧閲忚緭鍏? ");
	//按钮二
  my_lv_obj.win_menu_sys2_btn = lv_btn_create(my_lv_obj.win_menu, my_lv_obj.win_menu_sys1_btn);
  label = lv_label_create(my_lv_obj.win_menu_sys2_btn, NULL);
  lv_label_set_text(label, "7017\n妯℃嫙閲忚緭鍏? ");
	//按钮三
  my_lv_obj.win_menu_sys3_btn = lv_btn_create(my_lv_obj.win_menu, my_lv_obj.win_menu_sys1_btn);
  label = lv_label_create(my_lv_obj.win_menu_sys3_btn, NULL);
  lv_label_set_text(label, "4055\n鏁板瓧閲忚緭鍑? ");
	//按钮四
  my_lv_obj.win_menu_sys4_btn = lv_btn_create(my_lv_obj.win_menu, my_lv_obj.win_menu_sys1_btn);
  label = lv_label_create(my_lv_obj.win_menu_sys4_btn, NULL);
  lv_label_set_text(label, "3402\n妯℃嫙閲忚緭鍑? ");	
	//设置位置
	lv_obj_align(my_lv_obj.win_menu_sys1_btn, NULL, LV_ALIGN_CENTER, -150, -80);
  lv_obj_align(my_lv_obj.win_menu_sys2_btn, NULL, LV_ALIGN_CENTER, 150, -80);
  lv_obj_align(my_lv_obj.win_menu_sys3_btn, NULL, LV_ALIGN_CENTER, -150, 80);
  lv_obj_align(my_lv_obj.win_menu_sys4_btn, NULL, LV_ALIGN_CENTER, 150, 80);
	//设置回调函数
	lv_obj_set_event_cb(my_lv_obj.win_menu_set_btn, win_menu_set_btn_handler);
	lv_obj_set_event_cb(my_lv_obj.win_menu_sys1_btn, win_menu_sys1_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_menu_sys2_btn, win_menu_sys2_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_menu_sys3_btn, win_menu_sys3_btn_handler);
  lv_obj_set_event_cb(my_lv_obj.win_menu_sys4_btn, win_menu_sys4_btn_handler);	
}
//按钮回调函数
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


