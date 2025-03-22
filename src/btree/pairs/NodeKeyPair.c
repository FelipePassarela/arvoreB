// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#include <stdlib.h>
#include "btree/node/BTreeNode.h"
#include "btree/pairs/NodeIndexPair.h"

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