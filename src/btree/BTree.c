// Felipe dos Santos Passarela - 2023100256

#include <stdlib.h>
#include <stdio.h>
#include "btree/BTree.h"
#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_io.h"

#define BTREE_FILE "btreebinary.txt"

struct BTree
{
    int order;
    int numKeys;
    BTreeNode *root;
    FILE *btreeFile;
};

BTree *BTree_create(int order)
{
    BTree *root = (BTree *)malloc(sizeof(BTree));
    root->order = order;
    root->numKeys = 0;
    root->root = BTreeNode_create(order, true, 0);
    root->btreeFile = fopen(BTREE_FILE, "wb");
    BTreeNode_diskWrite(root->root, root->btreeFile);
    // TODO: Insert first pair
    // BTreeNode_insert()
    // root->numKeys = 1;
    return root;
}

void BTree_destroy(BTree *root)
{
    BTreeNode_destroy(root->root);
    fclose(root->btreeFile);
    free(root);
}

int BTree_search(BTree *root, int key)
{
    NodeIndexPair *nodeIndex = BTreeNode_search(key, BTreeNode_getPos(root->root), root->order, root->btreeFile);
    if (nodeIndex == NULL) return NULL_VALUE;

    BTreeNode *foundNode = NodeIndexPair_getNode(nodeIndex);
    int keyIndex = NodeIndexPair_getIndex(nodeIndex);
    int foundValue = BTreeNode_getValueAt(foundNode, keyIndex);

    NodeIndexPair_destroy(nodeIndex);
    BTreeNode_destroy(foundNode);
    return foundValue;
}
