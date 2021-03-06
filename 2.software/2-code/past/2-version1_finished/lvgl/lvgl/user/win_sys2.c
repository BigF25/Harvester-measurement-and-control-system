#include "win_sys2.h" 
#include "mylvgl.h"
#include "beep.h"
#include "rtc.h"

void show_win_sys2(void)
{
	/**************win界面***********************/
	my_lv_obj.win_sys2 = lv_win_create(my_lv_obj.scr, NULL);
	gettime(my_lv_obj.win_flag,my_lv_obj.time);
	lv_win_set_title(my_lv_obj.win_sys2, my_lv_obj.time);
	/*****************按钮********************/
	my_lv_obj.win_sys2_close_btn = lv_win_add_btn(my_lv_obj.win_sys2, LV_SYMBOL_CLOSE);
	my_lv_obj.win_sys2_table_up_btn = lv_win_add_btn(my_lv_obj.win_sys2, LV_SYMBOL_UP);
	my_lv_obj.win_sys2_table_down_btn = lv_win_add_btn(my_lv_obj.win_sys2, LV_SYMBOL_DOWN);
	my_lv_obj.win_sys2_msg_btn = lv_win_add_btn(my_lv_obj.win_sys2, LV_SYMBOL_WARNING);
  lv_obj_set_event_cb(my_lv_obj.win_sys2_close_btn, win_sys2_close_btn_handler);					//设置回调函数
  lv_obj_set_event_cb(my_lv_obj.win_sys2_table_up_btn, win_sys2_table_up_btn_handler);		//设置回调函数
  lv_obj_set_event_cb(my_lv_obj.win_sys2_table_down_btn, win_sys2_table_down_btn_handler);//设置回调函数
  lv_obj_set_event_cb(my_lv_obj.win_sys2_msg_btn, win_sys2_msg_btn_handler);							//设置回调函数
		/******************表格*******************/
	my_lv_obj.win_sys2_table = lv_table_create(my_lv_obj.win_sys2, NULL); 
	lv_obj_set_click(my_lv_obj.win_sys2_table, false);																					//不可点击
	lv_obj_add_style(my_lv_obj.win_sys2_table, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//输入风格
	lv_table_set_col_cnt(my_lv_obj.win_sys2_table, 4);
	lv_table_set_row_cnt(my_lv_obj.win_sys2_table, 5);
	lv_table_set_col_width(my_lv_obj.win_sys2_table, 0, 80);
	lv_table_set_col_width(my_lv_obj.win_sys2_table, 1, 200);
	lv_table_set_col_width(my_lv_obj.win_sys2_table, 2, 160);
	lv_table_set_col_width(my_lv_obj.win_sys2_table, 3, 100);
	lv_obj_align(my_lv_obj.win_sys2_table, my_lv_obj.win_sys2, LV_ALIGN_CENTER, -40, 25);
	win_sys2_table_show(my_lv_obj.win_sys2_table_count,SHOW);//显示表格内容
	lv_obj_set_event_cb(my_lv_obj.win_sys2_table, win_sys2_table_handler);//设置回调函数
	/**************滑动开关***********************/
	my_lv_obj.win_sys2_can_rec_switch = lv_switch_create(my_lv_obj.win_sys2, NULL);
	my_lv_obj.win_sys2_sd_rec_switch = lv_switch_create(my_lv_obj.win_sys2, NULL);
	lv_obj_align(my_lv_obj.win_sys2_can_rec_switch, my_lv_obj.win_sys1, LV_ALIGN_IN_TOP_LEFT, 700, 125);
	lv_obj_align(my_lv_obj.win_sys2_sd_rec_switch, my_lv_obj.win_sys1, LV_ALIGN_IN_TOP_LEFT, 700, 250);
	lv_switch_set_anim_time(my_lv_obj.win_sys2_can_rec_switch, 0);//关闭动画
	lv_switch_set_anim_time(my_lv_obj.win_sys2_sd_rec_switch, 0);//关闭动画
	lv_obj_set_event_cb(my_lv_obj.win_sys2_can_rec_switch, win_sys2_can_rec_switch_handler);	//设置回调函数
	lv_obj_set_event_cb(my_lv_obj.win_sys2_sd_rec_switch, win_sys2_sd_rec_switch_handler);		//设置回调函数
	/**************滑动开关的标签*****************/
	lv_obj_t * win_sys2_switch_temp_label1;
	lv_obj_t * win_sys2_switch_temp_label2;
	win_sys2_switch_temp_label1 = lv_label_create(my_lv_obj.win_sys2, NULL);
	win_sys2_switch_temp_label2 = lv_label_create(my_lv_obj.win_sys2, NULL);
	lv_obj_add_style(win_sys2_switch_temp_label1, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//杈撳叆椋庢牸
	lv_obj_add_style(win_sys2_switch_temp_label2, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//杈撳叆椋庢牸	
  lv_label_set_text(win_sys2_switch_temp_label1, "CAN鎺ユ敹 ");
  lv_label_set_text(win_sys2_switch_temp_label2, "SD鍗¤褰? ");
	lv_obj_align(win_sys2_switch_temp_label1, my_lv_obj.win_sys2_can_rec_switch, LV_ALIGN_CENTER, 0, -25);
	lv_obj_align(win_sys2_switch_temp_label2, my_lv_obj.win_sys2_sd_rec_switch, LV_ALIGN_CENTER, 0, -25);
	my_lv_obj.win_sys2_can_rec_switch_state_label = lv_label_create(my_lv_obj.win_sys2, NULL);
	my_lv_obj.win_sys2_sd_rec_switch_state_label = lv_label_create(my_lv_obj.win_sys2, NULL);
	lv_obj_add_style(my_lv_obj.win_sys2_can_rec_switch_state_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//杈撳叆椋庢牸
	lv_obj_add_style(my_lv_obj.win_sys2_sd_rec_switch_state_label,  LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//杈撳叆椋庢牸
	lv_obj_align(my_lv_obj.win_sys2_can_rec_switch_state_label, my_lv_obj.win_sys2_can_rec_switch, LV_ALIGN_CENTER, 0, 25);
	lv_obj_align(my_lv_obj.win_sys2_sd_rec_switch_state_label, my_lv_obj.win_sys2_sd_rec_switch, LV_ALIGN_CENTER, 0, 25);
	win_sys2_switch_state_show();//刷新switch状态和标签状态
	if(my_lv_obj.SDCard_flag == SD_ERROR)
		 lv_obj_set_click(my_lv_obj.win_sys2_sd_rec_switch, false);
	else
		 lv_obj_set_click(my_lv_obj.win_sys2_sd_rec_switch, true);
	my_lv_obj.win_sys2_finish_loading_flag = WIN_SYS2_FINISHED;
}
void win_sys2_close_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_MENU;
		my_lv_obj.win_sys2_finish_loading_flag = WIN_SYS2_LOADING;
		lv_obj_del(my_lv_obj.win_sys2);
	}
}
void win_sys2_table_up_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys2_table_count--;
		if(my_lv_obj.win_sys2_table_count < 0 )
		{
			my_lv_obj.win_sys2_table_count = WIN_SYS2_TABLE_PAGE;
		}
		win_sys2_table_show(my_lv_obj.win_sys2_table_count,SHOW);
	}
}
void win_sys2_table_down_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys2_table_count++;
		if( my_lv_obj.win_sys2_table_count > WIN_SYS2_TABLE_PAGE)
		{
			my_lv_obj.win_sys2_table_count = 0;
		}
		win_sys2_table_show(my_lv_obj.win_sys2_table_count,SHOW);	
	}
}
void win_sys2_msg_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys2_msgbox_msg=lv_msgbox_create(my_lv_obj.win_sys2, NULL);
		static const char * btns[] ={"CLOSE", "OPEN", ""};
		lv_msgbox_add_btns(my_lv_obj.win_sys2_msgbox_msg, btns);
		lv_msgbox_set_anim_time(my_lv_obj.win_sys2_msgbox_msg, 0);//关闭动画
	}
}
void win_sys2_can_rec_switch_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys2_can_rec_switch_flag = lv_switch_get_state(my_lv_obj.win_sys2_can_rec_switch);
		if( my_lv_obj.win_sys2_can_rec_switch_flag == WIN_SYS2_SWITCH_CLOSE) 
			my_lv_obj.win_sys2_sd_rec_switch_flag = WIN_SYS2_SWITCH_CLOSE;
		win_sys2_switch_state_show();
	}
}
void win_sys2_sd_rec_switch_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys2_sd_rec_switch_flag = lv_switch_get_state(my_lv_obj.win_sys2_sd_rec_switch);
		if(my_lv_obj.win_sys2_sd_rec_switch_flag == WIN_SYS2_SWITCH_OPEN) 
			my_lv_obj.win_sys2_can_rec_switch_flag = WIN_SYS2_SWITCH_OPEN;
		if(my_lv_obj.SDCard_flag == SD_ERROR)
		{
			my_lv_obj.win_sys2_sd_rec_switch_flag = WIN_SYS2_SWITCH_CLOSE;
		}
		win_sys2_switch_state_show();
	}
}
void win_sys2_table_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_REFRESH) 
	{
		win_sys2_table_show(my_lv_obj.win_sys2_table_count,dSHOW);
	}
}
void win_sys2_table_handler_event_send(void)
{
	lv_event_send(my_lv_obj.win_sys2_table,LV_EVENT_REFRESH,NULL);
}
void win_sys2_table_show(u8 num,u8 flag)
{
	if(flag)
	{
		switch(num)
		{
			case 0:
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 0, 0, "搴忓彿");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 1-num*4, 0, "1");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 2-num*4, 0, "2");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 3-num*4, 0, "3");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 4-num*4, 0, "4");
				break;
			case 1:
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 0, 0, "搴忓彿");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 5-num*4, 0, "5");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 6-num*4, 0, "");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 7-num*4, 0, "");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 8-num*4, 0, "");
				break;
		}
		switch(num)
		{
			case 0:
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 0, 1, "鐩戞祴鐗╃悊閲? ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 1-num*4, 1, "鎷ㄧ杞珮搴? ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 2-num*4, 1, "鍓插彴楂樺害 ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 3-num*4, 1, "楸奸碁绛涘紑搴? ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 4-num*4, 1, "浠垮舰鏉?1瑙掑害 ");
				break;
			case 1:
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 0, 1, "鐩戞祴鐗╃悊閲? ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 5-num*4, 1, "浠垮舰鏉?2瑙掑害 ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 6-num*4, 1, "");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 7-num*4, 1, "");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 8-num*4, 1, "");
				break;
		}
		switch(num)
		{
			case 0:
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 0, 3, "鍗曚綅 ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 1-num*4, 3, "鍘樼背 ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 2-num*4, 3, "鍘樼背 ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 3-num*4, 3, "鍘樼背 ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 4-num*4, 3, "搴? ");
				break;
			case 1:
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 0, 3, "鍗曚綅 ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 5-num*4, 3, "搴? ");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 6-num*4, 3, "");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 7-num*4, 3, "");
				lv_table_set_cell_value(my_lv_obj.win_sys2_table, 8-num*4, 3, "");
				break;
		}
	}
	switch(num)
	{
		case 0:
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 0, 2, "缁撴灉 ");	
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 1-num*4, 2, my_lv_obj.win_sys2_7017_result_char[0]);    		
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 2-num*4, 2, my_lv_obj.win_sys2_7017_result_char[1]);
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 3-num*4, 2, my_lv_obj.win_sys2_7017_result_char[2]);
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 4-num*4, 2, my_lv_obj.win_sys2_7017_result_char[3]);
			break;
		case 1:
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 0, 2, "缁撴灉 ");    		
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 5-num*4, 2, my_lv_obj.win_sys2_7017_result_char[4]);
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 6-num*4, 2, "");
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 7-num*4, 2, "");
			lv_table_set_cell_value(my_lv_obj.win_sys2_table, 8-num*4, 2, "");
			break;
	}
}
void win_sys2_switch_state_show(void)
{
	if(my_lv_obj.win_sys2_can_rec_switch_flag == WIN_SYS2_SWITCH_OPEN)
	{
		lv_switch_on(my_lv_obj.win_sys2_can_rec_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys2_can_rec_switch_state_label, "鎵撳紑 ");
	}
	else if(my_lv_obj.win_sys2_can_rec_switch_flag == WIN_SYS2_SWITCH_CLOSE)
	{
		lv_switch_off(my_lv_obj.win_sys2_can_rec_switch,LV_ANIM_OFF);	
		lv_label_set_text(my_lv_obj.win_sys2_can_rec_switch_state_label, "鍏抽棴 ");
	}
	if(my_lv_obj.win_sys2_sd_rec_switch_flag == WIN_SYS2_SWITCH_OPEN)
	{
		lv_switch_on(my_lv_obj.win_sys2_sd_rec_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys2_sd_rec_switch_state_label, "鎵撳紑 ");
	}
	else if(my_lv_obj.win_sys2_sd_rec_switch_flag == WIN_SYS2_SWITCH_CLOSE)
	{
		lv_switch_off(my_lv_obj.win_sys2_sd_rec_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys2_sd_rec_switch_state_label, "鍏抽棴 ");
	}	
}

