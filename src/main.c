// Felipe dos Santos Passarela - 2023100256
// Fábio Henrique Pascoal - 2024102901
// Lucas Alexandre Flaneto de Queiroz - 2021101921

#include <stdio.h>
#include <math.h>
#include "btree/BTree.h"

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
    if (fscanf(input, "%d\n%d\n", &order, &numOps) != 2)
    {
        fprintf(stderr, "Error: Invalid input format\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    int convertedOrder = ceil(order / 2) + 1;
    BTree *tree = BTree_create(convertedOrder);

    for (int i = 0; i < numOps; i++)
    {
        char op;
        char line[256];
        
        if (fgets(line, sizeof(line), input) == NULL)
        {
            fprintf(stderr, "Error: unexpected end of file\n");
            break;
        }

        if (sscanf(line, " %c", &op) != 1)
            continue;

        switch (op)
        {
            case 'I':
            {
                int key, value;
                if (sscanf(line, "I %d, %d", &key, &value) == 2)
                {
                    BTree_insert(tree, key, value);
                }
                break;
            }
            case 'R':
            {
                int key;
                if (sscanf(line, "R %d", &key) == 1)
                {
                    BTree_remove(tree, key);
                }
                break;
            }
            case 'B':
            {
                int key;
                if (sscanf(line, "B %d", &key) == 1)
                {
                    bool found = BTree_contains(tree, key);
                    fprintf(output, "%s\n", found ? 
                        "O REGISTRO ESTA NA ARVORE!" : 
                        "O REGISTRO NAO ESTA NA ARVORE!");
                }
                break;
            }
            default:
                fprintf(stderr, "Unknowns operation: %c\n", op);
                break;
        }
    }

    fprintf(output, "\n-- ARVORE B\n");
    BTree_printLevelOrder(tree, output);

    BTree_destroy(tree);
    fclose(input);
    fclose(output);
    
    return 0;
}