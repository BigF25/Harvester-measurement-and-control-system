#include "button.h" 
//////////////////////////////////////////////////////////////////////////////////	 	 

//初始化PA5和PA6为输出口、初始化PB6和PB7为输出口		    
//BUTTON IO初始化
void BUTTON_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  //GPIOA5,A6输出初始化设置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOF时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
//	GPIO_ResetBits(GPIOC,GPIO_Pin_1 | GPIO_Pin_2);//初始化低电平
//	GPIO_ResetBits(GPIOC,GPIO_Pin_3| GPIO_Pin_4);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_5 | GPIO_Pin_6);
	
	//GPIOB6,B7输入初始化设置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOF时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
  GPIO_SetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_6);//初始化高电平
	GPIO_SetBits(GPIOB,GPIO_Pin_7 | GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13);

}
