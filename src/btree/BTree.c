// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#include <stdlib.h>
#include <stdio.h>
#include "btree/BTree.h"
#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_utils.h"
#include "btree/pairs/NodeIndexPair.h"

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

int BTree_search(BTree *tree, int key)
{
    NodeIndexPair *nodeIndex = BTreeNode_search(tree->root, key);
    if (nodeIndex == NULL) return NULL_VALUE;

    BTreeNode *foundNode = NodeIndexPair_getNode(nodeIndex);
    int keyIndex = NodeIndexPair_getIndex(nodeIndex);
    int foundValue = BTreeNode_getValueAt(foundNode, keyIndex);

    NodeIndexPair_destroy(nodeIndex);
    return foundValue;
}

void BTree_remove(BTree *tree, int key)
{
    tree->root = BTreeNode_remove(tree->root, key);
    tree->numKeys--;
}

bool BTree_contains(BTree* tree, int key)
{
    return BTree_search(tree, key) != NULL_VALUE;
}

void BTree_destroy(BTree *tree)
{
    BTreeNode_destroy(tree->root);
    free(tree);
}

void BTree_printLevelOrder(BTree *tree, FILE* outputFile)
{
    int level = 0;
    Queue *nodes = BTreeNode_getLevelOrder(tree->root, tree->numKeys);

    while (!Queue_isEmpty(nodes))
    {
        BTreeNode *node;
        Queue_dequeue(nodes, &node);
        if (BTreeNode_getLevel(node) > level)
        {
            level++;
            fprintf(outputFile, "\n");
        }
        
        const int *keys = BTreeNode_getKeys(node);
        for (int i = 0; i < BTreeNode_getNumKeys(node); i++)
        {
            if (i == 0) fprintf(outputFile, "[");
            fprintf(outputFile, "key: %d, ", keys[i]);
            bool lastIteration = (i == BTreeNode_getNumKeys(node) - 1);
            if (lastIteration) fprintf(outputFile, "]");
        }
    }
    fprintf(outputFile, "\n");
    Queue_destroy(nodes);
}

