// TDOO: Put name and matriculation in all files

#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "BTreeNode.h"
#include "Queue.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (input == NULL)
    {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }

    if (output == NULL)
    {
        printf("Error: could not open file %s\n", argv[2]);
        return 1;
    }

    int order, numOps;
    fscanf(input, "%d\n%d\n", &order, &numOps);

    BTree *tree = BTree_create(order);

    for (int i = 0; i < numOps; i++)
    {
        char op;
        fscanf(input, "%c ", &op);

        switch (op)
        {
            case 'I':
            {
                int key1, key2;
                fscanf(input, "%d, %d\n", &key1, &key2);
                BTree_insert(tree, key1);
                BTree_insert(tree, key2);
                break;
            }
            case 'R':
            {
                int key;
                fscanf(input, "%d\n", &key);
                BTree_remove(tree, key);
                break;
            }
            case 'B':
            {
                int key;
                fscanf(input, "%d\n", &key);
                bool found = BTree_search(tree, key);
                char *msg = found ? "O REGISTRO ESTA NA ARVORE!\n" : "O REGISTRO NAO ESTA NA ARVORE!\n";
                fprintf(output, "%s", msg);
                printf("%s", msg); // TODO: Remove this line
                break;
            }
            default:
                break;
        }
    }

    //     -- ARVORE B
    // [key: 51, key: 75, ]
    // [key: 20, key: 40, key: 45, ][key: 55, key: 60, key: 62, ][key: 77, ]

    printf("-- ARVORE B\n");  // TODO: Remove this line
    fprintf(output, "-- ARVORE B\n");

    int level = 0;
    Queue *nodes = BTree_getNodes(tree);
    while (!Queue_isEmpty(nodes))
    {
        BTreeNode *node;
        Queue_dequeue(nodes, &node);
        
        printf("[");  // TODO: Remove this line
        fprintf(output, "[");

        for (int i = 0; i < BTreeNode_getNumKeys(node); i++)
        {
            printf("key: %d, ", BTreeNode_getKeys(node)[i]);
            fprintf(output, "key: %d, ", BTreeNode_getKeys(node)[i]);
        }

        printf(" l=%d]", level);  // TODO: Remove this line
        fprintf(output, " l=%d]\n", level);  // Keeping output for level

        if (BTreeNode_getLevel(node) > level)
        {
            level = BTreeNode_getLevel(node);
            printf("\n");  // TODO: Remove this line
            fprintf(output, "\n");
        }
    }
    
    fprintf(output, "\n");

    BTree_destroy(tree);
    Queue_destroy(nodes);
    fclose(input);
    fclose(output);
    
    return 0;
}