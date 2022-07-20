#include "COMscreen.h"
#include "stdio.h"
#include "string.h"
#include "log.h"

#include "translate.h"
#include "COMscreen_drive.h"
#include "queue2.h"	   
#include "CANdevice.h"
#include "delay.h"


ComScreenMsg my_comscreen_msg;

/*! 
*  \brief  	��������ʼ��
*  \param  	��
*  \return  ��
*/
void COMscreen_Init(void)
{
	COMscreen_USART_Init();
	COMscreen_value_init();
}
/*! 
*  \brief  	��ʼ����������ر����ĳ�ֵ
*  \param  	��
*  \return  ��
*/
void COMscreen_value_init(void)
{
	my_comscreen_msg.scr_can_but_flag=0;
	my_comscreen_msg.scr_sd_but_flag=0;	
	my_comscreen_msg.sd_ready_flag=0;	
	my_comscreen_msg.scr_4055_motor1_but_ena_flag=0;
	my_comscreen_msg.scr_4055_motor1_but_dir_flag=0;	
	my_comscreen_msg.scr_4055_motor2_but_ena_flag=0;
	my_comscreen_msg.scr_4055_motor3_but_dir_flag=0;
	my_comscreen_msg.scr_4055_motor1_slider_value=1;
	my_comscreen_msg.scr_4055_motor2_slider_value=1;
}
/*! 
*  \brief  	�Ӷ�����ȡ��ָ��
*  					���ָ������ ʹ��MCU_Reaction_ReferToCmd()������Ӧִ�ж���
*  					ʹ��for����20��ѭ��������Ϊ�˷�ָֹ�������һֱ��������ѭ���޷�break�������
*  \param  	��
*  \return  ��
*/
void COMscreen_REV_Cmd(void)
{
	for(int i=0; i<20; i++)
	{
		extern queue2 *myqueue2;	
		static u8 cmd_buf[64];
		static int cmd_buf_p = 0;
		//��������ǿյ� ֱ�ӷ���
		if(get_queue2_length(myqueue2)==0) return;
//		queue2_print(myqueue2);////////////////////////////////////////////////////////////////////
		//������һ������
		cmd_buf[cmd_buf_p]= myqueue2->front->buf;
		delete_queue2(myqueue2);
		//�����⵽���ݰ�β��
		if(	cmd_buf_p>=11 &&	cmd_buf[cmd_buf_p-0] == 0xFF && 
													cmd_buf[cmd_buf_p-1] == 0xFF && 
													cmd_buf[cmd_buf_p-2] == 0xFC && 
													cmd_buf[cmd_buf_p-3] == 0xFF			)
		{
			//ȷ������������
			if(	cmd_buf[0] == 0xEE )
			{
//				printf("The cmd_buf is :");/////////////////////////////////////////////////////
//				for(int j = 0;j<=cmd_buf_p; j++)/////////////////////////////////////////////////////
//					printf("%2x ",cmd_buf[j]);///////////////////////////////////////////////////////////
//				printf("\r\n");////////////////////////////////////////////////////////////
				//������Ч ִ��ָ��ֽ⶯��
				MCU_Reaction_ReferToCmd(cmd_buf);
				cmd_buf_p = 0;
				break;
			}
		}
		//�����⵽���ݰ�ͷ
		else if(cmd_buf[cmd_buf_p]==0xEE)
		{
			cmd_buf_p = 0;
			cmd_buf[cmd_buf_p] = 0xEE;
		}
		cmd_buf_p++;
	}
}
/*! 
*  \brief  	�����������ص�ָ����ݲ�ͬ��ָ�������Ҫִ�в�ͬ�Ķ���
*  \param  	cmd_buffer ָ�������׵�ַ
*  \return  ��
*/
void MCU_Reaction_ReferToCmd(uint8* cmd_buffer)
{
	uint8 control_id = ((PCTRL_MSG)cmd_buffer)->control_id2;							//����ָ��Ŀؼ�id
//	printf("control_id:%d\n\r", control_id);
//	uint32 slider_4055_value = PTR2U32(((PCTRL_MSG)cmd_buffer)->param);		//����ָ���������Ϣ
	static uint32 slider1_value = 0;
	static uint32 slider2_value = 0;
	static uint8 button_state;
	switch(control_id)
	{
		//3402ģ�����ؿؼ�id
		case SCR_3402_SLIDER1_ID:				//��һ������ؼ�
			slider1_value = PTR2U32(((PCTRL_MSG)cmd_buffer)->param);//����ָ���������Ϣ
			Set_3402_Analogoutput(ADDRESS_3402, slider1_value, slider2_value);
			break;
		case SCR_3402_SLIDER2_ID:				//�ڶ�������ؼ�
			slider2_value = PTR2U32(((PCTRL_MSG)cmd_buffer)->param);//����ָ���������Ϣ
			Set_3402_Analogoutput(ADDRESS_3402, slider1_value, slider2_value);
			break;
		//4055ģ������id
		case SCR_4055_MOTOR1_BUT_DIR_ID://���1�ٶ�3�����򣩰�ť�ؼ�
			button_state = ((PCTRL_MSG)cmd_buffer)->param[1] ? 
											button_state&0xFD/*11111101*/ : button_state|0x02/*00000010*/;//����ָ���������Ϣ
			Set_4055_Switchoutput(ADDRESS_4055, button_state);
//			printf("hereDIR***********************************************\n\r");
			break;
//		case SCR_4055_MOTOR1_BUT_ENA_ID://���1�ٶ�2��ť�ؼ�
//			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen_msg.scr_4055_motor_can_send_msg);
//			break;
//		case SCR_4055_MOTOR1_BUT_ENA_ID://���1�ٶ�1��ť�ؼ�
//			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen_msg.scr_4055_motor_can_send_msg);
//			break;
		case SCR_4055_MOTOR1_BUT_ENA_ID://���1�ٶ�0��ť�ؼ�
			button_state = ((PCTRL_MSG)cmd_buffer)->param[1] ? 
											button_state&0xFE/*11111110*/ : button_state|0x01/*00000001*/;//����ָ���������Ϣ
			Set_4055_Switchoutput(ADDRESS_4055, button_state);
//			printf("hereENA***********************************************\n\r");
			break;
		case SCR_4055_MOTOR2_BUT_DIR_ID://���1�ٶ�3�����򣩰�ť�ؼ�
			button_state = ((PCTRL_MSG)cmd_buffer)->param[1] ? 
											button_state&0xDF/*11011111*/ : button_state|0x20/*00100000*/;//����ָ���������Ϣ
			Set_4055_Switchoutput(ADDRESS_4055, button_state);
			break;
//		case SCR_4055_MOTOR2_BUT_ENA_ID://���1�ٶ�2��ť�ؼ�
//			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen_msg.scr_4055_motor_can_send_msg);
//			break;
//		case SCR_4055_MOTOR2_BUT_DIR_ID://���1�ٶ�1��ť�ؼ�
//			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen_msg.scr_4055_motor_can_send_msg);
//			break;
		case SCR_4055_MOTOR2_BUT_ENA_ID:	//���1�ٶ�0��ť�ؼ�
			button_state = ((PCTRL_MSG)cmd_buffer)->param[1] ? 
											button_state&0xEF/*11101111*/ : button_state|0x10/*00010000*/;//����ָ���������Ϣ
			Set_4055_Switchoutput(ADDRESS_4055, button_state);
			break;
		
		//5801ģ�����ؿؼ�id
		case SCR_5801_1_CAN_BUT_ID:
			my_comscreen_msg.scr_can_but_flag = button_state;
			break;
		case SCR_5801_1_SD_BUT_ID:
			my_comscreen_msg.scr_sd_but_flag = button_state;
			break;

		//SD��ҳ�����ؿؼ�id
//		case SCR_SET_SD_BUT_ID:
//		{
//			u32 total,free;
//			if(SD_GetState() == SD_CARD_ERROR)
//			{
//				if(SD_Init())
//				{
//					my_comscreen_msg.sd_ready_flag = 0;
//					const u8 LEN = 64;
//					u8 comscreen_send_msg[LEN] = {0xEE,0xB1,0x10,0x00,0x07,0x00,0x02,0x53,0x44,0xBF,0xA8,0xB4,0xED,0xCE,0xF3,0xFF,0xFC,0xFF,0xFF };
//					my_USART_Send_Data(comscreen_send_msg,LEN);
//				}
//				else
//				{
//					exfuns_init();							//Ϊfatfs��ر��������ڴ�		
//					f_mount(fs[0],"0:",1); 					//����SD�� 
//					if(exf_getfree("0",&total,&free))//SD Card Fatfs Error!
//					{				
//						my_comscreen_msg.sd_ready_flag = 0;
//						const u8 LEN = 64;
//						u8 comscreen_send_msg[LEN] = {0xEE,0xB1,0x10,0x00,0x07,0x00,0x02,0x53,0x44,0xBF,0xA8,0xB4,0xED,0xCE,0xF3,0xFF,0xFC,0xFF,0xFF };
//						my_USART_Send_Data(comscreen_send_msg,LEN);
//					}
//					else
//						goto A;//SD Card Ready!
//				}
//			}
//			else
//			{
//				exf_getfree("0",&total,&free);
//				A:
//				total = total>>10;
//				free = free>>10;
//				my_comscreen_msg.sd_ready_flag = 1;
//				const u8 LEN = 64;
//				u8 comscreen_send_msg[LEN] = {0xEE,0xB1,0x10,0x00,0x07,0x00,0x02,0x53,0x44,0xBF,0xA8,0xD5,0xFD,0xB3,0xA3,0xFF,0xFC,0xFF,0xFF };
//				my_USART_Send_Data(comscreen_send_msg,LEN);
//			}
//			break;	
//		}
	}
	success();
}
/*! 
*  \brief  	��MCU����һ��ˢ��ָ�������
*  \param  	screenID ��Ļid
*  \return  ��
*/
void UpdateComScreen(u8 screenID)
{
	int len;
	u8 ComScreenCmd[200];
	len = Translate_AscllChar2ComScreenCMD(ComScreenCmd,screenID);
	COMscreen_Send_Data(ComScreenCmd,len+1);
}
/*! 
*  \brief  	���´�������������
*  \return  ��
*/
void UpdateComScreen_ALL(void)
{
	UpdateComScreen(SCR_5801_1_ID);
	UpdateComScreen(SCR_5801_2_ID);
	UpdateComScreen(SCR_5801_3_ID);
	UpdateComScreen(SCR_7017_1_ID);
	UpdateComScreen(SCR_7017_2_ID);
	success();
}
