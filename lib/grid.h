#ifndef LIB_GRID_H
#define LIB_GRID_H

typedef struct Cell {
    int x;
    int y;
    int isMine;
    int isRevealed;
    int adjacentMines;
} Cell;

typedef struct Grid {
    int xVector;
    int yVector;
    int totalMines;
    Cell **grid;
} Grid;

Grid *construct(const int x, const int y);

void _hydrate(Grid *grid, const int x, const int y);

void show(const Grid *grid);

int pos(char input);

void revealSafeCells(Grid *grid, int x, int y);

void reveal(Grid *grid, int x, int y, int all);

void revealAll(Grid *grid);

int countAdjacentMines(Grid *grid, int x, int y);

#endif