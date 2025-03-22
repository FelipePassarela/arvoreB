// Fábio Henrique Pascoal - 2024102901
// Felipe dos Santos Passarela - 2023100256
// Lucas Alexandre Flaneto de Queiroz - 2021101921

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
