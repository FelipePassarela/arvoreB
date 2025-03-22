// Felipe dos Santos Passarela - 2023100256

#ifndef BTREENODE_H
#define BTREENODE_H

#include <stdbool.h>
#include <stdio.h>
#include "btree/node/pairs/NodeIndexPair.h"

#define NULL_KEY (-1)
#define NULL_VALUE (-1)
#define NULL_CHILD (-1)

typedef struct BTreeNode BTreeNode;

BTreeNode *BTreeNode_create(int order, bool isLeaf, int diskPos);
void BTreeNode_destroy(BTreeNode *node);

NodeIndexPair *BTreeNode_search(int key, int nodePos, int order, FILE *btreeFile);
void BTreeNode_insert(BTreeNode *node, int key, int value);
void BTreeNode_remove(BTreeNode *root, int key);

bool BTreeNode_isLeaf(BTreeNode *node);
int BTreeNode_getPos(BTreeNode *node);
int BTreeNode_getOrder(BTreeNode *node);
int BTreeNode_getNumKeys(BTreeNode *node);
int *BTreeNode_getKeys(BTreeNode *node);
int *BTreeNode_getValues(BTreeNode *node);
int *BTreeNode_getChildren(BTreeNode *node);
int BTreeNode_getKeyAt(BTreeNode *node, int index);
int BTreeNode_getValueAt(BTreeNode *node, int index);
int BTreeNode_getChildAt(BTreeNode *node, int index);
int BTreeNode_getSize(int order);

void BTreeNode_setIsLeaf(BTreeNode *node, bool isLeaf);
void BTreeNode_setDiskPos(BTreeNode *node, int diskPos);
void BTreeNode_setNumKeys(BTreeNode *node, int numKeys);
void BTreeNode_setKeyAt(BTreeNode *node, int index, int key);
void BTreeNode_setValueAt(BTreeNode *node, int index, int value);
void BTreeNode_setChildAt(BTreeNode *node, int index, int child);

#endif //BTREENODE_H
