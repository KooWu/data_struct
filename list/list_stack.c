#include <stdio.h>
#include "comm.h"
#include "list.h"

int InitListStack(ListNode *root, int size)
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

int ReleaseListStack(ListNode *root)
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

int PopListStack(ListNode *root, ListNode *node)
{
    if ((root == NULL) || (node == NULL)) {
        dbg("invalid param");
        return -1;
    }
    if (root->count == 0) {
        dbg("stack is empty");
        return -1;
    }
    root->count--;
    DelHeadListNode(root, node);
    return 0;
}

int PushListStack(ListNode *root, ListNode *node)
{
    if ((root == NULL) || (node == NULL)) {
        dbg("invalid param");
        return -1;
    }
    if (root->count == root->maxSize) {
        dbg("stack is full");
        return -1;
    }
    root->count++;
    InsertHeadListNode(root, node);
    return 0;
}

void TestNodeStack(void)
{
    ListNode root;
    InitListStack(&root, 4);
    ListNode *node = CreateListNode(2);
    PushListStack(&root, node);

    node = CreateListNode(3);
    PushListStack(&root, node);

    node = CreateListNode(4);
    PushListStack(&root, node);

    node = CreateListNode(1);
    PushListStack(&root, node);

    node = CreateListNode(11);
    PushListStack(&root, node);

    node = CreateListNode(11);
    PopListStack(&root, node);
    printf("node->val: %d\n", node->val);

    PrintListNode(&root);
    ReleaseListNode(&root);
}

