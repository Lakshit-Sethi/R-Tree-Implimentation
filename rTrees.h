#include <stdbool.h>
typedef struct pair pair;
struct pair
{
    int minLimit;
    int maxLimit;
};

typedef struct MBR MBR;
struct MBR
{
    pair pairX;
    pair pairY;
};

typedef struct Node Node;
struct Node
{
    bool isLeaf;
    MBR boundingRectangle;
    int noOfChildren;
    union
    {
        MBR *rectangle;
        Node **childNodes;
    } children;
};

typedef struct rTree rTree;
struct rTree
{
    int maxChildren;
    int minChildren;
    Node *root;
};