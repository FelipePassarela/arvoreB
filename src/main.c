#include <stdio.h>
#include "../include/BTree.h"

int main(void)
{
    BTree *tree = BTree_create(3); // Cria uma B-Tree de ordem 3

    // Insere algumas chaves na árvore
    BTree_insert(tree, 10);
    BTree_insert(tree, 20);
    BTree_insert(tree, 5);
    BTree_insert(tree, 6);
    BTree_insert(tree, 12);
    BTree_insert(tree, 30);
    BTree_insert(tree, 7);
    BTree_insert(tree, 17);

    // Imprime a árvore
    printf("B-Tree:\n");
    BTree_printPreOrder(tree);

    // Busca por algumas chaves
    printf("\nSearching for key 6: %s\n", BTree_search(tree, 6) ? "Found" : "Not Found");
    printf("Searching for key -1: %s\n", BTree_search(tree, -1) ? "Found" : "Not Found");

    // Destroi a árvore
    BTree_destroy(tree);

    return 0;
}