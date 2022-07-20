#ifndef __COMSCREEN_DRIVE_H
#define __COMSCREEN_DRIVE_H	
#include "sys.h"


#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long
#define int16    short int
#define int32    long
#define PTR2U16(PTR) ((((uint8 *)(PTR))[0]<<8)|((uint8 *)(PTR))[1])  //�ӻ�����ȡ16λ����
#define PTR2U32(PTR) ((((uint8 *)(PTR))[0]<<24)|(((uint8 *)(PTR))[1]<<16)|(((uint8 *)(PTR))[2]<<8)|((uint8 *)(PTR))[3])  //�ӻ�����ȡ32λ����

#define HEAD0 0xEE
#define HEAD1 0xB1
#define HEAD2 0x12
#define TAIL0 0xFF;
#define TAIL1 0xFC;
#define TAIL2 0xFF;
#define TAIL3 0xFF;
/*! 
*  \brief  	�������������ص�����
*/
typedef struct
{
    uint8   cmd_head;                    //֡ͷ
    uint8   cmd_type;                    //��������(UPDATE_CONTROL)    
    uint8   ctrl_msg;                    //CtrlMsgType-ָʾ��Ϣ������
    uint8   screen_id1;                  //������Ϣ�Ļ���ID
    uint8   screen_id2;                  //������Ϣ�Ļ���ID
    uint8   control_id1;                 //������Ϣ�Ŀؼ�ID
    uint8   control_id2;                 //������Ϣ�Ŀؼ�ID
    uint8   control_type;                //�ؼ�����
    uint8   param[256];                  //�ɱ䳤�Ȳ��������256���ֽ�
    uint8  	cmd_tail[4];                 //֡β
}CTRL_MSG,*PCTRL_MSG;

void COMscreen_USART_Init(void);
void COMscreen_Send_Data(u8 *buf, u8 len);


#endif 
