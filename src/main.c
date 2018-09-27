#include <stdio.h>
#include <stdlib.h>

#include "../lib/grid.h"
#include "../lib/interface.h"

#define MAX_READ_LEN 3

int main(int argc, char *argv[]) {
    char *in;
    Grid *grid = construct(10, 10);
    // read(in);
    show(grid);
    // printf("%d %d %d\n", grid->grid[pos(in[0])][pos(in[1])]);

    // printf("%d\n", grid->totalMines);

    reveal(grid, 2, 2, NULL);

    system("pause");

    return 0;
}