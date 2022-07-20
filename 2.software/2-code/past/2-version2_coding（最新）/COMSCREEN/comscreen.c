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
					exfuns_init();							//Ϊfatfs��ر��������ڴ�		
					f_mount(fs[0],"0:",1); 					//����SD�� 
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
	my_comscreen_value.timer_tick_count = 0;                                               //��ʱ������
	my_comscreen_value.current_screen_id = 0;                                                 //��ǰ����ID
	my_comscreen_value.progress_value = 0;                                                     //����������ֵ
	my_comscreen_value.test_value = 0;                                                         //����ֵ
	my_comscreen_value.update_en = 0;                                                          //���±��
	my_comscreen_value.meter_flag = 0;                                                         //�Ǳ�ָ��������־λ
	my_comscreen_value.num = 0;                                                                //���߲��������
	my_comscreen_value.sec = 1;                                                                  //ʱ����
	my_comscreen_value.curves_type = 0;                                                        //���߱�־λ  0Ϊ���Ҳ���1Ϊ��ݲ�
	my_comscreen_value.second_flag=0;                                                          //ʱ���־λ
	my_comscreen_value.icon_flag = 0;                                                          //ͼ���־λ
	my_comscreen_value.Progress_Value = 0;                                                     //��������ֵ
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
*  \brief  ��Ϣ��������
*  \param msg ��������Ϣ
*  \param size ��Ϣ����
*/
void ProcessMessage( PCTRL_MSG msg, uint16 size ) 
{
	uint8 cmd_type = msg->cmd_type;                                                  //ָ������
	uint8 ctrl_msg = msg->ctrl_msg;                                                  //��Ϣ������
	uint8 control_type = msg->control_type;                                          //�ؼ�����
	uint16 screen_id = PTR2U16(&msg->screen_id);                                     //����ID
	uint16 control_id = PTR2U16(&msg->control_id);                                   //�ؼ�ID
	uint32 value = PTR2U32(msg->param);                                              //��ֵ


	switch(cmd_type) 
	{
		case NOTIFY_TOUCH_PRESS:                                                        //����������
		case NOTIFY_TOUCH_RELEASE:                                                      //�������ɿ�
			NotifyTouchXY(my_comscreen_value.cmd_buffer[1],PTR2U16(my_comscreen_value.cmd_buffer+2),PTR2U16(my_comscreen_value.cmd_buffer+4));
			break;
		case NOTIFY_WRITE_FLASH_OK:                                                     //дFLASH�ɹ�
			NotifyWriteFlash(1);
			break;
		case NOTIFY_WRITE_FLASH_FAILD:                                                  //дFLASHʧ��
			NotifyWriteFlash(0);
			break;
		case NOTIFY_READ_FLASH_OK:                                                      //��ȡFLASH�ɹ�
			NotifyReadFlash(1,my_comscreen_value.cmd_buffer+2,size-6);                                     //ȥ��֡ͷ֡β
			break;
		case NOTIFY_READ_FLASH_FAILD:                                                   //��ȡFLASHʧ��
			NotifyReadFlash(0,0,0);
			break;
		case NOTIFY_READ_RTC:                                                           //��ȡRTCʱ��
			NotifyReadRTC(my_comscreen_value.cmd_buffer[2],my_comscreen_value.cmd_buffer[3],my_comscreen_value.cmd_buffer[4],my_comscreen_value.cmd_buffer[5],my_comscreen_value.cmd_buffer[6],my_comscreen_value.cmd_buffer[7],my_comscreen_value.cmd_buffer[8]);
			break;
		case NOTIFY_CONTROL: {
			if(ctrl_msg==MSG_GET_CURRENT_SCREEN) {                                  //����ID�仯֪ͨ
				NotifyScreen(screen_id);                                            //�����л������ĺ���
			} else {
				switch(control_type) {
					case kCtrlButton:                                                   //��ť�ؼ�
						NotifyButton(screen_id,control_id,msg->param[1]);
						break;
					case kCtrlText:                                                     //�ı��ؼ�
						NotifyText(screen_id,control_id,msg->param);
						break;
					case kCtrlProgress:                                                 //�������ؼ�
						NotifyProgress(screen_id,control_id,value);
						break;
					case kCtrlSlider:                                                   //�������ؼ�
						NotifySlider(screen_id,control_id,value);
						break;
					case kCtrlMeter:                                                    //�Ǳ�ؼ�
						NotifyMeter(screen_id,control_id,value);
						break;
					case kCtrlMenu:                                                     //�˵��ؼ�
						NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);
						break;
					case kCtrlSelector:                                                 //ѡ��ؼ�
						NotifySelector(screen_id,control_id,msg->param[0]);
						break;
					case kCtrlRTC:                                                      //����ʱ�ؼ�
						NotifyTimer(screen_id,control_id);
						break;
					default:
						break;
				}
			}
			break;
		}
		case NOTIFY_HandShake:                                                          //����֪ͨ
			NOTIFYHandShake();
			break;
		default:
			break;
	}
}
/*!
*  \brief  ����֪ͨ
*/
void NOTIFYHandShake(void) 
{
	SetButtonValue(3,2,1);
}

/*!
*  \brief  �����л�֪ͨ
*  \details  ��ǰ����ı�ʱ(�����GetScreen)��ִ�д˺���
*  \param screen_id ��ǰ����ID
*/
void NotifyScreen(uint16 screen_id) 
{
	//TODO: ����û�����
	my_comscreen_value.current_screen_id = screen_id;                                                   //�ڹ��������п��������л�֪ͨ����¼��ǰ����ID

	//��������3����һ����ť
	if(screen_id == 3) {
		SetButtonValue(3,1,1);
	}
	//���������Զ�����GIF
	if(my_comscreen_value.current_screen_id == 9) {
		AnimationStart(9,1);                                                         //������ʼ����
	}
	//���������������ȡ��ǰ�ı�ֵ
	if(my_comscreen_value.current_screen_id==5) {
		GetControlValue(5,1);
	}
	//������ά��ҳ�����ɶ�ά��
	if(my_comscreen_value.current_screen_id==14) {
		//��ά��ؼ���ʾ�����ַ�ʱ����Ҫת��ΪUTF8���룬
		//ͨ����ָ�����֡���ת����www.gz-dc.com�� ���õ��ַ�����������
		uint8 dat[] = {0x77,0x77,0x77,0x2E,0x67,0x7A,0x2D,0x64,0x63,0x2E,0x63,0x6F,0x6D};
		SetTextValue(14,1,dat);                                                      //���Ͷ�ά���ַ�����
	}

	//���ݼ�¼��ʾ
	if(my_comscreen_value.current_screen_id == 15) {
		Record_SetEvent(15,1,0,0);
		Record_SetEvent(15,1,1,0);
		Record_SetEvent(15,1,2,0);
		Record_SetEvent(15,1,3,0);
		Record_SetEvent(15,1,4,0);
		Record_SetEvent(15,1,5,0);
		Record_SetEvent(15,1,6,0);
		Record_SetEvent(15,1,7,0);
		delay_ms(2000);                                                              //��ʱ����
		Record_ResetEvent(15,1,0,0);
		Record_ResetEvent(15,1,1,0);
		Record_ResetEvent(15,1,2,0);

	}

}

/*!
*  \brief  ���������¼���Ӧ
*  \param press 1���´�������3�ɿ�������
*  \param x x����
*  \param y y����
*/
void NotifyTouchXY(uint8 press,uint16 x,uint16 y) 
{
	//TODO: ����û�����
}


/*!
*  \brief  ��������
*  ע�⣺��������û��RTC ���ȿ��¹��̻���ID����Ӧ�����ܻ���ı������������ˢ�µ�һ��
*/
void UpdateUI(void) 
{
	/**************** �ı����棬������4   **********************/
	//�ı����ú���ʾ  ��ʱ20msˢ��һ��
	if(my_comscreen_value.current_screen_id==4) {
		//��ǰ�������¶ȴ�0��1000ѭ����ʾ�������ִ�0-999ѭ����ʾ
		SetTextInt32(4,6,my_comscreen_value.test_value%1000,0,1);                                      //��ǰ����
		SetTextInt32(4,7,my_comscreen_value.test_value%1000,0,1);                                      //������
		SetTextValue(4,1,"����10");                                                 //�����ı�ֵ

		my_comscreen_value.test_value++;
		if(my_comscreen_value.test_value >= 1000) {
			my_comscreen_value.test_value = 0;
		}
		if(my_comscreen_value.test_value>0&&my_comscreen_value.test_value<500) {                                           //����0С��500�ı���ʾ��ɫ
			SetControlBackColor(4,6,0xF800);                                         //�����ı�����ɫ
		} else if(my_comscreen_value.test_value>=500) {                                                 //����500�ı�����ɫ
			SetControlBackColor(4,6,0x001F);                                         //�����ı�����ɫ
		}
	}
	/**************** �Ǳ��棬������6   **********************/
	//�Ǳ�ؼ�   ��ʱ20msˢ��һ��
	if(my_comscreen_value.current_screen_id == 6) {
		if(my_comscreen_value.meter_flag == 0) {                                                        //��־λ 0˳ʱ�� ��1��ʱ��
			//˳ʱ����ת
			SetMeterValue(6,1,my_comscreen_value.test_value);                                           //����ͼƬָ����ת�Ƕ�
			my_comscreen_value.test_value +=1;                                                          //ָ����ת��0�ȵ�260��
			if(my_comscreen_value.test_value >= 260) {
				my_comscreen_value.test_value = 260;
				my_comscreen_value.meter_flag = 1;
			}
		} else if(my_comscreen_value.meter_flag == 1) {
			//��ʱ����ת
			Set_picMeterValue(6,1,my_comscreen_value.test_value);                                       //����ͼƬָ����ת�Ƕ�
			my_comscreen_value.test_value -=1;                                                          //ָ����ת��260�ȵ�0��
			if(my_comscreen_value.test_value <= 0) {
				my_comscreen_value.test_value = 0;
				my_comscreen_value.meter_flag = 0;
			}
		}
	}
	/**************** ͼ�껭�棬������10   **********************/
	//ͼ��1s������ʾ
	if(my_comscreen_value.current_screen_id == 10) {
		if(my_comscreen_value.timer_tick_count %100 == 0 && my_comscreen_value.icon_flag == 0) {
			SetButtonValue(10,5,0);
			SetButtonValue(10,2,1);                                                      //������ͼ��
			AnimationPlayFrame(10,1,0);
			my_comscreen_value.icon_flag = 1 ;
		} else if(my_comscreen_value.timer_tick_count %100 == 0 && my_comscreen_value.icon_flag == 1) {
			SetButtonValue(10,2,0);
			SetButtonValue(10,3,1);                                                      //��ͣ��ͼ��
			AnimationPlayFrame(10,1,1);
			my_comscreen_value.icon_flag = 2;
		} else if(my_comscreen_value.timer_tick_count %100 == 0 && my_comscreen_value.icon_flag == 2) {
			SetButtonValue(10,3,0);
			SetButtonValue(10,4,1);                                                      //ֹͣͼ��
			AnimationPlayFrame(10,1,2);
			my_comscreen_value.icon_flag = 3 ;
		} else if(my_comscreen_value.timer_tick_count %100 == 0 && my_comscreen_value.icon_flag == 3) {
			SetButtonValue(10,4,0);
			SetButtonValue(10,5,1);                                                      //����ͼ��
			AnimationPlayFrame(10,1,3);
			my_comscreen_value.icon_flag  = 0 ;
		}
	}

	/**************** ���߻��棬������11   **********************/
	//ʵʱ���ߣ����Ҳ����顣  ��ʱ20ms��������
	if(my_comscreen_value.current_screen_id == 11) {
		if(my_comscreen_value.curves_type == 0) {
			//��������
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

			GraphChannelDataAdd(11,1,0,&sin[my_comscreen_value.num],2);                                    //������ݵ�����  һ����������

			my_comscreen_value.num += 2;
			if(my_comscreen_value.num >= 255) {
				my_comscreen_value.num =0;
			}
		} else if(my_comscreen_value.curves_type == 1) {
			//��ݲ�����
			uint8 sawtooth[180] = {0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252
			                      };


			GraphChannelDataAdd(11,1,0,&sawtooth[my_comscreen_value.num],2);                              //������ݵ�����  һ����������
			my_comscreen_value.num +=2 ;
			if(my_comscreen_value.num >= 180) {
				my_comscreen_value.num =0;
			}
		}
	}
	/**************** ��ʱ���߻��棬������16   **********************/
	//��ʱ���ߣ����Ҳ�����
	if(my_comscreen_value.current_screen_id == 16 && my_comscreen_value.timer_tick_count %100 == 0) {                         //��ʷ���߿ؼ���������1sһ���㡣//һ������������
		if(my_comscreen_value.curves_type == 0) {
			//��������
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

			HistoryGraph_SetValueInt8(16,1,&sin[my_comscreen_value.num],1);                               //�����ʷ��������
			my_comscreen_value.num++;
			if(my_comscreen_value.num >= 255) {
				my_comscreen_value.num =0;
			}
		} else if(my_comscreen_value.curves_type == 1) {
			//��ݲ�����
			uint8 sawtooth[180] = {0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
			                       0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252
			                      };

			HistoryGraph_SetValueInt8(16,1,&sawtooth[my_comscreen_value.num],1);                          //�����ʷ��������
			my_comscreen_value.num++;
			if(my_comscreen_value.num >= 90) {
				my_comscreen_value.num =0;
			}
		}


	}

}


/*!
*  \brief  ��ť�ؼ�֪ͨ
*  \details  ����ť״̬�ı�(�����GetControlValue)ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param state ��ť״̬��0����1����
*/
void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state) 
{
	//�����������߲���
	if(screen_id == 11) {
		if(control_id==2) {                                                          //���Ҳ��ؼ�
			my_comscreen_value.curves_type = 0;
		} else if(control_id==3) {                                                   //��ݲ��ؼ�
			my_comscreen_value.curves_type = 1;
		}
	}
	//ʱ�仭�水ť��ȡRTCʱ��
	if(screen_id == 8) {
		if(control_id==8 && state == 1) {                                            //��ȡʱ��
			ReadRTC();
		}
	}
	//ѡ��ؼ���ʾʱ���
	if(screen_id == 13 && control_id==4) {
		if(my_comscreen_value.Select_H>=0&&my_comscreen_value.Select_H<=6) {                                                     //0~6Сʱ���賿
			SetSelectorValue(13,3,0);                                                       //����ѡ��ؼ�ѡ��
		}

		else if(my_comscreen_value.Select_H>=7&&my_comscreen_value.Select_H<=12) {                                                //7~12Сʱ������
			SetSelectorValue(13,3,1);
		}

		else if(my_comscreen_value.Select_H>=13&&my_comscreen_value.Select_H<=18) {                                               //13~18Сʱ������
			SetSelectorValue(13,3,2);
		}

		else if(my_comscreen_value.Select_H>18&&my_comscreen_value.Select_H<=23) {                                                //19~23Сʱ����ҹ
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
		if(control_id==3) {                                                          //�ݼ�
			my_comscreen_value.Progress_Value -= 1;
			if(my_comscreen_value.Progress_Value <= 0) {
				my_comscreen_value.Progress_Value = 0;
			}
			SetProgressValue(5,1,my_comscreen_value.Progress_Value);                                    //���ý�������ֵ
			SetTextInt32(5,2,my_comscreen_value.Progress_Value,0,1);                                    //�����ı����ֵ
		} else if(control_id==4) {                                                   //�ݼ�
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
*  \brief  �ı��ؼ�֪ͨ
*  \details  ���ı�ͨ�����̸���(�����GetControlValue)ʱ��ִ�д˺���
*  \details  �ı��ؼ����������ַ�����ʽ�·���MCU������ı��ؼ������Ǹ���ֵ��
*  \details  ����Ҫ�ڴ˺����н��·��ַ�������ת�ظ���ֵ��
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param str �ı��ؼ�����
*/
void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str) 
{
	if(screen_id==4) {                                                               //����ID2���ı����ú���ʾ
		int32 value=0;
		sscanf(str,"%ld",&value);                                                    //���ַ���ת��Ϊ����
		if(control_id==2) {                                                          //��ߵ�ѹ
			//�޶���ֵ��Χ��Ҳ�������ı��ؼ����������ã�
			if(value<0) {
				value = 0;
			} else if(value>380) {
				value = 380;
			}
			SetTextInt32(4,2,value,0,1);                                             //������ߵ�ѹ
			SetTextInt32(4,5,value/2,1,1);                                           //������ߵ�ѹ/2
		}
	}
}

/*!
*  \brief  �������ؼ�֪ͨ
*  \details  ����GetControlValueʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param value ֵ
*/
void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value) 
{
	if(screen_id == 5) {
		my_comscreen_value.Progress_Value = value;
		SetTextInt32(5,2,my_comscreen_value.Progress_Value,0,1);                                        //�����ı����ֵ
	}
}

/*!
*  \brief  �������ؼ�֪ͨ
*  \details  ���������ı�(�����GetControlValue)ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param value ֵ
*/
void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value) 
{
	uchar back[1] = {0};
	if(screen_id==7&&control_id==2) {                                                //�������
		if(value<100||value>0) {
			SetProgressValue(7,1,value);                                             //���½�������ֵ
			SetTextInt32(7,3,value,0,1);
			sprintf(back,"%c",(255-value*2));                                        //���ñ������� ����ֵ��Χ 0~255��0������255�
			SetBackLight(back[0]);
		}
	}
	if(screen_id==7&&control_id==5) {                                                //�������
		if(value<100||value>0) {
			SetProgressValue(7,4,value);                                             //���½�������ֵ
			SetTextInt32(7,6,value,0,1);
		}
	}
}

/*!
*  \brief  �Ǳ�ؼ�֪ͨ
*  \details  ����GetControlValueʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param value ֵ
*/
void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value) 
{
	//TODO: ����û�����
}

/*!
*  \brief  �˵��ؼ�֪ͨ
*  \details  ���˵���»��ɿ�ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param item �˵�������
*  \param state ��ť״̬��0�ɿ���1����
*/
void NotifyMenu(uint16 screen_id, uint16 control_id, uint8 item, uint8 state) 
{
	//TODO: ����û�����
}

/*!
*  \brief  ѡ��ؼ�֪ͨ
*  \details  ��ѡ��ؼ��仯ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param item ��ǰѡ��
*/
void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item) 
{
	if(screen_id == 13&&control_id == 1) {                              //��ȡ��ǰѡ��ؼ���ֵ
		my_comscreen_value.Select_H =  item;
	}
	if(screen_id == 13&&control_id == 2) {                              //��ȡ��ǰѡ��ؼ���ֵ
		my_comscreen_value.Select_M =  item;
	}

}

/*!
*  \brief  ��ʱ����ʱ֪ͨ����
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*/
void NotifyTimer(uint16 screen_id, uint16 control_id) 
{
	if(screen_id==8&&control_id == 7) {
		SetBuzzer(100);
	}
}

/*!
*  \brief  ��ȡ�û�FLASH״̬����
*  \param status 0ʧ�ܣ�1�ɹ�
*  \param _data ��������
*  \param length ���ݳ���
*/
void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length) 
{
	//TODO: ����û�����
}

/*!
*  \brief  д�û�FLASH״̬����
*  \param status 0ʧ�ܣ�1�ɹ�
*/
void NotifyWriteFlash(uint8 status) 
{
	//TODO: ����û�����
}

/*!
*  \brief  ��ȡRTCʱ�䣬ע�ⷵ�ص���BCD��
*  \param year �꣨BCD��
*  \param month �£�BCD��
*  \param week ���ڣ�BCD��
*  \param day �գ�BCD��
*  \param hour ʱ��BCD��
*  \param minute �֣�BCD��
*  \param second �루BCD��
*/
void NotifyReadRTC(uint8 year,uint8 month,uint8 week,uint8 day,uint8 hour,uint8 minute,uint8 second) 
{
	int years,months,weeks,days,hours,minutes;

	my_comscreen_value.sec    =(0xff & (second>>4))*10 +(0xf & second);                                    //BCD��תʮ����
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
		SetTextValue(8,7,"������");
	} else if(weeks == 1) {
		SetTextValue(8,7,"����һ");
	} else if(weeks == 2) {
		SetTextValue(8,7,"���ڶ�");
	} else if(weeks == 3) {
		SetTextValue(8,7,"������");
	} else if(weeks == 4) {
		SetTextValue(8,7,"������");
	} else if(weeks == 5) {
		SetTextValue(8,7,"������");
	} else if(weeks == 6) {
		SetTextValue(8,7,"������");
	}
}
