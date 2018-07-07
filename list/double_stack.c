#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define OK 1
#define ERROR -1

typedef int ElementType;

typedef struct{
    ElementType data[MAXSIZE];
    int top1,top2;
}DoubleStack;

// 这里的命名还是应该为InitStack,不为create,因为我们并没有在这里动态分配内存来创建一个栈
// 只是对一个已经分配了空间的栈进行初始化而已
int InitStack(DoubleStack *stack)
{
    stack->top1 = -1;
    stack->top2 = MAXSIZE;
    return OK;
}

int is_empty(DoubleStack *stack,int tag)
{
    if(tag == 1)
    {
        return stack->top1 == -1;
    }
    else if(tag == 2)
    {
        return stack->top2 == MAXSIZE;
    }
    return ERROR;
}

int is_full(DoubleStack *stack)
{
    return stack->top1 + 1 == stack->top2;
}

int push(DoubleStack *stack,ElementType x,int tag)
{
	if (is_full(stack))
    {
        return ERROR;
    }
    if (tag == 1)
    {
        stack->data[++stack->top1] = x;
    }
    else if (tag == 2)
    {
        stack->data[--stack->top2] = x;
    }else{
        return ERROR;
    }
    return OK;
}

ElementType pop(DoubleStack *stack,int tag)
{
    if (is_empty(stack,tag))
    {
        puts("栈为空");
        return ERROR;
    }
    if (tag == 1)
    {
        return stack->data[stack->top1--];
    }
    else if (tag == 2)
    {
        return stack->data[stack->top2++];
    }
    return ERROR;
}

void print_stack(DoubleStack *stack,int tag)
{
    if ((tag == 1 && stack->top1 == -1) || (tag == 2 && stack->top2 == MAXSIZE))
    {
        puts("stack is empty");
        return;
    }
    switch(tag)
    {
        case 1:
            {
                for (int i = 0; i <= stack -> top1; i++)
                {
                    printf("%4d", stack->data[i]);
                }
            }
        break;
        case 2:
            {
                for (int i = MAXSIZE - 1; i > stack -> top2; i--)
                {
                    printf("%4d", stack->data[i]);
                }
            }
        break;
    }
    puts("");
}

int main()
{
        int j;
        DoubleStack stack;
        InitStack(&stack);
        for (int i = 0; i < 5; ++i)
        {
            push(&stack,i,1);
            push(&stack,i,2);
        }
        printf("栈1是否为空:%d\n", is_empty(&stack,1));
        printf("栈2是否为空:%d\n", is_empty(&stack,2));
		printf("栈是否已满:%d\n", is_full(&stack));

        puts("push数据后");
        puts("栈1的内容,bottom->top");
        print_stack(&stack,1);
        puts("栈1的内容,bottom->top");
        print_stack(&stack,2);

        printf("栈1弹出数据:%d\n",pop(&stack,1));
        printf("栈1弹出数据:%d\n",pop(&stack,1));
        printf("栈1弹出数据:%d\n",pop(&stack,1));
        printf("栈1弹出数据:%d\n",pop(&stack,1));
        printf("栈1弹出数据:%d\n",pop(&stack,1));

        printf("栈2弹出数据:%d\n",pop(&stack,2));
        printf("栈2弹出数据:%d\n",pop(&stack,2));
        printf("栈2弹出数据:%d\n",pop(&stack,2));
        printf("栈2弹出数据:%d\n",pop(&stack,2));
        printf("栈2弹出数据:%d\n",pop(&stack,2));
        
        return 0;
}