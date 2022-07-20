#include "win_sys1.h" 
#include "mylvgl.h"
#include "beep.h"
#include "rtc.h"

void show_win_sys1(void)
{
	/**************win����***********************/
	my_lv_obj.win_sys1 = lv_win_create(my_lv_obj.scr, NULL);
	
	gettime(my_lv_obj.win_flag,my_lv_obj.time);
	lv_win_set_title(my_lv_obj.win_sys1, my_lv_obj.time);
	/*****************��ť********************/
	my_lv_obj.win_sys1_close_btn = lv_win_add_btn(my_lv_obj.win_sys1, LV_SYMBOL_CLOSE);
	my_lv_obj.win_sys1_table_up_btn = lv_win_add_btn(my_lv_obj.win_sys1, LV_SYMBOL_UP);
	my_lv_obj.win_sys1_table_down_btn = lv_win_add_btn(my_lv_obj.win_sys1, LV_SYMBOL_DOWN);
	my_lv_obj.win_sys1_msg_btn = lv_win_add_btn(my_lv_obj.win_sys1, LV_SYMBOL_WARNING);
  lv_obj_set_event_cb(my_lv_obj.win_sys1_close_btn, win_sys1_close_btn_handler);					//���ûص�����
  lv_obj_set_event_cb(my_lv_obj.win_sys1_table_up_btn, win_sys1_table_up_btn_handler);		//���ûص�����
  lv_obj_set_event_cb(my_lv_obj.win_sys1_table_down_btn, win_sys1_table_down_btn_handler);//���ûص�����
  lv_obj_set_event_cb(my_lv_obj.win_sys1_msg_btn, win_sys1_msg_btn_handler);							//���ûص�����
	/******************���*******************/
	my_lv_obj.win_sys1_table = lv_table_create(my_lv_obj.win_sys1, NULL); 
	lv_obj_set_click(my_lv_obj.win_sys1_table, false);																					//���ɵ��
	lv_obj_add_style(my_lv_obj.win_sys1_table, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//������
	lv_table_set_col_cnt(my_lv_obj.win_sys1_table, 4);
	lv_table_set_row_cnt(my_lv_obj.win_sys1_table, 5);
	lv_table_set_col_width(my_lv_obj.win_sys1_table, 0, 80);
	lv_table_set_col_width(my_lv_obj.win_sys1_table, 1, 200);
	lv_table_set_col_width(my_lv_obj.win_sys1_table, 2, 140);
	lv_table_set_col_width(my_lv_obj.win_sys1_table, 3, 120);
	lv_obj_align(my_lv_obj.win_sys1_table, my_lv_obj.win_sys1, LV_ALIGN_CENTER, -40, 25);
	win_sys1_table_show(my_lv_obj.win_sys1_table_count,SHOW);//��ʾ�������
	lv_obj_set_event_cb(my_lv_obj.win_sys1_table, win_sys1_table_handler);//���ûص�����
	/**************��������***********************/
	my_lv_obj.win_sys1_can_rec_switch = lv_switch_create(my_lv_obj.win_sys1, NULL);
	my_lv_obj.win_sys1_sd_rec_switch = lv_switch_create(my_lv_obj.win_sys1, NULL);
	lv_obj_align(my_lv_obj.win_sys1_can_rec_switch, my_lv_obj.win_sys1, LV_ALIGN_IN_TOP_LEFT, 700, 125);
	lv_obj_align(my_lv_obj.win_sys1_sd_rec_switch, my_lv_obj.win_sys1, LV_ALIGN_IN_TOP_LEFT, 700, 250);
	lv_switch_set_anim_time(my_lv_obj.win_sys1_can_rec_switch, 0);//�رն���
	lv_switch_set_anim_time(my_lv_obj.win_sys1_sd_rec_switch, 0);//�رն���
	lv_obj_set_event_cb(my_lv_obj.win_sys1_can_rec_switch, win_sys1_can_rec_switch_handler);	//���ûص�����
	lv_obj_set_event_cb(my_lv_obj.win_sys1_sd_rec_switch, win_sys1_sd_rec_switch_handler);		//���ûص�����
	/**************�������صı�ǩ*****************/
	lv_obj_t * win_sys1_switch_temp_label1;
	lv_obj_t * win_sys1_switch_temp_label2;
	win_sys1_switch_temp_label1 = lv_label_create(my_lv_obj.win_sys1, NULL);
	win_sys1_switch_temp_label2 = lv_label_create(my_lv_obj.win_sys1, NULL);
	lv_obj_add_style(win_sys1_switch_temp_label1, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//������
	lv_obj_add_style(win_sys1_switch_temp_label2, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//������	
  lv_label_set_text(win_sys1_switch_temp_label1, "CAN接收 ");
  lv_label_set_text(win_sys1_switch_temp_label2, "SD卡记录 ");
	lv_obj_align(win_sys1_switch_temp_label1, my_lv_obj.win_sys1_can_rec_switch, LV_ALIGN_CENTER, 0, -25);
	lv_obj_align(win_sys1_switch_temp_label2, my_lv_obj.win_sys1_sd_rec_switch, LV_ALIGN_CENTER, 0, -25);
	my_lv_obj.win_sys1_can_rec_switch_state_label = lv_label_create(my_lv_obj.win_sys1, NULL);
	my_lv_obj.win_sys1_sd_rec_switch_state_label = lv_label_create(my_lv_obj.win_sys1, NULL);
	lv_obj_add_style(my_lv_obj.win_sys1_can_rec_switch_state_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//������
	lv_obj_add_style(my_lv_obj.win_sys1_sd_rec_switch_state_label,  LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//������
	lv_obj_align(my_lv_obj.win_sys1_can_rec_switch_state_label, my_lv_obj.win_sys1_can_rec_switch, LV_ALIGN_CENTER, 0, 25);
	lv_obj_align(my_lv_obj.win_sys1_sd_rec_switch_state_label, my_lv_obj.win_sys1_sd_rec_switch, LV_ALIGN_CENTER, 0, 25);
	win_sys1_switch_state_show();//ˢ��switch״̬�ͱ�ǩ״̬
	if(my_lv_obj.SDCard_flag == SD_ERROR)
		 lv_obj_set_click(my_lv_obj.win_sys1_sd_rec_switch, false);
	else
		 lv_obj_set_click(my_lv_obj.win_sys1_sd_rec_switch, true);
	my_lv_obj.win_sys1_finish_loading_flag = WIN_SYS1_FINISHED;
}
void win_sys1_close_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_MENU;
		my_lv_obj.win_sys1_finish_loading_flag = WIN_SYS1_LOADING;
		lv_obj_del(my_lv_obj.win_sys1);
	}
}
void win_sys1_table_up_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys1_table_count--;
		if(my_lv_obj.win_sys1_table_count < 0 )
		{
			my_lv_obj.win_sys1_table_count = WIN_SYS1_TABLE_PAGE;
		}
		win_sys1_table_show(my_lv_obj.win_sys1_table_count,SHOW);
	}
}
void win_sys1_table_down_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys1_table_count++;
		if( my_lv_obj.win_sys1_table_count > WIN_SYS1_TABLE_PAGE)
		{
			my_lv_obj.win_sys1_table_count = 0;
		}
		win_sys1_table_show(my_lv_obj.win_sys1_table_count,SHOW);	
	}
}
void win_sys1_msg_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys1_msgbox_msg=lv_msgbox_create(my_lv_obj.win_sys1, NULL);
		static const char * btns[] ={"CLOSE", "OPEN", ""};
		lv_msgbox_add_btns(my_lv_obj.win_sys1_msgbox_msg, btns);
		lv_msgbox_set_anim_time(my_lv_obj.win_sys1_msgbox_msg, 0);//�رն���
	}
}
void win_sys1_can_rec_switch_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys1_can_rec_switch_flag = lv_switch_get_state(my_lv_obj.win_sys1_can_rec_switch);
		if( my_lv_obj.win_sys1_can_rec_switch_flag == WIN_SYS1_SWITCH_CLOSE) 
			my_lv_obj.win_sys1_sd_rec_switch_flag = WIN_SYS1_SWITCH_CLOSE;
		win_sys1_switch_state_show();
	}
}
void win_sys1_sd_rec_switch_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_sys1_sd_rec_switch_flag = lv_switch_get_state(my_lv_obj.win_sys1_sd_rec_switch);
		if(my_lv_obj.win_sys1_sd_rec_switch_flag == WIN_SYS1_SWITCH_OPEN) 
			my_lv_obj.win_sys1_can_rec_switch_flag = WIN_SYS1_SWITCH_OPEN;
		if(my_lv_obj.SDCard_flag == SD_ERROR)
		{
			my_lv_obj.win_sys1_sd_rec_switch_flag = WIN_SYS1_SWITCH_CLOSE;
		}
		win_sys1_switch_state_show();
	}
}
void win_sys1_table_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_REFRESH) 
	{
		win_sys1_table_show(my_lv_obj.win_sys1_table_count,dSHOW);
	}
}
void win_sys1_table_handler_event_send(void)
{
	lv_event_send(my_lv_obj.win_sys1_table,LV_EVENT_REFRESH,NULL);
}
void win_sys1_table_show(u8 num,u8 flag)
{
	if(flag)
	{
		switch(num)
		{
			case 0:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 0, "序号");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 1-num*4, 0, "1");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 2-num*4, 0, "2");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 3-num*4, 0, "3");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 4-num*4, 0, "4");
				break;
			case 1:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 0, "序号");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 5-num*4, 0, "5");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 6-num*4, 0, "6");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 7-num*4, 0, "7");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 8-num*4, 0, "8");
				break;
			case 2:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 0, "序号");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 9-num*4, 0, "9");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 10-num*4, 0, "10");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 11-num*4, 0, "11");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 12-num*4, 0, "12");
				break;
		}
		switch(num)
		{
			case 0:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 1, "监测物理量 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 1-num*4, 1, "前进速度 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 2-num*4, 1, "拨禾轮转速 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 3-num*4, 1, "输送槽转速 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 4-num*4, 1, "割台搅龙转速 ");
				break;
			case 1:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 1, "监测物理量 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 5-num*4, 1, "滚筒转速 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 6-num*4, 1, "风机转速 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 7-num*4, 1, "冗余绞龙转速 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 8-num*4, 1, "籽粒绞龙转速 ");
				break;
			case 2:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 1, "监测物理量 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 9-num*4, 1, "碎草装置转速 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 10-num*4, 1, "发动机转速 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 11-num*4, 1, "籽粒夹带损失 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 12-num*4, 1, "籽粒清选损失 ");
				break;
		}
		switch(num)
		{
			case 0:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 3, "单位 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 1-num*4, 3, "米/秒 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 2-num*4, 3, "转/分钟 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 3-num*4, 3, "转/分钟 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 4-num*4, 3, "转/分钟 ");
				break;
			case 1:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 3, "单位 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 5-num*4, 3, "转/分钟 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 6-num*4, 3, "转/分钟 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 7-num*4, 3, "转/分钟 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 8-num*4, 3, "转/分钟 ");
				break;
			case 2:
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 3, "单位 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 9-num*4, 3, "转/分钟 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 10-num*4, 3, "转/分钟 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 11-num*4, 3, "粒 ");
				lv_table_set_cell_value(my_lv_obj.win_sys1_table, 12-num*4, 3, "粒 ");
				break;
		}
	}
	switch(num)
	{
		case 0:
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 2, "结果 ");    		
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 1-num*4, 2, my_lv_obj.win_sys1_5801_result_char_1[0]);    		
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 2-num*4, 2, my_lv_obj.win_sys1_5801_result_char_1[1]);
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 3-num*4, 2, my_lv_obj.win_sys1_5801_result_char_1[2]);
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 4-num*4, 2, my_lv_obj.win_sys1_5801_result_char_1[3]);
			break;
		case 1:
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 2, "结果 ");    		
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 5-num*4, 2, my_lv_obj.win_sys1_5801_result_char_1[4]);
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 6-num*4, 2, my_lv_obj.win_sys1_5801_result_char_1[5]);
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 7-num*4, 2, my_lv_obj.win_sys1_5801_result_char_1[6]);
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 8-num*4, 2, my_lv_obj.win_sys1_5801_result_char_1[7]);
			break;
		case 2:
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 0, 2, "结果 ");    		
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 9 -num*4, 2, my_lv_obj.win_sys1_5801_result_char_2[0]);
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 10-num*4, 2, my_lv_obj.win_sys1_5801_result_char_2[1]);
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 11-num*4, 2, my_lv_obj.win_sys1_5801_result_char_2[6]);
			lv_table_set_cell_value(my_lv_obj.win_sys1_table, 12-num*4, 2, my_lv_obj.win_sys1_5801_result_char_2[7]);
			break;
	}
}
void win_sys1_switch_state_show(void)
{
	if(my_lv_obj.win_sys1_can_rec_switch_flag)
	{
		lv_switch_on(my_lv_obj.win_sys1_can_rec_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys1_can_rec_switch_state_label, "打开 ");
	}
	else 
	{
		lv_switch_off(my_lv_obj.win_sys1_can_rec_switch,LV_ANIM_OFF);	
		lv_label_set_text(my_lv_obj.win_sys1_can_rec_switch_state_label, "关闭 ");
	}
	if(my_lv_obj.win_sys1_sd_rec_switch_flag == WIN_SYS1_SWITCH_OPEN)
	{
		lv_switch_on(my_lv_obj.win_sys1_sd_rec_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys1_sd_rec_switch_state_label, "打开 ");
	}
	else if(my_lv_obj.win_sys1_sd_rec_switch_flag == WIN_SYS1_SWITCH_CLOSE)
	{
		lv_switch_off(my_lv_obj.win_sys1_sd_rec_switch,LV_ANIM_OFF);
		lv_label_set_text(my_lv_obj.win_sys1_sd_rec_switch_state_label, "关闭 ");
	}	
}

