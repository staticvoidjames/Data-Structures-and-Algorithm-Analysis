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

// 归并排序的核心----归并...
void merge(List *list, int left, int middle, int right, int *tmp)
{
    int right_start = middle + 1;
    int i = 0;
    // 归并左右两个数组数据,存放到临时数组中
    while (left <= middle && right_start <= right)
    {
        if (list->data[left] <= list->data[right_start])
        {
            tmp[i++] = list->data[left++];
        }
        else
        {
            tmp[i++] = list->data[right_start++];
        }
    }
    while (left <= middle)
    {
        tmp[i++] = list->data[left++];
    }
    while (right_start <= right)
    {
        tmp[i++] = list->data[right_start++];
    }
    // 从临时数组中将数组导回去
    while (i > 0)
    {
        list->data[right--] = tmp[--i];
    }
}

// 归并排序,递归实现方式
void merge_sort_with_recursive(List *list, int left, int right, int *tmp)
{
    int middle;
    if (right > left)
    {
        middle = (left + right) / 2;
        merge_sort_with_recursive(list, left, middle, tmp);      /* 递归解决左边 */
        merge_sort_with_recursive(list, middle + 1, right, tmp); /* 递归解决右边 */
        merge(list, left, middle, right, tmp);                   /* 合并两段有序序列 */
    }
}

// 归并排序(递归实现)
void merge_sort_recursive(List *list)
{
    int *tmp = (int *)malloc(sizeof(int) * list->length);
    merge_sort_with_recursive(list, 1, list->length, tmp);
    free(tmp);
}

// 归并排序(非递归实现)
void merge_sort(List *list)
{
    int *tmp = (int *)malloc(sizeof(int) * list->length);
    int length = 1;
    int left, middle, right;
    // 先当做长度为1的子序列两两归并,每次归并完成后,将长度*2,继续两两归并,知道长度为总序列长度的1/2
    while (length < list->length)
    {
        left = 1;
        while (left + 2 * length - 1 <= list->length)
        {
            right = left + 2 * length - 1;
            middle = (left + right) / 2;
            // printf("left:%d\tmiddle:%d\tright:%d\n", left, middle, right);
            merge(list, left, middle, right, tmp);
            left += 2 * length;
        }

        right = left + 2 * length - 1;
        middle = (left + right) / 2;
        // 剩下的是两个序列
        if (middle < list->length)
        {
            merge(list, left, middle, list->length, tmp);
        }
        else
        {
            // 只能做一个序列了,这里不需要处理,直接让他待在那就行了,这里面的数据肯定是有序的,
            // 因为之前已经对这里归并排序过了
            // 这里留下了一组数据,在后续的归并中,除了最后一次,其余的次数是不可能来处理这组
            // 数据的(两两归并,每轮归并后序列长度length*2就决定了这个性质,设x = list->length % length,则list->length % (2 * length) >= x),
            // 也就是说这组数据不会变,而最后的一次归并,由于middle < list->length(最后一次2 * length >= list->length)肯定会成立,肯定会归并这里的数据
        }
        printf("length:%d\n", length);
        print_list(*list);

        length *= 2;
    }
    free(tmp);
}

/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge(int A[], int TmpA[], int L, int R, int RightEnd)
{ /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
    int LeftEnd, NumElements, Tmp;
    int i;

    LeftEnd = R - 1; /* 左边终点位置 */
    Tmp = L;         /* 有序序列的起始位置 */
    NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
            TmpA[Tmp++] = A[L++]; /* 将左边元素复制到TmpA */
        else
            TmpA[Tmp++] = A[R++]; /* 将右边元素复制到TmpA */
    }

    while (L <= LeftEnd)
        TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
    while (R <= RightEnd)
        TmpA[Tmp++] = A[R++]; /* 直接复制右边剩下的 */
                              // 这里就不需要倒回去了
    // for (i = 0; i < NumElements; i++, RightEnd--)
    // A[RightEnd] = TmpA[RightEnd]; /* 将有序的TmpA[]复制回A[] */
}

/* length = 当前有序子列的长度*/
void Merge_pass(int A[], int TmpA[], int N, int length)
{ /* 两两归并相邻有序子列 */
    int i, j;
    for (i = 0; i <= N - 2 * length; i += 2 * length)
        Merge(A, TmpA, i, i + length, i + 2 * length - 1);
    if (i + length < N) /* 归并最后2个子列*/
        Merge(A, TmpA, i, i + length, N - 1);
    else /* 最后只剩1个子列*/
        for (j = i; j < N; j++)
            TmpA[j] = A[j];
}

// 归并排序(非递归方式)
// 中国大学mooc 《数据结构》版(有修改)
void merge_sort1(List *list)
{
    int length;
    int *TmpA;
    length = 1; /* 初始化子序列长度*/
    TmpA = malloc(list->length * sizeof(int));
    while (length < list->length)
    {
        // 该版本与merge_sort的区别在于这里,这里讲源数组和临时数组进行了两次逆向的"倒来倒去"的操作,
        // 这里避免了再每一次merge的时候都进行2次"倒来倒去",这里2次merge的话才需要2次"倒来倒去"
        Merge_pass(list->data + 1, TmpA, list->length, length);
        length *= 2;
        Merge_pass(TmpA, list->data + 1, list->length, length);
        length *= 2;
    }
    free(TmpA);
}

int main(int argc, char const *argv[])
{
    List list;

    puts("初始化list");
    init_list(&list);
    print_list(list);

    puts("after merge_sort_recursive:");
    merge_sort_recursive(&list);
    print_list(list);

    puts("初始化list");
    init_list(&list);
    print_list(list);

    puts("after merge_sort:");
    merge_sort(&list);
    print_list(list);

    puts("初始化list");
    init_list(&list);
    print_list(list);

    puts("after merge_sort1:");
    merge_sort1(&list);
    print_list(list);

    return 0;
}
