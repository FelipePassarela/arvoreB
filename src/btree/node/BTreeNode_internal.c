// Felipe dos Santos Passarela - 2023100256

#include "btree/node/BTreeNode.h"
#include "btree/node/BTreeNode_internal.h"
#include <stdio.h>

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

    BTreeNode *newChild = BTreeNode_create(order, BTreeNode_isLeaf(child));
    BTreeNode_setNumKeys(newChild, mid);

    int midKey = BTreeNode_getKeyAt(child, mid);
    int midValue = BTreeNode_getValueAt(child, mid);
    
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

void BTreeNode_removeInternal(BTreeNode *node, int keyToRemove) 
{
    int currentIndex = 0;
    int numKeys = BTreeNode_getNumKeys(node);
    int order = BTreeNode_getOrder(node);

    // Find the index of the key or where it should be
    while (currentIndex < numKeys && BTreeNode_getKeyAt(node, currentIndex) < keyToRemove) 
    {
        currentIndex++;
    }

    bool keyIsPresentOnNode = (currentIndex < numKeys && BTreeNode_getKeyAt(node, currentIndex) == keyToRemove);
    if (keyIsPresentOnNode) 
    {
        // First case: If the node is a leaf, remove the key by shifting the elements
        if (BTreeNode_isLeaf(node)) 
        {
            for (int pos = currentIndex; pos < numKeys - 1; pos++)
            {
                int nextKey = BTreeNode_getKeyAt(node, pos + 1);
                int nextValue = BTreeNode_getValueAt(node, pos + 1);
                BTreeNode_setKeyAt(node, pos, nextKey);
                BTreeNode_setValueAt(node, pos, nextValue);
            }
            BTreeNode_decrementNumKeys(node, 1);
        } 
        else 
        {
            // Second case: If the node is an internal, handle the left and right children
            BTreeNode *leftChild = BTreeNode_getChildAt(node, currentIndex);
            BTreeNode *rightChild = BTreeNode_getChildAt(node, currentIndex + 1);
            bool leftHasExcessKeys = BTreeNode_getNumKeys(leftChild) > order - 1;
            bool rightHasExcessKeys = BTreeNode_getNumKeys(rightChild) > order - 1;

            if (leftHasExcessKeys) 
            {
                int predecessorKey = BTreeNode_getPredecessor(node, currentIndex);
                BTreeNode_setKeyAt(node, currentIndex, predecessorKey);
                BTreeNode_setValueAt(node, currentIndex, predecessorKey); // TODO: Set value properly
                BTreeNode_removeInternal(leftChild, predecessorKey);
            } 
            else if (rightHasExcessKeys) 
            {
                int successorKey = BTreeNode_getSuccessor(node, currentIndex);
                BTreeNode_setKeyAt(node, currentIndex, successorKey);
                BTreeNode_setValueAt(node, currentIndex, successorKey); // TODO: Set value properly
                BTreeNode_removeInternal(rightChild, successorKey);
            } 
            else 
            {
                // Merge the two child nodes and remove the key in the merge
                BTreeNode_mergeChild(node, currentIndex);
                BTreeNode_removeInternal(leftChild, keyToRemove);
            }
        }
    } 
    else 
    {
        // If the key is not in the node and the node is a leaf, 
        if (BTreeNode_isLeaf(node)) return; // then it is not present in the tree

        BTreeNode *child = BTreeNode_getChildAt(node, currentIndex);
        int childNumKeys = BTreeNode_getNumKeys(child);
        bool notFilled = (childNumKeys < order - 1);
        bool isLastKey = (currentIndex == numKeys);
        bool shouldUsePreviousChild = (isLastKey && currentIndex > numKeys);
        
        if (notFilled)
        {
            BTreeNode_fill(node, currentIndex);
        }
        if (shouldUsePreviousChild)
        {
            child = BTreeNode_getChildAt(node, currentIndex - 1);
            BTreeNode_removeInternal(child, keyToRemove);
        }
        else
        {
            child = BTreeNode_getChildAt(node, currentIndex);
            BTreeNode_removeInternal(child, keyToRemove);
        }
    }
}

void BTreeNode_fill(BTreeNode *node, int childIndex) 
{
    int minKeys = BTreeNode_getOrder(node) - 1;
    int numKeys = BTreeNode_getNumKeys(node);
    bool hasPrevSibling = (childIndex > 0);
    bool hasNextSibling = (childIndex < numKeys);

    if (hasPrevSibling)
    {
        BTreeNode *prevSibling = BTreeNode_getChildAt(node, childIndex - 1);
        bool prevCanBorrow = BTreeNode_getNumKeys(prevSibling) > minKeys;
        if (prevCanBorrow) BTreeNode_borrowFromPrev(node, childIndex);
    }
    else if (hasNextSibling)
    {
        BTreeNode *nextSibling = BTreeNode_getChildAt(node, childIndex + 1);
        bool nextCanBorrow = BTreeNode_getNumKeys(nextSibling) > minKeys;
        if (nextCanBorrow) BTreeNode_borrowFromNext(node, childIndex);
    }
    else 
    {
        if (hasNextSibling) BTreeNode_mergeChild(node, childIndex);
        else                BTreeNode_mergeChild(node, childIndex - 1);
    }
}

void BTreeNode_borrowFromPrev(BTreeNode *parent, int targetIndex) 
{
    BTreeNode *targetChild = BTreeNode_getChildAt(parent, targetIndex);
    BTreeNode *leftSibling = BTreeNode_getChildAt(parent, targetIndex - 1);

    // Shift all keys in target child to make space for the new key
    for (int pos = BTreeNode_getNumKeys(targetChild) - 1; pos >= 0; pos--)
    {
        int prevKey = BTreeNode_getKeyAt(targetChild, pos);
        BTreeNode_setKeyAt(targetChild, pos + 1, prevKey);
    }

    // If not leaf, shift all child pointers to right and transfer last child from sibling
    if (!BTreeNode_isLeaf(targetChild)) 
    {
        for (int pos = BTreeNode_getNumKeys(targetChild); pos >= 0; pos--) 
        {
            BTreeNode *prevChild = BTreeNode_getChildAt(targetChild, pos);
            BTreeNode_setChildAt(targetChild, pos + 1, prevChild);
        }
        BTreeNode *lastSibChild = BTreeNode_getChildAt(leftSibling, BTreeNode_getNumKeys(leftSibling));
        BTreeNode_setChildAt(targetChild, 0, lastSibChild);
    }

    // Move the parent's key down to the target child's first position
    int parentKey = BTreeNode_getKeyAt(parent, targetIndex - 1);
    int parentValue = BTreeNode_getValueAt(parent, targetIndex - 1);
    BTreeNode_setKeyAt(targetChild, 0, parentKey);
    BTreeNode_setValueAt(targetChild, 0, parentValue);
  
    // Move the sibling's last key up to the parent
    int sibNumKeys = BTreeNode_getNumKeys(leftSibling) - 1;
    int lastSibKey = BTreeNode_getKeyAt(leftSibling, sibNumKeys);
    int lastSibValue = BTreeNode_getValueAt(leftSibling, sibNumKeys);
    BTreeNode_setKeyAt(parent, targetIndex - 1, lastSibKey);
    BTreeNode_setValueAt(parent, targetIndex - 1, lastSibValue);

    BTreeNode_incrementNumKeys(targetChild, 1);
    BTreeNode_decrementNumKeys(leftSibling, 1);
}

void BTreeNode_borrowFromNext(BTreeNode *parent, int targetIndex) 
{
    BTreeNode *targetChild = BTreeNode_getChildAt(parent, targetIndex);
    BTreeNode *rightSibling = BTreeNode_getChildAt(parent, targetIndex + 1);

    // Moves the parent key to the last position of the target child
    int parentKey = BTreeNode_getKeyAt(parent, targetIndex);
    int parentValue = BTreeNode_getValueAt(parent, targetIndex);
    BTreeNode_setKeyAt(targetChild, BTreeNode_getNumKeys(targetChild), parentKey);
    BTreeNode_setValueAt(targetChild, BTreeNode_getNumKeys(targetChild), parentValue);

    // If it isn't a leaf, move the first child of sibling
    if (!BTreeNode_isLeaf(targetChild)) 
    {
        BTreeNode *firstSibChild = BTreeNode_getChildAt(rightSibling, 0);
        BTreeNode_setChildAt(targetChild, BTreeNode_getNumKeys(targetChild) + 1, firstSibChild);
    }

    // Move the first key from sibling to parent
    int firstSibKey = BTreeNode_getKeyAt(rightSibling, 0);
    int firstSibValue = BTreeNode_getValueAt(rightSibling, 0);
    BTreeNode_setKeyAt(parent, targetIndex, firstSibKey);
    BTreeNode_setValueAt(parent, targetIndex, firstSibValue);

    // Shift all sibling keys to the left
    for (int pos = 0; pos < BTreeNode_getNumKeys(rightSibling) - 1; pos++)
    {
        int nextKey = BTreeNode_getKeyAt(rightSibling, pos + 1);
        int nextValue = BTreeNode_getValueAt(rightSibling, pos + 1);
        BTreeNode_setKeyAt(rightSibling, pos, nextKey);
        BTreeNode_setValueAt(rightSibling, pos, nextValue);
    }

    // If it isn't a leaf, shift all sibling children to the left
    if (!BTreeNode_isLeaf(rightSibling))
    {
        for (int pos = 0; pos < BTreeNode_getNumKeys(rightSibling); pos++)
        {
            BTreeNode *nextChild = BTreeNode_getChildAt(rightSibling, pos + 1);
            BTreeNode_setChildAt(rightSibling, pos, nextChild);
        }
    }

    BTreeNode_incrementNumKeys(targetChild, 1);
    BTreeNode_decrementNumKeys(rightSibling, 1);
}

void BTreeNode_mergeChild(BTreeNode *parent, int targetIndex) 
{
    BTreeNode *leftChild = BTreeNode_getChildAt(parent, targetIndex);
    BTreeNode *rightChild = BTreeNode_getChildAt(parent, targetIndex + 1);
    int order = BTreeNode_getOrder(leftChild);

    // Move parent's key to the middle position of left child
    int parentKey = BTreeNode_getKeyAt(parent, targetIndex);
    int parentValue = BTreeNode_getValueAt(parent, targetIndex);
    BTreeNode_setKeyAt(leftChild, order - 1, parentKey);
    BTreeNode_setValueAt(leftChild, order - 1, parentValue);

    // Copy all keys and values from right child to left child
    for (int pos = 0; pos < BTreeNode_getNumKeys(rightChild); pos++)
    {
        int rightKey = BTreeNode_getKeyAt(rightChild, pos);
        int rightValue = BTreeNode_getValueAt(rightChild, pos);
        BTreeNode_setKeyAt(leftChild, order + pos, rightKey);
        BTreeNode_setValueAt(leftChild, order + pos, rightValue);
    }

    // If nodes aren't leaves, transfer child pointers
    if (!BTreeNode_isLeaf(leftChild)) 
    {
        for (int pos = 0; pos <= BTreeNode_getNumKeys(rightChild); pos++)
        {
            BTreeNode *rightChildPtr = BTreeNode_getChildAt(rightChild, pos);
            BTreeNode_setChildAt(leftChild, order + pos, rightChildPtr);
        }
    }

    // Shift keys and values in parent to fill the gap
    for (int pos = targetIndex + 1; pos < BTreeNode_getNumKeys(parent); pos++)
    {
        int nextKey = BTreeNode_getKeyAt(parent, pos);
        int nextValue = BTreeNode_getValueAt(parent, pos);
        BTreeNode_setKeyAt(parent, pos - 1, nextKey);
        BTreeNode_setValueAt(parent, pos - 1, nextValue);
    }

    // Shift child pointers in parent to remove right child reference
    for (int pos = targetIndex + 2; pos <= BTreeNode_getNumKeys(parent); pos++)
    {
        BTreeNode *nextChild = BTreeNode_getChildAt(parent, pos);
        BTreeNode_setChildAt(parent, pos - 1, nextChild);
    }
    
    BTreeNode_incrementNumKeys(leftChild, BTreeNode_getNumKeys(rightChild) + 1);
    BTreeNode_decrementNumKeys(parent, 1);

    BTreeNode_destroyOnly(rightChild);
}

int BTreeNode_getPredecessor(BTreeNode *parent, int childIndex) 
{
    // Keep moving to the rightmost child until reaching a leaf
    BTreeNode *current = BTreeNode_getChildAt(parent, childIndex);
    while (!BTreeNode_isLeaf(current))
    {
        int lastChildIndex = BTreeNode_getNumKeys(current);
        current = BTreeNode_getChildAt(current, lastChildIndex);
    }
    int lastKeyIndex = BTreeNode_getNumKeys(current) - 1;
    return BTreeNode_getKeyAt(current, lastKeyIndex);
}

int BTreeNode_getSuccessor(BTreeNode *parent, int childIndex) 
{
    // Keep moving to the leftmost child until reaching a leaf
    BTreeNode *current = BTreeNode_getChildAt(parent, childIndex + 1);
    while (!BTreeNode_isLeaf(current))
    {
        current = BTreeNode_getChildAt(current, 0);
    }
    return BTreeNode_getKeyAt(current, 0);
}
