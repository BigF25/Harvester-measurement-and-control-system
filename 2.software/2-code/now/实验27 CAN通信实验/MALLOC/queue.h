#ifndef __QUEUE_H
#define __QUEUE_H
#include "malloc.h"
#include "sys.h"
typedef struct _node{
	CanRxMsg data;
	RTC_DateTypeDef RTC_DateStruct;//4
	RTC_TimeTypeDef RTC_TimeStruct;//4
	struct _node *next;
}node;
typedef struct _queue{
	node *front;
	node *rear;
}queue;
extern queue *myqueue;

//��ʼ������
void queue_Init(void);
//��������
queue *create_queue(void);
//����ڵ�
queue *insert_queue(queue *myqueue);
//ɾ���ڵ�
queue *delete_queue(queue *myqueue);
//��ö��г���
int get_queue_length(queue *myqueue);
//�������
void queue_print(queue *myqueue);

#endif

