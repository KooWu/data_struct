#ifndef TREE_H
#define TREE_H

typedef struct {
    int val;
    int weight;
    int color;
} TwoTreeData;

typedef struct _tagTwoTreeNode {
    TwoTreeData data;
    struct _tagTwoTreeNode *parent;
    struct _tagTwoTreeNode *leftNode;
    struct _tagTwoTreeNode *rightNode;
} TwoTreeNode;

#endif