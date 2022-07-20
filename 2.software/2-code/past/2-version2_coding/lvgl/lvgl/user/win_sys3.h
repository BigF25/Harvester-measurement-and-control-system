#ifndef WIN_SYS3_H
#define WIN_SYS3_H
#include "sys.h"
#include "mylvgl.h"

void show_win_sys3(void);
void win_sys3_close_btn_handler(lv_obj_t * obj, lv_event_t event);
void win_sys3_msg_btn_handler(lv_obj_t * obj, lv_event_t event);
void win_sys3_motor1_ena_switch_handler(lv_obj_t * obj, lv_event_t event);
void win_sys3_motor1_dir_switch_handler(lv_obj_t * obj, lv_event_t event);
void win_sys3_motor2_ena_switch_handler(lv_obj_t * obj, lv_event_t event);
void win_sys3_motor2_dir_switch_handler(lv_obj_t * obj, lv_event_t event);
void win_sys3_motor1_speed_slider_handler(lv_obj_t * obj, lv_event_t event);
void win_sys3_motor2_speed_slider_handler(lv_obj_t * obj, lv_event_t event);
void win_sys3_state_show(void);

#endif


