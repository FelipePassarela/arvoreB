//
// Created by Felipe Passarela on 17/03/2025.
//

#ifndef BTREENODE_H
#define BTREENODE_H

#include <stdbool.h>

typedef struct BTreeNode BTreeNode;

BTreeNode *BTreeNode_create(int order, bool isLeaf);

BTreeNode *BTreeNode_search(BTreeNode *root, int key);

BTreeNode* BTreeNode_insert(BTreeNode *node, int key);

void BTreeNode_insertNonFull(BTreeNode *node, int key);

void BTreeNode_splitChild(BTreeNode *parent, int i, BTreeNode *child);

BTreeNode* BTreeNode_delete(BTreeNode* root, int key);

void BTreeNode_deleteInternal(BTreeNode *node, int key);

int BTreeNode_getPredecessor(BTreeNode *node, int idx);

int BTreeNode_getSuccessor(BTreeNode *node, int idx);

void BTreeNode_fill(BTreeNode *node, int idx);

void BTreeNode_borrowFromPrev(BTreeNode *node, int idx);

void BTreeNode_borrowFromNext(BTreeNode *node, int idx);

void BTreeNode_mergeChild(BTreeNode *node, int idx);

void BTreeNode_printInOrder(BTreeNode *root);

void BTreeNode_printPreOrder(BTreeNode *root, int level);

void BTreeNode_destroy(BTreeNode *node);

int BTreeNode_getNumKeys(BTreeNode *node);

int BTreeNode_getKeyAt(BTreeNode *node, int i);

bool BTreeNode_isLeaf(BTreeNode *node);

bool BTreeNode_isFull(BTreeNode *node);

BTreeNode *BTreeNode_setChildAt(BTreeNode *node, int i, BTreeNode* child);

#endif //BTREENODE_H
