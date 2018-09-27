#ifndef LIB_GRID_H
#define LIB_GRID_H

#define MINE "x"
#define SAFE "#"
#define EMPTY "."

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
    int totalRevealed;
    int win;
    int over;
    Cell **matrix;
} Grid;

Grid *construct(const int xVector, const int yVector);

void _hydrateMatrix(Grid *grid);

void _hydrateCell(Grid *grid, const int x, const int y);

void each(Grid *grid, void (*func)(Grid *, Cell *));

void _countAdjacentMines(Grid *grid, Cell *cell);

void show(const Grid *grid);

void reveal(Grid *grid, Cell *cell);

void _revealSafeCells(Grid *grid, Cell *cell);

void _clear(void);

int readCoords(const Grid *grid, const char *str, int *x, int *y);

#endif