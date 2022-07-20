#include "sys.h"		    
#include "usart2.h"	 
#include "delay.h" 
#include "string.h"
 
//发送、接收缓存区 	
#define SEND_BUF_SIZE_USART2 65536	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.
#define RECEIVE_BUF_SIZE_USART2 300//***********串口2receive没必要这么大，不用接收全部atk模块回显过来的数据****
uint8_t SendBuff_USART2[300];	//发送数据缓冲区
uint8_t ReceiveBuff_USART2[300];	//接收数据缓冲区

//初始化IO 串口2
//bound:波特率	  
void USART2_Init(uint32_t bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	USART_DeInit(USART2);  //复位串口2
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	
  //串口2引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3
		
	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate            = bound;//波特率设置
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity              = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
  USART_Cmd(USART2, ENABLE);  //使能串口2

  NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;       //串口2中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;	    //子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;			//IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);							//根据指定的参数初始化VIC寄存器、
    
  NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Stream5_IRQn; //嵌套通道为DMA1_Stream5_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级为 2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2; //响应优先级为 2
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE; //通道中断使能
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Stream6_IRQn ;//串口2发送中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;   //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE; //IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);

  USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);  	//开启串口空闲中断
  USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);  	// 开启串口DMA发送
  USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);  	// 开启串口DMA接收

  /* 配置串口DMA接收*/
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  					// 开启DMA时钟
		
  DMA_DeInit(DMA1_Stream5);                                       //初始化DMA Stream
  DMA_InitStructure.DMA_Channel            = DMA_Channel_4; 							//通道选择
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;		//DMA外设地址
  DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)ReceiveBuff_USART2;		//DMA 存储器0地址
  DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;   				//*****外设到存储器模式
  DMA_InitStructure.DMA_BufferSize         = RECEIVE_BUF_SIZE_USART2;						//数据接收量
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;		//外设非增量模式
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;					//存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外设数据长度:8位
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;			//存储器数据长度:8位
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;							//使用普通模式
  DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;				    //高等优先级
  DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;                  //不开启FIFO模式
  DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;           //FIFO阈值
  DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;				//存储器突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;		//外设突发单次传输
  DMA_Init(DMA1_Stream5, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream5, ENABLE); //使能DMA1_Stream5通道

  DMA_DeInit(DMA1_Stream6);    //初始化DMA Stream
  while (DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);//等待DMA可配置
  /* 配置DMA1 Stream6，USART1发送 */
  DMA_InitStructure.DMA_Channel            = DMA_Channel_4;               //通道选择
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;            //DMA外设地址
  DMA_InitStructure.DMA_Memory0BaseAddr    = (u32)SendBuff_USART2;      //DMA 存储器0地址
  DMA_InitStructure.DMA_DIR                = DMA_DIR_MemoryToPeripheral;  //存储器到外设模式
  DMA_InitStructure.DMA_BufferSize         = SEND_BUF_SIZE_USART2;       //数据传输量
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;   //外设非增量模式
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;        //存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外设数据长度:8位
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;     //存储器数据长度:8位
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;             //使用普通模式
  DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;         //中等优先级
  DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_1QuarterFull;
  DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;      //存储器突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;  //外设突发单次传输
  DMA_Init(DMA1_Stream6, &DMA_InitStructure);                             //初始化DMA Stream7

  DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);							//DMA1_Stream6传输完成中断
  DMA_Cmd(DMA1_Stream6, DISABLE);											//不使能
  USART_Cmd(USART2, ENABLE);  //使能串口1
}


void USART2_Send_Data(char *buf,uint16_t len)
{
	memcpy(SendBuff_USART2,buf,len);				//复制数据到DMA发送缓存区
	while (DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);	//确保DMA可以被设置
	DMA_SetCurrDataCounter(DMA1_Stream6,len);			//重新设置数据传输长度
	DMA_Cmd(DMA1_Stream6,ENABLE);						//打开DMA数据流，开始发送
}

//发送完成中断
void DMA1_Stream6_IRQHandler(void)
{
	//清除标志
	if(DMA_GetFlagStatus(DMA1_Stream6,DMA_FLAG_TCIF6)!=RESET)//等待DMA1_Stream6传输完成
	{
		DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6); //清除DMA1_Stream6传输完成标志
   	DMA_Cmd(DMA1_Stream6,DISABLE);				//关闭使能
    USART_ITConfig(USART2,USART_IT_TC,ENABLE);  //打开串口发送完成中断
	}
}

//空闲中断
void USART2_IRQHandler(void)  												//串口2中断服务程序
{
  if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET) 	//空闲中断触发
  {
   DMA_Cmd(DMA1_Stream5, DISABLE);  					   /* 暂时关闭dma，数据尚未处理 */
   DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);  		/* 清DMA标志位 */
   DMA_Cmd(DMA1_Stream5, ENABLE);      				/*打开DMA*/
   USART_ReceiveData(USART2);   						//清除空闲中断标志位（接收函数有清标志位的作用）
  }
 if(USART_GetFlagStatus(USART2,USART_IT_TXE)==RESET)	//串口发送完成
 {
   USART_ITConfig(USART2,USART_IT_TC,DISABLE);
	}
}

