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

void PercDown(int A[], int p, int N)
{
    /* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    int X;
    X = A[p]; /* 取出根结点存放的值 */
    for ( Parent = p; (Parent * 2 + 1) < N; Parent = Child ) {
        Child = Parent * 2 + 1;
        if ( (Child != N - 1) && (A[Child] < A[Child + 1]) )
            Child++;  /* Child指向左右子结点的较大者 */
        if ( X >= A[Child] )
            break; /* 找到了合适位置 */
        else  /* 下滤X */
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

// 原理可参考附件:堆排序(算法2).png
// 堆排序(算法1)请参考堆排序(算法1),这里就不实现了
void heap_sort(List *list)
{
    int i, n;
    for (i = list->length / 2; i >= 0; i --)
    {
        PercDown(list->data + 1, i, list->length);
    }
    print_list(*list);
    n = list->length;
    for (i = n; i > 1; i --)
    {
        // 删除最大堆顶
        swap(list, 1, n --);
        PercDown(list->data + 1, 0, n);
    }
}

int main(int argc, char const *argv[])
{
    List list;

    puts("初始化list");
    init_list(&list);
    print_list(list);
    puts("after heap_sort:");
    heap_sort(&list);
    print_list(list);

    return 0;
}
