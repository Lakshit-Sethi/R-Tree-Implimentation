#include <stdbool.h>
#include <stdlib.h>
typedef struct pair pair;
struct pair // stores maximum and minimum limits of any dimension(In our case only 2-D)
{
    int minLimit;
    int maxLimit;
};

typedef struct MBR MBR; // Minimum bounding rectangle storing the limits in different dimensions.
struct MBR
{
    pair pairX;
    pair pairY;
};

typedef struct Node Node;
typedef struct Entry Entry;
struct Node // Node of the tree
{
    int noOfEntries;
    bool isLeaf;
    Entry **entries;
    Entry *parentEntry;
    Node *parent;
};

struct Entry
{
    MBR *rectangle;
    Node *childNode;
};

typedef struct rTree rTree;
struct rTree
{
    int maxChildren; // M
    int minChildren; // m
    Entry *start;    // contains a pointer to root of the tree.
    Node *root;
};

MBR *createMBR(int minX, int maxX, int minY, int maxY);
Node *createNode(Entry *parentEntry,Node* parentNode, rTree *tree);
Entry *createEntry(MBR *rectangle, Node *child);
rTree *createRtree(int minchild, int maxchild);
