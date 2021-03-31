#include <stdio.h>
#include "comm.h"
#include "list.h"

int InitListQueue(ListNode *root, int size)
{
    if ((root == 0) || (size == 0) || (size > LIST_MAX_SIZE)) {
        dbg("invalid param");
        return -1;
    }
    root->count = 0;
    root->maxSize = size;
    InitListNode(root);
    return 0;
}

int ReleaseListQueue(ListNode *root)
{
    if (root == 0) {
        dbg("invalid param");
        return -1;
    }
    ReleaseListNode(root);
    root->maxSize = 0;
    root->count = 0;
    return 0;
}

int DeListQueue(ListNode *root, ListNode *node)
{
    if ((root == NULL) || (node == NULL)) {
        dbg("invalid param");
        return -1;
    }
    if (root->count == 0) {
        dbg("queue is empty");
        return -1;
    }
    root->count--;
    DelHeadListNode(root, node);
    return 0;
}

int EnListQueue(ListNode *root, ListNode *node)
{
    if ((root == NULL) || (node == NULL)) {
        dbg("invalid param");
        return -1;
    }
    if (root->count == root->maxSize) {
        dbg("queue is full");
        return -1;
    }
    root->count++;
    InsertTailListNode(root, node);
    return 0;
}

void TestNodeQueue(void)
{
    ListNode root;
    InitListQueue(&root, 4);
    ListNode *node = CreateListNode(2);
    EnListQueue(&root, node);

    node = CreateListNode(3);
    EnListQueue(&root, node);

    node = CreateListNode(4);
    EnListQueue(&root, node);

    node = CreateListNode(1);
    EnListQueue(&root, node);

    node = CreateListNode(11);
    EnListQueue(&root, node);

    node = CreateListNode(11);
    DeListQueue(&root, node);
    printf("node->val: %d\n", node->val);

    PrintListNode(&root);
    ReleaseListNode(&root);
}