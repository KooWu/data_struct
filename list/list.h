#ifndef LIST_H
#define LIST_H

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

int InitListStack(ListNode *root, int size);
int ReleaseListStack(ListNode *root);
int PopListStack(ListNode *root, ListNode *node);
int PushListStack(ListNode *root, ListNode *node);

int InitListQueue(ListNode *root, int size);
int ReleaseListQueue(ListNode *root);
int DeListQueue(ListNode *root, ListNode *node);
int EnListQueue(ListNode *root, ListNode *node);

#endif
