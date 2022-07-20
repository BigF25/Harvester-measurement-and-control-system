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

//��ʼ������
void queue2_Init(void);
//��������
queue2 *create_queue2(void);
//����ڵ�
queue2 *insert_queue2(queue2 *myqueue);
//ɾ���ڵ�
queue2 *delete_queue2(queue2 *myqueue);
//��ö��г���
int get_queue2_length(queue2 *myqueue);
//�������
void queue2_print(queue2 *myqueue);

#endif

