// Fábio Henrique Pascoal - 2024102901
// Felipe dos Santos Passarela - 2023100256
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <stdbool.h>
#include <stdio.h>
#include "btree/node/BTreeNode.h"
#include "utils/Queue.h"

typedef struct BTreeNode BTreeNode;

BTreeNode *BTreeNode_create(int order, int nodePos, bool isLeaf);
void BTreeNode_destroy(BTreeNode *node);

BTreeNode *BTreeNode_search(BTreeNode *root, int key);
BTreeNode *BTreeNode_insert(BTreeNode *node, int key, int value);
BTreeNode *BTreeNode_remove(BTreeNode *root, int key);

void disk_write(FILE *file, BTreeNode *node);
BTreeNode *disk_read(FILE *file, int nodePos, int order);

bool BTreeNode_isLeaf(BTreeNode *node);
bool BTreeNode_isFull(BTreeNode *node);
bool BTreeNode_isEmpty(BTreeNode *node);

int BTreeNode_getLevel(BTreeNode *node);
int BTreeNode_getOrder(BTreeNode *node);
int BTreeNode_getNumKeys(BTreeNode *node);
const int *BTreeNode_getValues(BTreeNode *node);
const int *BTreeNode_getKeys(BTreeNode *node);

void BTreeNode_printInOrder(BTreeNode *root);
void BTreeNode_printPreOrder(BTreeNode *root, int level);
Queue *BTreeNode_getLevelOrder(BTreeNode *root, int totalKeys);

#endif //BTREE_NODE_H
