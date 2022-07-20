#ifndef WIN_SYS1_H
#define WIN_SYS1_H
#include "sys.h"
#include "mylvgl.h"

void show_win_sys1(void);
void win_sys1_close_btn_handler(lv_obj_t * obj, lv_event_t event);
void win_sys1_table_up_btn_handler(lv_obj_t * obj, lv_event_t event);
void win_sys1_table_down_btn_handler(lv_obj_t * obj, lv_event_t event);
void win_sys1_msg_btn_handler(lv_obj_t * obj, lv_event_t event);
void win_sys1_can_rec_switch_handler(lv_obj_t * obj, lv_event_t event);
void win_sys1_sd_rec_switch_handler(lv_obj_t * obj, lv_event_t event);
void win_sys1_table_handler(lv_obj_t * obj, lv_event_t event);
void win_sys1_table_handler_event_send(void);

#define SHOW 1
#define dSHOW 0
void win_sys1_table_show(u8 num,u8 flag);
void win_sys1_switch_state_show(void);

#endif


