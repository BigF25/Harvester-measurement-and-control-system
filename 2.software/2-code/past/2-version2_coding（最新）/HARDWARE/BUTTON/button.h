#ifndef __BUTTON_H
#define __BUTTON_H
#include "sys.h"

#define set(x,y) y=x?0:1

//BUTTON�˿ڶ���

#define BUTTON_C1 PCout(1)    //���  
#define BUTTON_C2 PCout(2)    //��� 
#define BUTTON_C3 PCout(3)    //��� 
#define BUTTON_C4 PCout(4)    //��� 
#define BUTTON_C5 PCout(5)    //��� 
#define BUTTON_C6 PCout(6)    //��� 

#define BUTTON_B5 PBin(5)     //����
#define BUTTON_B6 PBin(6)     //����
#define BUTTON_B7 PBin(7)     //����
#define BUTTON_B8 PBin(8)     //����
#define BUTTON_B12 PBin(12)     //����
#define BUTTON_B13 PBin(13)     //����

void BUTTON_Init(void);//��ʼ��		 				    
#endif
