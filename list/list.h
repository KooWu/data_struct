#ifndef LIST_H
#define LIST_H

#if 1
#define dbg(fmt, args... ) printf("file[%s], line[%d]: "fmt"\n", __FILE__, __LINE__, ##args);
#else
#define dbg(fmt, msg... )
#endif

#define LIST_MAX_SIZE 50

typedef struct tagListNode {
    int val;
    int count;
    int maxSize;
    struct tagListNode *prev;
    struct tagListNode *next;
} ListNode;

int InitListNode(ListNode *node);
ListNode *CreateListNode(int val);
int InsertHeadListNode(ListNode *root, ListNode *node);
int InsertTailListNode(ListNode *root, ListNode *node);
int DelTailListNode(ListNode *root, ListNode *node);
int DelHeadListNode(ListNode *root, ListNode *node);
void PrintListNode(ListNode *root);
void ReleaseListNode(ListNode *root);

void TestNodeQueue(void);
void TestNodeStack(void);



#endif
