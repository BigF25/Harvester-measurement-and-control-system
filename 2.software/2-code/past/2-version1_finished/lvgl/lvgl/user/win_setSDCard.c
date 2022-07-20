#include "win_setSDCard.h" 
#include "mylvgl.h"

void show_win_setSDCard(void)
{
	my_lv_obj.win_setSDCard = lv_win_create(my_lv_obj.scr, NULL);//����MENU����
	gettime(my_lv_obj.win_flag,my_lv_obj.time);
	lv_win_set_title(my_lv_obj.win_setSDCard, my_lv_obj.time);
	
	/**************��ǩ***********************/
	my_lv_obj.win_setSDCard_label = lv_label_create(my_lv_obj.win_setSDCard, NULL);
	lv_obj_add_style(my_lv_obj.win_setSDCard_label, LV_BTN_PART_MAIN, &my_lv_obj.win_font1_style);		//输入风格
	lv_label_set_text(my_lv_obj.win_setSDCard_label, "");
	/**************��ť***********************/
	my_lv_obj.win_setSDCard_close_btn = lv_win_add_btn(my_lv_obj.win_setSDCard, LV_SYMBOL_CLOSE);
	my_lv_obj.win_setSDCard_refresh_btn = lv_win_add_btn(my_lv_obj.win_setSDCard, LV_SYMBOL_REFRESH);
//	my_lv_obj.win_sys1_back_btn = lv_win_add_btn(my_lv_obj.win_sys1, LV_SYMBOL_LEFT);
	
  lv_obj_set_event_cb(my_lv_obj.win_setSDCard_close_btn, win_setSDCard_close_btn_handler);/*����btn1�ص�����*/
  lv_obj_set_event_cb(my_lv_obj.win_setSDCard_refresh_btn, win_setSDCard_refresh_btn_handler);/*����btn1�ص�����*/
	
	
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
				lv_label_set_text(my_lv_obj.win_setSDCard_label, "SD卡错误 请检查！ ");
				my_lv_obj.SDCard_flag = SD_ERROR;//SD Card Fatfs Error!
			}
				
			else
			{
				exfuns_init();							//Ϊfatfs��ر��������ڴ�		
				f_mount(fs[0],"0:",1); 					//����SD�� 
				if(exf_getfree("0",&total,&free))
					//SD Card Fatfs Error!
					lv_label_set_text(my_lv_obj.win_setSDCard_label, "SD卡文件系统错误 请检查！ ");
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
			sprintf(totalchar, "SD卡正常 \n总大小： %.2f GB\n",(double)total/1024.0);
			sprintf(freechar, "剩余可用大小：%.2f GB",(double)free/1024.0);			
			strcpy(temp,totalchar);
			strcat(temp,freechar);
			lv_label_set_text(my_lv_obj.win_setSDCard_label, temp);
			my_lv_obj.SDCard_flag = SD_READY;//SD Card Ready!
		}
	}
}



