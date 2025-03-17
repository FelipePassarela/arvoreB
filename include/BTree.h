//
// Created by Felipe Passarela on 17/03/2025.
//

#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>

typedef struct BTree BTree;

BTree *BTree_create(int order);

void BTree_insert(BTree *tree, int key);

bool BTree_search(BTree *tree, int key);

void BTree_remove(BTree *tree, int key);

void BTree_printInOrder(BTree *tree);

void BTree_printPreOrder(BTree *tree);

void BTree_destroy(BTree *tree);

#endif //BTREE_H
