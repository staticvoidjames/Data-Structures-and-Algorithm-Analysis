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

void q_sort(List *list, int start, int end)
{
	int i, j;
	if (end - start > 0)
	{
		// pivot  /'pɪvət ;ˋpɪvət / 枢纽，中心，支点
		// 找到pivot_key，这里直接通过二分法找中间的元素
		// 50	60	40
		int pivot_index = (start + end) / 2;
		int pivot_key = list->data[pivot_index];
		swap(list, pivot_index, end); //把pivot_key放到最后,便于后续处理
		i = start - 1;
		j = end;
		// 将所有<pivot_key的元素放到左边，所有>pivot_key的元素放到右边,最后将pivot_key放到中间
		// 一旦pivot_key放到指定位置后，在后续的排序过程中，它的位置都不会变了
		// 索引i往右走，j往左走，把左边比pivot_key大的和右边的比pivot_key小的元素进行交换
		while (1)
		{
			// 索引i往右走，j往左走，把左边比pivot_key大的和右边的比pivot_key小的元素进行交换
			while (list->data[++i] < pivot_key);
			while (list->data[--j] > pivot_key);
			if (i < j)
			{
				swap(list, i, j);
			}
			else
			{
				break;
			}
		}
		swap(list, i, end); // index为i的元素比pivot_key要大，将原来保存在end处的值为pivot_key的元素与i进行位置交换
		// printf("i:%d\tj:%d\n", i, j);
		// printf("start:%d\tend:%dpivot_index:%d\tpivot_key:%d\n", start, end, pivot_index, pivot_key);
		// print_list(*list);

		// 上面的过程就是快速排序的一轮循环,接下来将依据pivot_key分开的左右两个list分别进行快速排序(递归)，直
		// 到那一轮的快排序列长度为1(对元素个数为1的序列没有必要排序了)
		q_sort(list, start, i - 1);
		q_sort(list, i + 1, end);
	}
}

// 快速排序
void quick_sort(List *list)
{
	q_sort(list, 1, list->length);
}

int main(int argc, char const *argv[])
{
	List list;

	puts("初始化list");
	init_list(&list);
	print_list(list);
	puts("after quick_sort:");
	quick_sort(&list);
	print_list(list);

	return 0;
}
