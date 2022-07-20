#include "timer.h"
#include "mylvgl.h"
#include "beep.h"
#include "rtc.h"
#include "can.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		//��Ļ����
		lv_tick_inc(1);

		//������ť��beep
		if(my_lv_obj.btn_beep_sound_flag)
		{
			my_lv_obj.btn_beep_sound_time++;
			if(my_lv_obj.btn_beep_sound_time>50) 
			{
				my_lv_obj.btn_beep_sound_time = 0;
				BEEP_sound(0);
			}
		}	
		my_lv_obj.time_timer_count++;
//		static int count = 0;
//		if(my_lv_obj.time_timer_count % 60 == 0) {
//			count++;
//			if(count == 4) count = 0;
//		}
//		switch(count)
//		{
//			case 0:
//			case 1:
//				enable_TPDO(ADDRESS_5801_1, TPDO1, TPDOCOMMAND_YES);
//				enable_TPDO(ADDRESS_5801_1, TPDO2, TPDOCOMMAND_YES);
//				enable_TPDO(ADDRESS_5801_1, TPDO3, TPDOCOMMAND_YES);
//				enable_TPDO(ADDRESS_5801_1, TPDO4, TPDOCOMMAND_YES);
//				enable_TPDO(ADDRESS_5801_2, TPDO1, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_2, TPDO4, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_7017, TPDO1, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_7017, TPDO2, TPDOCOMMAND_NO);	
//				break;
//			case 2:
//				enable_TPDO(ADDRESS_5801_1, TPDO1, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_1, TPDO2, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_1, TPDO3, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_1, TPDO4, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_2, TPDO1, TPDOCOMMAND_YES);
//				enable_TPDO(ADDRESS_5801_2, TPDO4, TPDOCOMMAND_YES);
//				enable_TPDO(ADDRESS_7017, TPDO1, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_7017, TPDO2, TPDOCOMMAND_NO);
//				break;
//			case 3:
//				enable_TPDO(ADDRESS_5801_1, TPDO1, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_1, TPDO2, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_1, TPDO3, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_1, TPDO4, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_2, TPDO1, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_5801_2, TPDO4, TPDOCOMMAND_NO);
//				enable_TPDO(ADDRESS_7017, TPDO1, TPDOCOMMAND_YES);
//				enable_TPDO(ADDRESS_7017, TPDO2, TPDOCOMMAND_YES);
//				break;
//		}
		if(my_lv_obj.win_sys3_motor1_ena_switch_flag == WIN_SYS3_SWITCH_OPEN && my_lv_obj.time_timer_count % my_lv_obj.win_sys3_motor1_speed_slider_value == 0 )
		{
			static u8 flag = 0;
			if(flag == 0) 
				my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value & 0xFB;//11111011
			else if(flag == 1)
				my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value | 0x04;//00000100
			Set_4055_Switchoutput(ADDRESS_4055, my_lv_obj.win_sys3_motor_value);
			flag = !flag;
		}
		if(my_lv_obj.win_sys3_motor2_ena_switch_flag == WIN_SYS3_SWITCH_OPEN && my_lv_obj.time_timer_count % my_lv_obj.win_sys3_motor2_speed_slider_value == 0 )
		{
			static u8 flag = 0;
			if(flag == 0) 
				my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value & 0x7F;//01111111
			else if(flag == 1)
				my_lv_obj.win_sys3_motor_value = my_lv_obj.win_sys3_motor_value | 0x80;//10000000
			Set_4055_Switchoutput(ADDRESS_4055, my_lv_obj.win_sys3_motor_value);
			flag = !flag;
		}
		//�������
		if(my_lv_obj.time_timer_count == 10000) my_lv_obj.time_timer_count = 0;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
