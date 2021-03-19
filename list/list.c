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

static void SwapListNextNode(ListNode *node1, ListNode *node2)
{
    ListNode *node1Prev = node1->prev;
    ListNode *node2Next = node2->next;

    node1->next = node2Next;
    node2Next->prev = node1;

    node1Prev->next = node2;
    node2->next = node1;
    node1->prev = node2;
    node2->prev = node1Prev;  
}

void SwapListAdjacentNode(ListNode *node1, ListNode *node2)
{
    if (node1->next == node2) {
        SwapListNextNode(node1, node2);
    } else {
        SwapListNextNode(node2, node1);
    }  
}

void SwapListNode(ListNode *node1, ListNode *node2)
{
    if (node1->next == node2 || node1->prev == node2) {
        return SwapListAdjacentNode(node1, node2);
    }

    ListNode *node1Prev = node1->prev;
    ListNode *node1Next = node1->next;
    ListNode *node2Prev = node2->prev;
    ListNode *node2Next = node2->next;

    node1Prev->next = node2;
    node2->next = node1Next;
    node1Next->prev = node2;
    node2->prev = node1Prev;

    node2Prev->next = node1;
    node1->next = node2Next;
    node2Next->prev = node1;
    node1->prev = node2Prev;
}

void SortListNode(ListNode *root)
{
    ListNode *cur = root;
    ListNode *end = root;
    ListNode *p = NULL;
    for (; cur != root->prev; end = end->prev) {
        for (p = root->next; p != end->prev;) {
            if (p->val > p->next->val) {
                SwapListAdjacentNode(p, p->next);
            } else {
                p = p->next;
            }
        }
        cur = cur->next;
    }
}

void PrintListNode(ListNode *root)
{
    ListNode *node = root->next;
    for (; node != root; node = node->next) {
        printf("%d->", node->val);
    }
    printf("end\n");
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

    ListNode *node1 = CreateListNode(13);
    InsertHeadListNode(&root, node1);

    ListNode *node2 = CreateListNode(4);
    InsertHeadListNode(&root, node2);

    ListNode *node3 = CreateListNode(1);
    InsertHeadListNode(&root, node3);

    PrintListNode(&root);
    SwapListNode(node3, node1);
    PrintListNode(&root);

    node = CreateListNode(5);
    InsertTailListNode(&root, node);

    node = CreateListNode(11);
    InsertTailListNode(&root, node);
    SortListNode(&root);
    PrintListNode(&root);
    ReleaseListNode(&root);
}

int main(void)
{
    TestListNode();
    //TestNodeQueue();
    //TestNodeStack();
    return 0;
}
