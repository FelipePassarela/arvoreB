// Fábio Henrique Pascoal - 2024102901
// Felipe dos Santos Passarela - 2023100256
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#include <assert.h>
#include <stdio.h>
#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_internal.h"

struct BTreeNode 
{
    int order;
    int numKeys;
    int level;
    int nodePos;        // Node's position at the tree considering a level order traversal
    int *keys;
    int *values;
    int *children;
    bool isLeaf;
};

BTreeNode *BTreeNode_create(int order, int nodePos, bool isLeaf)
{
    assert(order >= 2 && "Order must be at least 2");
    
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->keys = (int *)malloc((order - 1) * sizeof(int));
    node->values = (int *)malloc((order - 1) * sizeof(int));
    node->children = (int *)calloc(order, sizeof(int));
    node->order = order;
    node->numKeys = 0;
    node->level = 0;
    node->nodePos = nodePos;
    node->isLeaf = isLeaf;

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

int BTreeNode_getChildPosAt(BTreeNode *node, int i) 
{
    assert(node && "Node cannot be NULL");
    assert(i >= 0 && i <= node->numKeys && "Index out of bounds");
    return node->children[i];
}

int *BTreeNode_getChildrenPos(BTreeNode *node) 
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

void BTreeNode_setChildPosAt(BTreeNode *node, int i, int childPos)
{
    assert(node && "Node cannot be NULL");
    assert(i >= 0 && i < (2 * node->order) && "Index out of bounds");
    
    node->children[i] = childPos;
}

void disk_write(FILE *file, BTreeNode *node)
{
    if (file == NULL || node == NULL) return;

    // Calculate the size of a single node in bytes.
    int nodeSize = sizeof(int) * (3 + 2 * (node->order - 1) + node->order) + sizeof(bool);
    // Move the file pointer to the correct position for writing the node.
    fseek(file, node->nodePos * nodeSize, SEEK_SET);

    // Write the node's data to the file.  Write in the same order as the struct.
    fwrite(&node->order, sizeof(int), 1, file);
    fwrite(&node->numKeys, sizeof(int), 1, file);
    fwrite(&node->level, sizeof(int), 1, file);
    fwrite(&node->isLeaf, sizeof(bool), 1, file);
    fwrite(&node->nodePos, sizeof(int), 1, file);
    fwrite(node->keys, sizeof(int), node->order - 1, file);
    fwrite(node->values, sizeof(int), node->order - 1, file);
    fwrite(node->children, sizeof(int), node->order, file);

    fflush(file); // Ensure data is written to the file.
}

BTreeNode *disk_read(FILE *file, int nodePos, int order)
{
    if (file == NULL) return NULL;
    
    // Calculate the size of a single node in bytes.
    int nodeSize = sizeof(int) * (4 + 2 * (order - 1) + order) + sizeof(bool);
    // Move the file pointer to the position of the node to be read.
    fseek(file, nodePos * nodeSize, SEEK_SET);

    // Allocate memory for a new BTreeNode.
    BTreeNode *node = BTreeNode_create(order, nodePos, false); //isLeaf will be read from file

    // Read the node's data from the file.  Read in the same order as written.
    fread(&node->order, sizeof(int), 1, file);
    fread(&node->numKeys, sizeof(int), 1, file);
    fread(&node->level, sizeof(int), 1, file);
    fread(&node->isLeaf, sizeof(bool), 1, file);
    fread(&node->nodePos, sizeof(int), 1, file);
    fread(node->keys, sizeof(int), order - 1, file);
    fread(node->values, sizeof(int), order - 1, file);
    fread(node->children, sizeof(int), order, file);

    return node;
}
