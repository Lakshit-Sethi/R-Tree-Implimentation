#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "rTrees.h"
const int INF = 1e9;
MBR *createMBR(int minX, int maxX, int minY, int maxY)
{
    MBR *rectangle = (MBR *)malloc(sizeof(MBR));
    rectangle->pairX.minLimit = minX;
    rectangle->pairX.maxLimit = maxX;
    rectangle->pairY.minLimit = minY;
    rectangle->pairY.maxLimit = maxY;
    return rectangle;
}

Node *createNode(Entry *parent, rTree *tree)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->noOfEntries = 0;
    node->isLeaf = 0;
    node->parent = parent;
    node->entries = (Entry **)malloc(tree->maxChildren * (sizeof(Entry *)));
    return node;
}

Entry *createEntry(MBR *rectangle, Node *child)
{
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    entry->childNode = child;
    entry->rectangle = rectangle;
    return entry;
}

rTree *createRtree(int minchild, int maxchild)
{
    rTree *tree= (rTree *)malloc(sizeof(rTree));
    tree->minChildren = minchild;
    tree->maxChildren = maxchild;
    tree->start = (Entry *)malloc(sizeof(Entry));
    tree->start->rectangle = NULL;
    tree->root = createNode(tree->start, tree);
    tree->root->isLeaf = 1;
    return tree;
}

void printEntry(Entry *Entry)
{
    MBR *MBR = Entry->rectangle;
    if(MBR==NULL)
    {
        return;
    }
    printf("Top Right -> %d,%d\n", MBR->pairX.maxLimit, MBR->pairY.maxLimit);
    printf("Bottom Left -> %d,%d\n", MBR->pairX.minLimit, MBR->pairY.minLimit);
    return;
}

void traverse(Node *currNode)
{
    if (currNode == NULL)
    {
        return;
    }
    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        printEntry(currNode->entries[i]);
        traverse(currNode->entries[i]->childNode);
    }
    return;
}



void preOrderTraversal(rTree *tree)
{
    printEntry(tree->start);
    traverse(tree->root);
}


int findArea(MBR *rectangle)
{
    int length=rectangle->pairX.maxLimit-rectangle->pairX.minLimit;
    int breadth=rectangle->pairY.maxLimit-rectangle->pairY.minLimit;
    return length*breadth;
}

// TODO: check if min max functions are correct
// TODO: check minimum maximum x and y when creating a new rectangle
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
        int area = newArea - currArea;
        int minCurrArea = min(minCurrArea, currArea);
        if (area < minArea)
        {
            minArea = area;
            minIndex = i;
        }
        else if(area==minArea && currArea<minCurrArea)
        {
            minArea=area;
            minIndex=i;
        }
    }
    return chooseLeaf(currNode->entries[minIndex]->childNode, newrectangle);
}


// pick seeds for splitting
void pickSeeds(Node *currNode, int *seed1, int *seed2)
{
    int maxDiff = 0;
    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        for (int j = i + 1; j < currNode->noOfEntries; j++)
        {
            int minx=min(currNode->entries[i]->rectangle->pairX.minLimit,currNode->entries[j]->rectangle->pairX.minLimit);
            int miny=min(currNode->entries[i]->rectangle->pairY.minLimit,currNode->entries[j]->rectangle->pairY.minLimit);
            int maxx=max(currNode->entries[i]->rectangle->pairX.maxLimit,currNode->entries[j]->rectangle->pairX.maxLimit);
            int maxy=max(currNode->entries[i]->rectangle->pairY.maxLimit,currNode->entries[j]->rectangle->pairY.maxLimit);
            MBR* newRect=createMBR(minx,maxx,miny,maxy);
            int diff = findArea(newRect)-findArea(currNode->entries[i]->rectangle)-findArea(currNode->entries[j]->rectangle);
            diff=abs(diff);
            if (diff > maxDiff)
            {
                maxDiff = diff;
                *seed1 = i;
                *seed2 = j;
            }
        }
    }
    return;
}

// pick next entry to be added to a group
// TODO : skip the entries that are already added to a group
int pickNext(Node *currNode, Entry *group1,Entry *group2,bool* res)
{
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
    return maxIndex;
}

// quadratic split
void quadraticSplit(Node *currNode, rTree *tree)
{
    int seed1,seed2;
    pickSeeds(currNode,&seed1,&seed2);
    Node *group1 = createNode(currNode->isLeaf,tree);
    Node *group2 = createNode(currNode->isLeaf,tree);
    group1->noOfEntries=1;
    group2->noOfEntries=1;
    group1->entries[0]=currNode->entries[seed1];
    group2->entries[0]=currNode->entries[seed2];
    currNode->entries[seed1]=NULL;
    currNode->entries[seed2]=NULL;
    currNode->noOfEntries-=2;
    while(currNode->noOfEntries>0)
    {
        if(group1->noOfEntries==tree->maxChildren)
        {
            for(int i=0;i<currNode->noOfEntries;i++)
            {
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
            currNode->entries[index]=currNode->entries[currNode->noOfEntries-1];
            currNode->noOfEntries--;
        }
    }
}

// adjust tree after insertion
void adjustTree(Node *currNode, rTree *tree)
{
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
}

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

//write insert function using choose leaf, quadratic split and adjust tree
void insert(rTree *tree, int x1, int y1, int x2, int y2)
{
    if(x1>x2)
    {
        swap(x1,x2);
    }
    if(y1>y2)
    {
        swap(y1,y2);
    }
    MBR *rect = createMBR(x1, x2, y1, y2);
    Node *currNode = chooseLeaf(tree->root, rect);
    Entry *entry = createEntry(rect, NULL);

    currNode->entries[currNode->noOfEntries] = entry;
    currNode->noOfEntries++;

    if (currNode->noOfEntries > tree->maxChildren)
    {
        quadraticSplit(currNode, tree);
        adjustTree(currNode, tree);
    }
    else
    {
        adjustTree(currNode, tree);
    }
}

// search overlapping rectangles
void search(Node *currNode, MBR *rect)
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
                printEntry(currNode->entries[i]);
            }
        }
        return;
    }

    for (int i = 0; i < currNode->noOfEntries; i++)
    {
        if (isOverlapping(currNode->entries[i]->rectangle, rect))
        {
            search(currNode->entries[i]->childNode, rect);
        }
    }
    
}

bool isOverlapping(MBR *rect1, MBR *rect2)
{
    if (rect1->pairX.minLimit > rect2->pairX.maxLimit || rect1->pairX.maxLimit < rect2->pairX.minLimit)
    {
        return false;
    }
    if (rect1->pairY.minLimit > rect2->pairY.maxLimit || rect1->pairY.maxLimit < rect2->pairY.minLimit)
    {
        return false;
    }
    return true;
}

// write main to create a tree
int main()
{
    rTree *tree = createRtree(2, 4);
    preOrderTraversal(tree);
    return 0;
}