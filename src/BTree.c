//
// Created by Felipe Passarela on 17/03/2025.
//

#include <malloc.h>
#include "../include/BTree.h"
#include "../include/BTreeNode.h"

struct BTree
{
    BTreeNode *root;
    int order;
};

BTree *BTree_create(int order)
{
    BTree *tree = (BTree *)malloc(sizeof(BTree));
    tree->root = BTreeNode_create(order, true);
    tree->order = order;
    return tree;
}

void BTree_insert(BTree *tree, int key)
{
    BTreeNode *root = tree->root;
    if (BTreeNode_isFull(root))
    {
        BTreeNode *newRoot = BTreeNode_create(tree->order, false);
        BTreeNode_setChildAt(newRoot, 0, root);
        BTreeNode_splitChild(newRoot, 0, root);
        BTreeNode_insertNonFull(newRoot, key);
        tree->root = newRoot;
    }
    else
        BTreeNode_insertNonFull(root, key);
}

bool BTree_search(BTree *tree, int key)
{
    return BTreeNode_search(tree->root, key) != NULL;
}

void BTree_printInOrder(BTree *tree)
{
    BTreeNode_printInOrder(tree->root);
}

void BTree_destroy(BTree *tree)
{
    BTreeNode_destroy(tree->root);
    free(tree);
}

void BTree_printPreOrder(BTree *tree)
{
    BTreeNode_printPreOrder(tree->root, 0);
}
