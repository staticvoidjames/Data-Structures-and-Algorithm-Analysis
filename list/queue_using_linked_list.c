#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
#define OK 1
#define ERROR -1

typedef int ElmentType;

typedef struct Node
{
    ElmentType data;
    struct Node *next;
}Node;

typedef struct
{
    Node *front;
    Node *rear;
}Queue;

void InitQueue(Queue *queue)
{
    Node *node = (Node *)malloc(sizeof(Node));
    queue->front = queue->rear = node;
}

void print_queue(Queue *queue)
{
    Node *p = queue->front->next;
    if(queue->rear == queue->front)
    {
        puts("队列为空");
    }
    while(p)
    {
        printf("%4d",p->data);
        p = p->next;
    }
    puts("");
}

int EnQueue(Queue *queue,ElmentType element)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->data = element;
    queue->rear->next = node;
    queue->rear = node;
    return OK;
}
int DeQueue(Queue *queue,ElmentType *element)
{
    if(queue->front == queue->rear)
    {
        return ERROR;
    }
    Node *node = queue->front->next;
    *element = node->data;
    queue->front->next = node->next;
    // 如果出队列的是队尾,在回收之前要将队列的头和尾都置到头结点上去
    if(node == queue->rear)
    {
        queue->rear = queue->front;
    }
    free(node);
    return OK;
}

int ClearQueue(Queue *queue)
{
    Node *p = queue->front->next,*tmp;
    while(p)
    {
        tmp=p;
        p = p->next;
        free(tmp);
    }
    queue->rear = queue->front;
    queue->front->next = NULL;
    return OK;
}

DestroyQueue(Queue *queue)
{
    while(queue->front)
    {
        queue->rear = queue->front->next;
        free(queue->front);
        queue->front = queue->rear;
    }
}

QueueEmpty(Queue *queue)
{
    return queue->front == queue->rear;
}

int QueueLength(Queue *queue)
{
    int i = 0;
    Node *p = queue->front;
    while(p != queue->rear)
    {
        i ++;
        p = p->next;
    }
    return i;
}

int GetHead(Queue *queue,ElmentType *element)
{ 
	if(queue->front==queue->rear)
		return ERROR;
	*element = queue->front->next->data;
	return OK;
}

int main()
{
 	int i;
    Queue queue;
    ElmentType element;
    InitQueue(&queue);
    printf("是否空队列？%d(1:空 0:否)  \n",QueueEmpty(&queue));
	printf("队列的长度为%d\n",QueueLength(&queue));
    
    for(i = 0; i < 10; i++)
    {
        EnQueue(&queue,i);
    }
    printf("插入10个元素后,队列的长度为%d\n",QueueLength(&queue));
	printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(&queue));
	printf("队列的元素依次为：");
	print_queue(&queue);

	i=GetHead(&queue,&element);
	printf("队头元素是：%d\n",element);

	DeQueue(&queue,&element);
	printf("删除了队头元素%d\n",element);

	i=GetHead(&queue,&element);
	printf("新的队头元素是：%d\n",element);

	ClearQueue(&queue);
	printf("清空队列后,queue.front=%u queue.rear=%u queue.front->next=%u\n",queue.front,queue.rear,queue.front->next);

	DestroyQueue(&queue);
	printf("销毁队列后,queue.front=%u queue.rear=%u\n",queue.front, queue.rear);
    return 0;
}
