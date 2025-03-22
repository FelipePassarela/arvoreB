//
// Created by Felipe Passarela on 21/03/2025.
//

#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_io.h"
#include "btree/node/pairs/NodeIndexPair.h"

#include <assert.h>
#include <stdlib.h>

struct BTreeNode
{
    int pos;
    int order;
    int numKeys;
    bool isLeaf;
    int *keys;
    int *values;
    int *children;
};

BTreeNode *BTreeNode_create(int order, bool isLeaf, int diskPos)
{
    assert(order >= 2 && "Order must be at least 2");

    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->keys = (int *)malloc((order - 1) * sizeof(int));
    node->values = (int *)malloc((order - 1) * sizeof(int));
    node->children = (int *)malloc(order * sizeof(BTreeNode *));

    node->pos = diskPos;
    node->order = order;
    node->numKeys = 0;
    node->isLeaf = isLeaf;

    for (int i = 0; i < order - 1; ++i)
    {
        node->keys[i] = NULL_KEY;
        node->values[i] = NULL_VALUE;
    }
    for (int i = 0; i < order; ++i)
    {
        node->children[i] = NULL_CHILD;
    }

    return node;
}

void BTreeNode_destroy(BTreeNode *node)
{
    if (node == NULL) return;
    free(node->keys);
    free(node->values);
    free(node->children);
    free(node);
}

NodeIndexPair *BTreeNode_search(int key, int nodePos, int order, FILE *btreeFile)
{
    BTreeNode *node = BTreeNode_diskRead(btreeFile, nodePos, order);
    if (node == NULL) return NULL;
    int numKeys = BTreeNode_getNumKeys(node);

    // TODO: Implement binary search
    int currentIndex = 0;
    while (currentIndex < numKeys && key > BTreeNode_getKeyAt(node, currentIndex))
    {
        currentIndex++;
    }

    bool keyFound = (currentIndex < numKeys && key == BTreeNode_getKeyAt(node, currentIndex));
    if (keyFound) return NodeIndexPair_create(node, currentIndex);

    bool keyNotInTree = BTreeNode_isLeaf(node);
    if (keyNotInTree)
    {
        BTreeNode_destroy(node);
        return NULL;
    }

    int childPos = BTreeNode_getChildAt(node, currentIndex);
    BTreeNode_destroy(node);
    return BTreeNode_search(key, childPos, order, btreeFile);
}

bool BTreeNode_isLeaf(BTreeNode *node)
{
    return node->isLeaf;
}

int BTreeNode_getPos(BTreeNode *node)
{
    return node->pos;
}

int BTreeNode_getOrder(BTreeNode *node)
{
    return node->order;
}

int BTreeNode_getNumKeys(BTreeNode *node)
{
    return node->numKeys;
}

int *BTreeNode_getKeys(BTreeNode *node)
{
    return node->keys;
}

int *BTreeNode_getValues(BTreeNode *node)
{
    return node->values;
}

int *BTreeNode_getChildren(BTreeNode *node)
{
    return node->children;
}

int BTreeNode_getKeyAt(BTreeNode *node, int index)
{
    return node->keys[index];
}

int BTreeNode_getValueAt(BTreeNode *node, int index)
{
    return node->values[index];
}

int BTreeNode_getChildAt(BTreeNode *node, int index)
{
    return node->children[index];
}

int BTreeNode_getSize(int order)
{
    int sizeArrays = (2 * (order - 1) + order) * sizeof(int);
    int sizeNode = sizeArrays + 3 * sizeof(int) + sizeof(bool);
    return sizeNode;
}

void BTreeNode_setIsLeaf(BTreeNode *node, bool isLeaf)
{
    node->isLeaf = isLeaf;
}

void BTreeNode_setDiskPos(BTreeNode *node, int diskPos)
{
    node->pos = diskPos;
}

void BTreeNode_setNumKeys(BTreeNode *node, int numKeys)
{
    node->numKeys = numKeys;
}

void BTreeNode_setKeyAt(BTreeNode *node, int index, int key)
{
    node->keys[index] = key;
}

void BTreeNode_setValueAt(BTreeNode *node, int index, int value)
{
    node->values[index] = value;
}

void BTreeNode_setChildAt(BTreeNode *node, int index, int child)
{
    node->children[index] = child;
}
