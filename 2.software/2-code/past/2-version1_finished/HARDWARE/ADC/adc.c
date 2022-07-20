#include "adc.h"
#include "delay.h"		 

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ���S�޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//#define SEND_BUF_SIZE 8200	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.
//u8 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����


volatile unsigned short m_ADCValue[ADC_SAMPLE_PNUM][ADC_SAMPLE_CNUM] = {0};

//��ʼ��ADC															   
void Adc_Init(void)
{    
  GPIO_InitTypeDef GPIO_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	//����RCCʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2, ENABLE);//ʹ��GPIOA��DMA2ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��

	//����GPIO�˿�
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
																GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//ѡ��PA0~PA7��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 
 
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
	
	//����DMA
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = (unsigned int)&(ADC1->DR);//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = (unsigned int)&m_ADCValue;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//���赽�洢��ģʽ
  DMA_InitStructure.DMA_BufferSize = ADC_SAMPLE_PNUM*ADC_SAMPLE_CNUM;;//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݳ���:16λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݳ���:16λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;       
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);//��ʼ��DMA Stream
  //˫����ģʽ����
	//DMA_DoubleBufferModeConfig(DMA2_Stream0,(uint32_t)(u16 *)(m_ADCValue1),DMA_Memory_0);    //DMA_Memory_0���ȱ�����
	//DMA_DoubleBufferModeCmd(DMA2_Stream0,ENABLE);	
	
	//����ADC
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;//���������׶�֮����ӳ�20��ʱ��
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʹ��
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
	
	//����ADC1
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//��ɨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//��������ת��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_ExternalTrigConv =  0;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = ADC_SAMPLE_CNUM;//1��ת���ڹ��������� Ҳ����ֻת����������1
  ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
	
	//ʹ��ADC1��DMA2
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);///////////
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
	
	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	

}				  

u16 ADC_Proc_Value(unsigned char nIndex)
{
	u32 nValue = 0;
	u32 nSum = 0;
	u8 i = 0, j = 0;
	u16 Temp = 0;	
	u16 tempArray[ADC_SAMPLE_PNUM] = {0};

	for	(i=0; i<ADC_SAMPLE_PNUM; i++)					//2��?��100����
	{
		tempArray[i] = m_ADCValue[i][nIndex];
//		printf("\t\t\t******ADCValue:%X\r\n",tempArray[i]);
	}
	for(i=0; i<ADC_SAMPLE_PNUM-1; i++)						//������?��?�䨮?��
	{
		for(j = i+1; j< ADC_SAMPLE_PNUM ;j++)
		{
			if(tempArray[j] < tempArray[i])
			{
				Temp = tempArray[i];
				tempArray[i] = tempArray[j];
				tempArray[j] = Temp;
			}
		}
	}	
	for(i=10; i<ADC_SAMPLE_PNUM-10; i++)						//��????��?��  debug
	{
		nSum += tempArray[i] ;
	}
	nValue = nSum / (ADC_SAMPLE_PNUM-20);//debug
	
	return nValue;
}


	 









