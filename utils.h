#ifndef UTILS_H_
#define UTILS_H_
#include "rTrees.h"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
#define INF 1e9

void swap(int *a,int *b);
void printEntry(Entry *Entry);
int findArea(MBR *rectangle);
MBR* findMBR(Node* currNode);
bool isOverlapping(MBR *rect1, MBR *rect2);
#endif

