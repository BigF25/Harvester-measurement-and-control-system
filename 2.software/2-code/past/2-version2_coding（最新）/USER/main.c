#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "beep.h"
#include "rtc.h"
#include "adc.h"
#include "can.h"
#include "mylvgl.h"
#include "timer.h"
#include "usart2.h"
#include "usart3.h"
#include "comscreen.h"
#include "button.h" 
#include "atk_m750.h"
#include "RingBuffer.h"
#include "string.h"
#include "oled.h"

MY_LV_OBJ my_lv_obj;
COMSCREEN_VAL my_comscreen_value;
COMSCREEN my_comscreen;


void finish_tmep(void);
void test_comscreen(void);


int main() {
	////////////////////System Init//////////////////////////////
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);														//设置系统中断优先级分组2
	delay_init(168);    																											//初始化延时函数
	uart_init(115200);																												//初始化串口		波特率为115200
	USART2_Init(115200);																												//初始化usart串口2
	USART3_Init(115200);																												//初始化usart串口3
	BEEP_Init();         																											//初始化蜂鸣器
	My_RTC_Init();
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);						//初始化RTC 		配置WAKE UP中断,1秒钟中断一次
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);		//初始化CAN			环回模式 波特率500Kbps
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);//CAN初始化环回模式,波特率500Kbps    
	TIM3_Int_Init(999,71);																										//初始化定时器1ms
	LCD_Init();
	////////////////////button和IIC1的PA6、7冲突//////////////////////////////
	BUTTON_Init();//button和IIC1的PA6、7冲突
	////////////////////can Init//////////////////////////////

//	Init_3402(ADDRESS_3402);
//	enable_TPDO(ADDRESS_3402, _TPDO1, TPDOCOMMAND_NO);
//	enable_TPDO(ADDRESS_3402, _TPDO2, TPDOCOMMAND_NO);delay_ms(100);
//	enable_TPDO(ADDRESS_3402, _TPDO3, TPDOCOMMAND_NO);
//	enable_TPDO(ADDRESS_3402, _TPDO4, TPDOCOMMAND_NO);delay_ms(100);

//	enable_TPDO(ADDRESS_5801_1, _TPDO1, TPDOCOMMAND_YES);
//	enable_TPDO(ADDRESS_5801_1, _TPDO2, TPDOCOMMAND_YES);delay_ms(100);
//	enable_TPDO(ADDRESS_5801_1, _TPDO3, TPDOCOMMAND_YES);
//	enable_TPDO(ADDRESS_5801_1, _TPDO4, TPDOCOMMAND_YES);delay_ms(100);
	
//	enable_TPDO(ADDRESS_5801_2, _TPDO1, TPDOCOMMAND_YES);
//	enable_TPDO(ADDRESS_5801_2, _TPDO2, TPDOCOMMAND_YES);delay_ms(100);
//	enable_TPDO(ADDRESS_5801_2, _TPDO3, TPDOCOMMAND_YES);
//	enable_TPDO(ADDRESS_5801_2, _TPDO4, TPDOCOMMAND_YES);delay_ms(100);

//	Init_4055(id);
//	Init_5801(ADDRESS_5801_1, 0xff);delay_ms(100);
//	Init_5801(ADDRESS_5801_2, 0x07);delay_ms(100);
//	enable_TPDO(ADDRESS_5801_2, _TPDO2, TPDOCOMMAND_YES);delay_ms(100);
//	Init_7017(ADDRESS_7017);delay_ms(100);
//	enable_TPDO(ADDRESS_7017, _TPDO1, TPDOCOMMAND_YES);delay_ms(100);
//	enable_TPDO(ADDRESS_7017, _TPDO2, TPDOCOMMAND_YES);delay_ms(100);

////////////////////5801 清零////////////////////////
	u8 clear_temp[8] = {0, 0, 0, 0, 1, 1, 1, 1};
	Set_5801_ClearCount(ADDRESS_5801_2, clear_temp);//清零计数通道

	////////////////////SD卡 FATFS Init////////////////////////

	usmart_dev.init(84);				//初始化USMART
	W25QXX_Init();							//初始化W25Q128
	my_mem_init(SRAMIN);				//初始化内部内存池
	my_mem_init(SRAMCCM);				//初始化CCM内存池
	if(SD_Init())								//初始化SD卡
		;//SD Card Error!
	else 
	{
		exfuns_init();//为fatfs相关变量申请内存
		f_mount(fs[0],"0:",1);//挂载SD卡
		if(exf_getfree("0",NULL,NULL))
			my_comscreen.sd_ready_flag = 0;//SD Card Fatfs Error!
		else
			my_comscreen.sd_ready_flag = 1;//SD Card Ready!
	}

	////////////////串口屏初始化//////////////////////////////
	systicket_init();//配置时钟节拍
	queue_reset();//清空串口接收缓冲区
	delay_ms(300);//延时等待串口屏初始化完毕,必须等待300ms
	
	//////////////////oled初始化//////////////////////////////
//	I2C_Configuration();
//	OLED_Init();
//	delay_ms(50);
//		
//	OLED_Fill(0xFF);
//	delay_ms(50);
//		
//	OLED_Fill(0x00);
//	delay_ms(50);
//	
//	//////////////////LCD初始化//////////////////////////////

 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(20,20,200,16,16,"can_send_msg");	
  POINT_COLOR=BLUE;//设置字体为蓝色	   

	qsize size = 0;
	u8 canbuf[8];
	u8 key;
	my_comscreen.sys_init_ready=1;	
		
		while(1)
		{
				u8 a[] = "aaaa";
		USART2_Send_Data(a,3);
		printf("updata");
		}
		
		
		
		
	while(1) 
	{
		qsize size = 0;
		USART3_Receive_Data(my_comscreen_value.cmd_buffer,&size);
		if(size>0)
			screen_ID_case();
		if(my_comscreen.scr_can_but_flag == 1)
			rec_can_value(my_comscreen.scr_5801_result_int, my_comscreen.scr_7017_result_int);
//		BUTTON_C1 = 1;
		set(BUTTON_B5,BUTTON_C1);
		set(BUTTON_B6,BUTTON_C2);
		set(BUTTON_B7,BUTTON_C3);
		set(BUTTON_B8,BUTTON_C4);
		set(BUTTON_B12,BUTTON_C5);
		set(BUTTON_B13,BUTTON_C6);
		
		delay_ms(50);
		rec_5801_ImpulseValue(ADDRESS_5801_1, my_lv_obj.win_sys1_5801_result_int_1);
		for(int i=0; i<8; i++)
		{
			sprintf(my_lv_obj.win_sys1_5801_result_char_1[i], "%.2f", my_lv_obj.win_sys1_5801_result_int_1[i]*0.6);
			LCD_ShowString(60*(i+1),40,200,16,16, my_lv_obj.win_sys1_5801_result_char_1[i]);
		}
		rec_7017_AiValue(ADDRESS_7017, my_lv_obj.win_sys2_7017_result_int);
		for(int i=0; i<8; i++)
		{
			sprintf(my_lv_obj.win_sys2_7017_result_char[i], "%d", my_lv_obj.win_sys2_7017_result_int[i]);
			LCD_ShowString(60*(i+1),200,200,16,16, my_lv_obj.win_sys2_7017_result_char[i]);
		}
		//LCD_ShowString(20,40,200,16,16, my_lv_obj.win_sys1_5801_result_char_1[5]);		
		//send_atkm750_data(scr_5801_resultd, scr_7017_resultd);
	}
}
void test_comscreen(void)
{
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 usartbuf[14];
	u8 canbuf[8];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);   //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);//CAN初始化环回模式,波特率500Kbps    

	LED_Init();					//初始化LED
	LCD_Init();					//LCD初始化
	USART2_Init(9600);		//初始化usart串口2
	USART3_Init(9600);		//初始化usart串口3
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"CAN TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/7");
	LCD_ShowString(30,130,200,16,16,"LoopBack Mode");	 
	LCD_ShowString(30,150,200,16,16,"KEY0:Send WK_UP:Mode");//显示提示信息		
  POINT_COLOR=BLUE;//设置字体为蓝色	   
	LCD_ShowString(30,170,200,16,16,"Count:");		  	//显示当前计数值	
	LCD_ShowString(30,190,200,16,16,"Send Data:");		//提示发送的数据	
	LCD_ShowString(30,250,200,16,16,"Receive Data:");	//提示接收到的数据		
 			

	static int32 test_value = 0;                                                     //测试值
	uint32 timer_tick_last_update = 0;                                               //上一次更新的时间
	qsize  size = 0;

	//配置时钟节拍
	systicket_init();

	//清空串口接收缓冲区
	queue_reset();
	//延时等待串口屏初始化完毕,必须等待300ms
	delay_ms(300);

	while(1) 
	{
		USART3_Receive_Data(my_comscreen_value.cmd_buffer,&size);
		if(size>0&&my_comscreen_value.cmd_buffer[1]!=0x07) 
		{                                            //接收到指令 ，及判断是否为开机提示
			ProcessMessage((PCTRL_MSG)my_comscreen_value.cmd_buffer, size);                             //指令处理
//						LCD_ShowxNum(30+i*32,230,((PCTRL_MSG)cmd_buffer)->control_type,3,16,0X80);	//显示数据
		} else if(size>0&&my_comscreen_value.cmd_buffer[1]==0x07) 
		{                                     //如果为指令0x07就软重置STM32
			__disable_fault_irq();
			NVIC_SystemReset();
		}


		//    特别注意
		//    MCU不要频繁向串口屏发送数据，否则串口屏的内部缓存区会满，从而导致数据丢失(缓冲区大小：标准型8K，基本型4.7K)
		//    1) 一般情况下，控制MCU向串口屏发送数据的周期大于100ms，就可以避免数据丢失的问题；
		//    2) 如果仍然有数据丢失的问题，请判断串口屏的BUSY引脚，为高时不能发送数据给串口屏。

		//    TODO: 添加用户代码
		//    数据有更新时标志位发生改变，定时100毫秒刷新屏幕
		if(my_comscreen_value.update_en&&my_comscreen_value.timer_tick_count-timer_tick_last_update>=TIME_100MS) 
		{
			my_comscreen_value.update_en = 0;
			timer_tick_last_update = my_comscreen_value.timer_tick_count;
			UpdateUI();
		}

		//这里为了演示方便，每20毫秒自动更新一次
		//进一次中断10ms，timer_tick_count值+1,100*timer_tick_count = 1s
		if(my_comscreen_value.timer_tick_count%2==0) 
		{
			UpdateUI();
		}
//		uint8 cmd_type = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->cmd_type;                                                  //指令类型x
//		uint8 ctrl_msg = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->ctrl_msg;                                                  //消息的类型
		uint16 screen_id = PTR2U16(&((PCTRL_MSG)my_comscreen_value.cmd_buffer)->screen_id);                                     //画面ID
		uint16 control_id = PTR2U16(&((PCTRL_MSG)my_comscreen_value.cmd_buffer)->control_id);                                   //控件ID
		uint8 control_type = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->control_type;                                          //控件类型
		uint8 button_state = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->param[1];
		LCD_ShowxNum(30+i*32,230,button_state,3,16,0X80);
		if(screen_id==3 && control_id==31 && button_state && button_state==1) 
		{
			Set_4055_Switchoutput(ADDRESS_4055, 0xaa);
		}
		
		key=CAN1_Receive_Msg(canbuf);
		if(key)//接收到有数据
		{			
			LCD_Fill(30,270,160,310,WHITE);//清除之前的显示
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(30+i*32,270,canbuf[i],3,16,0X80);	//显示数据
				else LCD_ShowxNum(30+(i-4)*32,290,canbuf[i],3,16,0X80);	//显示数据
 			}
		}
	}
}

void test_usart(void) {
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 usartbuf[14];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);   //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200

	LED_Init();					//初始化LED
	LCD_Init();					//LCD初始化
	USART2_Init(9600);		//初始化usart串口2
	USART3_Init(9600);		//初始化usart串口3
	POINT_COLOR=RED;//设置字体为红色
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");
	LCD_ShowString(30,70,200,16,16,"RS485 TEST");
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/7");
	LCD_ShowString(30,130,200,16,16,"KEY0:Send");    	//显示提示信息

	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(30,150,200,16,16,"Count:");			  //显示当前计数值
	LCD_ShowString(30,170,200,16,16,"Send Data:");		//提示发送的数据
	LCD_ShowString(30,210,200,16,16,"Receive Data:");	//提示接收到的数据

	while(1) {
		USART2_Receive_Data(usartbuf,&key);
		if(key) { //接收到有数据
			if(key>14)key=14;//最大是5个数据.
			for(i=0; i<key; i++)LCD_ShowxNum(30+i*32,230,usartbuf[i],3,16,0X80);	//显示数据
		}
		t++;
		delay_ms(10);
		if(t==20) {
			LED0=!LED0;//提示系统正在运行
			t=0;
			cnt++;
			LCD_ShowxNum(30+48,150,cnt,3,16,0X80);	//显示数据
		}
	}
}


void finish_tmep() {
	////////////////////System Init//////////////////////////////
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);														//设置系统中断优先级分组2
	delay_init(168);    																											//初始化延时函数
	uart_init(115200);																												//初始化串口		波特率为115200
	BEEP_Init();         																											//初始化蜂鸣器
	My_RTC_Init();
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);						//初始化RTC 		配置WAKE UP中断,1秒钟中断一次
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);		//初始化CAN			环回模式 波特率500Kbps
	TIM3_Int_Init(999,71);																										//初始化定时器1ms

	////////////////////Lvgl Init//////////////////////////////
	FSMC_SRAM_Init();						//初始化外部SRAM
	lvgl_init();								//初始化LVGL

	////////////////////can Init//////////////////////////////
//	Init_3402(ADDRESS_3402);
//	delay_ms(100);										//初始化3402模块
//	Init_4055(ADDRESS_4055);
//	delay_ms(100);										//初始化4055模块
//	Init_5801(ADDRESS_5801_1, 0xff);
//	delay_ms(100);						//初始化5801模块
//	Init_5801(ADDRESS_5801_2, 0x07);
//	delay_ms(100);
//	enable_TPDO(ADDRESS_5801_2, TPDO2, TPDOCOMMAND_NO);
//	enable_TPDO(ADDRESS_5801_2, TPDO3, TPDOCOMMAND_NO);
//	Init_7017(ADDRESS_7017);
//	delay_ms(100);										//初始化7017模块
//	enable_TPDO(ADDRESS_7017, TPDO1, TPDOCOMMAND_YES);
//	enable_TPDO(ADDRESS_7017, TPDO2, TPDOCOMMAND_YES);

	////////////////////SD卡 FATFS Init////////////////////////
	usmart_dev.init(84);				//初始化USMART
	W25QXX_Init();							//初始化W25Q128
	my_mem_init(SRAMIN);				//初始化内部内存池
	my_mem_init(SRAMCCM);				//初始化CCM内存池
	if(SD_Init())								//初始化SD卡
		;//SD Card Error!
	else {
		exfuns_init();//为fatfs相关变量申请内存
		f_mount(fs[0],"0:",1);//挂载SD卡
		if(exf_getfree("0",NULL,NULL))
			my_lv_obj.SDCard_flag = SD_ERROR;//SD Card Fatfs Error!
		else
			my_lv_obj.SDCard_flag = SD_READY;//SD Card Ready!
	}

	////////////////////win Init//////////////////////////////
	show_win_menu();
	BEEP_sound(1);
	while(1) {
		lv_task_handler();
//	uint32_t id=0;
//	u32 buf[8];
//	rec_5801_ImpulseValue(1,buf,&id);
////	send_7017_msg(1);
//	rec_7017_msg(&id, buf);
//		rec_7017_AiValue(1, my_lv_obj.resutl_char);
//		if(id==0x181||1)
//		{
//			LCD_ShowxNum(10,10,my_lv_obj.win_sys3_slider_value,4,16,0);//delay_ms(1000);
//			LCD_ShowxNum(60+1*50,170,buf[0],4,16,0);//delay_ms(1000);
//			LCD_ShowxNum(60+2*50,170,buf[1],4,16,0);//delay_ms(1000);
//			LCD_ShowxNum(60+3*50,170,buf[2],4,16,0);//delay_ms(1000);
//			LCD_ShowxNum(60+4*50,170,buf[3],4,16,0);//delay_ms(1000);
//			LCD_ShowxNum(60+5*50,170,buf[4],4,16,0);delay_ms(1000);
//			LCD_ShowxNum(60+6*50,170,buf[5],4,16,0);//delay_ms(1000);
//			LCD_ShowxNum(60+7*50,170,buf[6],4,16,0);//delay_ms(1000);
//			LCD_ShowxNum(60+8*50,170,buf[7],4,16,0);//delay_ms(1000);
//		}
//	while(1) ;
	}

}
