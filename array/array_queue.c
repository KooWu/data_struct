#include <stdio.h>
#include <stdlib.h>
#include "comm.h"
#include "array.h"

int InitArrayQueue(ArrayInfo *queue, int size)
{
    if ((queue == NULL) || (size <= 0) || (size > ARRAY_MAX_SIZE)) {
        dbg("invalid param");
        return -1;
    }

    queue->data = (int *)malloc(size *sizeof(int));
    if (queue->data == NULL) {
        dbg("malloc failed");
        return -1;
    }

    queue->count = 0;
    queue->front = 0;
    queue->rear = 0;
    queue->maxSize = size;
    return 0;
}

int ReleaseArrayQueue(ArrayInfo *queue)
{
    if (queue == NULL) {
        dbg("invalid param");
        return -1;
    }

    queue->count = 0;
    queue->front = 0;
    queue->rear = 0;
    queue->maxSize = 0;

    if (queue->data != NULL) {
        free(queue->data);
        queue->data = NULL;
    }

    return 0;
}

int EnArrayQueue(ArrayInfo *queue, int val)
{
    if ((queue == NULL) || (queue->data == NULL)) {
        dbg("invalid param");
        return -1;
    }

    if ((queue->rear + 1) % queue->maxSize == queue->front) {
        dbg("queue is full");
        return -1;
    }

    queue->data[queue->rear] = val;
    queue->rear = (queue->rear + 1) % queue->maxSize;

    return 0;
}

int DeArrayQueue(ArrayInfo *queue, int *val)
{
    if ((queue == NULL) || (queue->data == NULL) || (val == NULL)) {
        dbg("invalid param");
        return -1;
    }

    if (queue->rear == queue->front) {
        dbg("queue is empty");
        return -1;
    }

    *val = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->maxSize;
    return 0;
}

void TestArrayQueue(void)
{
    ArrayInfo queue;
    int val;
    InitArrayQueue(&queue, 4);
    EnArrayQueue(&queue, 2);
    EnArrayQueue(&queue, 7);
    EnArrayQueue(&queue, 9);
    EnArrayQueue(&queue, 10);
    EnArrayQueue(&queue, 21);
    DeArrayQueue(&queue, &val);
    printf("pop val: %d\n", val);
    DeArrayQueue(&queue, &val);
    printf("pop val: %d\n", val);
    ReleaseArrayQueue(&queue);
}

