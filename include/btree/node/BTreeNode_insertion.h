//
// Created by Felipe Passarela on 21/03/2025.
//

#ifndef BTREENODE_INSERTION_H
#define BTREENODE_INSERTION_H

#include "btree/node/BTreeNode.h"

void BTreeNode_insertNonFull(BTreeNode *node, int keyToInsert, int valueToInsert);
void BTreeNode_splitChild(BTreeNode *parent, int splitIndex, BTreeNode *child);

#endif //BTREENODE_INSERTION_H
