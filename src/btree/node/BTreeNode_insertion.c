// Felipe dos Santos Passarela - 2023100256

#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_internal.h"

void BTreeNode_insertNonFull(BTreeNode *node, int keyToInsert, int valueToInsert)
{
    // Start from rightmost element
    int currentIndex = BTreeNode_getNumKeys(node) - 1;
    
    if (BTreeNode_isLeaf(node))
    {
        while (currentIndex >= 0 && BTreeNode_getKeyAt(node, currentIndex) > keyToInsert)
        {
            // Shift greater elements to the right
            int prevKey = BTreeNode_getKeyAt(node, currentIndex);
            int prevValue = BTreeNode_getValueAt(node, currentIndex);
            BTreeNode_setKeyAt(node, currentIndex + 1, prevKey);
            BTreeNode_setValueAt(node, currentIndex + 1, prevValue);
            currentIndex--;
        }
        
        // Update value if key exists, otherwise insert new key-value pair
        if (currentIndex >= 0 && BTreeNode_getKeyAt(node, currentIndex) == keyToInsert)
        {
            BTreeNode_setValueAt(node, currentIndex, valueToInsert);
        }
        else
        {
            BTreeNode_setKeyAt(node, currentIndex + 1, keyToInsert);
            BTreeNode_setValueAt(node, currentIndex + 1, valueToInsert);
            BTreeNode_incrementNumKeys(node, 1);
        }
    }
    else
    {
        // Find appropriate child to insert the key
        while (currentIndex >= 0 && BTreeNode_getKeyAt(node, currentIndex) > keyToInsert)
        {
            currentIndex--;
        }
        if (currentIndex >= 0 && BTreeNode_getKeyAt(node, currentIndex) == keyToInsert)
        {
            BTreeNode_setValueAt(node, currentIndex, valueToInsert);
            return;
        }
        currentIndex++;
        BTreeNode *targetChild = BTreeNode_getChildAt(node, currentIndex);

        // Handle child split if necessary
        if (BTreeNode_isFull(targetChild))
        {
            BTreeNode_splitChild(node, currentIndex, targetChild);
            bool shouldMoveRight = (BTreeNode_getKeyAt(node, currentIndex) < keyToInsert);
            if (shouldMoveRight) currentIndex++;
        }

        // Recursively insert into appropriate child
        targetChild = BTreeNode_getChildAt(node, currentIndex);
        BTreeNode_insertNonFull(targetChild, keyToInsert, valueToInsert);
    }
}

void BTreeNode_splitChild(BTreeNode *parent, int splitIndex, BTreeNode *child)
{
    int order = BTreeNode_getOrder(parent);
    int mid = order - 1;
    int midKey = BTreeNode_getKeyAt(child, mid);
    int midValue = BTreeNode_getValueAt(child, mid);

    BTreeNode *newChild = BTreeNode_create(order, BTreeNode_isLeaf(child));
    BTreeNode_setNumKeys(newChild, mid);
    
    // Copy upper half of keys to new child
    for (int pos = 0; pos < mid; pos++)
    {
        int key = BTreeNode_getKeyAt(child, pos + mid + 1);
        int value = BTreeNode_getValueAt(child, pos + mid + 1);
        BTreeNode_setKeyAt(newChild, pos, key);
        BTreeNode_setValueAt(newChild, pos, value);
    }
    
    // If internal node, redistribute child pointers
    if (!BTreeNode_isLeaf(child))
    {
        for (int pos = 0; pos < mid + 1; pos++)
        {
            BTreeNode *nextSibling = BTreeNode_getChildAt(child, pos + mid + 1);
            BTreeNode_setChildAt(newChild, pos, nextSibling);
        }
    }
    BTreeNode_setNumKeys(child, mid);
    
    // Make space in parent for new key and child pointer
    for (int pos = BTreeNode_getNumKeys(parent); pos >= splitIndex + 1; pos--) 
    {
        BTreeNode *childAtIndex = BTreeNode_getChildAt(parent, pos);
        BTreeNode_setChildAt(parent, pos + 1, childAtIndex);
    }
    BTreeNode_setChildAt(parent, splitIndex + 1, newChild);
    
    for (int pos = BTreeNode_getNumKeys(parent) - 1; pos >= splitIndex; pos--)
    {
        int prevKey = BTreeNode_getKeyAt(parent, pos);
        int prevValue = BTreeNode_getValueAt(parent, pos);
        BTreeNode_setKeyAt(parent, pos + 1, prevKey);
        BTreeNode_setValueAt(parent, pos + 1, prevValue);
    }
    
    // Move middle key to parent and update counts
    BTreeNode_setKeyAt(parent, splitIndex, midKey);
    BTreeNode_setValueAt(parent, splitIndex, midValue);
    BTreeNode_incrementNumKeys(parent, 1);
}
