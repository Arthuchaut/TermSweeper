#include <stdio.h>
#include <stdlib.h>

#include "../lib/grid.h"
#include "../lib/interface.h"

#define MAX_READ_LEN 3

int main(int argc, char *argv[]) {
    char in[10];
    int xVector = 20;
    int yVector = 20;
    int x = NULL;
    int y = NULL;
    Grid *grid = construct(xVector, yVector);

    show(grid);

    while (!grid->win && !grid->over) {
        if (readCoords(grid, in, &x, &y)) reveal(grid, &grid->matrix[x][y]);
        else if (isExit(in)) exit(0);
        else {
            printf("Wrong coords.\n");
            await();
            show(grid);
        }
    }

    if (grid->win) {
        printf("Congratulations ! You found the %d mines ! :)\n\n", grid->totalMines);
    } else {
        printf("Uh... It seem's like you walked on a mine ...\n");
        printf("You had revealed %d%% of the grid.\n\n",
        (grid->totalRevealed * 100) / (grid->xVector * grid->yVector));
    }

    await();

    return 0;
}

