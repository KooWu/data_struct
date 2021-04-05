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

void InitTwoTreeNode(TwoTreeNode *node, int val);
TwoTreeNode *CreateTwoTreeNode(int val);
int InsertTwoTreeNode(TwoTreeNode *root, int val);
TwoTreeNode *BuildTwoTreeNode(int *array, int num);
TwoTreeNode *GetTwoTreeNodeMidNextNode(TwoTreeNode *root, int val);
TwoTreeNode *FindTwoTreeNode(TwoTreeNode *root, int val);
void ResetDelNodeParentInfo(TwoTreeNode *delNode, TwoTreeNode *newNode);
bool DelTwoTreeNode(TwoTreeNode **root, TwoTreeNode *node);
void PrintTwoTreeNodeThreeRegion(const TwoTreeNode *node);
void PrintTwoTreeNodePrevOrder(const TwoTreeNode *root);
void PrintTwoTreeNodeMidOrder(const TwoTreeNode *root);
void PrintTwoTreeNodeTailOrder(const TwoTreeNode *root);
void DfsTwoTreeNodePrevOrder(TwoTreeNode *root);
void DfsTwoTreeNodeMidOrder(TwoTreeNode *root);
void DfsTwoTreeNodeNextOrder(TwoTreeNode *root);
void BfsTwoTreeNode(TwoTreeNode *root);

#endif