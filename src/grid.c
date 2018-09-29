#include <stdio.h>
#include <stdlib.h>

#include "../lib/grid.h"
#include "../lib/interface.h"
#include "../lib/exception.h"

/**
 * Initialize the grid
 * 
 * @param {const int} xVector The row size
 * @param {const int} yVector The column size
 * 
 * @returns {Grid *} A Grid pointer
 */ 
Grid *construct(const int xVector, const int yVector) {
    Grid *grid = malloc(sizeof(Grid));
    (grid == NULL) ? raise("grid.h : malloc returns a NULL pointer.") : NULL;

    srand(time(NULL));

    grid->xVector = xVector;
    grid->yVector = yVector;
    grid->totalMines = 0;
    grid->totalRevealed = 0;
    grid->totalFlags = 0;
    grid->over = 0;
    grid->win = 0;

    _hydrateMatrix(grid);

    return grid;
}

/**
 * Create the matrix of cells
 * 
 * @param {Grid *} grid A Grid pointer
 * 
 * @returns {void}
 */
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

/**
 * Initialize the cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {const int} x The row coordinate
 * @param {const int} y The column coordinate
 * 
 * @returns {void}
 */
void _hydrateCell(Grid *grid, const int x, const int y) {
    int isMine = (rand() % 6) == (rand() % 6);

    grid->matrix[x][y].x = x;
    grid->matrix[x][y].y = y;
    grid->matrix[x][y].isMine = isMine;
    grid->matrix[x][y].isRevealed = 0;
    grid->matrix[x][y].isFlagged = 0;
    grid->matrix[x][y].adjacentMines = 0;

    grid->totalMines += isMine;
}

/**
 * Loop on the grid
 * Call a callback function for each cell
 * 
 * @param {Grid *} grid The Grid pointer to loop for
 * @param {function *} The callback pointer
 *      @param {Grid *} The Grid pointer
 *      @param {Cell *} The iterated Cell pointer
 * 
 * @returns {void}
 */
void each(Grid *grid, void (*func)(Grid *, Cell *)) {
    for (int i = 0; i < grid->xVector; ++i) {
        for (int j = 0; j < grid->yVector; ++j) {
            func(grid, &grid->matrix[i][j]);
        }
    }
}

/**
 * Counts all adjacent mines in a given cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer
 * 
 * @returns {void}
 */
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

/**
 * Print the grid on the console
 * 
 * @param {const Grid *} grid The Grid pointer
 * 
 * @returns {void}
 */
void show(const Grid *grid) {
    clear();
    printHelp();

    printf("%s ", SP);
    for (int i = 0; i < grid->xVector; ++i) printf("%c%s", 65 + i, SP);
    printf("\n\n");

    for (int i = 0; i < grid->xVector; ++i) {
        printf("%c%s", 65 + i, SP);
        for (int j = 0; j < grid->yVector; ++j) {
            if (grid->matrix[i][j].isFlagged) {
                    printf("%s%s", FLAG, SP);
            } else if (grid->matrix[i][j].isRevealed) {
                if (!grid->matrix[i][j].isMine) {
                    if (grid->matrix[i][j].adjacentMines) {
                        printf("%d%s", grid->matrix[i][j].adjacentMines, SP);
                    } else printf("%s%s", SAFE, SP);
                } else printf("%s%s", MINE, SP);
            } else printf("%s%s", EMPTY, SP);
        }
        printf("\n\n");
    }

    printStats(grid);
}

/**
 * Reveal a cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The cell pointer to reveal
 * 
 * @returns {void}
 */
void reveal(Grid *grid, Cell *cell) {
    cell->isRevealed = 1;
    ++grid->totalRevealed;

    if (cell->isFlagged) {
        cell->isFlagged = 0;
        --grid->totalFlags;
    }
    
    if (cell->isMine) {
        grid->over = 1;
        each(grid, &setReveal);
        show(grid);
        return;
    }

    if (!cell->adjacentMines) _revealSafeCells(grid, cell);

    grid->win = (grid->totalRevealed == (grid->xVector * grid->yVector) - grid->totalMines);

    show(grid);
}

/**
 * Reveal the cell without conditions (for the end game)
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer to reveal
 * 
 * @returns {void}
 */
void setReveal(Grid *grid, Cell *cell) {
    if (!cell->isFlagged) cell->isRevealed = 1;
}

/**
 * Unflag a cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer to unflag
 * 
 * @returns {void}
 */
void unflag(Grid *grid, Cell *cell) {
    if (cell->isFlagged) {
        cell->isFlagged = 0;
        --grid->totalFlags;
    }

    show(grid);
}

/**
 * Flag a cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer to flag
 * 
 * @returns {void}
 */
void flag(Grid *grid, Cell *cell) {
    if (!cell->isRevealed && !cell->isFlagged) {
        cell->isFlagged = 1;
        ++grid->totalFlags;
    }

    show(grid);
}

/**
 * Recurvise function to reveal all adjacent safe cells 
 * relatives to an initial cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer
 * 
 * @returns {void}
 */
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

/**
 * Read the user command
 * 
 * @param {char *} args The user command
 * 
 * @returns {int | NULL} A number indicating which command has been entered
 */
int command(char *args) {
    if (strlen(args) < 2 || strlen(args) > 4) return 0;

    if (strlen(args) == 3) {
        if (args[0] == IFLAG) return 1;
        if (args[0] == IUNFLAG) return 2;

        return NULL;
    }

    if (strlen(args) == 4) {
        if (!strcmp(args, IEXIT)) return 4;

        return NULL;
    }

    return 3;
}

/**
 * Display an error message if the command is not exists
 * 
 * @param {const Grid *} grid The Grid pointer
 * @param {const char *} msg The message to print
 * 
 * @returns {void}
 */
void wrongCommand(const Grid *grid, const char *msg) {
    printf("%s\n", msg);
    await();
    show(grid);
}

/**
 * Return and (x;y) coordinate from the user command
 * 
 * @param {const Grid *} grid The Grid pointer
 * @param {const char *} str The user command
 * @param {int *} x The x pointer to be assigned
 * @param {int *} y The y pointer to be assigned
 * 
 * @returns {int} A Boolean indicating that the coordinates have been calculated
 */
int coords(const Grid *grid, const char *str, int *x, int *y) {
    *x = toupper(str[0]) - 65;
    *y = toupper(str[1]) - 65;

    if (*x < grid->xVector && *x >= 0 &&
        *y < grid->yVector && *y >= 0) {
        if (!grid->matrix[*x][*y].isRevealed) return 1;
    }

    return 0;
}

/**
 * Get the percentage of revealed cells
 * 
 * @param {const Grid *} grid The Grid pointer
 * 
 * @returns {int} The percentage
 */
int percentage(const Grid *grid) {
    return (grid->totalRevealed * 100) / (grid->xVector * grid->yVector);
}

/**
 * Load the game
 * 
 * @param {const int} xVector The row size
 * @param {const int} yVector The column size
 * 
 * @returns {void}
 */
void start(const int xVector, const int yVector) {
    char args[STDIN_LEN], sub[4], error[STDIN_LEN];
    int x = NULL, y = NULL;
    Grid *grid = construct(xVector, yVector);

    show(grid);

    while (!grid->win && !grid->over) {
        if (read(args)) {
            switch (command(args)) {
                case 1: // Flag
                    memcpy(sub, &args[1], 2);
                    sub[2] = '\0';

                    if (coords(grid, sub, &x, &y)) {    
                        flag(grid, &grid->matrix[x][y]);
                    } else {
                        sprintf(error, "Coords (%d;%d) doesn't exists.", x, y);
                        wrongCommand(grid, error);
                    }
                    break;
                case 2: // Unflag
                    memcpy(sub, &args[1], 2);
                    sub[2] = '\0';

                    if (coords(grid, sub, &x, &y)) {
                        unflag(grid, &grid->matrix[x][y]);
                    } else {
                        sprintf(error, "Coords (%d;%d) doesn't exists.", x, y);
                        wrongCommand(grid, error);
                    }
                    break;
                case 3: // Reveal
                    if (coords(grid, args, &x, &y)) {
                        reveal(grid, &grid->matrix[x][y]);
                    } else {
                        sprintf(error, "Coords (%d;%d) doesn't exists.", x, y);
                        wrongCommand(grid, error);
                    }
                    break;
                case 4: // Exit
                    printf("Return to the menu ...\n");
                    return;
                    break;
                default: // Wrong command
                    wrongCommand(grid, "Wrong command.");
            }
        }
    }

    if (grid->win) {
        printf("Congratulations ! You found the %d mines ! :)\n\n", grid->totalMines);
    } else {
        printf("Um... It looks like you stepped on a mine...\n");
        printf("You revealed %d%% of the grid.\n\n", percentage(grid));
    }
}