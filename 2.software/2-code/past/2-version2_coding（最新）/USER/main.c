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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);														//����ϵͳ�ж����ȼ�����2
	delay_init(168);    																											//��ʼ����ʱ����
	uart_init(115200);																												//��ʼ������		������Ϊ115200
	USART2_Init(115200);																												//��ʼ��usart����2
	USART3_Init(115200);																												//��ʼ��usart����3
	BEEP_Init();         																											//��ʼ��������
	My_RTC_Init();
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);						//��ʼ��RTC 		����WAKE UP�ж�,1�����ж�һ��
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);		//��ʼ��CAN			����ģʽ ������500Kbps
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������500Kbps    
	TIM3_Int_Init(999,71);																										//��ʼ����ʱ��1ms
	LCD_Init();
	////////////////////button��IIC1��PA6��7��ͻ//////////////////////////////
	BUTTON_Init();//button��IIC1��PA6��7��ͻ
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

////////////////////5801 ����////////////////////////
	u8 clear_temp[8] = {0, 0, 0, 0, 1, 1, 1, 1};
	Set_5801_ClearCount(ADDRESS_5801_2, clear_temp);//�������ͨ��

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
			my_comscreen.sd_ready_flag = 0;//SD Card Fatfs Error!
		else
			my_comscreen.sd_ready_flag = 1;//SD Card Ready!
	}

	////////////////��������ʼ��//////////////////////////////
	systicket_init();//����ʱ�ӽ���
	queue_reset();//��մ��ڽ��ջ�����
	delay_ms(300);//��ʱ�ȴ���������ʼ�����,����ȴ�300ms
	
	//////////////////oled��ʼ��//////////////////////////////
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
//	//////////////////LCD��ʼ��//////////////////////////////

 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(20,20,200,16,16,"can_send_msg");	
  POINT_COLOR=BLUE;//��������Ϊ��ɫ	   

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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);   //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������500Kbps    

	LED_Init();					//��ʼ��LED
	LCD_Init();					//LCD��ʼ��
	USART2_Init(9600);		//��ʼ��usart����2
	USART3_Init(9600);		//��ʼ��usart����3
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"CAN TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/7");
	LCD_ShowString(30,130,200,16,16,"LoopBack Mode");	 
	LCD_ShowString(30,150,200,16,16,"KEY0:Send WK_UP:Mode");//��ʾ��ʾ��Ϣ		
  POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
	LCD_ShowString(30,170,200,16,16,"Count:");		  	//��ʾ��ǰ����ֵ	
	LCD_ShowString(30,190,200,16,16,"Send Data:");		//��ʾ���͵�����	
	LCD_ShowString(30,250,200,16,16,"Receive Data:");	//��ʾ���յ�������		
 			

	static int32 test_value = 0;                                                     //����ֵ
	uint32 timer_tick_last_update = 0;                                               //��һ�θ��µ�ʱ��
	qsize  size = 0;

	//����ʱ�ӽ���
	systicket_init();

	//��մ��ڽ��ջ�����
	queue_reset();
	//��ʱ�ȴ���������ʼ�����,����ȴ�300ms
	delay_ms(300);

	while(1) 
	{
		USART3_Receive_Data(my_comscreen_value.cmd_buffer,&size);
		if(size>0&&my_comscreen_value.cmd_buffer[1]!=0x07) 
		{                                            //���յ�ָ�� �����ж��Ƿ�Ϊ������ʾ
			ProcessMessage((PCTRL_MSG)my_comscreen_value.cmd_buffer, size);                             //ָ���
//						LCD_ShowxNum(30+i*32,230,((PCTRL_MSG)cmd_buffer)->control_type,3,16,0X80);	//��ʾ����
		} else if(size>0&&my_comscreen_value.cmd_buffer[1]==0x07) 
		{                                     //���Ϊָ��0x07��������STM32
			__disable_fault_irq();
			NVIC_SystemReset();
		}


		//    �ر�ע��
		//    MCU��ҪƵ���򴮿����������ݣ����򴮿������ڲ��������������Ӷ��������ݶ�ʧ(��������С����׼��8K��������4.7K)
		//    1) һ������£�����MCU�򴮿����������ݵ����ڴ���100ms���Ϳ��Ա������ݶ�ʧ�����⣻
		//    2) �����Ȼ�����ݶ�ʧ�����⣬���жϴ�������BUSY���ţ�Ϊ��ʱ���ܷ������ݸ���������

		//    TODO: ����û�����
		//    �����и���ʱ��־λ�����ı䣬��ʱ100����ˢ����Ļ
		if(my_comscreen_value.update_en&&my_comscreen_value.timer_tick_count-timer_tick_last_update>=TIME_100MS) 
		{
			my_comscreen_value.update_en = 0;
			timer_tick_last_update = my_comscreen_value.timer_tick_count;
			UpdateUI();
		}

		//����Ϊ����ʾ���㣬ÿ20�����Զ�����һ��
		//��һ���ж�10ms��timer_tick_countֵ+1,100*timer_tick_count = 1s
		if(my_comscreen_value.timer_tick_count%2==0) 
		{
			UpdateUI();
		}
//		uint8 cmd_type = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->cmd_type;                                                  //ָ������x
//		uint8 ctrl_msg = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->ctrl_msg;                                                  //��Ϣ������
		uint16 screen_id = PTR2U16(&((PCTRL_MSG)my_comscreen_value.cmd_buffer)->screen_id);                                     //����ID
		uint16 control_id = PTR2U16(&((PCTRL_MSG)my_comscreen_value.cmd_buffer)->control_id);                                   //�ؼ�ID
		uint8 control_type = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->control_type;                                          //�ؼ�����
		uint8 button_state = ((PCTRL_MSG)my_comscreen_value.cmd_buffer)->param[1];
		LCD_ShowxNum(30+i*32,230,button_state,3,16,0X80);
		if(screen_id==3 && control_id==31 && button_state && button_state==1) 
		{
			Set_4055_Switchoutput(ADDRESS_4055, 0xaa);
		}
		
		key=CAN1_Receive_Msg(canbuf);
		if(key)//���յ�������
		{			
			LCD_Fill(30,270,160,310,WHITE);//���֮ǰ����ʾ
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(30+i*32,270,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(30+(i-4)*32,290,canbuf[i],3,16,0X80);	//��ʾ����
 			}
		}
	}
}

void test_usart(void) {
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 usartbuf[14];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);   //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200

	LED_Init();					//��ʼ��LED
	LCD_Init();					//LCD��ʼ��
	USART2_Init(9600);		//��ʼ��usart����2
	USART3_Init(9600);		//��ʼ��usart����3
	POINT_COLOR=RED;//��������Ϊ��ɫ
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");
	LCD_ShowString(30,70,200,16,16,"RS485 TEST");
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/7");
	LCD_ShowString(30,130,200,16,16,"KEY0:Send");    	//��ʾ��ʾ��Ϣ

	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(30,150,200,16,16,"Count:");			  //��ʾ��ǰ����ֵ
	LCD_ShowString(30,170,200,16,16,"Send Data:");		//��ʾ���͵�����
	LCD_ShowString(30,210,200,16,16,"Receive Data:");	//��ʾ���յ�������

	while(1) {
		USART2_Receive_Data(usartbuf,&key);
		if(key) { //���յ�������
			if(key>14)key=14;//�����5������.
			for(i=0; i<key; i++)LCD_ShowxNum(30+i*32,230,usartbuf[i],3,16,0X80);	//��ʾ����
		}
		t++;
		delay_ms(10);
		if(t==20) {
			LED0=!LED0;//��ʾϵͳ��������
			t=0;
			cnt++;
			LCD_ShowxNum(30+48,150,cnt,3,16,0X80);	//��ʾ����
		}
	}
}


void finish_tmep() {
	////////////////////System Init//////////////////////////////
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);														//����ϵͳ�ж����ȼ�����2
	delay_init(168);    																											//��ʼ����ʱ����
	uart_init(115200);																												//��ʼ������		������Ϊ115200
	BEEP_Init();         																											//��ʼ��������
	My_RTC_Init();
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);						//��ʼ��RTC 		����WAKE UP�ж�,1�����ж�һ��
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);		//��ʼ��CAN			����ģʽ ������500Kbps
	TIM3_Int_Init(999,71);																										//��ʼ����ʱ��1ms

	////////////////////Lvgl Init//////////////////////////////
	FSMC_SRAM_Init();						//��ʼ���ⲿSRAM
	lvgl_init();								//��ʼ��LVGL

	////////////////////can Init//////////////////////////////
//	Init_3402(ADDRESS_3402);
//	delay_ms(100);										//��ʼ��3402ģ��
//	Init_4055(ADDRESS_4055);
//	delay_ms(100);										//��ʼ��4055ģ��
//	Init_5801(ADDRESS_5801_1, 0xff);
//	delay_ms(100);						//��ʼ��5801ģ��
//	Init_5801(ADDRESS_5801_2, 0x07);
//	delay_ms(100);
//	enable_TPDO(ADDRESS_5801_2, TPDO2, TPDOCOMMAND_NO);
//	enable_TPDO(ADDRESS_5801_2, TPDO3, TPDOCOMMAND_NO);
//	Init_7017(ADDRESS_7017);
//	delay_ms(100);										//��ʼ��7017ģ��
//	enable_TPDO(ADDRESS_7017, TPDO1, TPDOCOMMAND_YES);
//	enable_TPDO(ADDRESS_7017, TPDO2, TPDOCOMMAND_YES);

	////////////////////SD�� FATFS Init////////////////////////
	usmart_dev.init(84);				//��ʼ��USMART
	W25QXX_Init();							//��ʼ��W25Q128
	my_mem_init(SRAMIN);				//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMCCM);				//��ʼ��CCM�ڴ��
	if(SD_Init())								//��ʼ��SD��
		;//SD Card Error!
	else {
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
