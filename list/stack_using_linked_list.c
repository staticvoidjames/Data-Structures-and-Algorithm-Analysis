#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 10
#define OK 0
#define ERROR -1

typedef int ElementType;

typedef struct Node
{
    ElementType data;
    struct Node *next;
}Node;

typedef struct
{
    Node *top;
    int size;
}Stack;

int create(Stack *stack)
{
    stack->top = NULL;
    stack->size = 0;
    return OK;
}

int isEmpty(Stack *stack)
{
    return stack->size == 0;
}

int push(Stack *stack,ElementType x)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = x;
    node->next = stack->top;
    stack->top = node;
    stack->size ++;
    return OK;
}

/*Looks at the object at the top of this stack and remove it from the stack.*/
// 这里用一个地址来接收结果，并不仅是因为需要两个返回数
// 另一个原因就是，栈在弹出一个节点后，会释放原来节点分配的内存空间,如果返回原节点结构内的数据会导致结果可能不正确,
// 这里的地址是用来将需要的结果在内存释放前复制出来到传入的地址中,保证结果的正确性
int pop(Stack *stack,ElementType *element)
{
    Node *first_node = stack->top;
    if (isEmpty(stack))
    {
        *element = ERROR;
        return ERROR;
    }
    stack->top = first_node->next;
    stack->size --;
    *element = first_node->data;
    // 这一步导致必须先将结果复制一份出来
    free(first_node);
    return OK;
}

/*Looks at the object at the top of this stack without removing it from the stack.*/
int peek(Stack *stack,ElementType *element)
{
    if(isEmpty(stack))
    {
        *element = ERROR;
        return ERROR;
    }
    *element = stack->top->data;
    return OK;
}

int length(Stack *stack)
{
    return stack->size;
}

void print_stack(Stack *stack)
{
    Node *node = stack->top;
    if(isEmpty(stack))
    {
        puts("空栈");
        return;
    }
    while(node)
    {
        printf("%-4d", node->data);
        node = node->next;
    }
    // 换行
    puts("");
}

int clear(Stack *stack)
{
    Node *prev = stack->top,*tmp;
    while(prev)
    {
        tmp = prev->next;
        free(prev);
        prev = tmp;
        stack->size --;
    }
    return OK;
}

int main(int argc, char const *argv[])
{
    int j;
    ElementType element;
    Stack stack;
    create(&stack);
    for(j=1;j<=10;j++)
    {
        push(&stack,j);
    }

    printf("栈中元素依次为：");
    print_stack(&stack);
    printf("栈长度为:%d\n",length(&stack));

    peek(&stack,&element);
    printf("栈顶元素为:%d\n",element);
    
    pop(&stack,&element);
    printf("弹出元素为:%d\n",element);
    peek(&stack,&element);
    printf("栈顶元素为:%d\n",element);
    printf("栈长度为:%d\n",length(&stack));

    clear(&stack);
    printf("清除栈后栈长度为:%d\n",length(&stack));
    printf("清除栈后栈,栈是否为空：%d\n",isEmpty(&stack));

    return 0;
}
