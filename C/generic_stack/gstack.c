/*
 * =====================================================================================
 *
 *       Filename:  gstack.c
 *
 *    Description:  Pure C Stack Library for any kind of data
 *
 *        Version:  1.0
 *        Created:  19/01/15 11:01:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  alllex 
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct {
	void *items;
	int size;
	int capacity;
	int itemSize;
	void (*freefn)(void *);	
} Stack;

void StackNew(Stack *stack, int itemSize, void (*freefn)(void *));
void StackDelete(Stack *stack);
char StackIsEmpty(Stack *stack);
void StackPush(Stack *stack, void *item);
void StackPop(Stack *stack, void *src);
static void StackGrow(Stack *stack);

void testInt()
{
	Stack stack;
	int t = 1;
	int num = 1;
	StackNew(&stack, sizeof(int), NULL);
	StackPush(&stack, &num); num = 2;
	StackPush(&stack, &num); num = 3;	
	StackPush(&stack, &num); num = 4;	
	StackPop(&stack, &t);
	printf("%d\n", t);
	StackPush(&stack, &num); num = 5;	
	StackPush(&stack, &num); num = 6;	
	StackPush(&stack, &num); 
	StackPop(&stack, &t);
	printf("%d\n", t);
	printf("Stack: size(%d), capacity(%d), itemSize(%d)\n", 
		stack.size, stack.capacity, stack.itemSize);
	StackDelete(&stack);
}

void StrFree(void *p)
{
	printf("Delete one string: %s\n", *(char **)p);
	free(*(char **)p);
}

void testStr()
{
	Stack s;
	char *str;
	int i = 0;
	StackNew(&s, sizeof(char *), StrFree);
	str = strdup("Alllex"); 
	StackPush(&s, &str);
	str = strdup("Mary");
	StackPush(&s, &str);
	str = strdup("Hello, world!");
	StackPush(&s, &str);
	for (i = 0; i < 2; i++) {
		StackPop(&s, &str);
		printf("%s\n", str);
		free(str);
	}	
	printf("Stack: size(%d), capacity(%d), itemSize(%d)\n", 
		s.size, s.capacity, s.itemSize);
	StackDelete(&s);
}

int main() 
{
	testInt();
	testStr();
	return 0;
}

void StackNew(Stack *stack, int itemSize, 
		void (*freefn)(void *))
{
	stack->size = 0;
	stack->capacity = 4;
	stack->itemSize = itemSize;
	stack->items = malloc(stack->capacity * itemSize);
	stack->freefn = freefn;
}

void StackDelete(Stack *stack)
{
	int i = 0;
	if (NULL != stack->freefn) {
		for (i = 0; i < stack->size; i++) {
			void *p = (char *)stack->items + 
					i * stack->itemSize;
			stack->freefn(p);
		}
	}	
	free(stack->items);
}

char StackIsEmpty(Stack *stack)
{
	return 0 == stack->size;
}

void StackPush(Stack *stack, void *item)
{
	if (stack->size == stack->capacity)
		StackGrow(stack);
	void *target = (char *)stack->items +
			stack->size * stack->itemSize;
	memcpy(target, item, stack->itemSize);
	stack->size++;
}

static void StackGrow(Stack *stack)
{
	stack->capacity *= 2;
	stack->items = realloc(stack->items, 
			stack->capacity * stack->itemSize);
}

void StackPop(Stack *stack, void *src)
{
	if (StackIsEmpty(stack)) {
		src = NULL;
		return;
	}
	void *tgt = (char *)stack->items +
			(--stack->size) * stack->itemSize;
	memcpy(src, tgt, stack->itemSize);
}

