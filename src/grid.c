#include <stdio.h>
#include <conio.h>
#include "../lib/grid.h"
#include "../lib/interface.h"
#include "../lib/exception.h"

Grid *construct(const int xVector, const int yVector) {
    Grid *grid = malloc(sizeof(Grid));
    (grid == NULL) ? raise("grid.h : malloc returns a NULL pointer.") : NULL;

    srand(time(NULL));

    grid->xVector = xVector;
    grid->yVector = yVector;
    grid->totalMines = 0;
    grid->totalRevealed = 0;
    grid->over = 0;
    grid->win = 0;

    _hydrateMatrix(grid);

    return grid;
}

void _hydrateMatrix(Grid *grid) {
    grid->matrix = malloc(sizeof(Cell *) * grid->xVector);
    (grid->matrix == NULL) ? raise("grid.h : malloc returns a NULL pointer.") : NULL;

    for (int i = 0; i < grid->xVector; ++i) {
        grid->matrix[i] = malloc(sizeof(Cell) * grid->yVector);
        (grid->matrix[i] == NULL) ? raise("grid.h : malloc returns a NULL pointer.") : NULL;

        for (int j = 0; j < grid->yVector; ++j) {
            _hydrateCell(grid, i, j);
        }
    }

    each(grid, &_countAdjacentMines);
}

void _hydrateCell(Grid *grid, const int x, const int y) {
    int isMine = (rand() % 6) == (rand() % 6);

    grid->matrix[x][y].x = x;
    grid->matrix[x][y].y = y;
    grid->matrix[x][y].isMine = isMine;
    grid->matrix[x][y].isRevealed = 0;
    grid->matrix[x][y].adjacentMines = 0;

    grid->totalMines += isMine;
}

void each(Grid *grid, void (*func)(Grid *, Cell *)) {
    for (int i = 0; i < grid->xVector; ++i) {
        for (int j = 0; j < grid->yVector; ++j) {
            func(grid, &grid->matrix[i][j]);
        }
    }
}

void _countAdjacentMines(Grid *grid, Cell *cell) {
    for (int i = cell->x - 1; i <= cell->x + 1; ++i) {
        for (int j = cell->y - 1; j <= cell->y + 1; ++j) {
            if (i >= 0 && i < grid->xVector &&
                j >= 0 && j < grid->yVector &&
                (i != cell->x || j != cell->y)) {
                cell->adjacentMines += grid->matrix[i][j].isMine;
            }
        }
    }
}

void show(const Grid *grid) {
    clear();

    printf("    ");
    for (int i = 0; i < grid->xVector; ++i) printf("%c   ", 65 + i);
    printf("\n\n");

    for (int i = 0; i < grid->xVector; ++i) {
        printf("%c   ", 65 + i);
        for (int j = 0; j < grid->yVector; ++j) {
            if (grid->matrix[i][j].isRevealed) {
                if (!grid->matrix[i][j].isMine) {
                    if (grid->matrix[i][j].adjacentMines) {
                        printf("%d   ", grid->matrix[i][j].adjacentMines);
                    } else printf("%s   ", SAFE);
                } else printf("%s   ", MINE);
            } else printf("%s   ", EMPTY);
        }
        printf("\n\n");
    }
}

void reveal(Grid *grid, Cell *cell) {
    cell->isRevealed = 1;
    ++grid->totalRevealed;
    
    if (cell->isMine) grid->over = 1;

    if (!cell->adjacentMines) _revealSafeCells(grid, cell);

    grid->win = (grid->totalRevealed == (grid->xVector * grid->yVector) - grid->totalMines);

    show(grid);
}

void _revealSafeCells(Grid *grid, Cell *cell) {
    for (int i = cell->x - 1; i <= cell->x + 1; ++i) {
        for (int j = cell->y - 1; j <= cell->y + 1; ++j) {
            if (i >= 0 && i < grid->xVector &&
                j >= 0 && j < grid->yVector) {
                if (!grid->matrix[i][j].isMine && !grid->matrix[i][j].adjacentMines) {
                    if (!grid->matrix[i][j].isRevealed) {
                        grid->matrix[i][j].isRevealed = 1;
                        ++grid->totalRevealed;
                        _revealSafeCells(grid, &grid->matrix[i][j]);
                    }
                } else if (!grid->matrix[i][j].isRevealed) {
                    grid->matrix[i][j].isRevealed = 1;
                    ++grid->totalRevealed;
                }
            }
        }
    }
}

int readCoords(const Grid *grid, const char *str, int *x, int *y) {
    printf("Coords : ");

    if (!read(str)) raise("Could not read the buffer.");

    *x = toupper(str[0]) - 65;
    *y = toupper(str[1]) - 65;

    return (*x < grid->xVector && *x >= 0 &&
            *y < grid->yVector && *y >= 0);
}