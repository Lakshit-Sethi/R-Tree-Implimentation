#include "rTrees.h"

int main()
{
    rTree *tree = createRtree(2, 4);
    insert(tree, 1, 2, 3, 4);
    insert(tree, 3, 5, 9, 14);
    insert(tree, 11, 12, 13, 14);
    insert(tree, 15, 17, 30, 37);
    insert(tree, 10, 20, 30, 40);
    insert(tree, 5, 7, 8, 9);
    insert(tree,3,5,3,40);
    preOrderTraversal(tree);
    search(tree,3,5,3,40);
    return 0;
}