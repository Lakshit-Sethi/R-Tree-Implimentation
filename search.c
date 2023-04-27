#include "utils.h"
#include "rTrees.h"

void search_utility(Node *currNode, MBR *rect)
{
    if (currNode == NULL)
    {
        return;
    }
    if(currNode->isLeaf)
    {
        for (int i = 0; i < currNode->noOfEntries; i++)
        {
            if (isOverlapping(currNode->entries[i]->rectangle, rect))
            {
                printf("\t! ");
                printEntry(currNode->entries[i]);
            }
        }
        return;
    }

    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        if (isOverlapping(currNode->entries[i]->rectangle, rect))
        {
            search_utility(currNode->entries[i]->childNode, rect);
        }
    }
    
}

// wrapper function for search_utility
void search(rTree *tree, int minX, int maxX, int minY, int maxY)
{
    if(minX>maxX)
    {
        swap(&minX,&maxX);
    }
    if(minY>maxY)
    {
        swap(&minY,&maxY);
    }
    MBR *search_rect = createMBR(minX, maxX, minY, maxY);
    search_utility(tree->root, search_rect);
}