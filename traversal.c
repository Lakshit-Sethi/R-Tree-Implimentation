#include "utils.h"
#include "rTrees.h"
//traversal.c


void traverse(Node *currNode)
{
    if (currNode == NULL)
    {
        return;
    }
    yellow("Entering Node %d\n", currNode->index);
    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        green("\tEntry %d\n", i);
        printEntry(currNode->entries[i]);
        traverse(currNode->entries[i]->childNode);
    }
    yellow("Exiting Node %d\n", currNode->index);
    return;
}

//traversal.c
void preOrderTraversal(rTree *tree)
{
    printEntry(tree->start);
    traverse(tree->root);
}
