#include "utils.h"
#include "rTrees.h"

void search_utility(Node *currNode, MBR *search_rect)
{
    if (currNode == NULL)
    {
        return;
    }
    if(currNode->isLeaf)
    {
        for (int i = 0; i < currNode->noOfEntries; i++)
        {
            if (isOverlapping(currNode->entries[i]->rectangle, search_rect))
            {
                green("!");
                printEntry(currNode->entries[i]);
            }
        }
        return;
    }

    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        if (isOverlapping(currNode->entries[i]->rectangle, search_rect))
        {
            search_utility(currNode->entries[i]->childNode, search_rect);
        }
    }
    
}

// wrapper function for search_utility
void search(rTree *tree, int minX, int maxX, int minY, int maxY)
{
    blue("[Entering Search]\n")
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
    blue("[Exiting Search]\n")
}