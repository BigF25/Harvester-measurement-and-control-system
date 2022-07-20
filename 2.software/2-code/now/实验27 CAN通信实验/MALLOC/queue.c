//数据队列相关的函数
#include "queue.h"	   
#include "stdio.h"	   

#include "malloc.h"

queue *myqueue;

void queue_Init(void)
{
	my_mem_init(SRAM_CAN_MSG); 	//初始化内部内存池
	myqueue = create_queue(); 	//新建一个队列
}

//创建队列
queue *create_queue(void)
{
	queue * myqueue = (queue*)mymalloc(SRAM_CAN_MSG,sizeof(queue));
	myqueue->front = NULL;
	myqueue->rear = NULL;
	return myqueue;
}
//插入节点
queue *insert_queue(queue *myqueue)
{
	if (myqueue == NULL)
	{
//		printf("myqueue is NULL\n");
		return NULL;
	}
	node *new_node = NULL;
	new_node = (node *)mymalloc(SRAM_CAN_MSG,sizeof(node));//create a new node
	while(new_node == NULL)
	{
		delete_queue(myqueue);
		new_node = (node *)mymalloc(SRAM_CAN_MSG,sizeof(node));//create a new node
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
queue *delete_queue(queue *myqueue)
{
	node *p_node = NULL;
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
int get_queue_length(queue *myqueue)
{
	node *p_node = NULL;
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
void queue_print(queue *myqueue)
{
	node *p_node = NULL;
	p_node = myqueue->front;
 
	if (p_node == NULL)
	{
		printf("this is empty queue\r\n");
		return;
	}
	printf("The queue is :\r\n");
	while (p_node != myqueue->rear)
	{
//		printf("20%d-%02d-%02d %02d:%02d:%02d\t", p_node->RTC_DateStruct.RTC_Year,p_node->RTC_DateStruct.RTC_Month,p_node->RTC_DateStruct.RTC_Date,p_node->RTC_TimeStruct.RTC_Hours,p_node->RTC_TimeStruct.RTC_Minutes,p_node->RTC_TimeStruct.RTC_Seconds);
//		printf("%x:\t", p_node->data.StdId);
		for(int i=0; i<8; i++)
		{
			printf("%x\t", p_node->data.Data[i]);
		}
		printf("\r\n");
		p_node = p_node->next;
	}
//	printf("20%d-%02d-%02d %02d:%02d:%02d\t", p_node->RTC_DateStruct.RTC_Year,p_node->RTC_DateStruct.RTC_Month,p_node->RTC_DateStruct.RTC_Date,p_node->RTC_TimeStruct.RTC_Hours,p_node->RTC_TimeStruct.RTC_Minutes,p_node->RTC_TimeStruct.RTC_Seconds);
//	printf("%x:\t", p_node->data.StdId);
	for(int i=0; i<8; i++)
	{
		printf("%x\t", p_node->data.Data[i]);
	}
	printf("\r\n");
}

