// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#ifndef BTREENODE_INSERTION_H
#define BTREENODE_INSERTION_H

#include "btree/node/BTreeNode.h"

/**
* @brief Inserts a key-value pair into a non-full node
*
* This function handles the insertion of a key-value pair into a node that is
* not at maximum capacity. If the node is a leaf, it directly inserts the key;
* otherwise, it recursively inserts into the appropriate child.
*
* @param node The node to insert into (must not be full)
* @param keyToInsert The key to be inserted
* @param valueToInsert The value associated with the key
*/
void BTreeNode_insertNonFull(BTreeNode *node, int keyToInsert, int valueToInsert);

/**
* @brief Splits a child node that has reached maximum capacity
*
* When a child node becomes full, this function splits it into two nodes and
* moves the middle key up to the parent. This is a key operation that maintains
* the B-Tree property during insertion.
*
* @param parent The parent node
* @param splitIndex The index of the child to be split
* @param child The child node to be split (must be full)
*/
void BTreeNode_splitChild(BTreeNode *parent, int splitIndex, BTreeNode *child);

#endif //BTREENODE_INSERTION_H