#include <stdio.h>
#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_internal.h"

void BTreeNode_printInOrder(BTreeNode *root)
{
    if (root == NULL) return;
    
    int numKeys = BTreeNode_getNumKeys(root);
    for (int pos = 0; pos < numKeys; pos++)
    {
        BTreeNode *child = BTreeNode_getChildAt(root, pos);
        BTreeNode_printInOrder(child);

        int key = BTreeNode_getKeyAt(root, pos);
        // int value = BTreeNode_getValueAt(root, i);
        // printf("%d : %d\n", key, value);
        printf("%d ", key);
    }
    BTreeNode *child = BTreeNode_getChildAt(root, numKeys);
    BTreeNode_printInOrder(child);
}

void BTreeNode_printPreOrder(BTreeNode *root, int level)
{
    if (root == NULL) return;
        
    int numKeys = BTreeNode_getNumKeys(root);
    for (int pos = 0; pos < numKeys; pos++)
    {
        for (int i = 0; i < level; i++)
        {
            printf("   ");
        }

        int key = BTreeNode_getKeyAt(root, pos);
        int value = BTreeNode_getValueAt(root, pos);
        printf("%d : %d\n", key, value);

        BTreeNode *child = BTreeNode_getChildAt(root, pos);
        BTreeNode_printPreOrder(child, level + 1);
    }
    BTreeNode *child = BTreeNode_getChildAt(root, numKeys);
    BTreeNode_printPreOrder(child, level + 1);
}

Queue* BTreeNode_getLevelOrder(BTreeNode* root, int totalKeys)
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
                
        if (!BTreeNode_isLeaf(node)) 
        {
            for (int i = 0; i <= BTreeNode_getNumKeys(node); i++) 
            {
                BTreeNode *child = BTreeNode_getChildAt(node, i);
                Queue_enqueue(nodeQueue, &child);
            }
        }
    }

    Queue_destroy(nodeQueue);
    return result;
}

void BTreeNode_updateLevels(BTreeNode* node, int level)
{
    BTreeNode_setLevel(node, level);
    if (!BTreeNode_isLeaf(node))
    {
        for (int pos = 0; pos <= BTreeNode_getNumKeys(node); pos++)
        {
            BTreeNode *child = BTreeNode_getChildAt(node, pos);
            BTreeNode_updateLevels(child, level + 1);
        }
    }
}

void BTreeNode_incrementNumKeys(BTreeNode* node, int value)
{
    int newNumKeys = BTreeNode_getNumKeys(node) + value;
    BTreeNode_setNumKeys(node, newNumKeys);
}

void BTreeNode_decrementNumKeys(BTreeNode* node, int value)
{
    int newNumKeys = BTreeNode_getNumKeys(node) - value;
    BTreeNode_setNumKeys(node, newNumKeys);
}
