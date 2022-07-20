#include "COMscreen_drive.h"
#include "usart3.h"
/*! 
*  \brief  	串口屏的串口通信接口初始化函数
*  \param  	无
*  \return  无
*/
void COMscreen_USART_Init(void)
{
	USART3_Init(115200);
}
/*! 
*  \brief  	串口屏的串口通信发送信息的接口函数
*  \param  	buf	需要发送的指令
*  \param  	len	需要发送的指令长度
*  \return  无
*/
void COMscreen_Send_Data(u8 *buf,u8 len)
{
		USART3_Send_Data(buf,len);
}
///*! 
//*  \brief  	串口屏的串口通信接收信息的接口函数
//*  \param  	buf	需要发送的指令
//*  \param  	len	需要发送的指令长度
//*  \return  无
//*/
//void COMscreen_Rec_Data(u8 *buf,u8 *len)
//{
//		USART3_Receive_Data(buf,len);
//}
