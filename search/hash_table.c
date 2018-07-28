#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 11
#define Nil -32768

/* 本案例冲突解决方式为线性探测法,除此之外的其他解决方式还有:
    平方探测法、双散列法和分离链接法等

    注意事项:
    1. 在插入时,先判断是否还有空位,如果没有,则没必要插入,不然会在找空位的时候出现死循环(可以在每次移到下一位的时候判断有没有移到最初的hash(x)的位置)
    2. 除了存储的数据外,还要有一个标志位表示当前节点的内容是否已被删除,因为使用了线性探测法,只能通过"懒删除"的方式删除数据,因为如果直接删除数据,
    在查找时,可能出现查找到当前位置时,出现了一个空位,导致查找过程已经停止了,但是之前这个值可能插入在更后面的地方
 */
typedef struct
{
    int *data;
    char *delete_flag; // 为0时表示正常,为1时表示已被删除
    int count;
} hash_table;

int init_table(hash_table *table)
{
    int i;
    table->data = (int *)malloc(sizeof(int) * HASHSIZE);
    table->delete_flag = (char *)malloc(sizeof(char) * HASHSIZE);
    table->count = 0;
    for (i = 0; i < HASHSIZE; i++)
    {
        table->data[i] = Nil;
        table->delete_flag[i] = 0;
    }
    return OK;
}

int hash(int key)
{
    return key % HASHSIZE;
}

int insert(hash_table *table, int x)
{
    int key = hash(x);
    if (table->count == HASHSIZE)
    {
        return UNSUCCESS;
    }
    // 如果一个位置上有没被删除的数据,那么就得跳过这个数据
    while (table->data[key] != Nil && !table->delete_flag[key])
    {
        key = (key + 1) % HASHSIZE; // 线性探测
    }
    table->data[key] = x;
    table->delete_flag[key] = 0;
    table->count++;
    return SUCCESS;
}

int find(hash_table table, int x)
{
    int origin_position = hash(x);
    int key = origin_position;
    while (table.data[key] != x && table.data[key] != Nil)
    {
        key = (key + 1) % HASHSIZE;
        if (key == origin_position) // 遍历了整个表还没有找到
        {
            break;
        }
    }
    if (table.data[key] == x && !table.delete_flag[key])
    {
        return key;
    }
    return -1;
}

int delete (hash_table *table, int x)
{
    int position = find(*table, x);
    if (position == -1)
    {
        return UNSUCCESS;
    }
    table->delete_flag[position] = 1;
}

main(int argc, char const *argv[])
{
    int arr[HASHSIZE] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48};
    int i, x;
    hash_table table;

    init_table(&table);
    for (i = 0; i < HASHSIZE; i++)
        insert(&table, arr[i]);

    puts("插入数据后:");
    for (i = 0; i < HASHSIZE; i++)
    {
        printf("position:%d\t data:%d\n",i,table.data[i]);
    }
    printf(" %d 的地址为：%d \n", arr[4], find(table, arr[4]));

    delete (&table, 16);
    puts("删除节点16后:");
    for (i = 0; i < HASHSIZE; i++)
    {
        printf(" %d 的地址为：%d \n", arr[i], find(table, arr[i]));
    }

    delete (&table, 22);
    puts("删除节点22后:");
    for (i = 0; i < HASHSIZE; i++)
    {
        printf(" %d 的地址为：%d \n", arr[i], find(table, arr[i]));
    }

    delete (&table, 48);
    puts("删除节点48后:");
    for (i = 0; i < HASHSIZE; i++)
    {
        printf(" %d 的地址为：%d \n", arr[i], find(table, arr[i]));
    }

    return 0;
}
