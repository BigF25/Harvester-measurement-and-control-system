#ifndef __QUEUE2_H
#define __QUEUE2_H
#include "malloc.h"
#include "sys.h"
#include "COMscreen.h"

typedef struct _node2{
	u8 buf;
	struct _node2 *next;
}node2;
typedef struct _queue2{
	node2 *front;
	node2 *rear;
}queue2;
extern queue2 *myqueue2;

//初始化队列
void queue2_Init(void);
//创建队列
queue2 *create_queue2(void);
//插入节点
queue2 *insert_queue2(queue2 *myqueue);
//删除节点
queue2 *delete_queue2(queue2 *myqueue);
//获得队列长度
int get_queue2_length(queue2 *myqueue);
//输出队列
void queue2_print(queue2 *myqueue);

#endif

