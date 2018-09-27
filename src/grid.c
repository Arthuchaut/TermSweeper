#include <stdio.h>
#include "../lib/grid.h"
#include "../lib/exception.h"

Grid *construct(const int x, const int y) {
    Grid *grid = malloc(sizeof(Grid));
    (grid == NULL) ? raise("grid.h : malloc returns a NULL pointer.") : NULL;

    grid->xVector = x;
    grid->yVector = y;
    grid->totalMines = 0;

    grid->grid = malloc(sizeof(Cell *) * x);
    (grid->grid == NULL) ? raise("grid.h : malloc returns a NULL pointer.") : NULL;

    srand(time(NULL));

    for (int i = 0; i < x; ++i) {
        grid->grid[i] = malloc(sizeof(Cell) * y);
        (grid->grid[i] == NULL) ? raise("grid.h : malloc returns a NULL pointer.") : NULL;

        for (int j = 0; j < y; ++j) {
            _hydrate(grid, i, j);
        }
    }

    return grid;
}

void _hydrate(Grid *grid, const int x, const int y) {
    int isMine = (rand() % 6) == (rand() % 6);

    grid->grid[x][y].x = x;
    grid->grid[x][y].y = y;
    grid->grid[x][y].isMine = isMine;
    grid->grid[x][y].isRevealed = 0;
    grid->grid[x][y].adjacentMines = 0;
    grid->totalMines += isMine;
}

void show(const Grid *grid) {
    system("cls");

    for (int i = -1; i < grid->xVector; ++i) {
        for (int j = -1; j < grid->yVector; ++j) {
            if (i == -1 && j > -1) {
                (j == 0) ? printf("    ") : NULL;
                printf("%c   ", 65 + j);
            } else if (j == -1 && i > -1) {
                printf("%c   ", 65 + i);
            } else if (j > -1) {
                if (grid->grid[i][j].isRevealed) {
                    if (!grid->grid[i][j].isMine) {
                        if (grid->grid[i][j].adjacentMines) {
                            printf("%d   ", grid->grid[i][j].adjacentMines);
                        } else printf("*   ");
                    } else printf("x   ");
                } else printf("o   ");
            }
        }

        printf("\n\n");
    }
}

int pos(char input) {
    input = toupper(input);

    if (input < 65 || input > 91) raise("Invalid input.");

    return input - 65;
}

void reveal(Grid *grid, int x, int y, int all) {
    // if (grid->grid[x][y].isMine) return;

    grid->grid[x][y].adjacentMines = countAdjacentMines(grid, x, y);

    if (!all) {
        if (grid->grid[x][y].adjacentMines) {
            grid->grid[x][y].isRevealed = 1;
            show(grid);
        } else {
            revealSafeCells(grid, x, y);
        }
    } else grid->grid[x][y].isRevealed = 1;
}

int countAdjacentMines(Grid *grid, int x, int y) {
    int count = 0;

    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i >= 0 && i < grid->xVector &&
                j >= 0 && j < grid->yVector &&
                (i != x || j != y)) {
                count += grid->grid[i][j].isMine;
            }
        }
    }

    return count;
}

void revealSafeCells(Grid *grid, int x, int y) {
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i >= 0 && i < grid->xVector &&
                j >= 0 && j < grid->yVector) {
                if (!grid->grid[i][j].isMine && !grid->grid[i][j].adjacentMines) {
                    if (!grid->grid[i][j].isRevealed) {
                        grid->grid[i][j].isRevealed = 1;
                        show(grid);
                        reveal(grid, i, j, NULL);
                    }
                } else if (!grid->grid[i][j].isRevealed) {
                    grid->grid[i][j].isRevealed = 1;
                    show(grid);
                }
            }
        }
    }
}

void revealAll(Grid *grid) {
    for (int i = 0; i < grid->xVector; ++i) {
        for (int j = 0; j < grid->yVector; ++j) {
            reveal(grid, i, j, 1);
        }
    }

    show(grid);
}