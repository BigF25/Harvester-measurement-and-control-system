#include "win_setSDCard.h" 
#include "mylvgl.h"

void show_win_setSDCard(void)
{
	my_lv_obj.win_setSDCard = lv_win_create(my_lv_obj.scr, NULL);//创建MENU界面
	gettime(my_lv_obj.win_flag,my_lv_obj.time);
	lv_win_set_title(my_lv_obj.win_setSDCard, my_lv_obj.time);
	
	/**************标签***********************/
	my_lv_obj.win_setSDCard_label = lv_label_create(my_lv_obj.win_setSDCard, NULL);
	lv_obj_add_style(my_lv_obj.win_setSDCard_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//杈撳叆椋庢牸
	lv_label_set_text(my_lv_obj.win_setSDCard_label, "");
	/**************按钮***********************/
	my_lv_obj.win_setSDCard_close_btn = lv_win_add_btn(my_lv_obj.win_setSDCard, LV_SYMBOL_CLOSE);
	my_lv_obj.win_setSDCard_refresh_btn = lv_win_add_btn(my_lv_obj.win_setSDCard, LV_SYMBOL_REFRESH);
//	my_lv_obj.win_sys1_back_btn = lv_win_add_btn(my_lv_obj.win_sys1, LV_SYMBOL_LEFT);
	
  lv_obj_set_event_cb(my_lv_obj.win_setSDCard_close_btn, win_setSDCard_close_btn_handler);/*设置btn1回调函数*/
  lv_obj_set_event_cb(my_lv_obj.win_setSDCard_refresh_btn, win_setSDCard_refresh_btn_handler);/*设置btn1回调函数*/
	
	
}
void win_setSDCard_close_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		my_lv_obj.win_flag = WIN_MENU;
		lv_obj_del(my_lv_obj.win_setSDCard);
	}
}
void win_setSDCard_refresh_btn_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) 
	{
		BEEP_sound(1);
		u32 total,free;
		char totalchar[50];
		char freechar[50];
		char temp[100];
		if(SD_GetState() == SD_CARD_ERROR)
		{
			if(SD_Init())
			{
				//SD Card Error!
				lv_label_set_text(my_lv_obj.win_setSDCard_label, "SD鍗￠敊璇? 璇锋鏌ワ紒 ");
				my_lv_obj.SDCard_flag = SD_ERROR;//SD Card Fatfs Error!
			}
				
			else
			{
				exfuns_init();							//为fatfs相关变量申请内存		
				f_mount(fs[0],"0:",1); 					//挂载SD卡 
				if(exf_getfree("0",&total,&free))
					//SD Card Fatfs Error!
					lv_label_set_text(my_lv_obj.win_setSDCard_label, "SD鍗℃枃浠剁郴缁熼敊璇? 璇锋鏌ワ紒 ");
				else
					goto A;//SD Card Ready!
			}
		}
		else
		{
			exf_getfree("0",&total,&free);
			A:
			total = total>>10;
			free = free>>10;
			sprintf(totalchar, "SD鍗℃甯? \n鎬诲ぇ灏忥細 %.2f GB\n",(double)total/1024.0);
			sprintf(freechar, "鍓╀綑鍙敤澶у皬锛?%.2f GB",(double)free/1024.0);			
			strcpy(temp,totalchar);
			strcat(temp,freechar);
			lv_label_set_text(my_lv_obj.win_setSDCard_label, temp);
			my_lv_obj.SDCard_flag = SD_READY;//SD Card Ready!
		}
	}
}



