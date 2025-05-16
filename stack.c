#include <stdio.h>
#include <stdlib.h>

#define byte unsigned char
#define SIZE 4

struct stack{
    byte stack[SIZE];
    int top;
};

void initStack(struct stack* stack)
{
    stack->top = -1;
}

void push(struct stack* stack, byte val)
{
    stack->top++;
    if(stack->top < SIZE)
    {
        stack->stack[stack->top] = val;
    }
    else
    {
        printf("STACK OVERFLOW\n");
        stack->top--;
        return;
    }
}

byte pop(struct stack* stack)
{
    if(stack->top > 0)
    {
        byte tmp = stack->stack[stack->top];
        stack->top--;
        return tmp;
    }
    else
    {
        printf("STACK IS EMPTY\n");
        return 0;
    }
}

void printStack(struct stack* Stack)
{
    for(int i = 0; i <= Stack->top; i++)
        printf("%d ", Stack->stack[i]);
    printf("\n");
}

int main()
{
    struct stack Stack;
    initStack(&Stack);
    push(&Stack, 10);
    push(&Stack, 20);
    printf("POPPED VALUE FROM STACK: %d\n", pop(&Stack));
    printStack(&Stack);
    push(&Stack, 100);
    push(&Stack, 255);
    printStack(&Stack);
    push(&Stack, 150);
    push(&Stack, 200);
    printStack(&Stack);
   
    return 0;
}