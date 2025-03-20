// Felipe dos Santos Passarela - 2023100256

#ifndef BTREE_NODE_INTERNAL_H
#define BTREE_NODE_INTERNAL_H

#include "btree/node/BTreeNode.h"

void BTreeNode_destroyOnly(BTreeNode *node);

int BTreeNode_getKeyAt(BTreeNode *node, int i);
int BTreeNode_getValueAt(BTreeNode *node, int i);
BTreeNode *BTreeNode_getChildAt(BTreeNode *node, int i);
BTreeNode **BTreeNode_getChildren(BTreeNode *node);
int BTreeNode_getPredecessor(BTreeNode *node, int idx);
int BTreeNode_getSuccessor(BTreeNode *node, int idx);

void BTreeNode_setLevel(BTreeNode *node, int level);
void BTreeNode_setNumKeys(BTreeNode *node, int numKeys);
void BTreeNode_setKeyAt(BTreeNode *node, int i, int key);
void BTreeNode_setValueAt(BTreeNode *node, int i, int value);
BTreeNode *BTreeNode_setChildAt(BTreeNode *node, int i, BTreeNode *child);

void BTreeNode_incrementNumKeys(BTreeNode *node, int value);
void BTreeNode_decrementNumKeys(BTreeNode *node, int value);
void BTreeNode_updateLevels(BTreeNode* node, int level);

void BTreeNode_insertNonFull(BTreeNode *node, int keyToInsert, int valueToInsert);
void BTreeNode_splitChild(BTreeNode *parent, int splitIndex, BTreeNode *child);
void BTreeNode_removeInternal(BTreeNode *node, int keyToRemove);
void BTreeNode_fill(BTreeNode *node, int childIndex);
void BTreeNode_borrowFromPrev(BTreeNode *parent, int targetIndex);
void BTreeNode_borrowFromNext(BTreeNode *parent, int targetIndex);
void BTreeNode_mergeChild(BTreeNode *parent, int targetIndex);

#endif