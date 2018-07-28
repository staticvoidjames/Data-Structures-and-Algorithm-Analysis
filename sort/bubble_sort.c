#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_SIZE 1000

typedef struct
{
    int data[MAX_SIZE + 1]; // data[0]作为哨兵
    int length;
} List;

// 交换list中下标为i和下标为j两个位置的值
void swap(List *list, int i, int j)
{
    int tmp = list->data[i];
    list->data[i] = list->data[j];
    list->data[j] = tmp;
}

void print_list(List list)
{
    int i;
    for (i = 1; i <= list.length; i++)
    {
        printf("%d\t", list.data[i]);
    }
    puts("");
}

void init_list(List *list)
{
    int d[10] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 5};
    int i;
    for (i = 0; i < 10; i++)
    {
        list->data[i + 1] = d[i];
    }
    list->length = 10;
}

// 从小到大排序
void bubble_sort(List *list)
{
    int i, j;
    // 第i次循环,冒泡出第i大的数据
    for (i = 1; i < list->length; i ++)
    {
        for (j = 1; j <= list->length - i; j ++)
        {
            if (list->data[j] > list->data[j + 1])
            {
                swap(list, j, j + 1);
            }
        }
    }
}

// 从小到大排序
// 冒泡排序的初步改进版
void bubble_sort_optimize(List *list)
{
    int i, j, isSorted = 0;// isSorted:在第i次循环中,如果没有发生交换,那么就是已经排序好了,如果发生了交换,就判断还没有排序好
    for (i = 1; i < list->length && !isSorted; i ++)
    {
        isSorted = 1;
        for (j = 1; j <= list->length - i; j ++)
        {
            if (list->data[j] > list->data[j + 1])
            {
                isSorted = 0;
                swap(list, j, j + 1);
            }
        }
    }
}

// 从小到大排序
// 冒泡排序的终极改进版
void bubble_sort_ultimate(List * list)
{
    int i, j, lastExchangeIndex = 1;
    // lastExchangeIndex:表示最后一次交换发生在的位置,代表其之后的数据都排序好了
    // 这里直接跳到寻找第lastExchangeIndex大的数
    for (i = lastExchangeIndex; i < list->length; i ++)
    {
        for (j = 1; j <= list->length - i; j ++)
        {
            if (list->data[j] > list->data[j + 1])
            {
                swap(list, j, j + 1);
                lastExchangeIndex = j;
            }
        }
    }
}

int main(int argc, char const * argv[])
{
    List list;

    puts("初始化list");
    init_list(&list);
    print_list(list);
    puts("after bubble sort:");
    bubble_sort(&list);
    print_list(list);

    puts("初始化list");
    init_list(&list);
    print_list(list);
    puts("after bubble_sort_optimize:");
    bubble_sort_optimize(&list);
    print_list(list);

    puts("初始化list");
    init_list(&list);
    print_list(list);
    puts("after bubble_sort_ultimate:");
    bubble_sort_ultimate(&list);
    print_list(list);
    return 0;
}
