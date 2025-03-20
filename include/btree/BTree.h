#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct BTree BTree;

BTree *BTree_create(int order);
void BTree_destroy(BTree *tree);
void BTree_insert(BTree *tree, int key, int value);
bool BTree_search(BTree *tree, int key);
void BTree_remove(BTree *tree, int key);
void BTree_printInOrder(BTree *tree, FILE* outputFile);
void BTree_printPreOrder(BTree *tree);
void BTree_printLevelOrder(BTree *tree, FILE* outputFile);

#endif //BTREE_H
