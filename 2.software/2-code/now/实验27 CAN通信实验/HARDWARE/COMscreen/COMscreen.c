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
*  \brief  	串口屏初始化
*  \param  	无
*  \return  无
*/
void COMscreen_Init(void)
{
	COMscreen_USART_Init();
	COMscreen_value_init();
}
/*! 
*  \brief  	初始化串口屏相关变量的初值
*  \param  	无
*  \return  无
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
*  \brief  	从队列中取出指令
*  					如果指令完整 使用MCU_Reaction_ReferToCmd()做出对应执行动作
*  					使用for限制20次循环仅仅是为了防止指令发生错误，一直在里面死循环无法break的情况，
*  \param  	无
*  \return  无
*/
void COMscreen_REV_Cmd(void)
{
	for(int i=0; i<20; i++)
	{
		extern queue2 *myqueue2;	
		static u8 cmd_buf[64];
		static int cmd_buf_p = 0;
		//如果队列是空的 直接返回
		if(get_queue2_length(myqueue2)==0) return;
//		queue2_print(myqueue2);////////////////////////////////////////////////////////////////////
		//读进来一个数据
		cmd_buf[cmd_buf_p]= myqueue2->front->buf;
		delete_queue2(myqueue2);
		//如果检测到数据包尾巴
		if(	cmd_buf_p>=11 &&	cmd_buf[cmd_buf_p-0] == 0xFF && 
													cmd_buf[cmd_buf_p-1] == 0xFF && 
													cmd_buf[cmd_buf_p-2] == 0xFC && 
													cmd_buf[cmd_buf_p-3] == 0xFF			)
		{
			//确认数据完整性
			if(	cmd_buf[0] == 0xEE )
			{
//				printf("The cmd_buf is :");/////////////////////////////////////////////////////
//				for(int j = 0;j<=cmd_buf_p; j++)/////////////////////////////////////////////////////
//					printf("%2x ",cmd_buf[j]);///////////////////////////////////////////////////////////
//				printf("\r\n");////////////////////////////////////////////////////////////
				//数据有效 执行指令分解动作
				MCU_Reaction_ReferToCmd(cmd_buf);
				cmd_buf_p = 0;
				break;
			}
		}
		//如果检测到数据包头
		else if(cmd_buf[cmd_buf_p]==0xEE)
		{
			cmd_buf_p = 0;
			cmd_buf[cmd_buf_p] = 0xEE;
		}
		cmd_buf_p++;
	}
}
/*! 
*  \brief  	处理串口屏返回的指令，依据不同的指令，主控需要执行不同的动作
*  \param  	cmd_buffer 指令数组首地址
*  \return  无
*/
void MCU_Reaction_ReferToCmd(uint8* cmd_buffer)
{
	uint8 control_id = ((PCTRL_MSG)cmd_buffer)->control_id2;							//解析指令的控件id
//	printf("control_id:%d\n\r", control_id);
//	uint32 slider_4055_value = PTR2U32(((PCTRL_MSG)cmd_buffer)->param);		//解析指令的数据信息
	static uint32 slider1_value = 0;
	static uint32 slider2_value = 0;
	static uint8 button_state;
	switch(control_id)
	{
		//3402模块的相关控件id
		case SCR_3402_SLIDER1_ID:				//第一个滑块控件
			slider1_value = PTR2U32(((PCTRL_MSG)cmd_buffer)->param);//解析指令的数据信息
			Set_3402_Analogoutput(ADDRESS_3402, slider1_value, slider2_value);
			break;
		case SCR_3402_SLIDER2_ID:				//第二个滑块控件
			slider2_value = PTR2U32(((PCTRL_MSG)cmd_buffer)->param);//解析指令的数据信息
			Set_3402_Analogoutput(ADDRESS_3402, slider1_value, slider2_value);
			break;
		//4055模块的相关id
		case SCR_4055_MOTOR1_BUT_DIR_ID://电机1速度3（方向）按钮控件
			button_state = ((PCTRL_MSG)cmd_buffer)->param[1] ? 
											button_state&0xFD/*11111101*/ : button_state|0x02/*00000010*/;//解析指令的数据信息
			Set_4055_Switchoutput(ADDRESS_4055, button_state);
//			printf("hereDIR***********************************************\n\r");
			break;
//		case SCR_4055_MOTOR1_BUT_ENA_ID://电机1速度2按钮控件
//			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen_msg.scr_4055_motor_can_send_msg);
//			break;
//		case SCR_4055_MOTOR1_BUT_ENA_ID://电机1速度1按钮控件
//			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen_msg.scr_4055_motor_can_send_msg);
//			break;
		case SCR_4055_MOTOR1_BUT_ENA_ID://电机1速度0按钮控件
			button_state = ((PCTRL_MSG)cmd_buffer)->param[1] ? 
											button_state&0xFE/*11111110*/ : button_state|0x01/*00000001*/;//解析指令的数据信息
			Set_4055_Switchoutput(ADDRESS_4055, button_state);
//			printf("hereENA***********************************************\n\r");
			break;
		case SCR_4055_MOTOR2_BUT_DIR_ID://电机1速度3（方向）按钮控件
			button_state = ((PCTRL_MSG)cmd_buffer)->param[1] ? 
											button_state&0xDF/*11011111*/ : button_state|0x20/*00100000*/;//解析指令的数据信息
			Set_4055_Switchoutput(ADDRESS_4055, button_state);
			break;
//		case SCR_4055_MOTOR2_BUT_ENA_ID://电机1速度2按钮控件
//			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen_msg.scr_4055_motor_can_send_msg);
//			break;
//		case SCR_4055_MOTOR2_BUT_DIR_ID://电机1速度1按钮控件
//			Set_4055_Switchoutput(ADDRESS_4055, my_comscreen_msg.scr_4055_motor_can_send_msg);
//			break;
		case SCR_4055_MOTOR2_BUT_ENA_ID:	//电机1速度0按钮控件
			button_state = ((PCTRL_MSG)cmd_buffer)->param[1] ? 
											button_state&0xEF/*11101111*/ : button_state|0x10/*00010000*/;//解析指令的数据信息
			Set_4055_Switchoutput(ADDRESS_4055, button_state);
			break;
		
		//5801模块的相关控件id
		case SCR_5801_1_CAN_BUT_ID:
			my_comscreen_msg.scr_can_but_flag = button_state;
			break;
		case SCR_5801_1_SD_BUT_ID:
			my_comscreen_msg.scr_sd_but_flag = button_state;
			break;

		//SD卡页面的相关控件id
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
//					exfuns_init();							//为fatfs相关变量申请内存		
//					f_mount(fs[0],"0:",1); 					//挂载SD卡 
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
*  \brief  	从MCU发送一条刷新指令到串口屏
*  \param  	screenID 屏幕id
*  \return  无
*/
void UpdateComScreen(u8 screenID)
{
	int len;
	u8 ComScreenCmd[200];
	len = Translate_AscllChar2ComScreenCMD(ComScreenCmd,screenID);
	COMscreen_Send_Data(ComScreenCmd,len+1);
}
/*! 
*  \brief  	更新串口屏所有数据
*  \return  无
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
