#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "comm.h"
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

TwoTreeNode *GetTwoTreeNodeMidNextNode(const TwoTreeNode *node)
{
    if (node == NULL) {
        dbg("invalid param")
        return NULL;
    }

    TwoTreeNode *cur = node->rightNode;
    while (1) {
        if (cur->leftNode != NULL) {
            cur = cur->leftNode;
        } else {
            break;
        }
    }
    printf("cur val: %d\n", node->data.val);
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
    newNode->parent = delNode->parent;
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
    } else if (delNode->leftNode == NULL && delNode->rightNode != NULL) {  //无左子树和有右子树
        if (delNode->parent != NULL) {
            ResetDelNodeParentInfo(delNode, delNode->rightNode);
        } else {
            *root = delNode->rightNode; //根节点
        }
    } else {  //左子树和右子树均有
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

void BstTwoTreeNodePrevOrder(const TwoTreeNode *root)
{
    if (root == NULL) {
        return;
    }
    PrintTwoTreeNodeTailOrder(root->leftNode);
    PrintTwoTreeNodeTailOrder(root->rightNode);
    printf("%d ", root->data.val);
}

int main(void)
{
    int nodeval[] = {9, 5, 3, 7, 15, 23, 11, 1, 10, 4, 13, 12, 21};
    //int nodeval[] = {9, 5, 3, 7, 15, 23, 11, 1, 10, 4, 13, 12};
    TwoTreeNode *root = BuildTwoTreeNode(nodeval, sizeof(nodeval) / sizeof(nodeval[0]));
    if (root == NULL) {
        dbg("BuildTwoTreeNode failed");
        return 0;
    }
    printf("prev order\n");
    PrintTwoTreeNodePrevOrder(root);
    printf("end\n");

    printf("mid order\n");
    PrintTwoTreeNodeMidOrder(root);
    printf("end\n");

    printf("tail order\n");
    PrintTwoTreeNodeTailOrder(root);
    printf("end\n");

    int val = 16;
    TwoTreeNode *node = FindTwoTreeNode(root, val);
    if (node != NULL) {
        printf("find %d\n", val);
    } else {
        printf("not find %d\n", val);
    }
    TwoTreeNode delNode;
    delNode.data.val = 15;
    bool isDel = DelTwoTreeNode(&root, &delNode);
    if (isDel) {
        PrintTwoTreeNodeThreeRegion(&delNode);
    }

    printf("prev order\n");
    PrintTwoTreeNodePrevOrder(root);
    printf("end\n");

    printf("mid order\n");
    PrintTwoTreeNodeMidOrder(root);
    printf("end\n");

    printf("tail order\n");
    PrintTwoTreeNodeTailOrder(root);
    printf("end\n");
   

    return 0;
}