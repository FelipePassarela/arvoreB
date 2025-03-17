//
// Created by Felipe Passarela on 17/03/2025.
//

#include <malloc.h>
#include <stdio.h>
#include "../include/BTreeNode.h"

struct BTreeNode 
{
    int order;
    int numKeys;
    int *keys;
    BTreeNode **children;
    bool isLeaf;
};

BTreeNode *BTreeNode_create(int order, bool isLeaf)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->order = order;
    node->numKeys = 0;
    node->keys = (int *)malloc(sizeof(int) * (2 * order - 1));
    node->children = (BTreeNode **)malloc(sizeof(BTreeNode *) * (2 * order));
    node->isLeaf = isLeaf;

    return node;
}

BTreeNode *BTreeNode_search(BTreeNode *root, int key)
{
    int i = 0;
    while (i < root->numKeys && key > root->keys[i])
        i++;
    
    if (i < root->numKeys && key == root->keys[i])
        return root;

    if (root->isLeaf)
        return NULL;

    return BTreeNode_search(root->children[i], key);
}

void BTreeNode_insertNonFull(BTreeNode *node, int key)
{
    int i = node->numKeys - 1;

    if (node->isLeaf)
    {
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->numKeys++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;

        if (BTreeNode_isFull(node->children[i]))
        {
            BTreeNode_splitChild(node, i, node->children[i]);
            if (key > node->keys[i])
                i++;
        }

        BTreeNode_insertNonFull(node->children[i], key);
    }
}

void BTreeNode_splitChild(BTreeNode *parent, int i, BTreeNode *child)
{
    BTreeNode *newChild = BTreeNode_create(child->order, child->isLeaf);
    newChild->numKeys = child->order - 1;

    for (int j = 0; j < child->order - 1; j++)
        newChild->keys[j] = child->keys[j + child->order];

    if (!child->isLeaf)
        for (int j = 0; j < child->order; j++)
            newChild->children[j] = child->children[j + child->order];
    child->numKeys = child->order - 1;

    for (int j = parent->numKeys; j > i; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = newChild;

    for (int j = parent->numKeys - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = child->keys[child->order - 1];
    parent->numKeys++;
}

void BTreeNode_printInOrder(BTreeNode *root)
{
    if (root != NULL)
    {
        for (int i = 0; i < root->numKeys; i++)
        {
            BTreeNode_printInOrder(root->children[i]);
            printf("%d\n", root->keys[i]);
        }
        BTreeNode_printInOrder(root->children[root->numKeys]);
    }
}

void BTreeNode_destroy(BTreeNode *node)
{
    if (node == NULL)
        return;

    for (int i = 0; i < node->numKeys; i++)
        BTreeNode_destroy(node->children[i]);
    BTreeNode_destroy(node->children[node->numKeys]);
    free(node->keys);
    free(node->children);
    free(node);
}

int BTreeNode_getNumKeys(BTreeNode *node)
{
    return node->numKeys;
}

int BTreeNode_getKeyAt(BTreeNode *node, int i)
{
    return node->keys[i];
}

bool BTreeNode_isLeaf(BTreeNode *node)
{
    return node->isLeaf;
}

bool BTreeNode_isFull(BTreeNode *node)
{
    return node->numKeys == 2 * node->order - 1;
}

BTreeNode *BTreeNode_setChildAt(BTreeNode *node, int i, BTreeNode *child)
{
    BTreeNode *old = node->children[i];
    node->children[i] = child;
    return old;
}

void BTreeNode_printPreOrder(BTreeNode *root, int level)
{
    if (root != NULL)
    {
        for (int i = 0; i < root->numKeys; i++)
        {
            for (int j = 0; j < level; j++)
                printf("   ");
            printf("%d\n", root->keys[i]);
            BTreeNode_printPreOrder(root->children[i], level + 1);
        }
        BTreeNode_printPreOrder(root->children[root->numKeys], level + 1);
    }
}
