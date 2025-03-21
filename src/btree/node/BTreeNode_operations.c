// Felipe dos Santos Passarela - 2023100256

#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_internal.h"

BTreeNode *BTreeNode_search(BTreeNode *root, int keyToFind)
{
    int currentIndex = 0;
    int numKeys = BTreeNode_getNumKeys(root);

    // TODO: Implement binary search
    while (currentIndex < numKeys && keyToFind > BTreeNode_getKeyAt(root, currentIndex)) 
    {
        currentIndex++;
    }
    
    bool keyFound = (currentIndex < numKeys && keyToFind == BTreeNode_getKeyAt(root, currentIndex));
    if (keyFound) return root;

    if (BTreeNode_isLeaf(root)) return NULL;

    BTreeNode* targetChild = BTreeNode_getChildAt(root, currentIndex);
    return BTreeNode_search(targetChild, keyToFind);
}

BTreeNode* BTreeNode_insert(BTreeNode *node, int key, int value)
{
    if (BTreeNode_isFull(node))
    {
        int order = BTreeNode_getOrder(node);
        BTreeNode *newRoot = BTreeNode_create(order, false);
        BTreeNode_setChildAt(newRoot, 0, node);
        BTreeNode_splitChild(newRoot, 0, node);
        BTreeNode_insertNonFull(newRoot, key, value);
        BTreeNode_updateLevels(newRoot, 0);
        return newRoot;
    }
    else
    {
        BTreeNode_insertNonFull(node, key, value);
        BTreeNode_updateLevels(node, 0);
        return node;
    }
}

BTreeNode* BTreeNode_remove(BTreeNode *root, int key) 
{
    BTreeNode_removeInternal(root, key);
    if (BTreeNode_isEmpty(root)) 
    {
        BTreeNode* newRoot = BTreeNode_isLeaf(root) ? NULL : BTreeNode_getChildAt(root, 0);
        BTreeNode_destroyOnly(root);
        if (newRoot) BTreeNode_updateLevels(newRoot, 0);
        return newRoot;
    }

    BTreeNode_updateLevels(root, 0);
    return root;
}

