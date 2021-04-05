#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "comm.h"
#include "array.h"
#include "tree.h"

void InitTwoTreeNode(TwoTreeNode *node, int val)
{
    node->data.val = val;
    node->data.weight = 0;
    node->data.color = 0;
    node->parent = NULL;
    node->leftNode = NULL;
    node->rightNode = NULL;
}

TwoTreeNode *CreateTwoTreeNode(int val)
{
    TwoTreeNode *node = (TwoTreeNode *)malloc(sizeof(TwoTreeNode));
    if (node == NULL) {
        dbg("malloc failed");
        return NULL;
    }
    InitTwoTreeNode(node, val);
    return node;
}

int InsertTwoTreeNode(TwoTreeNode *root, int val)
{
    if (root == NULL) {
        dbg("invalid param");
        return -1;
    }

    TwoTreeNode *node = CreateTwoTreeNode(val);
    if (node == NULL) {
        dbg("CreateTwoTreeNode failed");
        return -1;
    }

    while (1) {
        if (root->data.val > val) {
            if (root->leftNode != NULL) {
                root = root->leftNode;
                continue;
            } else {
                node->parent = root;
                root->leftNode = node;
                break;
            }
        } else {
            if (root->rightNode != NULL) {
                root = root->rightNode;
                continue;
            } else {
                node->parent = root;
                root->rightNode = node;
                break;
            }
        }
    }

    return 0;
}

TwoTreeNode *BuildTwoTreeNode(int *array, int num)
{
    if ((array == NULL) || (num <= 0)) {
        dbg("invalid param");
        return NULL;
    }

    TwoTreeNode *root = CreateTwoTreeNode(array[0]);
    if (root == NULL) {
        dbg("CreateTwoTreeNode root failed");
        return NULL;
    }
    int i;
    int ret;
    for (i = 1; i < num; i++) {
        ret = InsertTwoTreeNode(root, array[i]);
        if (ret != 0) {
            dbg("InsertTwoTreeNode failed");
            return NULL;
        }
    }
    return root;
}

TwoTreeNode *GetTwoTreeNodeMidNextNode(TwoTreeNode *root, int val)
{
    if (root == NULL) {
        dbg("invalid param")
        return NULL;
    }

    TwoTreeNode *cur = FindTwoTreeNode(root, val);
    if (cur == NULL) {
        dbg("not find %d", val);
        return NULL;
    }
    PrintTwoTreeNodeThreeRegion(cur);

    if (cur->rightNode != NULL) {
        cur = cur->rightNode;
        while (1) {
            if (cur->leftNode != NULL) {
                cur = cur->leftNode;
            } else {
                break;
            }
        }
    } else {
        if (cur->parent == NULL) {
            return NULL;
        }
        if (cur->parent->leftNode == cur) {
            cur = cur->parent;
        } else {
            while (1) {
                if (cur == NULL || cur->parent == NULL) {
                    dbg("no next node");
                    return NULL;
                }
                if (cur->parent->leftNode == cur) {
                    cur = cur->parent;
                    break;
                }
                cur = cur->parent;
            }
        }
    }

    printf("cur val: %d\n", cur->data.val);

    return cur;
}

TwoTreeNode *FindTwoTreeNode(TwoTreeNode *root, int val)
{
    if (root == NULL) {
        dbg("invalid param");
        return NULL;
    }
    TwoTreeNode *cur = root;
    while (cur->data.val != val) {
        if (cur->data.val > val) {
            cur = cur->leftNode;
        } else {
            cur = cur->rightNode;
        }
        if (cur == NULL) {
            break;
        }
    }
    return cur;
}

void ResetDelNodeParentInfo(TwoTreeNode *delNode, TwoTreeNode *newNode)
{
    if (delNode->parent->leftNode == delNode) {
        delNode->parent->leftNode = newNode;
    } else {
        delNode->parent->rightNode = newNode;
    }
    if (newNode != NULL) {
        newNode->parent = delNode->parent;
    }
}

bool DelTwoTreeNode(TwoTreeNode **root, TwoTreeNode *node)
{
    TwoTreeNode *delNode = FindTwoTreeNode(*root, node->data.val);
    if (delNode == NULL) {
        dbg("not find node");
        return false;
    }

    *node = *delNode;
    if (delNode->leftNode == NULL && delNode->rightNode == NULL) { //无左右子树
        if (delNode->parent != NULL) {
            ResetDelNodeParentInfo(delNode, NULL);
        } else {
            *root = NULL; //只有根节点
        }
    } else if (delNode->leftNode != NULL && delNode->rightNode == NULL) { //有左子树和无右子树
        if (delNode->parent != NULL) {
            ResetDelNodeParentInfo(delNode, delNode->leftNode);
        } else {
            *root = delNode->leftNode; //根节点
        }
    } else if (delNode->leftNode == NULL && delNode->rightNode != NULL) { //无左子树和有右子树
        if (delNode->parent != NULL) {
            ResetDelNodeParentInfo(delNode, delNode->rightNode);
        } else {
            *root = delNode->rightNode; //根节点
        }
    } else { //左子树和右子树均有
        TwoTreeNode *newNode = delNode->rightNode;
        while (1) {
            if (newNode->leftNode == NULL) {
                break;
            }
            newNode = newNode->leftNode;
        }

        if (newNode->parent != delNode) {
            newNode->parent->leftNode = newNode->rightNode;
        }
        
        if (newNode->rightNode != NULL) {
            newNode->rightNode->parent = newNode->parent;
        }
        if (delNode->parent != NULL) {
            ResetDelNodeParentInfo(delNode, newNode);
        } else {
            *root = newNode; //根节点
        }

        newNode->leftNode = delNode->leftNode;
        delNode->leftNode->parent = newNode;
        if (delNode->rightNode != newNode) {
            newNode->rightNode = delNode->rightNode;
            delNode->rightNode->parent = newNode;
        }
    }
    free(delNode);
    return true;
}

void PrintTwoTreeNodeThreeRegion(const TwoTreeNode *node)
{
    if (node == NULL) {
        dbg("invalid param");
        return;
    }
    printf("cur val: %d\n", node->data.val);
    if (node->parent != NULL) {
        printf("parent val: %d\n", node->parent->data.val);
    } else {
        printf("parent val: nul\n");
    }

    if (node->leftNode != NULL) {
        printf("leftNode val: %d\n", node->leftNode->data.val);
    } else {
        printf("leftNode val: nul\n");
    }

    if (node->rightNode != NULL) {
        printf("rightNode val: %d\n", node->rightNode->data.val);
    } else {
        printf("rightNode val: nul\n");
    }
}

void PrintTwoTreeNodePrevOrder(const TwoTreeNode *root)
{   
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data.val);
    PrintTwoTreeNodePrevOrder(root->leftNode);
    PrintTwoTreeNodePrevOrder(root->rightNode);
}

void PrintTwoTreeNodeMidOrder(const TwoTreeNode *root)
{
    if (root == NULL) {
        return;
    }
    PrintTwoTreeNodeMidOrder(root->leftNode);
    printf("%d ", root->data.val);
    PrintTwoTreeNodeMidOrder(root->rightNode);
}

void PrintTwoTreeNodeTailOrder(const TwoTreeNode *root)
{
    if (root == NULL) {
        return;
    }
    PrintTwoTreeNodeTailOrder(root->leftNode);
    PrintTwoTreeNodeTailOrder(root->rightNode);
    printf("%d ", root->data.val);
}

void DfsTwoTreeNodePrevOrder(TwoTreeNode *root)
{
    if (root == NULL) {
        dbg("invalid root");
        return;
    }
    ArrayInfo stack;
    int ret = InitArrayStack(&stack, 50);
    if (ret != 0) {
        dbg("InitArrayStack failed");
        return;
    }

    int val;
    TwoTreeNode *cur = root;
    while (1) {
        if (cur != NULL) {
            printf("%d ", cur->data.val);
            if (cur->rightNode != NULL) {
                (void)PushArrayStack(&stack, (int)cur->rightNode);
            }
            cur = cur->leftNode;
        } else {
            ret = PopArrayStack(&stack, &val);
            if (ret != 0) {
                break;
            }
            cur = (TwoTreeNode *)val;
        }
    }
    printf("end\n");
    ReleaseArrayStack(&stack);
}

void DfsTwoTreeNodeMidOrder(TwoTreeNode *root)
{
    if (root == NULL) {
        dbg("invalid root");
        return;
    }
    ArrayInfo stack;
    int ret = InitArrayStack(&stack, 50);
    if (ret != 0) {
        dbg("InitArrayStack failed");
        return;
    }

    int val;
    TwoTreeNode *cur = root;
    while (1) {
        if (cur != NULL) {
            (void)PushArrayStack(&stack, (int)cur);
            cur = cur->leftNode;
        } else {
            ret = PopArrayStack(&stack, &val);
            if (ret != 0) {
                break;
            }
            cur = (TwoTreeNode *)val;
            if (cur == NULL) {
                dbg("invalid cur node\n");
                break;
            }
            printf("%d ", cur->data.val);
            cur = cur->rightNode;
        }
    }
    printf("end\n");
    ReleaseArrayStack(&stack);
}

void DfsTwoTreeNodeNextOrder(TwoTreeNode *root)
{
    if (root == NULL) {
        dbg("invalid root");
        return;
    }
    ArrayInfo outputStack;
    int ret = InitArrayStack(&outputStack, 50);
    if (ret != 0) {
        dbg("InitArrayStack failed");
        return;
    }

    ArrayInfo stack;
    ret = InitArrayStack(&stack, 50);
    if (ret != 0) {
        dbg("InitArrayStack failed");
        return;
    }

    int val;
    TwoTreeNode *cur = root;
    while (1) {
        if (cur != NULL) {
            (void)PushArrayStack(&stack, (int)cur);
            (void)PushArrayStack(&outputStack, (int)cur);
            cur = cur->rightNode;
        } else {
            ret = PopArrayStack(&stack, &val);
            if (ret != 0) {
                break;
            }
            cur = (TwoTreeNode *)val;
            if (cur == NULL) {
                dbg("invalid cur node\n");
                break;
            }
            cur = cur->leftNode;
        }
    }
    ReleaseArrayStack(&stack);
    while (1) {
        ret = PopArrayStack(&outputStack, &val);
        if (ret != 0) {
            break;
        }
        cur = (TwoTreeNode *)val;
        if (cur == NULL) {
            dbg("invalid cur node\n");
            break;
        }
        printf("%d ", cur->data.val);
    }
    ReleaseArrayStack(&outputStack);
    
    printf("end\n");    
}

void BfsTwoTreeNode(TwoTreeNode *root)
{
    if (root == NULL) {
        dbg("invalid root");
        return;
    }

    ArrayInfo queue;
    int ret = InitArrayQueue(&queue, 50);
    if (ret != 0) {
        dbg("InitArrayStack failed");
        return;
    }

    EnArrayQueue(&queue, (int)root);
    int val;
    TwoTreeNode *cur = NULL;
    while (1) {
        ret = DeArrayQueue(&queue, &val);
        if (ret != 0) {
            break;
        }
        cur = (TwoTreeNode *)val;
        if (cur == NULL) {
            dbg("invalid cur node");
        }
        printf("%d ", cur->data.val);
        if (cur->leftNode != NULL) {
            EnArrayQueue(&queue, (int)cur->leftNode);
        }

        if (cur->rightNode != NULL) {
            EnArrayQueue(&queue, (int)cur->rightNode);
        }
    }
    ReleaseArrayQueue(&queue);
    
    printf("end\n");
}