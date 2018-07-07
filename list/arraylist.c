#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 200
typedef int ElementType;
#define OK 0
#define ERROR -1

struct array_list
{
    ElementType data[MAXSIZE];
    int length;
};

int create(struct array_list *list)
{
    if (list == NULL)
    {
        return ERROR;
    }
    list->length = 0;
    return OK;
}

int is_empty(struct array_list *list)
{
    return list->length == 0;
}

int size(struct array_list *list)
{
    return list->length;
}

int find(struct array_list *list,ElementType x)
{
    int i = 0;
    while(i < list->length && list->data[i] != x)
    {
        i ++;
    }
    if(list->length == 0 || i == list->length)
    {
        return ERROR;
    }
    return i;
}

int insert(struct array_list *list,ElementType x,int position)
{
    int i;
    if(list->length + 1 > MAXSIZE || position > list->length || position < 0)
    {
        return ERROR;
    }
    list->length ++;
    for(i = list->length;i >= position;i --)
    {
        list->data[i + 1] = list->data[i];
    }
    list->data[position] = x;
    return OK;
}

// remove方法与stdio.h冲突。。。
int list_remove(struct array_list *list,int position)
{
    int i;
    if(position > list->length || position < 0)
    {
        return ERROR;
    }
    for(i = position;i < list->length - 1;i ++)
    {
        list->data[i] = list->data[i + 1];
    }
    list->length --;
    return OK;
}

ElementType get(struct array_list *list,int position)
{
    if(position < 0 || position >= list->length)
    {
        return ERROR;
    }
    return list->data[position];
}

void print_list(struct array_list *list)
{
    int i;
    for(i = 0;i < list->length;i++)    
    {
        printf("%d\n",list->data[i]);
    }
}

void clear(struct array_list *list)
{
    list->length = 0;
}

int union_list(struct array_list *list1,struct array_list *list2)
{
    int i;
    for(i = 0;i < list2->length;i++)
    {
        ElementType x = get(list2,i);
        if(find(list1,x) == ERROR && insert(list1,x,list1->length) == ERROR)
        {
         	return ERROR;
        }
    }
    return OK;
}

int main(int argc, char const *argv[])
{
    int i,j;
    // 这个时候已经分配了结构体的内存，只是没有赋初值
    struct array_list list;
    struct array_list list1;
    // 建表时将结构体的指针传过去，create函数直接通过指针操作该结构体
    // 如果这里什么都不传，就要在create函数中创建一个结构体局部变量，然后返回，返回结构体时会将结构体的内容复制到list中，效率低
    // 函数中不能返回局部变量的指针，因为在函数退出时，局部变量都会被回收，这时如果还保留其指针，没有谁会保证其所指向的值不会被改变
    create(&list);
    printf("list.length=%d\n",size(&list));

    for(j=1;j<=5;j++)
        insert(&list,j,0);
    puts("插入数据1~5后");
    print_list(&list);
    printf("表长度:%d\n",size(&list));

    i=is_empty(&list);
    printf("list是否空：%d(1:是 0:否)\n",i);

    list_remove(&list,0);
    puts("删除第0个数据后");
    print_list(&list);

    puts("3在表中的位置:");
    printf("%d\n", find(&list,3));

    puts("表中第1个位置的元素:");
    printf("%d\n", get(&list,1));

    create(&list1);
    for(j=1;j<=20;j++)
        insert(&list1,j,0);
    puts("插入数据1~20后,表2中的数据:");
    print_list(&list1);
    printf("表长度:%d\n",size(&list1));

    union_list(&list,&list1);
    puts("合并两个列表后:");
    print_list(&list);

    clear(&list);
    puts("清除表内容后:");
    print_list(&list);

    return 0;
}
