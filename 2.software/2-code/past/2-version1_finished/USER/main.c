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


#define ADC_SAMPLE_CNUM 8//AD 采样通道数

//ALIENTEK 探索者STM32F407开发板 实验18
//ADC模数转换实验-库函数版本  
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


MY_LV_OBJ my_lv_obj;

int main()
{

	////////////////////System Init//////////////////////////////
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);														//设置系统中断优先级分组2
	delay_init(168);    																											//初始化延时函数
	uart_init(115200);																												//初始化串口		波特率为115200
	BEEP_Init();         																											//初始化蜂鸣器
	My_RTC_Init();RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);						//初始化RTC 		配置WAKE UP中断,1秒钟中断一次
//	Adc_Init();         																										//初始化ADC
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);		//初始化CAN			环回模式 波特率500Kbps
	TIM3_Int_Init(999,71);																										//初始化定时器1ms
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);		//初始化CAN			环回模式 波特率500Kbps
		
	////////////////////Lvgl Init//////////////////////////////
	FSMC_SRAM_Init();						//初始化外部SRAM  
	lvgl_init();								//初始化LVGL
	////////////////////can Init//////////////////////////////
	Init_3402(ADDRESS_3402);delay_ms(100);										//初始化3402模块
	Init_4055(ADDRESS_4055);delay_ms(100);										//初始化4055模块	
	Init_5801(ADDRESS_5801_1, 0xff);delay_ms(100);						//初始化5801模块
	Init_5801(ADDRESS_5801_2, 0x07);delay_ms(100);						//初始化5801模块
	enable_TPDO(ADDRESS_5801_2, TPDO2, TPDOCOMMAND_NO);
	enable_TPDO(ADDRESS_5801_2, TPDO3, TPDOCOMMAND_NO);
	Init_7017(ADDRESS_7017);delay_ms(100);										//初始化7017模块
	enable_TPDO(ADDRESS_7017, TPDO1, TPDOCOMMAND_YES);
	enable_TPDO(ADDRESS_7017, TPDO2, TPDOCOMMAND_YES);

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
			my_lv_obj.SDCard_flag = SD_ERROR;//SD Card Fatfs Error!
		else
			my_lv_obj.SDCard_flag = SD_READY;//SD Card Ready!
	}
		
	////////////////////win Init//////////////////////////////
	show_win_menu();
	BEEP_sound(1);
	while(1) 	
	{
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



