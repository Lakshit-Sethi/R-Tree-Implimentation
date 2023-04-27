#include "utils.h"
#include "rTrees.h"
//traversal.c


void traverse(Node *currNode)
{
    if (currNode == NULL)
    {
        return;
    }
    printf("Entering Node %d\n", currNode->index);
    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        printf("\tEntry %d\n", i);
        printEntry(currNode->entries[i]);
        traverse(currNode->entries[i]->childNode);
    }
    printf("Exiting Node %d\n", currNode->index);
    return;
}

//traversal.c
void preOrderTraversal(rTree *tree)
{
    printEntry(tree->start);
    traverse(tree->root);
}
