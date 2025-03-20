#include <assert.h>
#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_internal.h"

struct BTreeNode 
{
    int order;
    int numKeys;
    int *keys;
    int *values;
    BTreeNode **children;
    bool isLeaf;
    int level;
};

BTreeNode *BTreeNode_create(int order, bool isLeaf)
{
    assert(order >= 2 && "Order must be at least 2");
    
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->keys = (int *)malloc((2 * order - 1) * sizeof(int));
    node->values = (int *)malloc((2 * order - 1) * sizeof(int));
    node->children = (BTreeNode **)malloc((2 * order) * sizeof(BTreeNode *));
    node->order = order;
    node->numKeys = 0;
    node->level = 0;
    node->isLeaf = isLeaf;

    for (int i = 0; i < 2 * order; i++) 
    {
        node->children[i] = NULL;
    }

    return node;
}

void BTreeNode_destroy(BTreeNode *node)
{
    if (node == NULL) return;

    for (int i = 0; i < node->numKeys; i++)
    {
        BTreeNode_destroy(node->children[i]);
    }

    BTreeNode_destroy(node->children[node->numKeys]);
    free(node->keys);
    free(node->values);
    free(node->children);
    free(node);
}

void BTreeNode_destroyOnly(BTreeNode *node)
{
    if (node == NULL) return;
    free(node->keys);
    free(node->values);
    free(node->children);
    free(node);
}

bool BTreeNode_isLeaf(BTreeNode *node) 
{ 
    assert(node && "Node cannot be NULL");
    return node->isLeaf; 
}

bool BTreeNode_isFull(BTreeNode *node) 
{ 
    assert(node && "Node cannot be NULL");
    return node->numKeys == 2 * node->order - 1; 
}

bool BTreeNode_isEmpty(BTreeNode *node) 
{ 
    assert(node && "Node cannot be NULL");
    return node->numKeys == 0; 
}

int BTreeNode_getLevel(BTreeNode *node) 
{
    assert(node && "Node cannot be NULL");
    return node->level;
}

int BTreeNode_getOrder(BTreeNode *node) 
{
    assert(node && "Node cannot be NULL");
    return node->order;
}

int BTreeNode_getNumKeys(BTreeNode *node) 
{
    assert(node && "Node cannot be NULL");
    return node->numKeys;
}

int BTreeNode_getKeyAt(BTreeNode *node, int i) 
{
    assert(node && "Node cannot be NULL");
    assert(i >= 0 && i < node->numKeys && "Index out of bounds");
    return node->keys[i];
}

int BTreeNode_getValueAt(BTreeNode *node, int i) 
{
    assert(node && "Node cannot be NULL");
    assert(i >= 0 && i < node->numKeys && "Index out of bounds");
    return node->values[i];
}

const int *BTreeNode_getValues(BTreeNode *node) 
{
    assert(node && "Node cannot be NULL");
    return node->values;
}

const int *BTreeNode_getKeys(BTreeNode *node) 
{
    assert(node && "Node cannot be NULL");
    return node->keys;
}

BTreeNode *BTreeNode_getChildAt(BTreeNode *node, int i) 
{
    assert(node && "Node cannot be NULL");
    assert(i >= 0 && i <= node->numKeys && "Index out of bounds");
    return node->children[i];
}

BTreeNode **BTreeNode_getChildren(BTreeNode *node) 
{
    assert(node && "Node cannot be NULL");
    return node->children;
}

void BTreeNode_setLevel(BTreeNode *node, int level)
{ 
    assert(node && "Node cannot be NULL");
    assert(level >= 0 && "Level must be non-negative");
    node->level = level; 
}

void BTreeNode_setNumKeys(BTreeNode *node, int numKeys)
{ 
    assert(node && "Node cannot be NULL");
    assert(numKeys >= 0 && numKeys <= (2 * node->order - 1) && "Invalid number of keys");
    node->numKeys = numKeys; 
}

void BTreeNode_setKeyAt(BTreeNode *node, int i, int key)
{ 
    assert(node && "Node cannot be NULL");
    assert(i >= 0 && i < (2 * node->order - 1) && "Index out of bounds");
    node->keys[i] = key; 
}

void BTreeNode_setValueAt(BTreeNode *node, int i, int value)
{ 
    assert(node && "Node cannot be NULL");
    assert(i >= 0 && i < (2 * node->order - 1) && "Index out of bounds");
    node->values[i] = value; 
}

BTreeNode *BTreeNode_setChildAt(BTreeNode *node, int i, BTreeNode *child)
{
    assert(node && "Node cannot be NULL");
    assert(i >= 0 && i < (2 * node->order) && "Index out of bounds");
    
    BTreeNode *old = node->children[i];
    node->children[i] = child;
    return old;
}
