#ifndef ARRAY_H
#define ARRAY_H

#define ARRAY_MAX_SIZE 50

typedef struct {
    int front;
    int rear;
    int count;
    int maxSize;
    int *data;
} ArrayInfo;

void TestArrayStack(void);
void TestArrayQueue(void);

int InitArrayStack(ArrayInfo *stack, int size);
int ReleaseArrayStack(ArrayInfo *stack);
int PushArrayStack(ArrayInfo *stack, int val);
int PopArrayStack(ArrayInfo *stack, int *val);

int InitArrayQueue(ArrayInfo *queue, int size);
int ReleaseArrayQueue(ArrayInfo *queue);
int EnArrayQueue(ArrayInfo *queue, int val);
int DeArrayQueue(ArrayInfo *queue, int *val);

#endif