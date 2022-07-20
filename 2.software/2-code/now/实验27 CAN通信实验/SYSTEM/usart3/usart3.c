#include "sys.h"		    
#include "usart3.h"	 
#include "string.h"
#include "stdio.h"
#include "queue.h"
#include "queue2.h"
   	  
//���͡����ջ����� 	
#define RECEIVE_BUF_SIZE_USART3 30
uint8_t ReceiveBuff_USART3[30];	//�������ݻ�����

//��ʼ��IO ����3
//bound:������	  
void USART3_Init(uint32_t bound)
{  	 
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 
	USART_DeInit(USART3);  //��λ����3
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
	
	//����2���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11 | GPIO_Pin_10; //GPIOB11��GPIOB10��ʼ��
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10
	
  //USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate            = bound;//������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	
	NVIC_InitStructure.NVIC_IRQChannel                   = USART3_IRQn;       //����3�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;	    //�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;			//IRQͨ��ʹ��
  NVIC_Init(&NVIC_InitStructure);							//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
    
  NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Stream1_IRQn; //Ƕ��ͨ��ΪDMA2_Stream1_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�Ϊ 2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2; //��Ӧ���ȼ�Ϊ 2
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE; //ͨ���ж�ʹ��
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Stream3_IRQn;//����3�����ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;   //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE; //IRQͨ��ʹ��
  NVIC_Init(&NVIC_InitStructure);

  USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);  	//�������ڿ����ж�
  USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);  	// ��������DMA����
  USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);  	// ��������DMA����

/* ���ô���DMA����*/
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  					// ����DMAʱ��
		
  DMA_DeInit(DMA1_Stream1);                                        //��ʼ��DMA Stream
  DMA_InitStructure.DMA_Channel            = DMA_Channel_4; 							//ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;		     //DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)ReceiveBuff_USART3;	//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;   //*****���赽�洢��ģʽ
  DMA_InitStructure.DMA_BufferSize         = RECEIVE_BUF_SIZE_USART3;			//���ݽ�����
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;		//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;				//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;			//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;							//ʹ����ͨģʽ
  DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;				//�ߵ����ȼ�
  DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;        //������FIFOģʽ
  DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;      //FIFO��ֵ
  DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;			//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;	//����ͻ�����δ���
  DMA_Init(DMA1_Stream1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream1, ENABLE); //ʹ��DMA1_Stream1ͨ��

  USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���1
}

//�����ж�
void USART3_IRQHandler(void)  												//����2�жϷ������
{
	if(USART_GetITStatus(USART3,USART_IT_IDLE)!=RESET) 	//�����жϴ���
	{
		DMA_Cmd(DMA1_Stream1, DISABLE);  					   /* ��ʱ�ر�dma��������δ���� */
		DMA_ClearFlag(DMA1_Stream1,DMA_FLAG_TCIF1);  		/* ��DMA��־λ */
		
		extern queue2 *myqueue2;
		for(uint8_t i=0; i<14; i++)
		{
			insert_queue2(myqueue2);
			myqueue2->rear->buf = ReceiveBuff_USART3[i];
		} 
		USART_ReceiveData(USART3);   						//��������жϱ�־λ�����պ��������־λ�����ã�
	}
	if(USART_GetFlagStatus(USART3,USART_IT_TXE)==RESET)	//���ڷ������
	{
		USART_ITConfig(USART3,USART_IT_TC,DISABLE);
	}
	DMA_Cmd(DMA1_Stream1, ENABLE);      				/*��DMA*/
}

//USART3����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����64���ֽ�)
void USART3_Send_Data(u8 *buf,u8 len)
{
	u8 t;
  	for(t=0;t<len;t++)		//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET){}; //�ȴ����ͽ���		
    USART_SendData(USART3,buf[t]); //��������
	}	 
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
}



