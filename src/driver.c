#include "rTrees.h"

int main()
{
    rTree *tree = createRtree(2, 4);
    // read the input from the file
    FILE *fp = fopen("src/data.txt", "r");
    int cnt=0;
    while(!feof(fp))
    {
        int x1, y1;
        fscanf(fp, "%d %d", &x1, &y1);
        printf("inserting (%d, %d), %d\n", x1, y1, cnt);
        insert(tree, x1, x1,y1, y1);
        cnt++;
    }
    fclose(fp);
    preOrderTraversal(tree);
    return 0;
    
}