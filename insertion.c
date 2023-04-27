#include "rTrees.h"
#include "utils.h"

//TODO:memory leak

// choose the most optimal leaf node to insert the new rectangle
Node *chooseLeaf(Node *currNode, MBR *newrectangle)
{
    if (currNode->isLeaf)
    {
        return currNode;
    }
    int minArea = INF;
    int minIndex = 0;
    int minCurrArea = INF;
    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        int currArea = findArea(currNode->entries[i]->rectangle);

        int minx=min(currNode->entries[i]->rectangle->pairX.minLimit,newrectangle->pairX.minLimit);
        int miny=min(currNode->entries[i]->rectangle->pairY.minLimit,newrectangle->pairY.minLimit);
        int maxx=max(currNode->entries[i]->rectangle->pairX.maxLimit,newrectangle->pairX.maxLimit);
        int maxy=max(currNode->entries[i]->rectangle->pairY.maxLimit,newrectangle->pairY.maxLimit);
        MBR* newRect=createMBR(minx,maxx,miny,maxy);
        
        int newArea = findArea(newRect);
        int diffArea = newArea - currArea;
        int minCurrArea = min(minCurrArea, currArea);
        
        if (diffArea < minArea)
        {
            minArea = diffArea;
            minIndex = i;
        }
        else if(diffArea==minArea && currArea<minCurrArea)
        {
            minArea=diffArea;
            minIndex=i;
        }
    }
    return chooseLeaf(currNode->entries[minIndex]->childNode, newrectangle);
}

// pick group representative for splitting current node
void pickSeeds(Node *currNode, int *seed1, int *seed2)
{
    printf("[Picking seeds]\n");
    int maxDiff = 0;
    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        for (int j = i + 1; j < currNode->noOfEntries; j++)
        {
            int minx=min(currNode->entries[i]->rectangle->pairX.minLimit,currNode->entries[j]->rectangle->pairX.minLimit);
            int miny=min(currNode->entries[i]->rectangle->pairY.minLimit,currNode->entries[j]->rectangle->pairY.minLimit);
            int maxx=max(currNode->entries[i]->rectangle->pairX.maxLimit,currNode->entries[j]->rectangle->pairX.maxLimit);
            int maxy=max(currNode->entries[i]->rectangle->pairY.maxLimit,currNode->entries[j]->rectangle->pairY.maxLimit);
            MBR* unionRect=createMBR(minx,maxx,miny,maxy);

            int diff = findArea(unionRect)-findArea(currNode->entries[i]->rectangle)-findArea(currNode->entries[j]->rectangle);
            diff=abs(diff);

            if (diff > maxDiff)
            {
                maxDiff = diff;
                *seed1 = i;
                *seed2 = j;
            }
        }
    }
    printf("[Exiting pickSeeds]\n");
    return;
}

// decide which entry to choose next, and which group to put it in
int pickNext(Node *currNode, Entry *group1,Entry *group2,bool* res)
{
    printf("[Entering pickNext]\n");
    
    int maxDiff = 0;
    int maxIndex = 0;
    MBR *g1rect = group1->rectangle;
    MBR *g2rect = group2->rectangle;
    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        if(currNode->entries[i]->rectangle==NULL)
        {
            continue;
        }
        int minx=min(g1rect->pairX.minLimit,currNode->entries[i]->rectangle->pairX.minLimit);
        int miny=min(g1rect->pairY.minLimit,currNode->entries[i]->rectangle->pairY.minLimit);
        int maxx=max(g1rect->pairX.maxLimit,currNode->entries[i]->rectangle->pairX.maxLimit);
        int maxy=max(g1rect->pairY.maxLimit,currNode->entries[i]->rectangle->pairY.maxLimit);
        MBR* newRect1=createMBR(minx,maxx,miny,maxy);
        int diff1 = findArea(newRect1)-findArea(g1rect);

        minx=min(g2rect->pairX.minLimit,currNode->entries[i]->rectangle->pairX.minLimit);
        miny=min(g2rect->pairY.minLimit,currNode->entries[i]->rectangle->pairY.minLimit);
        maxx=max(g2rect->pairX.maxLimit,currNode->entries[i]->rectangle->pairX.maxLimit);
        maxy=max(g2rect->pairY.maxLimit,currNode->entries[i]->rectangle->pairY.maxLimit);
        MBR* newRect2=createMBR(minx,maxx,miny,maxy);
        int diff2 = findArea(newRect2)-findArea(g2rect);

        int diff = abs(diff1 - diff2);
        if (diff > maxDiff)
        {
            maxDiff = diff;
            maxIndex = i;
            if(diff1<diff2)
            {
                *res=true;
            }
            else if(diff1>diff2)
            {
                *res=false;
            }
            else if(findArea(g1rect)<findArea(g2rect))
            {
                *res=true;
            }
            else if(findArea(g1rect)>findArea(g2rect))
            {
                *res=false;
            }
            else if(group1->childNode->noOfEntries<group2->childNode->noOfEntries)
            {
                *res=true;
            }
            else
            {
                *res=false;
            }
        }
    }

    printf("[Exiting pickNext]\n");
    return maxIndex;
}

// split the node into two groups
void quadraticSplit(Node *currNode, rTree *tree)
{
    printf("[Entering Split]\n");
    int seed1,seed2;
    pickSeeds(currNode,&seed1,&seed2);
    Node *group1 = createNode(NULL,currNode,tree);
    Node *group2 = createNode(NULL,currNode,tree);
    if(currNode->isLeaf==true)
    {
        group1->isLeaf=true;
        group2->isLeaf=true;
        currNode->isLeaf=false;
    }
    else
    {
        group1->isLeaf=false;
        group2->isLeaf=false;
    }
    group1->noOfEntries=1;
    group2->noOfEntries=1;
    group1->entries[0]=currNode->entries[seed1];
    group2->entries[0]=currNode->entries[seed2];
    currNode->entries[seed2]=currNode->entries[currNode->noOfEntries-1];
    currNode->noOfEntries--;
    currNode->entries[seed1]=currNode->entries[currNode->noOfEntries-1];
    currNode->noOfEntries--;

    while(currNode->noOfEntries>0)
    {
        if(group1->noOfEntries==tree->maxChildren)
        {
            for(int i=0;i<currNode->noOfEntries;i++)
            {
                printEntry(currNode->entries[i]);
                group2->entries[group2->noOfEntries]=currNode->entries[i];
                group2->noOfEntries++;
            }
            currNode->noOfEntries=0;
            break;
        }
        else if(group2->noOfEntries==tree->maxChildren)
        {
            for(int i=0;i<currNode->noOfEntries;i++)
            {
                printEntry(currNode->entries[i]);
                group1->entries[group1->noOfEntries]=currNode->entries[i];
                group1->noOfEntries++;
            }
            currNode->noOfEntries=0;
            break;
        }
        else
        {
            bool res;
            int index=pickNext(currNode,group1->entries[0],group2->entries[0],&res);
            if(res)
            {
                group1->entries[group1->noOfEntries]=currNode->entries[index];
                group1->noOfEntries++;
            }
            else
            {
                group2->entries[group2->noOfEntries]=currNode->entries[index];
                group2->noOfEntries++;
            }
            printf("{");
            // free(currNode->entries[currNode->noOfEntries-1]);
            printEntry(currNode->entries[index]);
            printf("}\n");
            currNode->entries[index]=currNode->entries[currNode->noOfEntries-1];
            currNode->noOfEntries--;
        }
    }
    if(currNode->parent==NULL)
    {
        currNode->noOfEntries=2;
        currNode->entries[0]=createEntry(findMBR(group1),group1);
        group1->parentEntry=currNode->entries[0];
        currNode->entries[1]=createEntry(findMBR(group2),group2);
        group2->parentEntry=currNode->entries[1];
        group1->parent=currNode;
        group2->parent=currNode;
        tree->root=currNode;
        currNode->isLeaf=false;
    }
    else
    {
        printEntry(currNode->parentEntry);
        currNode->parentEntry->childNode=group1;
        currNode->parentEntry->rectangle=findMBR(group1);
        currNode->parent->entries[currNode->parent->noOfEntries]=createEntry(findMBR(group2),group2);
        currNode->parent->noOfEntries++;
        group1->parent=currNode->parent;
        group1->parentEntry=currNode->parentEntry;
        group2->parentEntry=currNode->parent->entries[currNode->parent->noOfEntries-1];
        group2->parent=currNode->parent;
        // TODO: abir
        if(currNode->parent->noOfEntries>tree->maxChildren)
        {
            quadraticSplit(currNode->parent,tree);
        }
    }
    printf("[Exiting Split]\n");
}

void adjustTree(Node *currNode, rTree *tree)
{
    printf("[Entering Adjust]\n");
    if (currNode == NULL)
    {
        return;
    }
    if (currNode->parent == NULL)
    {
        tree->root = currNode;
        return;
    }
    Node *parent = currNode->parent;
    for (int i = 0; i < parent->noOfEntries; i++)
    {
        if (parent->entries[i]->childNode == currNode)
        {
            parent->entries[i]->rectangle = findMBR(currNode);
            break;
        }
    }
    if (parent->noOfEntries >= tree->maxChildren)
    {
        quadraticSplit(parent, tree);
        adjustTree(parent->parent, tree);
    }
    else
    {
        adjustTree(parent, tree);
    }
    printf("[Exiting Adjust]\n");
}


void insert(rTree *tree, int minX, int maxX, int minY, int maxY)
{
    printf("[Entering Insert]\n");
    if(minX>maxX)
    {
        swap(&minX,&maxX);
    }
    if(minY>maxY)
    {
        swap(&minY,&maxY);
    }
    MBR *rect = createMBR(minX, maxX, minY, maxY);
    Node *currNode = chooseLeaf(tree->root, rect);
    Entry *entry = createEntry(rect, NULL);

    currNode->entries[currNode->noOfEntries] = entry;
    currNode->noOfEntries++;

    if (currNode->noOfEntries > tree->maxChildren)
    {
        //TODO: abir
        quadraticSplit(currNode, tree);
        adjustTree(currNode, tree);
    }
    else
    {
        adjustTree(currNode, tree);
    }
    printf("[Exiting Insert]\n");
}
