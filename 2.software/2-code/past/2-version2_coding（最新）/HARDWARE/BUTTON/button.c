#include "button.h" 
//////////////////////////////////////////////////////////////////////////////////	 	 

//��ʼ��PA5��PA6Ϊ����ڡ���ʼ��PB6��PB7Ϊ�����		    
//BUTTON IO��ʼ��
void BUTTON_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  //GPIOA5,A6�����ʼ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOFʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
//	GPIO_ResetBits(GPIOC,GPIO_Pin_1 | GPIO_Pin_2);//��ʼ���͵�ƽ
//	GPIO_ResetBits(GPIOC,GPIO_Pin_3| GPIO_Pin_4);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_5 | GPIO_Pin_6);
	
	//GPIOB6,B7�����ʼ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOFʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
  GPIO_SetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_6);//��ʼ���ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_7 | GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13);

}
