// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#ifndef BTREENODE_UTILS_H
#define BTREENODE_UTILS_H

#include "btree/node/BTreeNode.h"

/**
* @brief Updates the level of all nodes in the tree
*
* @param node The node to start updating from
*/
void BTreeNode_updateLevels(BTreeNode* node, int level);

/**
* @brief Increments the number of keys of the node by a value
*
* @param node The node to start updating from
* @param value The value to increment
*/
void BTreeNode_incrementNumKeys(BTreeNode *node, int value);

/**
* @brief Decrements the number of keys of the node by a value
*
* @param node The node to start updating from
* @param value The value to Decrement
*/
void BTreeNode_decrementNumKeys(BTreeNode *node, int value);

/**
* @brief Prints the keys of the B-Tree in-order (sorted)
*
* @param root The root node to start printing from
*/
void BTreeNode_printInOrder(BTreeNode *root);

/**
* @brief Gets a queue containing all nodes in level order (breadth-first)
*
* @param root The root node to start from
* @param totalKeys The total number of keys in the tree
* @return A queue containing all nodes in level order
*/
Queue *BTreeNode_getLevelOrder(BTreeNode *root, int totalKeys);

#endif //BTREENODE_UTILS_H
