#ifndef __BUTTON_H
#define __BUTTON_H
#include "sys.h"

#define set(x,y) y=x?0:1

//BUTTON端口定义

#define BUTTON_C1 PCout(1)    //输出  
#define BUTTON_C2 PCout(2)    //输出 
#define BUTTON_C3 PCout(3)    //输出 
#define BUTTON_C4 PCout(4)    //输出 
#define BUTTON_C5 PCout(5)    //输出 
#define BUTTON_C6 PCout(6)    //输出 

#define BUTTON_B5 PBin(5)     //输入
#define BUTTON_B6 PBin(6)     //输入
#define BUTTON_B7 PBin(7)     //输入
#define BUTTON_B8 PBin(8)     //输入
#define BUTTON_B12 PBin(12)     //输入
#define BUTTON_B13 PBin(13)     //输入

void BUTTON_Init(void);//初始化		 				    
#endif
