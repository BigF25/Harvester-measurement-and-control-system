#ifndef WIN_SETTIME_H
#define WIN_SETTIME_H
#include "sys.h"
#include "mylvgl.h"



void show_win_settime(void);
void win_settime_roller_handler(lv_obj_t * obj, lv_event_t event);
void win_settime_close_btn_handler(lv_obj_t * obj, lv_event_t event); 
void win_settime_ok_btn_handler(lv_obj_t * obj, lv_event_t event); 

#endif


