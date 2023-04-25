#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "rTrees.h"

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
    rTree *tree;
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
