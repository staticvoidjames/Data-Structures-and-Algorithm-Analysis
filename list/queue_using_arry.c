#include <stdio.h>
#include <stdlib.h>

// 循环队列 因为需要使用queue->front和queue->rear之间的关系来判断一个元素是否为空/满。
// 因为这两者的关系有0-MAX_SIZE-1种,而具体队列中元素的个数有MAX_SIZE种情况,
// 所以在本队列中有一个元素不使用，导致队列为空的判断为queue->front == queue->rear
// 队列满的判断为(queue->rear + 1)%MAXSIZE == queue->front
// (queue->rear  - queue->front + MAXSIZE) % MAXSIZE表示队列中元素的个数
#define MAXSIZE 10
#define ERROR -1
#define OK 0

typedef int ElementType;

typedef struct
{
	ElementType data[MAXSIZE];
	int front;
	int rear;
}Queue;

void InitQueue(Queue *queue)
{
	queue->front = queue->rear = 0;
}

void ClearQueue(Queue *queue)
{
	queue->front = queue->rear = 0;
}

int isEmpty(Queue *queue)
{
	return queue->front == queue->rear;
}

int size(Queue *queue)
{
	return (queue->rear  - queue->front + MAXSIZE) % MAXSIZE;
}

int isFull(Queue *queue)
{
	return size(queue) == MAXSIZE - 1;
}

int enqueue(Queue *queue,ElementType element)
{
	if (isFull(queue))
	{
		return ERROR;
	}
	queue->data[queue->rear] = element;
	queue->rear = (queue->rear + 1) % MAXSIZE;
	return OK;
}

int dequeue(Queue *queue,ElementType *element)
{
	if (isEmpty(queue))
	{
		return ERROR;
	}
	queue->rear = (queue->rear - 1) % MAXSIZE;
	*element = queue->data[queue->rear];
	return OK;
}

void printQueue(Queue *queue)
{
	int index = queue->front;
	if (isEmpty(queue))
	{
		puts("空队列");
	}
	while(index != queue->rear)
	{
		printf("%4d", queue->data[index]);
		index = (index + 1) % MAXSIZE;
	}
	puts("");
}

int main(int argc, char const *argv[])
{
	Queue queue;
	ElementType element;

	InitQueue(&queue);
	printf("初始化队列后，队列空否？%u(1:空 0:否)\n",isEmpty(&queue));	
	
	for (int i = 0; i < MAXSIZE; ++i)
	{
		enqueue(&queue,i);
	}

	printf("插入%d个数据后,队列长度为: %d\n",MAXSIZE,size(&queue));
	printf("现在队列空否？%u(1:空 0:否)\n",isEmpty(&queue));
	printf("现在队列中的元素为: \n");
	printQueue(&queue);

	dequeue(&queue,&element);
	printf("弹出元素%d\n", element);

	dequeue(&queue,&element);
	printf("弹出元素%d\n", element);

	enqueue(&queue,9);
	enqueue(&queue,10);

	ClearQueue(&queue);
	puts("清空队列后,队列内元素为:");
	printQueue(&queue);

	return 0;
}
