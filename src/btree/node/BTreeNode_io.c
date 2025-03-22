//
// Created by Felipe Passarela on 21/03/2025.
//

#include "BTreeNode_io.h"

BTreeNode *BTreeNode_diskRead(FILE *file, int nodePos, int order)
{
    int nodeSize = BTreeNode_getSize(order);
    fseek(file, nodePos * nodeSize, SEEK_SET);

    int diskPos;
    int nodeOrder;
    int numKeys;
    bool isLeaf;
    int *keys;
    int *values;
    int *children;

    fread(&diskPos, sizeof(int), 1, file);
    fread(&nodeOrder, sizeof(int), 1, file);
    fread(&numKeys, sizeof(int), 1, file);
    fread(&isLeaf, sizeof(bool), 1, file);
    fread(keys, sizeof(int), order - 1, file);
    fread(values, sizeof(int), order - 1, file);
    fread(children, sizeof(int), order, file);

    BTreeNode *node = BTreeNode_create(order, isLeaf, diskPos);
    BTreeNode_setNumKeys(node, numKeys);

    for (int i = 0; i < order - 1; ++i)
    {
        BTreeNode_setKeyAt(node, i, keys[i]);
        BTreeNode_setValueAt(node, i, values[i]);
    }
    for (int i = 0; i < order; ++i)
    {
        BTreeNode_setChildAt(node, i, children[i]);
    }

    return node;
}

void BTreeNode_diskWrite(BTreeNode *node, FILE *file)
{
    int nodeSize = BTreeNode_getSize(BTreeNode_getOrder(node));
    fseek(file, BTreeNode_getPos(node) * nodeSize, SEEK_SET);

    int diskPos = BTreeNode_getPos(node);
    int order = BTreeNode_getOrder(node);
    int numKeys = BTreeNode_getNumKeys(node);
    bool isLeaf = BTreeNode_isLeaf(node);
    int *keys = BTreeNode_getKeys(node);
    int *values = BTreeNode_getValues(node);
    int *children = BTreeNode_getChildren(node);

    fwrite(&diskPos, sizeof(int), 1, file);
    fwrite(&order, sizeof(int), 1, file);
    fwrite(&numKeys, sizeof(int), 1, file);
    fwrite(&isLeaf, sizeof(bool), 1, file);
    fwrite(keys, sizeof(int), order - 1, file);
    fwrite(values, sizeof(int), order - 1, file);
    fwrite(children, sizeof(int), order, file);
}
