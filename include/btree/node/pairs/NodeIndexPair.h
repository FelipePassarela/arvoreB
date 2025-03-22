//
// Created by Felipe Passarela on 21/03/2025.
//

#ifndef NODEINDEXPAIR_H
#define NODEINDEXPAIR_H

struct BTreeNode; // Forward declaration
typedef struct BTreeNode BTreeNode;

typedef struct NodeIndexPair NodeIndexPair;

NodeIndexPair *NodeIndexPair_create(BTreeNode* node, int index);
void NodeIndexPair_destroy(NodeIndexPair *nodeIndex);

BTreeNode *NodeIndexPair_getNode(NodeIndexPair *nodeIndex);
int NodeIndexPair_getIndex(NodeIndexPair *nodeIndex);

#endif //NODEINDEXPAIR_H
