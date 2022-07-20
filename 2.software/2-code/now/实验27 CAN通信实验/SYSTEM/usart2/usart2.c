#include "sys.h"		    
#include "usart2.h"	 
#include "delay.h" 
#include "string.h"
 
//���͡����ջ����� 	
#define SEND_BUF_SIZE_USART2 65536	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.
#define RECEIVE_BUF_SIZE_USART2 300//***********����2receiveû��Ҫ��ô�󣬲��ý���ȫ��atkģ����Թ���������****
uint8_t SendBuff_USART2[300];	//�������ݻ�����
uint8_t ReceiveBuff_USART2[300];	//�������ݻ�����

//��ʼ��IO ����2
//bound:������	  
void USART2_Init(uint32_t bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	USART_DeInit(USART2);  //��λ����2
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
  //����2���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3
		
	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate            = bound;//����������
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2

  NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;       //����2�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;	    //�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;			//IRQͨ��ʹ��
  NVIC_Init(&NVIC_InitStructure);							//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
    
  NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Stream5_IRQn; //Ƕ��ͨ��ΪDMA1_Stream5_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�Ϊ 2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2; //��Ӧ���ȼ�Ϊ 2
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE; //ͨ���ж�ʹ��
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Stream6_IRQn ;//����2�����ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;   //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE; //IRQͨ��ʹ��
  NVIC_Init(&NVIC_InitStructure);

  USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);  	//�������ڿ����ж�
  USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);  	// ��������DMA����
  USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);  	// ��������DMA����

  /* ���ô���DMA����*/
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);  					// ����DMAʱ��
		
  DMA_DeInit(DMA1_Stream5);                                       //��ʼ��DMA Stream
  DMA_InitStructure.DMA_Channel            = DMA_Channel_4; 							//ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;		//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)ReceiveBuff_USART2;		//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;   				//*****���赽�洢��ģʽ
  DMA_InitStructure.DMA_BufferSize         = RECEIVE_BUF_SIZE_USART2;						//���ݽ�����
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;		//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;					//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;			//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;							//ʹ����ͨģʽ
  DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;				    //�ߵ����ȼ�
  DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;                  //������FIFOģʽ
  DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;           //FIFO��ֵ
  DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;				//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;		//����ͻ�����δ���
  DMA_Init(DMA1_Stream5, &DMA_InitStructure);
  DMA_Cmd(DMA1_Stream5, ENABLE); //ʹ��DMA1_Stream5ͨ��

  DMA_DeInit(DMA1_Stream6);    //��ʼ��DMA Stream
  while (DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);//�ȴ�DMA������
  /* ����DMA1 Stream6��USART1���� */
  DMA_InitStructure.DMA_Channel            = DMA_Channel_4;               //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;            //DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr    = (u32)SendBuff_USART2;      //DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR                = DMA_DIR_MemoryToPeripheral;  //�洢��������ģʽ
  DMA_InitStructure.DMA_BufferSize         = SEND_BUF_SIZE_USART2;       //���ݴ�����
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;   //���������ģʽ
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;        //�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;     //�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;             //ʹ����ͨģʽ
  DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;         //�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_1QuarterFull;
  DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;      //�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;  //����ͻ�����δ���
  DMA_Init(DMA1_Stream6, &DMA_InitStructure);                             //��ʼ��DMA Stream7

  DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);							//DMA1_Stream6��������ж�
  DMA_Cmd(DMA1_Stream6, DISABLE);											//��ʹ��
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1
}


void USART2_Send_Data(char *buf,uint16_t len)
{
	memcpy(SendBuff_USART2,buf,len);				//�������ݵ�DMA���ͻ�����
	while (DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);	//ȷ��DMA���Ա�����
	DMA_SetCurrDataCounter(DMA1_Stream6,len);			//�����������ݴ��䳤��
	DMA_Cmd(DMA1_Stream6,ENABLE);						//��DMA����������ʼ����
}

//��������ж�
void DMA1_Stream6_IRQHandler(void)
{
	//�����־
	if(DMA_GetFlagStatus(DMA1_Stream6,DMA_FLAG_TCIF6)!=RESET)//�ȴ�DMA1_Stream6�������
	{
		DMA_ClearFlag(DMA1_Stream6,DMA_FLAG_TCIF6); //���DMA1_Stream6������ɱ�־
   	DMA_Cmd(DMA1_Stream6,DISABLE);				//�ر�ʹ��
    USART_ITConfig(USART2,USART_IT_TC,ENABLE);  //�򿪴��ڷ�������ж�
	}
}

//�����ж�
void USART2_IRQHandler(void)  												//����2�жϷ������
{
  if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET) 	//�����жϴ���
  {
   DMA_Cmd(DMA1_Stream5, DISABLE);  					   /* ��ʱ�ر�dma��������δ���� */
   DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);  		/* ��DMA��־λ */
   DMA_Cmd(DMA1_Stream5, ENABLE);      				/*��DMA*/
   USART_ReceiveData(USART2);   						//��������жϱ�־λ�����պ��������־λ�����ã�
  }
 if(USART_GetFlagStatus(USART2,USART_IT_TXE)==RESET)	//���ڷ������
 {
   USART_ITConfig(USART2,USART_IT_TC,DISABLE);
	}
}

