#include <stdio.h>
#include <stdlib.h>

/*  无哨兵顺序查找
    a:数组,查找集
    size:要查找的数组个数
    x:为要查找的关键字
*/
int sequential_search_normal(int a[], int size, int x)
{
    int i;
    for (i = 1; i <= size; i++)
    {
        if (a[i] == x)
            return i;
    }
    return 0;
}

/* 有哨兵顺序查找 */
int sequential_search_with_guard(int a[], int size, int x)
{
    int i;
    a[0] = x;
    i = size;
    while (a[i] != x)
    {
        i--;
    }
    return i;
}

int main(int argc, char const *argv[])
{
    int length = 11;

    int a[10], i, index;

    for (i = 0; i <= length; i++)
    {
        a[i] = i;
    }
    printf("index of %d(normal):%d\n", 5, sequential_search_normal(a, length, 5));
    printf("index of %d(normal):%d\n", 11, sequential_search_normal(a, length, 11));

    printf("index of %d(哨兵方式):%d\n", 5, sequential_search_with_guard(a, length, 5));
    printf("index of %d(哨兵方式):%d\n", 11, sequential_search_with_guard(a, length, 11));

    return 0;
}
