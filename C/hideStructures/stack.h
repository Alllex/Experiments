#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <malloc.h>

typedef struct Stack *pStack;

void create(pStack *stack);
void clear(pStack *stack);
void push(pStack *stack, const int x);
int pop(pStack *stack);
int peek(pStack *stack);
int isEmpty(pStack *stack);

#endif // STACK_H
