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

//初始化队列
void queue_Init(void);
//创建队列
queue *create_queue(void);
//插入节点
queue *insert_queue(queue *myqueue);
//删除节点
queue *delete_queue(queue *myqueue);
//获得队列长度
int get_queue_length(queue *myqueue);
//输出队列
void queue_print(queue *myqueue);

#endif

