//数据队列相关的函数
#include "queue2.h"	   
#include "stdio.h"	   

#include "malloc.h"

queue2 *myqueue2;

void queue2_Init(void)
{
//	my_mem_init(SRAM_CAN_MSG); 	//初始化内部内存池
	myqueue2 = create_queue2(); 	//新建一个队列
}

//创建队列
queue2 *create_queue2(void)
{
	queue2 * myqueue = (queue2*)mymalloc(SRAM_CAN_MSG,sizeof(queue2));
	myqueue->front = NULL;
	myqueue->rear = NULL;
	return myqueue;
}
//插入节点
queue2 *insert_queue2(queue2 *myqueue)
{
	if (myqueue == NULL)
	{
//		printf("myqueue is NULL\n");
		return NULL;
	}
	node2 *new_node = NULL;
	new_node = (node2 *)mymalloc(SRAM_CAN_MSG,sizeof(node2));//create a new node
	while(new_node == NULL)
	{
		delete_queue2(myqueue);
		new_node = (node2 *)mymalloc(SRAM_CAN_MSG,sizeof(node2));//create a new node
	}
	//new_node->data = data;
	new_node->next = NULL;

	if (myqueue->rear == NULL)//if the queue is empty
	{
		myqueue->front = myqueue->rear = new_node;
	}
	else
	{
		myqueue->rear->next = new_node;
		myqueue->rear = new_node;//move queue rear pointer to new_node
	}
 
	return myqueue;
}
//删除节点
queue2 *delete_queue2(queue2 *myqueue)
{
	node2 *p_node = NULL;
	p_node = myqueue->front;
	if (p_node == NULL)
	{
//		printf("this is empty queue\n");
		return NULL;
	}
	else
	{
		myqueue->front = myqueue->front->next;
		if (myqueue->front == NULL)
		{
			myqueue->rear = NULL;
		}
		myfree(SRAM_CAN_MSG,p_node);
	}
	return myqueue;
}
//获得队列长度
int get_queue2_length(queue2 *myqueue)
{
	node2 *p_node = NULL;
	int len = 0;
 
	p_node = myqueue->front;
	if (NULL != p_node)
	{
		len = 1;
	}
	while (p_node != myqueue->rear)
	{
		p_node = p_node->next;
		len++;
	}
	return len;
}
//输出队列
void queue2_print(queue2 *myqueue)
{
	node2 *p_node = NULL;
	p_node = myqueue->front;
 
	if (p_node == NULL)
	{
		printf("this is empty queue2\r\n");
		return;
	}
	printf("The queue2 is :\t");
	while (p_node != myqueue->rear)
	{
		printf("%2x ", p_node->buf);
		p_node = p_node->next;
	}
	printf("%2x ", p_node->buf);
	printf("\r\n");
}

