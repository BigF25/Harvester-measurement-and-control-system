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


#define ADC_SAMPLE_CNUM 8//AD ����ͨ����

//ALIENTEK ̽����STM32F407������ ʵ��18
//ADCģ��ת��ʵ��-�⺯���汾  
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


MY_LV_OBJ my_lv_obj;

int main()
{

	////////////////////System Init//////////////////////////////
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);														//����ϵͳ�ж����ȼ�����2
	delay_init(168);    																											//��ʼ����ʱ����
	uart_init(115200);																												//��ʼ������		������Ϊ115200
	BEEP_Init();         																											//��ʼ��������
	My_RTC_Init();RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);						//��ʼ��RTC 		����WAKE UP�ж�,1�����ж�һ��
//	Adc_Init();         																										//��ʼ��ADC
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);		//��ʼ��CAN			����ģʽ ������500Kbps
	TIM3_Int_Init(999,71);																										//��ʼ����ʱ��1ms
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);		//��ʼ��CAN			����ģʽ ������500Kbps
		
	////////////////////Lvgl Init//////////////////////////////
	FSMC_SRAM_Init();						//��ʼ���ⲿSRAM  
	lvgl_init();								//��ʼ��LVGL
	////////////////////can Init//////////////////////////////
	Init_3402(ADDRESS_3402);delay_ms(100);										//��ʼ��3402ģ��
	Init_4055(ADDRESS_4055);delay_ms(100);										//��ʼ��4055ģ��	
	Init_5801(ADDRESS_5801_1, 0xff);delay_ms(100);						//��ʼ��5801ģ��
	Init_5801(ADDRESS_5801_2, 0x07);delay_ms(100);						//��ʼ��5801ģ��
	enable_TPDO(ADDRESS_5801_2, TPDO2, TPDOCOMMAND_NO);
	enable_TPDO(ADDRESS_5801_2, TPDO3, TPDOCOMMAND_NO);
	Init_7017(ADDRESS_7017);delay_ms(100);										//��ʼ��7017ģ��
	enable_TPDO(ADDRESS_7017, TPDO1, TPDOCOMMAND_YES);
	enable_TPDO(ADDRESS_7017, TPDO2, TPDOCOMMAND_YES);

	////////////////////SD�� FATFS Init////////////////////////
	usmart_dev.init(84);				//��ʼ��USMART
	W25QXX_Init();							//��ʼ��W25Q128
	my_mem_init(SRAMIN);				//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);				//��ʼ��CCM�ڴ��
	if(SD_Init())								//��ʼ��SD��
		;//SD Card Error!
	else
	{
		exfuns_init();//Ϊfatfs��ر��������ڴ�		
		f_mount(fs[0],"0:",1);//����SD�� 
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



