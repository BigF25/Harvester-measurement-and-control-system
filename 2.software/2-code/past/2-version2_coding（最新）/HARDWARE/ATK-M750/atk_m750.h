#ifndef __ATK_M750_H
#define __ATK_M750_H

#include "sys.h"

/**
 * ****************************************************************************
 * @file            dtu.c
 * @author          ����ԭ���Ŷӣ�ALIENTEK��
 * @version         V1.0
 * @data            2020-04-14
 * @brief           DTU��������
 * @copyright       Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 * ****************************************************************************
 * @attention       
 * 
 * ʵ��ƽ̨������ԭ��STM32F103������    +   ����ԭ��ATK-M750/ATK-M751��4G DTU��Ʒ��
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 * 
 * �޸�˵��
 * V1.0 20200414
 * ��һ�η���
 * ****************************************************************************
*/

/****************************************************************************/

#define DTU_RX_CMD_BUF_SIZE (512)

void send_atkm750_data();

typedef enum
{
    DTU_WORKMODE_NET = 0,  /*����͸��ģʽ*/
    DTU_WORKMODE_HTTP,     /*http͸��ģʽ*/
    DTU_WORKMODE_MQTT,     /*mqtt͸��ģʽ*/
    DTU_WORKMODE_ALIYUN,   /*������͸��ģʽ*/
    DTU_WORKMODE_ONENET,   /*OneNET͸��ģʽ*/
    DTU_WORKMODE_BAIDUYUN, /*�ٶ���͸��ģʽ*/
} _dtu_work_mode_eu;

typedef struct
{
    uint32_t timeout; /*ָ��ȴ���ʱʱ�䣬��λ��100ms*/
    char *read_cmd;   /*��ѯ����ָ��      ��ο�DTU AT�û��ֲ�˵��������д*/
    char *write_cmd;  /*���ò���ָ��      ��ο�DTU AT�û��ֲ�˵��������д*/
} _dtu_atcmd_st;

void dtu_get_urc_info(uint8_t ch);

void send_data_to_dtu(u8 *data, u8 len);

int dtu_config_init(_dtu_work_mode_eu work_mode);

#endif
