#ifndef ARRAY_H
#define ARRAY_H

#if 1
#define dbg(fmt, args... ) printf("file[%s], line[%d]: "fmt"\n", __FILE__, __LINE__, ##args);
#else
#define dbg(fmt, msg... )
#endif

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

#endif