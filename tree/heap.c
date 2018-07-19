#include <stdio.h>
#include <stdlib.h>

/* 本案例按最大堆(大顶堆)方式实现
   最小堆(小顶堆)方式的实现原理相同,这里就不多余实现了
*/
#define MAX_DATA 1000
#define OK 1
#define ERROR 0


typedef int ElementType;

typedef struct HeapNode
{
    ElementType *data;// 最大堆的数据,以数组形式表示的完全二叉树
    int size;// 当前节点数量
    int capacity;// 可容纳节点数量
}*Heap;

typedef Heap MaxHeap;

MaxHeap create_heap(int max_size)
{
    Heap h = (Heap)malloc(sizeof(struct HeapNode));
    h->data = (ElementType *)malloc(sizeof(ElementType) * (max_size + 1));// data[0]用作哨兵,放置MAX_DATA
    h->size = 0;
    h->capacity = max_size;
    h->data[0] = MAX_DATA;/* 定义"哨兵"为大于堆中所有可能元素的值*/
    return h;
}

int is_full(MaxHeap h)
{
    return h->size == h->capacity;
}

int is_empty(MaxHeap h)
{
    return h->size == 0;
}

/* 这里插入一个元素x,不考虑堆中已经存在这个元素的情况 */
int insert(MaxHeap h,ElementType x)
{
    int i;
    if(is_full(h))
    {
        puts("最大堆已经满了~");
        return ERROR;
    }
    h->size ++;
    i = h->size;
    // 如果x > h->data[i >> 1],将h->data[i >> 1]的值修改到h->data[i]的位置
    for(i = h->size;x > h->data[i >> 1];i >>= 1)
    {
        h->data[i] = h->data[i >> 1];
    }
    h->data[i] = x;
    return OK;
}

/* 从堆上取出堆顶的数据 */
ElementType delete_max(MaxHeap h)
{
    int target_position,child;
    ElementType max_item,last_item;

    if(is_empty(h))
    {
        puts("最大堆为空");
        return ERROR;
    }

    max_item = h->data[1];
    last_item = h->data[h->size --];// 要保证在删除之后还是最大堆,就需要为最后一个元素在删除后的堆中找到一个合适的位置

    target_position = 1;
    child = target_position << 1;

    while(child <= h->size)
    {
        // 在当前父节点中找到更大的那个子节点,用它的值替换掉当前的节点值(如果这个子节点的值>last_item的值)
        child = target_position << 1;
        if(child != h->size && h->data[child + 1] > h->data[child])// 如果当前节点有兄弟节点且兄弟节点更大,去更大的节点的位置
        {
            child ++;
        }
        // last_item找到了位置,直接跳出这个循环即可
        if(last_item > h->data[child])
        {
            break;
        }
        h->data[target_position] = h->data[child];
        target_position = child;
        child = target_position << 1;
    }
    h->data[target_position] = last_item;
    return max_item;
}

/* 将以h->data[p]为根节点的完全二叉树调成一个堆 */
void PercDown(MaxHeap h,int p)
{
    int target_position, child;
    ElementType current_item;

    current_item = h->data[p];
    target_position = p;

    for(target_position = p;target_position << 1 <= h->size;target_position = child)
    {
        child = target_position << 1;
        if(child != h->size && h->data[child + 1] > h->data[child])
        {
            child ++;
        }
        if(current_item > h->data[child])
        {
            break;
        }
        h->data[target_position] = h->data[child];
    }
    h->data[target_position] = current_item;
}

/* 建造一个最大堆的方式有2种:
   1.来一个元素出入一个元素,假设有n个元素,插入一个元素的时间复杂度为O(logn),插入n个元素的时间复杂度就是O(nlogn)
   2.来一个元素就插入到数组的最后(顺序插入),全部插入完成后,调整节点位置,使之成为一个最大堆。其时间复杂度为O(n)。
	这里的事件复杂度推算方式，请参考附件图片:   			
*/
void build_heap(MaxHeap h)
{
    /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
    /* 从最后一个结点的父节点开始，到根结点1 */
    int i;
    // 对最高的有儿子的节点将以其为根节点的二叉树调成一个堆
    for(i = h->size >> 1; i > 0; i --)
    {
        PercDown(h,i);
    }
}

void print_heap(MaxHeap h)
{
    int i;
    for(i = 1;i <= h->size;i ++)
    {
        printf("%d\t",h->data[i]);
    }
    puts("");
}

int main(int argc,char **argv)
{
    MaxHeap h = create_heap(100);
    int i;
    int data[] = {MAX_DATA,79,66,43,83,72,87,38,55,91,30,49,9};
    insert(h,79);
    insert(h,66);
    insert(h,43);
    insert(h,83);
    insert(h,72);
    insert(h,87);
    insert(h,38);
    insert(h,55);
    insert(h,91);
    insert(h,30);
    insert(h,49);
    insert(h,9);

    puts("插入数据后:");
    print_heap(h);

    printf("删除顶点元素%d后:",delete_max(h));
    print_heap(h);
    printf("删除顶点元素%d后:",delete_max(h));
    print_heap(h);
    printf("删除顶点元素%d后:",delete_max(h));
    print_heap(h);
    printf("删除顶点元素%d后:",delete_max(h));
    print_heap(h);
    
    h = create_heap(100);
    // 这里将一个本地指针变量赋给了一个结构体成员,这其实是很危险的,但是考虑这里是演示,且在main函数中,就无所谓了
    // 虽然也是本地变量指针,但是其所指向的内容是通过动态分配在堆空间中,在程序结束前是不会被释放的
    h->data = data;
    h->size = 12;
    puts("重新初始化并插入数据后(还未对数据进行整理为堆的形式):");
    print_heap(h);
    
    build_heap(h);
    puts("对数据进行整理为堆的形式后:");
    print_heap(h);

    return 0;
}