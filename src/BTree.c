#include <stdlib.h>
#include <stdio.h>
#include "BTree.h"
#include "BTreeNode.h"

struct BTree
{
    BTreeNode *root;
    int order;
    unsigned numKeys;
};

BTree *BTree_create(int order)
{
    BTree *tree = (BTree *)malloc(sizeof(BTree));
    tree->root = BTreeNode_create(order, true);
    tree->order = order;
    tree->numKeys = 0;
    return tree;
}

void BTree_insert(BTree *tree, int key, int value)
{
    tree->root = BTreeNode_insert(tree->root, key, value);
    tree->numKeys++;
}

bool BTree_search(BTree *tree, int key)
{
    return BTreeNode_search(tree->root, key) != NULL;
}

void BTree_remove(BTree *tree, int key)
{
    tree->root = BTreeNode_delete(tree->root, key);
    tree->numKeys--;
}

void BTree_printInOrder(BTree *tree)
{
    BTreeNode_printInOrder(tree->root);
}

void BTree_destroy(BTree *tree)
{
    BTreeNode_destroy(tree->root);
}

void BTree_printPreOrder(BTree *tree)
{
    BTreeNode_printPreOrder(tree->root, 0);
}

void BTree_printLevelOrder(BTree *tree)
{
    Queue *nodes = BTree_getNodes(tree);
    int level = 0;
    while (!Queue_isEmpty(nodes))
    {
        
        BTreeNode *node;
        Queue_dequeue(nodes, &node);
        if (BTreeNode_getLevel(node) > level)
        {
            level++;
            printf("\n");
        }
        
        const int *keys = BTreeNode_getKeys(node);
        for (int i = 0; i < BTreeNode_getNumKeys(node); i++)
        {
            if (i == 0) printf("[");
            printf("key: %d, ", keys[i]);
            if (i == BTreeNode_getNumKeys(node) - 1) printf("l=%d]", BTreeNode_getLevel(node));
        }
    }
    printf("\n");
}

Queue* BTree_getNodes(BTree* tree)
{
    return BTreeNode_getNodes(tree->root, tree->numKeys);
}
