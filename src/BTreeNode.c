#include <stdlib.h>
#include <stdio.h>
#include "BTreeNode.h"

struct BTreeNode 
{
    int order;
    int numKeys;
    int *keys;
    BTreeNode **children;
    bool isLeaf;
    int level;
};

static void BTreeNode_insertNonFull(BTreeNode *node, int key);

static void BTreeNode_splitChild(BTreeNode *parent, int i, BTreeNode *child);

static void BTreeNode_deleteInternal(BTreeNode *node, int key);

static void BTreeNode_fill(BTreeNode *node, int idx);

static void BTreeNode_borrowFromPrev(BTreeNode *node, int idx);

static void BTreeNode_borrowFromNext(BTreeNode *node, int idx);

static void BTreeNode_mergeChild(BTreeNode *node, int idx);

static void BTreeNode_updateLevels(BTreeNode *node, int level);

static int BTreeNode_getPredecessor(BTreeNode *node, int idx);

static int BTreeNode_getSuccessor(BTreeNode *node, int idx);

BTreeNode *BTreeNode_create(int order, bool isLeaf)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->order = order;
    node->numKeys = 0;
    node->keys = (int *)malloc(sizeof(int) * (2 * order - 1));
    node->children = (BTreeNode **)malloc(sizeof(BTreeNode *) * (2 * order));
    node->isLeaf = isLeaf;
    node->level = 0;

    return node;
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

BTreeNode* BTreeNode_insert(BTreeNode* node, int key)
{
    if (BTreeNode_isFull(node))
    {
        BTreeNode *newRoot = BTreeNode_create(node->order, false);
        BTreeNode_setChildAt(newRoot, 0, node);
        BTreeNode_splitChild(newRoot, 0, node);
        BTreeNode_insertNonFull(newRoot, key);
        BTreeNode_updateLevels(newRoot, 0);
        return newRoot;
    }
    else
    {
        BTreeNode_insertNonFull(node, key);
        BTreeNode_updateLevels(node, 0);
        return node;
    }
}

BTreeNode* BTreeNode_delete(BTreeNode* root, int key) 
{
    BTreeNode_deleteInternal(root, key);
    // Se a raiz ficar sem chaves, a árvore diminui de altura.
    if (root->numKeys == 0) 
    {
        BTreeNode* newRoot = root->isLeaf ? NULL : root->children[0];
        free(root->keys);
        free(root->children);
        free(root);
        if (newRoot) BTreeNode_updateLevels(newRoot, 0);
        return newRoot;
    }

    BTreeNode_updateLevels(root, 0);
    return root;
}

void BTreeNode_printInOrder(BTreeNode *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < root->numKeys; i++)
    {
        BTreeNode_printInOrder(root->children[i]);
        printf("%d\n", root->keys[i]);
    }
}

void BTreeNode_printPreOrder(BTreeNode *root, int level)
{
    if (root == NULL)
        return;

    for (int i = 0; i < root->numKeys; i++)
    {
        for (int j = 0; j < level; j++)
            printf("   ");
        printf("%d\n", root->keys[i]);
        BTreeNode_printPreOrder(root->children[i], level + 1);
    }
}

Queue* BTreeNode_getNodes(BTreeNode* root, int totalKeys)
{
    Queue *nodeQueue = Queue_create(totalKeys, sizeof(BTreeNode *));
    Queue *result = Queue_create(totalKeys, sizeof(BTreeNode *));
    
    BTreeNode *temp = root;
    Queue_enqueue(nodeQueue, &temp);
    
    while (!Queue_isEmpty(nodeQueue)) 
    {
        BTreeNode *node;
        Queue_dequeue(nodeQueue, &node);
        Queue_enqueue(result, &node);
                
        if (!node->isLeaf) 
        {
            for (int i = 0; i <= node->numKeys; i++) 
            {
                BTreeNode *child = node->children[i];
                Queue_enqueue(nodeQueue, &child);
            }
        }
    }

    Queue_destroy(nodeQueue);
    return result;
}

int BTreeNode_getLevel(BTreeNode* node)
{
    return node->level;
}

int BTreeNode_getNumKeys(BTreeNode* node)
{
    return node->numKeys;
}

const int* BTreeNode_getKeys(BTreeNode* node)
{
    return node->keys;
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

void BTreeNode_deleteInternal(BTreeNode *node, int key) 
{
    int idx = 0;
    while (idx < node->numKeys && node->keys[idx] < key)
        idx++;

    // Se a chave está presente neste nó.
    if (idx < node->numKeys && node->keys[idx] == key) 
    {
        if (node->isLeaf) 
        {
            // Caso 1: nó folha - remove a chave diretamente.
            for (int i = idx; i < node->numKeys - 1; i++)
                node->keys[i] = node->keys[i + 1];
            node->numKeys--;
        } 
        else 
        {
            // Caso 2: nó interno.
            BTreeNode *leftChild = node->children[idx];
            BTreeNode *rightChild = node->children[idx + 1];
            if (leftChild->numKeys >= node->order) 
            {
                int pred = BTreeNode_getPredecessor(node, idx);
                node->keys[idx] = pred;
                BTreeNode_deleteInternal(leftChild, pred);
            } 
            else if (rightChild->numKeys >= node->order) 
            {
                int succ = BTreeNode_getSuccessor(node, idx);
                node->keys[idx] = succ;
                BTreeNode_deleteInternal(rightChild, succ);
            } 
            else 
            {
                BTreeNode_mergeChild(node, idx);
                BTreeNode_deleteInternal(leftChild, key);
            }
        }
    } 
    else 
    {
        // Se a chave não foi encontrada neste nó.
        if (node->isLeaf)
            return; // Chave não presente na árvore.

        bool flag = (idx == node->numKeys);

        if (node->children[idx]->numKeys < node->order)
            BTreeNode_fill(node, idx);
        if (flag && idx > node->numKeys)
            BTreeNode_deleteInternal(node->children[idx - 1], key);
        else
            BTreeNode_deleteInternal(node->children[idx], key);
    }
}

void BTreeNode_fill(BTreeNode *node, int idx) 
{
    if (idx != 0 && node->children[idx - 1]->numKeys >= node->order)
        BTreeNode_borrowFromPrev(node, idx);
    else if (idx != node->numKeys && node->children[idx + 1]->numKeys >= node->order)
        BTreeNode_borrowFromNext(node, idx);
    else 
    {
        if (idx != node->numKeys)
            BTreeNode_mergeChild(node, idx);
        else
            BTreeNode_mergeChild(node, idx - 1);
    }
}

void BTreeNode_borrowFromPrev(BTreeNode *node, int idx) 
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx - 1];

    // Desloca as chaves e filhos do child para a direita.
    for (int i = child->numKeys - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->isLeaf) 
    {
        for (int i = child->numKeys; i >= 0; i--) 
        {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = node->keys[idx - 1];
    if (!child->isLeaf)
        child->children[0] = sibling->children[sibling->numKeys];
    node->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];

    child->numKeys++;
    sibling->numKeys--;
}

void BTreeNode_borrowFromNext(BTreeNode *node, int idx) 
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];

    child->keys[child->numKeys] = node->keys[idx];
    if (!child->isLeaf)
        child->children[child->numKeys + 1] = sibling->children[0];
    node->keys[idx] = sibling->keys[0];

    for (int i = 0; i < sibling->numKeys - 1; i++)
        sibling->keys[i] = sibling->keys[i + 1];

    if (!sibling->isLeaf) 
    {
        for (int i = 0; i < sibling->numKeys; i++) 
        {
            sibling->children[i] = sibling->children[i + 1];
        }
    }
    child->numKeys++;
    sibling->numKeys--;
}

void BTreeNode_mergeChild(BTreeNode *node, int idx) 
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];

    // Une a chave do nó pai com as chaves do sibling.
    child->keys[child->numKeys] = node->keys[idx];

    for (int i = 0; i < sibling->numKeys; i++)
        child->keys[child->numKeys + 1 + i] = sibling->keys[i];

    if (!child->isLeaf) 
    {
        for (int i = 0; i <= sibling->numKeys; i++) 
        {
            child->children[child->numKeys + 1 + i] = sibling->children[i];
        }
    }

    child->numKeys += sibling->numKeys + 1;

    // Remove a referência para sibling neste nó.
    for (int i = idx + 1; i < node->numKeys; i++) 
    {
        node->keys[i - 1] = node->keys[i];
        node->children[i] = node->children[i + 1];
    }
    node->numKeys--;

    free(sibling->keys);
    free(sibling->children);
    free(sibling);
}

void BTreeNode_updateLevels(BTreeNode* node, int level)
{
    node->level = level;
    if (!node->isLeaf)
    {
        for (int i = 0; i <= node->numKeys; i++)
            BTreeNode_updateLevels(node->children[i], level + 1);
    }
}

int BTreeNode_getPredecessor(BTreeNode *node, int idx) 
{
    BTreeNode *current = node->children[idx];
    while (!current->isLeaf)
        current = current->children[current->numKeys];
    return current->keys[current->numKeys - 1];
}

int BTreeNode_getSuccessor(BTreeNode *node, int idx) 
{
    BTreeNode *current = node->children[idx + 1];
    while (!current->isLeaf)
        current = current->children[0];
    return current->keys[0];
}
