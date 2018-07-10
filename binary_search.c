#include <stdio.h>

int binary_search(int *array,int length,int target)
{
    int left = 0,right = length - 1,middle;
    // 这一个步骤可以不存在,因为二分的时候如果找不
    // 到会自动退出返回-1,但是先进行判断可以提高效率
    // 如果在超出范围直接返回不存在
    // if(!(array[right] >= target && target >= array[left]))
    // {
    //     return -1;
    // }
    while(left <= right)
    {
        middle = (left + right) / 2;
        if(array[middle] > target)
        {
            // 这里必须是right = middle - 1;不能是right = middle;
            // 否则在数组{1,2}中查找0时会陷入死循环(array[middle] > target会一直成立,middle永远会为0)
            // 而且right = middle - 1;为在找不到target时提供了退出条件
            // 这里array[middle]与target已经比较完成了,没必要再比较了
            right = middle - 1;
        }
        else if(array[middle] < target)
        {
            // 这里必须是left = middle + 1;不能是left = middle;
            // 否则在数组{1,2}中查找2时会陷入死循环(array[middle] < target会一直成立,middle永远会为0)
            // (n + (n + 1)) / 2 = n在整数计算时成立
            // 而且left = middle + 1;为在找不到target时提供了退出条件
            // 这里array[middle]与target已经比较完成了,没必要再比较了
            left = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return -1;
}

int binary_search1(int nums[],int length,int target)
{
    // 
    int low = 0, high = length;
    while(low < high)
    {
        int mid = (low + high) / 2;
        if(nums[mid] == target)
            return mid;
        if(nums[mid] < target)
            low = mid + 1;
        else
            high = mid;
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int array[12] = {1,2,6,8,10,80,81,91,106,209,346,946};
    printf("数组中1的下标:%d\n",binary_search(array,12,1));
    printf("数组中2的下标:%d\n",binary_search(array,12,2));
    printf("数组中6的下标:%d\n",binary_search(array,12,6));
    printf("数组中8的下标:%d\n",binary_search(array,12,8));
    printf("数组中946的下标:%d\n",binary_search(array,12,946));
    printf("数组中209的下标:%d\n",binary_search(array,12,209));
    printf("数组中91的下标:%d\n",binary_search(array,12,91));
    printf("数组中346的下标:%d\n",binary_search(array,12,346));
    printf("数组中346的下标:%d\n",binary_search(array,12,56456));

    return 0;
}
