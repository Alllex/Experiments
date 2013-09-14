#include "stack.h"

typedef struct StackElem
{
    int value;
    struct StackElem *next;
} StackElem;

typedef struct Stack
{
    StackElem *head;
} Stack;

void create(pStack *stack)
{
    *stack = (Stack *) malloc(sizeof(Stack));
    (*stack)->head = NULL;
}

void clear(pStack *stack)
{
    while ((*stack)->head != NULL)
    {
        pop(stack);
    }
}

void push(pStack *stack, const int x)
{
    StackElem *pushing = (StackElem *) malloc(sizeof(StackElem));
    pushing->value = x;
    pushing->next = (*stack)->head;
    (*stack)->head = pushing;
}

int pop(pStack *stack)
{
    if (isEmpty(stack))
    {
        return 0;
    }
    StackElem *current = (*stack)->head;
    int result = current->value;
    StackElem *temp = current->next;
    free(current);
    (*stack)->head = temp;
    return result;
}

int peek(pStack *stack)
{
    return (isEmpty(stack) ? 0 : (*stack)->head->value);
}

int isEmpty(pStack *stack)
{
    return (*stack)->head == NULL;
}
