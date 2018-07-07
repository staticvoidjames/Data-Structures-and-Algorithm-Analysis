#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 10
#define OK 0
#define ERROR -1

typedef int ElementType;

typedef struct stack
{
    ElementType data[MAX_SIZE];
    int top;
}Stack;

int create(Stack *stack)
{
    stack->top = -1;
    return OK;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

int push(Stack *stack,ElementType x)
{
    if(stack->top == MAX_SIZE - 1)
    {
        return ERROR;
    }
    stack->data[++stack->top] = x;
    return OK;
}

/*Looks at the object at the top of this stack and remove it from the stack.*/
ElementType pop(Stack *stack)
{
    if(isEmpty(stack))
    {
        return ERROR;
    }
    return stack->data[stack->top--];
}


/*Looks at the object at the top of this stack without removing it from the stack.*/
ElementType peek(Stack *stack)
{
    if(isEmpty(stack))
    {
        return ERROR;
    }
    return stack->data[stack->top];
}

int length(Stack *stack)
{
    return stack->top + 1;
}

void print_stack(Stack *stack)
{
    int i;
    if(stack->top == -1)
    {
        puts("空栈");
        return;
    }
    for(i = 0;i <= stack->top;i ++)
    {
        printf("%-4d",stack->data[i]);
    }
    // 换行
    puts("");
}

int clear(Stack *stack)
{
    int i;
    stack->top = -1;
    return OK;
}

int main(int argc, char const *argv[])
{
    int j;
    Stack stack;
    create(&stack);
    for(j=1;j<=10;j++)
    {
        push(&stack,j);
    }

    printf("栈中元素依次为：");
    print_stack(&stack);

    printf("栈长度为:%d\n",length(&stack));
    
    printf("栈顶元素为:%d\n",peek(&stack));
    
    pop(&stack);
    printf("弹出一个元素后栈顶元素为:%d\n",peek(&stack));
    printf("栈长度为:%d\n",length(&stack));

    clear(&stack);
    printf("清除栈后栈长度为:%d\n",length(&stack));
    printf("清除栈后栈,栈是否为空：%d\n",isEmpty(&stack));

    return 0;
}
