#include <stdbool.h>
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
struct Node // Node of the tree
{
    bool isLeaf;           // To check if it is a leaf node or not
    MBR boundingRectangle; // the rectangle bounding all of its children if it is a non leaf node
    int noOfChildren;      // for iterating througn the array of children.
    union
    {
        MBR *rectangle;    // Used if it is a leaf node and points to a rectangle which bounds our object.
        Node **childNodes; // Used if it is a non-leaf node
    } children;
};

typedef struct rTree rTree;
struct rTree
{
    int maxChildren; // M
    int minChildren; // m
    Node *root;      // root of the tree.
};
