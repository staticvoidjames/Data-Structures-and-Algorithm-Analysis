// 本链表结构没有使用头结点
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define OK 1
#define ERROR -1

typedef int ElementType;
//这里使用typedef定义一个结构体类型,这样的话后续声明一个节点只需要 Node node;即可
// 避免了每次声明时都需要 stuct Node node;声明结构体指针时同理
typedef struct Node
{
    ElementType data;
    struct Node *next;
}Node;

typedef struct LinkedList
{
    Node *head;// 第一个结点
    int size;
}LinkedList;

int create(LinkedList *list)
{
    list->size = 0;
    list->head = NULL;
    return OK;
}

int find(LinkedList *list,ElementType x)
{
    int i = 0;
    ElementType element;
    Node *node;
    if(list->size == 0)
    {
        return ERROR;
    }
    node = list->head;
    while(node && (node->data != x))
    {
        i ++;
        node = node->next;
    }
    if(node)
    {
        return i;
    }
    return ERROR;
}

Node *get(LinkedList *list,int position)
{
    Node *prev;
    int i;
    if(position < 0 || position >= list->size)
    {
        return NULL;
    }
    prev = list->head;
    for(i = 0;i < position;i++)
    {
        prev = prev->next;
    }
    return prev;
}

int insert(LinkedList *list,ElementType x,int position)
{
    int i;
    Node *prev,*node;
    if(position < 0 || position> list->size)
    {
        return ERROR;
    }
    node = (Node *) malloc(sizeof(Node));
    node->data = x;

    // 如果有头结点，这里就不需要单独处理第0个数据了
    // 有头结点的话，第一个数据就是头结点
    if (position == 0)
    {
        node->next = list->head;
        list->head = node;
        list->size ++;
        return OK;
    }
    prev = get(list,position -1);
    node->next = prev->next;
    prev->next = node;
    list->size ++;
    return OK;
}

void print_list(LinkedList *list)
{
    int i;
    Node *node = list->head;
    if(list->size == 0)
    {
        puts("链表为空");
        return;
    }
    printf("size:%d\n", list->size);
    for(i = 0;i < list->size;i ++)
    {
        printf("%d\n",node->data);
        node = node->next;
    }
}

int list_remove(LinkedList *list,int position)
{
    Node *prev,*node;
    if(position < 0 || position> list->size)
    {
        return ERROR;
    }
    if (position == 0)
    {
        node = list->head;
        list->head = node->next;
        free(node);
        list->size --;
        return OK;
    }
    prev = get(list,position - 1);
    node = prev->next;
    prev->next = node->next;
    free(node);
    list->size --;
    return OK;
}

int is_empty(LinkedList *list)
{
    return list->size == 0;
}

int clear(LinkedList *list)
{
    Node *node = list->head,*tmp;
    for (int i = 0; i < list->size; ++i)
    {
        tmp = node;
        node = node->next;
        free(node);
    }
    list->size = 0;
    return OK;
}

int size(LinkedList *list)
{
    return list->size;
}

//	头插法
void creat_linked_head(LinkedList *list, int n)
{
	Node *node;
    int i;
    srand(time(0));
    // 这里将head作为头结点
    list->head = (Node *)malloc(sizeof(Node));
    list->size = 0;
    list->head->data = 0;
    list->head->next = NULL;
    list->size ++;

    for(i = 0;i < n - 1;i ++)
    {
       node = (Node *)malloc(sizeof(Node));
       node->data = rand()%100;
       node->next = list->head;
       list->head = node;
       list->size ++;
   }
}

//	尾插法
void creat_linked_end(LinkedList *list, int n)
{
	Node *node,*prev;
    int i;
    srand(time(0));
    list->size = 0;
    list->head = (Node *)malloc(sizeof(Node));
    list->head->data = 0;
    list->head->next = NULL;
    list->size ++;

    for(i = 0;i < n - 1;i ++)
    {
        prev = get(list,i);
        node = (Node *)malloc(sizeof(Node));
        node->data = rand()%100;
        node->next = NULL;
        prev->next = node;
        list->size ++;
    }
}

int main(int argc, char const *argv[])
{
    int i,j;
    LinkedList list,head_list,end_list;
    create(&list);
    printf("list.length=%d\n",size(&list));

    insert(&list,5,0);
    insert(&list,3,0);
    insert(&list,4,1);
    insert(&list,2,0);
    insert(&list,1,0);
    puts("插入数据1~5后");
    printf("%d\n", list.head->data);
    printf("表长度:%d\n",size(&list));

    i=is_empty(&list);
    printf("list是否空：%d(1:是 0:否)\n",i);

    list_remove(&list,0);
    puts("删除第0个数据后");
    print_list(&list);

    list_remove(&list,1);
    puts("删除第1个数据后");
    print_list(&list);

    puts("3在表中的位置:");
    printf("%d\n", find(&list,3));


    puts("4在表中的位置:");
    printf("%d\n", find(&list,4));

    clear(&list);
    puts("清除链表内所有数据后:");
    print_list(&list);

    creat_linked_head(&head_list,10);
    puts("头插法10个随机数:");
    print_list(&head_list);

    creat_linked_end(&end_list,10);
    puts("尾插法10个随机数:");
    print_list(&end_list);

    return 0;
}