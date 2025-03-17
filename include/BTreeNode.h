#ifndef BTREENODE_H
#define BTREENODE_H

#include <stdbool.h>
#include "Queue.h"

typedef struct BTreeNode BTreeNode;

BTreeNode *BTreeNode_create(int order, bool isLeaf);

void BTreeNode_destroy(BTreeNode *node);


BTreeNode *BTreeNode_search(BTreeNode *root, int key);

BTreeNode* BTreeNode_insert(BTreeNode *node, int key);

BTreeNode* BTreeNode_delete(BTreeNode* root, int key);

void BTreeNode_printInOrder(BTreeNode *root);

void BTreeNode_printPreOrder(BTreeNode *root, int level);


Queue *BTreeNode_getNodes(BTreeNode *root, int totalKeys);

int BTreeNode_getLevel(BTreeNode *node);

int BTreeNode_getNumKeys(BTreeNode *node);

const int* BTreeNode_getKeys(BTreeNode *node);

bool BTreeNode_isLeaf(BTreeNode *node);

bool BTreeNode_isFull(BTreeNode *node);

BTreeNode *BTreeNode_setChildAt(BTreeNode *node, int i, BTreeNode* child);

#endif //BTREENODE_H
