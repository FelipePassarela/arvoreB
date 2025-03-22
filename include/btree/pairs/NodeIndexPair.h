// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#ifndef NODEINDEXPAIR_H
#define NODEINDEXPAIR_H

struct BTreeNode; // Forward declaration
typedef struct BTreeNode BTreeNode;

/**
* @brief A structure that pairs a BTreeNode with an index
* 
* This structure is used to store both a node reference and an index position
* within that node, typically for search results that need to identify both
* the node where a key was found and its position within the node.
*/
typedef struct NodeIndexPair NodeIndexPair;

/**
* @brief Creates a new NodeIndexPair
* 
* @param node The BTreeNode to reference
* @param index The index position within the node
* @return A pointer to the newly created NodeIndexPair
*/
NodeIndexPair *NodeIndexPair_create(BTreeNode* node, int index);

/**
* @brief Deallocates memory for a NodeIndexPair
* 
* @param nodeIndex The NodeIndexPair to destroy
*/
void NodeIndexPair_destroy(NodeIndexPair *nodeIndex);

/**
* @brief Gets the BTreeNode from a NodeIndexPair
* 
* @param nodeIndex The NodeIndexPair to get the node from
* @return The BTreeNode pointer stored in the pair
*/
BTreeNode *NodeIndexPair_getNode(NodeIndexPair *nodeIndex);

/**
* @brief Gets the index from a NodeIndexPair
* 
* @param nodeIndex The NodeIndexPair to get the index from
* @return The index value stored in the pair
*/
int NodeIndexPair_getIndex(NodeIndexPair *nodeIndex);

#endif //NODEINDEXPAIR_H