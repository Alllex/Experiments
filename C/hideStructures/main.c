#include <stdio.h>

#include "stack.h"

int main(void)
{
    pStack stack;
    int i = 0;
    printf("Hello World!\n");
    create(&stack);
    for (i = 0; i < 10; ++i)
    {
        push(&stack, i + 1);
    }
    for (i = 0; i < 8; ++i)
    {
        printf("%d) %d\n", i + 1, peek(&stack));
        pop(&stack);
    }
    printf("%s\n", (isEmpty(&stack) ? "cleared" : "not empty"));
    clear(&stack);
    printf("%s\n", (isEmpty(&stack) ? "cleared" : "not empty"));
    return 0;
}

