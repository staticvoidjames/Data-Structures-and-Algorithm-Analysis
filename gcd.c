#include <stdio.h>
#include <stdlib.h>

/* 相关博客:http://blog.jobbole.com/106315/ 
   关于这篇博客,其中有1点点需要纠正:
   1. 文中说更相减损法是对辗转相处法的改进,并说更相减损法是出自《九章算术》，但是维基百科中关于辗转相除法的解释是,
   其在最初提出时就是更相减损法,而辗转相除法更像是更相减损法的变种,或者可以说是改进(在不考虑取模相对减法更复杂这一点外,其减少了计算的次数),
   
   辗转相除法,又名欧几里得算法,最早出现在欧几里得的《几何原本》中（大约公元前300年）,而《九章算术》现今流传的大多是在三国时期魏元帝景元四年（263年）,
   就此可以推论《九章算术》中相关算法比欧几里得提出对应算法时间晚500年左右,这和我们一般认为中国什么东西都比国外早的观念不同。
*/

int gcd_normal(int num1,int num2)
{
    int i;
    int big = num1 > num2 ? num1 : num2;
    int small = num2 < num1 ? num2 : num1;
    if(big % small == 0)
    {
        return small;
    }
    i = small / 2;
    while(1)
    {
        if(small % i == 0 && big % i == 0)
        {
            return i;
        }
        i --;
    }
}

/* 更相减损法 */
int gcd_by_minus(int num1,int num2)
{
    int big = num1 > num2 ? num1 : num2;
    int small = num2 < num1 ? num2 : num1;
    int tmp;
    while(big != small)
    {
        big = big - small;
        if(small > big)
        {
            tmp = big;
            big = small;
            small = tmp;
        }
    }
}

/* 更相减损法(递归实现) */
int gcd_by_minus_with_recursive(int num1,int num2)
{
    if(num1 == num2)
    {
        return num1;
    }
    else if(num1 > num2)
    {
        return gcd_by_minus_with_recursive(num1 - num2,num2);
    }
    else
    {
        return gcd_by_minus_with_recursive(num1,num2 - num1);
    }
}

/* 辗转相除法
   这里的值需要按从大到小的顺序传入
 */
int gcd_by_mod(int big,int small)
{
    int mod;
    do
    {
        mod = big % small;
        big = small;
        small = mod;
    }while(mod);
    return big;
}

/* 辗转相除法
   这里的值需要按从大到小的顺序传入
 */
int gcd_by_mod_with_recursive(int big,int small)
{
    int mod = big % small;
    if(!mod)
    {
        return small;
    }
    else
    {
        return gcd_by_minus(small,mod);
    }
}

/*更相减损术与移位结合：不但避免了取模运算，而且算法性能稳定

当a和b均为偶数，gcb(a,b) = 2*gcb(a/2, b/2) = 2*gcb(a>>1, b>>1)
当a为偶数，b为奇数，gcb(a,b) = gcb(a/2, b) = gcb(a>>1, b)
当a为奇数，b为偶数，gcb(a,b) = gcb(a, b/2) = gcb(a, b>>1)
当a和b均为奇数，利用更相减损术运算一次，gcb(a,b) = gcb(b, a-b),此时a-b必然是偶数，又可以继续进行移位运算。
*/
int gcd_optimize(int num1,int num2)
{
    int flag1 = num1 & 1;// num1为奇数时为1
    int flag2 = num2 & 1;// num2为奇数时为1
    printf("flag1:%d,flag2:%d\n",flag1,flag2);
    if(num1 == num2)
    {
        return num1;
    }
    if(!flag1 && !flag2)
    {
        // 均为偶数
        return gcd_optimize(num1 >> 1,num2 >> 1) << 1;
    }
    else if(flag1 & flag2)
    {
        // 均为奇数
         if(num2 > num1)
         {
             return gcd_optimize(num2,num1);
         }
         return gcd_optimize(num2,num1 - num2);
    }
    else if(flag1)
    {
        // num1为奇数,num2为偶数
        return gcd_optimize(num1,num2 >> 1);
    }
    else
    {
        // num1为偶数,num2为奇数
        return gcd_optimize(num1 >> 1,num2);
    }
}

int main(int argc, char const *argv[])
{
    printf("5和25的最大公约数(暴力求解方式):%d\n",gcd_normal(5,25));
    printf("60和48的最大公约数(暴力求解方式):%d\n",gcd_normal(60,48));
    printf("60和90的最大公约数(暴力求解方式):%d\n",gcd_normal(60,90));
    puts("");

    printf("5和25的最大公约数(更相减损法):%d\n",gcd_by_minus(5,25));
    printf("60和48的最大公约数(更相减损法):%d\n",gcd_by_minus(60,48));
    printf("60和90的最大公约数(更相减损法):%d\n",gcd_by_minus(60,90));
    puts("");

    printf("5和25的最大公约数(更相减损法_递归实现):%d\n",gcd_by_minus(5,25));
    printf("60和48的最大公约数(更相减损法_递归实现):%d\n",gcd_by_minus(60,48));
    printf("60和90的最大公约数(更相减损法_递归实现):%d\n",gcd_by_minus(60,90));
    puts("");

    printf("5和25的最大公约数(辗转相除法):%d\n",gcd_by_mod(25,5));
    printf("60和48的最大公约数(辗转相除法):%d\n",gcd_by_mod(60,48));
    printf("60和90的最大公约数(辗转相除法):%d\n",gcd_by_mod(60,90));
    puts("");

    printf("5和25的最大公约数(辗转相除法_递归实现):%d\n",gcd_by_mod_with_recursive(25,5));
    printf("60和48的最大公约数(辗转相除法_递归实现):%d\n",gcd_by_mod_with_recursive(60,48));
    printf("60和90的最大公约数(辗转相除法_递归实现):%d\n",gcd_by_mod_with_recursive(60,90));
    puts("");

    printf("5和25的最大公约数(更相减损术与移位结合):%d\n",gcd_optimize(5,25));
    printf("60和48的最大公约数(更相减损术与移位结合):%d\n",gcd_optimize(60,48));
    printf("60和90的最大公约数(更相减损术与移位结合):%d\n",gcd_optimize(60,90));
    
    return 0;
}
