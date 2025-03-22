//
// Created by Felipe Passarela on 21/03/2025.
//

#ifndef BTREENODE_UTILS_H
#define BTREENODE_UTILS_H

#include <stdbool.h>
#include "BTreeNode.h"
#include "utils/Queue.h"

void BTreeNode_incrementNumKeys(BTreeNode *node, int value);
void BTreeNode_decrementNumKeys(BTreeNode *node, int value);

bool BTreeNode_isFull(BTreeNode *node);
bool BTreeNode_isEmpty(BTreeNode *node);

void BTreeNode_printInOrder(BTreeNode *root);
void BTreeNode_printPreOrder(BTreeNode *root, int level);
Queue *BTreeNode_getLevelOrder(BTreeNode *root, int totalKeys);

#endif //BTREENODE_UTILS_H
