#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

int main(void)
{
    //int nodeval[] = {9, 5, 3, 7, 15, 23, 11, 1, 10, 4, 13, 12, 21};
    int nodeval[] = {9, 2, 4, 11, 3, 18, 7, 8, 1, 12, 23, 5, 6, 22};
    //int nodeval[] = {9, 5, 3, 7, 15, 23, 11, 1, 10, 4, 13, 12};
    TwoTreeNode *root = BuildTwoTreeNode(nodeval, sizeof(nodeval) / sizeof(nodeval[0]));
    if (root == NULL) {
        printf("BuildTwoTreeNode failed\n");
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
    #if 1
    TwoTreeNode delNode;
    delNode.data.val = 9;
    bool isDel = DelTwoTreeNode(&root, &delNode);
    if (isDel) {
        PrintTwoTreeNodeThreeRegion(&delNode);
    }
    #endif

    printf("prev order\n");
    PrintTwoTreeNodePrevOrder(root);
    printf("end\n");

    printf("mid order\n");
    PrintTwoTreeNodeMidOrder(root);
    printf("end\n");

    printf("tail order\n");
    PrintTwoTreeNodeTailOrder(root);
    printf("end\n");

    printf("dfs prev order\n");
    DfsTwoTreeNodePrevOrder(root);

    printf("dfs mid order\n");
    DfsTwoTreeNodeMidOrder(root);

    printf("dfs next order\n");
    DfsTwoTreeNodeNextOrder(root);

    printf("bfs\n");
    BfsTwoTreeNode(root);

    GetTwoTreeNodeMidNextNode(root, 6);

    return 0;
}