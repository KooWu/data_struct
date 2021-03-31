#include <stdio.h>
#include <stdlib.h>
#include "comm.h"
#include "array.h"

int InitArrayStack(ArrayInfo *stack, int size)
{
    if ((stack == NULL) || (size <= 0) || (size > ARRAY_MAX_SIZE)) {
        dbg("invalid param");
        return -1;
    }

    stack->data = (int *)malloc(size *sizeof(int));
    if (stack->data == NULL) {
        dbg("malloc failed");
        return -1;
    }

    stack->count = 0;
    stack->front = 0;
    stack->rear = 0;
    stack->maxSize = size;
    return 0;
}

int ReleaseArrayStack(ArrayInfo *stack)
{
    if (stack == NULL) {
        dbg("invalid param");
        return -1;
    }

    stack->count = 0;
    stack->front = 0;
    stack->rear = 0;
    stack->maxSize = 0;

    if (stack->data != NULL) {
        free(stack->data);
        stack->data = NULL;
    }

    return 0;
}

int PushArrayStack(ArrayInfo *stack, int val)
{
    if ((stack == NULL) || (stack->data == NULL)) {
        dbg("invalid param");
        return -1;
    }

    if (stack->count == stack->maxSize) {
        dbg("stack is full");
        return -1;
    }

    stack->data[stack->count] = val;
    stack->count++;
    return 0;
}

int PopArrayStack(ArrayInfo *stack, int *val)
{
    if ((stack == NULL) || (stack->data == NULL) || (val == NULL)) {
        dbg("invalid param");
        return -1;
    }

    if (stack->count <= 0) {
        dbg("stack is empty");
        return -1;
    }

    *val = stack->data[stack->count - 1];
    stack->count--;
    return 0;
}

void TestArrayStack(void)
{
    ArrayInfo stack;
    int val;
    InitArrayStack(&stack, 4);
    PushArrayStack(&stack, 2);
    PushArrayStack(&stack, 7);
    PushArrayStack(&stack, 9);
    PushArrayStack(&stack, 10);
    PushArrayStack(&stack, 21);
    PopArrayStack(&stack, &val);
    printf("pop val: %d\n", val);
    PopArrayStack(&stack, &val);
    printf("pop val: %d\n", val);
    ReleaseArrayStack(&stack);
}

