#ifndef LIB_GRID_H
#define LIB_GRID_H

#define SP "   " // The space to seperate cells

#define MINE "x" // The mine character
#define SAFE "*" // The safe cell character
#define FLAG "F" // The flagged cell character
#define EMPTY "." // The unrevealed cell character

#define IFLAG 'f' // The flag command
#define IUNFLAG 'u' // The unflag command
#define IEXIT "menu" // The menu command

/**
 * The Cell strcture
 * 
 * @attr {int} x The x coordinate
 * @attr {int} y The y coordinate
 * @attr {int} isMine
 * @attr {int} isRevealed
 * @attr {int} isFlagged
 * @attr {int} adjacentMines
 */
typedef struct Cell {
    int x;
    int y;
    int isMine;
    int isRevealed;
    int isFlagged;
    int adjacentMines;
} Cell;

/**
 * The Grid strcture
 * 
 * @attr {int} xVector The row size
 * @attr {int} yVector The column size
 * @attr {int} totalMines
 * @attr {int} totalRevealed
 * @attr {int} totalFlags
 * @attr {int} win The boolean to indicate if win
 * @attr {int} over The boolean to indicate if game over
 * @attr {Cell **} matrix The grid of cells
 */
typedef struct Grid {
    int xVector;
    int yVector;
    int totalMines;
    int totalRevealed;
    int totalFlags;
    int win;
    int over;
    Cell **matrix;
} Grid;

/**
 * Initialize the grid
 * 
 * @param {const int} xVector The row size
 * @param {const int} yVector The column size
 * 
 * @returns {Grid *} A Grid pointer
 */ 
Grid *construct(const int xVector, const int yVector);

/**
 * Create the matrix of cells
 * 
 * @param {Grid *} grid A Grid pointer
 * 
 * @returns {void}
 */
void _hydrateMatrix(Grid *grid);

/**
 * Initialize the cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {const int} x The row coordinate
 * @param {const int} y The column coordinate
 * 
 * @returns {void}
 */
void _hydrateCell(Grid *grid, const int x, const int y);

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
void each(Grid *grid, void (*func)(Grid *, Cell *));

/**
 * Counts all adjacent mines in a given cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer
 * 
 * @returns {void}
 */
void _countAdjacentMines(Grid *grid, Cell *cell);

/**
 * Print the grid on the console
 * 
 * @param {const Grid *} grid The Grid pointer
 * 
 * @returns {void}
 */
void show(const Grid *grid);

/**
 * Reveal a cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The cell pointer to reveal
 * 
 * @returns {void}
 */
void reveal(Grid *grid, Cell *cell);

/**
 * Reveal the cell without conditions (for the end game)
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer to reveal
 * 
 * @returns {void}
 */
void setReveal(Grid *grid, Cell *cell);

/**
 * Unflag a cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer to unflag
 * 
 * @returns {void}
 */
void unflag(Grid *grid, Cell *cell);

/**
 * Flag a cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer to flag
 * 
 * @returns {void}
 */
void flag(Grid *grid, Cell *cell);

/**
 * Recurvise function to reveal all adjacent safe cells 
 * relatives to an initial cell
 * 
 * @param {Grid *} grid The Grid pointer
 * @param {Cell *} cell The Cell pointer
 * 
 * @returns {void}
 */
void _revealSafeCells(Grid *grid, Cell *cell);

/**
 * Read the user command
 * 
 * @param {char *} args The user command
 * 
 * @returns {int | NULL} A number indicating which command has been entered
 */
int command(char *args);

/**
 * Display an error message if the command is not exists
 * 
 * @param {const Grid *} grid The Grid pointer
 * @param {const char *} msg The message to print
 * 
 * @returns {void}
 */
void wrongCommand(const Grid *grid, const char *msg);

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
int coords(const Grid *grid, const char *str, int *x, int *y);

/**
 * Get the percentage of revealed cells
 * 
 * @param {const Grid *} grid The Grid pointer
 * 
 * @returns {int} The percentage
 */
int percentage(const Grid *grid);

/**
 * Load the game
 * 
 * @param {const int} xVector The row size
 * @param {const int} yVector The column size
 * 
 * @returns {void}
 */
void start(const int xVector, const int yVector);

#endif