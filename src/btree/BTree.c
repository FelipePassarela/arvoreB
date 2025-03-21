// Fábio Henrique Pascoal - 2024102901
// Felipe dos Santos Passarela - 2023100256
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#include <stdlib.h>
#include <stdio.h>
#include "btree/BTree.h"
#include "btree/node/BTreeNode.h"

#define FILENAME "binary.exe"
#define BINARY_WRITE "wb"
#define BINARY_READ "rb"

struct BTree
{
    FILE *binaryFileWrite;
    FILE *binaryFileRead;
    BTreeNode *root;
    int order;
    unsigned numKeys;
};

BTree *BTree_create(int order)
{
    BTree *tree = (BTree *)malloc(sizeof(BTree));

    tree->binaryFileWrite = fopen(FILENAME, BINARY_WRITE);
    tree->binaryFileRead = fopen(FILENAME, BINARY_READ);
    tree->root = BTreeNode_create(order, 0, true);
    tree->order = order;
    tree->numKeys = 0;
    
    return tree;
}

void BTree_insert(BTree *tree, int key, int value)
{
    tree->root = BTreeNode_insert(tree->root, key, value);
    tree->numKeys++;
}

bool BTree_search(BTree *tree, int key)
{
    return BTreeNode_search(tree->root, key) != NULL;
}

void BTree_remove(BTree *tree, int key)
{
    tree->root = BTreeNode_remove(tree->root, key);
    tree->numKeys--;
}

void BTree_printInOrder(BTree *tree, FILE* outputFile)
{
    BTreeNode_printInOrder(tree->root);
    printf("\n");
}

void BTree_destroy(BTree *tree)
{
    BTreeNode_destroy(tree->root);
    fclose(tree->binaryFileRead);
    fclose(tree->binaryFileWrite);
    free(tree);
}

void BTree_printPreOrder(BTree *tree)
{
    BTreeNode_printPreOrder(tree->root, 0);
    printf("\n");
}

void BTree_printLevelOrder(BTree *tree, FILE* outputFile)
{
    int level = 0;
    Queue *nodes = BTreeNode_getLevelOrder(tree->root, tree->numKeys);

    while (!Queue_isEmpty(nodes))
    {
        BTreeNode *node;
        Queue_dequeue(nodes, &node);
        if (BTreeNode_getLevel(node) > level)
        {
            level++;
            fprintf(outputFile, "\n");
        }
        
        const int *keys = BTreeNode_getKeys(node);
        for (int i = 0; i < BTreeNode_getNumKeys(node); i++)
        {
            if (i == 0) fprintf(outputFile, "[");
            fprintf(outputFile, "key: %d, ", keys[i]);
            bool lastIteration = (i == BTreeNode_getNumKeys(node) - 1);
            if (lastIteration) fprintf(outputFile, "]");
        }
    }
    fprintf(outputFile, "\n");
    Queue_destroy(nodes);
}

