#ifndef LIB_MENU_H
#define LIB_MENU_H

#include "../lib/grid.h"

#define NBSP 20 // The box width
#define STDIN_LEN 100 // The maximum characters to read

/**
 * Read the user command
 * 
 * @param {char *} args The user command
 * 
 * @returns {int} A Boolean indicating that the reading went well
 */
int read(char *args);

/**
 * Free the buffer
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void freeBuffer(void);

/**
 * Clear the console
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void clear(void);

/**
 * Patient before continuing the program
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void await(void);

/**
 * Print space to formatting a box in console
 * 
 * @param {char *} str The string to add spaces
 * 
 * @returns {void}
 */
void space(char *str);

/**
 * Print a line for formating a box in console
 * 
 * @param {char *} str The string to add line
 * 
 * @returns {void}
 */
void printLine(char *str);

/**
 * Print statistics of the current game
 * 
 * @param {const Grid *} grid The Grid pointer
 * 
 * @returns {void}
 */
void printStats(const Grid *grid);

/**
 * Print help on commands to play
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void printHelp(void);

/**
 * Print the rules of the game
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void printRules(void);

/**
 * Print the menu
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void menu(void);

#endif