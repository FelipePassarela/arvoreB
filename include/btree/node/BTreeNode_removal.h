// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#ifndef BTREENODE_REMOVAL_H
#define BTREENODE_REMOVAL_H

#include "btree/node/BTreeNode.h"

/**
* @brief Removes a key from a non-leaf node
*
* This function handles the removal of a key from an internal node in the B-Tree.
*
* @param node The node to remove the key from
* @param keyToRemove The key to be removed
*/
void BTreeNode_removeInternal(BTreeNode *node, int keyToRemove);

/**
* @brief Ensures that a child node has at least the minimum number of keys
*
* This function fills a child node that has fewer than the minimum required
* number of keys by borrowing keys from siblings or merging with a sibling.
*
* @param node The parent node
* @param childIndex The index of the child that needs filling
*/
void BTreeNode_fill(BTreeNode *node, int childIndex);

/**
* @brief Borrows a key from the previous sibling
*
* Moves a key from the previous child of the parent node to the target child.
*
* @param parent The parent node
* @param targetIndex The index of the child that needs a key
*/
void BTreeNode_borrowFromPrev(BTreeNode *parent, int targetIndex);

/**
* @brief Borrows a key from the next sibling
*
* Moves a key from the next child of the parent node to the target child.
*
* @param parent The parent node
* @param targetIndex The index of the child that needs a key
*/
void BTreeNode_borrowFromNext(BTreeNode *parent, int targetIndex);

/**
* @brief Merges a child with its next sibling
*
* Combines the target child with its next sibling, including the separator
* key from the parent.
*
* @param parent The parent node
* @param targetIndex The index of the child to be merged
*/
void BTreeNode_mergeChild(BTreeNode *parent, int targetIndex);

/**
* @brief Finds the predecessor of a key
*
* Gets the largest key that is smaller than the key at the given index.
*
* @param node The node containing the key
* @param idx The index of the key
* @return The predecessor key
*/
int BTreeNode_getPredecessor(BTreeNode *node, int idx);

/**
* @brief Finds the successor of a key
*
* Gets the smallest key that is larger than the key at the given index.
*
* @param node The node containing the key
* @param idx The index of the key
* @return The successor key
*/
int BTreeNode_getSuccessor(BTreeNode *node, int idx);

#endif //BTREENODE_REMOVAL_H