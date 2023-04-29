#include "rTrees.h"

int main()
{
    rTree *tree = createRtree(2, 4);
    // read the input from the file
    FILE *fp = fopen("data/data.txt", "r");
    while(!feof(fp))
    {
        int x1, y1;
        fscanf(fp, "%d %d", &x1, &y1);
        point pt={x1,y1};
        insertPoint(tree, pt);
    }
    fclose(fp);
    printf("Number of nodes in the tree: %d\n", tree->no_of_nodes);

    return 0;
    
}