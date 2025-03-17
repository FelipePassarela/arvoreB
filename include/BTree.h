#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include "Queue.h"

typedef struct BTree BTree;

BTree *BTree_create(int order);

void BTree_destroy(BTree *tree);

void BTree_insert(BTree *tree, int key, int value);

bool BTree_search(BTree *tree, int key);

void BTree_remove(BTree *tree, int key);

void BTree_printInOrder(BTree *tree);

void BTree_printPreOrder(BTree *tree);

void BTree_printLevelOrder(BTree *tree);

Queue* BTree_getNodes(BTree *tree);

#endif //BTREE_H
