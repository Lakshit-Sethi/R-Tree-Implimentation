#include "rTrees.h"

int main()
{
    // create a tree with minimum degree 2 and maximum degree 4
    rTree *tree = createRtree(2, 4);
    // inserting a polygon
    polygon pt=(polygon)malloc(sizeof(point)*8);
    pt[0].x=0;pt[0].y=0;
    pt[1].x=-1;pt[1].y=1;
    pt[2].x=0;pt[2].y=1;
    pt[3].x=1;pt[3].y=1;
    pt[4].x=2;pt[4].y=1;
    pt[5].x=2;pt[5].y=1;
    pt[6].x=3;pt[6].y=0;
    pt[7].x=4;pt[7].y=0;
    insertPolygon(tree,pt,8);
    preOrderTraversal(tree);
    // // insert the following entries
    // insert(tree, 1, 2, 3, 4);
    // insert(tree, 3, 5, 9, 14);
    // insert(tree, 11, 12, 13, 14);
    // insert(tree, 15, 17, 30, 53);
    // insert(tree, 10, 20, 30, 40);
    // insert(tree, 5, 7, 8, 9);

    // // traverse the tree
    // // preOrderTraversal(tree);

    // // insert some more entries
    // insert(tree, 3, 5, 3, 40);

    // // traverse the tree
    // // preOrderTraversal(tree);

    // // search for all entries that overlap with the rectangle with bottom left corner (3,3) and top right corner (5,40)
    // insert(tree, 1, 2, 6, 12);
    // // preOrderTraversal(tree);
    // insert(tree, 2, 3, 7, 11);
    // insert(tree, 2, 3, 8, 12);
    // preOrderTraversal(tree);
    // insert(tree, 2, 3, 9, 10);
    // preOrderTraversal(tree);

    // // search for all entries that overlap with the rectangle with bottom left corner (3,3) and top right corner (5,40)
    // search(tree,3,5,3,40);
    return 0;
    
}