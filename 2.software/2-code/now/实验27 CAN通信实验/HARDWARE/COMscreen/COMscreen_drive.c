#include "COMscreen_drive.h"
#include "usart3.h"
/*! 
*  \brief  	�������Ĵ���ͨ�Žӿڳ�ʼ������
*  \param  	��
*  \return  ��
*/
void COMscreen_USART_Init(void)
{
	USART3_Init(115200);
}
/*! 
*  \brief  	�������Ĵ���ͨ�ŷ�����Ϣ�Ľӿں���
*  \param  	buf	��Ҫ���͵�ָ��
*  \param  	len	��Ҫ���͵�ָ���
*  \return  ��
*/
void COMscreen_Send_Data(u8 *buf,u8 len)
{
		USART3_Send_Data(buf,len);
}
///*! 
//*  \brief  	�������Ĵ���ͨ�Ž�����Ϣ�Ľӿں���
//*  \param  	buf	��Ҫ���͵�ָ��
//*  \param  	len	��Ҫ���͵�ָ���
//*  \return  ��
//*/
//void COMscreen_Rec_Data(u8 *buf,u8 *len)
//{
//		USART3_Receive_Data(buf,len);
//}
