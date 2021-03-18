#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int InitListNode(ListNode *node)
{
    node->next = node;
    node->prev = node;

    return 0;
}

ListNode *CreateListNode(int val)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        dbg("malloc failed");
        return NULL;
    }
    node->val = val;
    (void)InitListNode(node);
    return node;
}

int InsertHeadListNode(ListNode *root, ListNode *node)
{
    if ((root == NULL) || (node == NULL)) {
        dbg("invalid param");
        return -1;
    }
    ListNode *rootNext = root->next;

    node->next = rootNext;
    node->prev = root;
    root->next = node;
    rootNext->prev = node;
    return 0;
}

int InsertTailListNode(ListNode *root, ListNode *node)
{
    if ((root == NULL) || (node == NULL)) {
        dbg("invalid param");
        return -1;
    }
    ListNode *rootPrev = root->prev;

    node->next = root;
    node->prev = rootPrev;
    rootPrev->next = node;
    root->prev = node;
    return 0;
}

int DelTailListNode(ListNode *root, ListNode *node)
{
    if ((root == NULL) || (node == NULL)) {
        dbg("invalid param");
        return -1;
    }
    ListNode *rootPrev = root->prev;
    if (rootPrev == root) {
        dbg("list is empty");
        return -1;
    }
    ListNode *rootPrevPrev = root->prev->prev;

    rootPrevPrev->next = root;
    root->prev = rootPrevPrev;
    node->val = rootPrev->val;
    free(rootPrev);
    return 0;
}

int DelHeadListNode(ListNode *root, ListNode *node)
{
    if ((root == NULL) || (node == NULL)) {
        dbg("invalid param");
        return -1;
    }
    ListNode *rootNext = root->next;
    if (rootNext == root) {
        dbg("list is empty");
        return -1;
    }
    ListNode *rootNextNext = root->next->next;

    root->next = rootNextNext;
    rootNextNext->prev = root;
    node->val = rootNext->val;
    free(rootNext);
    return 0;
}

void PrintListNode(ListNode *root)
{
    ListNode *node = root->next;
    for (; node != root; node = node->next) {
        printf("%d->", node->val);
    }
    printf("\n");
}

void ReleaseListNode(ListNode *root)
{
    ListNode *del = NULL;
    ListNode *node = root->next;
    for (; node != root;) {
        del = node;
        node = node->next;
        free(del);
    }
    root->next = root;
    root->prev = root;
}

void TestListNode(void)
{
    ListNode root;
    InitListNode(&root);
    ListNode *node = CreateListNode(2);
    InsertHeadListNode(&root, node);

    node = CreateListNode(3);
    InsertHeadListNode(&root, node);

    node = CreateListNode(4);
    InsertHeadListNode(&root, node);

    node = CreateListNode(1);
    InsertTailListNode(&root, node);

    node = CreateListNode(11);
    InsertTailListNode(&root, node);

    PrintListNode(&root);
    ReleaseListNode(&root);
}

int main(void)
{
    //TestListNode();
    //TestNodeQueue();
    TestNodeStack();
    return 0;
}
