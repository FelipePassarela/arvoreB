// Felipe dos Santos Passarela - 2023100256

#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct BTree BTree;

BTree *BTree_create(int order);
void BTree_destroy(BTree *root);

int BTree_search(BTree *root, int key);

void BTree_printInOrder(BTree *root, FILE* outputFile);
void BTree_printPreOrder(BTree *root);
void BTree_printLevelOrder(BTree *root, FILE* outputFile);

#endif //BTREE_H
