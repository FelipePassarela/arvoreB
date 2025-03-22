// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#ifndef BTREENODE_H
#define BTREENODE_H

#include <stdbool.h>
#include "btree/node/BTreeNode.h"
#include "btree/pairs/NodeIndexPair.h"
#include "utils/Queue.h"

#define NULL_KEY (-1)
#define NULL_VALUE (-1)

/**
* @brief B-Tree node structure
* 
* Represents a single node in a B-Tree, containing keys, values,
* and pointers to child nodes.
*/
typedef struct BTreeNode BTreeNode;

/**
* @brief Creates a new B-Tree node
* 
* @param order The order of the B-Tree (maximum children per node)
* @param isLeaf Whether this node is a leaf node
* @return A pointer to the newly created node
*/
BTreeNode *BTreeNode_create(int order, bool isLeaf);

/**
* @brief Deallocates memory for a B-Tree node and all its children
* 
* @param node The node to destroy
*/
void BTreeNode_destroy(BTreeNode *node);

/**
* @brief Deallocates memory for only a B-Tree node. Children are not affected
*
* @param node The node to destroy
*/
void BTreeNode_destroyOnly(BTreeNode *node);

/**
* @brief Searches for a key in the B-Tree starting from the given node
* 
* @param root The root node to start searching from
* @param key The key to search for
* @return A NodeIndexPair containing the node and index where the key was found, or NULL if not found
*/
NodeIndexPair *BTreeNode_search(BTreeNode *root, int key);

/**
* @brief Inserts a key-value pair into the B-Tree
* 
* @param node The root node to insert into
* @param key The key to insert
* @param value The value associated with the key
* @return The new root node after insertion (may have changed due to splitting)
*/
BTreeNode *BTreeNode_insert(BTreeNode *node, int key, int value);

/**
* @brief Removes a key from the B-Tree
* 
* @param root The root node to remove from
* @param key The key to remove
* @return The new root node after removal (may have changed due to merging)
*/
BTreeNode *BTreeNode_remove(BTreeNode *root, int key);

/**
* @brief Checks if a node is a leaf node
* 
* @param node The node to check
* @return true if the node is a leaf, false otherwise
*/
bool BTreeNode_isLeaf(BTreeNode *node);

/**
* @brief Checks if a node has reached its maximum capacity
* 
* @param node The node to check
* @return true if the node is full, false otherwise
*/
bool BTreeNode_isFull(BTreeNode *node);

/**
* @brief Checks if a node has no keys
* 
* @param node The node to check
* @return true if the node is empty, false otherwise
*/
bool BTreeNode_isEmpty(BTreeNode *node);

/**
* @brief Gets the level of the node in the tree (0 for root)
* 
* @param node The node to get the level of
* @return The level of the node
*/
int BTreeNode_getLevel(BTreeNode *node);

/**
* @brief Gets the order of the B-Tree
* 
* @param node A node in the B-Tree
* @return The order of the B-Tree
*/
int BTreeNode_getOrder(BTreeNode *node);

/**
* @brief Gets the number of keys stored in the node
* 
* @param node The node to get the number of keys from
* @return The number of keys in the node
*/
int BTreeNode_getNumKeys(BTreeNode *node);

/**
* @brief Gets an array of all values stored in the node
* 
* @param node The node to get values from
* @return A pointer to the array of values
*/
const int *BTreeNode_getValues(BTreeNode *node);

/**
* @brief Gets an array of all keys stored in the node
* 
* @param node The node to get keys from
* @return A pointer to the array of keys
*/
const int *BTreeNode_getKeys(BTreeNode *node);

/**
* @brief Gets an array of all children stored in the node
*
* @param node The node to get keys from
* @return A pointer to the array of children
*/
BTreeNode **BTreeNode_getChildren(BTreeNode *node);

/**
* @brief Gets the key at a specific index in the node
* 
* @param node The node to get the key from
* @param i The index of the key
* @return The key at the specified index
*/
int BTreeNode_getKeyAt(BTreeNode *node, int i);

/**
* @brief Gets the value at a specific index in the node
* 
* @param node The node to get the value from
* @param i The index of the value
* @return The value at the specified index
*/
int BTreeNode_getValueAt(BTreeNode *node, int i);

/**
* @brief Gets the child at a specific index in the node
*
* @param node The node to get the value from
* @param i The index of the value
* @return The child at the specified index
*/
BTreeNode *BTreeNode_getChildAt(BTreeNode *node, int i);

/**
* @brief Sets the level of the node
*
* @param node The node to get the value from
* @param level The new level of the node
*/
void BTreeNode_setLevel(BTreeNode *node, int level);

/**
* @brief Sets the number of keys of the the node
*
* @param node The node to get the value from
* @param numKeys The new number of keys
*/
void BTreeNode_setNumKeys(BTreeNode *node, int numKeys);

/**
* @brief Sets a key at a specific index in the node
*
* @param node The node to set the key
* @param i The index to set the key
*/
void BTreeNode_setKeyAt(BTreeNode *node, int i, int key);

/**
* @brief Sets a value at a specific index in the node
*
* @param node The node to set the value
* @param i The index to set the value
*/
void BTreeNode_setValueAt(BTreeNode *node, int i, int value);

/**
* @brief Sets a child at a specific index in the node
*
* @param node The node to set the child
* @param i The index to set the child
*/
BTreeNode *BTreeNode_setChildAt(BTreeNode *node, int i, BTreeNode *child);

#endif //BTREENODE_H