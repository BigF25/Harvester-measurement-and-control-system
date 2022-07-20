#include "comscreen.h"
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "stdio.h"
#include "hw_config.h"
#include "ulitity.h"
#include "string.h"
#include "delay.h"
#include "usart2.h"
#include "usart3.h"
#include "3402.h"
#include "4055.h"
#include "5801.h"
#include "7017.h"
#include "mylvgl.h"
#include "lcd.h"
#include "timer.h"

void screen_ID_case(void)
{
	uint16 screen_id = PTR2U16(&((PCTRL_MSG)my_comscreen_value.cmd_buffer)->screen_id);
	switch(screen_id)
	{
		case SCR_MAIN_ID:
			
			break;			
		case SCR_5801_1_ID:
			control_ID_case();
			break;
		case SCR_5801_2_ID:
			control_ID_case();
			break;			
		case SCR_7017_1_ID:
			control_ID_case();
			break;
		case SCR_7017_2_ID:
			control_ID_case();
			break;
		case SCR_4055_ID:
			control_ID_case();
			break;
		case SCR_3402_ID:
			control_ID_case();
			break;
		case SCR_SET_ID:
			control_ID_case();
			break;	
		default:
			break;
		}
}
void control_ID_case(void)
{
	uint16 control_id = PTR2U16(&((PCTRL_MSG)my_comscreen_value.cmd_buffer)->control_id);
	u8 button_state = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->param[1];
	uint32 slider_4055_value = PTR2U32(((PCTRL_MSG)my_comscreen_value.cmd_buffer)->param);
	static uint32 slider1_value = 0;
	static uint32 slider2_value = 0;
	switch(control_id)
	{
		case SCR_5801_1_CAN_BUT_ID:
			my_comscreen.scr_can_but_flag = button_state;
			break;
		case SCR_5801_1_SD_BUT_ID:
			my_comscreen.scr_sd_but_flag = button_state;
			break;
			
		case SCR_4055_MOTOR1_BUT_ENA_ID:
			if(button_state == 0) 
			{
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg & 0xFE;//11111110
				my_comscreen.scr_4055_motor1_but_ena_flag = 0;
			}
			else if(button_state == 1)
			{
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg | 0x01;//00000001
				my_comscreen.scr_4055_motor1_but_ena_flag = 1;
			}
			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen.scr_4055_motor_can_send_msg);
			break;
			
		case SCR_4055_MOTOR1_BUT_DIR_ID:
			if(button_state == 0) 
			{
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg & 0xFD;//11111110
				my_comscreen.scr_4055_motor1_but_dir_flag = 0;
			}
			else if(button_state == 1)
			{
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg | 0x02;//00000001
				my_comscreen.scr_4055_motor1_but_dir_flag = 1;
			}
			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen.scr_4055_motor_can_send_msg);
			break;
			
		case SCR_4055_MOTOR1_SLIDER_ID:
			my_comscreen.scr_4055_motor1_slider_value = slider_4055_value;
			break;
			
		case SCR_4055_MOTOR2_BUT_ENA_ID:
			if(button_state == 0) 
			{
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg & 0xDF;//11111110
				my_comscreen.scr_4055_motor2_but_ena_flag = 0;
			}
			else if(button_state == 1)
			{
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg | 0x20;//00000001
				my_comscreen.scr_4055_motor2_but_ena_flag = 1;
			}
				
			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen.scr_4055_motor_can_send_msg);
			break;
			
		case SCR_4055_MOTOR2_BUT_DIR_ID:
			if(button_state == 0) 
			{
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg & 0xBF;//11111110
				my_comscreen.scr_4055_motor3_but_dir_flag = 0;
			}
			else if(button_state == 1)
			{
				my_comscreen.scr_4055_motor_can_send_msg = my_comscreen.scr_4055_motor_can_send_msg | 0x40;//00000001
				my_comscreen.scr_4055_motor3_but_dir_flag = 1;
			}
			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen.scr_4055_motor_can_send_msg);
			break;
			
		case SCR_4055_MOTOR2_SLIDER_ID:
			my_comscreen.scr_4055_motor2_slider_value = slider_4055_value;
			break;
			
		case SCR_3402_SLIDER1_ID:
			slider1_value = PTR2U32(((PCTRL_MSG)my_comscreen_value.cmd_buffer)->param);
			Set_3402_Analogoutput(ADDRESS_3402, slider1_value, slider2_value);
			break;
			
		case SCR_3402_SLIDER2_ID:
			slider2_value = PTR2U32(((PCTRL_MSG)my_comscreen_value.cmd_buffer)->param);
			Set_3402_Analogoutput(ADDRESS_3402, slider1_value, slider2_value);
			break;
		case SCR_SET_SD_BUT_ID:
		{
			u32 total,free;
			if(SD_GetState() == SD_CARD_ERROR)
			{
				if(SD_Init())
				{
					my_comscreen.sd_ready_flag = 0;
					const u8 LEN = 64;
					u8 comscreen_send_msg[LEN] = {0xEE,0xB1,0x10,0x00,0x07,0x00,0x02,0x53,0x44,0xBF,0xA8,0xB4,0xED,0xCE,0xF3,0xFF,0xFC,0xFF,0xFF };
					my_USART_Send_Data(comscreen_send_msg,LEN);
				}
				else
				{
					exfuns_init();							//为fatfs相关变量申请内存		
					f_mount(fs[0],"0:",1); 					//挂载SD卡 
					if(exf_getfree("0",&total,&free))//SD Card Fatfs Error!
					{				
						my_comscreen.sd_ready_flag = 0;
						const u8 LEN = 64;
						u8 comscreen_send_msg[LEN] = {0xEE,0xB1,0x10,0x00,0x07,0x00,0x02,0x53,0x44,0xBF,0xA8,0xB4,0xED,0xCE,0xF3,0xFF,0xFC,0xFF,0xFF };
						my_USART_Send_Data(comscreen_send_msg,LEN);
					}
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
				my_comscreen.sd_ready_flag = 1;
				const u8 LEN = 64;
				u8 comscreen_send_msg[LEN] = {0xEE,0xB1,0x10,0x00,0x07,0x00,0x02,0x53,0x44,0xBF,0xA8,0xD5,0xFD,0xB3,0xA3,0xFF,0xFC,0xFF,0xFF };
				my_USART_Send_Data(comscreen_send_msg,LEN);
			}
			break;	
		}
	}
}
void comscreen_value_init(void)
{
	my_comscreen_value.timer_tick_count = 0;                                               //定时器节拍
	my_comscreen_value.current_screen_id = 0;                                                 //当前画面ID
	my_comscreen_value.progress_value = 0;                                                     //进度条测试值
	my_comscreen_value.test_value = 0;                                                         //测试值
	my_comscreen_value.update_en = 0;                                                          //更新标记
	my_comscreen_value.meter_flag = 0;                                                         //仪表指针往返标志位
	my_comscreen_value.num = 0;                                                                //曲线采样点计数
	my_comscreen_value.sec = 1;                                                                  //时间秒
	my_comscreen_value.curves_type = 0;                                                        //曲线标志位  0为正弦波，1为锯齿波
	my_comscreen_value.second_flag=0;                                                          //时间标志位
	my_comscreen_value.icon_flag = 0;                                                          //图标标志位
	my_comscreen_value.Progress_Value = 0;                                                     //进度条的值
	my_comscreen.scr_can_but_flag=0;
	my_comscreen.scr_sd_but_flag=0;	
	my_comscreen.sd_ready_flag=0;	
	my_comscreen.scr_4055_motor1_but_ena_flag=0;
	my_comscreen.scr_4055_motor1_but_dir_flag=0;	
	my_comscreen.scr_4055_motor2_but_ena_flag=0;
	my_comscreen.scr_4055_motor3_but_dir_flag=0;
	my_comscreen.scr_4055_motor1_slider_value=1;
	my_comscreen.scr_4055_motor2_slider_value=1;
}
/*!
*  \brief  消息处理流程
*  \param msg 待处理消息
*  \param size 消息长度
*/
void ProcessMessage( PCTRL_MSG msg, uint16 size ) 
{
	uint8 cmd_type = msg->cmd_type;                                                  //指令类型
	uint8 ctrl_msg = msg->ctrl_msg;                                                  //消息的类型
	uint8 control_type = msg->control_type;                                          //控件类型
	uint16 screen_id = PTR2U16(&msg->screen_id);                                     //画面ID
	uint16 control_id = PTR2U16(&msg->control_id);                                   //控件ID
	uint32 value = PTR2U32(msg->param);                                              //数值


	switch(cmd_type) 
	{
		case NOTIFY_TOUCH_PRESS:                                                        //触摸屏按下
		case NOTIFY_TOUCH_RELEASE:                                                      //触摸屏松开
			NotifyTouchXY(my_comscreen_value.cmd_buffer[1],PTR2U16(my_comscreen_value.cmd_buffer+2),PTR2U16(my_comscreen_value.cmd_buffer+4));
			break;
		case NOTIFY_WRITE_FLASH_OK:                                                     //写FLASH成功
			NotifyWriteFlash(1);
			break;
		case NOTIFY_WRITE_FLASH_FAILD:                                                  //写FLASH失败
			NotifyWriteFlash(0);
			break;
		case NOTIFY_READ_FLASH_OK:                                                      //读取FLASH成功
			NotifyReadFlash(1,my_comscreen_value.cmd_buffer+2,size-6);                                     //去除帧头帧尾
			break;
		case NOTIFY_READ_FLASH_FAILD:                                                   //读取FLASH失败
			NotifyReadFlash(0,0,0);
			break;
		case NOTIFY_READ_RTC:                                                           //读取RTC时间
			NotifyReadRTC(my_comscreen_value.cmd_buffer[2],my_comscreen_value.cmd_buffer[3],my_comscreen_value.cmd_buffer[4],my_comscreen_value.cmd_buffer[5],my_comscreen_value.cmd_buffer[6],my_comscreen_value.cmd_buffer[7],my_comscreen_value.cmd_buffer[8]);
			break;
		case NOTIFY_CONTROL: {
			if(ctrl_msg==MSG_GET_CURRENT_SCREEN) {                                  //画面ID变化通知
				NotifyScreen(screen_id);                                            //画面切换调动的函数
			} else {
				switch(control_type) {
					case kCtrlButton:                                                   //按钮控件
						NotifyButton(screen_id,control_id,msg->param[1]);
						break;
					case kCtrlText:                                                     //文本控件
						NotifyText(screen_id,control_id,msg->param);
						break;
					case kCtrlProgress:                                                 //进度条控件
						NotifyProgress(screen_id,control_id,value);
						break;
					case kCtrlSlider:                                                   //滑动条控件
						NotifySlider(screen_id,control_id,value);
						break;
					case kCtrlMeter:                                                    //仪表控件
						NotifyMeter(screen_id,control_id,value);
						break;
					case kCtrlMenu:                                                     //菜单控件
						NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);
						break;
					case kCtrlSelector:                                                 //选择控件
						NotifySelector(screen_id,control_id,msg->param[0]);
						break;
					case kCtrlRTC:                                                      //倒计时控件
						NotifyTimer(screen_id,control_id);
						break;
					default:
						break;
				}
			}
			break;
		}
		case NOTIFY_HandShake:                                                          //握手通知
			NOTIFYHandShake();
			break;
		default:
			break;
	}
}
/*!
*  \brief  握手通知
*/
void NOTIFYHandShake(void) 
{
	SetButtonValue(3,2,1);
}

/*!
*  \brief  画面切换通知
*  \details  当前画面改变时(或调用GetScreen)，执行此函数
*  \param screen_id 当前画面ID
*/
void NotifyScreen(uint16 screen_id) 
{
	//TODO: 添加用户代码
	my_comscreen_value.current_screen_id = screen_id;                                                   //在工程配置中开启画面切换通知，记录当前画面ID

	//进到画面3亮起一个按钮
	if(screen_id == 3) {
		SetButtonValue(3,1,1);
	}
	//进到画面自动播放GIF
	if(my_comscreen_value.current_screen_id == 9) {
		AnimationStart(9,1);                                                         //动画开始播放
	}
	//进到进度条界面获取当前文本值
	if(my_comscreen_value.current_screen_id==5) {
		GetControlValue(5,1);
	}
	//进到二维码页面生成二维码
	if(my_comscreen_value.current_screen_id==14) {
		//二维码控件显示中文字符时，需要转换为UTF8编码，
		//通过“指令助手”，转换“www.gz-dc.com” ，得到字符串编码如下
		uint8 dat[] = {0x77,0x77,0x77,0x2E,0x67,0x7A,0x2D,0x64,0x63,0x2E,0x63,0x6F,0x6D};
		SetTextValue(14,1,dat);                                                      //发送二维码字符编码
	}

	//数据记录显示
	if(my_comscreen_value.current_screen_id == 15) {
		Record_SetEvent(15,1,0,0);
		Record_SetEvent(15,1,1,0);
		Record_SetEvent(15,1,2,0);
		Record_SetEvent(15,1,3,0);
		Record_SetEvent(15,1,4,0);
		Record_SetEvent(15,1,5,0);
		Record_SetEvent(15,1,6,0);
		Record_SetEvent(15,1,7,0);
		delay_ms(2000);                                                              //延时两秒
		Record_ResetEvent(15,1,0,0);
		Record_ResetEvent(15,1,1,0);
		Record_ResetEvent(15,1,2,0);

	}

}

/*!
*  \brief  触摸坐标事件响应
*  \param press 1按下触摸屏，3松开触摸屏
*  \param x x坐标
*  \param y y坐标
*/
void NotifyTouchXY(uint8 press,uint16 x,uint16 y) 
{
	//TODO: 添加用户代码
}


/*!
*  \brief  更新数据
*  注意：若串口屏没有RTC 请先看下工程画面ID，对应工功能画面的编号与下面数据刷新的一致
*/
void UpdateUI(void) 
{
	/**************** 文本画面，画面编号4   **********************/
	//文本设置和显示  定时20ms刷新一次
	if(my_comscreen_value.current_screen_id==4) {
		//当前电流、温度从0到1000循环显示，艺术字从0-999循环显示
		SetTextInt32(4,6,my_comscreen_value.test_value%1000,0,1);                                      //当前电流
		SetTextInt32(4,7,my_comscreen_value.test_value%1000,0,1);                                      //艺术字
		SetTextValue(4,1,"机房10");                                                 //设置文本值

		my_comscreen_value.test_value++;
		if(my_comscreen_value.test_value >= 1000) {
			my_comscreen_value.test_value = 0;
		}
		if(my_comscreen_value.test_value>0&&my_comscreen_value.test_value<500) {                                           //大于0小于500文本显示红色
			SetControlBackColor(4,6,0xF800);                                         //设置文本背景色
		} else if(my_comscreen_value.test_value>=500) {                                                 //大于500文本显蓝色
			SetControlBackColor(4,6,0x001F);                                         //设置文本背景色
		}
	}
	/**************** 仪表画面，画面编号6   **********************/
	//仪表控件   定时20ms刷新一次
	if(my_comscreen_value.current_screen_id == 6) {
		if(my_comscreen_value.meter_flag == 0) {                                                        //标志位 0顺时针 ，1逆时针
			//顺时针旋转
			SetMeterValue(6,1,my_comscreen_value.test_value);                                           //设置图片指针旋转角度
			my_comscreen_value.test_value +=1;                                                          //指针旋转从0度到260度
			if(my_comscreen_value.test_value >= 260) {
				my_comscreen_value.test_value = 260;
				my_comscreen_value.meter_flag = 1;
			}
		} else if(my_comscreen_value.meter_flag == 1) {
			//逆时针旋转
			Set_picMeterValue(6,1,my_comscreen_value.test_value);                                       //设置图片指针旋转角度
			my_comscreen_value.test_value -=1;                                                          //指针旋转从260度到0度
			if(my_comscreen_value.test_value <= 0) {
				my_comscreen_value.test_value = 0;
				my_comscreen_value.meter_flag = 0;
			}
		}
	}
	/**************** 图标画面，画面编号10   **********************/
	//图标1s轮流显示
	if(my_comscreen_value.current_screen_id == 10) {
		if(my_comscreen_value.timer_tick_count %100 == 0 && my_comscreen_value.icon_flag == 0) {
			SetButtonValue(10,5,0);
			SetButtonValue(10,2,1);                                                      //工作中图标
			AnimationPlayFrame(10,1,0);
			my_comscreen_value.icon_flag = 1 ;
		} else if(my_comscreen_value.timer_tick_count %100 == 0 && my_comscreen_value.icon_flag == 1) {
			SetButtonValue(10,2,0);
			SetButtonValue(10,3,1);                                                      //暂停中图标
			AnimationPlayFrame(10,1,1);
			my_comscreen_value.icon_flag = 2;
		} else if(my_comscreen_value.timer_tick_count %100 == 0 && my_comscreen_value.icon_flag == 2) {
			SetButtonValue(10,3,0);
			SetButtonValue(10,4,1);                                                      //停止图标
			AnimationPlayFrame(10,1,2);
			my_comscreen_value.icon_flag = 3 ;
		} else if(my_comscreen_value.timer_tick_count %100 == 0 && my_comscreen_value.icon_flag == 3) {
			SetButtonValue(10,4,0);
			SetButtonValue(10,5,1);                                                      //隐藏图标
			AnimationPlayFrame(10,1,3);
			my_comscreen_value.icon_flag  = 0 ;
		}
	}

	/**************** 曲线画面，画面编号11   **********************/
	//实时曲线，正弦波数组。  定时20ms更新数据
	if(my_comscreen_value.current_screen_id == 11) {
		if(my_comscreen_value.curves_type == 0) {
			//正弦数组
			uint8 sin[256] = {1,1,1,1,1,2,3,4,6,8,10,13,15,
			                  19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
			                  140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
			                  236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
			                  245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
			                  158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
			                  33,29,25,22,19,15,13,10,8,6,4,3,2,1,1,1,1,1,2,3,4,6,8,10,13,15,
			                  19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
			                  140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
			                  236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
			                  245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
			                  158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
			                  33,29,25,22,19,15,13,10,8,6,4,3,2
			                 };

			GraphChannelDataAdd(11,1,0,&sin[my_comscreen_value.num],2);                                    //添加数据到曲线  一次两个数据

			my_comscreen_value.num += 2;
			if(my_comscreen_value.num >= 255) {
				my_comscreen_value.num =0;
			}
		} else if(my_comscreen_value.curves_type == 1) {
			//锯齿波数组
			uint8 sawtooth[180] = {0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252
			                      };


			GraphChannelDataAdd(11,1,0,&sawtooth[my_comscreen_value.num],2);                              //添加数据到曲线  一次两个数据
			my_comscreen_value.num +=2 ;
			if(my_comscreen_value.num >= 180) {
				my_comscreen_value.num =0;
			}
		}
	}
	/**************** 历时曲线画面，画面编号16   **********************/
	//历时曲线，正弦波数组
	if(my_comscreen_value.current_screen_id == 16 && my_comscreen_value.timer_tick_count %100 == 0) {                         //历史曲线控件采样周期1s一个点。//一次添加五个数据
		if(my_comscreen_value.curves_type == 0) {
			//正弦数组
			uint8 sin[256] = {1,1,1,1,1,2,3,4,6,8,10,13,15,
			                  19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
			                  140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
			                  236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
			                  245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
			                  158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
			                  33,29,25,22,19,15,13,10,8,6,4,3,2,1,1,1,1,1,2,3,4,6,8,10,13,15,
			                  19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
			                  140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
			                  236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
			                  245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
			                  158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
			                  33,29,25,22,19,15,13,10,8,6,4,3,2
			                 };

			HistoryGraph_SetValueInt8(16,1,&sin[my_comscreen_value.num],1);                               //添加历史曲线数据
			my_comscreen_value.num++;
			if(my_comscreen_value.num >= 255) {
				my_comscreen_value.num =0;
			}
		} else if(my_comscreen_value.curves_type == 1) {
			//锯齿波数组
			uint8 sawtooth[180] = {0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252
			                      };

			HistoryGraph_SetValueInt8(16,1,&sawtooth[my_comscreen_value.num],1);                          //添加历史曲线数据
			my_comscreen_value.num++;
			if(my_comscreen_value.num >= 90) {
				my_comscreen_value.num =0;
			}
		}


	}

}


/*!
*  \brief  按钮控件通知
*  \details  当按钮状态改变(或调用GetControlValue)时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param state 按钮状态：0弹起，1按下
*/
void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state) 
{
	//按键控制曲线波形
	if(screen_id == 11) {
		if(control_id==2) {                                                          //正弦波控件
			my_comscreen_value.curves_type = 0;
		} else if(control_id==3) {                                                   //锯齿波控件
			my_comscreen_value.curves_type = 1;
		}
	}
	//时间画面按钮获取RTC时间
	if(screen_id == 8) {
		if(control_id==8 && state == 1) {                                            //获取时间
			ReadRTC();
		}
	}
	//选择控件显示时间段
	if(screen_id == 13 && control_id==4) {
		if(my_comscreen_value.Select_H>=0&&my_comscreen_value.Select_H<=6) {                                                     //0~6小时，凌晨
			SetSelectorValue(13,3,0);                                                       //设置选择控件选项
		}

		else if(my_comscreen_value.Select_H>=7&&my_comscreen_value.Select_H<=12) {                                                //7~12小时，上午
			SetSelectorValue(13,3,1);
		}

		else if(my_comscreen_value.Select_H>=13&&my_comscreen_value.Select_H<=18) {                                               //13~18小时，下午
			SetSelectorValue(13,3,2);
		}

		else if(my_comscreen_value.Select_H>18&&my_comscreen_value.Select_H<=23) {                                                //19~23小时，深夜
			SetSelectorValue(13,3,3);
		}
		my_comscreen_value.Last_H   = my_comscreen_value.Select_H;
		my_comscreen_value.Last_M   = my_comscreen_value.Select_M;
	}
	if(screen_id == 13 && control_id==5) {
		SetSelectorValue(13,1,my_comscreen_value.Last_H);
		SetSelectorValue(13,2,my_comscreen_value.Last_M);
	}
	if(screen_id == 5) {
		if(control_id==3) {                                                          //递减
			my_comscreen_value.Progress_Value -= 1;
			if(my_comscreen_value.Progress_Value <= 0) {
				my_comscreen_value.Progress_Value = 0;
			}
			SetProgressValue(5,1,my_comscreen_value.Progress_Value);                                    //设置进度条的值
			SetTextInt32(5,2,my_comscreen_value.Progress_Value,0,1);                                    //设置文本框的值
		} else if(control_id==4) {                                                   //递加
			my_comscreen_value.Progress_Value += 1;
			if(my_comscreen_value.Progress_Value >= 100) {
				my_comscreen_value.Progress_Value = 100;
			}
			SetProgressValue(5,1,my_comscreen_value.Progress_Value);
			SetTextInt32(5,2,my_comscreen_value.Progress_Value,0,1);
		}
	}

}

/*!
*  \brief  文本控件通知
*  \details  当文本通过键盘更新(或调用GetControlValue)时，执行此函数
*  \details  文本控件的内容以字符串形式下发到MCU，如果文本控件内容是浮点值，
*  \details  则需要在此函数中将下发字符串重新转回浮点值。
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param str 文本控件内容
*/
void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str) 
{
	if(screen_id==4) {                                                               //画面ID2：文本设置和显示
		int32 value=0;
		sscanf(str,"%ld",&value);                                                    //把字符串转换为整数
		if(control_id==2) {                                                          //最高电压
			//限定数值范围（也可以在文本控件属性中设置）
			if(value<0) {
				value = 0;
			} else if(value>380) {
				value = 380;
			}
			SetTextInt32(4,2,value,0,1);                                             //更新最高电压
			SetTextInt32(4,5,value/2,1,1);                                           //更新最高电压/2
		}
	}
}

/*!
*  \brief  进度条控件通知
*  \details  调用GetControlValue时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param value 值
*/
void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value) 
{
	if(screen_id == 5) {
		my_comscreen_value.Progress_Value = value;
		SetTextInt32(5,2,my_comscreen_value.Progress_Value,0,1);                                        //设置文本框的值
	}
}

/*!
*  \brief  滑动条控件通知
*  \details  当滑动条改变(或调用GetControlValue)时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param value 值
*/
void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value) 
{
	uchar back[1] = {0};
	if(screen_id==7&&control_id==2) {                                                //滑块控制
		if(value<100||value>0) {
			SetProgressValue(7,1,value);                                             //更新进度条数值
			SetTextInt32(7,3,value,0,1);
			sprintf(back,"%c",(255-value*2));                                        //设置背光亮度 背光值范围 0~255，0最亮，255最暗
			SetBackLight(back[0]);
		}
	}
	if(screen_id==7&&control_id==5) {                                                //滑块控制
		if(value<100||value>0) {
			SetProgressValue(7,4,value);                                             //更新进度条数值
			SetTextInt32(7,6,value,0,1);
		}
	}
}

/*!
*  \brief  仪表控件通知
*  \details  调用GetControlValue时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param value 值
*/
void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value) 
{
	//TODO: 添加用户代码
}

/*!
*  \brief  菜单控件通知
*  \details  当菜单项按下或松开时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param item 菜单项索引
*  \param state 按钮状态：0松开，1按下
*/
void NotifyMenu(uint16 screen_id, uint16 control_id, uint8 item, uint8 state) 
{
	//TODO: 添加用户代码
}

/*!
*  \brief  选择控件通知
*  \details  当选择控件变化时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param item 当前选项
*/
void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item) 
{
	if(screen_id == 13&&control_id == 1) {                              //获取当前选择控件的值
		my_comscreen_value.Select_H =  item;
	}
	if(screen_id == 13&&control_id == 2) {                              //获取当前选择控件的值
		my_comscreen_value.Select_M =  item;
	}

}

/*!
*  \brief  定时器超时通知处理
*  \param screen_id 画面ID
*  \param control_id 控件ID
*/
void NotifyTimer(uint16 screen_id, uint16 control_id) 
{
	if(screen_id==8&&control_id == 7) {
		SetBuzzer(100);
	}
}

/*!
*  \brief  读取用户FLASH状态返回
*  \param status 0失败，1成功
*  \param _data 返回数据
*  \param length 数据长度
*/
void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length) 
{
	//TODO: 添加用户代码
}

/*!
*  \brief  写用户FLASH状态返回
*  \param status 0失败，1成功
*/
void NotifyWriteFlash(uint8 status) 
{
	//TODO: 添加用户代码
}

/*!
*  \brief  读取RTC时间，注意返回的是BCD码
*  \param year 年（BCD）
*  \param month 月（BCD）
*  \param week 星期（BCD）
*  \param day 日（BCD）
*  \param hour 时（BCD）
*  \param minute 分（BCD）
*  \param second 秒（BCD）
*/
void NotifyReadRTC(uint8 year,uint8 month,uint8 week,uint8 day,uint8 hour,uint8 minute,uint8 second) 
{
	int years,months,weeks,days,hours,minutes;

	my_comscreen_value.sec    =(0xff & (second>>4))*10 +(0xf & second);                                    //BCD码转十进制
	years   =(0xff & (year>>4))*10 +(0xf & year);
	months  =(0xff & (month>>4))*10 +(0xf & month);
	weeks   =(0xff & (week>>4))*10 +(0xf & week);
	days    =(0xff & (day>>4))*10 +(0xf & day);
	hours   =(0xff & (hour>>4))*10 +(0xf & hour);
	minutes =(0xff & (minute>>4))*10 +(0xf & minute);

	SetTextInt32(8,1,years,1,1);
	SetTextInt32(8,2,months,1,1);
	SetTextInt32(8,3,days,1,1);
	SetTextInt32(8,4,hours,1,1);
	SetTextInt32(8,5,minutes,1,1);
	SetTextInt32(8,6,my_comscreen_value.sec,1,1);
	if(weeks == 0) {
		SetTextValue(8,7,"星期日");
	} else if(weeks == 1) {
		SetTextValue(8,7,"星期一");
	} else if(weeks == 2) {
		SetTextValue(8,7,"星期二");
	} else if(weeks == 3) {
		SetTextValue(8,7,"星期三");
	} else if(weeks == 4) {
		SetTextValue(8,7,"星期四");
	} else if(weeks == 5) {
		SetTextValue(8,7,"星期五");
	} else if(weeks == 6) {
		SetTextValue(8,7,"星期六");
	}
}
