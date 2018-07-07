#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

struct Array{
    int *data;
    int size;
};

struct Array create(int size)
{
    // 这里直接使用结构体,而不使用指针,避免使用起来复杂
    struct Array arr;
    arr.data = (int *)malloc(sizeof(ElementType) * size);
    arr.size = size;
    return arr;
}

void print(struct Array *arr)
{
    if(arr == NULL)
        return;
    for(int i = 0;i < arr->size; i ++)
    {
        printf("%d ",arr->data[i]);
    }
    putchar('\n');
}

int is_empty(struct Array *arr)
{
    return arr->size == 0;
}

void set(struct Array *arr,int position,ElementType x)
{
    int *p,i;
    if(arr == NULL)
    {
        return;
    }
    if(arr->size <= position)
    {
        p = (int *)malloc((position + 1) * sizeof(ElementType));
        for(i = 0;i < arr->size;i ++)
        {
            p[i] = arr->data[i];
        }
        free(arr->data);
        arr->data = p;
        arr->size = position + 1;
    }
    arr->data[position] = x;
}

ElementType get(struct Array *arr,int position)
{
    if(position >= arr->size)
    {
        return -1;
    }
    return arr->data[position];
}
void clear(struct Array *arr)
{
    if(arr == NULL)
    {
        return;
    }
    free(arr->data);
}

int main(int argc, char const *argv[])
{
    struct Array arr = create(10);
    puts("可变数组是否为空:");
    printf("%d\n", is_empty(&arr));
    for (int i = 0; i < arr.size; ++i)
    {
        arr.data[i] = i;
    }
    print(&arr);
    printf("size of Array:%d\n", arr.size);
    puts("the 2nd data:");
    printf("%d\n", get(&arr,2));

    set(&arr,2,1000);
    printf("after set 2nd to 1000:%d\n", get(&arr,2));

    set(&arr,2000,20);
    printf("after set 2000th to 20:%d\n", get(&arr,2000));
    printf("size of Array:%d\n", arr.size);

    return 0;
}
