#include "rTrees.h"
#include "utils.h"

//Swaps two integer variables.
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

// Print the details of an entry
void printEntry(Entry *Entry)
{
    MBR *MBR = Entry->rectangle;
    if(MBR==NULL)
    {
        return;
    }
    printf("\t\tTop Right -> %d,%d\n", MBR->pairX.maxLimit, MBR->pairY.maxLimit);
    printf("\t\tBottom Left -> %d,%d\n", MBR->pairX.minLimit, MBR->pairY.minLimit);
    return;
}

// Find the area of a rectangle
int findArea(MBR *rectangle)
{
    int length=rectangle->pairX.maxLimit-rectangle->pairX.minLimit;
    int breadth=rectangle->pairY.maxLimit-rectangle->pairY.minLimit;
    return length*breadth;
}

//Find the MBR of a node given all its entries
MBR* findMBR(Node* currNode)
{
    int minx=currNode->entries[0]->rectangle->pairX.minLimit;
    int miny=currNode->entries[0]->rectangle->pairY.minLimit;
    int maxx=currNode->entries[0]->rectangle->pairX.maxLimit;
    int maxy=currNode->entries[0]->rectangle->pairY.maxLimit;

    for(int i=1;i<currNode->noOfEntries;i++)
    {
        minx=min(minx,currNode->entries[i]->rectangle->pairX.minLimit);
        miny=min(miny,currNode->entries[i]->rectangle->pairY.minLimit);
        maxx=max(maxx,currNode->entries[i]->rectangle->pairX.maxLimit);
        maxy=max(maxy,currNode->entries[i]->rectangle->pairY.maxLimit);
    }
    
    return createMBR(minx,maxx,miny,maxy);
}

// checks if two rectangles are overlapping
bool isOverlapping(MBR *rect1, MBR *rect2)
{
    if (rect1->pairX.minLimit >= rect2->pairX.maxLimit || rect1->pairX.maxLimit <= rect2->pairX.minLimit)
    {
        return false;
    }
    if (rect1->pairY.minLimit >= rect2->pairY.maxLimit || rect1->pairY.maxLimit <= rect2->pairY.minLimit)
    {
        return false;
    }
    return true;
}