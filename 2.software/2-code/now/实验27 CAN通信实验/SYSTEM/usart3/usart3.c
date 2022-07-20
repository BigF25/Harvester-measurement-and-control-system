#include "sys.h"		    
#include "usart3.h"	 
#include "string.h"
#include "stdio.h"
#include "queue.h"
#include "queue2.h"
   	  
//发送、接收缓存区 	
#define RECEIVE_BUF_SIZE_USART3 30
uint8_t ReceiveBuff_USART3[30];	//接收数据缓冲区

//初始化IO 串口3
//bound:波特率	  
void USART3_Init(uint32_t bound)
{  	 
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 
	USART_DeInit(USART3);  //复位串口3
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
	
	//串口2引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11 | GPIO_Pin_10; //GPIOB11和GPIOB10初始化
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化GPIOB11，和GPIOB10
	
  //USART3 初始化设置
	USART_InitStructure.USART_BaudRate            = bound;//波特率一般设置为9600;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity              = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART3, &USART_InitStructure); //初始化串口3
	
	NVIC_InitStructure.NVIC_IRQChannel                   = USART3_IRQn;       //串口3中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;	    //子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;			//IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);							//根据指定的参数初始化VIC寄存器、
    
  NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Stream1_IRQn; //嵌套通道为DMA2_Stream1_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级为 2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2; //响应优先级为 2
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE; //通道中断使能
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Stream3_IRQn;//串口3发送中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;   //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE; //IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);

  USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);  	//开启串口空闲中断
  USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);  	// 开启串口DMA接收
  USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);  	// 开启串口DMA接收

/* 配置串口DMA接收*/
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  					// 开启DMA时钟
		
  DMA_DeInit(DMA1_Stream1);                                        //初始化DMA Stream
  DMA_InitStructure.DMA_Channel            = DMA_Channel_4; 							//通道选择
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;		     //DMA外设地址
  DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)ReceiveBuff_USART3;	//DMA 存储器0地址
  DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;   //*****外设到存储器模式
  DMA_InitStructure.DMA_BufferSize         = RECEIVE_BUF_SIZE_USART3;			//数据接收量
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;		//外设非增量模式
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;				//存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外设数据长度:8位
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;			//存储器数据长度:8位
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;							//使用普通模式
  DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;				//高等优先级
  DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;        //不开启FIFO模式
  DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;      //FIFO阈值
  DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;			//存储器突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;	//外设突发单次传输
  DMA_Init(DMA1_Stream1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream1, ENABLE); //使能DMA1_Stream1通道

  USART_Cmd(USART3, ENABLE);  //使能串口1
}

//空闲中断
void USART3_IRQHandler(void)  												//串口2中断服务程序
{
	if(USART_GetITStatus(USART3,USART_IT_IDLE)!=RESET) 	//空闲中断触发
	{
		DMA_Cmd(DMA1_Stream1, DISABLE);  					   /* 暂时关闭dma，数据尚未处理 */
		DMA_ClearFlag(DMA1_Stream1,DMA_FLAG_TCIF1);  		/* 清DMA标志位 */
		
		extern queue2 *myqueue2;
		for(uint8_t i=0; i<14; i++)
		{
			insert_queue2(myqueue2);
			myqueue2->rear->buf = ReceiveBuff_USART3[i];
		} 
		USART_ReceiveData(USART3);   						//清除空闲中断标志位（接收函数有清标志位的作用）
	}
	if(USART_GetFlagStatus(USART3,USART_IT_TXE)==RESET)	//串口发送完成
	{
		USART_ITConfig(USART3,USART_IT_TC,DISABLE);
	}
	DMA_Cmd(DMA1_Stream1, ENABLE);      				/*打开DMA*/
}

//USART3发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void USART3_Send_Data(u8 *buf,u8 len)
{
	u8 t;
  	for(t=0;t<len;t++)		//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET){}; //等待发送结束		
    USART_SendData(USART3,buf[t]); //发送数据
	}	 
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //等待发送结束		
}



