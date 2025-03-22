//
// Created by Felipe Passarela on 21/03/2025.
//

#include "BTreeNode_utils.h"

void BTreeNode_incrementNumKeys(BTreeNode *node, int value)
{
    int newNumKeys = BTreeNode_getNumKeys(node) + value;
    BTreeNode_setNumKeys(node, newNumKeys);
}

void BTreeNode_decrementNumKeys(BTreeNode *node, int value)
{
    int newNumKeys = BTreeNode_getNumKeys(node) - value;
    BTreeNode_setNumKeys(node, newNumKeys);
}

bool BTreeNode_isFull(BTreeNode *node)
{
    return BTreeNode_getNumKeys(node) == (BTreeNode_getOrder(node) - 1);
}

bool BTreeNode_isEmpty(BTreeNode *node)
{
    return BTreeNode_getNumKeys(node) == 0;
}
