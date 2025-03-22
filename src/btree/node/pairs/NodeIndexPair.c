//
// Created by Felipe Passarela on 21/03/2025.
//

#include <stdlib.h>
#include "btree/node/BTreeNode.h"
#include "btree/node/pairs/NodeIndexPair.h"

struct NodeIndexPair
{
    BTreeNode *node;
    int index;
};

NodeIndexPair *NodeIndexPair_create(BTreeNode *node, int index)
{
    NodeIndexPair *nodeKey = (NodeIndexPair *)malloc(sizeof(NodeIndexPair));
    nodeKey->node = node;
    nodeKey->index = index;
    return nodeKey;
}

void NodeIndexPair_destroy(NodeIndexPair *nodeIndex)
{
    free(nodeIndex);
}

BTreeNode *NodeIndexPair_getNode(NodeIndexPair *nodeIndex)
{
    return nodeIndex->node;
}

int NodeIndexPair_getIndex(NodeIndexPair *nodeIndex)
{
    return nodeIndex->index;
}
