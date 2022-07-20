#include "adc.h"
#include "delay.h"		 

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ADC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有S限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//#define SEND_BUF_SIZE 8200	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.
//u8 SendBuff[SEND_BUF_SIZE];	//发送数据缓冲区


volatile unsigned short m_ADCValue[ADC_SAMPLE_PNUM][ADC_SAMPLE_CNUM] = {0};

//初始化ADC															   
void Adc_Init(void)
{    
  GPIO_InitTypeDef GPIO_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	//配置RCC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2, ENABLE);//使能GPIOA、DMA2时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟

	//配置GPIO端口
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
																GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//选择PA0~PA7组
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 
 
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 
	
	//配置DMA
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;  //通道选择
  DMA_InitStructure.DMA_PeripheralBaseAddr = (unsigned int)&(ADC1->DR);//DMA外设地址
  DMA_InitStructure.DMA_Memory0BaseAddr = (unsigned int)&m_ADCValue;//DMA 存储器0地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//外设到存储器模式
  DMA_InitStructure.DMA_BufferSize = ADC_SAMPLE_PNUM*ADC_SAMPLE_CNUM;;//数据传输量 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据长度:16位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//存储器数据长度:16位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 使用普通模式 
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//中等优先级
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;       
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//存储器突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);//初始化DMA Stream
  //双缓冲模式设置
	//DMA_DoubleBufferModeConfig(DMA2_Stream0,(uint32_t)(u16 *)(m_ADCValue1),DMA_Memory_0);    //DMA_Memory_0首先被传输
	//DMA_DoubleBufferModeCmd(DMA2_Stream0,ENABLE);	
	
	//配置ADC
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;//两个采样阶段之间的延迟20个时钟
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA使能
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
	//配置ADC1
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//非扫描模式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//开启连续转换
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_ExternalTrigConv =  0;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
  ADC_InitStructure.ADC_NbrOfConversion = ADC_SAMPLE_CNUM;//1个转换在规则序列中 也就是只转换规则序列1
  ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	//使能ADC1和DMA2
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);///////////
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
	
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	

}				  

u16 ADC_Proc_Value(unsigned char nIndex)
{
	u32 nValue = 0;
	u32 nSum = 0;
	u8 i = 0, j = 0;
	u16 Temp = 0;	
	u16 tempArray[ADC_SAMPLE_PNUM] = {0};

	for	(i=0; i<ADC_SAMPLE_PNUM; i++)					//2é?ˉ100×é
	{
		tempArray[i] = m_ADCValue[i][nIndex];
//		printf("\t\t\t******ADCValue:%X\r\n",tempArray[i]);
	}
	for(i=0; i<ADC_SAMPLE_PNUM-1; i++)						//è￥μ?×?′ó?μ
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
	for(i=10; i<ADC_SAMPLE_PNUM-10; i++)						//è????ù?μ  debug
	{
		nSum += tempArray[i] ;
	}
	nValue = nSum / (ADC_SAMPLE_PNUM-20);//debug
	
	return nValue;
}


	 









