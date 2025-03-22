//
// Created by Felipe Passarela on 21/03/2025.
//

#ifndef BTREENODE_IO_H
#define BTREENODE_IO_H

#include <stdio.h>
#include "BTreeNode.h"

BTreeNode *BTreeNode_diskRead(FILE *file, int nodePos, int order);
void BTreeNode_diskWrite(BTreeNode *node, FILE *file);

#endif //BTREENODE_IO_H
