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

    int t = (order) / 2 + (order % 2 == 0);
    BTree *tree = BTree_create(t);

    for (int i = 0; i < numOps; i++)
    {
        char op;
        fscanf(input, "%c ", &op);

        switch (op)
        {
            case 'I':
            {
                int key, value;
                fscanf(input, "%d, %d\n", &key, &value);
                BTree_insert(tree, key, value);
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
                break;
            }
            default:
                break;
        }
    }

    fprintf(output, "\n-- ARVORE B\n");
    BTree_printLevelOrder(tree, output);
    // BTree_printInOrder(tree, output);

    BTree_destroy(tree);
    fclose(input);
    fclose(output);
    
    return 0;
}