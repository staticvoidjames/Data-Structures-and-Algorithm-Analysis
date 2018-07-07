
#include<stdio.h>
/*最大子列和问题求解    具体原理参见博客:https://blog.csdn.net/miaoqiucheng/article/details/78181670 */
/*暴力求解方式  时间复杂度为O(n3)*/
int brutal_crack( int data[], int n )
{
    int sum, max_sum = 0;
    int i, j, k;
    for( i = 0; i < n; i++ ) {
        for( j = i; j < n; j++ ) {
            sum = 0;
            for( k = i; k <= j; k++ )
                sum += data[k];
            if( sum > max_sum )
                max_sum = sum;
            }
    }
    return max_sum;
}
/*预处理方式    时间复杂度为O(n2)*/
int preprocess( int data[], int n )
{ 
    int sum, max_sum = 0;
    int i, j;
    for( i = 0; i < n; i++ ) {
        sum = 0;
        for( j = i; j < n; j++ ) {
            sum += data[j];
            if( sum > max_sum )
                max_sum = sum;
            }
    }
    return max_sum;
}

/*求最大子列和的复杂度为O(nlgn)的解法*/
int maxsubsequence(int data[],int start,int end){
    int maxLeft = 0;
    int maxRight = 0;
    int maxborderleft = 0;
    int maxborderright = 0;
    int center = (start + end)/2;
    int i = 0;
    if(start == end){
        return data[start] > 0 ? data[start] : 0;
    }else{
        maxLeft = maxsubsequence(data,start,center);
        maxRight = maxsubsequence(data,center + 1,end);
    }

    int left = 0;
    for(i = center;i >= start; i--){
        left += data[i];
        if(left > maxborderleft){
            maxborderleft = left;
        }
    }
    maxborderleft = maxborderleft > 0 ? maxborderleft : 0;
    int right = 0;
    for(i = center + 1;i <= end; i++){
        right += data[i];
        if(right > maxborderright){
            maxborderright = right;
        }
    }
    maxborderright = maxborderright > 0 ? maxborderright : 0;
    int maxborder = maxborderleft + maxborderright;
    return (maxLeft > maxRight) ? (maxLeft > maxborder ? maxLeft : maxborder):(maxRight > maxborder ? maxRight : maxborder);;
}

/*累积遍历  时间复杂度为O(n)*/
int simple_traverse( int data[], int n )
{ 
    int sum, max_sum;
    int i;
        sum = max_sum = 0;
        for(i = 0; i < n; i++ ) {
            sum += data[i]; /* 向右累加 */
            if( sum > max_sum )
                max_sum = sum; /* 发现更大和则更新当前结果 */
            else if( sum < 0 ) /* 如果当前子列和为负 */
                sum = 0; /* 则不可能使后面的部分和增大，抛弃之 */
}
    return max_sum;
} 

int main(int argc, char const *argv[])
{
    int data[] = {4,-3,5,-2,-1,2,6,-2};
    int result = brutal_crack(data,8);
    printf("%d\n", result);
    result = preprocess(data,8);
    printf("%d\n", result);
    result = maxsubsequence(data,0,7);
    printf("%d\n", result);
    result = simple_traverse(data,8);
    printf("%d\n", result);
    return 0;
}

