#ifndef __COMSCREEN_DRIVE_H
#define __COMSCREEN_DRIVE_H	
#include "sys.h"


#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long
#define int16    short int
#define int32    long
#define PTR2U16(PTR) ((((uint8 *)(PTR))[0]<<8)|((uint8 *)(PTR))[1])  //从缓冲区取16位数据
#define PTR2U32(PTR) ((((uint8 *)(PTR))[0]<<24)|(((uint8 *)(PTR))[1]<<16)|(((uint8 *)(PTR))[2]<<8)|((uint8 *)(PTR))[3])  //从缓冲区取32位数据

#define HEAD0 0xEE
#define HEAD1 0xB1
#define HEAD2 0x12
#define TAIL0 0xFF;
#define TAIL1 0xFC;
#define TAIL2 0xFF;
#define TAIL3 0xFF;
/*! 
*  \brief  	解析串口屏返回的命令
*/
typedef struct
{
    uint8   cmd_head;                    //帧头
    uint8   cmd_type;                    //命令类型(UPDATE_CONTROL)    
    uint8   ctrl_msg;                    //CtrlMsgType-指示消息的类型
    uint8   screen_id1;                  //产生消息的画面ID
    uint8   screen_id2;                  //产生消息的画面ID
    uint8   control_id1;                 //产生消息的控件ID
    uint8   control_id2;                 //产生消息的控件ID
    uint8   control_type;                //控件类型
    uint8   param[256];                  //可变长度参数，最多256个字节
    uint8  	cmd_tail[4];                 //帧尾
}CTRL_MSG,*PCTRL_MSG;

void COMscreen_USART_Init(void);
void COMscreen_Send_Data(u8 *buf, u8 len);


#endif 
