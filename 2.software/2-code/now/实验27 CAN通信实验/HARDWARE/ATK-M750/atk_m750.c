#include "atk_m750.h"
#include "sys.h"
#include <string.h>
#include "translate.h"
#include "stdio.h"
#include "usart2.h"
#include "log.h"


void atkm_Init(void)
{
	atkm_USART_Init();
}
void atkm_USART_Init(void)
{
	USART2_Init(115200);
}
void send_atkm750_data(void)
{
	char DTUData[300]={0};
	Translate_AscllChar2DTUMsg(DTUData);
	USART2_Send_Data(DTUData, strlen(DTUData));
	success();
}

