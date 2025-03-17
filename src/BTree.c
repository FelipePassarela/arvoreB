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
    tree->root = BTreeNode_insert(tree->root, key);
}

bool BTree_search(BTree *tree, int key)
{
    return BTreeNode_search(tree->root, key) != NULL;
}

void BTree_remove(BTree *tree, int key)
{
    tree->root = BTreeNode_delete(tree->root, key);
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
