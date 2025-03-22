// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief B-Tree data structure
 * 
 * A balanced tree data structure that maintains sorted data and allows for
 * efficient insertion, deletion, and search operations.
 */
typedef struct BTree BTree;

/**
 * @brief Creates a new B-Tree with the specified order
 * 
 * @param order The order of the B-Tree (maximum number of children per node)
 * @return A pointer to the newly created B-Tree
 */
BTree *BTree_create(int order);

/**
 * @brief Frees all memory associated with the B-Tree
 * 
 * @param tree The B-Tree to destroy
 */
void BTree_destroy(BTree *tree);

/**
 * @brief Inserts a key-value pair into the B-Tree
 * 
 * @param tree The target B-Tree
 * @param key The key to insert
 * @param value The value associated with the key
 */
void BTree_insert(BTree *tree, int key, int value);

/**
 * @brief Searches for a key in the B-Tree
 * 
 * @param tree The B-Tree to search in
 * @param key The key to search for
 * @return the value if the key exists, NULL_VALUE otherwise
 */
int BTree_search(BTree *tree, int key);

/**
 * @brief Removes a key from the B-Tree
 * 
 * @param tree The B-Tree to remove from
 * @param key The key to remove
 */
void BTree_remove(BTree *tree, int key);

/**
 * @brief Verify if a key exists in the B-Tree
 * 
 * @param tree The B-Tree to search in
 * @param key The key to verify for
 * @return true if the key exists, false otherwise
 */
bool BTree_contains(BTree *tree, int key);

/**
 * @brief Prints the B-Tree in level order (breadth-first traversal)
 * 
 * Outputs each level of the tree on a separate line, with each node's keys
 * enclosed in brackets.
 * 
 * @param tree The B-Tree to print
 * @param outputFile The file to write the output to
 */
void BTree_printLevelOrder(BTree *tree, FILE* outputFile);

#endif //BTREE_H
